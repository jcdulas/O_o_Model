import { resolve } from "node:path";
import { readFile } from "node:fs/promises";
import { pathToFileURL } from "node:url";
const [modelModule, solverModule, fixture] = process.argv.slice(2);
const model = await (await import(pathToFileURL(resolve(modelModule)))).loadOoModel();
const solver = await (await import(pathToFileURL(resolve(solverModule)))).loadOosSolver();
const ids = Int32Array.from({length: fixture ? 20301 : 200000}, (_, i) => i + 1);
const x = Float64Array.from(ids, id => (id - 1) * 0.00123456789);
const selected = Int32Array.from({length: 1000}, (_, i) => ids[(fixture ? 19 : 199)*i]);
const xyz = new Float64Array(3000);
for (let i = 0; i < selected.length; ++i) {
  const row = selected[i] - 1;
  xyz[3*i] = fixture ? row % 201 : -(i + 1);
  if (fixture) { xyz[3*i+1] = Math.floor(row / 201); xyz[3*i+2] = 0.001; }
}
if (fixture) model.writeFile("/work/shell.oos", new Uint8Array(await readFile(fixture)));
let deck;
let trial, snapshot;
try {
  const start = performance.now();
  deck = fixture ? model.readModel("/work/shell.oos", {strict: true}) : model.createModel();
  if (!fixture) deck.addCardBatch("Node", {id: ids, position1: x, position2: 0, position3: 0});
  const built = performance.now();
  trial = deck.copy();
  const copied = performance.now();
  trial.setNodePositions(selected, xyz);
  const edited = performance.now();
  snapshot = solver.modelFromReader(model, trial);
  const end = performance.now();
  const repeated = [];
  for (let i = 0; i < 7; ++i) {
    snapshot.delete();
    snapshot = undefined;
    xyz[2] += 0.001;
    trial.setNodePositions(selected, xyz);
    const begin = performance.now();
    snapshot = solver.modelFromReader(model, trial);
    repeated.push(performance.now() - begin);
  }
  repeated.sort((a, b) => a - b);
  console.log(JSON.stringify({build_ms: built-start, copy_ms: copied-built,
                             edit_ms: edited-copied, snapshot_ms: end-edited,
                             repeat_snapshot_ms: repeated[3]}));
} finally { snapshot?.delete(); trial?.delete(); deck?.delete(); }
