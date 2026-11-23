"""Source material for the model card reference. All paths refer to this checkout."""
import csv
import json
import re
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DATA = Path(__file__).parent / "reference"
FAMILIES = {
    "aero": "Aerodynamics and aeroelasticity",
    "constraints": "Constraints", "coordinate_systems": "Coordinate systems",
    "dynamics": "Dynamics", "elements": "Elements and connections", "explicit": "Explicit analysis",
    "loads": "Loads", "materials": "Materials", "matrices": "Matrices", "nodes": "Points and geometry",
    "nonlinear_contact": "Nonlinear analysis and contact", "optimisation": "Design and optimization",
    "parameters": "Model parameters", "properties": "Element properties", "rigid_elements": "Rigid elements",
    "sets": "Sets", "solution_control": "Solution controls", "superelements": "Superelements",
    "tables": "Functions and tables", "thermal": "Heat transfer",
}


def words(name):
    tokens = re.findall(r"[A-Z]+(?=[A-Z][a-z]|\d|$)|[A-Z]?[a-z]+|[0-9]+|[A-Z]", name)
    return " ".join({"id": "ID", "dof": "degree of freedom", "mat": "material", "elem": "element",
                     "coord": "coordinate", "freq": "frequency", "prop": "property",
                     "coeff": "coefficient", "constr": "constraint", "ref": "reference",
                     "num": "number", "max": "maximum", "min": "minimum"}.get(t.lower(), t.lower()) for t in tokens)


@dataclass
class Example:
    record: str
    path: str = ""


def examples_for(cards):
    # Prefer short readable records in real model files over isolated parser fixtures.
    choices = defaultdict(list)
    for path in sorted((ROOT / "validation/models").rglob("*.oos")):
        for line in path.read_text(encoding="utf-8-sig").splitlines():
            name = line.partition(";")[0]
            if name in cards and not re.search("nastran|autodesk|patran|abaqus|ansys|MSC Software", line, re.I):
                choices[name].append(Example(line, path.relative_to(ROOT).as_posix()))

    def rank(example):
        fields = next(csv.reader([example.record], delimiter=";"))
        filled = sum(bool(field.strip()) for field in fields[1:])
        return (max(0, len(example.record) - 125), filled < 2, -min(6, filled), len(example.record),
                example.path, example.record)

    examples = {name: min(entries, key=rank) for name, entries in choices.items()}
    # Standalone geometry declarations and deliberately uncalibrated material-format examples.
    examples.update({name: Example(line) for name, line in {
        "SurfaceEdge": "SurfaceEdge;1;301;302;Smooth",
        "SurfaceFacet": "SurfaceFacet;501",
        "SurfaceLine": "SurfaceLine;1;501;502;503",
        "SphericalDetonation": "SphericalDetonation;1;1",
        "JonesWilkinsLeeStateEquation": "JonesWilkinsLeeStateEquation;1",
    }.items()})
    for name in ("DeflagrationStateEquation", "IgnitionGrowthStateEquation"):
        values = ["1" if f["kind"] == "integer" else "1." if f["kind"] == "real" else ""
                  for f in cards[name]["fields"]]
        examples[name] = Example(";".join([name, *values]))
    if examples.keys() != cards.keys():
        raise ValueError(f"Review examples for {sorted(cards.keys() ^ examples.keys())}")
    return examples


@dataclass
class Card:
    name: str
    family: str
    purpose: str
    example: Example
    references: dict
    diagnostics: list
    required: set
    id_space: str
    member_notes: dict


