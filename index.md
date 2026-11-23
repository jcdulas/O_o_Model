# O_o_Reader documentation

Read, edit and query finite element models in .oos and HDF5 .ooh5 format with the same C++20 library from **JavaScript (WebAssembly)** or **Python (native C++)**.

**[Published documentation](https://jcdulas.github.io/O_o_Reader/)** · [JavaScript / WASM releases](https://github.com/jcdulas/O_o_Reader/releases) · [Python wheels on PyPI](https://pypi.org/project/oo-reader/)

## Start here

- [Getting started](docs/getting-started.md): install either package and run the same example in JavaScript and Python.
- [JavaScript operations](docs/wasm-api.md) and [Python package](docs/python.md) cover model I/O, queries and typed tables.
- [Project overview](README.md): capabilities, repository layout and build commands.
- [API reference](docs/api.rst): JavaScript and Python operations, TypeScript declarations and C++ headers.
- [Construct and edit models](docs/model-construction.md): cards, load cases, includes, parts and batch input.
- [Optimization with JavaScript and Python](docs/optimization.md): design points, model updates and accepted-point archives.
- [Architecture with diagrams](docs/architecture.md): module dependencies, data ownership and execution flow.
- [Module guide](docs/modules.md): implementation structure and detailed technical guides.
- [Element names](docs/element-naming.md): shared vocabulary, implementation roles and compatibility.
- [Download or build the documentation](docs/documentation.md): published site, HTML archives and local builds.

## Detailed guides

- [Model format](docs/model-format.md) and [card catalogue](docs/model-format-cards.md).
- [JavaScript and Python operations](docs/wasm-api.md) and [native model/results archive](docs/archive-format.md).
- [Architecture](docs/architecture.md), [table packages](docs/table-package.md) and [naming](docs/naming.md).

## Reader and Solver

| Project | Responsibility |
| --- | --- |
| [O_o_Reader](https://github.com/jcdulas/O_o_Reader/blob/main/index.md) | Model records, native model/results archives and model queries |
| [O_o_Solver](https://github.com/jcdulas/O_o_Solver/blob/main/index.md) | Finite element analyses from reader tables |

The reader and solver have public documentation sites and exchange model data through typed table packages.

~~~{toctree}
:hidden:
:maxdepth: 2
:caption: User guide

docs/getting-started
docs/python
docs/optimization
README
docs/model-format
docs/model-format-cards
docs/wasm-api
docs/model-construction
docs/archive-format
docs/table-package
docs/naming
docs/element-naming
~~~

~~~{toctree}
:hidden:
:maxdepth: 2
:caption: Reference and development

docs/api
docs/architecture
docs/modules
validation/models/README
docs/documentation
LEGAL
~~~
