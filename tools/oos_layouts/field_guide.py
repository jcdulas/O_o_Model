"""Field conventions shared by the compact layouts, including lists and keyed sections."""
import json
import re

from card_reference import DATA, words

COMMON = json.loads((DATA / "fields.json").read_text(encoding="utf-8"))
PHYSICAL = dict(line.split("\t", 1) for line in (DATA / "physical-fields.tsv").read_text(encoding="utf-8").splitlines())
SPECIFIC = json.loads((DATA / "conventions.json").read_text(encoding="utf-8"))
INDEXED = [(re.compile(pattern), meaning) for pattern, meaning in
           (line.split("\t", 1) for line in (DATA / "indexed-fields.tsv").read_text(encoding="utf-8").splitlines())]
CORNERS = {"SolidTetra": 4, "SolidHexa": 8, "SolidPenta": 6, "SolidPyramid": 5,
           "ShellTria3": 3, "ShellTria6": 3, "ShellQuad4": 4, "ShellQuad8": 4,
           "PlaneStressTria6": 3, "PlaneStressQuad8": 4, "PlaneStrainTria6": 3, "PlaneStrainQuad8": 4}
# Connectivity order used by the Reader's geometry module (SolidVolume.hpp).
SOLID_EDGES = {
    "SolidTetra": [(1, 2), (2, 3), (3, 1), (1, 4), (2, 4), (3, 4)],
    "SolidPenta": [(1, 2), (2, 3), (3, 1), (1, 4), (2, 5), (3, 6), (4, 5), (5, 6), (6, 4)],
    "SolidHexa": [(1, 2), (2, 3), (3, 4), (4, 1), (1, 5), (2, 6), (3, 7), (4, 8),
                  (5, 6), (6, 7), (7, 8), (8, 5)],
    "SolidPyramid": [(1, 2), (2, 3), (3, 4), (4, 1), (1, 5), (2, 5), (3, 5), (4, 5)],
}
DIMENSIONS = {
    "Pressure": "force per area", "Stress": "force per area", "Modulus": "force per area",
    "Thickness": "length", "Radius": "length", "Diameter": "length", "Length": "length",
    "Distance": "length", "Width": "length", "Area": "length squared", "Volume": "length cubed",
    "Frequency": "inverse time", "Velocity": "length per time", "Speed": "length per time",
    "Acceleration": "length per time squared", "Time": "time", "Temperature": "temperature",
    "MomentOfInertia": "length to the fourth power", "Force": "force", "Strain": "dimensionless",
}
ID_NAMES = {"Group": "Set identifier shared by entries in the same group.",
            "PerCardType": "Identifier in the namespace of this card type.",
            "None": "Identifier carried by the record."}


