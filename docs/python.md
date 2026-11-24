# Native Python package

The `oo-model` distribution exposes the C++ Model in the CPython process.
Install it with `python -m pip install oo-model` or build from a source checkout with `python -m pip install .`.
The standard import name is `oo_model`. Extract the matching WASM distribution as described in [Getting started](getting-started.md).

## Build and query a model in memory

Create a node at (1, 2, 3) and count the rows in the node table. Both examples print `1`.

**JavaScript / WebAssembly**

```javascript
import { loadOoModel } from "./model/index.js";

const api = await loadOoModel();
const deck = api.createModel();
try {
  deck.addCard({ type: "Node", fields: [1, null, 1, 2, 3] });
  const nodes = api.runQuery("nodesTable", { deck });
  try {
    console.log(nodes.rowCount());
  } finally {
    nodes.delete();
  }
} finally {
  deck.delete();
}
```

**Python / native C++**

```python
from oo_model import create_model

deck = create_model()
deck.add_card("Node", [1, None, 1., 2., 3.])
nodes = deck.query("nodesTable")
print(len(nodes))
```

WASM handles own native allocations and expose `delete()`. Python manages those lifetimes and exposes query tables through the Arrow C Data Interface.

Tables implement the Arrow PyCapsule interface. Pass them directly to the native Solver
or, with the optional PyArrow package, call `pyarrow.record_batch(nodes)`. The consumer
owns a reference to the exported buffers. It can outlive the table or deck.
`deck.copy()` gives a copy-on-write model. Use `set_card_value` on the copy to change a
named field, or `with_design_point(ids, values)` to make a copy at a new design point.

Build a deck with NumPy columns using the [in-memory construction API](model-construction.md#a-complete-model). See [file adapters](architecture.md#file-adapters) for a source build without HDF5.

## Build and publish

Build with Python 3.10 or later, a C++20 compiler, CMake 3.25 or later, Ninja and
HDF5 (C API) and zlib development libraries. Run
`python -m pip wheel --no-deps . -w dist` from the repository root.
Verify an installed wheel with `python -m pip install pyarrow` and
`python python/tests/smoke.py`.

The **Python wheels** workflow builds CPython 3.10–3.14 wheels for Linux x86-64
and Windows x64, bundles the required shared libraries and tests archive I/O and
Arrow ownership. It also builds a source distribution. Configure a PyPI trusted
publisher for this repository, workflow `python-wheels.yml` and environment `pypi`.
Enable the workflow's publish input to upload a new version. A default run only
creates downloadable artifacts. Release the Model before the matching Solver.
