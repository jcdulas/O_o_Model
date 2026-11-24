# Loads

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AccelFieldLoad

A static acceleration load that varies over the model.

**Record format and fields**

`AccelFieldLoad;id;frameId;directionX;directionY;directionZ;direction;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 4 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 5 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |
| 6 | `direction` | `text` | — | Orientation in which the specified quantity acts or is measured. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `location` | `real` | — | Position at which the record is applied or the response is evaluated. |
| 2 | `acceleration` | `real` | — | Acceleration (length per time squared). |

Accepted words: `Constant`, `Element`, `Table`, `XDirection`, `YDirection`, `ZDirection`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `directionX` — at least one component of the acceleration vector must not be zero.

**Example record**

~~~text
AccelFieldLoad;15;;0.;0.;-1.;YDirection;0.;9810.;500.;19620.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 15`, `directionX = 0.`, `directionY = 0.`, `directionZ = -1.`.

## AccelNodeLoad

A static acceleration load on individual grid points.

**Record format and fields**

`AccelNodeLoad;id;frameId;magnitude;directionX;directionY;directionZ;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 5 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 6 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `any` | — | Identifier of the grid point addressed by this record. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `directionX` — at least one component of the acceleration vector must not be zero.
- `nodeId` — the card needs at least one grid point.

**Example record**

~~~text
AccelNodeLoad;16;;19620.;0.;0.;-1.;13;14;15;31;Through;35
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 16`, `magnitude = 19620.`, `directionX = 0.`, `directionY = 0.`.

## AcousticInfiniteParams

Supplies named settings for acoustic infinite elements, including geometric tolerance and the starting number for additional points.

**Record format and fields**

`AcousticInfiniteParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `number` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Constant`, `Element`, `Table`.

Accepted parameter names: `FieldPointInsideTolerance`, `FirstExtraPointId`.

**Example record**

~~~text
AcousticInfiniteParams;FieldPointInsideTolerance;0.01;FirstExtraPointId;9000001
~~~

[Model containing this record](../../../validation/models/acoustics/infinite_elements_sol108.oos)

## AcousticPressureLoadMatrices

Identifies exported acoustic pressure-load matrices to use in a frequency-response model.

**Record format and fields**

`AcousticPressureLoadMatrices;id;dataFileUnit;propertyFileUnit;scaleReal;scaleImaginary;fileLoadCaseId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `dataFileUnit` | `integer` | Required | Logical file unit containing the data values. |
| 3 | `propertyFileUnit` | `integer` | Required | Logical file unit containing the associated properties. |
| 4 | `scaleReal` | `real` | — | Real part of the complex factor multiplying the supplied data. |
| 5 | `scaleImaginary` | `real` | — | Imaginary part of the complex factor multiplying the supplied data. |
| 6 | `fileLoadCaseId` | `integer` | — | Identifier selecting the file load case record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AcousticPressureLoadMatrices;21;41;42;1.5;0.;1
~~~

[Model containing this record](../../../validation/models/read_only_thermal_acoustic/acoustic_pressure_load_sol108.oos)

Reading the example gives `id = 21`, `dataFileUnit = 41`, `propertyFileUnit = 42`, `scaleReal = 1.5`.

## AxialDeformationLoad

Enforced axial deformations of one-dimensional elements, for static analysis.

**Record format and fields**

`AxialDeformationLoad;id;<deformations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `deformations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `integer` | — | Identifier of the element addressed by this record. |
| 2 | `deformation` | `real` | — | Di: a positive value is an elongation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the deformation set ID must be a positive integer.
- `elemId1` — the card needs at least one element.
- `elemId3` — the card defines at most three deformations.
- `elemId1` — an element ID must be a positive integer.

**Example record**

~~~text
AxialDeformationLoad;19;203;0.1;201;-0.05
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 19`.

## AxisymConePressureLoad

The static pressure on a conical shell element, the one between two rings over an azimuthal sector.

**Record format and fields**

`AxisymConePressureLoad;id;pressure;ringId1;ringId2;phiAngle1;phiAngle2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `pressure` | `real` | Required | Normal force per unit area, in the model’s pressure units. |
| 3 | `ringId1` | `integer` | Required | Identifier addressing node data. |
| 4 | `ringId2` | `integer` | Required | Identifier addressing node data. |
| 5 | `phiAngle1` | `real` | 0.0 | Angular coordinate or orientation denoted by phi in the local geometry. Entry 1. |
| 6 | `phiAngle2` | `real` | 360.0 | Angular coordinate or orientation denoted by phi in the local geometry. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymConePressureLoad;10;0.2;3;4;0.;60.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 10`, `pressure = 0.2`, `ringId1 = 3`, `ringId2 = 4`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId1 = 3`, `ringId2 = 4`.

## AxisymConeTemperatureLoad

The temperature of a ring of a conical shell model at an azimuth angle.

**Record format and fields**

`AxisymConeTemperatureLoad;id1;ringId1;phiAngle1;temperature1;id2;ringId2;phiAngle2;temperature2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered AxisymConeTemperatureLoad data. |
| 2 | `ringId1` | `integer` | — | Identifier selecting the ring record or set. |
| 3 | `phiAngle1` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. Entry 1. |
| 4 | `temperature1` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 1. |
| 5 | `id2` | `integer` | — | Identifier at position 2 in the ordered AxisymConeTemperatureLoad data. |
| 6 | `ringId2` | `integer` | — | Identifier selecting the ring record or set. |
| 7 | `phiAngle2` | `real` | — | Angular coordinate or orientation denoted by phi in the local geometry. Entry 2. |
| 8 | `temperature2` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.
- `ringId` — the ring ID must be a positive integer.

**Example record**

