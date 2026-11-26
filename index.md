# O_o_Model documentation

Build, edit and query finite element models through the O_o_Model API in JavaScript (WebAssembly), Python or C++20. Applications supply cards and analysis controls in memory. O_o_Solver consumes the resulting model tables through its API.

**[Published documentation](https://jcdulas.github.io/O_o_Model/)** · [JavaScript / WASM releases](https://github.com/jcdulas/O_o_Model/releases) · [Native Python wheels](https://pypi.org/project/oo-model/0.2.4/)

## Start here

- [Getting started](docs/getting-started.md): install a package and run the same example in JavaScript, Python and C++.
- [JavaScript operations](docs/wasm-api.md) and [Python package](docs/python.md) cover model I/O, queries and typed tables.
- [Project overview](README.md): capabilities, repository layout and build commands.
- [Model input reference](docs/reference/index.md) covers the command line, initialization, case control, bulk data and parameters.
- [API reference](docs/api.rst): JavaScript, Python and C++ operations, TypeScript declarations and C++ headers.
- [Mesh edit benchmark and RBE3 regression](docs/model-clients.md) gives comparable results across all three clients.
- [Construct and edit models](docs/model-construction.md): cards, load cases, includes, parts and batch input.
- [Optimization with JavaScript, Python and C++](docs/optimization.md): design points, model updates and accepted-point archives.
- [Architecture with diagrams](docs/architecture.md): module dependencies, data ownership and execution flow.
- [Module guide](docs/modules.md): implementation structure and detailed technical guides.
- [Element names](docs/element-naming.md): shared vocabulary, implementation roles and compatibility.
- [Download or build the documentation](docs/documentation.md): published site, HTML archives and local builds.

## Detailed guides

- [Model format](docs/model-format.md) and [card catalogue](docs/model-format-cards.md).
- [JavaScript, Python and C++ operations](docs/wasm-api.md) and [native model/results archive](docs/archive-format.md).
- [Architecture](docs/architecture.md), [table packages](docs/table-package.md) and [naming](docs/naming.md).

## Model and Solver

| Project | Responsibility |
| --- | --- |
| [O_o_Model](https://github.com/jcdulas/O_o_Model/blob/main/index.md) | Model construction, editing, validation and typed queries |
| [O_o_Solver](https://github.com/jcdulas/O_o_Solver/blob/main/index.md) | Model snapshots, finite element analyses and result arrays |

JavaScript transfers typed table packages between the two WASM memories. Python passes Arrow buffers within the same process. The Solver returns arrays of results to the caller.

~~~{toctree}
:hidden:
:maxdepth: 2
:caption: User guide

docs/getting-started
docs/python
docs/optimization
README
docs/model-format
docs/wasm-api
docs/model-construction
docs/model-clients
docs/archive-format
docs/table-package
docs/naming
docs/element-naming
~~~

~~~{toctree}
:hidden:
:maxdepth: 2
:caption: Reference and development

docs/reference/index
docs/api
docs/architecture
docs/modules
validation/models/README
docs/documentation
LEGAL
~~~
