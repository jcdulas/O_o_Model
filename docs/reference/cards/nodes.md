# Points and geometry

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AcousticSlotControl

Defines the harmonic index and default fluid properties for an acoustic cavity represented by slots.

**Record format and fields**

`AcousticSlotControl;defaultDensity;defaultBulkModulus;harmonic;defaultSlotWidth;defaultSlotCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `defaultDensity` | `real` | — | Density used when the corresponding input leaves its density unspecified. |
| 2 | `defaultBulkModulus` | `real` | — | Default bulk modulus (force per area). |
| 3 | `harmonic` | `integer` | — | Index identifying the spatial or temporal harmonic. |
| 4 | `defaultSlotWidth` | `real` | — | Default slot width (length). |
| 5 | `defaultSlotCount` | `integer` | — | Number of default slot entries. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `harmonic` — `harmonic` must not be negative.
- `defaultSlotCount` — `defaultSlotCount` must not be negative.

**Example record**

~~~text
AcousticSlotControl;1.2E-12;0.142;0;5.;6
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `defaultDensity = 1.2E-12`, `defaultBulkModulus = 0.142`, `harmonic = 0`, `defaultSlotWidth = 5.`.

## AcousticSlotFluidPoint

An axisymmetric fluid point of the acoustic cavity (slot) analysis, a scalar degree of freedom (the pressure) with a two-dimensional location.

**Record format and fields**

`AcousticSlotFluidPoint;id;radius;zCoord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 3 | `zCoord` | `real` | Required | Z coordinate of the location in the specified frame. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be an integer from 1 to 999999.

**Example record**

~~~text
AcousticSlotFluidPoint;1;25.;0.
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 1`, `radius = 25.`, `zCoord = 0.`.

## AcousticSlotSurfacePoint

A slot surface point of the acoustic cavity (slot) analysis, a scalar degree of freedom (the pressure) with a two-dimensional location and a slot width.

**Record format and fields**

`AcousticSlotSurfacePoint;id;radius;zCoord;slotWidth;fluidPointId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 3 | `zCoord` | `real` | Required | Z coordinate of the location in the specified frame. |
| 4 | `slotWidth` | `real` | — | Slot width (length). |
| 5 | `fluidPointId` | `integer` | 0 | Identifier addressing node data. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `radius` — `radius` must not be zero.

**Example record**

~~~text
AcousticSlotSurfacePoint;21;50.;0.;;11
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

Reading the example gives `id = 21`, `radius = 50.`, `zCoord = 0.`, `fluidPointId = 11`.

**Referenced records in this example**

- [AcousticSlotFluidPoint](nodes.md#acousticslotfluidpoint) via `fluidPointId = 11`.

## AdaptiveRefineControl

The control of the local adaptive mesh refinement for one criterion.

**Record format and fields**

`AdaptiveRefineControl;id;repeatCount;criterionId;regionMethod;regionId;snapMethod;maximumLevel`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `repeatCount` | `integer` | — | Number of repetitions of the defined event or block. |
| 3 | `criterionId` | `integer` | Required | Identifier selecting the criterion record or set. |
| 4 | `regionMethod` | `text` | — | Selects the region method for AdaptiveRefineControl. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 6 | `snapMethod` | `integer` | — | Selects the snap method for AdaptiveRefineControl. |
| 7 | `maximumLevel` | `integer` | same as repeatCount | Deepest allowed level of the specified hierarchy or refinement. |

Accepted words: `All`, `Constant`, `Element`, `Property`, `Superelement`, `Table`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `repeatCount` — `repeatCount` must not be negative.
- `snapMethod` — `snapMethod` must be 0 or 1.

**Example record**

~~~text
AdaptiveRefineControl;1;2;1;All;;0;2
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol101_adaptive_mesh.oos)

Reading the example gives `id = 1`, `repeatCount = 2`, `criterionId = 1`, `regionMethod = All`.

## AdaptiveRefineCriterion

A criterion that picks the elements to refine in the adaptive mesh refinement.

**Record format and fields**

`AdaptiveRefineCriterion;id;kind;parameter1;parameter2;parameter3;parameter4;parameter5;parameter6`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `integer` | — | Selects the kind for AdaptiveRefineCriterion. |
| 3 | `parameter1` | `real` | — | Parameter 1 of the selected refinement criterion; its meaning follows the criterion. |
| 4 | `parameter2` | `real` | — | Parameter 2 of the selected refinement criterion; its meaning follows the criterion. |
| 5 | `parameter3` | `real` | — | Parameter 3 of the selected refinement criterion; its meaning follows the criterion. |
| 6 | `parameter4` | `real` | — | Parameter 4 of the selected refinement criterion; its meaning follows the criterion. |
| 7 | `parameter5` | `real` | — | Parameter 5 of the selected refinement criterion; its meaning follows the criterion. |
| 8 | `parameter6` | `real` | — | Parameter 6 of the selected refinement criterion; its meaning follows the criterion. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `kind` — `kind` must be 1, 2, 3 or 4.

**Example record**

~~~text
AdaptiveRefineCriterion;2;2;0.;0.;0.;15.
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol101_adaptive_mesh.oos)

Reading the example gives `id = 2`, `kind = 2`, `parameter1 = 0.`, `parameter2 = 0.`.

## AssociativeNode

Associates a grid point with the assembly step that combines model parts.

**Record format and fields**

`AssociativeNode;id;origNodeId;partitionName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `origNodeId` | `integer` | Required | Identifier selecting the orig node record or set. |
| 3 | `partitionName` | `text` | — | Text naming the partition. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AssociativeNode;101;1000;LEFT_WING_TANK
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/service_and_paa_cards.oos)

Reading the example gives `id = 101`, `origNodeId = 1000`, `partitionName = LEFT_WING_TANK`.

## AxisymConeControl

Identifies the model as an axisymmetric conical shell system using rings, shell elements and ring loads.

**Record format and fields**

`AxisymConeControl;highestHarmonic`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `highestHarmonic` | `integer` | Required | Largest harmonic index included in the representation. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `highestHarmonic` — `highestHarmonic` must be an integer from 0 to 997.

**Example record**

~~~text
AxisymConeControl;2
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_free_modes.oos)

Reading the example gives `highestHarmonic = 2`.

## AxisymConePoint

Defines a point on a conical shell ring for concentrated loads and displacement recovery.

**Record format and fields**

`AxisymConePoint;id;ringId;phiAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `ringId` | `integer` | Required | Identifier addressing node data. |
| 3 | `phiAngle` | `real` | Required | Angular coordinate or orientation denoted by phi in the local geometry. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymConePoint;51;5;0.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 51`, `ringId = 5`, `phiAngle = 0.`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId = 5`.

## AxisymConeRing

A ring of a conical shell model (an axisymmetric structure described by harmonics).

**Record format and fields**

`AxisymConeRing;id;radius;zCoord;permanentConstraints`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 3 | `zCoord` | `real` | Required | Z coordinate of the location in the specified frame. |
| 4 | `permanentConstraints` | `integer` | 0 | 0 = no permanent constraint. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `permanentConstraints` — `permanentConstraints` must be digits 1 to 6 with no repeat.

**Example record**

