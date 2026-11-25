# Model operations in JavaScript, Python and C++

Use [Getting started](getting-started.md) to install the package for your language. Python imports `oo_model` from the native `oo-model` wheel. The JavaScript examples use `oor` for the loaded WASM module. The C++ snippets use `oor::core` for in-memory operations. File examples also require their format adapter, and the combined results facade requires the adapter-enabled `oor::api` build.

The package `oo-model` (built in `build/wasm/dist`) runs the whole library in a browser, a web worker or Node.js.
It is a WebAssembly module (`oor_reader_core.wasm`, made by Emscripten) and a small JavaScript wrapper
(`index.js` and `model-editing.js`, with its types in `index.d.ts`).

The module is **64-bit WebAssembly** (Memory64): it can use up to 16 GB of memory, where 32-bit WebAssembly stops at
4 GB, so large decks and result sets fit in memory with what is read from them. It needs a runtime that supports
Memory64: Node.js 24 or later, and a browser that ships the feature (check the browsers you target: a runtime without
it refuses to compile the module).

## Loading

**JavaScript / WebAssembly**

```js
import { loadOoModel } from "./model/index.js";

const oor = await loadOoModel();
console.log(oor.version()); // "0.2.3"
```

**Python**

```python
from importlib.metadata import version
from oo_model import create_model

print(version("oo-model"))
```

**C++20**

```cpp
#include <oor/base/Version.hpp>
std::cout << oor::base::LIBRARY_VERSION;
```

In a browser, serve `oor_reader_core.wasm` next to `oor_reader_core.js`, or tell Emscripten where it is:

**JavaScript / WebAssembly**

```js
const oor = await loadOoModel({ locateFile: (file) => `/static/${file}` });
```

**Python**

Install the native package with `python -m pip install oo-model`. The Python importer loads its compiled extension from the environment.

```python
from oo_model import create_model

deck = create_model()
```

**C++20**

```cpp
auto deck = oor::api::Deck::createModel(); // executable linked to oor::core
```

The module is single-threaded: run it in a web worker to keep the page responsive on large files.

## Optional file adapters

For applications that import or persist files, the adapters use the WASM in-memory file system. Put the input files in it, and take the output files
out of it:

**JavaScript / WebAssembly**

```js
const text = await (await fetch("plate.oos")).text();
oor.writeFile("/work/plate.oos", text);          // a model file: also write the files it includes, at their paths
oor.writeFile("/work/run.ooh5", new Uint8Array(await file.arrayBuffer()));
// ... work ...
const bytes = oor.readFile("/work/run.ooh5");   // Uint8Array, to download or upload
oor.removeFile("/work/run.ooh5");               // free the memory of a file you no longer need
```

**Python**

```python
from pathlib import Path
from oo_model import read_model

deck = read_model("plate.oos")
archive_bytes = Path("run.ooh5").read_bytes()
```

**C++20**

```cpp
auto deck = oor::formats::oos::read("plate.oos");
std::ifstream archive("run.ooh5", std::ios::binary);
std::vector<char> bytes{std::istreambuf_iterator<char>(archive), {}};
```

## Models

Use `oor.createModel()` to construct an empty model without a file. The [model construction guide](model-construction.md)
covers object input, typed batches, stable keys, load cases, controls, includes and parts. These APIs also edit imported models.

**JavaScript / WebAssembly**

```js
const deck = oor.readModel("/work/plate.oos", { strict: false });  // a model file (model-format.md)
deck.cardCounts();        // { IsoMat: 1, Node: 6, ShellQuad4: 2, ShellProp: 1 }: card types by their neutral names
deck.diagnostics();       // [{ severity, code, message, location }]
deck.toModelText();
deck.writeModel("/work/out.oos", { splitIncludes: true });
deck.writeArchive("/work/model.ooh5"); // native typed model, without result tables
const nativeDeck = oor.readModel("/work/model.ooh5");
nativeDeck.delete();
deck.delete();            // free the C++ object when done
```

**Python**

```python
deck = read_model("plate.oos", strict=False)
print(deck.card_counts, [d.message for d in deck.diagnostics])
deck.write_model("out.oos")
deck.write_archive("model.ooh5")
restored = read_model("model.ooh5")
```

**C++20**

