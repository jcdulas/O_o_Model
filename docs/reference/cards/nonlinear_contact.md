# Nonlinear analysis and contact

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## BoltConnection

Represents a bolt cut by tying pairs of grid points on opposite sides to a common control node. A force or prescribed motion at this node applies pretension.

**Record format and fields**

`BoltConnection;id;controlNode;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `controlNode` | `integer` | Required | Identifier of the grid point through which this definition is controlled. |

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

Accepted words: `Bottom`, `Top`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `topNodes` — a grid point ID must be a positive integer.
- `bottomNodes` — a grid point ID must be a positive integer.

**Example record**

~~~text
BoltConnection;1;999;Top;4;305;307;306;308;Bottom;4;401;403;402;404
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_contact_bolt.oos)

Reading the example gives `id = 1`, `controlNode = 999`.

## BoltPretension

Defines a bolt pretension section through a layer of elements. An axial force or displacement at the control node loads the section.

**Record format and fields**

`BoltPretension;id;controlNode;form;directionX;directionY;directionZ;offset;idType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `controlNode` | `integer` | Required | Identifier of the grid point through which this definition is controlled. |
| 3 | `form` | `integer` | 0 | Selects the form for BoltPretension. |
| 4 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 5 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 6 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |
| 7 | `offset` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. |
| 8 | `idType` | `text` | List | Selects the ID type for BoltPretension. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Elems`**

**Repeated group `elements`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `element` | `integer` | — | Identifier of the element selected in this group. |

**Section `Nodes`**

**Repeated group `nodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |

Accepted words: `Elems`, `List`, `Nodes`, `Set`, `TypedListSet3`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `elements` — an element ID must be a positive integer.
- `nodes` — a grid point ID must be a positive integer.
- `elements` — the bolt needs elements.

**Example record**

~~~text
BoltPretension;1;1001;0;;;;0.;List;Elems;4;1;2;3;4
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_bolt1_pretension.oos)

Reading the example gives `id = 1`, `controlNode = 1001`, `form = 0`, `offset = 0.`.

## BrakeMotion

The motion direction of a body of a brake system, which a [BrakeSystem](nonlinear_contact.md#brakesystem) names (MT1_ID, MT2_ID).

**Record format and fields**

`BrakeMotion;id;velocity;form;cosineX;cosineY;cosineZ;xCoord;yCoord;zCoord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `velocity` | `real` | 0.0 | Rate of displacement in the specified direction (length per time). |
| 3 | `form` | `text` | — | Selects the form for BrakeMotion. |
| 4 | `cosineX` | `real` | 0.0 | Direction cosines. |
| 5 | `cosineY` | `real` | 0.0 | Direction cosine relative to axis Y. |
| 6 | `cosineZ` | `real` | 0.0 | Direction cosine relative to axis Z. |
| 7 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 8 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 9 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |

Accepted words: `Constant`, `Element`, `RotationMotion`, `Table`, `TranslationMotion`.

**Example record**

~~~text
BrakeMotion;42;1.E+3;TranslationMotion;0.;1.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_brake_squeal.oos)

Reading the example gives `id = 42`, `velocity = 1.E+3`, `form = TranslationMotion`, `cosineX = 0.`.

## BrakeProp

The property of a brake system for the brake squeal analysis, named by a [BrakeSystem](nonlinear_contact.md#brakesystem).

**Record format and fields**

`BrakeProp;id;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `number` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `AverageStiffnessMethod`, `Constant`, `Element`, `Friction`, `Table`, `TemperatureAverageStiffness`.

**Example record**

~~~text
BrakeProp;1;AverageStiffnessMethod;1.E+5;Friction;0.3
~~~

[Model containing this record](../../../validation/models/modules/modules_brake_squeal_sol400.oos)

Reading the example gives `id = 1`.

## BrakeSqueal

The data of a brake squeal analysis of one wheel, or of another rotating object in contact with friction between sets of bodies (unsymmetric friction stiffness matrices).

**Record format and fields**

`BrakeSqueal;id;loadFactor;areaStiffness;squealOnly;axisX;axisY;axisZ;xCoord;yCoord;zCoord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `loadFactor` | `real` | 0.0 | Multiplier for load. |
| 3 | `areaStiffness` | `real` | Required | Contact stiffness normalized by the effective contact area. |
| 4 | `squealOnly` | `text` | — | Restricts the option to the brake-squeal analysis when selected. |
| 5 | `axisX` | `real` | — | X direction cosine of the axis of rotation. |
| 6 | `axisY` | `real` | — | Component Y of the specified axis vector. |
| 7 | `axisZ` | `real` | — | Component Z of the specified axis vector. |
| 8 | `xCoord` | `real` | — | X coordinate of the location in the specified frame. |
| 9 | `yCoord` | `real` | — | Y coordinate of the location in the specified frame. |
| 10 | `zCoord` | `real` | — | Z coordinate of the location in the specified frame. |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
BrakeSqueal;100;0.5;1.E+5;No;0.;0.;1.;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_brake_squeal.oos)

Reading the example gives `id = 100`, `loadFactor = 0.5`, `areaStiffness = 1.E+5`, `squealOnly = No`.

## BrakeSystem

The data of a brake system for brake squeal calculations with one wheel or several, on one axis or several.

**Record format and fields**

`BrakeSystem;id;loadFactor;frictionVectorMode;squealOnly;slidingContactOption;<disks>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `loadFactor` | `real` | 0.0 | Multiplier for load. |
| 3 | `frictionVectorMode` | `integer` | 0 | Selects how the friction direction vector is defined or updated. |
| 4 | `squealOnly` | `text` | Yes | Restricts the option to the brake-squeal analysis when selected. |
| 5 | `slidingContactOption` | `integer` | 0 | Selects the sliding contact option for BrakeSystem. |

**Repeated group `disks`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `diskName` | `text` | — | Text naming the disk. |
| 2 | `firstBodyId` | `integer` | — | Identifier selecting the first body record or set. |
| 3 | `secondBodyId` | `integer` | — | Identifier selecting the second body record or set. |
| 4 | `firstMotionId` | `integer` | — | Identifier selecting the first motion record or set. |
| 5 | `secondMotionId` | `integer` | — | Identifier selecting the second motion record or set. |
| 6 | `brakePropId` | `integer` | — | Identifier selecting the brake property record or set. |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
BrakeSystem;900;0.5;0;No;0;INNER;1;2;41;;51;OUTER;1;3;42;42;52
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_brake_squeal.oos)

Reading the example gives `id = 900`, `loadFactor = 0.5`, `frictionVectorMode = 0`, `squealOnly = No`.

## ContactAutoParams

Specifies name–value settings for automatic contact generation.

**Record format and fields**

`ContactAutoParams;id;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | 0 | Identifier in the namespace of this card type. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BilinearCoulomb`, `Both`, `Full`, `GeneralGlue`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `BeamCapping`, `BeamContact`, `ContactKind`, `DetectionDistance`, `EdgeContact`, `ElemSet`, `FrictionCoefficient`, `FrictionKind`, `IgnoreThickness`, `InitialStressFree`, `ModelDimension`, `PropertySet`, `RigidBodySet`, `SeedElemSet`, `SeedNodeSet`, `SelfContact`.

**Example record**

~~~text
ContactAutoParams;0;ContactKind;TouchOnly;DetectionDistance;1.;BeamContact;Yes;FrictionCoefficient;0.1
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_auto_beam_contact.oos)

Reading the example gives `id = 0`.

## ContactBeamCap

Whether a cap is added to a beam and how many segments model a rod or tube section, for the segment-to-segment beam contact.

**Record format and fields**

`ContactBeamCap;id;capKind;segmentCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `capKind` | `integer` | 0 | Selects the cap kind for ContactBeamCap. |
| 3 | `segmentCount` | `integer` | 32 | Number of segment entries. |

**Example record**

~~~text
ContactBeamCap;1;1;16
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_beam_segment_contact.oos)

Reading the example gives `id = 1`, `capKind = 1`, `segmentCount = 16`.

## ContactBeamRadius

The equivalent radius of beams for the node-to-segment beam-to-beam contact: the radius of the beam elements or bodies it lists, or the default radius of all beam elements.

**Record format and fields**

`ContactBeamRadius;radius;idKind;<ids>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 2 | `idKind` | `text` | ElemId | Selects the ID kind for ContactBeamRadius. |

**Repeated group `ids`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entityId` | `any` | — | Identifier selecting the entity record or set. |

Accepted words: `All`, `Body`, `By`, `ElemId`, `Through`.

**Example record**

~~~text
ContactBeamRadius;2.5;ElemId;11;Through;14
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_auto_beam_contact.oos)

Reading the example gives `radius = 2.5`, `idKind = ElemId`.

## ContactBeamSectionFlags

The branches and segments of a beam section that take part in the segment-to-segment beam contact.

**Record format and fields**

`ContactBeamSectionFlags;id;branch1;segmentFlag1;branch2;segmentFlag2;branch3;segmentFlag3;<segments>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `branch1` | `integer` | 0 | Identifies the branch of the selected beam section. Entry 1. |
| 3 | `segmentFlag1` | `integer` | 0 | Selects the segment flag 1 for ContactBeamSectionFlags. |
| 4 | `branch2` | `integer` | 0 | Identifies the branch of the selected beam section. Entry 2. |
| 5 | `segmentFlag2` | `integer` | 0 | Selects the segment flag 2 for ContactBeamSectionFlags. |
| 6 | `branch3` | `integer` | 0 | Identifies the branch of the selected beam section. Entry 3. |
| 7 | `segmentFlag3` | `integer` | 0 | Selects the segment flag 3 for ContactBeamSectionFlags. |

**Repeated group `segments`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `branch` | `integer` | — | Identifies the branch of the selected beam section. |
| 2 | `segmentFlag` | `integer` | — | Selects the segment flag for segments. |

**Example record**

~~~text
ContactBeamSectionFlags;1;0;1
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_beam_segment_contact.oos)

Reading the example gives `id = 1`, `branch1 = 0`, `segmentFlag1 = 1`.

## ContactBezierSurface

A rigid contact body made of a Bezier surface.

**Record format and fields**

`ContactBezierSurface;id;pointCount1;pointCount2;subdivisions1;subdivisions2;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointCount1` | `integer` | Required | Number of point entries. |
| 3 | `pointCount2` | `integer` | Required | Number of point entries. |
| 4 | `subdivisions1` | `integer` | Required | The subdivisions in the first direction. |
| 5 | `subdivisions2` | `integer` | Required | The subdivisions in the second direction. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node` — a grid point ID must be a positive integer.

**Example record**

~~~text
ContactBezierSurface;52;2;2;4;4;9002;9005;9003;9006
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 52`, `pointCount1 = 2`, `pointCount2 = 2`, `subdivisions1 = 4`.

## ContactBody

A flexible or rigid contact body in 2D or 3D.

**Record format and fields**

Forms: `noMotionLine`, `motionLine`.

### ContactBody: noMotionLine

Form `noMotionLine`, when `lines` is a word.

`ContactBody;id;dimension;behavior;surfaceId;contactKind;friction;splineSegmentsId;control;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dimension` | `text` | ThreeDimensional | Spatial dimension or section dimension according to the selected entry. |
| 3 | `behavior` | `text` | Deformable | Selects the assumed response of the body or contact formulation. |
| 4 | `surfaceId` | `integer` | 0 | Identifier selecting the surface record or set. |
| 5 | `contactKind` | `integer` | 0 | Selects the contact kind for ContactBody. |
| 6 | `friction` | `number` | 0.0 | Controls tangential resistance to relative motion at the interface. |
| 7 | `splineSegmentsId` | `integer` | 0 | Identifier selecting the spline segments record or set. |
| 8 | `control` | `integer` | 0 | -1 position control, 0 velocity control, a grid point number for load control. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Advance`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `smoothingAngle` | `real` | — | Angle limit used when smoothing adjacent surface segments. |
| 2 | `contactOption` | `integer` | — | Selects the contact option for advance. |
| 3 | `midsideProjection` | `integer` | — | > 0: the mid-side grid points are projected onto the splines. |

**Section `Rigid`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `referenceNode` | `integer` | — | Identifier of the grid point serving as the reference for this definition. |
| 2 | `entityCount` | `integer` | — | Number of entity entries. |
| 3 | `rigidBodyName` | `text` | — | Text naming the rigid body. Written as one text field. |

**Section `ApproachVelocity`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `approachAngularVelocity` | `real` | — | Approach angular velocity (length per time). |
| 2 | `approachAxis1` | `real` | — | Component 1 of the direction of approach or rigid motion. |
| 3 | `approachAxis2` | `real` | — | Component 2 of the direction of approach or rigid motion. |
| 4 | `approachAxis3` | `real` | — | Component 3 of the direction of approach or rigid motion. |
| 5 | `approachVelocity1` | `real` | — | Approach velocity 1 (length per time). |
| 6 | `approachVelocity2` | `real` | — | Approach velocity 2 (length per time). |
| 7 | `approachVelocity3` | `real` | — | Approach velocity 3 (length per time). |

**Section `Growth`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `growthFactor1` | `real` | — | Multiplier for growth. |
| 2 | `growthFactor2` | `real` | — | Multiplier for growth. |
| 3 | `growthFactor3` | `real` | — | Multiplier for growth. |
| 4 | `growthTable1` | `integer` | — | Identifier of the table used at position 1 in the crack-growth relation. |
| 5 | `growthTable2` | `integer` | — | Identifier of the table used at position 2 in the crack-growth relation. |
| 6 | `growthTable3` | `integer` | — | Identifier of the table used at position 3 in the crack-growth relation. |

**Section `HeatTransfer`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `environmentFilmCoefficient` | `number` | — | Coefficient in the relation for environment film. |
| 2 | `sinkTemperature` | `number` | — | Sink temperature (temperature). |
| 3 | `contactHeatTransferCoefficient` | `number` | — | Coefficient in the relation for contact heat transfer. |
| 4 | `bodyTemperature` | `number` | — | Body temperature (temperature). |
| 5 | `nearContactConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact convection. |
| 6 | `nearContactNaturalConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact natural convection. |
| 7 | `thermalInterfaceKind` | `integer` | — | Selects the thermal interface kind for heat. |
| 8 | `nearContactNaturalConvectionExponent` | `number` | — | Power in the law for near contact natural convection. |
| 9 | `emissivity` | `number` | — | Ratio of emitted radiation to that of a black body at the same temperature. |
| 10 | `distanceDependentConvectionCoefficient` | `number` | — | Coefficient in the relation for distance dependent convection. |
| 11 | `nearContactNonlinearConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact nonlinear convection. |
| 12 | `nearContactNonlinearConvectionExponent` | `number` | — | Power in the law for near contact nonlinear convection. |
| 13 | `environmentNonlinearConvectionCoefficient` | `number` | — | Coefficient in the relation for environment nonlinear convection. |
| 14 | `environmentNonlinearConvectionExponent` | `number` | — | Power in the law for environment nonlinear convection. |
| 15 | `environmentNaturalConvectionCoefficient` | `number` | — | Coefficient in the relation for environment natural convection. |
| 16 | `environmentNaturalConvectionExponent` | `number` | — | Power in the law for environment natural convection. |
| 17 | `additionalHeatCoefficient1` | `real` | — | Coefficient in the relation for additional heat. |
| 18 | `additionalHeatCoefficient2` | `real` | — | Coefficient in the relation for additional heat. |