~~~text
AxisymConeTemperatureLoad;20;1;0.;120.;20;1;180.;80.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id1 = 20`, `ringId1 = 1`, `phiAngle1 = 0.`, `temperature1 = 120.`.

## AxisymRingForceLoad

A static concentrated force on a ring of a conical shell model (it needs an [AxisymConeControl](nodes.md#axisymconecontrol) card).

**Record format and fields**

`AxisymRingForceLoad;id;ringId;harmonicId;scaleFactor;radialForce;azimuthalForce;axialForce`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `ringId` | `integer` | Required | Identifier addressing node data. |
| 3 | `harmonicId` | `any` | Required | Identifier selecting the harmonic record or set. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `radialForce` | `real` | 0.0 | Radial force (force). |
| 6 | `azimuthalForce` | `real` | 0.0 | Azimuthal force (force). |
| 7 | `axialForce` | `real` | 0.0 | Axial force (force). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `ringId` — the ring ID must be a positive integer.
- `harmonicId` — the harmonic cannot be negative.
- `harmonicId` — the end of a sequence of harmonics cannot be below its start.

**Example record**

~~~text
AxisymRingForceLoad;10;5;1;1.;100.;0.;0.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 10`, `ringId = 5`, `harmonicId = 1`, `scaleFactor = 1.`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId = 5`.

## AxisymRingMomentLoad

A static concentrated moment on a ring of a conical shell model.

**Record format and fields**

`AxisymRingMomentLoad;id;ringId;harmonicId;scaleFactor;radialMoment;azimuthalMoment;axialMoment`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `ringId` | `integer` | Required | Identifier addressing node data. |
| 3 | `harmonicId` | `any` | Required | Identifier selecting the harmonic record or set. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `radialMoment` | `real` | 0.0 | Component of applied moment in the radial direction (force times length). |
| 6 | `azimuthalMoment` | `real` | 0.0 | Component of applied moment in the circumferential direction (force times length). |
| 7 | `axialMoment` | `real` | 0.0 | Component of applied moment along the axis (force times length). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `harmonicId` — the harmonic cannot be negative.
- `harmonicId` — the end of a sequence of harmonics cannot be below its start.

**Example record**

~~~text
AxisymRingMomentLoad;10;5;1;1.;0.;2.E+3;0.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 10`, `ringId = 5`, `harmonicId = 1`, `scaleFactor = 1.`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId = 5`.

## AxisymTractionLoad

A surface traction on the side of an axisymmetric element ([ShellAxisym](elements.md#shellaxisym), [AxisymQuad](elements.md#axisymquad), [AxisymTria](elements.md#axisymtria), [AxisymTria6](elements.md#axisymtria6)).

**Record format and fields**

`AxisymTractionLoad;id;elemId;tractionA;tractionB;nodeA;nodeB;tractionAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `tractionA` | `real` | Required | Applied traction at the labeled position A. |
| 4 | `tractionB` | `real` | same as tractionA | Applied traction at the labeled position B. |
| 5 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 6 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 7 | `tractionAngle` | `real` | 0.0 | Orientation of the applied traction relative to its local reference. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `elemId` — the element ID must be a positive integer.
- `nodeA` — the grid point ID must be a positive integer.
- `nodeB` — the grid point ID must be a positive integer.

**Example record**

~~~text
AxisymTractionLoad;2;1;1.;0.5;13;19;30.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_axisymmetric_ploadx1.oos)

Reading the example gives `id = 2`, `elemId = 1`, `tractionA = 1.`, `tractionB = 0.5`.

**Referenced records in this example**