```cpp
auto deck = oor::formats::oos::read("plate.oos", {.strict = false});
for (const auto& diagnostic : deck->diagnostics()) std::cerr << diagnostic.message << '\n';
oor::formats::oos::write(*deck, "out.oos");
oor::formats::ooh5::write(*deck, "model.ooh5");
auto restored = oor::formats::ooh5::read("model.ooh5");
```

Model records, diagnostics and JavaScript values use the same exact neutral names
([naming.md](naming.md)): `ShellQuad4`, `propId`, `All` and `Yes`.

`readModel` detects a native `.ooh5` archive by its content and loads its typed model. Otherwise it reads model records,
regardless of the path's extension. An archive without a model raises an error. `writeModel` writes model records and
returns any content it could not carry, one description per item. `toModelText` gives one text with Include files flattened.

### Cards by ID

Every card type can be read by ID, with the names of its fields:

**JavaScript / WebAssembly**

```js
const node = deck.nodes[11];        // undefined when there is no grid point 11
node.xyz;                           // Float64Array [x1, x2, x3] in the CP system of the grid point
node.xyzGlobal;                    // its position in the basic system
node.positionFrameId;               // the other fields, by name
deck.elements[10].nodes;            // the grid points of element 10
deck.properties[1].thickness;       // the thickness of ShellProp 1
deck.materials[1].e;
deck.coords[5];
deck.cardById("SinglePointConstrList", 7);           // any card type ("source"); a set card gives the first card of its ID
deck.nodes.ids();                   // [1, 2, 3, ...]
```

**Python**

Use the optional PyArrow package to inspect the same node by ID.

```python
import pyarrow as pa

nodes = pa.record_batch(deck.card_table("nodes", ["id", "xyzGlobal"]))
row = nodes.column("id").to_pylist().index(11)
print(nodes.column("xyzGlobal")[row].as_py())
```

**C++20**

```cpp
if (auto node = oor::api::findCard(*deck, "Node", 11, {"xyzGlobal"}))
    for (const auto& [name, value] : node->values)
        if (name == "xyzGlobal") for (auto x : value.numbers) std::cout << x << ' ';
```

A card is `{ type, id, key, values, fields, text, comment }`; each named value is also a property of the card (`node.xyz` is
`node.values.xyz`). `fields` are the fields as written, field 1 first: the numbering the editing functions use.

### Editing cards

**JavaScript / WebAssembly**

```js
deck.setCardField("nodes", 11, 3, "2.5");          // compact field 3 of a Node (position1) set to 2.5
deck.setCardFields("ShellProp", 1, ["1", "1", "0.25"]);
deck.properties[1].thickness = 0.25;                // a field by its name: the card is updated in the deck
deck.nodes[11].position1 = 2.5;
deck.setCardValue("ShellProp", 1, "bendingMatId", "3"); // the same, as a function
deck.cardFieldNames("ShellProp", 1);              // [{ field: 1, name: "id" }, { field: 2, name: "membraneMatId" }, ...]
deck.replaceCard("ShellProp", 1, "ShellProp;1;1;0.25");  // one model record of the same card type
deck.addCards("Node;7;;3.;0.;0.\nShellQuad4;12;1;3;7;8;6");   // [{ type: "Node", id: 7 }, { type: "ShellQuad4", id: 12 }]
deck.removeCard("elements", 12);
```

**Python**

```python
deck.set_card_value("Node", 11, "position1", 2.5)
deck.set_card_value("ShellProp", 1, "thickness", 0.25)
```

**C++20**

```cpp
oor::api::setCardValue(*deck, "Node", 11, "position1", "2.5");
oor::api::setCardValue(*deck, "ShellProp", 1, "thickness", "0.25");
```

An edited card keeps its place in the deck, its comment and its link to attached results. Its new fields are checked as
the model reader checks them: a field the card cannot hold, or an ID another card has, throws an `Error` that says why,
and nothing changes. `addCards` adds all its cards or none.

A property can be assigned when it is the exact neutral name listed by `cardFieldNames`, such as `thickness` or
`position1`. The card is read again, so its properties show the new state. A value with several fields, such as
`xyz`, is set field by field (`position1`, `position2`, `position3`). Unknown field names throw an `Error` that lists
the card's fields. `fields` and numerical edits use the compact order of the model record, including separate fields
for alternatives such as `materialAngle` and `matFrameId`.

## Results

**JavaScript / WebAssembly**