**Section `PatchSurface`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `patchCount` | `integer` | — | Number of patch entries. |

**Repeated group `patches`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `patchId` | `integer` | — | Identifier selecting the patch record or set. |
| 2 | `patchNode1` | `integer` | — | Grid point at position 1 in the surface patch connectivity. |
| 3 | `patchNode2` | `integer` | — | Grid point at position 2 in the surface patch connectivity. |
| 4 | `patchNode3` | `integer` | — | Grid point at position 3 in the surface patch connectivity. |
| 5 | `patchNode4` | `integer` | — | Grid point at position 4 in the surface patch connectivity. |

**Section `BezierSurface`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointCount1` | `integer` | — | Number of point entries. |
| 2 | `pointCount2` | `integer` | — | Number of point entries. |
| 3 | `subdivisions1` | `integer` | — | The subdivisions in the first direction. |
| 4 | `subdivisions2` | `integer` | — | The subdivisions in the second direction. |

**Repeated group `controlPoints`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `controlPoint` | `integer` | — | Point defining the geometry or motion of the associated contact surface. |

**Section `NurbsCurve`**

**Repeated group `curveData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `curveDataValue` | `number` | — | Numeric data at the current position in the curve description. |

**Section `NurbsSurface`**

**Repeated group `surfaceData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `surfaceDataValue` | `number` | — | Numeric data at the current position of the surface description. |

### ContactBody: motionLine

Form `motionLine`, for every other record.

`ContactBody;id;dimension;behavior;surfaceId;contactKind;friction;splineSegmentsId;control;loadNode;angularVelocity;axisCosine1;axisCosine2;axisCosine3;rigidVelocity1;rigidVelocity2;rigidVelocity3;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dimension` | `text` | ThreeDimensional | Spatial dimension or section dimension according to the selected entry. |
| 3 | `behavior` | `text` | Deformable | Selects the assumed response of the body or contact formulation. |
| 4 | `surfaceId` | `integer` | 0 | Identifier selecting the surface record or set. |
| 5 | `contactKind` | `integer` | 0 | Selects the contact kind for ContactBody. |
| 6 | `friction` | `number` | 0.0 | Controls tangential resistance to relative motion at the interface. |
| 7 | `splineSegmentsId` | `integer` | 0 | Identifier selecting the spline segments record or set. |
| 8 | `control` | `integer` | 0 | -1 position control, 0 velocity control, a grid point number for load control. |
| 9 | `loadNode` | `integer` | 0 | Grid point at which the selected load or control quantity is evaluated. |
| 10 | `angularVelocity` | `number` | — | Angular velocity (length per time). |
| 11 | `axisCosine1` | `number` | — | Direction cosine for axis component 1 (dimensionless). |
| 12 | `axisCosine2` | `number` | — | Direction cosine for axis component 2 (dimensionless). |
| 13 | `axisCosine3` | `number` | — | Direction cosine for axis component 3 (dimensionless). |
| 14 | `rigidVelocity1` | `number` | — | Rigid velocity 1 (length per time). |
| 15 | `rigidVelocity2` | `number` | — | Rigid velocity 2 (length per time). |
| 16 | `rigidVelocity3` | `number` | — | Rigid velocity 3 (length per time). |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Advance`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `smoothingAngle` | `real` | — | Angle limit used when smoothing adjacent surface segments. |
| 2 | `contactOption` | `integer` | — | Selects the contact option for advance. |
| 3 | `midsideProjection` | `integer` | — | > 0: the mid-side grid points are projected onto the splines. |

**Section `Rigid`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `referenceNode` | `integer` | — | Identifier of the grid point serving as the reference for this definition. |
| 2 | `entityCount` | `integer` | — | Number of entity entries. |
| 3 | `rigidBodyName` | `text` | — | Text naming the rigid body. Written as one text field. |

**Section `ApproachVelocity`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `approachAngularVelocity` | `real` | — | Approach angular velocity (length per time). |
| 2 | `approachAxis1` | `real` | — | Component 1 of the direction of approach or rigid motion. |
| 3 | `approachAxis2` | `real` | — | Component 2 of the direction of approach or rigid motion. |
| 4 | `approachAxis3` | `real` | — | Component 3 of the direction of approach or rigid motion. |
| 5 | `approachVelocity1` | `real` | — | Approach velocity 1 (length per time). |
| 6 | `approachVelocity2` | `real` | — | Approach velocity 2 (length per time). |
| 7 | `approachVelocity3` | `real` | — | Approach velocity 3 (length per time). |

**Section `Growth`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `growthFactor1` | `real` | — | Multiplier for growth. |
| 2 | `growthFactor2` | `real` | — | Multiplier for growth. |
| 3 | `growthFactor3` | `real` | — | Multiplier for growth. |
| 4 | `growthTable1` | `integer` | — | Identifier of the table used at position 1 in the crack-growth relation. |
| 5 | `growthTable2` | `integer` | — | Identifier of the table used at position 2 in the crack-growth relation. |
| 6 | `growthTable3` | `integer` | — | Identifier of the table used at position 3 in the crack-growth relation. |

**Section `HeatTransfer`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `environmentFilmCoefficient` | `number` | — | Coefficient in the relation for environment film. |
| 2 | `sinkTemperature` | `number` | — | Sink temperature (temperature). |
| 3 | `contactHeatTransferCoefficient` | `number` | — | Coefficient in the relation for contact heat transfer. |
| 4 | `bodyTemperature` | `number` | — | Body temperature (temperature). |
| 5 | `nearContactConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact convection. |
| 6 | `nearContactNaturalConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact natural convection. |
| 7 | `thermalInterfaceKind` | `integer` | — | Selects the thermal interface kind for heat. |
| 8 | `nearContactNaturalConvectionExponent` | `number` | — | Power in the law for near contact natural convection. |
| 9 | `emissivity` | `number` | — | Ratio of emitted radiation to that of a black body at the same temperature. |
| 10 | `distanceDependentConvectionCoefficient` | `number` | — | Coefficient in the relation for distance dependent convection. |
| 11 | `nearContactNonlinearConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact nonlinear convection. |
| 12 | `nearContactNonlinearConvectionExponent` | `number` | — | Power in the law for near contact nonlinear convection. |
| 13 | `environmentNonlinearConvectionCoefficient` | `number` | — | Coefficient in the relation for environment nonlinear convection. |
| 14 | `environmentNonlinearConvectionExponent` | `number` | — | Power in the law for environment nonlinear convection. |
| 15 | `environmentNaturalConvectionCoefficient` | `number` | — | Coefficient in the relation for environment natural convection. |
| 16 | `environmentNaturalConvectionExponent` | `number` | — | Power in the law for environment natural convection. |
| 17 | `additionalHeatCoefficient1` | `real` | — | Coefficient in the relation for additional heat. |
| 18 | `additionalHeatCoefficient2` | `real` | — | Coefficient in the relation for additional heat. |

**Section `PatchSurface`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `patchCount` | `integer` | — | Number of patch entries. |

**Repeated group `patches`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `patchId` | `integer` | — | Identifier selecting the patch record or set. |
| 2 | `patchNode1` | `integer` | — | Grid point at position 1 in the surface patch connectivity. |
| 3 | `patchNode2` | `integer` | — | Grid point at position 2 in the surface patch connectivity. |
| 4 | `patchNode3` | `integer` | — | Grid point at position 3 in the surface patch connectivity. |
| 5 | `patchNode4` | `integer` | — | Grid point at position 4 in the surface patch connectivity. |

**Section `BezierSurface`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointCount1` | `integer` | — | Number of point entries. |
| 2 | `pointCount2` | `integer` | — | Number of point entries. |
| 3 | `subdivisions1` | `integer` | — | The subdivisions in the first direction. |
| 4 | `subdivisions2` | `integer` | — | The subdivisions in the second direction. |

**Repeated group `controlPoints`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `controlPoint` | `integer` | — | Point defining the geometry or motion of the associated contact surface. |

**Section `NurbsCurve`**

**Repeated group `curveData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `curveDataValue` | `number` | — | Numeric data at the current position in the curve description. |

**Section `NurbsSurface`**

**Repeated group `surfaceData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `surfaceDataValue` | `number` | — | Numeric data at the current position of the surface description. |

Accepted words: `Advance`, `ApproachVelocity`, `BezierSurface`, `Deformable`, `Growth`, `HeatTransfer`, `NurbsCurve`, `NurbsSurface`, `PatchSurface`, `Rigid`, `Symmetric`, `ThreeDimensional`, `TwoDimensional`.

Accepted parameter names: `AdditionalHeatCoefficient1`, `AdditionalHeatCoefficient2`, `BodyTemperature`, `ContactHeatTransferCoefficient`, `DistanceDependentConvectionCoefficient`, `Emissivity`, `EnvironmentFilmCoefficient`, `EnvironmentNaturalConvectionCoefficient`, `EnvironmentNaturalConvectionExponent`, `EnvironmentNonlinearConvectionCoefficient`, `EnvironmentNonlinearConvectionExponent`, `NearContactConvectionCoefficient`, `NearContactNaturalConvectionCoefficient`, `NearContactNaturalConvectionExponent`, `NearContactNonlinearConvectionCoefficient`, `NearContactNonlinearConvectionExponent`, `SinkTemperature`, `ThermalInterfaceKind`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `rigid` — the rigid body name has no comma, $ or tab.
- `rigid` — the rigid body name does not begin or end with a blank.
- `patches` — PATCH3D needs at least one patch.
- `patches` — a grid point ID must be a positive integer.
- `bezier` — a grid point ID must be a positive integer.

**Example record**

~~~text
ContactBody;1;ThreeDimensional;Deformable;1
~~~

[Model containing this record](../../../validation/models/glued_contact/glued_pcomp_z0.oos)

## ContactBody1

