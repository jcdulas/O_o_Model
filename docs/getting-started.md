# Getting started

Build, edit and query finite element models through the O_o_Model API in JavaScript (WebAssembly), Python or native C++20. Applications supply cards and analysis controls in memory. O_o_Solver consumes the resulting model tables through its API.

(build-requirements)=
## Install the packages

| Interface | Install |
| --- | --- |
| JavaScript / WebAssembly | Extract the [Model ZIP](https://github.com/jcdulas/O_o_Model/releases/download/v0.2.1/O_o_Model-wasm.zip) into `model/` next to your script. Use Node.js 24+ or a browser with Memory64 support. |
| Python | Install the [native wheel](https://pypi.org/project/oo-model/0.2.1/) with `python -m pip install oo-model==0.2.1`. For source builds, see the [native build requirements](python.md#build-and-publish). |
| C++20 / vcpkg | Add `oo-model` from the [O_o registry](https://github.com/jcdulas/O_o_vcpkg) and link `oor::core`. |

(read-and-query-a-model)=
## Build and query a model in memory

Create a node at (1, 2, 3) and count the rows in the node table. All three examples print `1`.

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

**Python**

```python
from oo_model import create_model

deck = create_model()
deck.add_card("Node", [1, None, 1., 2., 3.])
nodes = deck.query("nodesTable")
print(len(nodes))
```

**C++20**

```cpp
#include <oor/api/CardEdits.hpp>
#include <oor/api/Queries.hpp>
#include <iostream>

int main()
{
    using Field = oor::model::FieldValue;
    const auto deck = oor::api::Deck::createModel();
    const oor::api::CardInput node{"Node", {{Field::Kind::Integer, 1, 0., {}}, {},
        {Field::Kind::Real, 0, 1., {}}, {Field::Kind::Real, 0, 2., {}}, {Field::Kind::Real, 0, 3., {}}}};
    oor::api::insertCard(*deck, node);
    const auto nodes = oor::api::runQuery("nodesTable", deck, nullptr, {});
    std::cout << nodes->rowCount() << '\n';
}
```

WASM handles own native allocations and expose `delete()`. Python manages those lifetimes and exposes query tables through the Arrow C Data Interface.

## Pass the deck to a solver

With O_o_Solver installed, JavaScript calls `solver.modelFromReader(api, deck)` while the deck is alive. In Python, call `oo_solver.model_from_reader(deck)`. In C++, call `oos::api::modelFromDeck(deck)`. All three calls build a solver snapshot from the model tables. The [Solver tutorial](https://jcdulas.github.io/O_o_Solver/docs/getting-started.html) constructs a loaded rod and reads its displacement in all three languages.

## Choose a file format

| Format | JavaScript / WebAssembly | Python | C++20 |
| --- | --- | --- | --- |
| `.oos` model records | `reader.readModel`, `deck.writeModel` | `read_model`, `deck.write_model` | `oor::formats::oos::read`, `write` |
| `.ooh5` model in HDF5 | `reader.readModel`, `deck.writeArchive` | `read_model`, `deck.write_archive` | `oor::formats::ooh5::read`, `write` |
| `.ooh5` result tables | `reader.openResults`, `results.writeArchive` | Read datasets with h5py as shown in the [archive guide](archive-format.md). | `oor::api::Results::open`, `writeArchive` (archive adapter) |
| Excel result workbook / HDF5 query export | `results.writeXlsx`, `reader.writeQueryTables` | The package exposes model query tables through Arrow. | `oor::api::Results::writeXlsx`, `oor::query::writeQueryTables` with their adapters |

For optional file exchange, the standard distribution includes the [OOS text adapter](https://github.com/jcdulas/O_o_OOS) and the [OOH5 archive adapter](https://github.com/jcdulas/O_o_OOH5). The [format specification](model-format.md) describes the text syntax. The [archive guide](archive-format.md) covers persistence of model and result tables.

## Continue

- [JavaScript guide](wasm-api.md) and [Python guide](python.md) cover file operations, queries, card editing and result objects.
- [API declarations](api.rst): JavaScript types, Python interfaces and C++ facade headers.
- [Native model/results archive](archive-format.md): model columns, result tables, compatibility and custom outputs.
- [Table packages](table-package.md): transfer of query tables to a consumer.
- [Architecture](architecture.md) and [module guide](modules.md): implementation entry points.

In JavaScript, release native-backed handles with `delete()` when their data is no longer needed.
