"""Time the same in-memory mesh workload as mesh.mjs and mesh.cpp."""
import json
import sys
from statistics import median
from time import perf_counter
import numpy as np
from oo_model import create_model, read_model
from oo_solver import model_from_reader

fixture = sys.argv[1] if len(sys.argv) > 1 else None
ids = np.arange(1, (20301 if fixture else 200000) + 1, dtype=np.int32)
x = (ids - 1).astype(np.float64) * 0.00123456789
stride = 19 if fixture else 199
selected = ids[:1000*stride:stride].copy()
xyz = np.zeros((1000, 3))
if fixture:
    xyz[:, 0] = (selected - 1) % 201
    xyz[:, 1] = (selected - 1) // 201
    xyz[:, 2] = 0.001
else:
    xyz[:, 0] = -np.arange(1, 1001)
start = perf_counter()
deck = read_model(fixture, strict=True) if fixture else create_model()
if not fixture:
    deck.add_card_batch("Node", {"id": ids, "position1": x, "position2": 0., "position3": 0.})
built = perf_counter()
trial = deck.copy()
copied = perf_counter()
trial.set_node_positions(selected, xyz)
edited = perf_counter()
snapshot = model_from_reader(trial)
end = perf_counter()
repeated = []
for _ in range(7):
    del snapshot
    xyz[0, 2] += 0.001
    trial.set_node_positions(selected, xyz)
    begin = perf_counter()
    snapshot = model_from_reader(trial)
    repeated.append(1000 * (perf_counter() - begin))
print(json.dumps({
    "build_ms": 1000 * (built - start),
    "copy_ms": 1000 * (copied - built),
    "edit_ms": 1000 * (edited - copied),
    "snapshot_ms": 1000 * (end - edited),
    "repeat_snapshot_ms": median(repeated),
}))