A flexible or rigid contact body, the new form of [ContactBody](nonlinear_contact.md#contactbody).

**Record format and fields**

`ContactBody1;id;bodyParamsId;dimension;behavior;surfaceId;rigidMotionId;forceReferencePoint`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bodyParamsId` | `integer` | 0 | Identifier selecting the body params record or set. |
| 3 | `dimension` | `text` | — | Spatial dimension or section dimension according to the selected entry. |
| 4 | `behavior` | `text` | — | Selects the assumed response of the body or contact formulation. |
| 5 | `surfaceId` | `integer` | 0 | Identifier selecting the surface record or set. |
| 6 | `rigidMotionId` | `integer` | 0 | Identifier selecting the rigid motion record or set. |
| 7 | `forceReferencePoint` | `integer` | 0 | The reference point of the resultant contact force: -1 origin, 0 centroid of the body. |

Accepted words: `Deformable`, `HeatTransfer`, `Rigid`, `Symmetric`, `ThreeDimensional`, `TwoDimensional`.

**Example record**

~~~text
ContactBody1;2;;TwoDimensional;Rigid;70;20
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 2`, `dimension = TwoDimensional`, `behavior = Rigid`, `surfaceId = 70`.

## ContactBodyChange

Changes the definition of the deformable contact bodies in a load case.

**Record format and fields**

`ContactBodyChange;id;kind;<ranges>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `kind` | `text` | — | Selects the kind for ContactBodyChange. |

**Repeated group `ranges`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bodyId` | `integer` | — | Identifier addressing contact body data. |
| 2 | `firstNode` | `integer` | — | Identifier addressing node in range data. |
| 3 | `lastNode` | `integer` | — | Final grid point of the ordered segment or selection. |
| 4 | `increment` | `integer` | — | Change applied in one continuation or loading step. |

Accepted words: `Exclude`, `Node`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `bodyId` — the card needs at least one body.
- `bodyId` — a body ID must be a positive integer.

**Example record**

~~~text
ContactBodyChange;1;Node;1;19;27;1;1;3;27;3
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 1`, `kind = Node`.

## ContactBodyMove

The movement of bodies in contact in a load case: the rigid bodies are moved until they touch the deformable ones, or the contact of some bodies is released.

**Record format and fields**

`ContactBodyMove;id;moveKind;<bodies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `moveKind` | `text` | Approach | Selects the move kind for ContactBodyMove. |

**Repeated group `bodies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bodyId` | `integer` | — | Identifier selecting the body record or set. |

Accepted words: `Approach`, `Release`, `Synchronous`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `bodies` — a body ID must be a positive integer.

**Example record**

~~~text
ContactBodyMove;2;Release;2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 2`, `moveKind = Release`.

## ContactBodyParams

The parameters of a contact body: friction, spline smoothing of the surface, check of the contact conditions, heat transfer coefficients, as (name, value) pairs.

**Record format and fields**

`ContactBodyParams;id;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BilinearCoulomb`, `Both`, `Full`, `GeneralGlue`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `AdditionalHeatCoefficient1`, `AdditionalHeatCoefficient2`, `BodyContactOptions`, `BodyTemperature`, `ContactHeatTransferCoefficient`, `DisplacementOption`, `DistanceDependentConvectionCoefficient`, `Emissivity`, `EnvironmentFilmCoefficient`, `EnvironmentNaturalConvectionCoefficient`, `EnvironmentNaturalConvectionExponent`, `EnvironmentNonlinearConvectionCoefficient`, `EnvironmentNonlinearConvectionExponent`, `FrictionCoefficient`, `InterfaceSubtype`, `MidsideNodes`, `NearContactConvectionCoefficient`, `NearContactNaturalConvectionCoefficient`, `NearContactNaturalConvectionExponent`, `NearContactNonlinearConvectionCoefficient`, `NearContactNonlinearConvectionExponent`, `SeparationAngle`, `SinkTemperature`, `ThermalInterfaceKind`.

**Example record**

~~~text
ContactBodyParams;5;FrictionCoefficient;0.1;InterfaceSubtype;0
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 5`.

## ContactBoxRegion

Selects elements inside a three-dimensional box as a region of a contact body.

**Record format and fields**

`ContactBoxRegion;id;inclusionRule;coordinateForm;cornerNode1;cornerNode2;cornerX1;cornerNode3;cornerY1;cornerNode4;cornerZ1;cornerNode5;cornerX2;cornerNode6;cornerY2;cornerNode7;cornerZ2;cornerNode8;cornerX3;cornerY3;cornerZ3;cornerX4;cornerY4;cornerZ4;cornerX5;cornerY5;cornerZ5;cornerX6;cornerY6;cornerZ6;cornerX7;cornerY7;cornerZ7;cornerX8;cornerY8;cornerZ8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `inclusionRule` | `integer` | 0 | Criterion for including candidate entities in the region. Alternative to `coordinateForm`. |
| 3 | `coordinateForm` | `text` | — | Selects the coordinate representation of the defined surface or motion. Alternative to `inclusionRule`. |
| 4 | `cornerNode1` | `any` | — | Grid point defining corner 1 of the selected geometry. |
| 5 | `cornerNode2` | `integer` | — | Grid point defining corner 2 of the selected geometry. Alternative to `cornerX1`. |
| 6 | `cornerX1` | `real` | — | Coordinate X of corner 1 in the local frame. Alternative to `cornerNode2`. |
| 7 | `cornerNode3` | `integer` | — | Grid point defining corner 3 of the selected geometry. Alternative to `cornerY1`. |
| 8 | `cornerY1` | `real` | — | Coordinate Y of corner 1 in the local frame. Alternative to `cornerNode3`. |
| 9 | `cornerNode4` | `integer` | — | Grid point defining corner 4 of the selected geometry. Alternative to `cornerZ1`. |
| 10 | `cornerZ1` | `real` | — | Coordinate Z of corner 1 in the local frame. Alternative to `cornerNode4`. |
| 11 | `cornerNode5` | `integer` | — | Grid point defining corner 5 of the selected geometry. Alternative to `cornerX2`. |
| 12 | `cornerX2` | `real` | — | Coordinate X of corner 2 in the local frame. Alternative to `cornerNode5`. |
| 13 | `cornerNode6` | `integer` | — | Grid point defining corner 6 of the selected geometry. Alternative to `cornerY2`. |
| 14 | `cornerY2` | `real` | — | Coordinate Y of corner 2 in the local frame. Alternative to `cornerNode6`. |
| 15 | `cornerNode7` | `integer` | — | Grid point defining corner 7 of the selected geometry. Alternative to `cornerZ2`. |
| 16 | `cornerZ2` | `real` | — | Coordinate Z of corner 2 in the local frame. Alternative to `cornerNode7`. |
| 17 | `cornerNode8` | `integer` | — | Grid point defining corner 8 of the selected geometry. Alternative to `cornerX3`. |
| 18 | `cornerX3` | `real` | — | Coordinate X of corner 3 in the local frame. Alternative to `cornerNode8`. |
| 19 | `cornerY3` | `real` | — | Coordinate Y of corner 3 in the local frame. |
| 20 | `cornerZ3` | `real` | — | Coordinate Z of corner 3 in the local frame. |
| 21 | `cornerX4` | `real` | — | Coordinate X of corner 4 in the local frame. |
| 22 | `cornerY4` | `real` | — | Coordinate Y of corner 4 in the local frame. |
| 23 | `cornerZ4` | `real` | — | Coordinate Z of corner 4 in the local frame. |
| 24 | `cornerX5` | `real` | — | Coordinate X of corner 5 in the local frame. |
| 25 | `cornerY5` | `real` | — | Coordinate Y of corner 5 in the local frame. |
| 26 | `cornerZ5` | `real` | — | Coordinate Z of corner 5 in the local frame. |
| 27 | `cornerX6` | `real` | — | Coordinate X of corner 6 in the local frame. |
| 28 | `cornerY6` | `real` | — | Coordinate Y of corner 6 in the local frame. |
| 29 | `cornerZ6` | `real` | — | Coordinate Z of corner 6 in the local frame. |
| 30 | `cornerX7` | `real` | — | Coordinate X of corner 7 in the local frame. |
| 31 | `cornerY7` | `real` | — | Coordinate Y of corner 7 in the local frame. |
| 32 | `cornerZ7` | `real` | — | Coordinate Z of corner 7 in the local frame. |
| 33 | `cornerX8` | `real` | — | Coordinate X of corner 8 in the local frame. |
| 34 | `cornerY8` | `real` | — | Coordinate Y of corner 8 in the local frame. |
| 35 | `cornerZ8` | `real` | — | Coordinate Z of corner 8 in the local frame. |

Accepted words: `Coordinates`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cornerX1` — the coordinates of the box must be finite.

**Example record**

~~~text
ContactBoxRegion;32;;Coordinates;0;;0.;;0.;;0.;;400.;;0.;;0.;;400.;100.;0.;0.;100.;0.;0.;0.;50.;400.;0.;50.;400.;100.;50.;0.;100.;50.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 32`, `coordinateForm = Coordinates`, `cornerNode1 = 0`, `cornerX1 = 0.`.

## ContactControlParams

The control parameters of the contact algorithm of the contact set that has the same number, as (name, value) pairs.

**Record format and fields**

`ContactControlParams;contactSetId;parameterName1;parameterValue1;parameterName2;parameterValue2;parameterName3;parameterValue3;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `contactSetId` | `integer` | Required | Identifier selecting the contact set record or set. |
| 2 | `parameterName1` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 1. |
| 3 | `parameterValue1` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 1. |
| 4 | `parameterName2` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 2. |
| 5 | `parameterValue2` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 2. |
| 6 | `parameterName3` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 3. |
| 7 | `parameterValue3` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 3. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Both`, `Constant`, `Element`, `Full`, `No`, `Off`, `On`, `Table`, `Yes`.

Accepted parameter names: `ContactTolerance`, `NormalPenalty`, `ShellThicknessOption`, `TangentPenalty`.

**Example record**

~~~text
ContactControlParams;200;PENTYP;1;INIPENE;0
~~~

[Model containing this record](../../../validation/models/read_only_nonlinear/legacy_surface_contact_sets.oos)

Reading the example gives `contactSetId = 200`, `parameterName1 = PENTYP`, `parameterValue1 = 1`, `parameterName2 = INIPENE`.

## ContactElemSurface

Defines the elements forming a contact surface for a contact body.

**Record format and fields**

`ContactElemSurface;id;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `element` | `any` | — | Identifier of the element selected in this group. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `elements` — the surface needs at least one element.

**Example record**

~~~text
ContactElemSurface;1;1;2;3;4
~~~

[Model containing this record](../../../validation/models/glued_contact/glued_stiffener_edge.oos)

Reading the example gives `id = 1`.

## ContactEllipsoidList

Groups the named contact ellipsoids of an occupant model.

**Record format and fields**

`ContactEllipsoidList;id;<ellipsoidNames>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `ellipsoidNames`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ellipsoidName` | `text` | — | Text naming the ellipsoid. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `ellipsoidNames` — the list needs at least one ellipsoid name.
- `ellipsoidNames` — an ellipsoid name is a word with no blank, comma or $.

**Example record**

~~~text
ContactEllipsoidList;2;HEAD;CHEST
~~~

[Model containing this record](../../../validation/models/read_only_nonlinear/sol700_occupant_ellipsoids.oos)

Reading the example gives `id = 2`.

## ContactFaceRegion

A contact region made of element faces, named by [ContactPair](nonlinear_contact.md#contactpair).

**Record format and fields**

`ContactFaceRegion;id;bodyParamsId;dimension;form;includeThickness;edgeContact;<faces>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bodyParamsId` | `integer` | 0 | Identifier selecting the body params record or set. |
| 3 | `dimension` | `text` | ThreeDimensional | Spatial dimension or section dimension according to the selected entry. |
| 4 | `form` | `text` | Face | Selects the form for ContactFaceRegion. |
| 5 | `includeThickness` | `text` | Yes | Selects whether the surface search includes the physical thickness. |
| 6 | `edgeContact` | `integer` | 1 | 1 beam and bar edges, 10 free and hard shell edges, 11 both. |

**Repeated group `faces`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `faceElemId` | `integer` | — | Identifier selecting the face element record or set. |
| 2 | `faceId` | `any` | — | Identifier selecting the face record or set. |
| 3 | `idType` | `any` | — | Selects the ID type for faces. |
| 4 | `node` | `integer` | — | Grid point to which this entry applies. |

Accepted words: `Both`, `Bottom`, `Elements`, `EndA`, `EndB`, `Face`, `No`, `Node`, `Rigid`, `Set`, `ThreeDimensional`, `Top`, `TwoDimensional`, `Yes`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `faces` — the surface needs at least one face.
- `faces` — an element or set ID must be a positive integer.
- `elemId` — the surface needs at least one face.
- `elemId` — an element ID must be a positive integer.
- `elemId` — a grid point ID must not be negative.
- `elemId` — the two corners of an edge of a 2D body are both given (the third blank) or both blank.
- `elemId` — the three corners of a face are all given or all blank.

**Example record**

~~~text
ContactFaceRegion;5;;TwoDimensional;Node;;;7;14;13;;8;15;14
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 5`, `dimension = TwoDimensional`, `form = Node`.

## ContactMaterialRegion

Selects elements by material to form a three-dimensional contact region.

**Record format and fields**

`ContactMaterialRegion;id;<materials>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `materials`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matId` | `integer` | — | Material identifier used to retrieve the constitutive data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `matIds` — the region needs at least one material.
- `matIds` — a material ID must be a positive integer.

**Example record**

~~~text
ContactMaterialRegion;11;2
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 11`.

## ContactNodeRegion

A contact region made of a list of grid points.

**Record format and fields**

`ContactNodeRegion;id;bodyParamsId;dimension;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bodyParamsId` | `integer` | 0 | Identifier selecting the body params record or set. |
| 3 | `dimension` | `any` | ThreeDimensional | Spatial dimension or section dimension according to the selected entry. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `any` | — | Identifier of the grid point addressed by this record. |

Accepted words: `By`, `ThreeDimensional`, `Through`, `TwoDimensional`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeId` — the card needs at least one grid point.

**Example record**

~~~text
ContactNodeRegion;22;1001;1010;1005;1006;1101;1110;1105;1106;1201;1210;1205;1206;1301;1310;1305;1306;1401;1410;1405;1406
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 22`, `bodyParamsId = 1001`, `dimension = 1010`.

## ContactNurbsCurve

A 2D rigid contact body made of a NURBS curve.

**Record format and fields**

`ContactNurbsCurve;id;pointCountU;orderU;subdivisions;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointCountU` | `integer` | Required | The control points (negative: given by coordinates). |
| 3 | `orderU` | `integer` | Required | Spline order in the first parametric direction. |
| 4 | `subdivisions` | `integer` | Required | The subdivisions. |

**Keyed sections in `dataLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Node`**

**Repeated group `controlNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |

**Section `Coordinates`**

**Repeated group `coordinates`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coordinate` | `real` | — | Coordinate of the specified point in the selected frame. |

**Section `HomogeneousCoordinates`**

**Repeated group `weights`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `homogeneous` | `real` | — | Selects homogeneous coordinates for the rational geometric definition. |

**Section `KnotVector`**

**Repeated group `knots`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `knot` | `real` | — | Parameter value in the knot sequence defining the spline. |

Accepted words: `Coordinates`, `HomogeneousCoordinates`, `KnotVector`, `Node`.

**Example record**

~~~text
ContactNurbsCurve;80;-2;2;1;Coordinates;4;20.;12.;20.;-2.;HomogeneousCoordinates;2;1.;1.;KnotVector;4;0.;0.;1.;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 80`, `pointCountU = -2`, `orderU = 2`, `subdivisions = 1`.

## ContactNurbsSurface

A rigid contact body made of a NURBS surface.

**Record format and fields**

`ContactNurbsSurface;id;pointCountU;pointCountV;orderU;orderV;subdivisionsU;subdivisionsV;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointCountU` | `integer` | Required | The control points in the U direction (negative: given by coordinates). |
| 3 | `pointCountV` | `integer` | Required | The control points in the V direction. |
| 4 | `orderU` | `integer` | Required | Spline order in the first parametric direction. |
| 5 | `orderV` | `integer` | Required | The order along V. |
| 6 | `subdivisionsU` | `integer` | Required | The subdivisions along U. |
| 7 | `subdivisionsV` | `integer` | Required | The subdivisions along V. |

**Keyed sections in `dataLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Node`**

**Repeated group `controlNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |

**Section `Coordinates`**

**Repeated group `coordinates`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coordinate` | `real` | — | Coordinate of the specified point in the selected frame. |

**Section `HomogeneousCoordinates`**

**Repeated group `weights`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `homogeneous` | `real` | — | Selects homogeneous coordinates for the rational geometric definition. |

**Section `KnotVector`**

**Repeated group `knots`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `knot` | `real` | — | Parameter value in the knot sequence defining the spline. |

**Section `Trimming`**

**Repeated group `trimCurves`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `trimCurveId` | `integer` | — | Identifier selecting the trim curve record or set. |

Accepted words: `Coordinates`, `HomogeneousCoordinates`, `KnotVector`, `Node`, `Trimming`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `trimCurveId` — a trimming curve ID must be a positive integer.

**Example record**

~~~text
ContactNurbsSurface;60;-2;2;2;2;4;4;Coordinates;12;20.;-2.;-2.;20.;22.;-2.;20.;-2.;12.;20.;22.;12.;HomogeneousCoordinates;4;1.;1.;1.;1.;KnotVector;8;0.;0.;1.;1.;0.;0.;1.;1.;Trimming;1;61
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 60`, `pointCountU = -2`, `pointCountV = 2`, `orderU = 2`.

## ContactPair

A contact pair: the bodies that touch (secondary, the "touching" bodies) and the bodies they touch (primary), with the parameter sets of the pair.

**Record format and fields**

`ContactPair;id;geomParamsId;physicalParamsId;secondaryBodyId;primaryBodyId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `geomParamsId` | `integer` | 0 | Identifier selecting the geom params record or set. |
| 3 | `physicalParamsId` | `integer` | 0 | Identifier selecting the physical params record or set. |
| 4 | `secondaryBodyId` | `integer` | 0 | Identifier selecting the secondary body record or set. |
| 5 | `primaryBodyId` | `integer` | 0 | Identifier selecting the primary body record or set. |

**Keyed sections in `bodyLists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Secondary`**

**Repeated group `secondaryBodies`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `secondaryBody` | `integer` | — | Body acting as the secondary side of the contact pair. |

**Section `Primary`**

**Repeated group `primaryBodies`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `primaryBody` | `integer` | — | Body acting as the primary side of the contact pair. |

Accepted words: `Primary`, `Secondary`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `secondaryBodies` — a body ID must not be negative.
- `primaryBodyId` — a body ID must not be negative.

**Example record**

~~~text
ContactPair;11;21;31;1;2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 11`, `geomParamsId = 21`, `physicalParamsId = 31`, `secondaryBodyId = 1`.

## ContactPairGeomParams

Sets geometric controls for a contact pair, including search order, interference fit, glue and the initial gap.

**Record format and fields**

`ContactPairGeomParams;id;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BilinearCoulomb`, `Both`, `Full`, `GeneralGlue`, `MonitorDisplacement`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `AdaptiveContactSurface`, `AugmentationDistance`, `AutomaticContact`, `ContactDistanceTolerance`, `ContactForceWeighting`, `ContactMethod`, `ContactSearchOrder`, `ContactSide`, `ContactThickness`, `ContactTimeControl`, `ContactToleranceBias`, `GlueInitialNormalStiffness`, `GlueInitialTangentStiffness`, `GlueNormalStiffness`, `GlueOption`, `GlueRotationCenter`, `GlueRotationNormalStiffness`, `GlueRotationTangentStiffness`, `GlueSecondRotationCenter`, `GlueSeparationOption`, `GlueStiffnessOption`, `GlueTangentStiffness`, `HardSoftRatio`, `IgnoreInitialPenetration`, `InitialGapDirectionSystem`, `InitialGapMargin`, `InitialGapOption`, `InitialGapSecondTolerance`, `InitialGapTolerance`, `InitialMonitor`, `InterferenceBodyOption`, `InterferenceCenterX`, `InterferenceCenterY`, `InterferenceCenterZ`, `InterferenceClosure`, `InterferenceDirectionSystem`, `InterferenceDirectionX`, `InterferenceDirectionY`, `InterferenceDirectionZ`, `InterferenceOption`, `InterferenceTable`, `InterferenceTolerance`, `MaxParametricCoordinate`, `MonitorDisplacement`, `MonitorDisplacementValue`, `NormalPenaltyFactor`, `NormalPenaltyScale`, `PenetrationLimit`, `SlidingVelocityThreshold`, `SoftContact`, `StickSlip`, `StressFreeInitialContact`, `TangentPenaltyFactor`, `TangentPenaltyScale`, `ThicknessOffset`, `TouchedBodyOptions`, `TouchingBodyOptions`.

**Example record**

~~~text
ContactPairGeomParams;20;GlueOption;1;GlueSeparationOption;0
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_vcct_unglue_dcb.oos)

Reading the example gives `id = 20`.

## ContactPairPhysicalParams

Sets the physical interaction between a pair of contact bodies, including friction, thermal contact and glue failure.

**Record format and fields**

`ContactPairPhysicalParams;id;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Both`, `Full`, `No`, `Off`, `On`, `Yes`.

Accepted parameter names: `ContactDamping`, `ContactEndTime`, `ContactHeatTransferCoefficient`, `ContactStartTime`, `DistanceDependentConvectionCoefficient`, `Emissivity`, `FrictionCoefficient`, `FrictionDecayCoefficient`, `FrictionStressLimit`, `GlueBreakNormalExponent`, `GlueBreakNormalStress`, `GlueBreakShearExponent`, `GlueBreakShearStress`, `GlueHeatTransfer`, `InitialPenetrationAdjustment`, `KineticFrictionCoefficient`, `NearContactConvectionCoefficient`, `NearContactDistance`, `NearContactNaturalConvectionCoefficient`, `NearContactNaturalConvectionExponent`, `NearContactNonlinearConvectionCoefficient`, `NearContactNonlinearConvectionExponent`, `PenaltyScaleFactor`, `SeparationForce`.

**Example record**

~~~text
ContactPairPhysicalParams;30;FrictionCoefficient;0.3
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_brake_squeal.oos)