```js
const results = oor.openResults("/work/run.ooh5"); // an HDF5 results archive, recognised by its content
results.format();          // "archive"
const tables = results.tables();
// [{ index, kind: "displacements", elementType: "", subcase: 1, analysis: "static", stepKind, steps, rowCount,
//    components: ["t1", "t2", "t3", "r1", "r2", "r3"], valueType: "float64", ... }]

const data = results.read(tables[0].index, { stepIndices: [0], components: ["t3"], ids: [5, 6] });
// { shape: [1, 2, 1], ids: Int32Array, values: Float64Array, steps, layers, nodeIds, elementIds, texts }
// values[(step * rows + row) * components + component]; complex values: a last dimension of 2 (real, imaginary)

results.writeArchive("/work/run.ooh5", { compressionLevel: 4, title: "PLATE" });
results.writeXlsx("/work/run.xlsx", { title: "PLATE" });  // an Excel workbook, for people
```

**Python**

For result datasets, including slices by step, see the [h5py examples](archive-format.md). Use h5py for the result values.

```python
import h5py

with h5py.File("run.ooh5") as archive:
    entry = archive["index/tables"][0]
    first_step = archive[entry["group"].decode()]["values"][0]
```

**C++20**

```cpp
const auto results = oor::api::Results::open("run.ooh5");
const auto tables = results->tables();
if (!tables.empty()) {
    const auto selection = results->read(tables.front().index, {.stepIndices = {0}, .components = {"t3"}, .ids = {5, 6}});
    std::cout << selection.shape.size();
}
```

`openResults` loads the result indexes, leaving model columns and result values unread. `model()` caches its deck;
subsequent calls share that deck and its edits. `attach(deck, false)` selects an existing deck instead. `writeArchive`
includes the attached deck, and preserves an embedded model even when `model()` has not been called. To write the model
alone, use `deck.writeArchive(path, options)`; it takes the same compression and title options. Archives containing only
results remain supported. New archives use version 4; version 3 result archives remain readable.

### A model and results in one archive

**JavaScript / WebAssembly**

```js
results.attach(deck, false);
results.writeArchive("/work/complete.ooh5", { compressionLevel: 4 });

const archive = oor.openResults("/work/complete.ooh5");
if (archive.hasModel()) {
  const embedded = archive.model(); // load once; later calls share the same C++ deck
  try {
    const maximum = oor.runQuery("maxDisplacement", { deck: embedded, results: archive });
    try {
      console.log(maximum.toCsv());
    } finally {
      maximum.delete();
    }
    embedded.writeModel("/work/export.oos");
    embedded.writeArchive("/work/model-only.ooh5");
  } finally {
    embedded.delete();
  }
}
archive.delete();
```

**Python**

```python
embedded = read_model("complete.ooh5")
embedded.write_model("export.oos")
embedded.write_archive("model-only.ooh5")
```

**C++20**

```cpp
auto embedded = oor::formats::ooh5::read("complete.ooh5");
oor::formats::oos::write(*embedded, "export.oos");
oor::formats::ooh5::write(*embedded, "model-only.ooh5");
```

In the JavaScript example, `maxDisplacement` uses the attached results. Python Model queries operate on the model.

| Operation | Behavior |
| --- | --- |
| `oor.openResults(path)` | Opens a model-only, result-only or combined archive and reads result indexes. |
| `results.hasModel()` | Reports an attached or embedded model without reading its columns. |
| `results.model()` | Returns the attached deck, or loads, caches and attaches the embedded deck; `null` when absent. |
| `oor.readModel(path, { strict })` | Reads `.oos` text or the native model independently; an archive without a model raises an error. |
| `results.attach(deck, strict)` | Selects a deck for model/result queries and subsequent archive writes. |
| `results.writeArchive(path, options)` | Includes the attached model, or preserves the embedded one if it has not yet been loaded. |
| `deck.writeArchive(path, options)` | Writes a model-only archive. |

Edits to the deck returned by `model()` are included by a later `results.writeArchive`. Calling `oor.readModel` instead
creates an independent deck: attach that deck explicitly if its edits should replace the model saved with the results.
`hasModel()` checks presence; a malformed or unsupported model schema raises an error when its model is loaded.

