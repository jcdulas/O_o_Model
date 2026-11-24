# Elements and connections

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AcousticAbsorberProp

The property of an [AcousticAbsorber](thermal.md#acousticabsorber) frequency-dependent acoustic absorber element.

**Record format and fields**

`AcousticAbsorberProp;id;resistanceTableId;reactanceTableId;impedanceScale;area;damping;stiffness;characteristicImpedance`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `resistanceTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 3 | `reactanceTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 4 | `impedanceScale` | `real` | 1.0 | Multiplier on the acoustic impedance assigned to the element. |
| 5 | `area` | `real` | 1.0 | Surface or cross-sectional measure, in squared model length units. |
| 6 | `damping` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. |
| 7 | `stiffness` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 8 | `characteristicImpedance` | `real` | 1.0 | Pressure-to-particle-velocity ratio used as the acoustic reference impedance. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `resistanceTableId` — a table ID cannot be negative.

**Example record**

~~~text
AcousticAbsorberProp;31;32;33;1.;;;;4.13E-7
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 31`, `resistanceTableId = 32`, `reactanceTableId = 33`, `impedanceScale = 1.`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `resistanceTableId = 32`, `reactanceTableId = 33`.

## AcousticAxisymFluid2

An axisymmetric fluid element that connects two fluid points (the fluid of an axisymmetric slot or cavity analysis, together with an [AcousticSlotControl](nodes.md#acousticslotcontrol) card).

**Record format and fields**

`AcousticAxisymFluid2;id;fluidPointId1;fluidPointId2;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 4 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.

**Example record**

~~~text
AcousticAxisymFluid2;101;1;2
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 101`, `fluidPointId1 = 1`, `fluidPointId2 = 2`.

## AcousticAxisymFluid3

An axisymmetric fluid element that connects three fluid points (the fluid of an axisymmetric slot or cavity analysis, together with an [AcousticSlotControl](nodes.md#acousticslotcontrol) card).

**Record format and fields**

`AcousticAxisymFluid3;id;fluidPointId1;fluidPointId2;fluidPointId3;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 4 | `fluidPointId3` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 5 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 6 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.

**Example record**

~~~text
AcousticAxisymFluid3;105;2;13;3
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 105`, `fluidPointId1 = 2`, `fluidPointId2 = 13`, `fluidPointId3 = 3`.

## AcousticAxisymFluid4

An axisymmetric fluid element that connects four fluid points (the fluid of an axisymmetric slot or cavity analysis, together with an [AcousticSlotControl](nodes.md#acousticslotcontrol) card).

**Record format and fields**

`AcousticAxisymFluid4;id;fluidPointId1;fluidPointId2;fluidPointId3;fluidPointId4;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 4 | `fluidPointId3` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 5 | `fluidPointId4` | `integer` | Required | Identifier selecting the fluid point record or set. |
| 6 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 7 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.

**Example record**

~~~text
AcousticAxisymFluid4;103;1;11;12;2
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 103`, `fluidPointId1 = 1`, `fluidPointId2 = 11`, `fluidPointId3 = 12`.

## AcousticInfiniteProp

The property of the acoustic conjugate infinite elements ([AcousticInfiniteTria3](elements.md#acousticinfinitetria3) and [AcousticInfiniteQuad4](elements.md#acousticinfinitequad4)).

**Record format and fields**

`AcousticInfiniteProp;id;matId;radialOrder;poleX;poleY;poleZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `radialOrder` | `integer` | Required | Radial interpolation order, greater than zero. |
| 4 | `poleX` | `real` | 0.0 | X coordinate of the pole. |
| 5 | `poleY` | `real` | 0.0 | Y coordinate of the pole. |
| 6 | `poleZ` | `real` | 0.0 | Z coordinate of the pole. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AcousticInfiniteProp;31;2;5;100.;100.;0.
~~~

[Model containing this record](../../../validation/models/acoustics/infinite_elements_sol108.oos)

Reading the example gives `id = 31`, `matId = 2`, `radialOrder = 5`, `poleX = 100.`.

**Referenced records in this example**

- [FluidMat](materials.md#fluidmat) via `matId = 2`.

## AcousticInfiniteQuad4

The base of an acoustic conjugate infinite element, a quadrilateral of four acoustic grid points.

**Record format and fields**

`AcousticInfiniteQuad4;id;propId;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AcousticInfiniteQuad4;3001;31;1001;1006;1106;1101
~~~

[Model containing this record](../../../validation/models/acoustics/infinite_elements_sol108.oos)

Reading the example gives `id = 3001`, `propId = 31`, `node1 = 1001`, `node2 = 1006`.

**Referenced records in this example**

- [AcousticInfiniteProp](elements.md#acousticinfiniteprop) via `propId = 31`.

## AcousticInfiniteTria3

The base of an acoustic conjugate infinite element, a triangle of three acoustic grid points.

**Record format and fields**

`AcousticInfiniteTria3;id;propId;node1;node2;node3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AcousticInfiniteTria3;3033;31;1201;1202;1207
~~~

[Model containing this record](../../../validation/models/acoustics/infinite_elements_sol108.oos)

Reading the example gives `id = 3033`, `propId = 31`, `node1 = 1201`, `node2 = 1202`.

**Referenced records in this example**

- [AcousticInfiniteProp](elements.md#acousticinfiniteprop) via `propId = 31`.

## AcousticSlot3

A three-point slot element of the acoustic cavity analysis (an evenly spaced radial slot that solves the wave equation in two dimensions).

**Record format and fields**

`AcousticSlot3;id;slotPoint1;slotPoint2;slotPoint3;density;bulkModulus;slotCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `slotPoint1` | `integer` | — | Point defining the location on the acoustic slot. Entry 1. |
| 3 | `slotPoint2` | `integer` | — | Point defining the location on the acoustic slot. Entry 2. |
| 4 | `slotPoint3` | `integer` | — | Point defining the location on the acoustic slot. Entry 3. |
| 5 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 6 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 7 | `slotCount` | `integer` | — | Number of slot entries. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.

**Example record**

~~~text
AcousticSlot3;203;22;32;33
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 203`, `slotPoint1 = 22`, `slotPoint2 = 32`, `slotPoint3 = 33`.

## AcousticSlot4

A four-point slot element of the acoustic cavity analysis (an evenly spaced radial slot that solves the wave equation in two dimensions).

**Record format and fields**

`AcousticSlot4;id;slotPoint1;slotPoint2;slotPoint3;slotPoint4;density;bulkModulus;slotCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `slotPoint1` | `integer` | — | Point defining the location on the acoustic slot. Entry 1. |
| 3 | `slotPoint2` | `integer` | — | Point defining the location on the acoustic slot. Entry 2. |
| 4 | `slotPoint3` | `integer` | — | Point defining the location on the acoustic slot. Entry 3. |
| 5 | `slotPoint4` | `integer` | — | Point defining the location on the acoustic slot. Entry 4. |
| 6 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 7 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 8 | `slotCount` | `integer` | — | Number of slot entries. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.

**Example record**

~~~text
AcousticSlot4;201;21;31;32;22
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 201`, `slotPoint1 = 21`, `slotPoint2 = 31`, `slotPoint3 = 32`.

## AxisymQuad

An axisymmetric quadrilateral element with four corners, up to four edge points and an optional centre point.

**Record format and fields**

`AxisymQuad;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;materialAngle;matFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. Alternative to `matFrameId`. |
| 13 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
AxisymQuad;1;1;1;2;5;4
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_axisymmetric_cohesive.oos)

Reading the example gives `id = 1`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [PlanePropNonlinear](properties.md#planepropnonlinear) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 5`, `node4 = 4`.

## AxisymQuad4

A four-node axisymmetric quadrilateral ring element.

**Record format and fields**

`AxisymQuad4;id;propId;node1;node2;node3;node4;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the four grid points must all be different.

**Example record**

~~~text
AxisymQuad4;201;3;201;202;203;204
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 201`, `propId = 3`, `node1 = 201`, `node2 = 202`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 3`.
- [Node](nodes.md#node) via `node1 = 201`, `node2 = 202`, `node3 = 203`, `node4 = 204`.

## AxisymQuad8

An axisymmetric quadrilateral ring element with four corners and up to four edge points.

**Record format and fields**

`AxisymQuad8;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
AxisymQuad8;202;3;205;206;207;208;209;210;211;212;0.
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 202`, `propId = 3`, `node1 = 205`, `node2 = 206`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 3`.
- [Node](nodes.md#node) via `node1 = 205`, `node2 = 206`, `node3 = 207`, `node4 = 208`, `node5 = 209`, `node6 = 210`, `node7 = 211`, `node8 = 212`.

## AxisymTria

An axisymmetric triangular element with three corners and up to three edge points.

**Record format and fields**

`AxisymTria;id;propId;node1;node2;node3;node4;node5;node6;materialAngle;matFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. Alternative to `matFrameId`. |
| 10 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node4` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
AxisymTria;4;40;4;5;10
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol103_axisymmetric_harmonic.oos)

Reading the example gives `id = 4`, `propId = 40`, `node1 = 4`, `node2 = 5`.

**Referenced records in this example**

- [AxisymHarmonicProp](properties.md#axisymharmonicprop) via `propId = 40`.
- [Node](nodes.md#node) via `node1 = 4`, `node2 = 5`, `node3 = 10`.

## AxisymTria6

An axisymmetric triangular cross-section ring element with up to six grid points.

**Record format and fields**

`AxisymTria6;id;matId;node1;node2;node3;node4;node5;node6;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `node1` — the corner grid points `node1`, `node3` and `node5` must be positive integers.
- `node2` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
AxisymTria6;1;1;11;12;13;16;19;15
~~~

[Model containing this record](../../../validation/models/linear_loads/static_axisymmetric_ploadx1.oos)

Reading the example gives `id = 1`, `matId = 1`, `node1 = 11`, `node2 = 12`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.
- [Node](nodes.md#node) via `node1 = 11`, `node2 = 12`, `node3 = 13`, `node4 = 16`, `node5 = 19`, `node6 = 15`.

## Bar2

A simple beam element.

**Record format and fields**

`Bar2;id;propId;nodeA;nodeB;orientation1;orientationNode;orientation2;orientation3;offsetKind;pinFlagsA;pinFlagsB;offset1A;offset2A;offset3A;offset1B;offset2B;offset3B`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 5 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 6 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 7 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 8 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 9 | `offsetKind` | `text` | — | Selects the offset kind for Bar2. |
| 10 | `pinFlagsA` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 11 | `pinFlagsB` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 12 | `offset1A` | `real` | — | Component 1 of the offset vector at end A in the specified frame. |
| 13 | `offset2A` | `real` | — | Component 2 of the offset vector at end A in the specified frame. |
| 14 | `offset3A` | `real` | — | Component 3 of the offset vector at end A in the specified frame. |
| 15 | `offset1B` | `real` | — | Component 1 of the offset vector at end B in the specified frame. |
| 16 | `offset2B` | `real` | — | Component 2 of the offset vector at end B in the specified frame. |
| 17 | `offset3B` | `real` | — | Component 3 of the offset vector at end B in the specified frame. |

Accepted words: `OffsetsBasicGlobalGlobal`, `OffsetsBasicGlobalOrient`, `OffsetsBasicOrientGlobal`, `OffsetsBasicOrientOrient`, `OffsetsGlobalGlobalGlobal`, `OffsetsGlobalGlobalOrient`, `OffsetsGlobalOrientGlobal`, `OffsetsGlobalOrientOrient`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propId` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — the grid point IDs must be positive integers.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — `orientationNode` cannot be `nodeA` or `nodeB`.
- `pinFlagsA` — `pinFlagsA` must be digits 1 to 6 with no repeat.
- `pinFlagsB` — `pinFlagsB` must be digits 1 to 6 with no repeat.

**Example record**

~~~text
Bar2;1;1;1;2;0.;;0.;1.
~~~

[Model containing this record](../../../validation/models/aero_models/sol106_superelement_cload.oos)

Reading the example gives `id = 1`, `propId = 1`, `nodeA = 1`, `nodeB = 2`.

**Referenced records in this example**

- [BarProp](properties.md#barprop) via `propId = 1`.
- [Node](nodes.md#node) via `nodeA = 1`, `nodeB = 2`.

## Bar2Defaults

Supplies default property, orientation and offset conventions for [Bar2](elements.md#bar2) elements whose corresponding fields are blank.

**Record format and fields**

`Bar2Defaults;propId;orientation1;orientationNode;orientation2;orientation3;offsetKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `integer` | 0 | Identifier of the property from which the element obtains its section or constitutive data. |
| 2 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 3 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 4 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 5 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 6 | `offsetKind` | `text` | — | Selects the offset kind for Bar2Defaults. |

Accepted words: `OffsetsBasicGlobalGlobal`, `OffsetsBasicGlobalOrient`, `OffsetsBasicOrientGlobal`, `OffsetsBasicOrientOrient`, `OffsetsGlobalGlobalGlobal`, `OffsetsGlobalGlobalOrient`, `OffsetsGlobalOrientGlobal`, `OffsetsGlobalOrientOrient`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propId` — `propId` must be 0 (blank) or a property ID.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — give the orientation as a vector or as a grid point, not both.

**Example record**

~~~text
Bar2Defaults;11;0.;;0.;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `propId = 11`, `orientation1 = 0.`, `orientation2 = 0.`, `orientation3 = 1.`.

**Referenced records in this example**

- [BarProp](properties.md#barprop) via `propId = 11`.

## Bar2Stations

Extra stations along a bar element where stresses and forces are recovered.

**Record format and fields**

`Bar2Stations;id;stationScale;station1;stationCount;station2;station3;station4;station5;station6`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stationScale` | `text` | — | Scale applied at the specified station along the element. |
| 3 | `station1` | `real` | — | Position along the member or sampled path. Entry 1. Alternative to `stationCount`. |
| 4 | `stationCount` | `integer` | — | Number of station entries. Alternative to `station1`. |
| 5 | `station2` | `real` | — | Position along the member or sampled path. Entry 2. |
| 6 | `station3` | `real` | — | Position along the member or sampled path. Entry 3. |
| 7 | `station4` | `real` | — | Position along the member or sampled path. Entry 4. |
| 8 | `station5` | `real` | — | Position along the member or sampled path. Entry 5. |
| 9 | `station6` | `real` | — | Position along the member or sampled path. Entry 6. |

Accepted words: `ActualLength`, `FractionalLength`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `stationCount` — the stations are listed or equally spaced, not both.
- `station1` — the card needs at least one station.
- `station6` — the card lists at most six stations.
- `station1` — the stations must be greater than 0.

**Example record**

~~~text
Bar2Stations;1401;FractionalLength;0.25;;0.5;0.75
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1401`, `stationScale = FractionalLength`, `station1 = 0.25`, `station2 = 0.5`.

## BarArbitrarySectionProp

The arbitrary cross-section of a [Bar2](elements.md#bar2), described by the points of a set of [GeomPoint](nodes.md#geompoint) cards.

**Record format and fields**

`BarArbitrarySectionProp;id;matId;form;nonStructMass;description`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `form` | `text` | — | Selects the form for BarArbitrarySectionProp. |
| 4 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 5 | `description` | `text` | — | Free text describing this record or its output. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `ClosedProfile`, `Constant`, `Element`, `GeneralSection`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `OpenProfile`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`.

**Example record**

~~~text
BarArbitrarySectionProp;12;1;ClosedProfile;;outerPerimeter=120,thickness=1.0
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `id = 12`, `matId = 1`, `form = ClosedProfile`, `description = outerPerimeter=120,thickness=1.0`.

description contains comma-separated items: outerPerimeter=id, outerMesh=id, innerPerimeter(index)=id, branch(index)=id, thickness(index)=value, core(index)=propertyId, layer(index)=[propertyId,setId], nonStructMass=value. Thickness and core values can select points with [value,points=(startId,endId)].

## Beam2

A two-node beam carrying axial force, bending moments, torsion and transverse shear. Its property describes the cross-section and its orientation defines the local bending axes.

**Record format and fields**

`Beam2;id;propId;nodeA;nodeB;orientation1;orientationNode;orientation2;orientation3;offsetKind;pinFlagsA;pinFlagsB;offset1A;offset2A;offset3A;offset1B;offset2B;offset3B;warpingPointA;warpingPointB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 5 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 6 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 7 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 8 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 9 | `offsetKind` | `text` | — | Selects the offset kind for Beam2. |
| 10 | `pinFlagsA` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 11 | `pinFlagsB` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 12 | `offset1A` | `real` | — | Component 1 of the offset vector at end A in the specified frame. |
| 13 | `offset2A` | `real` | — | Component 2 of the offset vector at end A in the specified frame. |
| 14 | `offset3A` | `real` | — | Component 3 of the offset vector at end A in the specified frame. |
| 15 | `offset1B` | `real` | — | Component 1 of the offset vector at end B in the specified frame. |
| 16 | `offset2B` | `real` | — | Component 2 of the offset vector at end B in the specified frame. |
| 17 | `offset3B` | `real` | — | Component 3 of the offset vector at end B in the specified frame. |
| 18 | `warpingPointA` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 19 | `warpingPointB` | `integer` | 0 | Identifier addressing scalar or grid point data. |

Accepted words: `OffsetsBasicGlobalGlobal`, `OffsetsBasicGlobalOrient`, `OffsetsBasicOrientGlobal`, `OffsetsBasicOrientOrient`, `OffsetsGlobalGlobalGlobal`, `OffsetsGlobalGlobalOrient`, `OffsetsGlobalOrientGlobal`, `OffsetsGlobalOrientOrient`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — the grid point IDs must be positive integers.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — `orientationNode` cannot be `nodeA` or `nodeB`.
- `pinFlagsA` — `pinFlagsA` must be digits 1 to 6 with no repeat.
- `pinFlagsB` — `pinFlagsB` must be digits 1 to 6 with no repeat.
- `warpingPointA` — `warpingPointA` must be 0 or a point ID.
- `warpingPointB` — `warpingPointB` must be 0 or a point ID.

**Example record**

~~~text
Beam2;1;1;1;2;0.;;0.;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_beam_segment_contact.oos)

Reading the example gives `id = 1`, `propId = 1`, `nodeA = 1`, `nodeB = 2`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 1`, `nodeB = 2`.

## Beam2Defaults

Supplies default property, orientation and offset conventions for [Beam2](elements.md#beam2) elements whose corresponding fields are blank.

**Record format and fields**

`Beam2Defaults;propId;orientation1;orientationNode;orientation2;orientation3;offsetKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `integer` | 0 | Identifier of the property from which the element obtains its section or constitutive data. |
| 2 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 3 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 4 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 5 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 6 | `offsetKind` | `text` | — | Selects the offset kind for Beam2Defaults. |

Accepted words: `OffsetsBasicGlobalGlobal`, `OffsetsBasicGlobalOrient`, `OffsetsBasicOrientGlobal`, `OffsetsBasicOrientOrient`, `OffsetsGlobalGlobalGlobal`, `OffsetsGlobalGlobalOrient`, `OffsetsGlobalOrientGlobal`, `OffsetsGlobalOrientOrient`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propId` — `propId` must be 0 (blank) or a property ID.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — give the orientation as a vector or as a grid point, not both.

**Example record**

~~~text
Beam2Defaults;31;0.;;0.;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `propId = 31`, `orientation1 = 0.`, `orientation2 = 0.`, `orientation3 = 1.`.

## Beam3

A three-node beam element (ends A and B and a middle point C).

**Record format and fields**

`Beam3;id;propId;nodeA;nodeB;nodeC;orientationNode;orientation1;orientation2;orientation3;offset1A;offset2A;offset3A;offset1B;offset2B;offset3B;offset1C;offset2C;offset3C;twistA;twistB;twistC;warpingPointA;warpingPointB;warpingPointC`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 5 | `nodeC` | `integer` | 0 | Identifier addressing node data. |
| 6 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 7 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 8 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 9 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 10 | `offset1A` | `real` | — | Component 1 of the offset vector at end A in the specified frame. |
| 11 | `offset2A` | `real` | — | Component 2 of the offset vector at end A in the specified frame. |
| 12 | `offset3A` | `real` | — | Component 3 of the offset vector at end A in the specified frame. |
| 13 | `offset1B` | `real` | — | Component 1 of the offset vector at end B in the specified frame. |
| 14 | `offset2B` | `real` | — | Component 2 of the offset vector at end B in the specified frame. |
| 15 | `offset3B` | `real` | — | Component 3 of the offset vector at end B in the specified frame. |
| 16 | `offset1C` | `real` | — | Component 1 of the offset vector at end C in the specified frame. |
| 17 | `offset2C` | `real` | — | Component 2 of the offset vector at end C in the specified frame. |
| 18 | `offset3C` | `real` | — | Component 3 of the offset vector at end C in the specified frame. |
| 19 | `twistA` | `real` | — | Section twist at the labeled position A. |
| 20 | `twistB` | `real` | — | Section twist at the labeled position B. |
| 21 | `twistC` | `real` | — | Section twist at the labeled position C. |
| 22 | `warpingPointA` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 23 | `warpingPointB` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 24 | `warpingPointC` | `integer` | 0 | Identifier addressing scalar or grid point data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — `nodeA` and `nodeB` must be positive grid point IDs.
- `nodeC` — `nodeC` must be 0 (blank) or a grid point ID.
- `nodeB` — `nodeA`, `nodeB` and `nodeC` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — `orientationNode` cannot be `nodeA`, `nodeB` or `nodeC`.
- `warpingPointA` — `warpingPointA`, `warpingPointB` and `warpingPointC` must be 0 (blank) or point IDs.

**Example record**

~~~text
Beam3;3;3;5;6;7;;0.;0.;1.
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 3`, `propId = 3`, `nodeA = 5`, `nodeB = 6`.

**Referenced records in this example**

- [BeamProp3](properties.md#beamprop3) via `propId = 3`.
- [Node](nodes.md#node) via `nodeA = 5`, `nodeB = 6`, `nodeC = 7`.

## BeamArbitrarySectionProp

The arbitrary cross-section of a [Beam2](elements.md#beam2) (or, with a Core or a Layer, of a [Beam3](elements.md#beam3)), described by the points of a set of [GeomPoint](nodes.md#geompoint) cards.

**Record format and fields**

`BeamArbitrarySectionProp;id;matId;form;description`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `form` | `text` | — | Selects the form for BeamArbitrarySectionProp. |
| 4 | `description` | `text` | — | Free text describing this record or its output. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `ClosedProfile`, `Constant`, `Element`, `GeneralSection`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `OpenProfile`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`.

**Example record**

~~~text
BeamArbitrarySectionProp;51;1;GeneralSection;outerPerimeter=510
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `id = 51`, `matId = 1`, `form = GeneralSection`, `description = outerPerimeter=510`.

description uses the same exact item names as BarArbitrarySectionProp, restricted to the items supported by this section form.

## BeamPropNonlinear

The nonlinear extension of the [BeamProp](properties.md#beamprop) or [BeamShapeProp](properties.md#beamshapeprop) with the same property ID.

**Record format and fields**

`BeamPropNonlinear;id;matId;sectionIntegration;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionIntegration` | `text` | — | Integration convention for recovering the section response. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `TwoNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior2` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 2. |
| 2 | `integration2` | `text` | — | Selects the rule used to integrate the element or section response. Entry 2. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `Element`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `TwoNodeElems`.

**Example record**

~~~text
BeamPropNonlinear;301;;Smeared;TwoNodeElems;Beam;LinearCubic
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_property_extensions.oos)

Reading the example gives `id = 301`, `sectionIntegration = Smeared`.

## Bushing

A generalized spring-and-damper element.

**Record format and fields**

`Bushing;id;propId;nodeA;nodeB;orientationNode;orientation1;orientation2;orientation3;frameId;offsetFraction;offsetFrameId;offset1;offset2;offset3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 5 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 6 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 7 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 8 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 9 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 10 | `offsetFraction` | `real` | — | Offset expressed as a fraction of the associated reference dimension or range. |
| 11 | `offsetFrameId` | `integer` | — | Identifier addressing coordinate data. |
| 12 | `offset1` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 1. |
| 13 | `offset2` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 2. |
| 14 | `offset3` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 3. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — `nodeA` must be a positive grid point ID.
- `nodeB` — `nodeB` must be 0 (blank) or a grid point ID.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `frameId` — `frameId` must be blank or a coordinate system ID.
- `offsetFrameId` — `offsetFrameId` must be -1 or a coordinate system ID.

**Example record**

~~~text
Bushing;101;101;101;102;;0.;1.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id = 101`, `propId = 101`, `nodeA = 101`, `nodeB = 102`.

**Referenced records in this example**

- [BushProp](properties.md#bushprop) via `propId = 101`.
- [Node](nodes.md#node) via `nodeA = 101`, `nodeB = 102`.

## Bushing1D

A rod-type spring and damper between two grid points.

**Record format and fields**

`Bushing1D;id;propId;nodeA;nodeB;frameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 5 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — `nodeA` must be a positive grid point ID.
- `nodeB` — `nodeB` must be 0 (blank) or a grid point ID.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `frameId` — `frameId` must be blank or a coordinate system ID.

**Example record**

~~~text
Bushing1D;54;54;10;26
~~~

[Model containing this record](../../../validation/models/cuts_monitor_points/cuts_model.oos)

Reading the example gives `id = 54`, `propId = 54`, `nodeA = 10`, `nodeB = 26`.

## Bushing2D

Models an in-plane connection between the inner and outer grid points of a bearing or bushing.

**Record format and fields**

`Bushing2D;id;propId;nodeA;nodeB;frameId;plane`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | — | Grid point identifier at connectivity position A. |
| 4 | `nodeB` | `integer` | — | Grid point identifier at connectivity position B. |
| 5 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 6 | `plane` | `text` | — | Reference plane used for the geometric definition. |

Accepted words: `Constant`, `Element`, `PlaneXy`, `PlaneYz`, `PlaneZx`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `frameId` — the coordinate system ID `frameId` must not be negative.

**Example record**

~~~text
Bushing2D;1;21;1;2;0;PlaneXy
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/service_and_paa_cards.oos)

Reading the example gives `id = 1`, `propId = 21`, `nodeA = 1`, `nodeB = 2`.

## CohesiveAxisymQuad

A linear or quadratic axisymmetric cohesive interface element with four to eight nodes, used to simulate the onset and growth of a delamination between two axisymmetric bodies.

**Record format and fields**

`CohesiveAxisymQuad;id;propId;node1;node2;node3;node4;node5;node6;node7;node8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CohesiveAxisymQuad;3;5;4;5;8;7
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_axisymmetric_cohesive.oos)

Reading the example gives `id = 3`, `propId = 5`, `node1 = 4`, `node2 = 5`.

**Referenced records in this example**

- [CohesiveProp](elements.md#cohesiveprop) via `propId = 5`.

## CohesiveHexa

A linear or quadratic three-dimensional cohesive interface element with eight to twenty nodes, used to simulate the onset and growth of a delamination between two bodies.

**Record format and fields**

`CohesiveHexa;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15;node16;node17;node18;node19;node20`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node13` | `integer` | — | Grid point to which this entry applies. Entry 13. |
| 16 | `node14` | `integer` | — | Grid point to which this entry applies. Entry 14. |
| 17 | `node15` | `integer` | — | Grid point to which this entry applies. Entry 15. |
| 18 | `node16` | `integer` | — | Grid point to which this entry applies. Entry 16. |
| 19 | `node17` | `integer` | — | Grid point to which this entry applies. Entry 17. |
| 20 | `node18` | `integer` | — | Grid point to which this entry applies. Entry 18. |
| 21 | `node19` | `integer` | — | Grid point to which this entry applies. Entry 19. |
| 22 | `node20` | `integer` | — | Grid point to which this entry applies. Entry 20. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CohesiveHexa;102;5;105;106;107;108;109;110;111;112
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solid_cohesive.oos)

Reading the example gives `id = 102`, `propId = 5`, `node1 = 105`, `node2 = 106`.

**Referenced records in this example**

- [CohesiveProp](elements.md#cohesiveprop) via `propId = 5`.

## CohesiveMat

The material of the interface cohesive zone elements that simulate the onset and the growth of a delamination.

**Record format and fields**

`CohesiveMat;id;cohesiveModel;tableId;cohesiveEnergy;criticalOpening;maxOpening;shearNormalStressRatio;exponent;viscousDissipation;referenceDisplacementRate;compressionStiffening;shearNormalEnergyRatio;inPlaneStiffness;normalStiffness`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `cohesiveModel` | `integer` | — | A TableStress1 or TableStressTemperature of cohesive energy against temperature, 0 for none. |
| 3 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 4 | `cohesiveEnergy` | `real` | — | Energy associated with separation of the cohesive interface. |
| 5 | `criticalOpening` | `real` | — | Critical opening distance. |
| 6 | `maxOpening` | `real` | — | Maximum opening displacement. |
| 7 | `shearNormalStressRatio` | `real` | 1.0 | Relative measure of shear normal stress. |
| 8 | `exponent` | `real` | 1.0 | Power applied to the associated variable in the stated relation. |
| 9 | `viscousDissipation` | `real` | 0.0 | Factor of viscous energy dissipation. |
| 10 | `referenceDisplacementRate` | `real` | 0.0 | Reference rate of relative displacement, 0.0 computes it. |
| 11 | `compressionStiffening` | `real` | 1.0 | Stiffening factor in compression. |
| 12 | `shearNormalEnergyRatio` | `real` | 1.0 | Relative measure of shear normal energy. |
| 13 | `inPlaneStiffness` | `real` | 0.0 | Stiffness in the plane of the element (linear solutions). |
| 14 | `normalStiffness` | `real` | 0.0 | Stiffness normal to the plane of the element (linear solutions). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cohesiveModel` — `cohesiveModel` must be 1, 2, 3, -1 or -2.

**Example record**

~~~text
CohesiveMat;5;1;;0.5;0.002;0.02;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_axisymmetric_cohesive.oos)

Reading the example gives `id = 5`, `cohesiveModel = 1`, `cohesiveEnergy = 0.5`, `criticalOpening = 0.002`.

## CohesivePenta

A linear or quadratic three-dimensional cohesive interface element with six to fifteen nodes (a wedge), used to simulate the onset and growth of a delamination between two bodies.

**Record format and fields**

`CohesivePenta;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node13` | `integer` | — | Grid point to which this entry applies. Entry 13. |
| 16 | `node14` | `integer` | — | Grid point to which this entry applies. Entry 14. |
| 17 | `node15` | `integer` | — | Grid point to which this entry applies. Entry 15. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CohesivePenta;202;5;204;205;206;207;208;209
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solid_cohesive.oos)

Reading the example gives `id = 202`, `propId = 5`, `node1 = 204`, `node2 = 205`.

**Referenced records in this example**

- [CohesiveProp](elements.md#cohesiveprop) via `propId = 5`.

## CohesiveProp

The property of the interface cohesive zone elements ([CohesiveQuad](elements.md#cohesivequad), [CohesiveHexa](elements.md#cohesivehexa), [CohesivePenta](elements.md#cohesivepenta) and [CohesiveAxisymQuad](elements.md#cohesiveaxisymquad)), which simulate the onset and growth of a delamination.

**Record format and fields**

`CohesiveProp;id;matId;integration;thickness;output;tangentStiffness`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `integration` | `integer` | — | Selects the rule used to integrate the element or section response. |
| 4 | `thickness` | `real` | 1.0 | Through-thickness dimension, in model length units. |
| 5 | `output` | `text` | — | Controls the information recovered or written for this entry. |
| 6 | `tangentStiffness` | `integer` | 0 | Local slope of the force–displacement relation at the current state. |

Accepted words: `Constant`, `Element`, `GaussPoints`, `Nodes`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `integration` — `integration` must be 0 (Gauss) or 1 (Newton-Cotes/Lobatto).
- `tangentStiffness` — `tangentStiffness` must be 0 (secant matrix) or 1 (tangent matrix).

**Example record**

~~~text
CohesiveProp;5;5;0;1.;Nodes;0
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_plane_strain_cohesive.oos)

Reading the example gives `id = 5`, `matId = 5`, `integration = 0`, `thickness = 1.`.

## CohesiveQuad

A linear or quadratic planar cohesive interface element with four to eight nodes, used to simulate the onset and growth of a delamination between two bodies in plane strain or plane stress.

**Record format and fields**

`CohesiveQuad;id;propId;node1;node2;node3;node4;node5;node6;node7;node8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CohesiveQuad;3;5;4;5;8;7
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_plane_strain_cohesive.oos)

Reading the example gives `id = 3`, `propId = 5`, `node1 = 4`, `node2 = 5`.

**Referenced records in this example**

- [CohesiveProp](elements.md#cohesiveprop) via `propId = 5`.

## ConicalShellProp

The property of the conical shell elements ([ShellConical2](elements.md#shellconical2)).

**Record format and fields**

`ConicalShellProp;id;matId1;thickness1;matId2;inertia;matId3;thickness2;nonStructMass;fiberDistance1;fiberDistance2;<phiAngles>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId1` | `integer` | 0 | Identifier addressing material data. |
| 3 | `thickness1` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 1. |
| 4 | `matId2` | `integer` | 0 | Identifier addressing material data. |
| 5 | `inertia` | `real` | 0.0 | Moment of inertia per unit width. |
| 6 | `matId3` | `integer` | 0 | Identifier addressing material data. |
| 7 | `thickness2` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 2. |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 9 | `fiberDistance1` | `real` | — | Fiber distance 1 (length). |
| 10 | `fiberDistance2` | `real` | — | Fiber distance 2 (length). |

**Repeated group `phiAngles`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `phiAngle` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId1` — the material IDs must not be negative.
- `thickness1` — `matId1` and `thickness1` must both be given or both be zero or blank.
- `inertia` — `matId2` and `inertia` must both be given or both be zero or blank.
- `thickness2` — `matId3` and `thickness2` must both be given or both be zero or blank.
- `thickness1` — the thicknesses `thickness1` and `thickness2` must not be negative.
- `phiAngle` — the card has at most 14 azimuthal coordinates `phiAngle`.

**Example record**

~~~text
ConicalShellProp;1;1;2.;1;0.6667;1;1.6667;;1.;-1.;0.;90.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_free_modes.oos)

Reading the example gives `id = 1`, `matId1 = 1`, `thickness1 = 2.`, `matId2 = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId1 = 1`, `matId2 = 1`, `matId3 = 1`.

## ConnectorSearchControl

Values of the parameters of the connector search that apply to a group of connector elements ([Fastener](elements.md#fastener), [Seam](elements.md#seam), [Weld](elements.md#weld)) and override the ones of the [ConnectorSearchParams](elements.md#connectorsearchparams) card for them.

**Record format and fields**

`ConnectorSearchControl;elementSetId;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elementSetId` | `integer` | Required | Identifier selecting the element set record or set. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `number` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `ConnectorSearchParams`, `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterName1` — the card needs at least one parameter and its value.

**Example record**

~~~text
ConnectorSearchControl;71;ProjectionTolerance;0.05;MaxEndPointMoves;3;GeneratedDataPrint;1
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_connector_iterative.oos)

Reading the example gives `elementSetId = 71`.

## ConnectorSearchParams

Sets named search controls for finding the surfaces joined by [Fastener](elements.md#fastener), [Weld](elements.md#weld) and [Seam](elements.md#seam) elements.

**Record format and fields**

`ConnectorSearchParams;<globalParameters>;<keyed sections>`

This part of the record has no fixed fields.

**Repeated group `globalParameters`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `number` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

**Keyed sections in `connectorSections`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Fastener`**

**Repeated group `parameters`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sectionParameterName` | `text` | — | Text naming the section parameter. |
| 2 | `sectionParameterValue` | `number` | — | Value associated with the selected section parameter. |

**Section `Weld`**

**Repeated group `parameters`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sectionParameterName` | `text` | — | Text naming the section parameter. |
| 2 | `sectionParameterValue` | `number` | — | Value associated with the selected section parameter. |

**Section `Seam`**

**Repeated group `parameters`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sectionParameterName` | `text` | — | Text naming the section parameter. |
| 2 | `sectionParameterValue` | `number` | — | Value associated with the selected section parameter. |

Accepted words: `Constant`, `Element`, `Fastener`, `Seam`, `Table`, `Weld`.

Accepted parameter names: `DiagnosticTableUnit`, `GeneratedDataPrint`, `GeometryCheckLevel`, `MaxDiameterHalvings`, `MaxEndPointMoves`, `MaxProjectionDistance`, `MaxShellNormalAngle`, `MoveEndPointsToProjection`, `PatchDiameterFactor`, `PatchStiffnessFactor`, `ProjectionTolerance`, `ProjectionToleranceSwitches`, `SeamEndMaxNormalAngle`, `SeamEndMinEdgeAngle`, `StopAfterConnectivityCheck`, `WeldMass`.

**Example record**

~~~text
ConnectorSearchParams;3;MaxShellNormalAngle;20.;ProjectionTolerance;0.02;MaxEndPointMoves;2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_connector_iterative.oos)

## CrackTip2D

Represents a two-dimensional crack-tip element associated with [UserDefined8Attributes](elements.md#userdefined8attributes).

**Record format and fields**

`CrackTip2D;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15;node16;node17;node18`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node13` | `integer` | — | Grid point to which this entry applies. Entry 13. |
| 16 | `node14` | `integer` | — | Grid point to which this entry applies. Entry 14. |
| 17 | `node15` | `integer` | — | Grid point to which this entry applies. Entry 15. |
| 18 | `node16` | `integer` | — | Grid point to which this entry applies. Entry 16. |
| 19 | `node17` | `integer` | — | Grid point to which this entry applies. Entry 17. |
| 20 | `node18` | `integer` | — | Grid point to which this entry applies. Entry 18. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `propId` — the property ID must be a positive integer.

**Example record**

~~~text
CrackTip2D;10;1;1;2;3;4;5;6;7
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_crack_tip_elements.oos)

Reading the example gives `id = 10`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [CrackTipProp2D](elements.md#cracktipprop2d) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 3`, `node4 = 4`, `node5 = 5`, `node6 = 6`, `node7 = 7`.

## CrackTip3D

Represents a three-dimensional crack-tip element associated with [UserDefined9Attributes](elements.md#userdefined9attributes).

**Record format and fields**

`CrackTip3D;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15;node16;node17;node18;node19;node20;node21;node22;node23;node24;node25;node26;node27;node28;node29;node30;node31;node32;node33;node34;node35;node36;node37;node38;node39;node40;node41;node42;node43;node44;node45;node46;node47;node48;node49;node50;node51;node52;node53;node54;node55;node56;node57;node58;node59;node60;node61;node62;node63;node64`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node13` | `integer` | — | Grid point to which this entry applies. Entry 13. |
| 16 | `node14` | `integer` | — | Grid point to which this entry applies. Entry 14. |
| 17 | `node15` | `integer` | — | Grid point to which this entry applies. Entry 15. |
| 18 | `node16` | `integer` | — | Grid point to which this entry applies. Entry 16. |
| 19 | `node17` | `integer` | — | Grid point to which this entry applies. Entry 17. |
| 20 | `node18` | `integer` | — | Grid point to which this entry applies. Entry 18. |
| 21 | `node19` | `integer` | — | Grid point to which this entry applies. Entry 19. |
| 22 | `node20` | `integer` | — | Grid point to which this entry applies. Entry 20. |
| 23 | `node21` | `integer` | — | Grid point to which this entry applies. Entry 21. |
| 24 | `node22` | `integer` | — | Grid point to which this entry applies. Entry 22. |
| 25 | `node23` | `integer` | — | Grid point to which this entry applies. Entry 23. |
| 26 | `node24` | `integer` | — | Grid point to which this entry applies. Entry 24. |
| 27 | `node25` | `integer` | — | Grid point to which this entry applies. Entry 25. |
| 28 | `node26` | `integer` | — | Grid point to which this entry applies. Entry 26. |
| 29 | `node27` | `integer` | — | Grid point to which this entry applies. Entry 27. |
| 30 | `node28` | `integer` | — | Grid point to which this entry applies. Entry 28. |
| 31 | `node29` | `integer` | — | Grid point to which this entry applies. Entry 29. |
| 32 | `node30` | `integer` | — | Grid point to which this entry applies. Entry 30. |
| 33 | `node31` | `integer` | — | Grid point to which this entry applies. Entry 31. |
| 34 | `node32` | `integer` | — | Grid point to which this entry applies. Entry 32. |
| 35 | `node33` | `integer` | — | Grid point to which this entry applies. Entry 33. |
| 36 | `node34` | `integer` | — | Grid point to which this entry applies. Entry 34. |
| 37 | `node35` | `integer` | — | Grid point to which this entry applies. Entry 35. |
| 38 | `node36` | `integer` | — | Grid point to which this entry applies. Entry 36. |
| 39 | `node37` | `integer` | — | Grid point to which this entry applies. Entry 37. |
| 40 | `node38` | `integer` | — | Grid point to which this entry applies. Entry 38. |
| 41 | `node39` | `integer` | — | Grid point to which this entry applies. Entry 39. |
| 42 | `node40` | `integer` | — | Grid point to which this entry applies. Entry 40. |
| 43 | `node41` | `integer` | — | Grid point to which this entry applies. Entry 41. |
| 44 | `node42` | `integer` | — | Grid point to which this entry applies. Entry 42. |
| 45 | `node43` | `integer` | — | Grid point to which this entry applies. Entry 43. |
| 46 | `node44` | `integer` | — | Grid point to which this entry applies. Entry 44. |
| 47 | `node45` | `integer` | — | Grid point to which this entry applies. Entry 45. |
| 48 | `node46` | `integer` | — | Grid point to which this entry applies. Entry 46. |
| 49 | `node47` | `integer` | — | Grid point to which this entry applies. Entry 47. |
| 50 | `node48` | `integer` | — | Grid point to which this entry applies. Entry 48. |
| 51 | `node49` | `integer` | — | Grid point to which this entry applies. Entry 49. |
| 52 | `node50` | `integer` | — | Grid point to which this entry applies. Entry 50. |
| 53 | `node51` | `integer` | — | Grid point to which this entry applies. Entry 51. |
| 54 | `node52` | `integer` | — | Grid point to which this entry applies. Entry 52. |
| 55 | `node53` | `integer` | — | Grid point to which this entry applies. Entry 53. |
| 56 | `node54` | `integer` | — | Grid point to which this entry applies. Entry 54. |
| 57 | `node55` | `integer` | — | Grid point to which this entry applies. Entry 55. |
| 58 | `node56` | `integer` | — | Grid point to which this entry applies. Entry 56. |
| 59 | `node57` | `integer` | — | Grid point to which this entry applies. Entry 57. |
| 60 | `node58` | `integer` | — | Grid point to which this entry applies. Entry 58. |
| 61 | `node59` | `integer` | — | Grid point to which this entry applies. Entry 59. |
| 62 | `node60` | `integer` | — | Grid point to which this entry applies. Entry 60. |
| 63 | `node61` | `integer` | — | Grid point to which this entry applies. Entry 61. |
| 64 | `node62` | `integer` | — | Grid point to which this entry applies. Entry 62. |
| 65 | `node63` | `integer` | — | Grid point to which this entry applies. Entry 63. |
| 66 | `node64` | `integer` | — | Grid point to which this entry applies. Entry 64. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `propId` — the property ID must be a positive integer.

**Example record**

~~~text
CrackTip3D;20;2;101;102;103;104;105;106;107;;;;;;;;;;;;119;120;121;122;123;124;125
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_crack_tip_elements.oos)

Reading the example gives `id = 20`, `propId = 2`, `node1 = 101`, `node2 = 102`.

**Referenced records in this example**

- [CrackTipProp3D](elements.md#cracktipprop3d) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 101`, `node2 = 102`, `node3 = 103`, `node4 = 104`, `node5 = 105`, `node6 = 106`, `node7 = 107`, `node19 = 119`, `node20 = 120`, `node21 = 121`, `node22 = 122`, `node23 = 123`, `node24 = 124`, `node25 = 125`.

## CrackTipProp2D

The property of a [CrackTip2D](elements.md#cracktip2d) crack tip element.

**Record format and fields**

`CrackTipProp2D;id;matId;thickness;planeCondition;nonStructMass;gammaCoefficient;phiAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness` | `real` | Required | Through-thickness dimension, in model length units. |
| 4 | `planeCondition` | `integer` | — | Selects the in-plane kinematic or stress assumption. |
| 5 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 6 | `gammaCoefficient` | `real` | — | Coefficient in the relation for gamma. |
| 7 | `phiAngle` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `planeCondition` — `planeCondition` must be 0 (plane strain) or 1 (plane stress).

**Example record**

~~~text
CrackTipProp2D;1;1;1.;0
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_crack_tip_elements.oos)

Reading the example gives `id = 1`, `matId = 1`, `thickness = 1.`, `planeCondition = 0`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## CrackTipProp3D

The property of a [CrackTip3D](elements.md#cracktip3d) crack tip element.

**Record format and fields**

`CrackTipProp3D;id;matId;gammaCoefficient;phiAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `gammaCoefficient` | `real` | — | Coefficient in the relation for gamma. |
| 4 | `phiAngle` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CrackTipProp3D;2;1
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_crack_tip_elements.oos)

Reading the example gives `id = 2`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## CurvedBeam2

A curved beam, curved pipe or elbow element between two grid points.

**Record format and fields**

`CurvedBeam2;id;propId;nodeA;nodeB;orientationNode;orientation1;orientation2;orientation3;geometryOption`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 5 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 6 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 7 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 8 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 9 | `geometryOption` | `integer` | Required | Selects the geometry option for CurvedBeam2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — the grid point IDs must be positive integers.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `orientationNode` — `orientationNode` cannot be `nodeA` or `nodeB`.
- `geometryOption` — `geometryOption` must be an integer from 1 to 4.

**Example record**

~~~text
CurvedBeam2;10;4;11;12;;0.;1.;0.;1
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 10`, `propId = 4`, `nodeA = 11`, `nodeB = 12`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 11`, `nodeB = 12`.

## DamperDofInline

A scalar damper that holds its own damping (no property).

**Record format and fields**

`DamperDofInline;id;damping;node1;components1;node2;components2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `damping` | `real` | Required | Dissipative coefficient of the selected connection, material or response law. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
DamperDofInline;55;0.5;15;3;23;3
~~~

[Model containing this record](../../../validation/models/cuts_monitor_points/cuts_frequency_complex.oos)

Reading the example gives `id = 55`, `damping = 0.5`, `node1 = 15`, `components1 = 3`.

## DamperDofInlineExplicit

The scalar damper that holds its own damping (no property), with the coordinate system its direction is given in.

**Record format and fields**

`DamperDofInlineExplicit;id;damping;node1;components1;node2;components2;frameId;follow`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `damping` | `real` | Required | Dissipative coefficient of the selected connection, material or response law. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `follow` | `text` | — | Specifies whether the direction or attachment follows the changing configuration. |

Accepted words: `Constant`, `CoordinateFrame`, `Element`, `Follow`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the point ID `node1` must not be negative.
- `components1` — `components1` must be 0 or a list of the digits 1 to 6, each at most once.
- `node2` — the point ID `node2` must not be negative.
- `components2` — `components2` must be 0 or a list of the digits 1 to 6, each at most once.
- `frameId` — the coordinate system ID must not be negative.

**Example record**

~~~text
DamperDofInlineExplicit;4003;0.005;3012;3
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4003`, `damping = 0.005`, `node1 = 3012`, `components1 = 3`.

## DamperDofProperty

A scalar damper that refers to a [DamperProp](properties.md#damperprop) property.

**Record format and fields**

`DamperDofProperty;id;propId;node1;components1;node2;components2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
DamperDofProperty;102;12;102;1;101;1
~~~

[Model containing this record](../../../validation/models/linear_elements/frequency_dependent_freq.oos)

Reading the example gives `id = 102`, `propId = 12`, `node1 = 102`, `components1 = 1`.

## DamperDofPropertyExplicit

The scalar damper that names a property, with the coordinate system its direction is given in.

**Record format and fields**

`DamperDofPropertyExplicit;id;propId;node1;components1;node2;components2;frameId;follow`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `follow` | `text` | — | Specifies whether the direction or attachment follows the changing configuration. |

Accepted words: `CoordinateFrame`, `Follow`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point ID `node1` must not be negative.
- `components1` — `components1` must be 0 or a list of the digits 1 to 6, each at most once.
- `node2` — the point ID `node2` must not be negative.
- `components2` — `components2` must be 0 or a list of the digits 1 to 6, each at most once.
- `frameId` — the coordinate system ID must not be negative.

**Example record**

~~~text
DamperDofPropertyExplicit;4004;4104;3013;3;3023;3
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4004`, `propId = 4104`, `node1 = 3013`, `components1 = 3`.

## DamperScalarInline

A scalar damper between two scalar points, with its own damping (no property).

**Record format and fields**

`DamperScalarInline;id;damping;scalarPoint1;scalarPoint2;id2;damping2;scalarPoint3;scalarPoint4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | — | Identifier in the element namespace. |
| 2 | `damping` | `real` | — | Dissipative coefficient of the selected connection, material or response law. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 5 | `id2` | `integer` | — | Identifier at position 2 in the ordered DamperScalarInline data. |
| 6 | `damping2` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 2. |
| 7 | `scalarPoint3` | `integer` | 0 | Scalar point at position 3 in the ordered connection. |
| 8 | `scalarPoint4` | `integer` | 0 | Scalar point at position 4 in the ordered connection. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint1` — `scalarPoint1` and `scalarPoint2` cannot both be blank or zero.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
DamperScalarInline;1808;0.2;1804
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1808`, `damping = 0.2`, `scalarPoint1 = 1804`.

## DamperScalarProperty

A scalar damper between two scalar points, with a [DamperProp](properties.md#damperprop) property.

**Record format and fields**

`DamperScalarProperty;id;propId;scalarPoint1;scalarPoint2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
DamperScalarProperty;1807;187;1803;1804
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1807`, `propId = 187`, `scalarPoint1 = 1803`, `scalarPoint2 = 1804`.

## ElemGeneration

Defines how elements are generated from a field of grid points.

**Record format and fields**

`ElemGeneration;kind;firstElemId;propId;gridFieldId;direction;thicknessOption;lowElemId;highElemId;valueA;valueB;valueC;valueD`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for ElemGeneration. |
| 2 | `firstElemId` | `integer` | Required | Identifier selecting the first element record or set. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `gridFieldId` | `integer` | Required | Identifier selecting the grid field record or set. |
| 5 | `direction` | `any` | — | Orientation in which the specified quantity acts or is measured. |
| 6 | `thicknessOption` | `any` | — | Selects the thickness option for ElemGeneration. |
| 7 | `lowElemId` | `any` | — | Identifier selecting the low element record or set. |
| 8 | `highElemId` | `any` | — | Identifier selecting the high element record or set. |
| 9 | `valueA` | `any` | — | Specified value at the labeled position A. |
| 10 | `valueB` | `any` | — | Specified value at the labeled position B. |
| 11 | `valueC` | `any` | — | Specified value at the labeled position C. |
| 12 | `valueD` | `any` | — | Specified value at the labeled position D. |

Accepted words: `Constant`, `Element`, `Hexa20`, `Hexa8`, `Quad4`, `Quad8`, `Table`, `Tria3`, `Tria6`.

**Example record**

~~~text
ElemGeneration;Quad4;21;1;31
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `kind = Quad4`, `firstElemId = 21`, `propId = 1`, `gridFieldId = 31`.

## Fastener

A fastener between two surface patches.

**Record format and fields**

`Fastener;id;propId;kind;patchIdA;patchIdB;spotNode;nodeA;nodeB;locationX;locationY;locationZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `kind` | `text` | — | Selects the kind for Fastener. |
| 4 | `patchIdA` | `integer` | Required | Identifier of the patch on side A. |
| 5 | `patchIdB` | `integer` | Required | Identifier of the patch on side B. |
| 6 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 7 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 8 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 9 | `locationX` | `real` | — | X coordinate of the location. |
| 10 | `locationY` | `real` | — | Y coordinate of the location. |
| 11 | `locationZ` | `real` | — | Z coordinate of the location. |

Accepted words: `Elements`, `Property`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `kind` — `kind` must be Property or Elements.
- `patchIdA` — `patchIdA` and `patchIdB` must be positive integers.
- `spotNode` — `spotNode`, `nodeA` and `nodeB` must be 0 (blank) or grid point IDs.
- `locationX` — `locationX`, `locationY` and `locationZ` must be all given or all blank.

**Example record**

~~~text
Fastener;2001;1;Elements;1;101;951
~~~

[Model containing this record](../../../validation/models/fasteners/cfast_forms.oos)

Reading the example gives `id = 2001`, `propId = 1`, `kind = Elements`, `patchIdA = 1`.

**Referenced records in this example**

- [FastenerProp](properties.md#fastenerprop) via `propId = 1`.
- [Node](nodes.md#node) via `spotNode = 951`.

## Gap2

A gap or friction element between two grid points.

**Record format and fields**

`Gap2;id;propId;nodeA;nodeB;orientationNode;orientation1;orientation2;orientation3;frameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 5 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `orientation1`. |
| 6 | `orientation1` | `real` | — | First component of the vector defining the element orientation. Alternative to `orientationNode`. |
| 7 | `orientation2` | `real` | 0.0 | Second component of the vector defining the element orientation. |
| 8 | `orientation3` | `real` | 0.0 | Third component of the vector defining the element orientation. |
| 9 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `nodeA` — the grid point IDs must be positive integers.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `frameId` — `frameId` must be blank or a coordinate system ID.

**Example record**

~~~text
Gap2;5;5;9;10;;0.;1.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 5`, `propId = 5`, `nodeA = 9`, `nodeB = 10`.

**Referenced records in this example**

- [GapProp](properties.md#gapprop) via `propId = 5`.
- [Node](nodes.md#node) via `nodeA = 9`, `nodeB = 10`.

## GeneralMatrix

Defines an element by a stiffness or flexibility matrix over an ordered set of independent degrees of freedom. A separate matrix can relate a dependent set to them.

**Record format and fields**

`GeneralMatrix;id;<independentDofs>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |

**Repeated group `independentDofs`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentPoint` | `integer` | — | Point associated with the independent degree of freedom. |
| 2 | `independentComponent` | `integer` | — | Degree of freedom contributing to the dependent motion. |

**Keyed sections in `parts`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DependentDofs`**

**Repeated group `dependentDofs`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentPoint` | `integer` | — | Point associated with the dependent degree of freedom. |
| 2 | `dependentComponent` | `integer` | — | Degree of freedom to be recovered from the independent motions. |

**Section `Stiffness`**

**Repeated group `stiffnessMatrix`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffness` | `real` | — | One term in the lower triangle of the stiffness matrix. Terms are ordered down each column. |

**Section `Flexibility`**

**Repeated group `flexibilityMatrix`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffness` | `real` | — | One term in the lower triangle of the stiffness matrix. Terms are ordered down each column. |

**Section `Dependency`**

**Repeated group `dependencyMatrix`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependencyMatrix` | `real` | — | Coefficient relating the independent set to the dependent set. This matrix is entered by rows. |

Accepted words: `Dependency`, `DependentDofs`, `Flexibility`, `Stiffness`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `independentPoint` — `independentPoint` must be a point ID and `independentComponent` a component from 0 to 6.
- `dependentPoint` — `dependentPoint` must be a point ID and `dependentComponent` a component from 0 to 6.

**Example record**

~~~text
GeneralMatrix;103;3;102;1;102;2;102;3;DependentDofs;6;101;1;101;2;101;3;101;4;101;5;101;6;Stiffness;6;1.E+3;0.;0.;2.E+3;0.;3.E+3
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 103`.

## HeatCapacity2

A damper (heat capacity, for heat transfer analysis) between two points, with a [HeatCapacityProp5](properties.md#heatcapacityprop5) property.

**Record format and fields**

`HeatCapacity2;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `node2` — the two points must be different.

**Example record**

~~~text
HeatCapacity2;202;2;2
~~~

[Model containing this record](../../../validation/models/linear_elements/heat_capacity_transient.oos)

Reading the example gives `id = 202`, `propId = 2`, `node1 = 2`.

**Referenced records in this example**

- [HeatCapacityProp5](properties.md#heatcapacityprop5) via `propId = 2`.

## LineInterface

An interface ties at least two geometric boundary curves together.

**Record format and fields**

`LineInterface;id;kind;boundaryList`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for LineInterface. |
| 3 | `boundaryList` | `text` | — | Identifier addressing geometric boundary data. Written as one text field. |

Accepted words: `Constant`, `Element`, `Linear`, `NodeList`, `Quadratic`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `boundaryList` — the card needs at least two boundaries in its `boundaryList`.

**Example record**

~~~text
LineInterface;431;NodeList;boundaries=(1,2)
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `id = 431`, `kind = NodeList`, `boundaryList = boundaries=(1,2)`.

boundaryList is boundaries=(id, id(Linear), id(Quadratic), ...). A bare ID uses Linear interpolation; the sign identifies an independent boundary. All names use exact case.

## MassDofInline

A scalar mass element that holds its own mass value (no property).

**Record format and fields**

`MassDofInline;id;mass;node1;components1;node2;components2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `mass` | `real` | Required | Inertial mass associated with the selected component or body. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
MassDofInline;504;0.004;503;5
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 504`, `mass = 0.004`, `node1 = 503`, `components1 = 5`.

## MassDofProperty

A scalar mass element that refers to a [MassProp](properties.md#massprop) property.

**Record format and fields**

`MassDofProperty;id;propId;node1;components1;node2;components2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
MassDofProperty;502;8;503;5
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 502`, `propId = 8`, `node1 = 503`, `components1 = 5`.

## MassScalarInline

A scalar mass element between two scalar points, with its own mass value (no property).

**Record format and fields**

`MassScalarInline;id;mass;scalarPoint1;scalarPoint2;id2;mass2;scalarPoint3;scalarPoint4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | — | Identifier in the element namespace. |
| 2 | `mass` | `real` | — | Inertial mass associated with the selected component or body. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 5 | `id2` | `integer` | — | Identifier at position 2 in the ordered MassScalarInline data. |
| 6 | `mass2` | `real` | — | Inertial mass associated with the selected component or body. Entry 2. |
| 7 | `scalarPoint3` | `integer` | 0 | Scalar point at position 3 in the ordered connection. |
| 8 | `scalarPoint4` | `integer` | 0 | Scalar point at position 4 in the ordered connection. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint1` — `scalarPoint1` and `scalarPoint2` cannot both be blank or zero.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
MassScalarInline;1812;0.001;1803
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1812`, `mass = 0.001`, `scalarPoint1 = 1803`.

## MassScalarProperty

A scalar mass element between two scalar points, with a [MassProp](properties.md#massprop) property.

**Record format and fields**

`MassScalarProperty;id;propId;scalarPoint1;scalarPoint2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
MassScalarProperty;202;22;201;202
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 202`, `propId = 22`, `scalarPoint1 = 201`, `scalarPoint2 = 202`.

## PlaneStrainQuad

A fully nonlinear plane strain quadrilateral element ([PlanePropNonlinear](properties.md#planepropnonlinear) or [PlaneCompProp](properties.md#planecompprop) property) with four corners, up to four edge points and an optional centre point.

**Record format and fields**

`PlaneStrainQuad;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;materialAngle;matFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. Alternative to `matFrameId`. |
| 13 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
PlaneStrainQuad;20;20;21;22;23;24;25;26;27;28;29
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_plane_strain_cohesive.oos)

Reading the example gives `id = 20`, `propId = 20`, `node1 = 21`, `node2 = 22`.

**Referenced records in this example**

- [PlanePropNonlinear](properties.md#planepropnonlinear) via `propId = 20`.
- [Node](nodes.md#node) via `node1 = 21`, `node2 = 22`, `node3 = 23`, `node4 = 24`, `node5 = 25`, `node6 = 26`, `node7 = 27`, `node8 = 28`, `node9 = 29`.

## PlaneStrainQuad4

A four-node plane strain element.

**Record format and fields**

`PlaneStrainQuad4;id;propId;node1;node2;node3;node4;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the four grid points must all be different.

**Example record**

~~~text
PlaneStrainQuad4;2;1;4;5;6;7;10.
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 2`, `propId = 1`, `node1 = 4`, `node2 = 5`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 4`, `node2 = 5`, `node3 = 6`, `node4 = 7`.

## PlaneStrainQuad8

A plane strain quadrilateral with four corners and up to four edge points.

**Record format and fields**

`PlaneStrainQuad8;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 1 after the 4 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 2 after the 4 corners. |
| 9 | `node7` | `integer` | — | Additional grid point at edge position 3 after the 4 corners. |
| 10 | `node8` | `integer` | — | Additional grid point at edge position 4 after the 4 corners. |
| 11 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
PlaneStrainQuad8;4;1;14;15;16;17;18;19;20;21;5.
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 4`, `propId = 1`, `node1 = 14`, `node2 = 15`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 14`, `node2 = 15`, `node3 = 16`, `node4 = 17`, `node5 = 18`, `node6 = 19`, `node7 = 20`, `node8 = 21`.

## PlaneStrainTria3

A three-node plane strain element.

**Record format and fields**

`PlaneStrainTria3;id;propId;node1;node2;node3;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.

**Example record**

~~~text
PlaneStrainTria3;1;1;1;2;3
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 1`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 3`.

## PlaneStrainTria6

A plane strain triangle with three corners and up to three edge points.

**Record format and fields**

`PlaneStrainTria6;id;propId;node1;node2;node3;node4;node5;node6;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Additional grid point at edge position 1 after the 3 corners. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 2 after the 3 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 3 after the 3 corners. |
| 9 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node4` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
PlaneStrainTria6;3;1;8;9;10;11;12;13
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 3`, `propId = 1`, `node1 = 8`, `node2 = 9`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 8`, `node2 = 9`, `node3 = 10`, `node4 = 11`, `node5 = 12`, `node6 = 13`.

## PlaneStressQuad4

A four-node plane stress element.

**Record format and fields**

`PlaneStressQuad4;id;propId;node1;node2;node3;node4;materialAngle;thicknessFlag;thickness1;thickness2;thickness3;thickness4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |
| 8 | `thicknessFlag` | `integer` | 0 | Selects the thickness flag for PlaneStressQuad4. |
| 9 | `thickness1` | `real` | — | Through-thickness dimension, in model length units. Entry 1. |
| 10 | `thickness2` | `real` | — | Through-thickness dimension, in model length units. Entry 2. |
| 11 | `thickness3` | `real` | — | Through-thickness dimension, in model length units. Entry 3. |
| 12 | `thickness4` | `real` | — | Through-thickness dimension, in model length units. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the four grid points must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
PlaneStressQuad4;102;2;104;105;106;107;10.
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 102`, `propId = 2`, `node1 = 104`, `node2 = 105`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 104`, `node2 = 105`, `node3 = 106`, `node4 = 107`.

## PlaneStressQuad8

A plane stress quadrilateral with four corners and up to four edge points.

**Record format and fields**

`PlaneStressQuad8;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 1 after the 4 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 2 after the 4 corners. |
| 9 | `node7` | `integer` | — | Additional grid point at edge position 3 after the 4 corners. |
| 10 | `node8` | `integer` | — | Additional grid point at edge position 4 after the 4 corners. |
| 11 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
PlaneStressQuad8;104;2;114;115;116;117;118;119;120;121
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 104`, `propId = 2`, `node1 = 114`, `node2 = 115`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 114`, `node2 = 115`, `node3 = 116`, `node4 = 117`, `node5 = 118`, `node6 = 119`, `node7 = 120`, `node8 = 121`.

## PlaneStressTria3

A three-node plane stress element.

**Record format and fields**

`PlaneStressTria3;id;propId;node1;node2;node3;materialAngle;thicknessFlag;thickness1;thickness2;thickness3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |
| 7 | `thicknessFlag` | `integer` | 0 | Selects the thickness flag for PlaneStressTria3. |
| 8 | `thickness1` | `real` | — | Through-thickness dimension, in model length units. Entry 1. |
| 9 | `thickness2` | `real` | — | Through-thickness dimension, in model length units. Entry 2. |
| 10 | `thickness3` | `real` | — | Through-thickness dimension, in model length units. Entry 3. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
PlaneStressTria3;101;2;101;102;103;0.;1;1.;1.;0.75
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 101`, `propId = 2`, `node1 = 101`, `node2 = 102`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 101`, `node2 = 102`, `node3 = 103`.

## PlaneStressTria6

A plane stress triangle with three corners and up to three edge points.

**Record format and fields**

`PlaneStressTria6;id;propId;node1;node2;node3;node4;node5;node6;materialAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Additional grid point at edge position 1 after the 3 corners. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 2 after the 3 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 3 after the 3 corners. |
| 9 | `materialAngle` | `real` | 0.0 | Angle defining the material orientation relative to the reference element axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node4` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
PlaneStressTria6;103;2;108;109;110;111;112;113
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 103`, `propId = 2`, `node1 = 108`, `node2 = 109`.

**Referenced records in this example**

- [PlaneProp](properties.md#planeprop) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 108`, `node2 = 109`, `node3 = 110`, `node4 = 111`, `node5 = 112`, `node6 = 113`.

## PlotLine2

A dummy line element that is only drawn on plots.

**Record format and fields**

`PlotLine2;id;node1;node2;id2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | — | Identifier in the namespace of this card type. |
| 2 | `node1` | `integer` | — | Identifier addressing node data. |
| 3 | `node2` | `integer` | — | Identifier addressing node data. |
| 4 | `id2` | `integer` | — | Identifier at position 2 in the ordered PlotLine2 data. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node2` — `node1` and `node2` must be different.

**Example record**

~~~text
PlotLine2;391;309;323
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 391`, `node1 = 309`, `node2 = 323`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 309`, `node2 = 323`.

## PlotQuad4

A dummy quadrilateral that is only drawn on plots.

**Record format and fields**

`PlotQuad4;id;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `node1` | `integer` | Required | Identifier addressing node data. |
| 3 | `node2` | `integer` | Required | Identifier addressing node data. |
| 4 | `node3` | `integer` | Required | Identifier addressing node data. |
| 5 | `node4` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node2` — the four grid points must be different: `node2` repeats `node1`.
- `node3` — the four grid points must be different: `node3` repeats another one.
- `node4` — the four grid points must be different: `node4` repeats another one.

**Example record**

~~~text
PlotQuad4;12;2;3;6;5
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `id = 12`, `node1 = 2`, `node2 = 3`, `node3 = 6`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 2`, `node2 = 3`, `node3 = 6`, `node4 = 5`.

## PlotSurface

Describes a surface mesh used for display, including structural or cavity boundaries.

**Record format and fields**

`PlotSurface;id;nodeId1;nodeId2;nodeId3;nodeId4;nodeId5;nodeId6;nodeId7;nodeId8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `nodeId1` | `integer` | — | Identifier addressing node data. |
| 3 | `nodeId2` | `integer` | — | Identifier of the grid point addressed by this record. Entry 2. |
| 4 | `nodeId3` | `integer` | — | Identifier of the grid point addressed by this record. Entry 3. |
| 5 | `nodeId4` | `integer` | — | Identifier of the grid point addressed by this record. Entry 4. |
| 6 | `nodeId5` | `integer` | — | Identifier of the grid point addressed by this record. Entry 5. |
| 7 | `nodeId6` | `integer` | — | Identifier of the grid point addressed by this record. Entry 6. |
| 8 | `nodeId7` | `integer` | — | Identifier of the grid point addressed by this record. Entry 7. |
| 9 | `nodeId8` | `integer` | — | Identifier of the grid point addressed by this record. Entry 8. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PlotSurface;392;301;303;309;307
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 392`, `nodeId1 = 301`, `nodeId2 = 303`, `nodeId3 = 309`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeId1 = 301`.

## PlotTria3

A dummy triangle that is only drawn on plots.

**Record format and fields**

`PlotTria3;id;node1;node2;node3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `node1` | `integer` | Required | Identifier addressing node data. |
| 3 | `node2` | `integer` | Required | Identifier addressing node data. |
| 4 | `node3` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node2` — the three grid points must be different: `node1` and `node2` are the same.
- `node3` — the three grid points must be different: `node3` repeats another one.

**Example record**

~~~text
PlotTria3;11;1;2;5
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `id = 11`, `node1 = 1`, `node2 = 2`, `node3 = 5`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 5`.

## PointMassInertia

A concentrated mass at a grid point, with its own offset and inertia.

**Record format and fields**

`PointMassInertia;id;node;frameId;mass;offset1;offset2;offset3;inertia11;inertia21;inertia22;inertia31;inertia32;inertia33`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `mass` | `real` | 0.0 | Inertial mass associated with the selected component or body. |
| 5 | `offset1` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 1. |
| 6 | `offset2` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 2. |
| 7 | `offset3` | `real` | — | Shift from the reference location or value in the convention of this entry. Entry 3. |
| 8 | `inertia11` | `real` | — | Component (1, 1) of the point mass inertia tensor (mass times length squared). |
| 9 | `inertia21` | `real` | — | Component (2, 1) of the point mass inertia tensor (mass times length squared). |
| 10 | `inertia22` | `real` | — | Component (2, 2) of the point mass inertia tensor (mass times length squared). |
| 11 | `inertia31` | `real` | — | Component (3, 1) of the point mass inertia tensor (mass times length squared). |
| 12 | `inertia32` | `real` | — | Component (3, 2) of the point mass inertia tensor (mass times length squared). |
| 13 | `inertia33` | `real` | — | Component (3, 3) of the point mass inertia tensor (mass times length squared). |

Designable field descriptors: mass, offset1, offset2, offset3, inertia11, inertia21, inertia22, inertia31, inertia32, inertia33.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `frameId` — `frameId` must be -1, 0 or a coordinate system ID.

**Example record**

~~~text
PointMassInertia;1;1;;0.001;;;;0.01;;0.01;;;0.01
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

Reading the example gives `id = 1`, `node = 1`, `mass = 0.001`, `inertia11 = 0.01`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 1`.

## PointMassMatrix

A concentrated mass at a grid point, given as a full 6 x 6 symmetric mass matrix.

**Record format and fields**

`PointMassMatrix;id;node;frameId;massTerm11;massTerm21;massTerm22;massTerm31;massTerm32;massTerm33;massTerm41;massTerm42;massTerm43;massTerm44;massTerm51;massTerm52;massTerm53;massTerm54;massTerm55;massTerm61;massTerm62;massTerm63;massTerm64;massTerm65;massTerm66`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `massTerm11` | `real` | 0.0 | Entry 11 of the mass term coefficients in the local component order. |
| 5 | `massTerm21` | `real` | 0.0 | Entry 21 of the mass term coefficients in the local component order. |
| 6 | `massTerm22` | `real` | 0.0 | Entry 22 of the mass term coefficients in the local component order. |
| 7 | `massTerm31` | `real` | 0.0 | Entry 31 of the mass term coefficients in the local component order. |
| 8 | `massTerm32` | `real` | 0.0 | Entry 32 of the mass term coefficients in the local component order. |
| 9 | `massTerm33` | `real` | 0.0 | Entry 33 of the mass term coefficients in the local component order. |
| 10 | `massTerm41` | `real` | 0.0 | Entry 41 of the mass term coefficients in the local component order. |
| 11 | `massTerm42` | `real` | 0.0 | Entry 42 of the mass term coefficients in the local component order. |
| 12 | `massTerm43` | `real` | 0.0 | Entry 43 of the mass term coefficients in the local component order. |
| 13 | `massTerm44` | `real` | 0.0 | Entry 44 of the mass term coefficients in the local component order. |
| 14 | `massTerm51` | `real` | 0.0 | Entry 51 of the mass term coefficients in the local component order. |
| 15 | `massTerm52` | `real` | 0.0 | Entry 52 of the mass term coefficients in the local component order. |
| 16 | `massTerm53` | `real` | 0.0 | Entry 53 of the mass term coefficients in the local component order. |
| 17 | `massTerm54` | `real` | 0.0 | Entry 54 of the mass term coefficients in the local component order. |
| 18 | `massTerm55` | `real` | 0.0 | Entry 55 of the mass term coefficients in the local component order. |
| 19 | `massTerm61` | `real` | 0.0 | Entry 61 of the mass term coefficients in the local component order. |
| 20 | `massTerm62` | `real` | 0.0 | Entry 62 of the mass term coefficients in the local component order. |
| 21 | `massTerm63` | `real` | 0.0 | Entry 63 of the mass term coefficients in the local component order. |
| 22 | `massTerm64` | `real` | 0.0 | Entry 64 of the mass term coefficients in the local component order. |
| 23 | `massTerm65` | `real` | 0.0 | Entry 65 of the mass term coefficients in the local component order. |
| 24 | `massTerm66` | `real` | 0.0 | Entry 66 of the mass term coefficients in the local component order. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `frameId` — `frameId` must be 0 or a coordinate system ID.

**Example record**

~~~text
PointMassMatrix;104;102;;0.001;0.;0.001;0.;0.;0.001;0.;0.;0.;1.;0.;0.;0.;0.;1.;0.;0.;0.;0.;0.;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 104`, `node = 102`, `massTerm11 = 0.001`, `massTerm21 = 0.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 102`.

## Rod2

A two-node line element for axial and torsional response. The rod property connects the element to its material and cross-section.

**Record format and fields**

`Rod2;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | First endpoint of the rod. The vector from node1 to node2 defines its local axial direction. |
| 4 | `node2` | `integer` | Required | Second endpoint of the rod. Its distance from node1 is the undeformed element length. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the two grid points must be different.

**Example record**

~~~text
Rod2;1;1;1;2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_arc_length_snap.oos)

Reading the example gives `id = 1`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [RodProp](properties.md#rodprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`.

## Rod2InlineSection

A rod element with its own area and torsional constant, no property entry.

**Record format and fields**

`Rod2InlineSection;id;node1;node2;matId;area;torsionConstant;torsionStressCoefficient;nonStructMass`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 3 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |
| 4 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 5 | `area` | `real` | 0.0 | Surface or cross-sectional measure, in squared model length units. |
| 6 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 7 | `torsionStressCoefficient` | `real` | 0.0 | Coefficient in the relation for torsion stress. |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the two grid points must be different.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
Rod2InlineSection;2;3;4;1;10.;5.
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 2`, `node1 = 3`, `node2 = 4`, `matId = 1`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 3`, `node2 = 4`.
- [IsoMat](materials.md#isomat) via `matId = 1`.

## Seam

A seam that connects two surface patches (shell elements).

**Record format and fields**

`Seam;id;propId;seamLine;patchKind;patchAStart;patchBStart;patchAEnd;patchBEnd;startNode;startX;endNode;startY;startZ;endX;endY;endZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `seamLine` | `text` | — | Line identifying the path of the seam connection. |
| 4 | `patchKind` | `text` | — | Selects the patch kind for Seam. |
| 5 | `patchAStart` | `integer` | Required | First entry defining the extent of patch A. |
| 6 | `patchBStart` | `integer` | 0 | First entry defining the extent of patch B. |
| 7 | `patchAEnd` | `integer` | 0 | Last entry defining the extent of patch A. |
| 8 | `patchBEnd` | `integer` | 0 | Last entry defining the extent of patch B. |
| 9 | `startNode` | `integer` | — | Grid point at the beginning of the path or directed edge. Alternative to `startX`. |
| 10 | `startX` | `real` | — | X coordinate of the start point. Alternative to `startNode`. |
| 11 | `endNode` | `integer` | — | Grid point at the end of the path or directed edge. Alternative to `startY`. |
| 12 | `startY` | `real` | — | Y coordinate of the start point. Alternative to `endNode`. |
| 13 | `startZ` | `real` | — | Z coordinate of the start point. |
| 14 | `endX` | `real` | — | X coordinate of the end point. |
| 15 | `endY` | `real` | — | Y coordinate of the end point. |
| 16 | `endZ` | `real` | — | Z coordinate of the end point. |

Accepted words: `Constant`, `Element`, `Elements`, `ShellProp`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `propId` — the property ID must be a positive integer.
- `patchAStart` — `patchAStart` is required and must be a positive integer.
- `patchBStart` — `patchBStart` must be a positive integer or blank.
- `patchAEnd` — `patchAEnd` must be a positive integer or blank.
- `patchBEnd` — `patchBEnd` must be a positive integer or blank.
- `startNode` — the alternate format gives coordinates, not the grid points `startNode` and `endNode`.
- `startNode` — `startNode` is required and must be a positive integer.
- `endNode` — `endNode` is required and must be a positive integer.
- `startX` — the format with the grid points `startNode` and `endNode` has no coordinates.

**Example record**

~~~text
Seam;331;33;;;31;32;;;;5.;;105.;1.;15.;105.;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `id = 331`, `propId = 33`, `patchAStart = 31`, `patchBStart = 32`.

**Referenced records in this example**

- [SeamProp](elements.md#seamprop) via `propId = 33`.

## SeamProp

The property of a [Seam](elements.md#seam) seam connection.

**Record format and fields**

`SeamProp;id;matId;kind;width;thickness;integration`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `kind` | `text` | — | Selects the kind for SeamProp. |
| 4 | `width` | `real` | Required | Transverse extent in model length units. |
| 5 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 6 | `integration` | `integer` | — | Selects the rule used to integrate the element or section response. |

Accepted words: `Constant`, `Element`, `Line`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `integration` — `integration` must be 0 or 2.

**Example record**

~~~text
SeamProp;33;1;;4.
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `id = 33`, `matId = 1`, `width = 4.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## ShearPanel4

A shear panel element with four corner grid points.

**Record format and fields**

`ShearPanel4;id;propId;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the four grid points must all be different.

**Example record**

~~~text
ShearPanel4;7;2;701;702;703;704
~~~

[Model containing this record](../../../validation/models/mass_geometry/quality_geomcheck.oos)

Reading the example gives `id = 7`, `propId = 2`, `node1 = 701`, `node2 = 702`.

**Referenced records in this example**

- [ShearPanelProp](properties.md#shearpanelprop) via `propId = 2`.
- [Node](nodes.md#node) via `node1 = 701`, `node2 = 702`, `node3 = 703`, `node4 = 704`.

## ShellAxisym

An axisymmetric thick shell line element with two end points and, optionally, a third point between them on the curve of the element.

**Record format and fields**

`ShellAxisym;id;propId;node1;node2;node3;offset`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `offset` | `real` | — | Shift from the reference location or value in the convention of this entry. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ShellAxisym;32;30;302;304;303
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_axisymmetric_cohesive.oos)

Reading the example gives `id = 32`, `propId = 30`, `node1 = 302`, `node2 = 304`.

**Referenced records in this example**

- [AxisymShellProp](properties.md#axisymshellprop) via `propId = 30`.

## ShellConical2

An axisymmetric conical shell element between two rings, with a [ConicalShellProp](elements.md#conicalshellprop) property.

**Record format and fields**

`ShellConical2;id;propId;ringIdA;ringIdB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `ringIdA` | `integer` | Required | Identifier addressing node data. |
| 4 | `ringIdB` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `ringIdA` — the ring IDs must be positive integers.
- `ringIdB` — `ringIdA` and `ringIdB` must be different.

**Example record**

~~~text
ShellConical2;1;1;1;2
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_free_modes.oos)

Reading the example gives `id = 1`, `propId = 1`, `ringIdA = 1`, `ringIdB = 2`.

**Referenced records in this example**

- [ConicalShellProp](elements.md#conicalshellprop) via `propId = 1`.
- [AxisymConeRing](nodes.md#axisymconering) via `ringIdA = 1`, `ringIdB = 2`.

## ShellQuad4

A four-node shell element.

**Record format and fields**

`ShellQuad4;id;propId;node1;node2;node3;node4;materialAngle;matFrameId;offset;thicknessFlag;cornerThickness1;cornerThickness2;cornerThickness3;cornerThickness4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Grid point at corner 4 of the element connectivity. |
| 7 | `materialAngle` | `real` | — | Rotation of the material direction relative to the element axes, in degrees. Alternative to `matFrameId`. |
| 8 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 9 | `offset` | `real` | 0.0 | Signed distance of the reference surface from the grid-point plane, along the element normal. |
| 10 | `thicknessFlag` | `integer` | 0 | Selects absolute corner thicknesses or factors of the property thickness. |
| 11 | `cornerThickness1` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 12 | `cornerThickness2` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 13 | `cornerThickness3` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 14 | `cornerThickness4` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |

Designable field descriptors: offset, cornerThickness1, cornerThickness2, cornerThickness3, cornerThickness4.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the four grid points must all be different.

**Example record**

~~~text
ShellQuad4;1;1;1;2;7;6
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_perforated_shell_sol111.oos)

Reading the example gives `id = 1`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [ShellProp](properties.md#shellprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 7`, `node4 = 6`.

## ShellQuad4Drilling

A four-node plate element with a drilling rotation.

**Record format and fields**

`ShellQuad4Drilling;id;propId;node1;node2;node3;node4;materialAngle;matFrameId;offset;thicknessFlag;cornerThickness1;cornerThickness2;cornerThickness3;cornerThickness4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. Alternative to `matFrameId`. |
| 8 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 9 | `offset` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. |
| 10 | `thicknessFlag` | `integer` | 0 | Selects the thickness flag for ShellQuad4Drilling. |
| 11 | `cornerThickness1` | `real` | — | Corner thickness 1 (length). |
| 12 | `cornerThickness2` | `real` | — | Corner thickness 2 (length). |
| 13 | `cornerThickness3` | `real` | — | Corner thickness 3 (length). |
| 14 | `cornerThickness4` | `real` | — | Corner thickness 4 (length). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the four grid points must all be different.

**Example record**

~~~text
ShellQuad4Drilling;3;1;301;302;303;304
~~~

[Model containing this record](../../../validation/models/mass_geometry/quality_geomcheck.oos)

Reading the example gives `id = 3`, `propId = 1`, `node1 = 301`, `node2 = 302`.

**Referenced records in this example**

- [ShellProp](properties.md#shellprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 301`, `node2 = 302`, `node3 = 303`, `node4 = 304`.

## ShellQuad8

A curved quadrilateral shell element with four corners and up to four edge points.

**Record format and fields**

`ShellQuad8;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;cornerThickness1;cornerThickness2;cornerThickness3;cornerThickness4;materialAngle;matFrameId;offset;thicknessFlag`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 1 after the 4 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 2 after the 4 corners. |
| 9 | `node7` | `integer` | — | Additional grid point at edge position 3 after the 4 corners. |
| 10 | `node8` | `integer` | — | Additional grid point at edge position 4 after the 4 corners. |
| 11 | `cornerThickness1` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 12 | `cornerThickness2` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 13 | `cornerThickness3` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 14 | `cornerThickness4` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 15 | `materialAngle` | `real` | — | Rotation of the material direction relative to the element axes, in degrees. Alternative to `matFrameId`. |
| 16 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 17 | `offset` | `real` | 0.0 | Signed distance of the reference surface from the grid-point plane, along the element normal. |
| 18 | `thicknessFlag` | `integer` | 0 | Selects absolute corner thicknesses or factors of the property thickness. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
ShellQuad8;1;6;1;2;3;4;5;6;7;8
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_hyperelastic_plplane.oos)

Reading the example gives `id = 1`, `propId = 6`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [PlanePropNonlinear](properties.md#planepropnonlinear) via `propId = 6`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 3`, `node4 = 4`, `node5 = 5`, `node6 = 6`, `node7 = 7`, `node8 = 8`.

## ShellTria3

A three-node shell element.

**Record format and fields**

`ShellTria3;id;propId;node1;node2;node3;materialAngle;matFrameId;offset;thicknessFlag;cornerThickness1;cornerThickness2;cornerThickness3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `materialAngle` | `real` | — | Rotation of the material direction relative to the element axes, in degrees. Alternative to `matFrameId`. |
| 7 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 8 | `offset` | `real` | 0.0 | Signed distance of the reference surface from the grid-point plane, along the element normal. |
| 9 | `thicknessFlag` | `integer` | 0 | Selects absolute corner thicknesses or factors of the property thickness. |
| 10 | `cornerThickness1` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 11 | `cornerThickness2` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 12 | `cornerThickness3` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |

Designable field descriptors: offset, cornerThickness1, cornerThickness2, cornerThickness3.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
ShellTria3;201;1;201;202;205;30.
~~~

[Model containing this record](../../../validation/models/frames/frames_shell_model.oos)

Reading the example gives `id = 201`, `propId = 1`, `node1 = 201`, `node2 = 202`.

## ShellTria3Drilling

A three-node plate element with a drilling rotation.

**Record format and fields**

`ShellTria3Drilling;id;propId;node1;node2;node3;materialAngle;matFrameId;offset;thicknessFlag;cornerThickness1;cornerThickness2;cornerThickness3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. Alternative to `matFrameId`. |
| 7 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 8 | `offset` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. |
| 9 | `thicknessFlag` | `integer` | 0 | Selects the thickness flag for ShellTria3Drilling. |
| 10 | `cornerThickness1` | `real` | — | Corner thickness 1 (length). |
| 11 | `cornerThickness2` | `real` | — | Corner thickness 2 (length). |
| 12 | `cornerThickness3` | `real` | — | Corner thickness 3 (length). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
ShellTria3Drilling;401;1;401;402;405;30.
~~~

[Model containing this record](../../../validation/models/frames/frames_shell_model.oos)

Reading the example gives `id = 401`, `propId = 1`, `node1 = 401`, `node2 = 402`.

## ShellTria6

A curved triangular shell element with three corners and up to three edge points.

**Record format and fields**

`ShellTria6;id;propId;node1;node2;node3;node4;node5;node6;materialAngle;matFrameId;offset;cornerThickness1;cornerThickness2;cornerThickness3;thicknessFlag`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | — | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | — | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | — | Additional grid point at edge position 1 after the 3 corners. |
| 7 | `node5` | `integer` | — | Additional grid point at edge position 2 after the 3 corners. |
| 8 | `node6` | `integer` | — | Additional grid point at edge position 3 after the 3 corners. |
| 9 | `materialAngle` | `real` | — | Rotation of the material direction relative to the element axes, in degrees. Alternative to `matFrameId`. |
| 10 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. Alternative to `materialAngle`. |
| 11 | `offset` | `real` | 0.0 | Signed distance of the reference surface from the grid-point plane, along the element normal. |
| 12 | `cornerThickness1` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 13 | `cornerThickness2` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 14 | `cornerThickness3` | `real` | — | Thickness at this corner, or a multiplier of the property thickness according to the thickness flag. |
| 15 | `thicknessFlag` | `integer` | 0 | Selects absolute corner thicknesses or factors of the property thickness. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node4` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.
- `thicknessFlag` — `thicknessFlag` must be 0 or 1.

**Example record**

~~~text
ShellTria6;2;6;11;12;13;14;15;16
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_hyperelastic_plplane.oos)

Reading the example gives `id = 2`, `propId = 6`, `node1 = 11`, `node2 = 12`.

**Referenced records in this example**

- [PlanePropNonlinear](properties.md#planepropnonlinear) via `propId = 6`.
- [Node](nodes.md#node) via `node1 = 11`, `node2 = 12`, `node3 = 13`, `node4 = 14`, `node5 = 15`, `node6 = 16`.

## SolidHexa

A hexahedral solid with eight corner nodes and up to twelve additional edge nodes.

**Record format and fields**

`SolidHexa;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15;node16;node17;node18;node19;node20`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | Required | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | Required | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | Required | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | Required | Grid point at corner 5 of the element connectivity. |
| 8 | `node6` | `integer` | Required | Grid point at corner 6 of the element connectivity. |
| 9 | `node7` | `integer` | Required | Grid point at corner 7 of the element connectivity. |
| 10 | `node8` | `integer` | Required | Grid point at corner 8 of the element connectivity. |
| 11 | `node9` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 2. Blank or zero omits it. |
| 12 | `node10` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 3. Blank or zero omits it. |
| 13 | `node11` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 4. Blank or zero omits it. |
| 14 | `node12` | `integer` | 0 | Optional grid point on the edge joining corners 4 and 1. Blank or zero omits it. |
| 15 | `node13` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 5. Blank or zero omits it. |
| 16 | `node14` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 6. Blank or zero omits it. |
| 17 | `node15` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 7. Blank or zero omits it. |
| 18 | `node16` | `integer` | 0 | Optional grid point on the edge joining corners 4 and 8. Blank or zero omits it. |
| 19 | `node17` | `integer` | 0 | Optional grid point on the edge joining corners 5 and 6. Blank or zero omits it. |
| 20 | `node18` | `integer` | 0 | Optional grid point on the edge joining corners 6 and 7. Blank or zero omits it. |
| 21 | `node19` | `integer` | 0 | Optional grid point on the edge joining corners 7 and 8. Blank or zero omits it. |
| 22 | `node20` | `integer` | 0 | Optional grid point on the edge joining corners 8 and 5. Blank or zero omits it. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
SolidHexa;1;1;1;2;3;4;5;6;7;8
~~~

[Model containing this record](../../../validation/models/dynamics/explicit_initial_conditions_sol700.oos)

Reading the example gives `id = 1`, `propId = 1`, `node1 = 1`, `node2 = 2`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 1`.
- [Node](nodes.md#node) via `node1 = 1`, `node2 = 2`, `node3 = 3`, `node4 = 4`, `node5 = 5`, `node6 = 6`, `node7 = 7`, `node8 = 8`.

## SolidPenta

A prismatic solid with six corner nodes and up to nine additional edge nodes.

**Record format and fields**

`SolidPenta;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13;node14;node15`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | Required | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | Required | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | Required | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | Required | Grid point at corner 5 of the element connectivity. |
| 8 | `node6` | `integer` | Required | Grid point at corner 6 of the element connectivity. |
| 9 | `node7` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 2. Blank or zero omits it. |
| 10 | `node8` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 3. Blank or zero omits it. |
| 11 | `node9` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 1. Blank or zero omits it. |
| 12 | `node10` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 4. Blank or zero omits it. |
| 13 | `node11` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 5. Blank or zero omits it. |
| 14 | `node12` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 6. Blank or zero omits it. |
| 15 | `node13` | `integer` | 0 | Optional grid point on the edge joining corners 4 and 5. Blank or zero omits it. |
| 16 | `node14` | `integer` | 0 | Optional grid point on the edge joining corners 5 and 6. Blank or zero omits it. |
| 17 | `node15` | `integer` | 0 | Optional grid point on the edge joining corners 6 and 4. Blank or zero omits it. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
SolidPenta;71;7;21;22;23;24;25;26
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 71`, `propId = 7`, `node1 = 21`, `node2 = 22`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 7`.
- [Node](nodes.md#node) via `node1 = 21`, `node2 = 22`, `node3 = 23`, `node4 = 24`, `node5 = 25`, `node6 = 26`.

## SolidPropNonlinear

The nonlinear extension of the [SolidProp](properties.md#solidprop) with the same property ID, for the solid elements ([SolidHexa](elements.md#solidhexa), [SolidPenta](elements.md#solidpenta), [SolidPyramid](elements.md#solidpyramid) and [SolidTetra](elements.md#solidtetra)) that name the [SolidProp](properties.md#solidprop).

**Record format and fields**

`SolidPropNonlinear;id;matId;direction;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `direction` | `integer` | 1 | Orientation in which the specified quantity acts or is measured. |
| 4 | `analysisType` | `text` | — | Selects the analysis type for SolidPropNonlinear. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `FourNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior4` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 4. |
| 2 | `integration4` | `text` | — | Selects the rule used to integrate the element or section response. Entry 4. |
| 3 | `heatBehavior4` | `text` | — | Heat behavior setting for the element configuration identified by 4. |
| 4 | `heatIntegration4` | `text` | — | Heat integration setting for the element configuration identified by 4. |

**Section `FiveNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior5` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 5. |
| 2 | `integration5` | `text` | — | Selects the rule used to integrate the element or section response. Entry 5. |
| 3 | `heatBehavior5` | `text` | — | Heat behavior setting for the element configuration identified by 5. |
| 4 | `heatIntegration5` | `text` | — | Heat integration setting for the element configuration identified by 5. |

**Section `SixNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior6` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 6. |
| 2 | `integration6` | `text` | — | Selects the rule used to integrate the element or section response. Entry 6. |
| 3 | `heatBehavior6` | `text` | — | Heat behavior setting for the element configuration identified by 6. |
| 4 | `heatIntegration6` | `text` | — | Heat integration setting for the element configuration identified by 6. |

**Section `EightNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior8` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 8. |
| 2 | `integration8` | `text` | — | Selects the rule used to integrate the element or section response. Entry 8. |
| 3 | `heatBehavior8` | `text` | — | Heat behavior setting for the element configuration identified by 8. |
| 4 | `heatIntegration8` | `text` | — | Heat integration setting for the element configuration identified by 8. |

**Section `TenNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior10` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 10. |
| 2 | `integration10` | `text` | — | Selects the rule used to integrate the element or section response. Entry 10. |
| 3 | `heatBehavior10` | `text` | — | Heat behavior setting for the element configuration identified by 10. |
| 4 | `heatIntegration10` | `text` | — | Heat integration setting for the element configuration identified by 10. |

**Section `ThirteenNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior13` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 13. |
| 2 | `integration13` | `text` | — | Selects the rule used to integrate the element or section response. Entry 13. |
| 3 | `heatBehavior13` | `text` | — | Heat behavior setting for the element configuration identified by 13. |
| 4 | `heatIntegration13` | `text` | — | Heat integration setting for the element configuration identified by 13. |

**Section `FifteenNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior15` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 15. |
| 2 | `integration15` | `text` | — | Selects the rule used to integrate the element or section response. Entry 15. |
| 3 | `heatBehavior15` | `text` | — | Heat behavior setting for the element configuration identified by 15. |
| 4 | `heatIntegration15` | `text` | — | Heat integration setting for the element configuration identified by 15. |

**Section `TwentyNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior20` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 20. |
| 2 | `integration20` | `text` | — | Selects the rule used to integrate the element or section response. Entry 20. |
| 3 | `heatBehavior20` | `text` | — | Heat behavior setting for the element configuration identified by 20. |
| 4 | `heatIntegration20` | `text` | — | Heat integration setting for the element configuration identified by 20. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `EightNodeElems`, `Element`, `FifteenNodeElems`, `FiveNodeElems`, `FourNodeElems`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `SixNodeElems`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `TenNodeElems`, `ThirteenNodeElems`, `TwentyNodeElems`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `direction` — `direction` must be 1, 2 or 3.

**Example record**

~~~text
SolidPropNonlinear;1;1;;ImplicitStructural;EightNodeElems;Solid;Linear
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solids_initial_state.oos)

Reading the example gives `id = 1`, `matId = 1`, `analysisType = ImplicitStructural`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `id = 1`.

## SolidPyramid

A solid with four corners on a quadrilateral base, one apex and up to eight additional edge nodes.

**Record format and fields**

`SolidPyramid;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node13`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | Required | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | Required | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | Required | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | Required | Grid point at corner 5 of the element connectivity. |
| 8 | `node6` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 2. Blank or zero omits it. |
| 9 | `node7` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 3. Blank or zero omits it. |
| 10 | `node8` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 4. Blank or zero omits it. |
| 11 | `node9` | `integer` | 0 | Optional grid point on the edge joining corners 4 and 1. Blank or zero omits it. |
| 12 | `node10` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 5. Blank or zero omits it. |
| 13 | `node11` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 5. Blank or zero omits it. |
| 14 | `node12` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 5. Blank or zero omits it. |
| 15 | `node13` | `integer` | 0 | Optional grid point on the edge joining corners 4 and 5. Blank or zero omits it. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node6` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
SolidPyramid;401;7;401;402;403;404;405
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 401`, `propId = 7`, `node1 = 401`, `node2 = 402`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 7`.
- [Node](nodes.md#node) via `node1 = 401`, `node2 = 402`, `node3 = 403`, `node4 = 404`, `node5 = 405`.

## SolidTetra

A tetrahedral solid with four corner nodes and up to six additional nodes on its edges. The position of an edge-node ID in the record determines which edge it belongs to.

**Record format and fields**

`SolidTetra;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point at corner 1 of the element connectivity. |
| 4 | `node2` | `integer` | Required | Grid point at corner 2 of the element connectivity. |
| 5 | `node3` | `integer` | Required | Grid point at corner 3 of the element connectivity. |
| 6 | `node4` | `integer` | Required | Grid point at corner 4 of the element connectivity. |
| 7 | `node5` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 2. Blank or zero omits it. |
| 8 | `node6` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 3. Blank or zero omits it. |
| 9 | `node7` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 1. Blank or zero omits it. |
| 10 | `node8` | `integer` | 0 | Optional grid point on the edge joining corners 1 and 4. Blank or zero omits it. |
| 11 | `node9` | `integer` | 0 | Optional grid point on the edge joining corners 2 and 4. Blank or zero omits it. |
| 12 | `node10` | `integer` | 0 | Optional grid point on the edge joining corners 3 and 4. Blank or zero omits it. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the corner grid points must be positive integers.
- `node5` — the grid point IDs must not be negative.
- `node1` — the grid points of an element must all be different.

**Example record**

~~~text
SolidTetra;72;7;24;25;26;27
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 72`, `propId = 7`, `node1 = 24`, `node2 = 25`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 7`.
- [Node](nodes.md#node) via `node1 = 24`, `node2 = 25`, `node3 = 26`, `node4 = 27`.

## SpringDofInline

A scalar spring that holds its own stiffness (no property).

**Record format and fields**

`SpringDofInline;id;stiffness;node1;components1;node2;components2;structuralDamping;stressCoefficient`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `stiffness` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 8 | `stressCoefficient` | `real` | 0.0 | Coefficient used to recover stress from the element force or section response. |

Designable field descriptors: stiffness, structuralDamping, stressCoefficient.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
SpringDofInline;3;1.E+3;2;1;101;1
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/service_and_paa_cards.oos)

Reading the example gives `id = 3`, `stiffness = 1.E+3`, `node1 = 2`, `components1 = 1`.

## SpringDofInlineExplicit

The scalar spring that holds its own stiffness (no property), with the coordinate system its direction is given in.

**Record format and fields**

`SpringDofInlineExplicit;id;stiffness;node1;components1;node2;components2;frameId;follow`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `stiffness` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `follow` | `text` | — | Specifies whether the direction or attachment follows the changing configuration. |

Accepted words: `Constant`, `CoordinateFrame`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the point ID `node1` must not be negative.
- `components1` — `components1` must be 0 or a list of the digits 1 to 6, each at most once.
- `node2` — the point ID `node2` must not be negative.
- `components2` — `components2` must be 0 or a list of the digits 1 to 6, each at most once.
- `frameId` — the coordinate system ID must not be negative.

**Example record**

~~~text
SpringDofInlineExplicit;4001;50.;3012;3
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4001`, `stiffness = 50.`, `node1 = 3012`, `components1 = 3`.

## SpringDofProperty

A scalar spring that refers to a [SpringProp](properties.md#springprop) property.

**Record format and fields**

`SpringDofProperty;id;propId;node1;components1;node2;components2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point IDs must not be negative.
- `components1` — `components1` must be a component from 0 to 6.
- `components2` — `components2` must be a component from 0 to 6.

**Example record**

~~~text
SpringDofProperty;201;201;201;1
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id = 201`, `propId = 201`, `node1 = 201`, `components1 = 1`.

## SpringDofPropertyExplicit

The scalar spring that names a property, with the coordinate system its direction is given in.

**Record format and fields**

`SpringDofPropertyExplicit;id;propId;node1;components1;node2;components2;frameId;follow`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `follow` | `text` | — | Specifies whether the direction or attachment follows the changing configuration. |

Accepted words: `CoordinateFrame`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the point ID `node1` must not be negative.
- `components1` — `components1` must be 0 or a list of the digits 1 to 6, each at most once.
- `node2` — the point ID `node2` must not be negative.
- `components2` — `components2` must be 0 or a list of the digits 1 to 6, each at most once.
- `frameId` — the coordinate system ID must not be negative.

**Example record**

~~~text
SpringDofPropertyExplicit;11;10;2;1;1;1
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol700_explicit_springs.oos)

Reading the example gives `id = 11`, `propId = 10`, `node1 = 2`, `components1 = 1`.

**Referenced records in this example**

- [SpringPropTable](properties.md#springproptable) via `propId = 10`.

## SpringOffsetExplicit

Defines a discrete spring with offsets between its attachment points in an explicit model.

**Record format and fields**

`SpringOffsetExplicit;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node2` — the grid point IDs must be positive integers.

**Example record**

~~~text
SpringOffsetExplicit;21;20;3;4
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol700_explicit_springs.oos)

Reading the example gives `id = 21`, `propId = 20`, `node1 = 3`, `node2 = 4`.

**Referenced records in this example**

- [SpringOffsetProp](properties.md#springoffsetprop) via `propId = 20`.
- [Node](nodes.md#node) via `node1 = 3`, `node2 = 4`.

## SpringScalarInline

A scalar spring between two scalar points, with its own stiffness (no property).

**Record format and fields**

`SpringScalarInline;id;stiffness;scalarPoint1;scalarPoint2;id2;stiffness2;scalarPoint3;scalarPoint4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | — | Identifier in the element namespace. |
| 2 | `stiffness` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 5 | `id2` | `integer` | — | Identifier at position 2 in the ordered SpringScalarInline data. |
| 6 | `stiffness2` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 2. |
| 7 | `scalarPoint3` | `integer` | 0 | Scalar point at position 3 in the ordered connection. |
| 8 | `scalarPoint4` | `integer` | 0 | Scalar point at position 4 in the ordered connection. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint1` — `scalarPoint1` and `scalarPoint2` cannot both be blank or zero.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
SpringScalarInline;203;500.;203
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id = 203`, `stiffness = 500.`, `scalarPoint1 = 203`.

## SpringScalarProperty

A scalar spring between two scalar points, with a [SpringProp](properties.md#springprop) property.

**Record format and fields**

`SpringScalarProperty;id;propId;scalarPoint1;scalarPoint2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `scalarPoint1` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `scalarPoint2` | `integer` | 0 | Identifier addressing scalar or grid point data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `scalarPoint1` — the scalar point IDs must not be negative.
- `scalarPoint2` — the two scalar points must be different.

**Example record**

~~~text
SpringScalarProperty;204;23;201;202
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 204`, `propId = 23`, `scalarPoint1 = 201`, `scalarPoint2 = 202`.

## Tube2

A tension-compression-torsion tube element between two grid points.

**Record format and fields**

`Tube2;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node1` — the two grid points must be different.

**Example record**

~~~text
Tube2;3;3;5;6
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 3`, `propId = 3`, `node1 = 5`, `node2 = 6`.

**Referenced records in this example**

- [TubeProp](properties.md#tubeprop) via `propId = 3`.
- [Node](nodes.md#node) via `node1 = 5`, `node2 = 6`.

## UserDefined1

The connection of a user dummy element of number 1, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined1;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined1;1;11;1;2;45.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 1`, `propId = 11`.

## UserDefined1Attributes

The attributes of the user dummy element number 1, whose connection is a [UserDefined1](elements.md#userdefined1) card and whose property is a [UserDefined1Prop](elements.md#userdefined1prop) card.

**Record format and fields**

`UserDefined1Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined1Attributes;2;1;2;0
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined1Prop

Supplies the property data for [UserDefined1](elements.md#userdefined1) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined1Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined1Prop;11;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 11`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined2

The connection of a user dummy element of number 2, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined2;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined2;2;12;2;3;50.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 2`, `propId = 12`.

## UserDefined2Attributes

The attributes of the user dummy element number 2, whose connection is a [UserDefined2](elements.md#userdefined2) card and whose property is a [UserDefined2Prop](elements.md#userdefined2prop) card.

**Record format and fields**

`UserDefined2Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined2Attributes;2;1;2;0;UserDefined2
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined2Prop

Supplies the property data for [UserDefined2](elements.md#userdefined2) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined2Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined2Prop;12;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 12`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined3

The connection of a user dummy element of number 3, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined3;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined3;3;13;3;4;55.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 3`, `propId = 13`.

## UserDefined3Attributes

The attributes of the user dummy element number 3, whose connection is a [UserDefined3](elements.md#userdefined3) card and whose property is a [UserDefined3Prop](elements.md#userdefined3prop) card.

**Record format and fields**

`UserDefined3Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined3Attributes;2;1;2;0;UserDefined3
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined3Prop

Supplies the property data for [UserDefined3](elements.md#userdefined3) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined3Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined3Prop;13;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 13`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined4

The connection of a user dummy element of number 4, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined4;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined4;4;14;4;5;60.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 4`, `propId = 14`.

## UserDefined4Attributes

The attributes of the user dummy element number 4, whose connection is a [UserDefined4](elements.md#userdefined4) card and whose property is a [UserDefined4Prop](elements.md#userdefined4prop) card.

**Record format and fields**

`UserDefined4Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined4Attributes;2;1;2;0;UserDefined4
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined4Prop

Supplies the property data for [UserDefined4](elements.md#userdefined4) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined4Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined4Prop;14;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 14`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined5

The connection of a user dummy element of number 5, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined5;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined5;5;15;5;6;65.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 5`, `propId = 15`.

## UserDefined5Attributes

The attributes of the user dummy element number 5, whose connection is a [UserDefined5](elements.md#userdefined5) card and whose property is a [UserDefined5Prop](elements.md#userdefined5prop) card.

**Record format and fields**

`UserDefined5Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined5Attributes;2;1;2;0;UserDefined5
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined5Prop

Supplies the property data for [UserDefined5](elements.md#userdefined5) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined5Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined5Prop;15;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 15`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined6

The connection of a user dummy element of number 6, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined6;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined6;6;16;6;7;70.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 6`, `propId = 16`.

## UserDefined6Attributes

The attributes of the user dummy element number 6, whose connection is a [UserDefined6](elements.md#userdefined6) card and whose property is a [UserDefined6Prop](elements.md#userdefined6prop) card.

**Record format and fields**

`UserDefined6Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined6Attributes;2;1;2;0;UserDefined6
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined6Prop

Supplies the property data for [UserDefined6](elements.md#userdefined6) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined6Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined6Prop;16;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 16`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined7

The connection of a user dummy element of number 7, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined7;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined7;7;17;7;8;75.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 7`, `propId = 17`.

## UserDefined7Attributes

The attributes of the user dummy element number 7, whose connection is a [UserDefined7](elements.md#userdefined7) card and whose property is a [UserDefined7Prop](elements.md#userdefined7prop) card.

**Record format and fields**

`UserDefined7Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined7Attributes;2;1;2;0;UserDefined7
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `nodeCount = 2`, `connectionFieldCount = 1`, `propertyFieldCount = 2`, `displacementComponentCount = 0`.

## UserDefined7Prop

Supplies the property data for [UserDefined7](elements.md#userdefined7) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined7Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined7Prop;17;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 17`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined8

The connection of a user dummy element of number 8, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined8;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined8;8;18;8;9;80.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 8`, `propId = 18`.

## UserDefined8Attributes

The attributes of the user dummy element number 8, whose connection is a [UserDefined8](elements.md#userdefined8) card and whose property is a [UserDefined8Prop](elements.md#userdefined8prop) card.

**Record format and fields**

`UserDefined8Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined8Attributes;18;0;5;0;CrackTip2D
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `nodeCount = 18`, `connectionFieldCount = 0`, `propertyFieldCount = 5`, `displacementComponentCount = 0`.

## UserDefined8Prop

Supplies the property data for [UserDefined8](elements.md#userdefined8) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined8Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined8Prop;18;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 18`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserDefined9

The connection of a user dummy element of number 9, an element whose stiffness, mass and output are computed by routines the user links into the solver.

**Record format and fields**

`UserDefined9;id;propId;<connectionFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Repeated group `connectionFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 99999999.
- `node1` — `node1` is required: the field after `propId` is a positive integer.

**Example record**

~~~text
UserDefined9;9;19;9;10;85.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 9`, `propId = 19`.

## UserDefined9Attributes

The attributes of the user dummy element number 9, whose connection is a [UserDefined9](elements.md#userdefined9) card and whose property is a [UserDefined9Prop](elements.md#userdefined9prop) card.

**Record format and fields**

`UserDefined9Attributes;nodeCount;connectionFieldCount;propertyFieldCount;displacementComponentCount;elementName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeCount` | `integer` | Required | Number of node entries. |
| 2 | `connectionFieldCount` | `integer` | 0 | Number of connection field entries. |
| 3 | `propertyFieldCount` | `integer` | 0 | Number of property field entries. |
| 4 | `displacementComponentCount` | `integer` | 0 | Number of displacement component entries. |
| 5 | `elementName` | `text` | — | Text naming the element. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeCount` — `nodeCount` must be a positive integer.
- `connectionFieldCount` — `connectionFieldCount` must not be negative.
- `propertyFieldCount` — `propertyFieldCount` must be an integer from 0 to 24.
- `displacementComponentCount` — `displacementComponentCount` must be 0 (no differential stiffness), 3 or 6.

**Example record**

~~~text
UserDefined9Attributes;64;0;6;0;CrackTip3D
~~~

[Model containing this record](../../../validation/models/linear_elements/cracks_seam_interface_static.oos)

Reading the example gives `nodeCount = 64`, `connectionFieldCount = 0`, `propertyFieldCount = 6`, `displacementComponentCount = 0`.

## UserDefined9Prop

Supplies the property data for [UserDefined9](elements.md#userdefined9) elements. The user element determines the meaning of the property values.

**Record format and fields**

`UserDefined9Prop;id;matId;<propertyFields>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |

**Repeated group `propertyFields`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyField` | `number` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propertyFields` — the card has at most 24 additional fields.

**Example record**

~~~text
UserDefined9Prop;19;1;1.;250.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol101_dummy_elements.oos)

Reading the example gives `id = 19`, `matId = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## ViscousDamper2

A viscous damper between two grid points, with a [ViscousDamperProp](properties.md#viscousdamperprop) property.

**Record format and fields**

`ViscousDamper2;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Identifier addressing node data. |
| 4 | `node2` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node2` — `node1` and `node2` must be different.

**Example record**

~~~text
ViscousDamper2;7;7;2;3
~~~

[Model containing this record](../../../validation/models/card_namespaces/namespace_conm2_cvisc.oos)

Reading the example gives `id = 7`, `propId = 7`, `node1 = 2`, `node2 = 3`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 2`, `node2 = 3`.

## Weld

A weld or fastener between two surface patches, a point and a patch, or two points.

**Record format and fields**

Forms: `partPattern`, `elementPattern`, `elementIds`, `gridIds`, `align`.

### Weld: partPattern

Form `partPattern`, when `kind` is `PartPatch`.

`Weld;id;propId;spotNode;kind;nodeA;nodeB;matFrameId;propIdA;propIdB;locationX;locationY;locationZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 4 | `kind` | `text` | — | Selects the kind for Weld. |
| 5 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 7 | `matFrameId` | `integer` | -1 | Coordinate system defining the material directions. |
| 8 | `propIdA` | `integer` | — | Identifier of the property on side A. |
| 9 | `propIdB` | `integer` | — | Identifier of the property on side B. |
| 10 | `locationX` | `real` | — | X coordinate of the location. |
| 11 | `locationY` | `real` | — | Y coordinate of the location. |
| 12 | `locationZ` | `real` | — | Z coordinate of the location. |

### Weld: elementPattern

Form `elementPattern`, when `kind` is `ElemPatch`.

`Weld;id;propId;spotNode;kind;nodeA;nodeB;matFrameId;shellIdA;shellIdB;locationX;locationY;locationZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 4 | `kind` | `text` | — | Selects the kind for Weld. |
| 5 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 7 | `matFrameId` | `integer` | -1 | Coordinate system defining the material directions. |
| 8 | `shellIdA` | `integer` | — | Identifier of the shell on side A. |
| 9 | `shellIdB` | `integer` | — | Identifier of the shell on side B. |
| 10 | `locationX` | `real` | — | X coordinate of the location. |
| 11 | `locationY` | `real` | — | Y coordinate of the location. |
| 12 | `locationZ` | `real` | — | Z coordinate of the location. |

### Weld: elementIds

Form `elementIds`, when `kind` is `ElemIdPatch`.

`Weld;id;propId;spotNode;kind;nodeA;nodeB;matFrameId;shellIdA;shellIdB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 4 | `kind` | `text` | — | Selects the kind for Weld. |
| 5 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 7 | `matFrameId` | `integer` | -1 | Coordinate system defining the material directions. |
| 8 | `shellIdA` | `integer` | — | Identifier of the shell on side A. |
| 9 | `shellIdB` | `integer` | 0 | Identifier of the shell on side B. |

### Weld: gridIds

Form `gridIds`, when `kind` is `NodeIdPatch`.

`Weld;id;propId;spotNode;kind;nodeA;nodeB;patchShapes;matFrameId;nodeA1;nodeA2;nodeA3;nodeA4;nodeA5;nodeA6;nodeA7;nodeA8;nodeB1;nodeB2;nodeB3;nodeB4;nodeB5;nodeB6;nodeB7;nodeB8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 4 | `kind` | `text` | — | Selects the kind for Weld. |
| 5 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 7 | `patchShapes` | `text` | — | Selects the shapes used to represent the paired attachment patches. |
| 8 | `matFrameId` | `integer` | -1 | Coordinate system defining the material directions. |
| 9 | `nodeA1` | `integer` | 0 | Identifier addressing node data. |
| 10 | `nodeA2` | `integer` | 0 | Identifier of the grid point on side A at position 2. |
| 11 | `nodeA3` | `integer` | 0 | Identifier of the grid point on side A at position 3. |
| 12 | `nodeA4` | `integer` | 0 | Identifier of the grid point on side A at position 4. |
| 13 | `nodeA5` | `integer` | 0 | Identifier of the grid point on side A at position 5. |
| 14 | `nodeA6` | `integer` | 0 | Identifier of the grid point on side A at position 6. |
| 15 | `nodeA7` | `integer` | 0 | Identifier of the grid point on side A at position 7. |
| 16 | `nodeA8` | `integer` | 0 | Identifier of the grid point on side A at position 8. |
| 17 | `nodeB1` | `integer` | 0 | Identifier of the grid point on side B at position 1. |
| 18 | `nodeB2` | `integer` | 0 | Identifier of the grid point on side B at position 2. |
| 19 | `nodeB3` | `integer` | 0 | Identifier of the grid point on side B at position 3. |
| 20 | `nodeB4` | `integer` | 0 | Identifier of the grid point on side B at position 4. |
| 21 | `nodeB5` | `integer` | 0 | Identifier of the grid point on side B at position 5. |
| 22 | `nodeB6` | `integer` | 0 | Identifier of the grid point on side B at position 6. |
| 23 | `nodeB7` | `integer` | 0 | Identifier of the grid point on side B at position 7. |
| 24 | `nodeB8` | `integer` | 0 | Identifier of the grid point on side B at position 8. |

### Weld: align

Form `align`, for every other record.

`Weld;id;propId;spotNode;kind;nodeA;nodeB;matFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Identifier addressing node data. |
| 4 | `kind` | `text` | — | Selects the kind for Weld. |
| 5 | `nodeA` | `integer` | 0 | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | 0 | Identifier addressing node data. |
| 7 | `matFrameId` | `integer` | -1 | Coordinate system defining the material directions. |

Accepted words: `AlignedNodes`, `ElemIdPatch`, `ElemPatch`, `NodeIdPatch`, `PartPatch`, `QuadPatch`, `QuadQuadPatch`, `QuadTriaPatch`, `TriaPatch`, `TriaQuadPatch`, `TriaTriaPatch`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `kind` — `kind` must be PartPatch, ElemPatch, ElemIdPatch, NodeIdPatch or AlignedNodes.
- `spotNode` — `spotNode`, `nodeA` and `nodeB` must be 0 (blank) or grid point IDs.
- `matFrameId` — `matFrameId` must be -1 or a coordinate system ID.
- `patchShapes` — `nodeA1` to `nodeB8` and `patchShapes` belong to the NodeIdPatch format.
- `nodeB` — `nodeA` and `nodeB` must be different.
- `patchShapes` — `patchShapes` must be QuadQuadPatch, QuadTriaPatch, TriaTriaPatch, TriaQuadPatch, QuadPatch or TriaPatch.
- `nodeA1` — the grid point IDs must not be negative.
- `nodeB1` — `nodeB1`, `nodeB2` and `nodeB3` are required for a patch to patch connection.
- `patchIdA` — the first patch (`propIdA` or `shellIdA`) must be a positive integer.
- `patchIdB` — `shellIdB` must be 0 (blank) or an element ID.
- `patchIdB` — the second patch (`propIdB` or `shellIdB`) must be a positive integer.
- `patchIdB` — the two patches must be different.
- `locationX` — `locationX`, `locationY` and `locationZ` must be all given or all blank.

**Example record**

~~~text
Weld;1001;2;901;PartPatch;;;;11;12
~~~

[Model containing this record](../../../validation/models/fasteners/cweld_forms.oos)