Reading the example gives `id = 30`.

## ContactParams

Sets named controls for contact detection and response, including separation, friction and geometric tolerance.

**Record format and fields**

`ContactParams;id;parameterName1;parameterValue1;parameterName2;parameterValue2;parameterName3;parameterValue3;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | 0 | Identifier in the namespace of this card type. |
| 2 | `parameterName1` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 1. |
| 3 | `parameterValue1` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 1. |
| 4 | `parameterName2` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 2. |
| 5 | `parameterValue2` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 2. |
| 6 | `parameterName3` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 3. |
| 7 | `parameterValue3` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 3. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BilinearCoulomb`, `Both`, `Full`, `GeneralGlue`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `AugmentationDistance`, `AugmentationOption`, `AugmentationTime`, `BackupControl`, `BeamToBeamContact`, `ContactAlgorithmVersion`, `ContactDistanceTolerance`, `ContactMethod`, `ContactTimeControl`, `ContactToleranceBasis`, `ContactToleranceBias`, `DisplacementIncrementLimit`, `DynamicPressureFactor`, `FrictionKind`, `GlueInitialNormalStiffness`, `GlueInitialTangentStiffness`, `GlueNormalStiffness`, `GlueOutput`, `GlueRotationCenter`, `GlueRotationNormalStiffness`, `GlueRotationTangentStiffness`, `GlueSecondRotationCenter`, `GlueStiffnessOption`, `GlueTangentStiffness`, `IgnoreShellThickness`, `InitialSeparationCheck`, `LineContact`, `MaxSeparations`, `NodeSeparation`, `NonlinearGlue`, `NormalPenaltyFactor`, `NormalPenaltyScale`, `OutputSplineFreq`, `ResidualVectorConstant`, `SegmentAngle`, `SegmentSymmetry`, `SeparationAcceleration`, `SeparationCriterion`, `SeparationForce`, `SolidLimit`, `StickSlip`, `TangentPenaltyFactor`, `TangentPenaltyScale`.

**Example record**

~~~text
ContactParams;0;ContactMethod;NodeToSurface;BeamToBeamContact;1
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_auto_beam_contact.oos)

Reading the example gives `id = 0`, `parameterName1 = ContactMethod`, `parameterValue1 = NodeToSurface`, `parameterName2 = BeamToBeamContact`.

## ContactPatchSurface

A rigid contact body made of quadrilateral patches.

**Record format and fields**

`ContactPatchSurface;id;<patches>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `patches`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `patchId` | `integer` | — | Identifier selecting the patch record or set. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 4 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 5 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `patchId` — the surface needs at least one patch.
- `node` — a grid point ID must be a positive integer.
- `node` — the four grid points of a patch must be different.

**Example record**

~~~text
ContactPatchSurface;51;1;9001;9002;9003;9004
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 51`.

## ContactPropertyRegion

Selects elements by property to form a three-dimensional contact region.

**Record format and fields**

`ContactPropertyRegion;id;<properties>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `properties`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `any` | — | Identifier of the property from which the element obtains its section or constitutive data. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `propIds` — the region needs at least one property.

**Example record**

~~~text
ContactPropertyRegion;102;2;3;4
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 102`.

## ContactRigidMotion

The motion of a rigid contact body.

**Record format and fields**

Forms: `noMotionLine`, `motionLine`.

### ContactRigidMotion: noMotionLine

Form `noMotionLine`, when `motionLines` is a word.

`ContactRigidMotion;id;referenceNode;control;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceNode` | `integer` | 0 | Identifier of the grid point serving as the reference for this definition. |
| 3 | `control` | `integer` | 0 | -1 position control, 0 velocity control, a grid point number for load control. |

**Keyed sections in `motionLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ApproachVelocity`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `approachAngularVelocity` | `real` | — | Approach angular velocity (length per time). |
| 2 | `approachAxis1` | `real` | — | Component 1 of the direction of approach or rigid motion. |
| 3 | `approachAxis2` | `real` | — | Component 2 of the direction of approach or rigid motion. |
| 4 | `approachAxis3` | `real` | — | Component 3 of the direction of approach or rigid motion. |
| 5 | `approachVelocity1` | `real` | — | Approach velocity 1 (length per time). |
| 6 | `approachVelocity2` | `real` | — | Approach velocity 2 (length per time). |
| 7 | `approachVelocity3` | `real` | — | Approach velocity 3 (length per time). |

**Section `Growth`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `growthFactor1` | `real` | — | Multiplier for growth. |
| 2 | `growthFactor2` | `real` | — | Multiplier for growth. |
| 3 | `growthFactor3` | `real` | — | Multiplier for growth. |
| 4 | `growthTable1` | `integer` | — | Identifier of the table used at position 1 in the crack-growth relation. |
| 5 | `growthTable2` | `integer` | — | Identifier of the table used at position 2 in the crack-growth relation. |
| 6 | `growthTable3` | `integer` | — | Identifier of the table used at position 3 in the crack-growth relation. |

### ContactRigidMotion: motionLine

Form `motionLine`, for every other record.