~~~text
AxisymConeRing;1;100.;0.;123456
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 1`, `radius = 100.`, `zCoord = 0.`, `permanentConstraints = 123456`.

## AxisymFluidControl

The basic parameters and the existence of an axisymmetric fluid analysis, with the harmonics of the solution.

**Record format and fields**

`AxisymFluidControl;frameId;gravity;defaultDensity;defaultBulkModulus;nonsymmetric;noHarmonicsFlag;<harmonics>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | Required | Coordinate system in which this entry is expressed. |
| 2 | `gravity` | `real` | Required | Acceleration of gravity used by the definition, in length per time squared. |
| 3 | `defaultDensity` | `real` | — | Density used when the corresponding input leaves its density unspecified. |
| 4 | `defaultBulkModulus` | `real` | — | Default bulk modulus (force per area). |
| 5 | `nonsymmetric` | `text` | — | Specifies whether the two sides or matrix halves are treated separately. |
| 6 | `noHarmonicsFlag` | `text` | — | Selects the no harmonics flag for AxisymFluidControl. |

**Repeated group `harmonics`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `harmonic` | `any` | — | Index identifying the spatial or temporal harmonic. |

Accepted words: `Constant`, `Element`, `No`, `None`, `Step`, `Table`, `Through`, `Yes`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `harmonic` — a harmonic must be an integer from 0 to 99.
- `lastHarmonic` — the end of a range must be above its start and at most 99.
- `harmonicStep` — `harmonicStep` must be a positive integer.
- `harmonic` — the harmonics must be in increasing order.

**Example record**

~~~text
AxisymFluidControl;1;9810.;1.E-9;2200.;No;;0;2
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `frameId = 1`, `gravity = 9810.`, `defaultDensity = 1.E-9`, `defaultBulkModulus = 2200.`.

## AxisymFluidFreePoint

A point on the free surface of an axisymmetric fluid at which the surface displacements are recovered.

**Record format and fields**

In the source layout, the form is called `pairsFromSlot3` when field 2 of the old layout is blank. Its compact field sequence is the one shown below.

Forms: `pairsFromSlot2`.

### AxisymFluidFreePoint: pairsFromSlot2

Form `pairsFromSlot2`, for every compact record.

`AxisymFluidFreePoint;fluidPointId;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fluidPointId` | `integer` | Required | Identifier addressing node data. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointId` | `integer` | — | Identifier of the point to which this entry applies. |
| 2 | `phiAngle` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. |

*Note*: at most three pairs.

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymFluidFreePoint;5;501;0.;502;45.
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

## AxisymFluidPressurePoint

A point of an axisymmetric fluid at which the pressure is recovered, and that may also measure pressure for a control device.

**Record format and fields**

In the source layout, the form is called `pairsFromSlot3` when field 2 of the old layout is blank. Its compact field sequence is the one shown below.

Forms: `pairsFromSlot2`.

### AxisymFluidPressurePoint: pairsFromSlot2

Form `pairsFromSlot2`, for every compact record.

`AxisymFluidPressurePoint;fluidPointId;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fluidPointId` | `integer` | Required | Identifier addressing node data. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointId` | `integer` | — | Identifier of the point to which this entry applies. |
| 2 | `phiAngle` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. |

*Note*: at most three pairs.

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymFluidPressurePoint;3;301;0.;302;45.
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

## AxisymFluidRing

A circle of an axisymmetric fluid model.

**Record format and fields**

`AxisymFluidRing;firstId;firstPosition1;firstPosition2;firstPosition3;secondId;secondPosition1;secondPosition2;secondPosition3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `firstId` | `integer` | — | Identifier selecting the first record or set. |
| 2 | `firstPosition1` | `real` | — | Coordinate 1 of the first position in the specified frame. |
| 3 | `firstPosition2` | `real` | 0.0 | Coordinate 2 of the first position in the specified frame. |
| 4 | `firstPosition3` | `real` | 0.0 | Coordinate 3 of the first position in the specified frame. |
| 5 | `secondId` | `integer` | — | Identifier selecting the second record or set. |
| 6 | `secondPosition1` | `real` | — | Coordinate 1 of the second position in the specified frame. |
| 7 | `secondPosition2` | `real` | 0.0 | Coordinate 2 of the second position in the specified frame. |
| 8 | `secondPosition3` | `real` | 0.0 | Coordinate 3 of the second position in the specified frame. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must be an integer from 1 to 499999.

**Example record**

~~~text
AxisymFluidRing;1;50.;;0.;2;100.;;0.
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `firstId = 1`, `firstPosition1 = 50.`, `firstPosition3 = 0.`, `secondId = 2`.

## AxisymFluidRingNode

A grid point on a fluid ring ([AxisymFluidRing](nodes.md#axisymfluidring)) of an axisymmetric model.

**Record format and fields**

`AxisymFluidRingNode;id;phiAngle;displacementFrameId;permanentConstraints;fluidPointId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `phiAngle` | `real` | Required | Angular coordinate or orientation denoted by phi in the local geometry. |
| 3 | `displacementFrameId` | `integer` | 0 | Coordinate system in which the displacement components are expressed. |
| 4 | `permanentConstraints` | `integer` | 0 | Permanent single-point constraints, as digits 1..6 (0 = none). |
| 5 | `fluidPointId` | `integer` | Required | Identifier addressing node data. |

Accepted words: `AxisymFluidRing`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.
- `displacementFrameId` — `displacementFrameId` must be 0 or a coordinate system ID.
- `permanentConstraints` — `permanentConstraints` must be digits 1 to 6 with no repeat.

**Example record**

~~~text
AxisymFluidRingNode;401;0.;1;246;4
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 401`, `phiAngle = 0.`, `displacementFrameId = 1`, `permanentConstraints = 246`.

**Referenced records in this example**

- [CylindricalFrame2](coordinate_systems.md#cylindricalframe2) via `displacementFrameId = 1`.

## ExtraPoint

Introduces an additional scalar degree of freedom for a dynamic model.

**Record format and fields**

`ExtraPoint;<ids>`

This part of the record has no fixed fields.

**Repeated group `ids`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | — | Identifier in the node namespace. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the extra point ID must be a positive integer.

**Example record**

~~~text
ExtraPoint;4001;4011;4012
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_transient_sol109.oos)

## GeomPoint

A geometric point that is not a grid point (an edge point for [SuperelementLocation](superelements.md#superelementlocation), a profile point of a [BeamArbitrarySectionProp](elements.md#beamarbitrarysectionprop)).

**Record format and fields**

`GeomPoint;id;positionFrameId;position1;position2;position3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the node namespace. |
| 2 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 3 | `position1` | `real` | 0.0 | Coordinate 1 of the specified location in its reference frame. |
| 4 | `position2` | `real` | 0.0 | Coordinate 2 of the specified location in its reference frame. |
| 5 | `position3` | `real` | 0.0 | Coordinate 3 of the specified location in its reference frame. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.
- `positionFrameId` — `positionFrameId` must be 0 or a coordinate system ID.

**Example record**

