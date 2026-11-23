# Sets

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AeroPrismNodeSet2

Selects structural grid points inside a prism over an aerodynamic panel for use by a spline.

**Record format and fields**

`AeroPrismNodeSet2;id;aeroPanelId;spanStart;spanEnd;chordStart;chordEnd;zMaximum;zMinimum`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier addressing aero element data. |
| 3 | `spanStart` | `real` | Required | Beginning of the selected interval in the spanwise coordinate. |
| 4 | `spanEnd` | `real` | Required | End of the selected interval in the spanwise coordinate. |
| 5 | `chordStart` | `real` | Required | Beginning of the selected interval in the chordwise coordinate. |
| 6 | `chordEnd` | `real` | Required | End of the selected interval in the chordwise coordinate. |
| 7 | `zMaximum` | `real` | 0.0 | Upper bound on the z coordinate of the selected region. |
| 8 | `zMinimum` | `real` | 0.0 | Lower bound on the z coordinate of the selected region. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `aeroPanelId` — the macro element ID must be a positive integer.

**Example record**

~~~text
AeroPrismNodeSet2;1100;1001;-0.01;1.01;-0.01;1.01;10.;-10.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/aero_spline_set2_trim.oos)

Reading the example gives `id = 1100`, `aeroPanelId = 1001`, `spanStart = -0.01`, `spanEnd = 1.01`.

**Referenced records in this example**