- [AxisymTria6](elements.md#axisymtria6) via `elemId = 1`.
- [Node](nodes.md#node) via `nodeA = 13`, `nodeB = 19`.

## Beam3DistributedLoad

A distributed load on a [Beam3](elements.md#beam3) element, over the whole length of the beam axis, along the line of the shear center.

**Record format and fields**

`Beam3DistributedLoad;id;elemId;frameId;directionX;directionY;directionZ;kind;scaleFactor;pressureA;pressureB;pressureC`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `frameId` | `any` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 5 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 6 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |
| 7 | `kind` | `text` | — | Selects the kind for Beam3DistributedLoad. |
| 8 | `scaleFactor` | `real` | — | Multiplier applied to the quantity specified by the entry. |
| 9 | `pressureA` | `real` | 0.0 | Pressure (force per area) at the labeled position A. |
| 10 | `pressureB` | `real` | 0.0 | Pressure (force per area) at the labeled position B. |
| 11 | `pressureC` | `real` | 0.0 | Pressure (force per area) at the labeled position C. |

Accepted words: `BasicFrame`, `Constant`, `Element`, `Force`, `LocalFrame`, `Moment`, `Table`, `WarpingBimoment`.

**Example record**

~~~text
Beam3DistributedLoad;18;301;;0.;0.;-1.;Force;1.;0.5;0.5;0.5
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 18`, `elemId = 301`, `directionX = 0.`, `directionY = 0.`.

## Beam3TemperatureLoad

The temperature field of the three-node beam element [Beam3](elements.md#beam3).

**Record format and fields**

`Beam3TemperatureLoad;id;elemId;temperatureA;temperatureB;temperatureC;gradientYA;gradientZA;gradientYB;gradientZB;gradientYC;gradientZC;temperatureCA;temperatureDA;temperatureEA;temperatureFA;temperatureCB;temperatureDB;temperatureEB;temperatureFB;temperatureCC;temperatureDC;temperatureEC;temperatureFC;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `temperatureA` | `real` | 0.0 | Temperature at the labeled position A. |
| 4 | `temperatureB` | `real` | 0.0 | Temperature at the labeled position B. |
| 5 | `temperatureC` | `real` | 0.0 | Temperature at the labeled position C. |
| 6 | `gradientYA` | `real` | 0.0 | Local y temperature gradient at the labeled position A. |
| 7 | `gradientZA` | `real` | 0.0 | Local z temperature gradient at the labeled position A. |
| 8 | `gradientYB` | `real` | 0.0 | Local y temperature gradient at the labeled position B. |
| 9 | `gradientZB` | `real` | 0.0 | Local z temperature gradient at the labeled position B. |
| 10 | `gradientYC` | `real` | 0.0 | Local y temperature gradient at the labeled position C. |
| 11 | `gradientZC` | `real` | 0.0 | Local z temperature gradient at the labeled position C. |
| 12 | `temperatureCA` | `real` | — | Temperature at the labeled position CA. |
| 13 | `temperatureDA` | `real` | — | Temperature at the labeled position DA. |
| 14 | `temperatureEA` | `real` | — | Temperature at the labeled position EA. |
| 15 | `temperatureFA` | `real` | — | Temperature at the labeled position FA. |
| 16 | `temperatureCB` | `real` | — | Temperature at the labeled position CB. |
| 17 | `temperatureDB` | `real` | — | Temperature at the labeled position DB. |
| 18 | `temperatureEB` | `real` | — | Temperature at the labeled position EB. |
| 19 | `temperatureFB` | `real` | — | Temperature at the labeled position FB. |
| 20 | `temperatureCC` | `real` | — | Temperature at the labeled position CC. |
| 21 | `temperatureDC` | `real` | — | Temperature at the labeled position DC. |
| 22 | `temperatureEC` | `real` | — | Temperature at the labeled position EC. |
| 23 | `temperatureFC` | `real` | — | Temperature at the labeled position FC. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `element` | `any` | — | Identifier of the element selected in this group. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
Beam3TemperatureLoad;20;301;80.;60.;70.;0.5;0.;0.5;0.;0.5;0.;82.5;82.5;77.5;77.5;62.5;62.5;57.5;57.5;72.5;72.5;67.5;67.5;302
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 20`, `elemId = 301`, `temperatureA = 80.`, `temperatureB = 60.`.

**Referenced records in this example**

- [Beam3](elements.md#beam3) via `elemId = 301`.

## BeamDistributedLoad

A concentrated or distributed load on a [Bar2](elements.md#bar2), [Beam2](elements.md#beam2) or [CurvedBeam2](elements.md#curvedbeam2) element.

**Record format and fields**

`BeamDistributedLoad;id;elemId;kind;scaleFactor;xCoord1;pressure1;xCoord2;pressure2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `kind` | `text` | — | Selects the kind for BeamDistributedLoad. |
| 4 | `scaleFactor` | `text` | — | Multiplier applied to the quantity specified by the entry. |
| 5 | `xCoord1` | `real` | Required | X coordinate of the location in the specified frame. Entry 1. |
| 6 | `pressure1` | `real` | Required | Normal force per unit area, in the model’s pressure units. Entry 1. |
| 7 | `xCoord2` | `real` | same as xCoord1 | X coordinate of the location in the specified frame. Entry 2. |
| 8 | `pressure2` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 2. |

Accepted words: `ActualLength`, `ForceX`, `ForceXAlongLength`, `ForceY`, `ForceYAlongLength`, `ForceZ`, `ForceZAlongLength`, `FractionalLength`, `FractionalProjectedLength`, `MomentX`, `MomentXAlongLength`, `MomentY`, `MomentYAlongLength`, `MomentZ`, `MomentZAlongLength`, `ProjectedLength`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `elemId` — the element ID must be a positive integer.

**Example record**

~~~text
BeamDistributedLoad;1;1401;ForceZ;FractionalLength;0.;0.2;1.;0.2
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1`, `elemId = 1401`, `kind = ForceZ`, `scaleFactor = FractionalLength`.

## CyclicAzimuthTableLoad

Loads of an axisymmetric cyclic model as a function of the azimuth angle, from a table of scale factors and a load set (two pairs at most).

**Record format and fields**

`CyclicAzimuthTableLoad;id;tableId1;loadSetId1;methodName1;tableId2;loadSetId2;methodName2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `tableId1` | `integer` | Required | Identifier addressing dynamic table data. |
| 3 | `loadSetId1` | `integer` | Required | Identifier addressing load combination set data. |
| 4 | `methodName1` | `integer` | 0 | Text naming the method. |
| 5 | `tableId2` | `integer` | Required | Identifier addressing dynamic table data. |
| 6 | `loadSetId2` | `integer` | Required | Identifier addressing load combination set data. |
| 7 | `methodName2` | `integer` | 0 | Text naming the method. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `tableId1` — the table ID must be a positive integer.
- `loadSetId1` — the load set ID must be a positive integer.
- `tableId2` — the table ID cannot be negative.
- `loadSetId2` — the load set ID cannot be negative.

**Example record**

~~~text
CyclicAzimuthTableLoad;10;19;31;1
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_axi_table_load_sol114.oos)

Reading the example gives `id = 10`, `tableId1 = 19`, `loadSetId1 = 31`, `methodName1 = 1`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `tableId1 = 19`.

## CyclicHarmonicLoad

The harmonic coefficients of a static or dynamic load of a cyclic symmetry model.

**Record format and fields**

`CyclicHarmonicLoad;id;scaleFactor;harmonicId;harmonicType;scaleFactor1;loadSetId1;scaleFactor2;loadSetId2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 3 | `harmonicId` | `integer` | — | Identifier selecting the harmonic record or set. |
| 4 | `harmonicType` | `text` | — | Selects the harmonic type for CyclicHarmonicLoad. |
| 5 | `scaleFactor1` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 1. |
| 6 | `loadSetId1` | `integer` | Required | Identifier addressing excitation set data. |
| 7 | `scaleFactor2` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 2. |
| 8 | `loadSetId2` | `integer` | Required | Identifier addressing excitation set data. |

Accepted words: `Constant`, `Cosine`, `CyclicStar`, `Element`, `GravityLoad`, `RotationalForceLoad`, `Sine`, `SymmetricStar`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `harmonicId` — the harmonic cannot be negative.

**Example record**

~~~text
CyclicHarmonicLoad;10;1.;0;Cosine;1.;11
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_rot_buckling_sol116.oos)

Reading the example gives `id = 10`, `scaleFactor = 1.`, `harmonicId = 0`, `harmonicType = Cosine`.

## CyclicSegmentLoad

A physical load on a segment of a cyclic symmetry model, from one or two load sets.

**Record format and fields**

`CyclicSegmentLoad;id;scaleFactor;segmentId;segmentType;scaleFactor1;loadSetId1;scaleFactor2;loadSetId2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 3 | `segmentId` | `integer` | Required | Identifier selecting the segment record or set. |
| 4 | `segmentType` | `text` | — | Selects the segment type for CyclicSegmentLoad. |
| 5 | `scaleFactor1` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 1. |
| 6 | `loadSetId1` | `integer` | Required | Identifier addressing excitation set data. |
| 7 | `scaleFactor2` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 2. |
| 8 | `loadSetId2` | `integer` | Required | Identifier addressing excitation set data. |

Accepted words: `Left`, `Right`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.

**Example record**

~~~text
CyclicSegmentLoad;30;1.;1;;1.;31
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_rot_frequency_sol118.oos)

Reading the example gives `id = 30`, `scaleFactor = 1.`, `segmentId = 1`, `scaleFactor1 = 1.`.

## DefaultTemperatureLoad

Assigns a default temperature to nodes in a load set. A [NodeTemperatureLoad](loads.md#nodetemperatureload) in the same set overrides it at its node.

**Record format and fields**

`DefaultTemperatureLoad;id1;temperature1;id2;temperature2;id3;temperature3;id4;temperature4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered DefaultTemperatureLoad data. |
| 2 | `temperature1` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 1. |
| 3 | `id2` | `integer` | — | Identifier at position 2 in the ordered DefaultTemperatureLoad data. |
| 4 | `temperature2` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 2. |
| 5 | `id3` | `integer` | — | Identifier at position 3 in the ordered DefaultTemperatureLoad data. |
| 6 | `temperature3` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 3. |
| 7 | `id4` | `integer` | — | Identifier at position 4 in the ordered DefaultTemperatureLoad data. |
| 8 | `temperature4` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.

**Example record**

~~~text
DefaultTemperatureLoad;2;20.
~~~

[Model containing this record](../../../validation/models/linear_elements/heat_capacity_transient.oos)

Reading the example gives `id1 = 2`, `temperature1 = 20.`.

## FacePressureLoad

A pressure on a face of a shell or solid element, or on a range of shell elements.

**Record format and fields**

`FacePressureLoad;id;elemId;pressure1;pressure2;pressure3;pressure4;node1;node3Or4OrElemId2;frameId;directionX;directionY;directionZ;surfaceOrLine;lineLoadDirection`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `pressure1` | `real` | 0.0 | Normal force per unit area, in the model’s pressure units. Entry 1. |
| 4 | `pressure2` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 2. |
| 5 | `pressure3` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 3. |
| 6 | `pressure4` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 4. |
| 7 | `node1` | `any` | 0 | Identifier addressing node data. |
| 8 | `node3Or4OrElemId2` | `integer` | — | Identifier selecting the node 3 or 4 or element record or set. |
| 9 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 10 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 11 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 12 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |
| 13 | `surfaceOrLine` | `text` | — | Selects whether the load is distributed over a face or along a line. |
| 14 | `lineLoadDirection` | `text` | — | Direction in which the distributed line load acts. |

*Note*: node1 and node3Or4OrElemId2 name the loaded face of a solid element: two diagonally opposite corners of a quadrilateral face (SolidHexa, SolidPenta, the base of a SolidPyramid); the two corners of the edge that a triangular face of a SolidPyramid has on the base; node1 alone for a triangular face of a SolidPenta; for a SolidTetra, node1 a corner of the face and the other the corner that is not on it.

Accepted words: `Line`, `Norm`, `Surface`, `Tangent`, `Through`, `XDirection`, `YDirection`, `ZDirection`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `elemId` — the element ID must be a positive integer.
- `frameId` — the coordinate system ID cannot be negative.

**Example record**

~~~text
FacePressureLoad;1;201;0.1;0.2;0.3;0.4
~~~

[Model containing this record](../../../validation/models/results_static/static_pload4_forms.oos)

Reading the example gives `id = 1`, `elemId = 201`, `pressure1 = 0.1`, `pressure2 = 0.2`.

**Referenced records in this example**

- [ShellQuad4](elements.md#shellquad4) via `elemId = 201`.

## FreeBodyLoad

An equilibrated free-body applied load case.

**Record format and fields**

`FreeBodyLoad;name;subsystemName;label`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `name` | `text` | — | The name of the load case. |
| 2 | `subsystemName` | `text` | — | Text naming the subsystem. |
| 3 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |

**Example record**

~~~text
FreeBodyLoad;TIPLD;SBTIP;tip bay free-body load
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `name = TIPLD`, `subsystemName = SBTIP`, `label = tip bay free-body load`.

## FreeBodyLoadSubcase

An equilibrated free-body subsystem.

**Record format and fields**

`FreeBodyLoadSubcase;names;nodeSetId;elementSetId;excludedForces;label`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `names` | `text` | — | Text labels included in this selection. |
| 2 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 3 | `elementSetId` | `integer` | 0 | Identifier addressing set data. |
| 4 | `excludedForces` | `text` | — | Force contributions to omit from the requested result. |
| 5 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FreeBodyLoadSubcase;SBTIP;1801;1802;;tip bay of the plate
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `names = SBTIP`, `nodeSetId = 1801`, `elementSetId = 1802`, `label = tip bay of the plate`.

## GravityLoad

An acceleration (gravity) load.

**Record format and fields**

`GravityLoad;id;frameId;magnitude;directionX;directionY;directionZ;mainBulkFlag`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 5 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 6 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |
| 7 | `mainBulkFlag` | `integer` | 0 | Selects the main bulk flag for GravityLoad. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `frameId` — the coordinate system ID cannot be negative.

**Example record**

~~~text
GravityLoad;99;0;9810.;0.;0.;-1.
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_bent_sol400.oos)

Reading the example gives `id = 99`, `frameId = 0`, `magnitude = 9810.`, `directionX = 0.`.

## HeatShellInitialTemperature

The initial temperature of the grid points of heat shell elements (those of a [ShellPropNonlinear](properties.md#shellpropnonlinear) heat transfer property) with a linear or quadratic temperature distribution across the thickness.

**Record format and fields**

`HeatShellInitialTemperature;id;node1;components1;temperature1;node2;components2;temperature2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | — | Identifier addressing node data. |
| 3 | `components1` | `integer` | 1 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `temperature1` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 1. |
| 5 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 6 | `components2` | `integer` | 1 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `temperature2` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1` — the card needs at least one grid point.
- `node2` — the card gives the temperatures of at most two grid points.

**Example record**

~~~text
HeatShellInitialTemperature;10;3;12;60.;13;12;60.
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_heat_shell_tempn1.oos)

Reading the example gives `id = 10`, `node1 = 3`, `components1 = 12`, `temperature1 = 60.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 3`.

## HydrostaticCavityLoad

A hydrostatic pressure load on the faces of shell and solid elements that are wetted by a fluid cavity.

**Record format and fields**

`HydrostaticCavityLoad;id;propId;nominalPressure;gravity;punchOption;punchPressureLoads;overrideOption;frameOrNode;baseHeight;heightAbove`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `nominalPressure` | `real` | 0.0 | Nominal pressure (force per area). |
| 4 | `gravity` | `real` | 1.0 | Acceleration of gravity used by the definition, in length per time squared. |
| 5 | `punchOption` | `integer` | 0 | Selects the punch option for HydrostaticCavityLoad. |
| 6 | `punchPressureLoads` | `integer` | 0 | Controls output of the generated pressure-load records. |
| 7 | `overrideOption` | `integer` | 0 | Selects the override option for HydrostaticCavityLoad. |
| 8 | `frameOrNode` | `integer` | — | Selects the coordinate system or grid point used to define the load direction. |
| 9 | `baseHeight` | `real` | 0.0 | Reference elevation from which the loading height is measured. |
| 10 | `heightAbove` | `real` | 0.0 | Distance above the reference elevation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
HydrostaticCavityLoad;301;2;0.;9810.;;;;0;0.;100.
~~~

[Model containing this record](../../../validation/models/linear_loads/freq_lseq_hydroc.oos)

Reading the example gives `id = 301`, `propId = 2`, `nominalPressure = 0.`, `gravity = 9810.`.

**Referenced records in this example**

- [SolidProp](properties.md#solidprop) via `propId = 2`.

## HydrostaticLoad

Applies hydrostatic pressure to selected shell or solid faces using the specified fluid density and reference elevation.

**Record format and fields**

`HydrostaticLoad;id;nominalPressure;density;gravity;elementSetId;nodeSetId;punchPressureLoads;overrideOption;frameOrNode;baseHeight;heightAbove;controlNodeSetId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nominalPressure` | `real` | 0.0 | Nominal pressure (force per area). |
| 3 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 4 | `gravity` | `real` | 1.0 | Acceleration of gravity used by the definition, in length per time squared. |
| 5 | `elementSetId` | `integer` | 0 | Identifier addressing set data. |
| 6 | `nodeSetId` | `integer` | 0 | Identifier of the set supplying the grid points. |
| 7 | `punchPressureLoads` | `integer` | 0 | Controls output of the generated pressure-load records. |
| 8 | `overrideOption` | `integer` | 0 | Selects the override option for HydrostaticLoad. |
| 9 | `frameOrNode` | `integer` | — | Selects the coordinate system or grid point used to define the load direction. |
| 10 | `baseHeight` | `real` | 0.0 | Reference elevation from which the loading height is measured. |
| 11 | `heightAbove` | `real` | 0.0 | Distance above the reference elevation. |
| 12 | `controlNodeSetId` | `integer` | 0 | Identifier addressing set data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
HydrostaticLoad;17;;1.E-9;9810.;1701;;;;0;0.;500.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 17`, `density = 1.E-9`, `gravity = 9810.`, `elementSetId = 1701`.

## ImperfectionCase

A collection of imperfections.

**Record format and fields**

`ImperfectionCase;id;<imperfections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `imperfections`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `imperfectionId` | `any` | — | Identifier selecting the imperfection record or set. |

Accepted words: `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
ImperfectionCase;5;1;2
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_imperfect_heated_strip.oos)

Reading the example gives `id = 5`.

## ImperfectionGeometry

The definition of a geometric imperfection, an ID that an [ImperfectionCase](loads.md#imperfectioncase) names.

**Record format and fields**

`ImperfectionGeometry;id;nodeSetId;scaleFactor;fileUnit;moduleId;<subcases>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `nodeSetId` | `integer` | 0 | Identifier of the set supplying the grid points. |
| 3 | `scaleFactor` | `real` | 0.0 | Multiplier applied to the quantity specified by the entry. |
| 4 | `fileUnit` | `integer` | 0 | The default of UNITi, 0 or above. |
| 5 | `moduleId` | `integer` | -1 | Identifier selecting the module record or set. |

**Repeated group `subcases`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `subcase` | `integer` | — | Identifier of the load case to which the data apply. |
| 2 | `step` | `integer` | — | The step of the result, 0 or above. |
| 3 | `modeIncrement` | `integer` | — | The mode (buckling, modal) or the increment (static), 0 or above. |
| 4 | `subcaseNodeSetId` | `integer` | — | Identifier selecting the subcase node set record or set. |
| 5 | `subcaseScaleFactor` | `real` | — | Multiplier for subcase scale. |
| 6 | `subcaseFileUnit` | `integer` | — | Logical file unit associated with the subcase data. |
| 7 | `subcaseModuleId` | `integer` | — | Identifier selecting the subcase module record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ImperfectionGeometry;1;;;;;;;;101;1.;31
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_imperfect_heated_strip.oos)

Reading the example gives `id = 1`.

## InflatorInlet

One inflator that blows into a gas bag ([GasBag](explicit.md#gasbag)) or an Euler coupling surface ([EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling)), on a part of their surface.

**Record format and fields**

`InflatorInlet;id;inflatorId;subsurfaceId;inflatorKind;inflatorKindId;areaCoefficientSource;areaCoefficient`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `inflatorId` | `integer` | Required | Identifier selecting the inflator record or set. |
| 3 | `subsurfaceId` | `integer` | Required | Identifier selecting the subsurface record or set. |
| 4 | `inflatorKind` | `text` | — | Selects the inflator kind for InflatorInlet. |
| 5 | `inflatorKindId` | `integer` | Required | Identifier selecting the inflator kind record or set. |
| 6 | `areaCoefficientSource` | `text` | — | Selects how the effective-area coefficient is supplied. |
| 7 | `areaCoefficient` | `any` | — | Coefficient in the relation for area. |

Accepted words: `ColdGasInflator`, `Constant`, `Element`, `HybridInflator`, `StandardInflator`, `Table`, `TankTestInflator`.

**Example record**

~~~text
InflatorInlet;2;21;202;HybridInflator;2;Constant;1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 2`, `inflatorId = 21`, `subsurfaceId = 202`, `inflatorKind = HybridInflator`.

## LineElemTemperatureLoad

The temperature field of one-dimensional elements ([Bar2](elements.md#bar2), [Beam2](elements.md#beam2), [CurvedBeam2](elements.md#curvedbeam2), [Rod2](elements.md#rod2), [Tube2](elements.md#tube2), [Rod2InlineSection](elements.md#rod2inlinesection)).

**Record format and fields**

`LineElemTemperatureLoad;id;elemId1;temperatureA;temperatureB;gradientYA;gradientYB;gradientZA;gradientZB;temperatureCA;temperatureDA;temperatureEA;temperatureFA;temperatureCB;temperatureDB;temperatureEB;temperatureFB;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId1` | `integer` | Required | Identifier of the element addressed by this record. Entry 1. |
| 3 | `temperatureA` | `real` | 0.0 | Temperature at the labeled position A. |
| 4 | `temperatureB` | `real` | 0.0 | Temperature at the labeled position B. |
| 5 | `gradientYA` | `real` | 0.0 | Local y temperature gradient at the labeled position A. |
| 6 | `gradientYB` | `real` | 0.0 | Local y temperature gradient at the labeled position B. |
| 7 | `gradientZA` | `real` | 0.0 | Local z temperature gradient at the labeled position A. |
| 8 | `gradientZB` | `real` | 0.0 | Local z temperature gradient at the labeled position B. |
| 9 | `temperatureCA` | `real` | — | Temperature at the labeled position CA. |
| 10 | `temperatureDA` | `real` | — | Temperature at the labeled position DA. |
| 11 | `temperatureEA` | `real` | — | Temperature at the labeled position EA. |
| 12 | `temperatureFA` | `real` | — | Temperature at the labeled position FA. |
| 13 | `temperatureCB` | `real` | — | Temperature at the labeled position CB. |
| 14 | `temperatureDB` | `real` | — | Temperature at the labeled position DB. |
| 15 | `temperatureEB` | `real` | — | Temperature at the labeled position EB. |
| 16 | `temperatureFB` | `real` | — | Temperature at the labeled position FB. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.
- `elemId1` — the card needs at least one element.

**Example record**

~~~text
LineElemTemperatureLoad;20;201;80.;60.;0.5;0.5;0.;0.;82.5;82.5;77.5;77.5;62.5;62.5;57.5;57.5;202;203
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 20`, `elemId1 = 201`, `temperatureA = 80.`, `temperatureB = 60.`.

## LoadCaseIdLabel

Combines part loads selected by the load ID used to generate each part subcase.

**Record format and fields**

`LoadCaseIdLabel;id;scaleFactor;<items>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

**Repeated group `items`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `itemScaleFactor` | `real` | — | Multiplier for item scale. |
| 2 | `loadId` | `integer` | — | Identifier selecting the load record or set. |
| 3 | `partName` | `text` | — | Text naming the part. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
LoadCaseIdLabel;1001;1.;1.;101;wing_part;0.5;301;tail_part
~~~

[Model containing this record](../../../validation/models/read_only_loads/paa_load_combinations.oos)

Reading the example gives `id = 1001`, `scaleFactor = 1.`.

## LoadCaseNameLabel

Combines part loads selected by their case-control load names.

**Record format and fields**

`LoadCaseNameLabel;id;scaleFactor;<items>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

**Repeated group `items`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `itemScaleFactor` | `real` | — | Multiplier for item scale. |
| 2 | `loadName` | `text` | — | Text naming the load. Written as one text field. |
| 3 | `partName` | `text` | — | Text naming the part. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
LoadCaseNameLabel;1002;1.;1.;gravity_z;wing_part;1.5;gravity_z;tail_part
~~~

[Model containing this record](../../../validation/models/read_only_loads/paa_load_combinations.oos)

Reading the example gives `id = 1002`, `scaleFactor = 1.`.

## LoadCaseSubcaseLabel

Combines loads from different parts by selecting a subcase in each part.

**Record format and fields**

`LoadCaseSubcaseLabel;id;scaleFactor;<items>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

**Repeated group `items`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `itemScaleFactor` | `real` | — | Multiplier for item scale. |
| 2 | `subcase` | `integer` | — | Identifier of the load case to which the data apply. |
| 3 | `partName` | `text` | — | Text naming the part. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
LoadCaseSubcaseLabel;1003;2.;1.;2;wing_part;-1.;1;tail_part
~~~

[Model containing this record](../../../validation/models/read_only_loads/paa_load_combinations.oos)

Reading the example gives `id = 1003`, `scaleFactor = 2.`.

## LoadCombination

A static load made of other load sets, combined linearly.

**Record format and fields**

`LoadCombination;id;scaleFactor;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `termScaleFactor` | `real` | — | Multiplier for term scale. |
| 2 | `loadSetId` | `integer` | — | Identifier selecting the load set record or set. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `scaleFactor1` — the card needs at least one load set.
- `loadSetId1` — a load set ID must be a positive integer.
- `loadSetId1` — the card cannot refer to its own set ID.

**Example record**

~~~text
LoadCombination;3;1.;2.;1;1.;2
~~~

[Model containing this record](../../../validation/models/results_static/static_elements_sort2.oos)

Reading the example gives `id = 3`, `scaleFactor = 1.`.

## MetadataBooleanPairs

Stores boolean name/value pairs belonging to a [MetadataGroup](loads.md#metadatagroup).

**Record format and fields**

`MetadataBooleanPairs;metadataGroupId;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataGroupId` | `integer` | Required | Identifier selecting the metadata group record or set. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `entryValue` | `text` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `False`, `Table`, `True`.

**Example record**

~~~text
MetadataBooleanPairs;60;STIFFNER;False
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `metadataGroupId = 60`.

## MetadataGroup

Entities of one kind added to a named group of the meta data written to the results files (it has no effect on the solution).

**Record format and fields**

`MetadataGroup;metadataGroupName;id;entityName;<entities>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataGroupName` | `text` | — | Text naming the metadata group. |
| 2 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 3 | `entityName` | `text` | — | Text naming the entity. |

**Repeated group `entities`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entityId` | `integer` | — | Identifier selecting the entity record or set. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the group ID must be a positive integer.
- `entityId1` — the card needs at least one entity ID.
- `entityId1` — an entity ID must be a positive integer.

**Example record**

~~~text
MetadataGroup;PLATE;60;ShellQuad4;101;102;103;104;105;106;107
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `metadataGroupName = PLATE`, `id = 60`, `entityName = ShellQuad4`.

## MetadataIntegerPairs

Stores integer name/value pairs belonging to a [MetadataGroup](loads.md#metadatagroup).

**Record format and fields**

`MetadataIntegerPairs;metadataGroupId;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataGroupId` | `integer` | Required | Identifier selecting the metadata group record or set. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `entryValue` | `integer` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MetadataIntegerPairs;60;NELEM;9
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `metadataGroupId = 60`.

## MetadataRealPairs

Stores real name/value pairs belonging to a [MetadataGroup](loads.md#metadatagroup).

**Record format and fields**

`MetadataRealPairs;metadataGroupId;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataGroupId` | `integer` | Required | Identifier selecting the metadata group record or set. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `entryValue` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MetadataRealPairs;60;THICK;2.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `metadataGroupId = 60`.

## MetadataTextPairs

Stores text name/value pairs belonging to a [MetadataGroup](loads.md#metadatagroup).

**Record format and fields**

`MetadataTextPairs;metadataGroupId;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataGroupId` | `integer` | Required | Identifier selecting the metadata group record or set. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `entryValue` | `text` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MetadataTextPairs;60;ABSNAME;cantilever_plate;ABSDESC;plate_of_seven_quads_and_two_trias
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `metadataGroupId = 60`.

## NodeTemperatureLoad

The temperatures of some grid points.

**Record format and fields**

`NodeTemperatureLoad;id;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `temperature` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.
- `node1` — the card needs at least one grid point.
- `node1` — a grid point ID must be a positive integer.

**Example record**

~~~text
NodeTemperatureLoad;20;405;150.;406;150.;407;150.
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 20`.

## PlateTemperatureLoad

The temperature field of plate, membrane and composite elements, as an average temperature and a gradient through the thickness.

**Record format and fields**

`PlateTemperatureLoad;id;elemId1;meanTemperature;temperatureGradient;temperature1;temperature2;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId1` | `integer` | Required | Identifier of the element addressed by this record. Entry 1. |
| 3 | `meanTemperature` | `real` | 0.0 | Mean temperature (temperature). |
| 4 | `temperatureGradient` | `real` | 0.0 | Change of temperature per unit distance. |
| 5 | `temperature1` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 1. |
| 6 | `temperature2` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. Entry 2. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.
- `elemId1` — the card needs at least one element.

**Example record**

~~~text
PlateTemperatureLoad;20;101;80.;0.5;;;102;Through;109
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 20`, `elemId1 = 101`, `meanTemperature = 80.`, `temperatureGradient = 0.5`.

## PointForceLoad

A concentrated force at a grid point.

**Record format and fields**

`PointForceLoad;id;node;frameId;magnitude;directionX;directionY;directionZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Load-set ID, selected by case control or a load combination. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `frameId` | `integer` | 0 | Frame for the force components. Zero uses the basic system. |
| 4 | `magnitude` | `real` | Required | Force scale multiplying the three direction components, in force units. |
| 5 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 6 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 7 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `frameId` — the coordinate system ID cannot be negative.

**Example record**

~~~text
PointForceLoad;1;3;;1.;0.;0.;1.
~~~

[Model containing this record](../../../validation/models/card_namespaces/namespace_aefact_twice.oos)

Reading the example gives `id = 1`, `node = 3`, `magnitude = 1.`, `directionX = 0.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 3`.

## PointForceLoad1

A concentrated force at a grid point whose direction is the line from G1 to G2.

**Record format and fields**

`PointForceLoad1;id;node;magnitude;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `node1` | `integer` | Required | Identifier addressing node data. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.

**Example record**

~~~text
PointForceLoad1;11;15;100.;13;15
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 11`, `node = 15`, `magnitude = 100.`, `node1 = 13`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 15`, `node1 = 13`, `node2 = 15`.

## PointForceLoad2

A concentrated force at a grid point whose direction is the cross product of the vector from G1 to G2 with the vector from G3 to G4.

**Record format and fields**

`PointForceLoad2;id;node;magnitude;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `node1` | `integer` | Required | Identifier addressing node data. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |
| 6 | `node3` | `integer` | Required | Identifier addressing node data. |
| 7 | `node4` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.
- `node3` — the grid point ID must be a positive integer.
- `node4` — the grid point ID must be a positive integer.

**Example record**

~~~text
PointForceLoad2;11;14;50.;13;14;13;10
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 11`, `node = 14`, `magnitude = 50.`, `node1 = 13`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 14`, `node1 = 13`, `node2 = 14`, `node3 = 13`, `node4 = 10`.

## PointMomentLoad

A concentrated moment at a grid point.

**Record format and fields**

`PointMomentLoad;id;node;frameId;magnitude;directionX;directionY;directionZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 5 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 6 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 7 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

Accepted words: `HingeMomentClass`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `frameId` — the coordinate system ID cannot be negative.

**Example record**

~~~text
PointMomentLoad;1;12;;100.;1.;0.;0.
~~~

[Model containing this record](../../../validation/models/sections/sections_model.oos)

Reading the example gives `id = 1`, `node = 12`, `magnitude = 100.`, `directionX = 1.`.

## PointMomentLoad1

A concentrated moment at a grid point whose axis is the line from G1 to G2.

**Record format and fields**

`PointMomentLoad1;id;node;magnitude;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `node1` | `integer` | Required | Identifier addressing node data. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.

**Example record**

~~~text
PointMomentLoad1;11;15;1.E+3;1;13
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 11`, `node = 15`, `magnitude = 1.E+3`, `node1 = 1`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 15`, `node1 = 1`, `node2 = 13`.

## PointMomentLoad2

A concentrated moment at a grid point whose axis is the cross product of the vector from G1 to G2 with the vector from G3 to G4.

**Record format and fields**

`PointMomentLoad2;id;node;magnitude;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `magnitude` | `real` | Required | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 4 | `node1` | `integer` | Required | Identifier addressing node data. |
| 5 | `node2` | `integer` | Required | Identifier addressing node data. |
| 6 | `node3` | `integer` | Required | Identifier addressing node data. |
| 7 | `node4` | `integer` | Required | Identifier addressing node data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID must be a positive integer.
- `node1` — the grid point ID must be a positive integer.
- `node2` — the grid point ID must be a positive integer.
- `node3` — the grid point ID must be a positive integer.
- `node4` — the grid point ID must be a positive integer.

**Example record**

~~~text
PointMomentLoad2;11;13;500.;1;2;1;4
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 11`, `node = 13`, `magnitude = 500.`, `node1 = 1`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 13`, `node1 = 1`, `node2 = 2`, `node3 = 1`, `node4 = 4`.

## PointsPressureLoad

A uniform pressure on the triangle or quadrilateral defined by three or four grid points.

**Record format and fields**

`PointsPressureLoad;id;pressure;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `pressure` | `real` | Required | Normal force per unit area, in the model’s pressure units. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | Required | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | 0 | Grid point to which this entry applies. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.

**Example record**

~~~text
PointsPressureLoad;12;0.05;4;5;8;7
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 12`, `pressure = 0.05`, `node1 = 4`, `node2 = 5`.

## RotationalForceLoad

A static load from an angular velocity and/or an angular acceleration about an axis.

**Record format and fields**

`RotationalForceLoad;id;node;frameId;magnitude;radius1;radius2;radius3;methodName;angularAcceleration;mainBulkFlag;regionId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | 0 | Grid point to which this entry applies. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `magnitude` | `real` | 0.0 | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |
| 5 | `radius1` | `real` | 0.0 | Radial dimension measured from the centre or axis (length). Entry 1. |
| 6 | `radius2` | `real` | 0.0 | Radial dimension measured from the centre or axis (length). Entry 2. |
| 7 | `radius3` | `real` | 0.0 | Radial dimension measured from the centre or axis (length). Entry 3. |
| 8 | `methodName` | `integer` | 1 | Text naming the method. |
| 9 | `angularAcceleration` | `real` | 0.0 | Angular acceleration (length per time squared). |
| 10 | `mainBulkFlag` | `integer` | 0 | Selects the main bulk flag for RotationalForceLoad. |
| 11 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — the grid point ID cannot be negative.
- `frameId` — the coordinate system ID cannot be negative.

**Example record**

~~~text
RotationalForceLoad;14;1;;5.;0.;0.;1.;2;1.
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `id = 14`, `node = 1`, `magnitude = 5.`, `radius1 = 0.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node = 1`.

## ScalarPointLoad

Concentrated static loads on scalar or grid points.

**Record format and fields**

`ScalarPointLoad;id;<loads>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `loads`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `scalarPoint` | `integer` | — | Identifier addressing scalar or grid point data. |
| 2 | `magnitude` | `real` | — | Scale of the quantity applied by this record. Its units follow the load or displacement being specified. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `scalarPoint1` — the card needs at least one load.
- `scalarPoint3` — the card defines at most three loads.
- `scalarPoint1` — a scalar or grid point ID must be a positive integer.

**Example record**

~~~text
ScalarPointLoad;1;1803;5.
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1`.

## ShellPressureLoad

A uniform pressure normal to a list of shell elements ([ShellQuad4](elements.md#shellquad4), [ShearPanel4](elements.md#shearpanel4), [ShellTria3](elements.md#shelltria3)).

**Record format and fields**

`ShellPressureLoad;id;pressure;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `pressure` | `real` | Required | Normal force per unit area, in the model’s pressure units. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `elemId1` — the card needs at least one element.

**Example record**

~~~text
ShellPressureLoad;1;2.5;1;Through;50
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol101_shape_basis.oos)

Reading the example gives `id = 1`, `pressure = 2.5`.

## StaticLoadSequence

Defines the static load vectors used as the spatial basis of a dynamic load.

**Record format and fields**

`StaticLoadSequence;id;excitationId;loadId;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier addressing excitation defined data. |
| 3 | `loadId` | `integer` | 0 | Identifier addressing load combination set data. |
| 4 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `excitationId` — the excitation set ID must be a positive integer.
- `loadId` — the load set ID cannot be negative.
- `tableId` — the temperature set ID cannot be negative.

**Example record**

~~~text
StaticLoadSequence;10;100;200
~~~

[Model containing this record](../../../validation/models/aero_models/sol106_superelement_cload.oos)

Reading the example gives `id = 10`, `excitationId = 100`, `loadId = 200`.

## SuperelementLoadCombination

A static load that combines the load vectors the [StaticLoadSequence](loads.md#staticloadsequence) cards define for a superelement.

**Record format and fields**

`SuperelementLoadCombination;id;scaleFactor;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `termScaleFactor` | `real` | — | Multiplier for term scale. |
| 2 | `loadId` | `integer` | — | Identifier selecting the load record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SuperelementLoadCombination;25;1.;2.;100
~~~

[Model containing this record](../../../validation/models/aero_models/sol106_superelement_cload.oos)

Reading the example gives `id = 25`, `scaleFactor = 1.`.

## TemperatureTimeGroup

A group of grid points that share one time function.

**Record format and fields**

`TemperatureTimeGroup;id;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node` — the card needs at least one grid point.

**Example record**

~~~text
TemperatureTimeGroup;101;1;Through;9
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_imperfect_heated_strip.oos)

Reading the example gives `id = 101`.

## TimeTemperatureLoad

Defines a temperature history by combining a spatial temperature field with a time-dependent scale.

**Record format and fields**

`TimeTemperatureLoad;id;groupId;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `groupId` | `integer` | Required | Identifier addressing temperature group data. |
| 3 | `tableId` | `integer` | Required | Identifier of the tabulated function to evaluate. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TimeTemperatureLoad;11;101;31
~~~

[Model containing this record](../../../validation/models/linear_loads/sol400_imperfect_heated_strip.oos)

Reading the example gives `id = 11`, `groupId = 101`, `tableId = 31`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `tableId = 31`.

## WettedSurfaceLoad

The load set that stands for an external fluid-structure service, with the wetted surface the service loads.

**Record format and fields**

`WettedSurfaceLoad;id;wettedSurfaceId;serviceName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `wettedSurfaceId` | `integer` | Required | Identifier selecting the wetted surface record or set. |
| 3 | `serviceName` | `text` | — | Text naming the service. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
WettedSurfaceLoad;30;1;fsisvc
~~~

[Model containing this record](../../../validation/models/read_only_thermal_acoustic/fsi_wetted_surface_sol400.oos)

Reading the example gives `id = 30`, `wettedSurfaceId = 1`, `serviceName = fsisvc`.
