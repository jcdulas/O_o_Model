"""Installed-wheel tests, including interoperability with a separate PyArrow installation."""
import gc
import tempfile
from pathlib import Path

import numpy as np
import oo_model
import oo_reader

# In the isolated wheel test the legacy import resolves to the same native types.
assert oo_reader.Deck is oo_model.Deck


def check_builder():
    deck = oo_model.create_model()
    added = deck.add_card_batch("Node", {
        "id": np.arange(1, 5, dtype=np.int32)[::2],
        "position1": np.array([0., 2.]),
        "position2": 0.,
    })
    assert added["ids"].tolist() == [1, 3]
    assert deck.add_card("Rod2", [2, 7, 1, 3])["id"] == 2
    deck.add_cards([
        {"type": "RodProp", "fields": {"id": 7, "matId": 8, "area": 1.}},
        {"type": "IsoMat", "fields": [8, 210e9, None, 0.3]},
    ])
    assert not deck.check_references()
    before = deck.card_counts
    for columns in ({"id": [11, 1]}, {"id": [11, 12], "position1": [0.]},
                    {"id": np.array([13, 2**63], dtype=np.uint64)},
                    {"id": [14], "position1": np.complex64(1+2j)},
                    {"id": [14], "position1": np.array([1+2j], dtype=np.complex64)}):
        try:
            deck.add_card_batch("Node", columns)
        except (TypeError, ValueError, RuntimeError):
            assert deck.card_counts == before
        else:
            raise AssertionError("invalid batch accepted")
    return deck


memory_deck = check_builder()
trial = memory_deck.copy()
ids = np.array([3, 1], dtype=np.int32)
xyz = np.array([[3., 4., 5.], [6., 7., 8.]])
before = trial.versions
for bad_ids, bad_xyz in ((ids.astype(np.int64), xyz), (ids, xyz.ravel()),
                         (ids, xyz.astype(np.float32)), (ids, xyz[:, ::-1]),
                         (np.array([3, 99], dtype=np.int32), xyz)):
    try:
        trial.set_node_positions(bad_ids, bad_xyz)
    except (TypeError, ValueError, RuntimeError):
        assert trial.versions == before
    else:
        raise AssertionError("invalid position batch accepted")
trial.set_node_positions(ids, xyz)
assert trial.versions[0] == before[0]
assert trial.versions[1] != before[1]

with tempfile.TemporaryDirectory() as directory:
    for name in ("mesh.oos", "mesh.ooh5"):
        path = str(Path(directory, name))
        if name.endswith(".ooh5"):
            memory_deck.write_archive(path)
        else:
            assert memory_deck.write_model(path) == []
        restored = oo_model.read_model(path)
        assert restored.card_counts == memory_deck.card_counts and not restored.check_references()
    path = Path(directory, "node.oos")
    path.write_text("[model]\nNode;1;;1.;2.;3.\n", encoding="utf-8")
    deck = oo_model.read_model(path)
    assert deck.card_counts == {"Node": 1}
    archive = str(path.with_suffix(".ooh5"))
    deck.write_archive(archive)
    assert oo_model.read_model(archive).card_counts == deck.card_counts
    table = deck.card_table("nodes", ["id", "xyzGlobal"])
    del deck
    gc.collect()
    assert len(table) == 1 and table.columns == ["id", "xyzGlobal"]
    import pyarrow as pa
    batch = pa.record_batch(table)
    assert batch.column("xyzGlobal").to_pylist() == [[1., 2., 3.]]
    del table
    gc.collect()
    assert batch.column("id").to_pylist() == [1]