- [AeroLiftingPanel1](aero.md#aeroliftingpanel1) via `aeroPanelId = 1001`.

## AnalysisDofSet

Degrees of freedom of the analysis set (a-set).

**Record format and fields**

`AnalysisDofSet;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
AnalysisDofSet;17;3
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## AnalysisDofSet1

The degrees of freedom C of a list of points in the analysis set (a-set).

**Record format and fields**

`AnalysisDofSet1;components;<nodes>`

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
AnalysisDofSet1;123456;1;4;7
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

Reading the example gives `components = 123456`.

## AxisymOmittedDofSet

Degrees of freedom of a conical shell model that are excluded (the o-set) from the analysis set (the a-set).

**Record format and fields**

`AxisymOmittedDofSet;<dofs>`

This part of the record has no fixed fields.

**Repeated group `dofs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ringId` | `integer` | — | Identifier selecting the ring record or set. |
| 2 | `harmonicId` | `integer` | — | Identifier selecting the harmonic record or set. |
| 3 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `ringId` — the card has at most 12 degrees of freedom.

**Example record**

~~~text
AxisymOmittedDofSet;3;2;2;2;2;4
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

## DofSetRenames

New names for the degree-of-freedom sets.

**Record format and fields**

`DofSetRenames;oldName1;newName1;oldName2;newName2;oldName3;newName3;oldName4;newName4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `oldName1` | `text` | — | Text naming the old. |
| 2 | `newName1` | `text` | — | Text naming the new. |
| 3 | `oldName2` | `text` | — | Text naming the old. |
| 4 | `newName2` | `text` | — | Text naming the new. |
| 5 | `oldName3` | `text` | — | Text naming the old. |
| 6 | `newName3` | `text` | — | Text naming the new. |
| 7 | `oldName4` | `text` | — | Text naming the old. |
| 8 | `newName4` | `text` | — | Text naming the new. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `oldName1` — the card needs at least one pair of names.
- `oldName4` — the card has at most four pairs of names.

**Example record**

~~~text
DofSetRenames;U4;TIPS
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `oldName1 = U4`, `newName1 = TIPS`.

## FixedBoundaryDofSet

Degrees of freedom of the fixed analysis set (b-set).

**Record format and fields**

`FixedBoundaryDofSet;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
FixedBoundaryDofSet;9;12345;19;12345
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## FixedBoundaryDofSet1

The degrees of freedom C of a list of points in the fixed analysis set (b-set).

**Record format and fields**

`FixedBoundaryDofSet1;components;<nodes>`

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
FixedBoundaryDofSet1;12345;29
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `components = 12345`.

## FreeBoundaryDofSet

Degrees of freedom of the free boundary set (c-set).

**Record format and fields**

`FreeBoundaryDofSet;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
FreeBoundaryDofSet;5;3
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## FreeBoundaryDofSet1

The degrees of freedom C of a list of points in the free boundary set (c-set).

**Record format and fields**

`FreeBoundaryDofSet1;components;<nodes>`

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
FreeBoundaryDofSet1;3;15;25
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `components = 3`.

## GeneralizedDofSet

Degrees of freedom of the generalized set (q-set).

**Record format and fields**

`GeneralizedDofSet;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
GeneralizedDofSet;1007;0;1008;0
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## GeneralizedDofSet1

The degrees of freedom C of a list of points in the generalized set (q-set).

**Record format and fields**

`GeneralizedDofSet1;components;<nodes>`

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
GeneralizedDofSet1;0;1001;Through;1006
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `components = 0`.

## IdListSet1

Groups grid points or elements for selection by splines, interfaces and other model entries.

**Record format and fields**

`IdListSet1;id;<members>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `members`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberId` | `any` | — | Identifier selecting the member record or set. |

Accepted words: `SkinElems`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.

**Example record**

~~~text
IdListSet1;1401;1;2;3;4;5;6
~~~

[Model containing this record](../../../validation/models/aero_sol144/aero_model.oos)

Reading the example gives `id = 1401`.

## OmittedDofSet

Degrees of freedom of the omitted set (o-set).

**Record format and fields**

`OmittedDofSet;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
OmittedDofSet;13;3;23;3
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## OmittedDofSet1

The degrees of freedom C of a list of points in the omitted set (o-set).

**Record format and fields**

`OmittedDofSet1;components;<nodes>`

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
OmittedDofSet1;3;3;Through;4
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `components = 3`.

## PropertyListSet4

A list of property IDs of one type, which a [FatigueDefinition](solution_control.md#fatiguedefinition) (the fatigue definition) names.

**Record format and fields**

`PropertyListSet4;id;entityClass;type;<propIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `entityClass` | `text` | — | Type of model entity included in the set. |
| 3 | `type` | `text` | — | Selects the type for PropertyListSet4. |

**Repeated group `propIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `any` | — | Identifier of the property from which the element obtains its section or constitutive data. |

Accepted words: `All`, `BarProp`, `BeamProp`, `Constant`, `Element`, `Property`, `ShearPanelProp`, `ShellProp`, `SolidProp`, `Table`, `Through`, `WeldProp`.

**Example record**

~~~text
PropertyListSet4;71;Property;ShellProp;1;2
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/fatigue_property_sets.oos)

Reading the example gives `id = 71`, `entityClass = Property`, `type = ShellProp`.

## RadiatedPowerPanelSet

Any number of panels, each a label and the [TypedListSet3](sets.md#typedlistset3) of the elements or the properties that make it up.

**Record format and fields**

`RadiatedPowerPanelSet;<panels>`

This part of the record has no fixed fields.

**Repeated group `panels`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `panelName` | `text` | — | Text naming the panel. |
| 2 | `panelSetId` | `integer` | — | Identifier selecting the panel set record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `panelName1` — the card needs at least one panel.

**Example record**

~~~text
RadiatedPowerPanelSet;PLATE;42
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

## ShapeBoundaryNodeSet

The grid points on the boundary of a shape optimisation, with the components for which the boundary motion is prescribed (they form the s-set).

**Record format and fields**

`ShapeBoundaryNodeSet;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `components` — C must be a list of the digits 1 to 6, each at most once.

**Example record**

~~~text
ShapeBoundaryNodeSet;123456;1;Through;6
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/shape_boundary_bndgrid.oos)

Reading the example gives `components = 123456`.

## TypedListSet3

A list of grid points, elements, points, properties or modules that other cards refer to.

**Record format and fields**

`TypedListSet3;id;kind;<members>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `kind` | `text` | — | Selects the kind for TypedListSet3. |

**Repeated group `members`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberId` | `any` | — | Identifier selecting the member record or set. |

Accepted words: `Elements`, `GeomPoint`, `Module`, `Node`, `Property`, `RigidElemsExcluded`, `RigidElemsIncluded`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.

**Example record**

~~~text
TypedListSet3;1001;Node;7;8;9
~~~

[Model containing this record](../../../validation/models/solution_control/sol111_transfer_path_definition.oos)

Reading the example gives `id = 1001`, `kind = Node`.

## UserDofSet

Degrees of freedom of a set that the user names.

**Record format and fields**

`UserDofSet;setName;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setName` | `text` | — | Text naming the set. |
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

Accepted words: `FixedBoundaryLetter`, `SinglePointLetter`, `Through`.

**Example record**

~~~text
UserDofSet;U1;9;3;29;3
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `setName = U1`, `node1 = 9`, `components1 = 3`, `node2 = 29`.

## UserDofSet1

The degrees of freedom C of a list of points in a set that the user names.

**Record format and fields**

`UserDofSet1;setName;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setName` | `text` | — | Text naming the set. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

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
UserDofSet1;U2;3;5;15;25
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

Reading the example gives `setName = U2`, `components = 3`.
