# Native Python package

The `oo-reader` distribution exposes the C++ Reader in the CPython process.
Install it from PyPI with `python -m pip install oo-reader`.
The standard import name is `oo_reader`. Place `wing.oos` in the working directory and extract the WASM package as described in [Getting started](getting-started.md).

**JavaScript / WebAssembly**

```javascript
import { readFile, writeFile } from "node:fs/promises";
import { loadOorReader } from "./reader/index.js";
const reader = await loadOorReader();
reader.writeFile("/work/wing.oos", await readFile("wing.oos", "utf8"));
const deck = reader.readModel("/work/wing.oos");
const nodes = reader.cardTable(deck, "nodes", ["id", "xyzGlobal"]);
const materials = reader.runQuery("materialsTable", { deck });
try {
  console.log(deck.cardCounts(), nodes.rowCount(), materials.rowCount());
  deck.writeArchive("/work/wing.ooh5");
  await writeFile("wing.ooh5", reader.readFile("/work/wing.ooh5"));
} finally {
  materials.delete(); nodes.delete(); deck.delete();
}
```

**Python / native C++**

```python
from oo_reader import read_model

deck = read_model("wing.oos")           # also accepts a native .ooh5 archive
counts = deck.card_counts
nodes = deck.card_table("nodes", ["id", "xyzGlobal"])
materials = deck.query("materialsTable")
print(counts, len(nodes), len(materials))
deck.write_archive("wing.ooh5")
```

Tables implement the Arrow PyCapsule interface. Pass them directly to the native Solver
or, with the optional PyArrow package, call `pyarrow.record_batch(nodes)`. The consumer
owns a reference to the exported buffers. It can outlive the table or deck.
`deck.copy()` gives a copy-on-write model. Use `set_card_value` on the copy to change a
named field, or `with_design_point(ids, values)` to make a copy at a new design point.

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
creates downloadable artifacts. Release the Reader before the matching Solver.
