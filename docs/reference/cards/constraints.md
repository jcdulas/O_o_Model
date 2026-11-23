# Constraints

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AutoConstrExclusion

Excludes specified point components from automatic singularity constraints.

**Record format and fields**

`AutoConstrExclusion;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
AutoConstrExclusion;7;345;8;345
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

## AutoConstrExclusionList

Excludes the same specified components at a list of points from automatic singularity constraints.

**Record format and fields**

`AutoConstrExclusionList;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `components` — C must be 0 or a list of the digits 1 to 6, each at most once.

**Example record**

~~~text
AutoConstrExclusionList;345;2;Through;4
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `components = 345`.

## CyclicAxisNodes

The grid points that lie on the axis of symmetry of a cyclic symmetry model.

**Record format and fields**

`CyclicAxisNodes;<nodes>`

This part of the record has no fixed fields.

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
CyclicAxisNodes;100
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_rot_modes_sol115.oos)

## CyclicBoundaryJoin

The boundary points of one side of a segment in a cyclic symmetry problem.

**Record format and fields**

`CyclicBoundaryJoin;sideCode;system;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sideCode` | `integer` | Required | Selects one side of the join, element or interface in the record’s local ordering. |
| 2 | `system` | `text` | — | Coordinate or selection system applying to this entry. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Constant`, `Cylindrical`, `Element`, `Rectangular`, `Spherical`, `Table`, `Through`, `Translation1`, `Translation2`, `Translation3`.

**Example record**

~~~text
CyclicBoundaryJoin;1;Translation2;1;Through;5
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_axi_table_load_sol114.oos)

Reading the example gives `sideCode = 1`, `system = Translation2`.

## CyclicSupport

The fictitious supports of a cyclic symmetry model.

**Record format and fields**

`CyclicSupport;nodeId;components`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | Required | Identifier of the grid point addressed by this record. |
| 2 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeId` — the grid point ID must be a positive integer.
- `components` — C must be a combination of the digits 1 to 6, each at most once.

**Example record**

~~~text
CyclicSupport;5;1245
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_rot_modes_sol115.oos)

Reading the example gives `nodeId = 5`, `components = 1245`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeId = 5`.

## EnforcedMotionConstr

The value of an enforced motion (displacement, velocity or acceleration) of one or two grid points.

**Record format and fields**

`EnforcedMotionConstr;id;node1;components1;enforcedValue1;node2;components2;enforcedValue2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | Required | Identifier addressing node data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `enforcedValue1` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 1. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `enforcedValue2` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 2. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.

**Example record**

~~~text
EnforcedMotionConstr;1;204;1;0.002;204;2;-0.01
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `id = 1`, `node1 = 204`, `components1 = 1`, `enforcedValue1 = 0.002`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 204`, `node2 = 204`.

## FreeBodySupport

The reference degrees of freedom of a free body (the r-set), which determine its rigid body motion.

**Record format and fields**

`FreeBodySupport;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
FreeBodySupport;1;123
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/free_free_suport_modes.oos)

## FreeBodySupportSet

Identifies the reference degrees of freedom for a free body and groups them under a selectable set ID.

**Record format and fields**

`FreeBodySupportSet;id;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the support set ID must be a positive integer.

**Example record**

~~~text
FreeBodySupportSet;5;1;456
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/free_free_suport_modes.oos)

Reading the example gives `id = 5`, `node1 = 1`, `components1 = 456`.

## GeomBoundaryCurve

Defines a line-interface boundary from the ordered element edges along a geometric curve.

**Record format and fields**

`GeomBoundaryCurve;id;startNode;endNode;entity;<entityIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `startNode` | `integer` | Required | Grid point at the beginning of the path or directed edge. |
| 3 | `endNode` | `integer` | Required | Grid point at the end of the path or directed edge. |
| 4 | `entity` | `text` | — | Entity selected by this constraint or group definition. |

**Repeated group `entityIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entityId` | `integer` | — | Identifier selecting the entity record or set. |

Accepted words: `Constant`, `Element`, `Node`, `Table`.

**Example record**

~~~text
GeomBoundaryCurve;2;411;423;Node;414;417;420
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `id = 2`, `startNode = 411`, `endNode = 423`, `entity = Node`.

## GeomSinglePointConstr

