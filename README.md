# O_o_Reader

Build, edit and query finite element models in memory, or load them through the .oos and HDF5 .ooh5 file adapters, with the same C++20 library from **JavaScript (WebAssembly)** or **Python (native C++)**.

**[Sphinx documentation](https://jcdulas.github.io/O_o_Reader/)** ·
[Model input reference](docs/reference/index.md) ·
[Model construction](https://jcdulas.github.io/O_o_Reader/docs/model-construction.html) ·
[API reference](https://jcdulas.github.io/O_o_Reader/docs/api.html)

## Install

| Interface | Install |
| --- | --- |
| JavaScript / WebAssembly | Extract the [Reader ZIP](https://github.com/jcdulas/O_o_Reader/releases/download/v0.2.0/O_o_Reader-wasm.zip) into `reader/` next to your script. Use Node.js 24+ or a browser with Memory64 support. |
| Python / native C++ | Run `python -m pip install oo-reader`. [PyPI](https://pypi.org/project/oo-reader/) provides wheels for CPython 3.10–3.14 on Windows x64 and Linux x86-64. |

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

Model queries cover geometry, mesh quality, mass, loads and connections. The JavaScript results API also queries stresses, margins and section cuts. [Query and export guide](docs/wasm-api.md)

Both interfaces construct models directly in memory, validate references, edit card fields and apply design points.
The standard build includes the text, archive and workbook adapters. An application building from source can link
only the in-memory core. [Model construction](docs/model-construction.md) · [Build profiles](docs/architecture.md#file-adapters) · [Archive format](docs/archive-format.md)

## Documentation

[Optimization with JavaScript and Python](docs/optimization.md): design interfaces, derivatives and accepted model updates.

**[Read Sphinx documentation](https://jcdulas.github.io/O_o_Reader/)** · [Architecture with diagrams](docs/architecture.md) · [Documentation index](index.md)

The Documentation workflow publishes the HTML site and provides a downloadable archive.
See [read, download and build instructions](docs/documentation.md).

New `.ooh5` files use archive version **4**, with native model schema **1**. Version **3** result archives remain
readable. See [choosing a format](docs/getting-started.md#choose-a-file-format) and
[archive compatibility](docs/archive-format.md#versions) before updating an existing viewer.

## Layout of the repository

| Folder | What |
| --- | --- |
| `include/oor/<module>/`, `src/<module>/` | the library, in modules that each use only the ones before them: `base` → `io` → `deck` → `model` → `results` → `analysis` → `query` → `api` |
| `src/formats/`, `include/oor/formats/` | Independent file adapter targets and their public C++ interfaces |
| `python/` | Native Python extension, public package and installed-wheel tests |
| `wasm/` | the WebAssembly module: the embind interface (`src/Bindings.cpp`), the JavaScript wrapper (`js/`), its Node.js test (`test/`) |
| `tests/cpp/<module>/` | the C++ tests (Catch2), run natively |
| `validation/models/` | model files written for the project, read by the tests |
| `docs/` | the archive format, JavaScript and Python interfaces, and architecture |
| `scripts/` | the build scripts |
| `tools/` | the layering check and the generator of the card catalogue (`oos_layouts/`) |
| `formats/` | the card layout catalogue of the model format (`oos-layouts.json`, [docs/model-format-cards.md](docs/model-format-cards.md)) |

Start reading at [docs/architecture.md](docs/architecture.md).

## Build

For the JavaScript distribution, use the WebAssembly build below. For a Python wheel, see the [native build and installation guide](docs/python.md#build-and-publish).

### Native (development and tests)

The standard distribution needs a C++20 compiler (GCC 12+ or Clang 16+), CMake 3.25+, Ninja and libhdf5 (on Windows: MSYS2 UCRT64 with
`mingw-w64-ucrt-x86_64-hdf5`).

```bash
cmake --preset release            # build/release
cmake --build --preset release
ctest --test-dir build/release -j 1 --timeout 1 --output-on-failure
```

or `scripts/check.sh` (build, tests, layering check).
Each native test has a one-second timeout; validation corpora run in small independent cases.

### WebAssembly

The module is 64-bit WebAssembly (Memory64, up to 16 GB of memory). Needs the Emscripten SDK
(`emsdk install latest && emsdk activate latest`, then its `emsdk_env` script) and a static libhdf5 built for 64-bit
WebAssembly, made once by `scripts/build_hdf5_wasm.sh <work folder>`.

```bash
scripts/build_wasm.sh <work folder of build_hdf5_wasm.sh>   # build/wasm/dist: the npm package
node --test wasm/test/*.test.mjs                        # the end-to-end test, in Node.js 24+
```

Each WebAssembly test checks its own duration against the same one-second limit.

The `WebAssembly` workflow builds the package on every push to `main` that changes the sources, runs these tests and
publishes it as `O_o_Reader-wasm.zip` in two [releases](https://github.com/jcdulas/O_o_Reader/releases):
`wasm-latest`, a pre-release that follows the branch, and one release kept for each version of `wasm/package.json`
(`v0.2.0`, ...), made by the first build of that version and not changed afterwards; the newest of these is the
latest release of the repository. Raise the version in `wasm/package.json` to keep a new one. Each run also keeps the
package 90 days as its `O_o_Reader-wasm` artifact.

## Licence

MIT (see [LICENSE](LICENSE)). The WebAssembly package includes HDF5 (BSD-style licence) and zlib (zlib licence).
