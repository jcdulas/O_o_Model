// The numbers JavaScript gives the module (card IDs, keys, field numbers, table positions) are checked before they
// are used, and the workbook keeps its texts well-formed.
import assert from "node:assert/strict";
import path from "node:path";
import { test } from "./helpers/fast-test.mjs";
import { fileURLToPath, pathToFileURL } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const dist = process.env.OOR_DIST ?? path.join(here, "..", "..", "build", "wasm", "dist");
const { loadOoModel } = await import(pathToFileURL(path.join(dist, "index.js")).href);
const oor = await loadOoModel();

const WHOLE = /must be a whole number from/;

function twoNodes() {
  const deck = oor.createModel();
  deck.addCard({ type: "Node", fields: [1, null, 1, 2, 3] });
  deck.addCard({ type: "Node", fields: [2, null, 4, 5, 6] });
  return deck;
}

test("a card ID that is not a whole 32-bit number is refused, never rounded to another card", () => {
  const deck = twoNodes();
  try {
    assert.equal(deck.card("nodes", 1, []).id, 1);
    assert.equal(deck.card("nodes", 7, []), null);
    for (const id of [1.9, 0.5, Number.NaN, Number.POSITIVE_INFINITY, 2 ** 32 + 1, -(2 ** 31) - 1]) {
      assert.throws(() => deck.card("nodes", id, []), WHOLE, `card(${id})`);
      assert.throws(() => deck.cardById("nodes", id), WHOLE, `cardById(${id})`);
      assert.throws(() => deck.cardFields("nodes", id), WHOLE, `cardFields(${id})`);
      assert.throws(() => deck.cardFieldNames("nodes", id), WHOLE, `cardFieldNames(${id})`);
      assert.throws(() => deck.setCardField("nodes", id, 3, "9."), WHOLE, `setCardField(${id})`);
      assert.throws(() => deck.setCardFields("nodes", id, ["1", "", "9.", "9.", "9."]), WHOLE, `setCardFields(${id})`);
      assert.throws(() => deck.setCardValue("nodes", id, "position1", "9."), WHOLE, `setCardValue(${id})`);
      assert.throws(() => deck.replaceCard("nodes", id, "Node;1;;9.;9.;9."), WHOLE, `replaceCard(${id})`);
      assert.throws(() => deck.removeCard("nodes", id), WHOLE, `removeCard(${id})`);
    }
    // nothing was edited or removed on the way
    assert.equal(deck.cardCount(), 2);
    assert.deepEqual(Array.from(deck.nodes[1].xyz), [1, 2, 3]);
    assert.equal(deck.removeCard("nodes", 1), true);
    assert.equal(deck.cardCount(), 1);
  } finally { deck.delete(); }
});

test("a field number and a key are whole numbers of their range", () => {
  const deck = twoNodes();
  try {
    for (const field of [0, 2.5, -1, Number.NaN])
      assert.throws(() => deck.setCardField("nodes", 1, field, "9."), WHOLE, `field ${field}`);
    deck.setCardField("nodes", 1, 3, "9.");
    assert.equal(deck.nodes[1].xyz[0], 9);

    const key = deck.nodes[2].key;
    assert.equal(deck.cardByKey({ type: "Node", key }).id, 2);
    for (const wrong of [key + 0.5, -1, 2 ** 32, Number.NaN]) {
      assert.throws(() => deck.cardByKey({ type: "Node", key: wrong }), WHOLE, `cardByKey(${wrong})`);
      assert.throws(() => deck.removeCardRef({ type: "Node", key: wrong }), WHOLE, `removeCardRef(${wrong})`);
      assert.throws(() => deck.setCardComment({ type: "Node", key: wrong }, "x"), WHOLE, `setCardComment(${wrong})`);
      assert.throws(() => deck.caseControl.section(wrong), WHOLE, `section(${wrong})`);
    }
    assert.equal(deck.cardCount(), 2);
    const global = deck.caseControl.global;
    assert.equal(deck.caseControl.section(global.key).key, global.key);
  } finally { deck.delete(); }
});

test("the position of a table or of a named result is a whole number from zero", () => {
  const results = oor.createResults([
    { kind: "displacements", subcase: 1, ids: [1], values: new Float64Array([1, 2, 3, 4, 5, 6]) },
    { kind: "displacements", subcase: 2, ids: [1], values: new Float64Array(6).fill(9) }], "review");
  try {
    results.addNamed({ kind: "aeroPressures", name: "wing", subcase: 1, analysisCode: 144, arrays: {
      elementId: { type: "int32", shape: [1], values: [7] },
      pressureCoefficient: { shape: [1], values: [0.5] }, pressure: { shape: [1], values: [2] } },
      texts: { elementKind: ["LS"] } });
    assert.equal(results.read(0).values[0], 1);
    assert.equal(results.read(1).values[0], 9);
    assert.equal(results.readNamed(0).name, "wing");
    for (const index of [-1, 0.5, 1.7, Number.NaN]) {
      assert.throws(() => results.read(index), WHOLE, `read(${index})`);
      assert.throws(() => results.readNamed(index), WHOLE, `readNamed(${index})`);
    }
    assert.throws(() => results.read(2), /there is no result table 2/);
    assert.throws(() => results.readNamed(1), /out of range/);
  } finally { results.delete(); }
});

test("a workbook keeps a long sheet name of accented letters a well-formed text", () => {
  const results = oor.createResults(
    [{ kind: "displacements", ids: [1], values: new Float64Array(6) }], "review");
  try {
    // "aeroPressures " and letters of two bytes each: a cut at 31 bytes would fall inside a letter
    results.addNamed({ kind: "aeroPressures", name: "é".repeat(30), subcase: 1, analysisCode: 144, arrays: {
      elementId: { type: "int32", shape: [1], values: [7] },
      pressureCoefficient: { shape: [1], values: [0.5] }, pressure: { shape: [1], values: [2] } },
      texts: { elementKind: ["LS"] } });
    assert.equal(results.writeXlsx("/work/review-names.xlsx", { compressionLevel: 0 }).finished, true);
    // the parts are stored, not compressed: the whole file must decode but for the binary headers between the parts
    const bytes = oor.readFile("/work/review-names.xlsx");
    const text = Buffer.from(bytes).toString("latin1");
    const from = text.indexOf("<workbook "), to = text.indexOf("</workbook>");
    assert.ok(from > 0 && to > from, "the workbook part is in the file");
    const workbook = new TextDecoder("utf-8", { fatal: true }).decode(bytes.subarray(from, to));
    assert.ok(workbook.includes(`name="aeroPressures ${"é".repeat(17)}"`), workbook);
  } finally { results.delete(); }
});