def definition(card, field, context=""):
    name = field["name"]
    label = words(name)
    if name in SPECIFIC.get(card.name, {}):
        return SPECIFIC[card.name][name]
    if name == "id":
        return ID_NAMES.get(card.id_space, "Identifier in the " + words(card.id_space) + " namespace."
                            if card.id_space else "Identifier of this entry.")
    node = re.fullmatch(r"node(\d+)", name)
    if node and card.name in CORNERS:
        i, corners = int(node[1]), CORNERS[card.name]
        if i <= corners:
            return f"Grid point at corner {i} of the element connectivity."
        if card.name in SOLID_EDGES:
            start, end = SOLID_EDGES[card.name][i - corners - 1]
            return f"Optional grid point on the edge joining corners {start} and {end}. Blank or zero omits it."
        return f"Additional grid point at edge position {i - corners} after the {corners} corners."
    if card.name in {"ShellQuad4", "ShellTria3", "ShellQuad8", "ShellTria6"}:
        if name == "materialAngle":
            return "Rotation of the material direction relative to the element axes, in degrees."
        if name == "offset":
            return "Signed distance of the reference surface from the grid-point plane, along the element normal."
        if name == "thicknessFlag":
            return "Selects absolute corner thicknesses or factors of the property thickness."
        if name.startswith("cornerThickness"):
            return "Thickness at this corner, or a multiplier of the property thickness according to the thickness flag."
    if name in COMMON:
        return COMMON[name]
    targets = card.references.get(name, set())
    if targets:
        return "Identifier addressing " + " or ".join(words(t) for t in sorted(targets)) + " data."
    base = re.sub(r"\d+$", "", name)
    ordinal = name[len(base):]
    if ordinal and base in COMMON:
        return COMMON[base] + f" Entry {ordinal}."
    if re.fullmatch(r"node(?:\d+|[A-Z])", name):
        return f"Grid point identifier at connectivity position {name[4:]}."
    if name in PHYSICAL:
        return PHYSICAL[name]
    if ordinal and base in PHYSICAL:
        return PHYSICAL[base] + f" Entry {ordinal}."
    specialized = patterned_definition(card, name, base, context)
    if specialized:
        return specialized
    if base.endswith("TableId"):
        return "Table supplying the variation of " + words(base[:-7]) + "."
    if base.endswith("Id"):
        return "Identifier selecting the " + words(base[:-2]) + " record or set."
    if base.endswith("Count"):
        return "Number of " + words(base[:-5]) + " entries."
    if re.fullmatch(r"(?:pinFlags|components)[A-Z0-9]+", name):
        return "Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6."
    if name.startswith("entryValue") or name.startswith("propertyField") or name.startswith("connectionField"):
        return "Positional input to the selected entry. Its interpretation is defined by the entry type or user routine."
    if name in {"kind", "type", "method", "form"} or base.endswith(("Kind", "Method", "Option", "Type", "Flag")):
        subject = context or card.name
        return "Selects the " + label + " for " + subject + "."
    if base.endswith("Name") or base.endswith("Label"):
        return "Text naming the " + words(re.sub(r"(Name|Label)$", "", base)) + "."
    if base.endswith(("Coefficient", "Exponent", "Factor", "Ratio", "Tolerance")):
        suffix = re.search(r"(Coefficient|Exponent|Factor|Ratio|Tolerance)$", base)[1]
        quantity = words(base[:-len(suffix)])
        if quantity:
            return {"Coefficient": "Coefficient in the relation for ", "Exponent": "Power in the law for ",
                    "Factor": "Multiplier for ", "Ratio": "Relative measure of ",
                    "Tolerance": "Permitted numerical deviation for "}[suffix] + quantity + "."
    if field["kind"] in {"real", "number"}:
        for suffix, dimension in DIMENSIONS.items():
            if base.endswith(suffix) or base == suffix.lower():
                return label.capitalize() + " (" + dimension + ")."
    if name in card.member_notes:
        note = card.member_notes[name]
        if note.lower() != label.lower():
            return note[:1].upper() + note[1:] + "."
    for pattern, meaning in INDEXED:
        if match := pattern.fullmatch(name):
            return meaning.format(match[0], *match.groups())
    raise ValueError(f"No field definition for {card.name}.{name} ({context})")

