# 4. Bulk data

The `[model]` section holds the geometry, connectivity, properties, materials, loads and constraints. Browse the [subject index](../model-format-cards.md#browse-by-subject) or the [alphabetical catalogue](../model-format-cards.md#cards). Each entry describes the purpose, field order, types, defaults and applicable variants, followed by a worked input record.

## Reading an entry

**Purpose.** `Rod2` connects two nodes using a rod property.

**Format.** `Rod2;id;propId;node1;node2`

| Field | Type | Meaning in the example |
| --- | --- | --- |
| `id` | Integer | Element 20 |
| `propId` | Integer | Property 30 supplies the area and identifies the material. A blank field defaults to the element ID. |
| `node1`, `node2` | Integer | Node IDs 1 and 2 define the element axis |

**Example.** `Rod2;20;30;1;2` connects the two nodes of the [rod model](introduction.md). Follow `RodProp;30;40;0.0004` to `IsoMat;40;7.0e10;;0.33;2700.`. The empty field between Young’s modulus and Poisson’s ratio is the shear-modulus field. [Rod2](cards/elements.md#rod2) · [RodProp](cards/properties.md#rodprop) · [IsoMat](cards/materials.md#isomat)

**Remarks.** Keep internal empty fields so the next value reaches the intended column. Trailing empty fields may be omitted. Some other cards accept a count or repeated group after the fixed fields. [Field conventions](../model-format.md#cards)

## Find a card by task

| Task | Entry points |
| --- | --- |
| Locate a node or define shell connectivity | [Node](cards/nodes.md#node) · [ShellTria3](cards/elements.md#shelltria3) · [ShellQuad4](cards/elements.md#shellquad4) |
| Define a solid and its material | [SolidTetra](cards/elements.md#solidtetra) · [SolidHexa](cards/elements.md#solidhexa) · [SolidProp](cards/properties.md#solidprop) |
| Set an applied load or hold nodal components | [PointForceLoad](cards/loads.md#pointforceload) · [SinglePointConstrList](cards/constraints.md#singlepointconstrlist) |
| Describe a design variable or a design region | [DesignVar](cards/optimisation.md#designvar) · [DesignTopologyRegion](cards/optimisation.md#designtopologyregion) |

~~~{toctree}
:hidden:
:maxdepth: 1

../model-format-cards
~~~
