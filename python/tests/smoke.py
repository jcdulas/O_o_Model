"""Installed-wheel tests, including interoperability with a separate PyArrow installation."""
import gc
import tempfile
from pathlib import Path

import oor_reader

with tempfile.TemporaryDirectory() as directory:
    path = Path(directory, "node.oos")
    path.write_text("[model]\nNode;1;;1.;2.;3.\n", encoding="utf-8")
    deck = oor_reader.read_model(path)
    assert deck.card_counts == {"Node": 1}
    archive = str(path.with_suffix(".ooh5"))
    deck.write_archive(archive)
    assert oor_reader.read_model(archive).card_counts == deck.card_counts
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