`ContactRigidMotion;id;referenceNode;control;loadNode;angularVelocity;axisCosine1;axisCosine2;axisCosine3;rigidVelocity1;rigidVelocity2;rigidVelocity3;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceNode` | `integer` | 0 | Identifier of the grid point serving as the reference for this definition. |
| 3 | `control` | `integer` | 0 | -1 position control, 0 velocity control, a grid point number for load control. |
| 4 | `loadNode` | `integer` | 0 | Grid point at which the selected load or control quantity is evaluated. |
| 5 | `angularVelocity` | `number` | — | Angular velocity (length per time). |
| 6 | `axisCosine1` | `number` | — | Direction cosine for axis component 1 (dimensionless). |
| 7 | `axisCosine2` | `number` | — | Direction cosine for axis component 2 (dimensionless). |
| 8 | `axisCosine3` | `number` | — | Direction cosine for axis component 3 (dimensionless). |
| 9 | `rigidVelocity1` | `number` | — | Rigid velocity 1 (length per time). |
| 10 | `rigidVelocity2` | `number` | — | Rigid velocity 2 (length per time). |
| 11 | `rigidVelocity3` | `number` | — | Rigid velocity 3 (length per time). |

**Keyed sections in `motionLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ApproachVelocity`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `approachAngularVelocity` | `real` | — | Approach angular velocity (length per time). |
| 2 | `approachAxis1` | `real` | — | Component 1 of the direction of approach or rigid motion. |
| 3 | `approachAxis2` | `real` | — | Component 2 of the direction of approach or rigid motion. |
| 4 | `approachAxis3` | `real` | — | Component 3 of the direction of approach or rigid motion. |
| 5 | `approachVelocity1` | `real` | — | Approach velocity 1 (length per time). |
| 6 | `approachVelocity2` | `real` | — | Approach velocity 2 (length per time). |
| 7 | `approachVelocity3` | `real` | — | Approach velocity 3 (length per time). |

**Section `Growth`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `growthFactor1` | `real` | — | Multiplier for growth. |
| 2 | `growthFactor2` | `real` | — | Multiplier for growth. |
| 3 | `growthFactor3` | `real` | — | Multiplier for growth. |
| 4 | `growthTable1` | `integer` | — | Identifier of the table used at position 1 in the crack-growth relation. |
| 5 | `growthTable2` | `integer` | — | Identifier of the table used at position 2 in the crack-growth relation. |
| 6 | `growthTable3` | `integer` | — | Identifier of the table used at position 3 in the crack-growth relation. |

Accepted words: `ApproachVelocity`, `Growth`.

**Example record**

~~~text
ContactRigidMotion;20;9110;0;;0.;0.;0.;1.;0.;-0.02
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

## ContactRigidSurfaceList

Collects rigid surface descriptions into a single region that a contact body can reference.

**Record format and fields**

`ContactRigidSurfaceList;id;<rigidSurfaces>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `rigidSurfaces`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `rigidSurfaceId` | `integer` | — | Identifier selecting the rigid surface record or set. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `rigidSurfaceIds` — the list needs at least one rigid surface.
- `rigidSurfaceIds` — a rigid surface ID must be a positive integer.

**Example record**

~~~text
ContactRigidSurfaceList;50;51;52
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 50`.

## ContactSegment

A segment of a contact surfacegiven by the grid points of an element face.

**Record format and fields**

`ContactSegment;id;surfaceId;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `surfaceId` | `integer` | Required | Identifier selecting the surface record or set. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | Required | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | 0 | Grid point to which this entry applies. Entry 4. |

**Example record**

~~~text
ContactSegment;1;12;10;11;14;13
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol700_contact_regions.oos)

Reading the example gives `id = 1`, `surfaceId = 12`, `node1 = 10`, `node2 = 11`.

## ContactSet

A contact set of the older contact definition.

**Record format and fields**

`ContactSet;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sourceRegionId` | `integer` | — | Identifier selecting the source region record or set. |
| 2 | `targetRegionId` | `integer` | — | Identifier selecting the target region record or set. |
| 3 | `friction` | `real` | — | Controls tangential resistance to relative motion at the interface. |
| 4 | `minimumDistance` | `real` | — | Minimum distance (length). |
| 5 | `maximumDistance` | `real` | — | Maximum distance (length). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `sourceRegionId` — the set needs at least one contact pair.

**Example record**

~~~text
ContactSet;101;2;1;0.1;0.;1.5
~~~

[Model containing this record](../../../validation/models/read_only_nonlinear/legacy_surface_contact_sets.oos)

Reading the example gives `id = 101`.

## ContactSetUnion

Combines several contact sets into one selectable set.

**Record format and fields**

`ContactSetUnion;id;<memberSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `memberSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberSetId` | `integer` | — | Identifier selecting the member set record or set. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `memberSetId` — the union needs at least one contact set.
- `memberSetId` — a contact set ID must be a positive integer.
- `memberSetId` — a contact set of the union is not the ID of the union itself.

**Example record**

~~~text
ContactSetUnion;200;101;102
~~~

[Model containing this record](../../../validation/models/read_only_nonlinear/legacy_surface_contact_sets.oos)

Reading the example gives `id = 200`.

## ContactSlideline

Defines the primary and secondary lines for sliding contact, together with the stiffness, friction and penetration settings.

**Record format and fields**

`ContactSlideline;id;secondaryLineId;primaryLineId;penaltyScale;frictionId;penetrationKind;frameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `secondaryLineId` | `integer` | Required | Identifier selecting the secondary line record or set. |
| 3 | `primaryLineId` | `integer` | Required | Identifier selecting the primary line record or set. |
| 4 | `penaltyScale` | `real` | 1.0 | Scale of the penalty values the program calculates. |
| 5 | `frictionId` | `integer` | 0 | Identifier selecting the friction record or set. |
| 6 | `penetrationKind` | `integer` | 1 | Selects the penetration kind for ContactSlideline. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |

**Example record**

~~~text
ContactSlideline;4;1;2;1.;3;1;0
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `id = 4`, `secondaryLineId = 1`, `primaryLineId = 2`, `penaltyScale = 1.`.

## ContactSurfaceParams

Sets surface interaction options such as normal orientation, stiffness, tying, offsets and activation times.

**Record format and fields**

`ContactSurfaceParams;contactSetId;parameterName1;parameterValue1;parameterName2;parameterValue2;parameterName3;parameterValue3;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `contactSetId` | `integer` | Required | Identifier selecting the contact set record or set. |
| 2 | `parameterName1` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 1. |
| 3 | `parameterValue1` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 1. |
| 4 | `parameterName2` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 2. |
| 5 | `parameterValue2` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 2. |
| 6 | `parameterName3` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. Entry 3. |
| 7 | `parameterValue3` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. Entry 3. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Both`, `Constant`, `Element`, `Full`, `No`, `Off`, `On`, `Table`, `Yes`.

Accepted parameter names: `BirthTime`, `ContactKind`, `ContactStiffness`, `DeathTime`, `ExtensionFactor`, `InitialPenetration`, `OffsetDistance`, `OffsetKind`, `PenetrationDepth`, `SegmentNormal`, `SideCount`, `TiedContact`, `TiedTolerance`, `ZeroPenetrationTime`.

**Example record**

~~~text
ContactSurfaceParams;101;ContactKind;0;SideCount;2;OffsetDistance;0.
~~~

[Model containing this record](../../../validation/models/read_only_nonlinear/legacy_surface_contact_sets.oos)

Reading the example gives `contactSetId = 101`, `parameterName1 = ContactKind`, `parameterValue1 = 0`, `parameterName2 = SideCount`.

## ContactTable

Defines which contact bodies interact in a load case and the associated contact or glue conditions.

**Record format and fields**

`ContactTable;id;secondaryBodyId;primaryBodyId;setCount;secondaryContactOption;primaryContactOption;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `secondaryBodyId` | `integer` | 0 | Identifier selecting the secondary body record or set. |
| 3 | `primaryBodyId` | `integer` | 0 | Identifier selecting the primary body record or set. |
| 4 | `setCount` | `integer` | 1 | Number of set entries. |
| 5 | `secondaryContactOption` | `integer` | 0 | Selects the secondary contact option for ContactTable. |
| 6 | `primaryContactOption` | `integer` | 0 | Selects the primary contact option for ContactTable. |

**Keyed sections in `sets`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Secondary`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setSecondaryBodyId` | `integer` | — | Identifier selecting the set secondary body record or set. |
| 2 | `contactDistanceTolerance` | `real` | — | Permitted numerical deviation for contact distance. |
| 3 | `separationForce` | `real` | — | Separation force (force). |
| 4 | `frictionCoefficient` | `number` | — | Coefficient in the relation for friction. |
| 5 | `interferenceClosure` | `real` | — | Controls how the initial interference is closed during the contact solution. |
| 6 | `glueOption` | `integer` | — | Selects the glue option for secondarySet. |
| 7 | `contactSearchOrder` | `integer` | — | Order in which the contact search processes candidate surfaces or bodies. |
| 8 | `stressFreeInitialContact` | `integer` | — | Controls whether the initially contacting configuration is treated as stress free. |
| 9 | `glueSeparationOption` | `integer` | — | Selects the glue separation option for secondarySet. |
| 10 | `nearContactDistance` | `real` | — | Near contact distance (length). |
| 11 | `kineticFrictionCoefficient` | `real` | — | Coefficient in the relation for kinetic friction. |
| 12 | `frictionDecayCoefficient` | `real` | — | Coefficient in the relation for friction decay. |
| 13 | `contactMethod` | `text` | — | Selects the contact method for secondarySet. |
| 14 | `adaptiveContactSurface` | `text` | — | Selects adaptive treatment of the surface during contact updates. |
| 15 | `contactThickness` | `real` | — | Contact thickness (length). |
| 16 | `thicknessOffset` | `real` | — | Offset applied to the thickness surface used in the contact geometry. |
| 17 | `penetrationLimit` | `real` | — | Largest permitted surface penetration in the contact test. |
| 18 | `penaltyScaleFactor` | `real` | — | Multiplier for penalty scale. |
| 19 | `contactStartTime` | `real` | — | Contact start time (time). |
| 20 | `contactEndTime` | `real` | — | Contact end time (time). |
| 21 | `maxParametricCoordinate` | `real` | — | Upper bound in the parametric coordinate of the surface or curve. |
| 22 | `initialPenetrationAdjustment` | `integer` | — | Selects the treatment of initial geometric overlap. |
| 23 | `ignoreInitialPenetration` | `integer` | — | Selects whether the initial overlap is excluded from the contact correction. |
| 24 | `automaticContact` | `text` | — | Controls automatic detection or generation of contacting pairs. |
| 25 | `contactSide` | `text` | — | Side of the surface eligible for contact. |
| 26 | `contactForceWeighting` | `text` | — | Weighting used when combining or distributing contact forces. |
| 27 | `monitorDisplacement` | `text` | — | Displacement component or option tracked during the step. |
| 28 | `monitorDisplacementValue` | `real` | — | Prescribed or target value of the monitored displacement. |
| 29 | `initialMonitor` | `real` | — | Starting value or selection of the quantity monitored during stepping. |
| 30 | `contactDamping` | `text` | — | Dissipation assigned to relative normal or tangential motion in contact. |

**Section `Primary`**

**Repeated group `primaryBodies`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `primaryBodyIds` | `integer` | — | List of identifiers on the primary side of contact. |