~~~text
GeomPoint;941;;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 941`, `position1 = 0.`, `position2 = 0.`, `position3 = 0.`.

## ModuleBolt

Defines a pretensioned bolt spanning modules. A control point couples pairs of grid points on opposite sides of its cut.

**Record format and fields**

`ModuleBolt;id;controlNode;controlModuleId;topModuleId;bottomModuleId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `controlNode` | `integer` | Required | Identifier of the grid point through which this definition is controlled. |
| 3 | `controlModuleId` | `integer` | 0 | Identifier selecting the control module record or set. |
| 4 | `topModuleId` | `integer` | 0 | Identifier selecting the top module record or set. |
| 5 | `bottomModuleId` | `integer` | 0 | Identifier selecting the bottom module record or set. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Top`**

**Repeated group `topNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `topNode` | `integer` | — | Grid point defining the top side of the connection. |

**Section `Bottom`**

**Repeated group `bottomNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bottomNode` | `integer` | — | Grid point defining the bottom side of the connection. |

Accepted words: `All`, `Bottom`, `Constant`, `Element`, `Table`, `Through`, `Top`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `topList` — the bolt needs grid points in `topList`.
- `bottomList` — the bolt needs grid points in `bottomList`.

**Example record**

~~~text
ModuleBolt;309;70;0;1;2;Top;2;103;107;Bottom;2;203;207
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 309`, `controlNode = 70`, `controlModuleId = 0`, `topModuleId = 1`.

## ModuleBoundaryNodes

The grid points of a module that the automatic search of the boundary with another module, or with all the others, is limited to.

**Record format and fields**

`ModuleBoundaryNodes;moduleIdA;otherModule;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 2 | `otherModule` | `any` | — | Identifier of the module on the other side of the operation. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeA` | `any` | — | Grid point identifier at connectivity position A. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
ModuleBoundaryNodes;1;0;101;104;107
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `moduleIdA = 1`, `otherModule = 0`.

## ModuleBrakeSystem

The data of a brake system for brake squeal calculations with one wheel or several, on one axis or several, in different modules.

**Record format and fields**

`ModuleBrakeSystem;id;squealLoadFactor;frictionVectorMethod;squealOnly;contactMethod;<disks>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `squealLoadFactor` | `real` | 0.0 | Multiplier for squeal load. |
| 3 | `frictionVectorMethod` | `integer` | 0 | Selects the friction vector method for ModuleBrakeSystem. |
| 4 | `squealOnly` | `text` | — | Restricts the option to the brake-squeal analysis when selected. |
| 5 | `contactMethod` | `integer` | 0 | Selects the contact method for ModuleBrakeSystem. |

**Repeated group `disks`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `diskName` | `text` | — | Text naming the disk. |
| 2 | `moduleId1` | `integer` | — | Identifier selecting the module record or set. |
| 3 | `body1Id` | `integer` | — | Identifier selecting the body 1 record or set. |
| 4 | `moduleId2` | `integer` | — | Identifier selecting the module record or set. |
| 5 | `body2Id` | `integer` | — | Identifier selecting the body 2 record or set. |
| 6 | `motion1Id` | `integer` | — | Identifier selecting the motion 1 record or set. |
| 7 | `motion2Id` | `integer` | — | Identifier selecting the motion 2 record or set. |
| 8 | `brakeSystemId` | `integer` | — | Identifier selecting the brake system record or set. |

Accepted words: `All`, `Constant`, `Element`, `No`, `Table`, `Through`, `Yes`.

**Example record**

~~~text
ModuleBrakeSystem;1;1.;0;No;0;DISK1;1;1;0;2;1;;1
~~~

[Model containing this record](../../../validation/models/modules/modules_brake_squeal_sol400.oos)

Reading the example gives `id = 1`, `squealLoadFactor = 1.`, `frictionVectorMethod = 0`, `squealOnly = No`.

## ModuleBulkOptions

The type of a module and how the boundary between modules is searched.

**Record format and fields**

`ModuleBulkOptions;id;kind;sourceModuleId;method;tolerance;unitNumber`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | — | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for ModuleBulkOptions. |
| 3 | `sourceModuleId` | `integer` | 0 | Identifier selecting the source module record or set. |
| 4 | `method` | `text` | — | Selects the method for ModuleBulkOptions. |
| 5 | `tolerance` | `real` | 0.0 | Allowable change or residual for the selected numerical check. |
| 6 | `unitNumber` | `integer` | 0 | Logical file unit used to identify an external resource. |

Accepted words: `All`, `Automatic`, `Constant`, `Element`, `External`, `ExternalBinaryResults`, `ExternalMatrixFile`, `Manual`, `Mirror`, `Move`, `Primary`, `Repeat`, `Table`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `sourceModuleId` — `sourceModuleId` must be zero or a positive module number.
- `unitNumber` — `unitNumber` must be zero or a positive unit number.

**Example record**

~~~text
ModuleBulkOptions;4;Move;1;Automatic
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 4`, `kind = Move`, `sourceModuleId = 1`, `method = Automatic`.

## ModuleBushing

A generalized spring-and-damper element whose end points may lie in different modules; the rules of the [Bushing](elements.md#bushing) apply to it.

**Record format and fields**

`ModuleBushing;id;propId;nodeA;nodeB;position1;orientationNode;position2;position3;frameId;offsetFraction;offsetFrameId;offset1;offset2;offset3;moduleIdA;moduleIdB;orientationModuleId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nodeA` | `integer` | Required | Grid point identifier at connectivity position A. |
| 4 | `nodeB` | `integer` | 0 | Grid point identifier at connectivity position B. |
| 5 | `position1` | `real` | — | Coordinate 1 of the specified location in its reference frame. Alternative to `orientationNode`. |
| 6 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. Alternative to `position1`. |
| 7 | `position2` | `real` | 0.0 | Coordinate 2 of the specified location in its reference frame. |
| 8 | `position3` | `real` | 0.0 | Coordinate 3 of the specified location in its reference frame. |
| 9 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 10 | `offsetFraction` | `real` | 0.5 | Offset expressed as a fraction of the associated reference dimension or range. |
| 11 | `offsetFrameId` | `integer` | -1 | Identifier selecting the offset frame record or set. |
| 12 | `offset1` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 1. |
| 13 | `offset2` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 2. |
| 14 | `offset3` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 3. |
| 15 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 16 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |
| 17 | `orientationModuleId` | `integer` | 0 | Identifier selecting the orientation module record or set. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer below 100 000 000.
- `nodeB` — `nodeB` must be 0 (blank) or a grid point ID.
- `orientationNode` — `orientationNode` must be a positive grid point ID.
- `frameId` — `frameId` must be blank or a coordinate system ID.
- `offsetFrameId` — `offsetFrameId` must be -1 or a coordinate system ID.

**Example record**

~~~text
ModuleBushing;305;34;111;211;;;;;0;;;;;;1;2
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 305`, `propId = 34`, `nodeA = 111`, `nodeB = 211`.

## ModuleConnection

How the boundary points of the modules are connected at a location.

**Record format and fields**

