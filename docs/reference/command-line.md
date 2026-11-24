# 1. Command line

## Read and inspect a model

Save the [rod model](introduction.md#a-rod-in-tension) as `tie.oos` in your working directory. Each script takes the input path as its first argument, prints the node and rod counts, and writes a model archive in the current working directory. Install the interface you use as described in [Getting started](../getting-started.md#install-the-packages).

**JavaScript / WebAssembly** · Save as `inspect.mjs` and run `node inspect.mjs tie.oos`.

~~~javascript
import { readFile, writeFile } from "node:fs/promises";
import { loadOoModel } from "./model/index.js";

const reader = await loadOoModel();
reader.writeFile("/work/input.oos", await readFile(process.argv[2]));
const deck = reader.readModel("/work/input.oos", { strict: true });
try {
  const counts = deck.cardCounts();
  console.log(counts.Node, counts.Rod2); // 2 1
  deck.writeArchive("/work/tie.ooh5");
  await writeFile("tie.ooh5", reader.readFile("/work/tie.ooh5"));
} finally {
  deck.delete();
}
~~~

**Python / native C++** · Save as `inspect_model.py` and run `python inspect_model.py tie.oos`.

~~~python
import sys
from oo_model import read_model

deck = read_model(sys.argv[1], strict=True)
print(deck.card_counts["Node"], deck.card_counts["Rod2"])  # 2 1
deck.write_archive("tie.ooh5")
~~~

## Input paths and working directory

The Python reader opens the host path directly. In the JavaScript example the first path is on the host, while `/work/input.oos` belongs to the module. For a model split across files, stage the includes under the same relative directory layout in the module, or place the files beside the root model on the host for Python. [Includes and parts](../model-format.md#includes-and-parts)

## Arguments and diagnostics

| Setting | Where to supply it | Effect |
| --- | --- | --- |
| Input path | First argument of either example | Opens the supplied model |
| Output path | The archive-writing call and, for JavaScript, the host write | Chooses where to save the archive |
| Strict reading | `{ strict: true }` or `strict=True` | Stops on a malformed known record and identifies its location |

To reopen the output, pass `tie.ooh5` as the input path. The Model recognizes the format by content. Choose a different output filename if you want to keep both archives.
