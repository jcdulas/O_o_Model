# Read, download and build the documentation

## Read online

The public site is **[O_o_Reader documentation](https://jcdulas.github.io/O_o_Reader/)**.
Start with the [paired JavaScript and Python examples](getting-started.md) or look up an operation in the [API reference](api.rst).
The [architecture guide](architecture.md) explains the modules and data flow with diagrams.
The [source index](../index.md) and the Markdown guides can also be read directly on GitHub.

The Documentation workflow builds and publishes `main`. Pull requests build the site and validate its local links,
images and diagrams; publication follows a successful build on `main` or a manual run.

## Download HTML

1. Open the [Documentation workflow](https://github.com/jcdulas/O_o_Reader/actions/workflows/documentation.yml).
2. Open its latest successful run on `main`.
3. Download the `O_o_Reader-documentation` artifact from **Artifacts** or the run summary.
4. Extract the ZIP archive and open `index.html`.

Archives are retained for 90 days. Use **Run workflow** to create a fresh archive if an older one has expired.
The published site remains the stable reading address.

For local browser search, serve the extracted directory:

~~~bash
python -m http.server 8000 --bind 127.0.0.1
~~~

Open `http://127.0.0.1:8000/`.

## Build locally

The documentation toolchain uses Python 3.13 or later. It does not require compiling the C++ libraries or WebAssembly.
From the repository root:

~~~bash
python -m venv .venv-docs
# Linux/macOS: source .venv-docs/bin/activate
# PowerShell:  .\.venv-docs\Scripts\Activate.ps1
python -m pip install -r docs/requirements.txt
python docs/diagrams/render.py --check
python -m sphinx -W --keep-going -b html -c docs -d build/docs/doctrees . build/docs/html
python docs/check_html.py build/docs/html
python -m http.server 8000 --bind 127.0.0.1 --directory build/docs/html
~~~

Generated HTML stays under the ignored `build/` directory.

## Architecture images

The architecture figures are standalone SVG files in [images](images/). They retain sharp text when enlarged and
render directly in both the repository and the HTML site. Each embedded image has alternative text and an explanatory
caption in its guide.

Edit the nodes, descriptions and connecting arrows in [figures.json](diagrams/figures.json), then regenerate:

~~~bash
python docs/diagrams/render.py
~~~

The [renderer](diagrams/render.py) uses the Python standard library to generate the SVGs. Its `--check` mode
verifies that the committed images match their specifications; the documentation workflow runs that check before publication.

The reader/solver boundary figure is shared by the two public projects. Keep its two copies aligned when changing
the inter-module contract. Update an image's alternative text and surrounding explanation when its meaning changes.

## Maintain the pages

- Edit the original Markdown guides or module `README.md` files. Sphinx reads them in place.
- Edit API declarations in their original header or TypeScript file. The API reference includes these files directly.
- Update the navigation in `index.md` and `docs/modules.md` when adding a page.
- Keep headings unique within each page so fragment links remain stable.
- Build with warnings treated as errors and run the local-resource checker before pushing.

The [model input reference](reference/index.md) uses the compiled Reader catalogues for the alphabetical
case-command and parameter entries. To regenerate them from the repository root with a native GCC or Clang build
and a single-configuration generator, use the same C++ compiler that built the libraries:

~~~sh
cmake --build build/native --target oor_model
c++ -std=c++20 -Iinclude tools/reference/write_control_reference.cpp \
    build/native/src/model/liboor_model.a build/native/src/deck/liboor_deck.a \
    build/native/src/io/liboor_io.a build/native/src/base/liboor_base.a -o build/write_control_reference
./build/write_control_reference docs/reference
~~~

The HTML build reads the checked-in Markdown and needs no compiler. For changes to card layouts, regenerate the
[card catalogue](model-format-cards.md) and its subject pages with `python tools/oos_layouts/write_cards_doc.py`.
The generator combines the model layouts, neutral vocabulary, typed card definitions, validation models and the
editorial descriptions in `tools/oos_layouts/reference/`. It reports missing purposes, field definitions and examples.
Run `python tools/oos_layouts/write_cards_doc.py --check` to check that the committed pages match their sources.
With the native `oo-reader` Python package installed, run `python tools/oos_layouts/check_card_examples.py` to
strict-read every published example and verify its typed card count and stable canonical representation.
Add `--archive` to verify each example through the native HDF5 adapter as well.

When changing archive storage, update [the format specification](archive-format.md), the
[JavaScript archive workflow](wasm-api.md#a-model-and-results-in-one-archive), the
[format selection guide](getting-started.md#choose-a-file-format) and the
[compatibility summary](element-naming.md#compatibility). Keep the API reference links to the public OOH5 adapter headers current. Review the model-input and archive diagrams when
loading or ownership changes. Keep archive version, native model schema version and table-package contract distinct.

The downloadable archive includes navigation, styles, images and the search index. Source-code links open the public
repository at `main`.