`ModuleConnection;id;kind;tolerance;xCoord;locationNode;yCoord;zCoord;moduleId;frameId;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for ModuleConnection. |
| 3 | `tolerance` | `real` | 0.0 | Allowable change or residual for the selected numerical check. |
| 4 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. Alternative to `locationNode`. |
| 5 | `locationNode` | `integer` | — | Grid point defining the location of the operation. Alternative to `xCoord`. |
| 6 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 7 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 8 | `moduleId` | `integer` | 0 | Identifier selecting the module record or set. |
| 9 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberModuleId` | `integer` | — | Identifier selecting the member module record or set. |
| 2 | `memberNodeId` | `integer` | — | Identifier selecting the member node record or set. |

Accepted words: `All`, `Constant`, `Element`, `Merge`, `ModuleRigidStar`, `Rigid`, `RigidStarReleased`, `Table`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `frameId` — `frameId` must be zero or a positive coordinate system ID.
- `locationNode` — `locationNode` must be a positive grid point ID.
- `memberNodeId` — `memberNodeId` must be zero (every grid point of the module) or a point ID.

**Example record**

~~~text
ModuleConnection;21;Rigid;0.001;0.;;40.;0.;;;2;201;4;109
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 21`, `kind = Rigid`, `tolerance = 0.001`, `xCoord = 0.`.

## ModuleContactCandidates

The modules that are candidates for the automatic detection of contact across modules.

**Record format and fields**

`ModuleContactCandidates;moduleSetId;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleSetId` | `integer` | -1 | Identifier selecting the module set record or set. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `firstModuleId` | `integer` | — | Identifier selecting the first module record or set. |
| 2 | `secondModuleId` | `integer` | — | Identifier selecting the second module record or set. |

Accepted words: `Constant`, `Element`, `Table`, `TypedListSet3`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `moduleId` — a module number must not be negative.

**Example record**

~~~text
ModuleContactCandidates;0;1;2
~~~

[Model containing this record](../../../validation/models/modules/modules_contact_auto_sol101.oos)

Reading the example gives `moduleSetId = 0`.

## ModuleContactDetectParams

The parameters that detect contact pairs between bodies that lie in different modules when the contact is generated automatically, as (name, value) pairs.

**Record format and fields**

`ModuleContactDetectParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BilinearCoulomb`, `Both`, `Full`, `GeneralGlue`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `BeamContact`, `ContactKind`, `DeleteSolids`, `DetectionDistance`, `EdgeContact`, `FrictionCoefficient`, `FrictionKind`, `IgnoreThickness`, `InitialStiffness`, `SelfContact`.

**Example record**

~~~text
ModuleContactDetectParams;ContactKind;PermanentGlue;DetectionDistance;3.
~~~

[Model containing this record](../../../validation/models/modules/modules_contact_auto_sol101.oos)

## ModuleContactPair

A contact pair whose touching and touched bodies lie in different modules: general contact, glued, step glued or permanently glued.

**Record format and fields**

`ModuleContactPair;id;geometricParamsId;physicalParamsId;secondaryModule;secondaryBodyId;primaryModule;primaryBodyId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `geometricParamsId` | `integer` | 0 | Identifier selecting the geometric params record or set. |
| 3 | `physicalParamsId` | `integer` | 0 | Identifier selecting the physical params record or set. |
| 4 | `secondaryModule` | `integer` | 0 | Module containing the secondary side of the connection. |
| 5 | `secondaryBodyId` | `integer` | 0 | Identifier selecting the secondary body record or set. |
| 6 | `primaryModule` | `integer` | 0 | Module containing the primary side of the connection. |
| 7 | `primaryBodyId` | `integer` | 0 | Identifier selecting the primary body record or set. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Secondary`**

**Repeated group `secondaryBodies`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `secondaryListModule` | `integer` | — | Module containing the list of secondary entities. |
| 2 | `secondaryListBodyId` | `integer` | — | Identifier selecting the secondary list body record or set. |

**Section `Primary`**

**Repeated group `primaryBodies`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `primaryListModule` | `integer` | — | Module containing the list of primary entities. |
| 2 | `primaryListBodyId` | `integer` | — | Identifier selecting the primary list body record or set. |

Accepted words: `Constant`, `Element`, `Primary`, `Secondary`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the `id` must not be negative.

**Example record**

~~~text
ModuleContactPair;1;7;;2;2;1;1
~~~

[Model containing this record](../../../validation/models/modules/modules_contact_table_sol101.oos)

Reading the example gives `id = 1`, `geometricParamsId = 7`, `secondaryModule = 2`, `secondaryBodyId = 2`.

## ModuleContactTable

Selects interactions involving bodies in different modules using their contact definitions.

**Record format and fields**

`ModuleContactTable;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `module` | `integer` | — | Identifier of the model part owning the selected entities. |
| 2 | `contactPairId` | `integer` | — | Identifier selecting the contact pair record or set. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — `id` must not be negative.

**Example record**

~~~text
ModuleContactTable;10;;1
~~~

[Model containing this record](../../../validation/models/modules/modules_brake_squeal_sol400.oos)

Reading the example gives `id = 10`.

## ModuleDirectMatrix

The header of a matrix of direct input at points of several modules, or one column of it.

**Record format and fields**

`ModuleDirectMatrix;entryName;columnModuleId;matrixShapeOrNodeJ;inputTypeOrComponentsJ;outputType;polarFlag;columnCount;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `columnModuleId` | `integer` | 0 | Identifier selecting the column module record or set. |
| 3 | `matrixShapeOrNodeJ` | `integer` | — | Selects the matrix shape for a header or the column grid point for a data record. |
| 4 | `inputTypeOrComponentsJ` | `integer` | — | Input numeric representation in a matrix header or column point components in a data record. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for ModuleDirectMatrix. |
| 6 | `polarFlag` | `integer` | 0 | Selects the polar flag for ModuleDirectMatrix. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | — | Identifier selecting the module record or set. |
| 2 | `node` | `integer` | — | Grid point to which this entry applies. |
| 3 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 4 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 5 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

Accepted words: `All`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `entryName` — `entryName` must be a nonempty matrix name without control characters.
- `matrixShape` — `matrixShape` must be 1 (square), 2 or 9 (rectangular) or 6 (symmetric).
- `inputType` — `inputType` must be 1, 2, 3 or 4.
- `outputType` — `outputType` must be 0, 1, 2, 3 or 4.
- `polarFlag` — `polarFlag` must not be negative.
- `columnCount` — `columnCount` must not be negative.
- `imaginaryValue` — a header card has no terms and no `imaginaryValue` fields.
- `componentsJ` — `componentsJ` must be one of the integers 1 to 6, or 0 for a scalar or extra point.
- `node` — a grid, scalar or extra point ID must be a positive integer.
- `components` — `components` must be one of the integers 1 to 6, or 0 for a scalar point.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (`imaginaryValue` is blank).

**Example record**

~~~text
ModuleDirectMatrix;KSPR;2;205;3;;;;2;205;3;100.
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `entryName = KSPR`, `columnModuleId = 2`, `matrixShapeOrNodeJ = 205`, `inputTypeOrComponentsJ = 3`.

## ModuleEntryExclusion

The Bulk Data entries of a primary module that a secondary (copied) module ignores.

**Record format and fields**

`ModuleEntryExclusion;<entries>`

This part of the record has no fixed fields.

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entry` | `text` | — | Member of the ordered input list, interpreted by the selected entry type. |

Accepted words: `Constant`, `Element`, `Node`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `entry1` — the card names at least one Bulk Data entry.
- `entry` — Node cannot be excluded (a fatal error).

