import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import { resolve } from "node:path";
import { pathToFileURL } from "node:url";

const [modelModule, solverModule, fixture] = process.argv.slice(2);
const model = await (await import(pathToFileURL(resolve(modelModule)))).loadOoModel();
const solver = await (await import(pathToFileURL(resolve(solverModule)))).loadOosSolver();
model.writeFile("/work/wing.oos", new Uint8Array(await readFile(fixture)));
const source = model.readModel("/work/wing.oos", { strict: true });
function evaluate(deck) {
  const problem = solver.optimizationFromReader(model, deck, {}, { analyses: { aeroelastic: [1], buckling: [2] } });
  try { return problem.evaluate(); } finally { problem.delete(); }
}
function measure(point) {
  return [point.values().responses.find(r => r.id === 4).values[0],
          point.nodalCoordinateGradient(4, [6]).values[0]];
}
const point = evaluate(source);
const trial = source.copy();
try {
  const before = measure(point);
  trial.setNodePositions(Int32Array.of(6), Float64Array.of(.181, 1.75, 0));
  assert.equal(trial.checkReferences().length, 0);
  const moved = evaluate(trial);
  const fresh = evaluate(source);
  try { console.log(JSON.stringify([before, measure(moved), measure(point), measure(fresh)])); }
  finally { fresh.delete(); moved.delete(); }
} finally { trial.delete(); point.delete(); source.delete(); }