**Section `FrictionAndBias`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frictionStressLimit` | `real` | — | Upper bound on the tangential frictional stress (force per area). |
| 2 | `contactToleranceBias` | `real` | — | Bias applied to the geometric contact tolerance. |
| 3 | `slidingVelocityThreshold` | `real` | — | Relative tangential velocity at which the sliding rule changes. |
| 4 | `hardSoftRatio` | `real` | — | Relative measure of hard soft. |
| 5 | `touchingBodyOptions` | `integer` | — | Contact options on the approaching side of the pair. |
| 6 | `touchedBodyOptions` | `integer` | — | Contact options on the receiving side of the pair. |

**Section `GlueBreak`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `glueBreakNormalStress` | `real` | — | Glue break normal stress (force per area). |
| 2 | `glueBreakShearStress` | `real` | — | Glue break shear stress (force per area). |
| 3 | `glueBreakNormalExponent` | `real` | — | Power in the law for glue break normal. |
| 4 | `glueBreakShearExponent` | `real` | — | Power in the law for glue break shear. |

**Section `SegmentContact`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `normalPenaltyFactor` | `real` | — | Multiplier for normal penalty. |
| 2 | `augmentationDistance` | `real` | — | Augmentation distance (length). |
| 3 | `tangentPenaltyFactor` | `real` | — | Multiplier for tangent penalty. |
| 4 | `stickSlip` | `real` | — | Selects the treatment of sticking and sliding in frictional contact. |

**Section `HeatTransfer`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `contactHeatTransferCoefficient` | `number` | — | Coefficient in the relation for contact heat transfer. |
| 2 | `nearContactConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact convection. |
| 3 | `nearContactNaturalConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact natural convection. |
| 4 | `nearContactNaturalConvectionExponent` | `number` | — | Power in the law for near contact natural convection. |
| 5 | `emissivity` | `number` | — | Ratio of emitted radiation to that of a black body at the same temperature. |
| 6 | `distanceDependentConvectionCoefficient` | `number` | — | Coefficient in the relation for distance dependent convection. |
| 7 | `nearContactNonlinearConvectionCoefficient` | `number` | — | Coefficient in the relation for near contact nonlinear convection. |
| 8 | `nearContactNonlinearConvectionExponent` | `number` | — | Power in the law for near contact nonlinear convection. |
| 9 | `glueHeatTransfer` | `integer` | — | Controls thermal transfer through a glued interface. |

Accepted words: `BilinearCoulomb`, `Both`, `FrictionAndBias`, `Full`, `GeneralGlue`, `GlueBreak`, `HeatTransfer`, `MonitorDisplacement`, `No`, `NodeToSurface`, `Off`, `On`, `PermanentGlue`, `Primary`, `PrimaryBodies`, `PrimaryBody`, `Secondary`, `SecondaryBody`, `SegmentContact`, `SegmentToSegment`, `StandardGlue`, `TouchOnly`, `Yes`.

Accepted parameter names: `AdaptiveContactSurface`, `AugmentationDistance`, `AutomaticContact`, `ContactDamping`, `ContactDistanceTolerance`, `ContactEndTime`, `ContactForceWeighting`, `ContactHeatTransferCoefficient`, `ContactMethod`, `ContactSearchOrder`, `ContactSide`, `ContactStartTime`, `ContactThickness`, `ContactToleranceBias`, `DistanceDependentConvectionCoefficient`, `Emissivity`, `FrictionCoefficient`, `FrictionDecayCoefficient`, `FrictionStressLimit`, `GlueBreakNormalExponent`, `GlueBreakNormalStress`, `GlueBreakShearExponent`, `GlueBreakShearStress`, `GlueHeatTransfer`, `GlueOption`, `GlueSeparationOption`, `HardSoftRatio`, `IgnoreInitialPenetration`, `InitialMonitor`, `InitialPenetrationAdjustment`, `InterferenceClosure`, `KineticFrictionCoefficient`, `MaxParametricCoordinate`, `MonitorDisplacement`, `MonitorDisplacementValue`, `NearContactConvectionCoefficient`, `NearContactDistance`, `NearContactNaturalConvectionCoefficient`, `NearContactNaturalConvectionExponent`, `NearContactNonlinearConvectionCoefficient`, `NearContactNonlinearConvectionExponent`, `NormalPenaltyFactor`, `PenaltyScaleFactor`, `PenetrationLimit`, `SeparationForce`, `SlidingVelocityThreshold`, `StickSlip`, `StressFreeInitialContact`, `TangentPenaltyFactor`, `ThicknessOffset`, `TouchedBodyOptions`, `TouchingBodyOptions`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `groups` — a touched body ID must be a positive integer.

**Example record**

~~~text
ContactTable;1;;;;;;Secondary;2;;;;;3;;;;;;;;;;;;;;;;;;;;;;;;;Primary;1;1
~~~

[Model containing this record](../../../validation/models/glued_contact/glued_shells_edge_to_edge.oos)

Reading the example gives `id = 1`.

## ContactTable1

The contact table of a load case, a list of [ContactPair](nonlinear_contact.md#contactpair) contact pairs.

**Record format and fields**

`ContactTable1;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | 0 | Identifier in the namespace of this card type. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pairId` | `any` | — | Identifier selecting the pair record or set. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `pairIds` — the table needs at least one contact pair.
- `pairIds` — the first entry must be the ID of a contact pair, not a range.

**Example record**

~~~text
ContactTable1;1;11;12;13
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 1`.

## ContactTrimCurve

The geometry of a trimming curve of a NURBS surface of a rigid contact body.

**Record format and fields**

`ContactTrimCurve;id;pointCount;order;subdivisions;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointCount` | `integer` | Required | Number of point entries. |
| 3 | `order` | `integer` | Required | NORUtrim: the order. |
| 4 | `subdivisions` | `integer` | Required | NSUBtrim: the subdivisions. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Coordinates`**

**Repeated group `coordinates`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coordinate` | `real` | — | Coordinate of the specified point in the selected frame. |

**Section `HomogeneousCoordinates`**

**Repeated group `homogeneousWeights`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `homogeneousWeight` | `real` | — | Weight multiplying the control point in homogeneous coordinates. |

**Section `KnotVector`**

**Repeated group `knots`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `knot` | `real` | — | Parameter value in the knot sequence defining the spline. |

Accepted words: `Coordinates`, `HomogeneousCoordinates`, `KnotVector`, `Node`.

**Example record**

~~~text
ContactTrimCurve;61;5;2;10;Coordinates;10;0.;0.;1.;0.;1.;1.;0.;1.;0.;0.;HomogeneousCoordinates;5;1.;1.;1.;1.;1.;KnotVector;7;0.;0.;0.25;0.5;0.75;1.;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 61`, `pointCount = 5`, `order = 2`, `subdivisions = 10`.

## ContactUnglueNodes

The grid points of a contact body that are taken out of glued contact and use standard contact instead (for a crack, the points along it).

**Record format and fields**

`ContactUnglueNodes;id;bodyId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `bodyId` | `integer` | Required | Identifier selecting the body record or set. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodes` — the card needs the grid points that leave the glued contact.

**Example record**

~~~text
ContactUnglueNodes;10;2;500;Through;502;600;Through;602
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_vcct_unglue_dcb.oos)

Reading the example gives `id = 10`, `bodyId = 2`.

## ContactUserService

Associates a contact body with a user routine and supplies the integer, real and text arguments it receives.

**Record format and fields**

`ContactUserService;bodyId;bodyKind;groupName;userRoutineName;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bodyId` | `integer` | Required | Identifier selecting the body record or set. |
| 2 | `bodyKind` | `text` | — | Selects the body kind for ContactUserService. |
| 3 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 4 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `IntegerData`**

**Repeated group `integerData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `integerValue` | `integer` | — | Integer payload assigned to the selected setting. |

**Section `RealData`**

**Repeated group `realData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |

**Section `TextData`**

**Repeated group `textData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `textValue` | `text` | — | Literal character value assigned to the selected item. |

Accepted words: `ContactBody`, `ContactBody1`, `IntegerData`, `RealData`, `TextData`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `textData` — textData must not be a section key.

**Example record**

~~~text
ContactUserService;1;ContactBody;CONTACT;UFRIC;RealData;1;0.2
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `bodyId = 1`, `bodyKind = ContactBody`, `groupName = CONTACT`, `userRoutineName = UFRIC`.

## CrackClosureCrack

A crack for the virtual crack closure technique, with the options of its growth, the resistance of the material and the grid points of the crack front.

**Record format and fields**

`CrackClosureCrack;setId;crackId;propagationKind;growthMethod;incrementMethod;growthCriterion;growthIncrement;growthResistance;growthResistanceII;growthResistanceIII;growthIncrementTableId;growthResistanceTableId;growthResistanceIITableId;growthResistanceIIITableId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `crackId` | `integer` | 1 | Identifier selecting the crack record or set. |
| 3 | `propagationKind` | `integer` | — | Selects the propagation kind for CrackClosureCrack. |
| 4 | `growthMethod` | `integer` | — | Selects the growth method for CrackClosureCrack. |
| 5 | `incrementMethod` | `integer` | — | Selects the increment method for CrackClosureCrack. |
| 6 | `growthCriterion` | `integer` | — | Criterion used to determine whether the crack advances. |
| 7 | `growthIncrement` | `real` | 0.0 | Amount by which the crack front advances in one growth increment. |
| 8 | `growthResistance` | `real` | 0.0 | Resistance assigned to propagation in the selected fracture mode. |
| 9 | `growthResistanceII` | `real` | 0.0 | Resistance to crack growth in in-plane shear (mode II). |
| 10 | `growthResistanceIII` | `real` | 0.0 | Resistance to crack growth in out-of-plane shear (mode III). |
| 11 | `growthIncrementTableId` | `integer` | 0 | Table supplying the variation of growth increment. |
| 12 | `growthResistanceTableId` | `integer` | 0 | Table supplying the variation of growth resistance. |
| 13 | `growthResistanceIITableId` | `integer` | 0 | Table supplying the variation of growth resistance ii. |
| 14 | `growthResistanceIIITableId` | `integer` | 0 | Table supplying the variation of growth resistance iii. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`, `TypedListSet3`.

**Example record**

~~~text
CrackClosureCrack;1;1;2;2;1;1;0.;0.3;;;0;;;;503;603
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_vcct_unglue_dcb.oos)

Reading the example gives `setId = 1`, `crackId = 1`, `propagationKind = 2`, `growthMethod = 2`.

## NonlinearAdaptiveStepping

Controls automatic load or time increments in a nonlinear analysis.

**Record format and fields**

`NonlinearAdaptiveStepping;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stepping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `minStepRatio` | `real` | — | Relative measure of minimum step. |
| 2 | `maxStepRatio` | `real` | — | Relative measure of maximum step. |
| 3 | `minTimeStep` | `real` | — | Shortest permitted time increment (time). |
| 4 | `maxTimeStep` | `real` | — | Longest permitted time increment (time). |
| 5 | `maxSubsteps` | `integer` | — | Maximum number of subdivisions of the current step. |
| 6 | `recycleCount` | `integer` | — | Number of recycle entries. |
| 7 | `timeStepScaleFactor` | `real` | — | Multiplier for time step scale. |
| 8 | `dampingKind` | `integer` | — | Selects the damping kind for stepping. |
| 9 | `dampingFactor` | `real` | — | Multiplier for damping. |

**Section `Creep`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `creepStepCheck` | `integer` | — | Checks the acceptance of a step against creep evolution. |
| 2 | `tensionCutoffStrain` | `real` | — | Tension cutoff strain (dimensionless). |
| 3 | `tensionCutoffStress` | `real` | — | Tension cutoff stress (force per area). |
| 4 | `cutoffTime` | `real` | — | Cutoff time (time). |

Accepted words: `Creep`, `DampingKindIndex`, `RelativeAccelConvergence`, `Stepping`.

Accepted parameter names: `CreepStepCheck`, `CutoffTime`, `DampingFactor`, `DampingKind`, `MaxStepRatio`, `MaxSubsteps`, `MaxTimeStep`, `MinStepRatio`, `MinTimeStep`, `RecycleCount`, `TensionCutoffStrain`, `TensionCutoffStress`, `TimeStepScaleFactor`.

**Example record**

~~~text
NonlinearAdaptiveStepping;30;Stepping;0.1;1.5;0.01;0.5;1000;10;1.2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_beam_segment_contact.oos)

Reading the example gives `id = 30`.

## NonlinearBushForceTables

Defines the speed-dependent matrix of force tables referenced by a nonlinear bushing load.

**Record format and fields**

`NonlinearBushForceTables;id;form;minimumFreq;maximumFreq;termTable11;termTable12;termTable13;termTable14;termTable15;termTable16;termTable21;termTable22;termTable23;termTable24;termTable25;termTable26;termTable31;termTable32;termTable33;termTable34;termTable35;termTable36;termTable41;termTable42;termTable43;termTable44;termTable45;termTable46;termTable51;termTable52;termTable53;termTable54;termTable55;termTable56;termTable61;termTable62;termTable63;termTable64;termTable65;termTable66`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `form` | `text` | — | Selects the form for NonlinearBushForceTables. |
| 3 | `minimumFreq` | `real` | 0.0 | Lowest frequency of the selected interval (inverse time). |
| 4 | `maximumFreq` | `real` | — | Highest frequency of the selected interval (inverse time). |
| 5 | `termTable11` | `integer` | — | Table identifier associated with term 11 in the specified relation. |
| 6 | `termTable12` | `integer` | — | Table identifier associated with term 12 in the specified relation. |
| 7 | `termTable13` | `integer` | — | Table identifier associated with term 13 in the specified relation. |
| 8 | `termTable14` | `integer` | — | Table identifier associated with term 14 in the specified relation. |
| 9 | `termTable15` | `integer` | — | Table identifier associated with term 15 in the specified relation. |
| 10 | `termTable16` | `integer` | — | Table identifier associated with term 16 in the specified relation. |
| 11 | `termTable21` | `integer` | — | Table identifier associated with term 21 in the specified relation. |
| 12 | `termTable22` | `integer` | — | Table identifier associated with term 22 in the specified relation. |
| 13 | `termTable23` | `integer` | — | Table identifier associated with term 23 in the specified relation. |
| 14 | `termTable24` | `integer` | — | Table identifier associated with term 24 in the specified relation. |
| 15 | `termTable25` | `integer` | — | Table identifier associated with term 25 in the specified relation. |
| 16 | `termTable26` | `integer` | — | Table identifier associated with term 26 in the specified relation. |
| 17 | `termTable31` | `integer` | — | Table identifier associated with term 31 in the specified relation. |
| 18 | `termTable32` | `integer` | — | Table identifier associated with term 32 in the specified relation. |
| 19 | `termTable33` | `integer` | — | Table identifier associated with term 33 in the specified relation. |
| 20 | `termTable34` | `integer` | — | Table identifier associated with term 34 in the specified relation. |
| 21 | `termTable35` | `integer` | — | Table identifier associated with term 35 in the specified relation. |
| 22 | `termTable36` | `integer` | — | Table identifier associated with term 36 in the specified relation. |
| 23 | `termTable41` | `integer` | — | Table identifier associated with term 41 in the specified relation. |
| 24 | `termTable42` | `integer` | — | Table identifier associated with term 42 in the specified relation. |
| 25 | `termTable43` | `integer` | — | Table identifier associated with term 43 in the specified relation. |
| 26 | `termTable44` | `integer` | — | Table identifier associated with term 44 in the specified relation. |
| 27 | `termTable45` | `integer` | — | Table identifier associated with term 45 in the specified relation. |
| 28 | `termTable46` | `integer` | — | Table identifier associated with term 46 in the specified relation. |
| 29 | `termTable51` | `integer` | — | Table identifier associated with term 51 in the specified relation. |
| 30 | `termTable52` | `integer` | — | Table identifier associated with term 52 in the specified relation. |
| 31 | `termTable53` | `integer` | — | Table identifier associated with term 53 in the specified relation. |
| 32 | `termTable54` | `integer` | — | Table identifier associated with term 54 in the specified relation. |
| 33 | `termTable55` | `integer` | — | Table identifier associated with term 55 in the specified relation. |
| 34 | `termTable56` | `integer` | — | Table identifier associated with term 56 in the specified relation. |
| 35 | `termTable61` | `integer` | — | Table identifier associated with term 61 in the specified relation. |
| 36 | `termTable62` | `integer` | — | Table identifier associated with term 62 in the specified relation. |
| 37 | `termTable63` | `integer` | — | Table identifier associated with term 63 in the specified relation. |
| 38 | `termTable64` | `integer` | — | Table identifier associated with term 64 in the specified relation. |
| 39 | `termTable65` | `integer` | — | Table identifier associated with term 65 in the specified relation. |
| 40 | `termTable66` | `integer` | — | Table identifier associated with term 66 in the specified relation. |

Accepted words: `AsymmetricForm`, `Constant`, `DiagonalForm`, `Element`, `SymmetricForm`, `Table`.

**Example record**

~~~text
NonlinearBushForceTables;21;DiagonalForm;100.;800.;501;502
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

Reading the example gives `id = 21`, `form = DiagonalForm`, `minimumFreq = 100.`, `maximumFreq = 800.`.

## NonlinearBushLoad3D

Applies a nonlinear three-dimensional force between coincident grid points as a function of relative displacement, velocity and rotor speed.

**Record format and fields**

`NonlinearBushLoad3D;setId;nodeA;nodeB;loadId1;loadId2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `loadId1` | `integer` | — | Identifier addressing bushing force set data. |
| 5 | `loadId2` | `integer` | — | Identifier addressing bushing force set data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
NonlinearBushLoad3D;100;1;2;21;22
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

