# Model edits in external optimization loops

The client checks exercise the public JavaScript, Python and C++ interfaces. The RBE3 check also runs against Solver 0.2.2. To reproduce the optimized snapshot timings, use Model 0.2.3 and Solver 0.2.3.

## RBE3 wing regression

Read the six-node wing from the Solver fixture. Evaluate its hinge moment and its derivative with respect to the basic X coordinate of RBE3 attachment node 6. Copy the model, move that node from (0.180, 1.75, 0) to (0.181, 1.75, 0), check the references and prepare a new SOL 144/105 problem. Finally, repeat the measurement on the retained point and on a fresh evaluation of the original model.

| Quantity | Original | Edited copy | Retained point and original rebuilt |
| --- | ---: | ---: | ---: |
| Hinge moment, response 4 | −0.906834794443 | −0.906885152804 | −0.906834794443 |
| Hinge moment derivative with respect to node 6 X | −0.050322129981 | −0.050394514339 | −0.050322129981 |

The three clients check against one reference with relative tolerance `2e-7` and absolute tolerance `1e-9`. The edit is in the node's input frame, which is the basic frame for node 6. All three programs compute the derivative from the retained Solver evaluation. [JavaScript](../tests/clients/rbe3.mjs) · [Python](../tests/clients/rbe3.py) · [C++](../tests/clients/rbe3.cpp)

## Cost of one mesh edit and snapshot

Each client creates 200,000 nodes, copies the deck, replaces the three coordinates of 1,000 nodes spaced 199 rows apart in a single call, and builds a Solver snapshot of the edited copy. Coordinate arrays are prepared before timing. Snapshot time includes the transfer of the model tables. This mesh contains only nodes, so no element assembly, factorization or solution time enters the measurement.

| Client | Construct nodes (ms) | Copy model (ms) | Edit 1,000 nodes (ms) | Build snapshot (ms) |
| --- | ---: | ---: | ---: | ---: |
| JavaScript / WASM64 | 207.60 | 0.812 | 0.903 | 268.95 |
| Python / NumPy | 121.11 | 0.028 | 0.980 | 30.83 |
| C++20 | 113.38 | 0.018 | 0.864 | 34.08 |

These are the original measurements with Solver 0.2.2, before the snapshot changes. Each phase shows its median over three fresh processes. The edit includes detaching the coordinate column shared with the original deck. [JavaScript](../tests/clients/mesh.mjs) · [Python](../tests/clients/mesh.py) · [C++](../tests/clients/mesh.cpp)

## Rebuilding after coordinate edits

The nodal benchmark isolates coordinate transfer on 200,000 nodes in the basic frame. A second benchmark reads a patch with 20,301 nodes, 20,000 quadrilateral shells, one material and one shell property. Every hundredth node starting at node 1 has a displacement frame rotated 90 degrees. The first trial moves 1,000 nodes out of plane on the patch. Each subsequent trial resubmits the same coordinates with one additional Z displacement at node 1.

| Model | Client | First snapshot before (ms) | First snapshot after (ms) | Rebuild before (ms) | Rebuild after (ms) |
| --- | --- | ---: | ---: | ---: | ---: |
| Nodes | JavaScript / WASM64 | 257.48 | 201.83 | 45.54 | 17.73 |
| Nodes | Python / NumPy | 34.27 | 15.14 | 26.15 | 8.08 |
| Nodes | C++20 | 32.75 | 14.69 | 26.24 | 8.20 |
| Shells | JavaScript / WASM64 | 249.94 | 241.11 | 34.97 | 27.01 |
| Shells | Python / NumPy | 17.63 | 17.29 | 12.78 | 12.57 |
| Shells | C++20 | 18.17 | 17.52 | 13.62 | 12.66 |

Measurements alternate the two builds over five fresh processes per version and client on the same Windows x64 workstation with Node.js 24 and CPython 3.13. Each process loads the modules, prepares the deck and times the first snapshot. It then times seven rebuilds, releasing the previous snapshot and applying the edit before starting each timer. The table reports the median across processes of the first time and of the seven-rebuild medians. Timings cover model transfer and snapshot construction. Assembly, factorization and solution are separate operations.

When every displacement frame is basic, Solver uses the identity rotation implicitly. At 200,000 nodes this saves a 14.4 MB array. With local displacement frames, Model reads the frame IDs and global positions directly from the nodal table to build the rotations. In storage order, the global XYZ column shares the coordinate buffer or the transformed-position cache. Later edits detach shared coordinates so previously exported snapshots retain their geometry. JavaScript still transfers the tables between two WASM memories and reuses the Model module's query catalogue across snapshots.

## Reproduce the checks

Use Model and Solver source checkouts in adjacent directories. With the Model build dependencies installed, build the C++ clients with the following commands from the Model root.

```sh
cmake -S tests/clients -B build/clients -G Ninja -DCMAKE_BUILD_TYPE=Release -DSOLVER_SOURCE="$PWD/../O_o_Solver"
cmake --build build/clients --target rbe3 mesh
```

Pass an **absolute path** for `SOLVER_SOURCE` if the directories have a different layout. For JavaScript, build both WASM64 packages. For Python, install both local packages into the same environment. The following commands use the Unix single-configuration executable layout.

```sh
fixture=../O_o_Solver/wasm/test/fixtures/trim-rbe3-wing.oos
node tests/clients/rbe3.mjs build/wasm/dist/index.js ../O_o_Solver/build/wasm/dist/index.js "$fixture" > build/js.json
python tests/clients/rbe3.py "$fixture" > build/python.json
build/clients/rbe3 "$fixture" > build/cpp.json
python tests/clients/check_rbe3.py build/js.json
python tests/clients/check_rbe3.py build/python.json
python tests/clients/check_rbe3.py build/cpp.json

node tests/clients/mesh.mjs build/wasm/dist/index.js ../O_o_Solver/build/wasm/dist/index.js
python tests/clients/mesh.py
build/clients/mesh

python tests/clients/shell_mesh.py build/shell.oos
node tests/clients/mesh.mjs build/wasm/dist/index.js ../O_o_Solver/build/wasm/dist/index.js build/shell.oos
python tests/clients/mesh.py build/shell.oos
build/clients/mesh build/shell.oos
```