def read_cards(layouts):
    purposes = json.loads((DATA / "purposes.json").read_text(encoding="utf-8"))
    if purposes.keys() != layouts.keys():
        raise ValueError(f"Review card purposes for {sorted(purposes.keys() ^ layouts.keys())}")
    examples = examples_for(layouts)
    headers = {p.stem[:-4]: p for p in (ROOT / "include/oor/model/cards").rglob("*Card.hpp")}
    result = {}
    for name in layouts:
        header = headers[name]
        family = header.relative_to(ROOT / "include/oor/model/cards").parts[0]
        folder = ROOT / "src" / header.parent.relative_to(ROOT / "include/oor")
        table = folder / (name + "Table.cpp")
        code = table.read_text(encoding="utf-8") if table.exists() else ""
        t_header = header.with_name(name + "Table.hpp").read_text(encoding="utf-8")
        space = re.search(r"CardCategory::\w+\s*,\s*base::IdSpace::(\w+)", t_header)
        refs = defaultdict(set)
        for field, target in re.findall(r'visitor\.visit\(\s*"(\w+)"\s*,\s*ReferenceTarget::(\w+)', code):
            refs[field].add(target)
        required = set(re.findall(r'reader\.required(?:Integer|Real|Text)\(\s*\d+\s*,\s*"(\w+)"', code))
        # Only publish literal, self-contained diagnostics. Dynamic bounds depend on runtime values.
        messages = re.findall(r'CardProblem\{\s*"[\w.-]+"\s*,\s*"([^"\\]+)"\s*,\s*"(\w+)"\s*\}', code)
        diagnostics = []
        for msg, f in dict.fromkeys(messages):
            msg = re.sub(r"\{field:(\w+)\}", r"`\1`", msg.replace("{field}", f"`{f}`"))
            if not re.search(r'\b[A-Z]{3,}\d*\b|format reference|implementation|[<>]\w|[{}]', msg):
                diagnostics.append((f, msg))
        notes = {}
        for field, note in re.findall(r'\b(\w+)\s*(?:=\s*[^;\n]*)?;\s*//\s*([^\n]+)', header.read_text(encoding="utf-8")):
            if (len(note) > 14 and not re.search(r'\b[A-Z][A-Z0-9_]+\b|\b(?:format|blank|member|column|solver|layout)\b|[;{}\x60]|:\s*$',
                                                  note)
                    and not note.endswith((",", " and", " or", " the"))):
                notes[field] = note.strip().rstrip(".")
        result[name] = Card(name, family, purposes[name], examples[name], dict(refs), diagnostics, required,
                            space[1] if space else "", notes)
    return result


def example_links(cards, layouts):
    """Resolve explicit fixed-field IDs against records in the same example model section."""
    by_path = defaultdict(list)
    for card in cards.values():
        if card.example.path:
            by_path[card.example.path].append(card)
    related = {}
    for path, examples in by_path.items():
        definitions = defaultdict(set)
        sections = defaultdict(set)
        section = ""
        for line in (ROOT / path).read_text(encoding="utf-8-sig").splitlines():
            if line.startswith("["):
                section = line if line.lower().startswith("[model") else ""
            name = line.partition(";")[0]
            if not section or name not in cards:
                continue
            sections[line].add(section)
            fields = layouts[name].get("fields", [])
            if not fields or fields[0]["name"] != "id":
                continue
            value = line.split(";", 2)[1]
            if value.isdecimal() and int(value) > 0:
                definitions[section, cards[name].id_space, int(value)].add(name)
        for card in examples:
            record = card.example.record
            if len(sections[record]) != 1:
                continue
            section = next(iter(sections[record]))
            values = next(csv.reader([record], delimiter=";"))[1:]
            links = defaultdict(list)
            for field, value in zip(layouts[card.name].get("fields", []), values):
                if not value.isdecimal() or int(value) <= 0:
                    continue
                name = field["name"]
                key = "nodes" if "nodes" in card.references and re.fullmatch(r"node(?:[A-C]|\d+)", name) else name
                targets = {other for space in card.references.get(key, ())
                           for other in definitions.get((section, space, int(value)), ())}
                if len(targets) == 1 and card.name not in targets:
                    links[next(iter(targets))].append((name, value))
            if links:
                related[card.name] = links
    return related
