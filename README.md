# O_o_Model

Build, edit and query finite element models through the O_o_Model API in JavaScript (WebAssembly) or Python (native C++). Applications supply cards and analysis controls in memory. O_o_Solver consumes the resulting model tables through its API.

**[Sphinx documentation](https://jcdulas.github.io/O_o_Model/)** ·
[Model input reference](docs/reference/index.md) ·
[Model construction](https://jcdulas.github.io/O_o_Model/docs/model-construction.html) ·
[API reference](https://jcdulas.github.io/O_o_Model/docs/api.html)

## Install

| Interface | Install |
| --- | --- |
| JavaScript / WebAssembly | Extract the [Model ZIP](https://github.com/jcdulas/O_o_Model/releases/download/v0.2.1/O_o_Model-wasm.zip) into `model/` next to your script. Use Node.js 24+ or a browser with Memory64 support. |
| Python / native C++ | Install the [native wheel](https://pypi.org/project/oo-model/0.2.1/) with `python -m pip install oo-model==0.2.1`. For source builds, see the [native build requirements](docs/python.md#build-and-publish). |

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

For batches of nodes or elements, pass typed JavaScript arrays or NumPy columns. See the [construction guide](docs/model-construction.md) for load cases, validation and editing. Applications that need persistence can use the [OOS adapter](https://github.com/jcdulas/O_o_OOS) for text models or the [OOH5 adapter](https://github.com/jcdulas/O_o_OOH5) for HDF5 archives. The standard packages include both adapters. [Build profiles](docs/architecture.md#file-adapters)

## Documentation

[Optimization with JavaScript and Python](docs/optimization.md): design interfaces, derivatives and accepted model updates.

**[Read Sphinx documentation](https://jcdulas.github.io/O_o_Model/)** · [Architecture with diagrams](docs/architecture.md) · [Documentation index](index.md)

The Documentation workflow publishes the HTML site and provides a downloadable archive.
See [read, download and build instructions](docs/documentation.md).

New `.ooh5` files use archive version **4**, with native model schema **1**. Version **3** result archives remain
readable. See [choosing a format](docs/getting-started.md#choose-a-file-format) and
[archive compatibility](docs/archive-format.md#versions) before updating an existing viewer.

## Layout of the repository

| Folder | What |
| --- | --- |
| `include/oor/<module>/`, `src/<module>/` | the library, in modules that each use only the ones before them: `base` → `io` → `deck` → `model` → `results` → `analysis` → `query` → `api` |
| `src/formats/` | Compatibility facade and pinned revisions of the external [OOS text adapter](https://github.com/jcdulas/O_o_OOS) and [OOH5 archive adapter](https://github.com/jcdulas/O_o_OOH5) |
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
publishes it as `O_o_Model-wasm.zip` in two [releases](https://github.com/jcdulas/O_o_Model/releases):
`wasm-latest`, a pre-release that follows the branch, and one release kept for each version of `wasm/package.json`
(`v0.2.1`, ...), made by the first build of that version and not changed afterwards; the newest of these is the
latest release of the repository. Raise the version in `wasm/package.json` to keep a new one. Each run also keeps the
package 90 days as its `O_o_Model-wasm` artifact.

## Licence

MIT (see [LICENSE](LICENSE)). The WebAssembly package includes HDF5 (BSD-style licence) and zlib (zlib licence).