def patterned_definition(card, name, base, context):
    # The suffixes distinguish physical locations, not additional fields in the record.
    if card.family == "coordinate_systems":
        if m := re.fullmatch(r"frameId([AB])", name):
            return f"Identifier of coordinate system {m[1]} defined by this record."
        if m := re.fullmatch(r"node([123])([AB])", name):
            role = {"1": "origin", "2": "point on the positive z-axis", "3": "point in the positive x–z half-plane"}[m[1]]
            return f"Grid point defining the {role} of frame {m[2]}."
        if m := re.fullmatch(r"point([ABC])([123])", name):
            role = {"A": "origin", "B": "point on the positive z-axis", "C": "point in the positive x–z half-plane"}[m[1]]
            return f"Coordinate {m[2]} of the {role}, expressed in the reference frame."
    if card.family == "tables" and name in {"x", "y"}:
        return ("Independent sample coordinate along the table axis." if name == "x"
                else "Tabulated response at the corresponding independent coordinate.")
    if card.family == "properties":
        suffix = re.search(r"(EndB|NodeC|[AB])$", name)
        where = {"EndB": " at end B", "NodeC": " at node C", "B": " at end B", "A": " at end A"}.get(
            suffix[1] if suffix else "", "")
        if m := re.match(r"(?:station)?[sS]tressPoint([C-F])([yz])", name):
            return f"Local {m[2]} coordinate of stress-recovery point {m[1]}{where} in the cross-section (length)."
        if m := re.match(r"warpingGradient([YZ])At([C-F])", name):
            return f"Derivative of the section warping function in local {m[1]} at recovery point {m[2]}{where}."
        if m := re.match(r"warpingAt([C-F])", name):
            return f"Section warping function at recovery point {m[1]}{where}."
        if m := re.match(r"(neutralAxis|nsmCenter)([YZ])", name):
            axis = "elastic neutral axis" if m[1] == "neutralAxis" else "centre of nonstructural mass"
            return f"Local {m[2]} coordinate of the {axis}{where} (length)."
        if name.startswith("nsmInertia"):
            return f"Sectional mass moment or product of inertia of the nonstructural mass{where}, about the indicated local axes."
        if re.search("bendingInertia", name, re.I):
            return f"Second moment of the section area for bending about the indicated local axis{where} (length to the fourth power)."
        if re.search("productInertia", name, re.I):
            return f"Product of section area about the local bending axes{where} (length to the fourth power)."
        if "torsionConstant" in name or name == "stationTorsionConstant":
            return f"Section torsion constant{where}; it multiplies the shear modulus in the torsional rigidity."
        if name.startswith("nonStructMass"):
            return f"Additional mass per unit member length{where}."
        if name.startswith("warpingCoefficient"):
            return f"Section coefficient for restrained warping{where}."
        if name.startswith(("stationDimension", "dimension")):
            return "Cross-section dimension in the order specified by the selected section shape (length)."
        if name.startswith(("stationStressOutput", "stressOutput")):
            return f"Controls stress recovery at the specified section location{where}."
    if m := re.fullmatch(r"(node|propId|patchId|solidId|shellId|superelementId|moduleId|frameId)([A-Z])(\d*)", name):
        thing = {"node":"grid point", "propId":"property", "patchId":"patch", "solidId":"solid",
                 "shellId":"shell", "superelementId":"superelement", "moduleId":"module", "frameId":"coordinate system"}[m[1]]
        return f"Identifier of the {thing} on side {m[2]}" + (f" at position {m[3]}." if m[3] else ".")
    if m := re.fullmatch(r"componentsAt([ABC])", name):
        return f"Selected degrees of freedom at point {m[1]}."
    if m := re.fullmatch(r"(offset|orientation)([123])([ABC])?", name):
        endpoint = f" at end {m[3]}" if m[3] else ""
        kind = "offset vector" if m[1] == "offset" else "orientation vector"
        return f"Component {m[2]} of the {kind}{endpoint} in the specified frame."
    if m := re.fullmatch(r"(?:station)?[sS]tressPoint([C-F])([yz])", name):
        return f"Local {m[2]} coordinate of section stress-recovery point {m[1]} (length)."
    if m := re.fullmatch(r"(point|center|localCenter|origin|boxOrigin|surfacePoint|location|start|end|min|max|pole)([XYZ])(\d*)", name):
        roles = {"origin":"origin", "boxOrigin":"box origin", "center":"centre", "localCenter":"centre in local axes",
                 "point":"specified point", "start":"start point", "end":"end point", "surfacePoint":"point on the surface",
                 "location":"location", "min":"lower spatial bound", "max":"upper spatial bound", "pole":"pole"}
        return f"{m[2]} coordinate of the {roles[m[1]]}" + (f" at position {m[3]}." if m[3] else ".")
    if m := re.fullmatch(r"(boxWidth|elemSize|width|height|depth|meshSize|elemCount|cubeCount|partitionCount)([XYZ])", name):
        if "Count" in m[1]:
            return f"Number of {words(m[1][:-5])} subdivisions along {m[2]}."
        return f"Size of the {words(m[1])} dimension along {m[2]} in length units."
    if m := re.fullmatch(r"(warpDirection|weftDirection|direction|velocity|accel|angularVelocity|normal|load|initialPosition)([XYZ0-9]+)", name):
        quantities = {"warpDirection":"warp direction vector", "weftDirection":"weft direction vector",
                      "direction":"specified direction", "velocity":"velocity vector (length per time)",
                      "accel":"acceleration vector (length per time squared)", "angularVelocity":"angular velocity vector",
                      "normal":"surface normal", "load":"applied load", "initialPosition":"initial position"}
        return f"Component {m[2]} of the {quantities[m[1]]}."
    if m := re.fullmatch(r"(youngsModulus|shearModulus|poissonRatio|thermalExpansion|conductivity|inertia)([A-Z][a-zA-Z0-9]*)", name):
        return {"youngsModulus":"Uniaxial elastic modulus (force per area)",
                "shearModulus":"Shear modulus (force per area)", "poissonRatio":"Transverse contraction ratio",
                "thermalExpansion":"Thermal expansion coefficient (inverse temperature)",
                "conductivity":"Thermal conductivity tensor component",
                "inertia":"Component of the inertia tensor"}[m[1]] + f" in the {m[2]} material or local axes."
    if m := re.fullmatch(r"(translationalStiffness|rotationalStiffness|rotationalDamping|extensionalDamping|stiffness|damping|massTerm|mass)(\d+)", name):
        return f"Entry {m[2]} of the {words(m[1])} coefficients in the local component order."
    if m := re.fullmatch(r"(temperature|pressure|traction|gradient[YZ]|twist|value)([A-F]{1,2})", name):
        measure = {"temperature":"Temperature", "pressure":"Pressure (force per area)", "traction":"Applied traction",
                   "gradientY":"Local y temperature gradient", "gradientZ":"Local z temperature gradient",
                   "twist":"Section twist", "value":"Specified value"}[m[1]]
        return f"{measure} at the labeled position {m[2]}."
    if m := re.fullmatch(r"(?:station|point|dimension|id)(\d+)", name):
        role = re.sub(r"\d+", "", name)
        return f"{role.capitalize() if role != 'id' else 'Identifier'} at position {m[1]} in the ordered {context or card.name} data."
    if m := re.fullmatch(r"(hashinFabric|hashinTape|hashinUnidirectional|strainLifeTerm|strainLifeError|snCurveTerm|meanStressTerm|spotWeldTerm|interactionTerm|degradationParameter)(\d*)", name):
        return f"Parameter {m[2] or 'value'} of the {words(m[1])} relation for this material."
    if m := re.fullmatch(r"(behavior|heatBehavior|integration|heatIntegration)(\d+)", name):
        return f"{words(m[1]).capitalize()} setting for the element configuration identified by {m[2]}."
    if m := re.fullmatch(r"(coefficient|constant)([A-Z]?\d*|[A-Z][a-z])", name):
        return f"Coefficient {m[2] or 'value'} in the {card.name} relation" + (f" for {words(context)}." if context else ".")
    if m := re.fullmatch(r"(?:real|integer|text)(?:Data|Attribute)", name):
        return "Payload passed in the declared type and order to the consumer of the record."
    if m := re.fullmatch(r"(fiber|matrix)(Compression|Tension|Shear)(Degradation|Theory|Scale)", name):
        return f"{m[3]} setting for the {m[2].lower()} response of the {m[1]} constituent."
    if m := re.fullmatch(r"(solid|liquid|austenite|martensite)(Density|ThermalExpansion|StressSlope|StressLimit)", name):
        return f"{words(m[2]).capitalize()} of the material in its {m[1]} phase."
    return None