Both archive writers accept `ArchiveWriteOptions`: `compressionLevel` (0 to 9, default 4), `shuffle` (default true),
`strict` (default false), `title`, `subtitle` and `label`. `strict` raises an error instead of reporting skipped result
tables. Unsupported model control data always raises an error rather than being omitted. Cards from Include files
and their source metadata are embedded; files merely referenced by other card or control values remain references.

The [native model specification](archive-format.md#native-model) describes typed columns, sparse fields, constants,
source precision and pending defaults. The [archive adapter example](archive-format.md#save-and-reopen-a-model-with-results)
is a complete runnable program. The archive, native model and table-package versions are separate contracts.

### Results made by a program

A solver, or a computation in the page, hands its results over as plain arrays; each table is checked against the
result catalogue (the components of each kind and element type):

**JavaScript / WebAssembly**

```js
const results = oor.createResults([
  {
    kind: "displacements", subcase: 1, stepKind: "time", steps: [0.0, 0.1],
    ids: [1, 2, 3], values: new Float32Array(2 * 3 * 6),       // (steps, rows, components), single precision kept
  },
  {
    kind: "stress", elementType: "ShellQuad4", subcase: 1,
    ids: [10, 10], layers: [1, 2], values: new Float64Array(2 * 8),
  },
], "my run");
```

**Python**

A Python producer can represent the same two-step displacement field in NumPy. The Python Model binding exposes model tables; the in-memory results writer is available in JavaScript and C++.

```python
import numpy as np

ids = np.array([1, 2, 3], dtype=np.int32)
steps = np.array([0., 0.1])
displacements = np.zeros((2, len(ids), 6), dtype=np.float32)
```

**C++20**

```cpp
std::vector<float> values(2 * 3 * 6);
oor::results::MemoryTableInput table;
table.kind = oor::results::ResultKind::Displacements;
table.ids = {1, 2, 3};
table.steps = {0., .1};
table.analysisCode = 6;
table.type = oor::results::ValueType::Float32;
table.values = std::as_bytes(std::span(values));
auto results = oor::api::Results::fromTables("my run", {table});
```

The members of a table are listed by `MemoryTable` in `index.d.ts`. Writing folders that do not exist yet are made.

For typed results with multiple arrays, use `oor.namedResultCatalogue()` to inspect the permitted kinds and shapes,
then `results.addNamed({ kind, arrays, texts, subcase, analysisCode })`. The named index is returned by
`results.named()`; `results.readNamed(index)` loads its typed numeric arrays and text columns. This includes SOL 144
pressure, force, trim and stability-derivative outputs. Named payloads survive `.ooh5` writes and reopenings.

### The Excel workbook

`writeXlsx` writes an index sheet (every table, with a link to its sheet) and one sheet per table: what the table is,
then a line per step and row with its labels (step, ID, grid point, layer, ...) and a column per component (two for a
complex value: real and imaginary parts), under a frozen header line with filters. A table longer than a sheet
(1,048,576 rows) goes on in the next sheets. The workbook is an output for people: the archive is the format to
exchange results.

Both writers return a report: `{ finished, bytes, written: [...], skipped: [{ kind, container, reason, message }] }`.
A table a format cannot hold is listed in `skipped`, never dropped silently.

## Queries

The named queries of the library (over 160: inventory of the model, geometry, mass, quality, loads, results, margins,
section cuts, ...) run on a deck, on results, or on both:

**JavaScript / WebAssembly**

```js
const nodes = oor.runQuery("nodesTable", { deck });
nodes.column("x").values;                   // Float64Array of the basic x coordinates

const elements = oor.runQuery("elementsTable", { deck, args: { columns: ["elementId", "type", "propId", "nodes"] } });
const nodesOf = elements.column("nodes");   // { kind: "numberList", values, offsets }

results.attach(deck, false);                // link the results to the cards of the deck
const worst = oor.runQuery("maxDisplacement", { deck, results });

oor.queryCatalogue();                       // every query, its description and parameters
worst.toCsv();
```

**Python**

```python
import pyarrow as pa

nodes = pa.record_batch(deck.query("nodesTable"))
print(nodes.column("x").to_numpy())
elements = deck.query("elementsTable", columns=["elementId", "type", "propId", "nodes"])
```

**C++20**

```cpp
auto nodes = oor::api::runQuery("nodesTable", deck, nullptr, {});
for (double x : nodes->column("x").as<double>()) std::cout << x << '\n';
auto args = oor::api::argumentsFromJson("elementsTable", R"({"columns":["elementId","type","propId","nodes"]})");
auto elements = oor::api::runQuery("elementsTable", deck, nullptr, args);
```

Arguments are plain JavaScript values: numbers, texts, arrays of IDs, objects for named sets
(`{ wing: [1, 2, 3] }`), `{ start, stop, step }` for step positions. See `argumentsFromJson` in
[include/oor/api/Queries.hpp](../include/oor/api/Queries.hpp) for every kind.

### Custom outputs in HDF5

**JavaScript / WebAssembly**

```js
oor.writeQueryTables("/work/outputs.h5", [
  { name: "nodes", table: nodes },
  { name: "worst_displacement", table: worst },
]);
```

**Python**

JavaScript and C++ provide the query-table archive writer. For a custom Python output, the following writes the node x coordinates as a plain HDF5 dataset.

```python
import h5py
import pyarrow as pa

nodes = pa.record_batch(deck.query("nodesTable"))
with h5py.File("outputs.h5", "w") as f:
    f["nodes/x"] = nodes.column("x").to_numpy()
```

**C++20**

```cpp
oor::query::writeQueryTables("outputs.h5", {{"nodes", nodes}, {"worst_displacement", worst}});
```

The layout of that file is in [archive-format.md](archive-format.md#query-tables-custom-outputs).

## Card tables

The named queries give views made for people. A program that computes on the model (the O_o_Solver module) reads the
cards themselves: every field of a card type, with the computed columns it asks for, sorted by ID.

**JavaScript / WebAssembly**

```js
oor.cardTypesOf(deck, "elements");                       // ["ShellQuad4", "ShellTria3"]
oor.cardTableColumns("ShellQuad4");                       // { stored: ["id", "propId", "nodes", ...], computed: [...] }
const quads = oor.cardTable(deck, "ShellQuad4", ["id", "propId", "nodes", "nodesRows", "propIdRow", "propType"]);
const nodes = oor.cardTable(deck, "nodes", ["id", "positionFrameId", "displacementFrameId", "permanentConstraints",
                                             "superelementId", "xyzGlobal"]);
oor.displacementRotations(deck);                         // Float64Array, 9 values per grid point (row-major)
oor.modelVersions(deck);                                 // { structure, content, control }
const bytes = quads.toPackage();                         // Uint8Array: the table with its exact Arrow layout
```

**Python**

```python
from oo_model import card_columns

stored, computed = card_columns("ShellQuad4")
quads = deck.card_table("ShellQuad4", ["id", "propId", "nodes", "nodesRows"])
rotations = deck.displacement_rotations()  # one row of nine values per node
```

**C++20**

```cpp
auto columns = oor::api::cardTableColumns("ShellQuad4");
auto quads = oor::api::cardTable(*deck, "ShellQuad4", {"id", "propId", "nodes", "nodesRows"});
auto rotations = oor::api::displacementRotations(*deck);
```

`nodesRows` indexes the rows of `cardTable(deck, "nodes")`, and `propIdRow` the rows of the property's card table.
A table package hands a table to another WebAssembly module: [table-package.md](table-package.md).

## Optimization designs

`designVariables(deck)` inspects bounds and dependencies, `optimizationTables(deck)` exports owned design table
packages, and `applyDesignPoint(deck, ids, values)` atomically writes an accepted point. The
[optimization guide](optimization.md) describes the Solver connection, validation and shape update rules.
`designCapabilities(deck)` reports which Model design updates and card edits can be prepared. Model documents
(`deck.setDocument`, `document`, `documentNames`, `removeDocument`) preserve serializable application state in `.ooh5`.
The Solver [external optimization guide](https://jcdulas.github.io/O_o_Solver/docs/external-optimization.html)
shows accepted-point persistence and restoration.

## Errors

Every error of the library is thrown as a JavaScript `Error` whose message says what went wrong:

**JavaScript / WebAssembly**

```js
try {
  oor.openResults("/work/missing.ooh5");
} catch (error) {
  console.error(error.message); // "cannot open /work/missing.ooh5: no such file"
}
```

**Python**

```python
try:
    read_model("missing.ooh5")
except RuntimeError as error:
    print(error)
```

**C++20**

```cpp
try { auto deck = oor::formats::ooh5::read("missing.ooh5"); }
catch (const std::exception& error) { std::cerr << error.what() << '\n'; }
```