Reading the example gives `setId = 100`, `nodeA = 1`, `nodeB = 2`, `loadId1 = 21`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 1`, `nodeB = 2`.

## NonlinearHarmonicFreqContinuation

Specifies forcing frequencies used for continuation in a nonlinear harmonic analysis.

**Record format and fields**

`NonlinearHarmonicFreqContinuation;id;initialFreq;initialStep;minimumStepSize;maximumStepSize;maximumSteps;minimumFreq;maximumFreq;derivativeStep;printOnFailure;outputRequest;outputFreqStep;outputFreqTolerance;outputStartFreq;outputEndFreq`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `initialFreq` | `real` | 0.0 | Starting frequency of the continuation procedure (inverse time). |
| 3 | `initialStep` | `real` | Required | First increment used by the stepping procedure. |
| 4 | `minimumStepSize` | `real` | — | Lower bound on one increment of the continuation variable. |
| 5 | `maximumStepSize` | `real` | — | Upper bound on one increment of the continuation variable. |
| 6 | `maximumSteps` | `integer` | 3 | Maximum number of increments to take. |
| 7 | `minimumFreq` | `real` | 0.0 | Lowest frequency of the selected interval (inverse time). |
| 8 | `maximumFreq` | `real` | — | Highest frequency of the selected interval (inverse time). |
| 9 | `derivativeStep` | `real` | 1.0E-3 | Perturbation used to evaluate the derivative numerically. |
| 10 | `printOnFailure` | `text` | No | Controls diagnostic output when a step fails. |
| 11 | `outputRequest` | `text` | — | The output request line is there. |
| 12 | `outputFreqStep` | `real` | — | Frequency spacing between successive outputs. |
| 13 | `outputFreqTolerance` | `real` | 5.0 | Permitted numerical deviation for output frequency. |
| 14 | `outputStartFreq` | `real` | — | Lowest frequency for which output is requested. |
| 15 | `outputEndFreq` | `real` | — | Highest frequency for which output is requested. |

Accepted words: `DefaultOutput`, `No`, `Yes`.

**Example record**

~~~text
NonlinearHarmonicFreqContinuation;30;300.;1.;;;400;250.;600.;0.001;No;DefaultOutput;10.;5.;300.;600.
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

Reading the example gives `id = 30`, `initialFreq = 300.`, `initialStep = 1.`, `maximumSteps = 400`.

## NonlinearHarmonicFreqList

The forcing frequencies of a nonlinear harmonic response, listed one by one.

**Record format and fields**

`NonlinearHarmonicFreqList;id;<frequencies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `frequencies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frequency` | `real` | — | Number of cycles per unit time. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `frequencies` — the card needs at least one frequency.
- `frequencies` — a forcing frequency must be greater than zero.

**Example record**

~~~text
NonlinearHarmonicFreqList;16;450.;500.;550.
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_radial_gap_squeeze_film.oos)

Reading the example gives `id = 16`.

## NonlinearHarmonicFreqSteps

The forcing frequencies of a nonlinear harmonic response at equal steps.

**Record format and fields**

`NonlinearHarmonicFreqSteps;id;startFreq;freqStep;stepCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `startFreq` | `real` | Required | Starting frequency of the specified range. |
| 3 | `freqStep` | `real` | Required | Increment in frequency between continuation steps. |
| 4 | `stepCount` | `integer` | 1 | Number of step entries. |

**Example record**

~~~text
NonlinearHarmonicFreqSteps;15;400.;20.;10
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_radial_gap_squeeze_film.oos)

Reading the example gives `id = 15`, `startFreq = 400.`, `freqStep = 20.`, `stepCount = 10`.

## NonlinearHarmonicParams

The parameters of a nonlinear harmonic response analysis.

**Record format and fields**

`NonlinearHarmonicParams;id;subharmonicFactor;harmonicCount;freqListId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `subharmonicFactor` | `integer` | 1 | Multiplier for subharmonic. |
| 3 | `harmonicCount` | `integer` | Required | Number of harmonic entries. |
| 4 | `freqListId` | `integer` | Required | Identifier addressing nonlinear frequency data. |

**Example record**

~~~text
NonlinearHarmonicParams;20;2;3;16
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_radial_gap_squeeze_film.oos)

Reading the example gives `id = 20`, `subharmonicFactor = 2`, `harmonicCount = 3`, `freqListId = 16`.

## NonlinearOutputItems

Selects additional quantities for nonlinear result output.

**Record format and fields**

`NonlinearOutputItems;id;<outputItems>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `outputItems`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `outputItem` | `text` | — | Quantity requested for recovery or output. |

Accepted words: `CauchyCreepStrain`, `CauchyElasticStrain`, `CauchyPlasticStrain`, `CauchyStress`, `CauchyThermalStrain`, `CauchyTotalStrain`, `ElemStateVariables`, `EquivalentElasticStrain`, `EquivalentVonMisesStress`, `FailureIndex1`, `FailureIndex2`, `FailureIndex3`, `FailureIndex4`, `MajorEngineeringStrain`, `TotalTemperature`.

**Example record**

~~~text
NonlinearOutputItems;9;EquivalentVonMisesStress;EquivalentElasticStrain;TTSTRNED
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 9`.

## NonlinearRadialGap

Defines a circular gap between two coincident grid points for a nonlinear dynamic response.

**Record format and fields**

`NonlinearRadialGap;setId;nodeA;nodeB;plane;stiffnessTableId;clearanceTableId;frictionTableId;radius;smoothing;smoothingValue`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `plane` | `text` | PlaneXy | Reference plane used for the geometric definition. |
| 5 | `stiffnessTableId` | `integer` | 0 | Table supplying the variation of stiffness. |
| 6 | `clearanceTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 7 | `frictionTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 8 | `radius` | `real` | 0.0 | Radial dimension measured from the centre or axis (length). |
| 9 | `smoothing` | `text` | — | Selects the treatment of variation between adjacent table samples. |
| 10 | `smoothingValue` | `real` | 1.0E6 | The value of the smoothing function. |

Accepted words: `Gamma`, `PlaneXy`, `PlaneYz`, `PlaneZx`.

**Example record**

~~~text
NonlinearRadialGap;100;1;2;PlaneXy;401;402;403;;Gamma;1.E+6
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_radial_gap_squeeze_film.oos)

Reading the example gives `setId = 100`, `nodeA = 1`, `nodeB = 2`, `plane = PlaneXy`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 1`, `nodeB = 2`.
- [TableDynamic1](tables.md#tabledynamic1) via `clearanceTableId = 402`, `frictionTableId = 403`.

## NonlinearSqueezeFilmDamper

Defines the transient nonlinear forces from a radial squeeze-film damper between two grid points.

**Record format and fields**

`NonlinearSqueezeFilmDamper;setId;nodeA;nodeB;plane;bearingDiameter;bearingLength;bearingClearance;bearingKind;viscosity;vapourPressure;portCount;pressure1;portAngle1;pressure2;portAngle2;pointCount;offset1;offset2;serviceGroup;serviceEvaluation;serviceParameter1;serviceParameter2;serviceParameter3;serviceParameter4;serviceParameter5;serviceParameter6;serviceParameter7;serviceParameter8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `plane` | `text` | PlaneXy | Reference plane used for the geometric definition. |
| 5 | `bearingDiameter` | `real` | — | Bearing diameter (length). |
| 6 | `bearingLength` | `real` | — | Bearing length (length). |
| 7 | `bearingClearance` | `real` | — | Clearance between the bearing and journal surfaces (length). |
| 8 | `bearingKind` | `text` | Long | Selects the bearing kind for NonlinearSqueezeFilmDamper. |
| 9 | `viscosity` | `real` | — | Viscous response coefficient in the selected constitutive or flow law. |
| 10 | `vapourPressure` | `real` | — | Vapour pressure (force per area). |
| 11 | `portCount` | `integer` | — | Number of port entries. |
| 12 | `pressure1` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 1. |
| 13 | `portAngle1` | `real` | — | The angular position of port 1. |
| 14 | `pressure2` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 2. |
| 15 | `portAngle2` | `real` | — | The angular position of port 2. |
| 16 | `pointCount` | `integer` | 101 | Number of point entries. |
| 17 | `offset1` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 1. |
| 18 | `offset2` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 2. |
| 19 | `serviceGroup` | `text` | — | Name identifying the group of user services. |
| 20 | `serviceEvaluation` | `text` | — | The "evalname" argument passed to the service. |
| 21 | `serviceParameter1` | `real` | 0.0 | Argument 1 passed to the user service in the ordered input data. |
| 22 | `serviceParameter2` | `real` | 0.0 | Argument 2 passed to the user service in the ordered input data. |
| 23 | `serviceParameter3` | `real` | 0.0 | Argument 3 passed to the user service in the ordered input data. |
| 24 | `serviceParameter4` | `real` | 0.0 | Argument 4 passed to the user service in the ordered input data. |
| 25 | `serviceParameter5` | `real` | 0.0 | Argument 5 passed to the user service in the ordered input data. |
| 26 | `serviceParameter6` | `real` | 0.0 | Argument 6 passed to the user service in the ordered input data. |
| 27 | `serviceParameter7` | `real` | 0.0 | Argument 7 passed to the user service in the ordered input data. |
| 28 | `serviceParameter8` | `real` | 0.0 | Argument 8 passed to the user service in the ordered input data. |

Accepted words: `Long`, `PlaneXy`, `PlaneXz`, `PlaneYz`, `PlaneZx`, `Short`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `values` — a field of the card must be a finite number.

**Example record**

~~~text
NonlinearSqueezeFilmDamper;100;1;2;PlaneXy;50.;20.;0.1;Short;2.E-8;0.002;1;0.2;90.
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_radial_gap_squeeze_film.oos)

Reading the example gives `setId = 100`, `nodeA = 1`, `nodeB = 2`, `plane = PlaneXy`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 1`, `nodeB = 2`.

## NonlinearStepControl

The control parameters of the load or time stepping(mechanical, thermal and coupled analysis) and of the contact analysis.

**Record format and fields**

`NonlinearStepControl;id;totalTime;controlSetting;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `totalTime` | `real` | 1.0 | Total time (time). |
| 3 | `controlSetting` | `text` | — | Setting assigned to the named contact or step control. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `General`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `maxIterations` | `integer` | — | Maximum number of iterations permitted at this stage. |
| 2 | `minIterations` | `integer` | — | Minimum number of iterations before the convergence decision. |
| 3 | `maxBisections` | `integer` | — | Maximum permitted subdivisions of an increment by bisection. |
| 4 | `creepOption` | `integer` | — | Selects the creep option for general. |

