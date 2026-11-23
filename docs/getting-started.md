# Getting started

Read, edit and query finite element models in .oos and HDF5 .ooh5 format with the same C++20 library from **JavaScript (WebAssembly)** or **Python (native C++)**.

(build-requirements)=
## Install the packages

| Interface | Install |
| --- | --- |
| JavaScript / WebAssembly | Extract the [Reader ZIP](https://github.com/jcdulas/O_o_Reader/releases/download/v0.2.0/O_o_Reader-wasm.zip) into `reader/` next to your script. Use Node.js 24+ or a browser with Memory64 support. |
| Python / native C++ | Run `python -m pip install oo-reader`. [PyPI](https://pypi.org/project/oo-reader/) provides wheels for CPython 3.10–3.14 on Windows x64 and Linux x86-64. |

(read-and-query-a-model)=
## Read, query and save a model

Create a model with one node at (1, 2, 3), count its nodes and write a model-only HDF5 archive. Save the JavaScript example as `example.mjs` and run `node example.mjs`, or save the Python example as `example.py` and run `python example.py`.

**JavaScript / WebAssembly**

```javascript
import { writeFile } from "node:fs/promises";
import { loadOorReader } from "./reader/index.js";

const reader = await loadOorReader();
reader.writeFile("/work/point.oos", "[model]\nNode;1;;1.;2.;3.\n");
const deck = reader.readModel("/work/point.oos");
const nodes = reader.runQuery("nodesTable", { deck });
try {
  console.log(nodes.rowCount()); // 1
  deck.writeArchive("/work/point.ooh5");
  await writeFile("point.ooh5", reader.readFile("/work/point.ooh5"));
} finally {
  nodes.delete();
  deck.delete();
}
```

**Python / native C++**

```python
from pathlib import Path
from oo_reader import read_model

Path("point.oos").write_text("[model]\nNode;1;;1.;2.;3.\n", encoding="utf-8")
deck = read_model("point.oos")
print(len(deck.query("nodesTable")))  # 1
deck.write_archive("point.ooh5")
```

Both scripts create `point.ooh5` in the current directory. The Node.js script copies the archive from WASM memory to disk; Python writes the host file directly.

## Choose a file format

| Format | JavaScript / WebAssembly | Native Python |
| --- | --- | --- |
| `.oos` model records | `reader.readModel`, `deck.writeModel` | `read_model`, `deck.write_model` |
| `.ooh5` model in HDF5 | `reader.readModel`, `deck.writeArchive` | `read_model`, `deck.write_archive` |
| `.ooh5` result tables | `reader.openResults`, `results.writeArchive` | Read datasets with h5py as shown in the [archive guide](archive-format.md). |
| Excel result workbook / HDF5 query export | `results.writeXlsx`, `reader.writeQueryTables` | The package exposes model query tables through Arrow. |

## Save and reopen a model with results

Save this example as `archive-model.mjs` in the repository root with the extracted Reader in `reader/`:

**JavaScript / WebAssembly**

~~~javascript
import { writeFile } from "node:fs/promises";
import { loadOorReader } from "./reader/index.js";

const oor = await loadOorReader();
oor.writeFile("/work/point.oos", "[model]\nNode;1;;0.;0.;0.\n");
const deck = oor.readModel("/work/point.oos");
const results = oor.createResults([
  { kind: "displacements", subcase: 1, ids: [1], values: new Float64Array([0.1, 0, 0, 0, 0, 0]) },
]);

try {
  results.attach(deck, false);
  results.writeArchive("/work/point.ooh5");
  await writeFile("point.ooh5", oor.readFile("/work/point.ooh5"));
  const archive = oor.openResults("/work/point.ooh5"); // result index only; model values stay unread
  const restored = archive.model();                  // loads the model and attaches it for queries
  try {
    console.log("Nodes:", restored.cardCounts().Node);
    console.log("Displacement:", archive.read(0).values[0]);
    restored.writeModel("/work/export.oos");
    console.log(oor.readFile("/work/export.oos", { encoding: "utf8" }));
  } finally {
    restored.delete();
    archive.delete();
  }
} finally {
  results.delete();
  deck.delete();
}
~~~

**Python / native C++**

Open the combined archive written to disk by the JavaScript example. Python can retrieve its model and export its records; the result-index API shown above belongs to JavaScript.

```python
from oo_reader import read_model

restored = read_model("point.ooh5")
print(restored.card_counts["Node"])  # 1
restored.write_model("export.oos")
```

Run it with `node archive-model.mjs`. `oor.readFile("/work/point.ooh5")` returns the archive bytes for downloading or
writing to host storage. `oor.readModel("/work/point.ooh5")` can load the model independently of its results.

For a model alone, call `deck.writeArchive`. For results alone, write a result set with no attached model.
`archive.hasModel()` checks whether a model is available; `archive.model()` returns `null` when absent, whereas
`oor.readModel` raises an error for an archive without a model. See [archive versions](archive-format.md#versions):
new writes use version 4, and version 3 result archives remain readable.

## Model conventions

- A record occupies one physical line, with semicolons between values.
- Card names, field names and vocabulary words use their exact neutral spelling.
- Quote values containing semicolons or quotes; double an embedded quote.
- Use `Include` records for model includes. Put every required file in the WASM file system for JavaScript or beside the host model at its declared relative path for Python.
- Inspect diagnostics before using a model. The C++ facade also offers strict read settings.

See the [format specification](model-format.md) and the [card catalogue](model-format-cards.md) for the ordered values,
defaults, alternatives and repeated groups of each card.

## Continue

- [JavaScript guide](wasm-api.md) and [Python guide](python.md) cover file operations, queries, card editing and result objects.
- [API declarations](api.rst): JavaScript types, Python interfaces and C++ facade headers.
- [Native model/results archive](archive-format.md): model columns, result tables, compatibility and custom outputs.
- [Table packages](table-package.md): transfer of query tables to a consumer.
- [Architecture](architecture.md) and [module guide](modules.md): implementation entry points.

In JavaScript, release native-backed handles with `delete()` when their data is no longer needed.
