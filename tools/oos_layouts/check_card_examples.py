"""Strict-read the published examples, write them again, and check canonical round trips.

Run after write_cards_doc.py --check with a native oo-reader from the same checkout.
"""
import json
import re
from pathlib import Path
from tempfile import TemporaryDirectory

from oo_reader import read_model

from card_reference import ROOT


def main():
    expected = set(json.loads((ROOT / "formats/oos-layouts.json").read_text(encoding="utf-8"))["cards"])
    checked = set()
    with TemporaryDirectory() as work:
        source, saved, again = (Path(work) / n for n in ("record.oos", "saved.oos", "again.oos"))
        for page in sorted((ROOT / "docs/reference/cards").glob("*.md")):
            content = page.read_text(encoding="utf-8")
            for name, section in re.findall(r"^## (\w+)\n(.*?)(?=^## |\Z)", content, re.S | re.M):
                examples = re.findall(r"^\*\*Example record\*\*\n\n~~~text\n(.+?)\n~~~", section, re.M)
                if len(examples) != 1 or name in checked or examples[0].split(";")[0] != name:
                    raise ValueError(f"{page.name}: expected one example for {name}")
                source.write_text("[model]\n" + examples[0] + "\n", encoding="utf-8")
                deck = read_model(source, strict=True)
                counts = deck.card_counts
                if set(counts) != {name} or counts[name] < 1:
                    raise ValueError(f"{name}: unexpected typed cards {counts}")
                deck.write_model(str(saved))
                restored = read_model(saved, strict=True)
                restored.write_model(str(again))
                if restored.card_counts != counts or saved.read_bytes() != again.read_bytes():
                    raise ValueError(f"{name}: canonical record changed on rereading")
                checked.add(name)
    if checked != expected:
        raise ValueError(f"Catalogue mismatch: {sorted(expected ^ checked)}")
    print(f"{len(checked)} card examples passed strict reading and canonical round trips.")


if __name__ == "__main__":
    main()