**Example record**

~~~text
ModuleEntryExclusion;PointForceLoad
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

## ModuleExcludedNodes

The grid points of a module that are left out when the module is attached to another one (or to all the others): the counterpart of the [ModuleBoundaryNodes](nodes.md#moduleboundarynodes), which limits the search to a list.

**Record format and fields**

`ModuleExcludedNodes;moduleIdA;otherModule;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 2 | `otherModule` | `any` | — | Identifier of the module on the other side of the operation. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeA` | `any` | — | Grid point identifier at connectivity position A. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
ModuleExcludedNodes;1;0;104
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `moduleIdA = 1`, `otherModule = 0`.

## ModuleFastener

A fastener with a material orientation that connects two surface patches that lie in two modules (the multi-module counterpart of the [Fastener](elements.md#fastener)).

**Record format and fields**

`ModuleFastener;id;propId;kind;patchIdA;patchIdB;spotNode;nodeA;nodeB;xStation;yStation;zStation;moduleIdA;moduleIdB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `kind` | `text` | — | Selects the kind for ModuleFastener. |
| 4 | `patchIdA` | `integer` | Required | Identifier of the patch on side A. |
| 5 | `patchIdB` | `integer` | Required | Identifier of the patch on side B. |
| 6 | `spotNode` | `integer` | 0 | Grid point locating the connection spot. |
| 7 | `nodeA` | `integer` | 0 | Grid point identifier at connectivity position A. |
| 8 | `nodeB` | `integer` | 0 | Grid point identifier at connectivity position B. |
| 9 | `xStation` | `real` | — | X coordinate of the evaluation station. |
| 10 | `yStation` | `real` | — | Y coordinate of the evaluation station. |
| 11 | `zStation` | `real` | — | Z coordinate of the evaluation station. |
| 12 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 13 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |

Accepted words: `Constant`, `Element`, `Elements`, `Property`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.

**Example record**

~~~text
ModuleFastener;306;31;Property;11;12;;;;15.;5.;1.5;1;2
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 306`, `propId = 31`, `kind = Property`, `patchIdA = 11`.

## ModuleFluidSet

Identifies the fluid points or elements in a module that participate in a [FluidStructureInterface](thermal.md#fluidstructureinterface).

**Record format and fields**

`ModuleFluidSet;moduleId;<ids>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | 0 | Identifier selecting the module record or set. |

**Repeated group `ids`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | — | Identifier carried by the record. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
ModuleFluidSet;1;1011;Through;1019
~~~

[Model containing this record](../../../validation/models/modules/modules_fluid_sets_sol103.oos)

Reading the example gives `moduleId = 1`.

## ModuleLabel

The label a module carries in the headings of the results output.

**Record format and fields**

`ModuleLabel;id;entryLabel`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | 0 | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. Written as one text field. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
ModuleLabel;1;Primary panel
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 1`, `entryLabel = Primary panel`.

## ModuleLocation

The position of a module in the main model, given by three points of the module and the three points of module 0 that they must be moved onto.

**Record format and fields**

`ModuleLocation;id;pointA1;pointA2;pointA3;pointB1;pointB2;pointB3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointA1` | `integer` | Required | The three points in the module (plain IDs). |
| 3 | `pointA2` | `integer` | Required | Grid or geometric point 2 in the original interface frame of the part to be positioned. |
| 4 | `pointA3` | `integer` | Required | Grid or geometric point 3 in the original interface frame of the part to be positioned. |
| 5 | `pointB1` | `integer` | Required | The three points of module 0 that they are moved onto. |
| 6 | `pointB2` | `integer` | Required | Matching point 2 in the receiving frame after positioning the part. |
| 7 | `pointB3` | `integer` | Required | Matching point 3 in the receiving frame after positioning the part. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ModuleLocation;2;201;203;207;951;952;953
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 2`, `pointA1 = 201`, `pointA2 = 203`, `pointA3 = 207`.

## ModuleMirror1

A mirror image of a module in a plane given by three points of the main Bulk Data.

**Record format and fields**

`ModuleMirror1;id;point1;point2;point3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `point1` | `integer` | Required | Point at position 1 in the ordered ModuleMirror1 data. |
| 3 | `point2` | `integer` | Required | Point at position 2 in the ordered ModuleMirror1 data. |
| 4 | `point3` | `integer` | Required | Point at position 3 in the ordered ModuleMirror1 data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ModuleMirror1;61;931;932;933
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 61`, `point1 = 931`, `point2 = 932`, `point3 = 933`.

## ModuleMirror2

A mirror image of a module in a plane given by two axes of a coordinate system.

**Record format and fields**

`ModuleMirror2;id;frameId;referenceNode;axes`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `referenceNode` | `integer` | 0 | Identifier of the grid point serving as the reference for this definition. |
| 4 | `axes` | `text` | — | Coordinate axes used to express or select the specified quantities. |

Accepted words: `Constant`, `Element`, `PlaneXy`, `PlaneXz`, `PlaneYx`, `PlaneYz`, `PlaneZx`, `PlaneZy`, `Table`.

**Example record**

~~~text
ModuleMirror2;71;;920;PlaneYz
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 71`, `referenceNode = 920`, `axes = PlaneYz`.

## ModuleMirrorPlane

A mirror image of a module (a primary or a secondary, copied one) in a plane given by three points of the main Bulk Data.

**Record format and fields**

`ModuleMirrorPlane;id;point1;point2;point3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `point1` | `integer` | Required | Point at position 1 in the ordered ModuleMirrorPlane data. |
| 3 | `point2` | `integer` | Required | Point at position 2 in the ordered ModuleMirrorPlane data. |
| 4 | `point3` | `integer` | Required | Point at position 3 in the ordered ModuleMirrorPlane data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ModuleMirrorPlane;3;911;912;913
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 3`, `point1 = 911`, `point2 = 912`, `point3 = 913`.

## ModuleMoveSequence

The sequence of moves that repositions a module, given as the numbers of [ModuleTranslation](nodes.md#moduletranslation), [ModuleRotation1](nodes.md#modulerotation1), [ModuleRotation2](nodes.md#modulerotation2), [ModuleMirror1](nodes.md#modulemirror1) and [ModuleMirror2](nodes.md#modulemirror2) cards, applied in the order of the list.

**Record format and fields**

`ModuleMoveSequence;id;<moveIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `moveIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moveId` | `integer` | — | Identifier selecting the move record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `moveId1` — the card needs at least one move (`moveId1`).

**Example record**

~~~text
ModuleMoveSequence;6;61;62
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 6`.

## ModuleMultiPointConstr

Defines a linear multipoint constraint using degrees of freedom in different modules.

**Record format and fields**

`ModuleMultiPointConstr;id;moduleId1;node1;components1;coefficient1;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `moduleId1` | `integer` | 0 | Identifier selecting the module record or set. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `coefficient1` | `real` | — | Coefficient 1 in the ModuleMultiPointConstr relation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | — | Identifier selecting the module record or set. |
| 2 | `node` | `integer` | — | Grid point to which this entry applies. |
| 3 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 4 | `coefficient` | `real` | — | Coefficient value in the ModuleMultiPointConstr relation for terms. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node` — the card needs at least one term.
- `components` — `components` must be one of the integers 1 to 6, or 0 for a scalar point.
- `coefficient1` — the coefficient of the dependent term (`coefficient1`) must not be zero.

**Example record**

~~~text
ModuleMultiPointConstr;10;2;208;3;1.;1;108;3;-1.
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 10`, `moduleId1 = 2`, `node1 = 208`, `components1 = 3`.

## ModuleRigidBodyStar

A rigid body whose six independent degrees of freedom are those of one grid point and whose dependent degrees of freedom are components of any number of other grid points, all of which may lie in different modules (the multi-module counterpart of the [RigidBodyStar](rigid_elements.md#rigidbodystar), whose rules apply).

**Record format and fields**

`ModuleRigidBodyStar;id;independentModuleId;independentNode;dependentComponents;<dependents>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `independentModuleId` | `integer` | 0 | Identifier selecting the independent module record or set. |
| 3 | `independentNode` | `integer` | Required | Point supplying an independent motion in the constraint. |
| 4 | `dependentComponents` | `integer` | Required | Component digits whose motion is determined by the constraint. |

**Repeated group `dependents`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentModule` | `number` | — | Module containing the dependent side of the connection. |
| 2 | `dependentNode` | `number` | — | Point whose selected motions are expressed through other degrees of freedom. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `dependentComponents` — `dependentComponents` must be a list of the digits 1 to 6, each at most once.
- `dependentNode` — the card needs at least one dependent grid point.

**Example record**

~~~text
ModuleRigidBodyStar;302;1;112;123456;2;212
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 302`, `independentModuleId = 1`, `independentNode = 112`, `dependentComponents = 123456`.

## ModuleRigidInterpolation

The motion of a reference grid point is the weighted average of the motion of other grid points, all of which may lie in different modules (the multi-module counterpart of the [RigidInterpolation](rigid_elements.md#rigidinterpolation), whose rules apply).

**Record format and fields**

`ModuleRigidInterpolation;id;referenceModuleId;referenceNode;referenceComponents;<weightedGroups>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceModuleId` | `integer` | 0 | Identifier selecting the reference module record or set. |
| 3 | `referenceNode` | `integer` | Required | Identifier of the grid point serving as the reference for this definition. |
| 4 | `referenceComponents` | `integer` | Required | Degrees of freedom used as the reference motion. |

**Repeated group `weightedGroups`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `weightedGroupItem` | `number` | — | Entity or quantity included in the group with the associated weight. |

**Keyed sections in `parts`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DependentDofs`**

**Repeated group `dependents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentModuleId` | `integer` | — | Identifier selecting the dependent module record or set. |
| 2 | `dependentNode` | `integer` | — | Point whose selected motions are expressed through other degrees of freedom. |
| 3 | `dependentComponents` | `integer` | — | Component digits whose motion is determined by the constraint. |

**Section `ThermalExpansion`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 2 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

Accepted words: `Constant`, `DependentDofs`, `Element`, `Table`, `ThermalExpansion`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `referenceComponents` — `referenceComponents` must be a list of the digits 1 to 6, each at most once.
- `weight1` — the card needs at least one weighted group.
- `components` — `components` must be a list of the digits 1 to 6, each at most once.
- `node` — a weighted group needs at least one grid point.
- `dependentComponents` — `dependentComponents` must be a list of the digits 1 to 6, each at most once.

**Example record**

~~~text
ModuleRigidInterpolation;304;;50;123;6;1.;123;1;106;2;206
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 304`, `referenceNode = 50`, `referenceComponents = 123`.

## ModuleRigidJoint

A rigid joint that connects two coinciding grid points that lie in two different modules (the multi-module counterpart of the [RigidJoint](rigid_elements.md#rigidjoint), whose rules apply).

**Record format and fields**

`ModuleRigidJoint;id;moduleIdA;nodeA;moduleIdB;nodeB;componentsB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 3 | `nodeA` | `integer` | Required | Grid point identifier at connectivity position A. |
| 4 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |
| 5 | `nodeB` | `integer` | Required | Grid point identifier at connectivity position B. |
| 6 | `componentsB` | `integer` | — | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `componentsB` — `componentsB` must be a list of the digits 1 to 6, each at most once.

**Example record**

~~~text
ModuleRigidJoint;301;;60;2;201;123456
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 301`, `nodeA = 60`, `moduleIdB = 2`, `nodeB = 201`.

## ModuleRigidRod

A pin-ended element that is rigid in translation and connects two grid points that lie in two modules (the multi-module counterpart of the [RigidRod](rigid_elements.md#rigidrod), whose rules apply).

**Record format and fields**

`ModuleRigidRod;id;moduleIdA;nodeA;moduleIdB;nodeB;componentsAtA;componentsAtB;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 3 | `nodeA` | `integer` | Required | Grid point identifier at connectivity position A. |
| 4 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |
| 5 | `nodeB` | `integer` | Required | Grid point identifier at connectivity position B. |
| 6 | `componentsAtA` | `integer` | 0 | Selected degrees of freedom at point A. |
| 7 | `componentsAtB` | `integer` | 0 | Selected degrees of freedom at point B. |
| 8 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 9 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `componentsAtA` — `componentsAtA` must be 1, 2, 3 or blank.
- `componentsAtB` — `componentsAtB` must be 1, 2, 3 or blank.

**Example record**

~~~text
ModuleRigidRod;303;1;104;2;204;;3
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 303`, `moduleIdA = 1`, `nodeA = 104`, `moduleIdB = 2`.

## ModuleRotation1

A rotation of a module about an axis given by two points of the main Bulk Data, optionally turning about a reference point.

**Record format and fields**

`ModuleRotation1;id;referenceNode;startNode;endNode;magnitude`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceNode` | `integer` | 0 | Identifier of the grid point serving as the reference for this definition. |
| 3 | `startNode` | `integer` | Required | Grid point at the beginning of the path or directed edge. |
| 4 | `endNode` | `integer` | Required | Grid point at the end of the path or directed edge. |
| 5 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `magnitude` — `magnitude` must not be zero.

**Example record**

~~~text
ModuleRotation1;41;;920;921;90.
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 41`, `startNode = 920`, `endNode = 921`, `magnitude = 90.`.

## ModuleRotation2

A rotation of a module about an axis of a coordinate system, optionally turning about a reference point.

**Record format and fields**

`ModuleRotation2;id;frameId;referenceNode;axis;magnitude`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `referenceNode` | `integer` | 0 | Identifier of the grid point serving as the reference for this definition. |
| 4 | `axis` | `text` | — | Coordinate axis about which the definition acts. |
| 5 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |

Accepted words: `Constant`, `Element`, `MinusXAxis`, `MinusYAxis`, `MinusZAxis`, `Table`, `XAxis`, `YAxis`, `ZAxis`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `magnitude` — `magnitude` must not be zero.

**Example record**

~~~text
ModuleRotation2;51;;920;ZAxis;-90.
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 51`, `referenceNode = 920`, `axis = ZAxis`, `magnitude = -90.`.

## ModuleSeam

A seam that connects two surface patches (shell elements) that lie in two modules (the multi-module counterpart of the [Seam](elements.md#seam), whose rules apply).

**Record format and fields**

`ModuleSeam;id;propId;seamLineName;patchKind;startPatchIdA;startPatchIdB;endPatchIdA;endPatchIdB;startNode;xStation;endNode;yStation;zStation;xEnd;yEnd;zEnd;moduleIdA;moduleIdB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `seamLineName` | `text` | — | Text naming the seam line. |
| 4 | `patchKind` | `text` | — | Selects the patch kind for ModuleSeam. |
| 5 | `startPatchIdA` | `integer` | Required | Identifier at the start of the patch range on side A. |
| 6 | `startPatchIdB` | `integer` | 0 | Identifier at the start of the patch range on side B. |
| 7 | `endPatchIdA` | `integer` | 0 | Identifier at the end of the patch range on side A. |
| 8 | `endPatchIdB` | `integer` | 0 | Identifier at the end of the patch range on side B. |
| 9 | `startNode` | `integer` | — | Grid point at the beginning of the path or directed edge. Alternative to `xStation`. |
| 10 | `xStation` | `real` | — | X coordinate of the evaluation station. Alternative to `startNode`. |
| 11 | `endNode` | `integer` | — | Grid point at the end of the path or directed edge. Alternative to `yStation`. |
| 12 | `yStation` | `real` | — | Y coordinate of the evaluation station. Alternative to `endNode`. |
| 13 | `zStation` | `real` | — | Z coordinate of the evaluation station. |
| 14 | `xEnd` | `real` | — | x coordinate of the endpoint. |
| 15 | `yEnd` | `real` | — | y coordinate of the endpoint. |
| 16 | `zEnd` | `real` | — | z coordinate of the endpoint. |
| 17 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 18 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |

Accepted words: `Constant`, `Element`, `Elements`, `ShellProp`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `startNode` — `startNode` is required and must be a positive integer.
- `endNode` — `endNode` is required and must be a positive integer.

**Example record**

~~~text
ModuleSeam;308;33;;ShellProp;11;12;;;;32.;;15.;1.5;38.;15.;1.5;1;2
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 308`, `propId = 33`, `patchKind = ShellProp`, `startPatchIdA = 11`.

## ModuleStructureSet

Identifies the structural points or elements in a module that participate in a [FluidStructureInterface](thermal.md#fluidstructureinterface).

**Record format and fields**

`ModuleStructureSet;moduleId;<ids>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | 0 | Identifier selecting the module record or set. |

**Repeated group `ids`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | — | Identifier carried by the record. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
ModuleStructureSet;0;1;Through;9
~~~

[Model containing this record](../../../validation/models/modules/modules_fluid_sets_sol103.oos)

Reading the example gives `moduleId = 0`.

## ModuleTranslation

A translation of a module, given as a vector between two points of the main Bulk Data.

**Record format and fields**

`ModuleTranslation;id;startNode;endNode;magnitude`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `startNode` | `integer` | Required | Grid point at the beginning of the path or directed edge. |
| 3 | `endNode` | `integer` | Required | Grid point at the end of the path or directed edge. |
| 4 | `magnitude` | `real` | 0.0 | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ModuleTranslation;62;941;942
~~~

[Model containing this record](../../../validation/models/modules/modules_boundary_move_sol101.oos)

Reading the example gives `id = 62`, `startNode = 941`, `endNode = 942`.

## ModuleWeld

A weld or fastener that connects two surface patches, a point and a patch, or two points, between two modules (the multi-module counterpart of the [Weld](elements.md#weld), whose rules apply).

**Record format and fields**

`ModuleWeld;id;propId;spotNode;kind;nodeA;nodeB;patchTypes;matFrameId;patchIdA;patchIdB;spotModuleId;moduleIdA;moduleIdB;nodeA1;xStation;nodeA2;yStation;nodeA3;zStation;nodeA4;nodeA5;nodeA6;nodeA7;nodeA8;nodeB1;nodeB2;nodeB3;nodeB4;nodeB5;nodeB6;nodeB7;nodeB8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `spotNode` | `integer` | 0 | Grid point locating the connection spot. |
| 4 | `kind` | `text` | — | Selects the kind for ModuleWeld. |
| 5 | `nodeA` | `integer` | 0 | Grid point identifier at connectivity position A. |
| 6 | `nodeB` | `integer` | 0 | Grid point identifier at connectivity position B. |
| 7 | `patchTypes` | `text` | — | Categories of patches included in the selection. |
| 8 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. |
| 9 | `patchIdA` | `integer` | — | Identifier of the patch on side A. |
| 10 | `patchIdB` | `integer` | — | Identifier of the patch on side B. |
| 11 | `spotModuleId` | `integer` | 0 | Identifier selecting the spot module record or set. |
| 12 | `moduleIdA` | `integer` | 0 | Identifier of the module on side A. |
| 13 | `moduleIdB` | `integer` | 0 | Identifier of the module on side B. |
| 14 | `nodeA1` | `integer` | — | Identifier of the grid point on side A at position 1. Alternative to `xStation`. |
| 15 | `xStation` | `real` | — | X coordinate of the evaluation station. Alternative to `nodeA1`. |
| 16 | `nodeA2` | `integer` | — | Identifier of the grid point on side A at position 2. Alternative to `yStation`. |
| 17 | `yStation` | `real` | — | Y coordinate of the evaluation station. Alternative to `nodeA2`. |
| 18 | `nodeA3` | `integer` | — | Identifier of the grid point on side A at position 3. Alternative to `zStation`. |
| 19 | `zStation` | `real` | — | Z coordinate of the evaluation station. Alternative to `nodeA3`. |
| 20 | `nodeA4` | `integer` | — | Identifier of the grid point on side A at position 4. |
| 21 | `nodeA5` | `integer` | — | Identifier of the grid point on side A at position 5. |
| 22 | `nodeA6` | `integer` | — | Identifier of the grid point on side A at position 6. |
| 23 | `nodeA7` | `integer` | — | Identifier of the grid point on side A at position 7. |
| 24 | `nodeA8` | `integer` | — | Identifier of the grid point on side A at position 8. |
| 25 | `nodeB1` | `integer` | — | Identifier of the grid point on side B at position 1. |
| 26 | `nodeB2` | `integer` | — | Identifier of the grid point on side B at position 2. |
| 27 | `nodeB3` | `integer` | — | Identifier of the grid point on side B at position 3. |
| 28 | `nodeB4` | `integer` | — | Identifier of the grid point on side B at position 4. |
| 29 | `nodeB5` | `integer` | — | Identifier of the grid point on side B at position 5. |
| 30 | `nodeB6` | `integer` | — | Identifier of the grid point on side B at position 6. |
| 31 | `nodeB7` | `integer` | — | Identifier of the grid point on side B at position 7. |
| 32 | `nodeB8` | `integer` | — | Identifier of the grid point on side B at position 8. |

Accepted words: `AlignedNodes`, `Constant`, `ElemIdPatch`, `ElemPatch`, `Element`, `NodeIdPatch`, `PartPatch`, `QuadPatch`, `QuadQuadPatch`, `QuadTriaPatch`, `Table`, `TriaPatch`, `TriaQuadPatch`, `TriaTriaPatch`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.
- `matFrameId` — `matFrameId` must be -1 (blank) or a coordinate system ID.
- `nodeA1` — the grid point IDs must not be negative.
- `patchIdB` — the two patches must be different.

**Example record**

~~~text
ModuleWeld;307;32;;PartPatch;;;;;11;12;;1;2;;25.;;15.;;1.5
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 307`, `propId = 32`, `kind = PartPatch`, `patchIdA = 11`.

## Node

A grid point with a position, an input coordinate system and a coordinate system for its displacement components.

**Record format and fields**

`Node;id;positionFrameId;position1;position2;position3;displacementFrameId;permanentConstraints;superelementId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Unique grid point identifier used by connectivity, loads and constraints. |
| 2 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 3 | `position1` | `real` | 0.0 | First coordinate in the position frame. It is x in a rectangular frame and radius in a cylindrical or spherical frame. |
| 4 | `position2` | `real` | 0.0 | Second coordinate in the position frame. It is y in a rectangular frame and an angle in cylindrical or spherical coordinates. |
| 5 | `position3` | `real` | 0.0 | Third coordinate in the position frame. It is z in rectangular and cylindrical coordinates and an angle in spherical coordinates. |
| 6 | `displacementFrameId` | `integer` | 0 | Coordinate system in which the displacement components are expressed. |
| 7 | `permanentConstraints` | `integer` | 0 | Component digits fixed at this node in its displacement frame. |
| 8 | `superelementId` | `integer` | 0 | Identifier of the superelement associated with the entry. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.
- `positionFrameId` — `positionFrameId` must be 0 or a coordinate system ID.
- `displacementFrameId` — `displacementFrameId` must be -1, 0 or a coordinate system ID.
- `permanentConstraints` — `permanentConstraints` must be digits 1 to 6 with no repeat.

**Example record**

~~~text
Node;1;1;50.;0.;0.;1
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_axi_table_load_sol114.oos)

Reading the example gives `id = 1`, `positionFrameId = 1`, `position1 = 50.`, `position2 = 0.`.

**Referenced records in this example**

- [CylindricalFrame2](coordinate_systems.md#cylindricalframe2) via `positionFrameId = 1`, `displacementFrameId = 1`.

## NodeDefaults

Supplies default position and displacement frames, permanent constraints and superelement membership for [Node](nodes.md#node) records with blank fields.

**Record format and fields**

`NodeDefaults;positionFrameId;displacementFrameId;permanentConstraints;superelementId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 2 | `displacementFrameId` | `integer` | 0 | Coordinate system in which the displacement components are expressed. |
| 3 | `permanentConstraints` | `integer` | 0 | Permanent single-point constraints, as digits 1..6 (0 = none). |
| 4 | `superelementId` | `integer` | 0 | Identifier of the superelement associated with the entry. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `positionFrameId` — `positionFrameId` must be 0 or a coordinate system ID.
- `displacementFrameId` — `displacementFrameId` must be -1, 0 or a coordinate system ID.
- `permanentConstraints` — `permanentConstraints` must be digits 1 to 6 with no repeat.
- `superelementId` — `superelementId` must be 0 or a superelement ID.

**Example record**

~~~text
NodeDefaults;10;10
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `positionFrameId = 10`, `displacementFrameId = 10`.

## NodeSequence

The sequence in which grid and scalar points are ordered (manual resequencing).

**Record format and fields**

`NodeSequence;<points>`

This part of the record has no fixed fields.

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `sequenceId` | `number` | — | Identifier selecting the sequence record or set. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1` — the card needs at least one point.
- `node1` — the card has at most four points.
- `node1` — a grid or scalar point ID must be a positive integer.
- `sequenceId1` — a sequence number must be greater than zero.

**Example record**

~~~text
NodeSequence;461;406.5;441;403.5
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

## ScalarPoint

Defines scalar grid-free degrees of freedom by their point identifiers.

**Record format and fields**

`ScalarPoint;<ids>`

This part of the record has no fixed fields.

**Repeated group `ids`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | — | Identifier in the node namespace. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the scalar point ID must be a positive integer.

**Example record**

~~~text
ScalarPoint;1001;Through;1008
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/component_mode_reduction.oos)

## ShellNormal

The surface normal vector at a grid point, for the [ShellQuad4](elements.md#shellquad4), [ShellQuad4Drilling](elements.md#shellquad4drilling), [ShellTria3](elements.md#shelltria3) and [ShellTria3Drilling](elements.md#shelltria3drilling) shell elements.

**Record format and fields**

`ShellNormal;nodeId;frameId;directionX;directionY;directionZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | Required | Identifier of the grid point addressed by this record. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 4 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 5 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `frameId` — `frameId` must be 0 or a coordinate system ID.

**Example record**

~~~text
ShellNormal;1111;10;1.;0.;0.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `nodeId = 1111`, `frameId = 10`, `directionX = 1.`, `directionY = 0.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeId = 1111`.

## SurfaceEdge

Declares how the surface continues across an edge between two nodes. A declaration may apply to one incident element when its state permits this.

**Record format and fields**

`SurfaceEdge;id;node1Id;node2Id;state;elementId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `node1Id` | `integer` | Required | Grid point at one end of the declared edge. |
| 3 | `node2Id` | `integer` | Required | Grid point at the other end of the declared edge. |
| 4 | `state` | `text` | — | Surface continuation at this edge. Smooth continues the tangent plane, Sharp marks a fold and Raw retains the mesh edge. |
| 5 | `elementId` | `integer` | 0 | Optional incident element restricting the declaration to its side of the edge. |

Accepted words: `Raw`, `Sharp`, `Smooth`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1Id` — the two grid points of the edge must be different.
- `state` — `state` is required: Smooth, Sharp or Raw.
- `state` — `state` must be Smooth, Sharp or Raw.
- `elementId` — `elementId` must be blank when `state` is Raw.

**Example record**

~~~text
SurfaceEdge;1;301;302;Smooth
~~~

Reading the example gives `id = 1`, `node1Id = 301`, `node2Id = 302`, `state = Smooth`.

## SurfaceFacet

Declares an existing shell element to be a flat facet bounded by straight folds. The element ID also identifies its declaration.

**Record format and fields**

`SurfaceFacet;elementId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elementId` | `integer` | Required | Identifier of the existing shell element whose face is declared planar. |

**Example record**

~~~text
SurfaceFacet;501
~~~

Reading the example gives `elementId = 501`.

## SurfaceLine

Declares the path or end of a surface line through an ordered sequence of grid points.

**Record format and fields**

`SurfaceLine;id;node1Id;throughNodeId;node2Id`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `node1Id` | `integer` | Required | First grid point defining the line direction. |
| 3 | `throughNodeId` | `integer` | Required | Grid point at which the line continues or terminates. |
| 4 | `node2Id` | `integer` | 0 | Next grid point on the line. Omit it to declare a line end. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1Id` — `node1Id` and `throughNodeId` must be different.
- `node2Id` — `node2Id` must be different from `node1Id` and `throughNodeId`.

**Example record**

~~~text
SurfaceLine;1;501;502;503
~~~

Reading the example gives `id = 1`, `node1Id = 501`, `throughNodeId = 502`, `node2Id = 503`.