**Section `LoadCaseContinue`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `incrementCountCoupled` | `integer` | — | Number of increments specified for the coupled solution. |
| 2 | `convergenceCoupled` | `text` | — | Selects convergence criteria for the coupled solution. |
| 3 | `displacementToleranceCoupled` | `real` | — | Convergence tolerance on displacement for the Coupled solution. |
| 4 | `loadToleranceCoupled` | `real` | — | Convergence tolerance on load for the Coupled solution. |
| 5 | `energyToleranceCoupled` | `real` | — | Convergence tolerance on energy for the Coupled solution. |
| 6 | `maxDivergencesCoupled` | `integer` | — | Upper bound on Divergences for the Coupled increment. |
| 7 | `maxBisectionsCoupled` | `integer` | — | Upper bound on Bisections for the Coupled increment. |
| 8 | `maxIterationsCoupled` | `integer` | — | Upper bound on Iterations for the Coupled increment. |
| 9 | `minIterationsCoupled` | `integer` | — | Minimum iterations before checking convergence of the coupled increment. |

**Section `FixedStepping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `incrementCount` | `integer` | — | Number of increment entries. |
| 2 | `outputInterval` | `integer` | — | Spacing between successive output requests. |

**Section `AdaptiveStepping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `initialTimeStepFactor` | `real` | — | Multiplier for initial time step. |
| 2 | `minTimeStepFactor` | `real` | — | Multiplier for minimum time step. |
| 3 | `maxTimeStepFactor` | `real` | — | Multiplier for maximum time step. |
| 4 | `desiredIterations` | `integer` | — | Target iteration count used when adjusting the next increment. |
| 5 | `timeStepScaleFactor` | `real` | — | Multiplier for time step scale. |
| 6 | `intermediateOutput` | `integer` | — | Controls output at intermediate increments or stations. |
| 7 | `maxSubsteps` | `integer` | — | Maximum number of subdivisions of the current step. |
| 8 | `dampingKind` | `integer` | — | Selects the damping kind for adaptiveStepping. |
| 9 | `dampingFactor` | `real` | — | Multiplier for damping. |
| 10 | `criteriaTableId` | `integer` | — | Table supplying the variation of criteria. |
| 11 | `physicsOption` | `integer` | — | Selects the physics option for adaptiveStepping. |
| 12 | `targetLimit` | `integer` | — | Limit on the monitored quantity used to accept or change the step. |
| 13 | `minStepRatio` | `real` | — | Relative measure of minimum step. |
| 14 | `maxStepRatio` | `real` | — | Relative measure of maximum step. |
| 15 | `timeStepAdjustInterval` | `integer` | — | Number or interval of steps between changes to the step size. |
| 16 | `stepMultiplier` | `integer` | — | Factor applied to the preceding step size. |
| 17 | `timeStepHoldBounds` | `real` | — | Controls the bounds maintained while the step size is held fixed. |
| 18 | `displacementConvergence` | `real` | — | Specifies the criterion based on change in displacement. |

**Section `ArcLengthMethod`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `steppingMethod` | `text` | — | Selects the stepping method for arcLengthMethod. |
| 2 | `initialTimeStepFactorAdapted` | `real` | — | Multiplier on the first adaptive time increment. |
| 3 | `minAdaptiveRatio` | `real` | — | Relative measure of minimum adaptive. |
| 4 | `maxAdaptiveRatio` | `real` | — | Relative measure of maximum adaptive. |
| 5 | `desiredIterationsAdapted` | `integer` | — | Target iteration count for adaptive increment control. |
| 6 | `maxSubstepsAdapted` | `integer` | — | Maximum number of adaptive subdivisions of an increment. |

**Section `HeatAnalysis`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `convergenceHeat` | `text` | — | Selects convergence criteria for the heat-transfer solution. |
| 2 | `displacementToleranceHeat` | `real` | — | Convergence tolerance on displacement for the Heat solution. |
| 3 | `loadToleranceHeat` | `real` | — | Convergence tolerance on load for the Heat solution. |
| 4 | `energyToleranceHeat` | `real` | — | Convergence tolerance on energy for the Heat solution. |
| 5 | `stiffnessMethodHeat` | `text` | — | Selects the matrix-update method in the thermal solution. |
| 6 | `stiffnessStepHeat` | `integer` | — | Increment interval for updating the thermal tangent matrix. |
| 7 | `maxQuasiNewtonVectorsHeat` | `integer` | — | Upper bound on QuasiNewtonVectors for the Heat increment. |
| 8 | `maxLineSearchesHeat` | `integer` | — | Upper bound on LineSearches for the Heat increment. |
| 9 | `lineSearchToleranceHeat` | `real` | — | Tolerance controlling termination of the thermal line search. |

**Section `MechanicalAnalysis`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `convergenceCriteria` | `text` | — | Selects the residual or increment measures checked for convergence. |
| 2 | `displacementTolerance` | `real` | — | Permitted numerical deviation for displacement. |
| 3 | `loadTolerance` | `real` | — | Permitted numerical deviation for load. |
| 4 | `energyTolerance` | `real` | — | Permitted numerical deviation for energy. |
| 5 | `stiffnessMethod` | `text` | — | Selects the stiffness method for mechanicalAnalysis. |
| 6 | `stiffnessUpdateStep` | `integer` | — | Step interval or stage at which the tangent stiffness is updated. |
| 7 | `massRatioConvergence` | `integer` | — | Mass-ratio criterion used when checking convergence of the step. |
| 8 | `maxQuasiNewtonVectors` | `integer` | — | Limit on the vectors retained in a quasi-Newton update. |
| 9 | `maxLineSearches` | `integer` | — | Maximum line-search updates in an iteration. |
| 10 | `lineSearchTolerance` | `real` | — | Permitted numerical deviation for line search. |
| 11 | `frictionStress` | `real` | — | Friction stress (force per area). |

**Section `CoupledAnalysis`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `heatFromPlasticWork` | `real` | — | Specifies conversion of plastic work into heat. |
| 2 | `heatFromFriction` | `real` | — | Specifies conversion of frictional work into heat at the interface. |

Accepted words: `AdaptiveStepping`, `ArcLengthMethod`, `CoupledAnalysis`, `Crisfield`, `CriteriaTableIdKind`, `FixedStepping`, `General`, `HeatAnalysis`, `LoadCaseAccumulation`, `LoadCaseContinue`, `LoadCasePerformance`, `MechanicalAnalysis`, `MildlyNonlinear`, `ModifiedRiks`, `QuasiLinear`, `Riks`, `SeverelyNonlinear`, `TypeKind`.

Accepted parameter names: `ConvergenceCoupled`, `ConvergenceCriteria`, `ConvergenceHeat`, `CreepOption`, `CriteriaTableId`, `DampingFactor`, `DampingKind`, `DesiredIterations`, `DesiredIterationsAdapted`, `DisplacementConvergence`, `DisplacementTolerance`, `DisplacementToleranceCoupled`, `DisplacementToleranceHeat`, `EnergyTolerance`, `EnergyToleranceCoupled`, `EnergyToleranceHeat`, `FrictionStress`, `HeatFromFriction`, `HeatFromPlasticWork`, `IncrementCount`, `IncrementCountCoupled`, `InitialTimeStepFactor`, `InitialTimeStepFactorAdapted`, `IntermediateOutput`, `LineSearchTolerance`, `LineSearchToleranceHeat`, `LoadTolerance`, `LoadToleranceCoupled`, `LoadToleranceHeat`, `MassRatioConvergence`, `MaxAdaptiveRatio`, `MaxBisections`, `MaxBisectionsCoupled`, `MaxDivergencesCoupled`, `MaxIterations`, `MaxIterationsCoupled`, `MaxLineSearches`, `MaxLineSearchesHeat`, `MaxQuasiNewtonVectors`, `MaxQuasiNewtonVectorsHeat`, `MaxStepRatio`, `MaxSubsteps`, `MaxSubstepsAdapted`, `MaxTimeStepFactor`, `MinAdaptiveRatio`, `MinIterations`, `MinIterationsCoupled`, `MinStepRatio`, `MinTimeStepFactor`, `OutputInterval`, `PhysicsOption`, `StepMultiplier`, `SteppingMethod`, `StiffnessMethod`, `StiffnessMethodHeat`, `StiffnessStepHeat`, `StiffnessUpdateStep`, `TargetLimit`, `TimeStepAdjustInterval`, `TimeStepHoldBounds`, `TimeStepScaleFactor`.

**Example record**

~~~text
NonlinearStepControl;1;1.;;AdaptiveStepping;0.1;1.E-4;0.25
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_vcct_unglue_dcb.oos)

Reading the example gives `id = 1`, `totalTime = 1.`.

## NonlinearUserOutput

Declares output quantities provided by a user routine for an explicit nonlinear analysis.

**Record format and fields**

`NonlinearUserOutput;id;groupName;outputKind;timeInterval;stepInterval;outputName;<entities>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `outputKind` | `text` | ElemExplicitOutput | Selects the output kind for NonlinearUserOutput. |
| 4 | `timeInterval` | `real` | — | Time between the events or updates specified by the record. |
| 5 | `stepInterval` | `integer` | — | Spacing of the steps at which this action is taken. |
| 6 | `outputName` | `text` | — | Text naming the output. |

**Repeated group `entities`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entityId` | `integer` | — | Identifier selecting the entity record or set. |

Accepted words: `ElemExplicitOutput`, `NodeExplicitOutput`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `entityIds` — the card needs at least one element or grid point.
- `entityIds` — an element or grid point ID must be a positive integer.

**Example record**

~~~text
NonlinearUserOutput;91;initex;ElemExplicitOutput;1.E-4;;BOXOUT;1001;1002;1003;1004;1005;1006
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 91`, `groupName = initex`, `outputKind = ElemExplicitOutput`, `timeInterval = 1.E-4`.

## SlidelineFriction

The friction between two bodies of a slideline contact region.

**Record format and fields**

`SlidelineFriction;id;stickStiffness;staticFriction`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stickStiffness` | `real` | 0.0 | Tangential stiffness used while the interface sticks. |
| 3 | `staticFriction` | `real` | Required | The coefficient of static friction. |

**Example record**

~~~text
SlidelineFriction;3;;0.2
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `id = 3`, `staticFriction = 0.2`.

## SlidelineOutput

The secondary nodes at which a slideline contact analysis writes output.

**Record format and fields**

`SlidelineOutput;id;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `By`, `Through`.

**Example record**

~~~text
SlidelineOutput;4;201;Through;203
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `id = 4`.

## SlidelineSegments

A curve of line segments of a slideline contact region, given by its grid points in topological order (one segment between every two consecutive points).

**Record format and fields**

`SlidelineSegments;id;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node` — the line needs at least one grid point.

**Example record**

~~~text
SlidelineSegments;1;203;202;201
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `id = 1`.

## SlidelineWidth

The width (3-D slideline) or thickness (2-D) of each line segment of the [SlidelineSegments](nonlinear_contact.md#slidelinesegments) of the same ID.

**Record format and fields**

`SlidelineWidth;segmentsId;<widths>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `segmentsId` | `integer` | Required | Identifier addressing slideline segments data. |

**Repeated group `widths`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `width` | `any` | — | Transverse extent in model length units. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `width` — the card needs at least one width.
- `width` — a width must be greater than zero.
- `width` — a single width has no end.
- `rangeStep` — the BY increment must be a finite number.
- `rangeStep` — the BY increment must go from the first width to the last one.

**Example record**

~~~text
SlidelineWidth;2;10.;10.;10.;10.
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_slideline_friction.oos)

Reading the example gives `segmentsId = 2`.

## StepControlCriteria

Defines target increments or bounds for monitored quantities used by [NonlinearStepControl](nonlinear_contact.md#nonlinearstepcontrol).

**Record format and fields**

`StepControlCriteria;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Keyed sections in `criteria`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `StrainIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `PlasticStrainIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `CreepStrainIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `NormalizedCreepStrainIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `StressIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `StrainEnergyIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `TemperatureIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `DisplacementIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `RotationIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

**Section `NormalizedStressIncrement`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `any` | — | Identifier selecting the set record or set. |
| 2 | `limit1` | `real` | — | Increment limit or target for criterion range 1. |
| 3 | `rangeEnd1` | `real` | — | Endpoint in the criterion variable defining range 1. |
| 4 | `limit2` | `real` | — | Increment limit or target for criterion range 2. |
| 5 | `rangeEnd2` | `real` | — | Endpoint in the criterion variable defining range 2. |
| 6 | `limit3` | `real` | — | Increment limit or target for criterion range 3. |
| 7 | `rangeEnd3` | `real` | — | Endpoint in the criterion variable defining range 3. |
| 8 | `limit4` | `real` | — | Increment limit or target for criterion range 4. |
| 9 | `rangeEnd4` | `real` | — | Endpoint in the criterion variable defining range 4. |

Accepted words: `All`, `Constant`, `CreepStrainIncrement`, `DisplacementIncrement`, `Element`, `NormalizedCreepStrainIncrement`, `NormalizedStressIncrement`, `PlasticStrainIncrement`, `RotationIncrement`, `StrainEnergyIncrement`, `StrainIncrement`, `StressIncrement`, `Table`, `TemperatureIncrement`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `criterion` — the table needs at least one criterion.

**Example record**

~~~text
StepControlCriteria;40;DisplacementIncrement;41;0.005;;;;;;;;StrainIncrement;All;0.001
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 40`.