Applies single-point constraints to the grid points associated with a geometric entity.

**Record format and fields**

`GeomSinglePointConstr;id;components;entityType;entityId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `entityType` | `text` | — | Selects the entity type for GeomSinglePointConstr. |
| 4 | `entityId` | `integer` | Required | Identifier addressing other data. |

Accepted words: `ElementEdge`, `ElementFace`, `GeomCurve`, `GeomSurface`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `entityId` — the entity ID must be a positive integer.

**Example record**

~~~text
GeomSinglePointConstr;2;3;ElementFace;1001
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `id = 2`, `components = 3`, `entityType = ElementFace`, `entityId = 1001`.

## MultiPointConstr

A multipoint constraint equation, the sum of Aj * u(Gj, Cj) = 0.

**Record format and fields**

`MultiPointConstr;id;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `coefficient` | `real` | — | Coefficient value in the MultiPointConstr relation for terms. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `node1` — the card needs at least one term.
- `node1` — a grid or scalar point ID must be a positive integer.
- `components1` — C must be one of the integers 1 to 6, or 0 for a scalar point.

**Example record**

~~~text
MultiPointConstr;50;31;1;1.;15;1;-1.
~~~

[Model containing this record](../../../validation/models/cuts_monitor_points/cuts_model.oos)

Reading the example gives `id = 50`.

## MultiPointConstrAxisym

A multipoint constraint equation of a conical shell, the sum of Aj * u(RIDj, HIDj, Cj) = 0.

**Record format and fields**

`MultiPointConstrAxisym;id;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ringId` | `integer` | — | Identifier selecting the ring record or set. |
| 2 | `harmonicId` | `integer` | — | Identifier selecting the harmonic record or set. |
| 3 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 4 | `coefficient` | `real` | — | Coefficient value in the MultiPointConstrAxisym relation for terms. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `ringId1` — the card needs at least one term.
- `ringId1` — a ring ID must be a positive integer.
- `harmonicId1` — a harmonic ID must not be negative.
- `components1` — C must be one of the integers 1 to 6.

**Example record**

~~~text
MultiPointConstrAxisym;2;4;1;3;1.;5;1;3;-1.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 2`.

## MultiPointConstrUnion

A multipoint constraint set that is the union of other multipoint constraint sets.

**Record format and fields**

`MultiPointConstrUnion;id;<memberSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `memberSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberSetId` | `integer` | — | Identifier addressing constraint set data. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `memberSetId1` — the card needs at least one constraint set.
- `memberSetId1` — a constraint set ID must be a positive integer.
- `memberSetId1` — a union of sets cannot refer to its own set ID.

**Example record**

~~~text
MultiPointConstrUnion;20;21;22
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 20`.

## MultiPointConstrValue

The load selectable right hand side Ym of one or two equations of non-homogeneous multipoint constraints (the [MultiPointConstrWithValue](constraints.md#multipointconstrwithvalue) cards).

**Record format and fields**

`MultiPointConstrValue;id;dependentNode1;dependentComponents1;rightHandSide1;dependentNode2;dependentComponents2;rightHandSide2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `dependentNode1` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `dependentComponents1` | `integer` | 0 | Component digits whose motion is determined by the constraint. Entry 1. |
| 4 | `rightHandSide1` | `real` | 0.0 | Specified value on the right-hand side of the constraint equation. Entry 1. |
| 5 | `dependentNode2` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `dependentComponents2` | `integer` | 0 | Component digits whose motion is determined by the constraint. Entry 2. |
| 7 | `rightHandSide2` | `real` | 0.0 | Specified value on the right-hand side of the constraint equation. Entry 2. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `dependentNode1` — the grid or scalar point ID must be a positive integer.
- `dependentNode2` — the grid or scalar point ID must be a positive integer.

**Example record**

