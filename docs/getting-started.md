# Getting started

Build, edit and query finite element models through the O_o_Model API in JavaScript (WebAssembly) or Python (native C++). Applications supply cards and analysis controls in memory. O_o_Solver consumes the resulting model tables through its API.

(build-requirements)=
## Install the packages

| Interface | Install |
| --- | --- |
| JavaScript / WebAssembly | Extract the [Model ZIP](https://github.com/jcdulas/O_o_Model/releases/download/v0.2.1/O_o_Model-wasm.zip) into `model/` next to your script. Use Node.js 24+ or a browser with Memory64 support. |
| Python / native C++ | Install the [native wheel](https://pypi.org/project/oo-model/0.2.1/) with `python -m pip install oo-model==0.2.1`. For source builds, see the [native build requirements](python.md#build-and-publish). |

(read-and-query-a-model)=
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

## Pass the deck to a solver

With O_o_Solver installed, JavaScript calls `solver.modelFromReader(api, deck)` while the deck is alive. In Python, call `oo_solver.model_from_reader(deck)`. Both calls build a solver snapshot from the model tables. The [Solver tutorial](https://jcdulas.github.io/O_o_Solver/docs/getting-started.html) constructs a loaded rod and reads its displacement in both languages.

## Choose a file format

| Format | JavaScript / WebAssembly | Native Python |
| --- | --- | --- |
| `.oos` model records | `reader.readModel`, `deck.writeModel` | `read_model`, `deck.write_model` |
| `.ooh5` model in HDF5 | `reader.readModel`, `deck.writeArchive` | `read_model`, `deck.write_archive` |
| `.ooh5` result tables | `reader.openResults`, `results.writeArchive` | Read datasets with h5py as shown in the [archive guide](archive-format.md). |
| Excel result workbook / HDF5 query export | `results.writeXlsx`, `reader.writeQueryTables` | The package exposes model query tables through Arrow. |

For optional file exchange, the standard distribution includes the [OOS text adapter](https://github.com/jcdulas/O_o_OOS) and the [OOH5 archive adapter](https://github.com/jcdulas/O_o_OOH5). The [format specification](model-format.md) describes the text syntax. The [archive guide](archive-format.md) covers persistence of model and result tables.

## Continue

- [JavaScript guide](wasm-api.md) and [Python guide](python.md) cover file operations, queries, card editing and result objects.
- [API declarations](api.rst): JavaScript types, Python interfaces and C++ facade headers.
- [Native model/results archive](archive-format.md): model columns, result tables, compatibility and custom outputs.
- [Table packages](table-package.md): transfer of query tables to a consumer.
- [Architecture](architecture.md) and [module guide](modules.md): implementation entry points.

In JavaScript, release native-backed handles with `delete()` when their data is no longer needed.