~~~text
MultiPointConstrValue;22;15;3;0.2
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 22`, `dependentNode1 = 15`, `dependentComponents1 = 3`, `rightHandSide1 = 0.2`.

## MultiPointConstrWithValue

Defines a linear constraint on nodal degrees of freedom with a prescribed right-hand side.

**Record format and fields**

`MultiPointConstrWithValue;id;dependentNode;dependentComponents;dependentCoefficient;rightHandSide;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `dependentNode` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `dependentComponents` | `integer` | 0 | Component digits whose motion is determined by the constraint. |
| 4 | `dependentCoefficient` | `real` | Required | Coefficient in the relation for dependent. |
| 5 | `rightHandSide` | `real` | 0.0 | Specified value on the right-hand side of the constraint equation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `coefficient` | `real` | — | Coefficient value in the MultiPointConstrWithValue relation for terms. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `dependentNode` — the grid or scalar point ID must be a positive integer.
- `nodes` — a grid or scalar point ID must be a positive integer.

**Example record**

~~~text
MultiPointConstrWithValue;50;15;3;1.;0.;14;3;-1.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 50`, `dependentNode = 15`, `dependentComponents = 3`, `dependentCoefficient = 1.`.

## RelativeEnforcedMotionConstr

The value of an enforced relative motion of one or two grid points, taken with respect to the position they had at the previous load step.

**Record format and fields**

`RelativeEnforcedMotionConstr;id;node1;components1;enforcedValue1;node2;components2;enforcedValue2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `enforcedValue1` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 1. |
| 5 | `node2` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `enforcedValue2` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 2. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node1` — the grid or scalar point ID must be a positive integer.
- `node2` — the grid or scalar point ID must be a positive integer.

**Example record**

~~~text
RelativeEnforcedMotionConstr;22;31;3;-0.01
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/sol400_spcr_rbe3_coincident.oos)

Reading the example gives `id = 22`, `node1 = 31`, `components1 = 3`, `enforcedValue1 = -0.01`.

## SinglePointConstr

Single point constraints, with an enforced motion, on one or two grid points.

**Record format and fields**

`SinglePointConstr;id;node1;components1;enforcedValue1;node2;components2;enforcedValue2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | Required | Identifier addressing node data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `enforcedValue1` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 1. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `enforcedValue2` | `real` | 0.0 | Prescribed value of the selected degree of freedom, in its displacement or rotation units. Entry 2. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.

**Example record**

~~~text
SinglePointConstr;1;5;1;20.;15;1;20.
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_heat_shell_tempn1.oos)

Reading the example gives `id = 1`, `node1 = 5`, `components1 = 1`, `enforcedValue1 = 20.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 5`, `node2 = 15`.

## SinglePointConstrAxisym

A single point constraint or an enforced displacement of a conical shell coordinate.

**Record format and fields**

`SinglePointConstrAxisym;id;ringId;harmonicId;components;enforcedValue`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `ringId` | `integer` | Required | Identifier addressing node data. |
| 3 | `harmonicId` | `integer` | Required | Identifier selecting the harmonic record or set. |
| 4 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 5 | `enforcedValue` | `real` | Required | Prescribed value of the selected degree of freedom, in its displacement or rotation units. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `ringId` — the ring ID must be a positive integer.
- `harmonicId` — the harmonic ID must not be negative.
- `components` — C must be a list of the digits 1 to 6, each at most once.

**Example record**

~~~text
SinglePointConstrAxisym;1;5;2;1;0.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 1`, `ringId = 5`, `harmonicId = 2`, `components = 1`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId = 5`.

## SinglePointConstrList

Single point constraints on a list of grid points.

**Record format and fields**

`SinglePointConstrList;id;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Constraint-set ID selected in case control. |
| 2 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which the same component mask is applied. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `components` — C must be 0 or a list of the digits 1 to 6, each at most once.
- `node1` — the card needs at least one grid point.

**Example record**

~~~text
SinglePointConstrList;1;123456;1;3;7;9
~~~

[Model containing this record](../../../validation/models/glued_contact/glued_stiffener_edge.oos)

Reading the example gives `id = 1`, `components = 123456`.

## SinglePointConstrUnion

A constraint set that is the union of other constraint sets.

**Record format and fields**

`SinglePointConstrUnion;id;<memberSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `memberSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberSetId` | `integer` | — | Identifier addressing constraint set data. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the constraint set ID must be a positive integer.
- `memberSetId1` — the card needs at least one constraint set.
- `memberSetId1` — a constraint set ID must be a positive integer.
- `memberSetId1` — a union of sets cannot refer to its own set ID.

**Example record**

~~~text
SinglePointConstrUnion;1;11;12
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 1`.
