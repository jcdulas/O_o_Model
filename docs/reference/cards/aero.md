# Aerodynamics and aeroelasticity

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AeroBeamSpline2

A beam spline, a line along which the structure bends and twists, that carries the displacements of a set of structural grid points to a row of aerodynamic boxes (or the elements of a body) and the forces back.

**Record format and fields**

`AeroBeamSpline2;id;aeroPanelId;firstBox;lastBox;nodeSetId;linearFlexibility;bendingTorsionRatio;frameId;rotationFlexibilityX;rotationFlexibilityY;usage`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier addressing aero element data. |
| 3 | `firstBox` | `integer` | Required | Identifier addressing aero box data. |
| 4 | `lastBox` | `integer` | Required | Identifier addressing aero box data. |
| 5 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 6 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 7 | `bendingTorsionRatio` | `real` | 1.0 | Relative measure of bending torsion. |
| 8 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 9 | `rotationFlexibilityX` | `real` | 0.0 | Compliance of the spline coupling in rotation about local X. |
| 10 | `rotationFlexibilityY` | `real` | 0.0 | Compliance of the spline coupling in rotation about local Y. |
| 11 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `lastBox` — `lastBox` cannot be below `firstBox`.

**Example record**

~~~text
AeroBeamSpline2;3101;3001;3001;3004;3100;0.;1.;;0.;0.
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

Reading the example gives `id = 3101`, `aeroPanelId = 3001`, `firstBox = 3001`, `lastBox = 3004`.

**Referenced records in this example**

- [AeroBody2](aero.md#aerobody2) via `aeroPanelId = 3001`.

## AeroBeamSpline5

A beam spline like [AeroBeamSpline2](aero.md#aerobeamspline2), for any aerodynamic geometry: the points it moves are listed in an [AeroBoxList](aero.md#aeroboxlist) instead of being a run of box numbers.

**Record format and fields**

`AeroBeamSpline5;id;aeroPanelId;aeroBoxListId;nodeSetId;linearFlexibility;bendingTorsionRatio;frameId;rotationFlexibilityX;rotationFlexibilityY;usage;method;functionKind;coreRadius`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier addressing aero element data. |
| 3 | `aeroBoxListId` | `integer` | Required | Identifier addressing aero list data. |
| 4 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 5 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 6 | `bendingTorsionRatio` | `real` | 1.0 | Relative measure of bending torsion. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `rotationFlexibilityX` | `real` | 0.0 | Compliance of the spline coupling in rotation about local X. |
| 9 | `rotationFlexibilityY` | `real` | 0.0 | Compliance of the spline coupling in rotation about local Y. |
| 10 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 11 | `method` | `text` | — | Selects the method for AeroBeamSpline5. |
| 12 | `functionKind` | `text` | — | Selects the function kind for AeroBeamSpline5. |
| 13 | `coreRadius` | `real` | — | Core radius (length). |

Accepted words: `Antisymmetric`, `Asymmetric`, `Beam`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `RigidSurfaceSpline`, `Symmetric`, `Table`, `WendlandFunction0`, `WendlandFunction2`.

**Example record**

~~~text
AeroBeamSpline5;1201;1001;1202;1203;0.;1.;20;-1.;-1.;Both;Beam
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 1201`, `aeroPanelId = 1001`, `aeroBoxListId = 1202`, `nodeSetId = 1203`.

**Referenced records in this example**

- [AeroLiftingPanel1](aero.md#aeroliftingpanel1) via `aeroPanelId = 1001`.
- [RectFrame2](coordinate_systems.md#rectframe2) via `frameId = 20`.

## AeroBody2

An aerodynamic body (a slender body surrounded by an interference tube) for the Doublet-Lattice method, given by its leading point and its length.

**Record format and fields**

`AeroBody2;id;propId;positionFrameId;slenderElemCount;interferenceElemCount;slenderListId;interferenceListId;interferenceGroupId;xCoord1;yCoord1;zCoord1;length`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `slenderElemCount` | `integer` | 0 | Number of slender element entries. |
| 5 | `interferenceElemCount` | `integer` | 0 | Number of interference element entries. |
| 6 | `slenderListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 7 | `interferenceListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 8 | `interferenceGroupId` | `integer` | Required | Identifier selecting the interference group record or set. |
| 9 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 10 | `yCoord1` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 1. |
| 11 | `zCoord1` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 1. |
| 12 | `length` | `real` | Required | Length (length). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `slenderElemCount` — `slenderElemCount` cannot be negative.
- `interferenceElemCount` — `interferenceElemCount` cannot be negative.
- `slenderElemCount` — `slenderElemCount` or `slenderListId` is required.
- `interferenceElemCount` — `interferenceElemCount` or `interferenceListId` is required.
- `interferenceGroupId` — `interferenceGroupId` cannot be negative.
- `xCoord1` — `xCoord1`, `yCoord1` and `zCoord1` must be finite numbers.

**Example record**

~~~text
AeroBody2;3001;3000;;8;4;;;1;-100.;1.E+3;0.;400.
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 3001`, `propId = 3000`, `slenderElemCount = 8`, `interferenceElemCount = 4`.

**Referenced records in this example**

- [AeroBodyProp2](aero.md#aerobodyprop2) via `propId = 3000`.

## AeroBodyProp2

The cross section of the [AeroBody2](aero.md#aerobody2) bodies that name it, and the angles at which the interference elements receive.

**Record format and fields**

`AeroBodyProp2;id;orientation;width;aspectRatio;slenderHalfWidthListId;interferenceHalfWidthListId;angleListId1;angleListId2;angleList1FirstElem;angleList1LastElem;angleList2FirstElem;angleList2LastElem`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero property namespace. |
| 2 | `orientation` | `text` | — | Specifies the local direction or axis convention used to orient the data. |
| 3 | `width` | `real` | Required | Transverse extent in model length units. |
| 4 | `aspectRatio` | `real` | Required | Relative measure of aspect. |
| 5 | `slenderHalfWidthListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 6 | `interferenceHalfWidthListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 7 | `angleListId1` | `integer` | 0 | Identifier addressing aero factor data. |
| 8 | `angleListId2` | `integer` | 0 | Identifier addressing aero factor data. |
| 9 | `angleList1FirstElem` | `integer` | 0 | First aerodynamic element to which angle list 1 applies. |
| 10 | `angleList1LastElem` | `integer` | 0 | Last aerodynamic element to which angle list 1 applies. |
| 11 | `angleList2FirstElem` | `integer` | 0 | First aerodynamic element to which angle list 2 applies. |
| 12 | `angleList2LastElem` | `integer` | 0 | Last aerodynamic element to which angle list 2 applies. |

Accepted words: `Constant`, `Element`, `PlaneZy`, `Table`, `YDirection`, `ZDirection`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `angleList1LastElem` — `angleList1LastElem` cannot be smaller than `angleList1FirstElem`.
- `angleList2LastElem` — `angleList2LastElem` cannot be smaller than `angleList2FirstElem`.

**Example record**

~~~text
AeroBodyProp2;3000;PlaneZy;40.;1.;3002;;3003;;1;4
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 3000`, `orientation = PlaneZy`, `width = 40.`, `aspectRatio = 1.`.

## AeroBoxList

A list of aerodynamic boxes (or aerodynamic grid points) that an [AeroControlSurface](aero.md#aerocontrolsurface), an [AeroComponent](aero.md#aerocomponent) or an [AeroSurfaceSpline4](aero.md#aerosurfacespline4) or [AeroBeamSpline5](aero.md#aerobeamspline5) names by its set ID.

**Record format and fields**

`AeroBoxList;id;<entries>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entry` | `any` | — | Member of the ordered input list, interpreted by the selected entry type. |

Accepted words: `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
AeroBoxList;1200;1020;1024;1028;1032
~~~

[Model containing this record](../../../validation/models/aero_sol144/aero_model.oos)

Reading the example gives `id = 1200`.

## AeroComponent

A component of the aerodynamic or structural model that a monitor point ([MonitorIntegratedLoad1](matrices.md#monitorintegratedload1), [MonitorDisplacement](matrices.md#monitordisplacement)) or an external spline integrates over.

**Record format and fields**

`AeroComponent;name;listKind;<lists>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `name` | `text` | — | Up to eight characters. |
| 2 | `listKind` | `text` | — | Selects the list kind for AeroComponent. |

**Repeated group `lists`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `listId` | `integer` | — | Identifier selecting the list record or set. |

Accepted words: `AeroBoxList`, `AeroPanels`, `ComponentId`, `Constant`, `Element`, `IdListSet1`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `listIds` — a blank field inside the list of `listIds`.
- `listIds` — `listIds` is required.

**Example record**

~~~text
AeroComponent;AILA;AeroBoxList;1210
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `name = AILA`, `listKind = AeroBoxList`.

## AeroComponentUnion

A component that is the union of other components.

**Record format and fields**

`AeroComponentUnion;name;<labels>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `name` | `text` | — | Up to eight characters. |

**Repeated group `labels`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroComponentUnion;SURFA;AILA;ELEVA
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `name = SURFA`.

## AeroControlSchedule

The schedule of a control surface, its deflection as a function of the Mach number and the angle of attack, for a trim.

**Record format and fields**

`AeroControlSchedule;id;controlSurfaceId;angleOfAttackListId;machListId;scheduleListId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `controlSurfaceId` | `integer` | Required | Identifier selecting the control surface record or set. |
| 3 | `angleOfAttackListId` | `integer` | 0 | Identifier selecting the angle of attack list record or set. |
| 4 | `machListId` | `integer` | 0 | Identifier selecting the mach list record or set. |
| 5 | `scheduleListId` | `integer` | Required | Identifier selecting the schedule list record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `angleOfAttackListId` — `angleOfAttackListId` and `machListId` cannot both be blank.

**Example record**

~~~text
AeroControlSchedule;1601;1201;1602;;1603
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1601`, `controlSurfaceId = 1201`, `angleOfAttackListId = 1602`, `scheduleListId = 1603`.

## AeroControlSurface

An aerodynamic control surface, a variable of the trim that rotates up to two groups of aerodynamic boxes about their hinge lines.

**Record format and fields**

`AeroControlSurface;id;label;frameId1;boxListId1;frameId2;boxListId2;effectiveness;linearDownwash;referenceChord;referenceArea;deflectionLowerLimit;deflectionUpperLimit;hingeMomentLowerLimit;hingeMomentUpperLimit;lowerLimitTableId;upperLimitTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 3 | `frameId1` | `integer` | Required | Identifier addressing coordinate data. |
| 4 | `boxListId1` | `integer` | Required | Identifier addressing aero list data. |
| 5 | `frameId2` | `integer` | 0 | Identifier addressing coordinate data. |
| 6 | `boxListId2` | `integer` | 0 | Identifier addressing aero list data. |
| 7 | `effectiveness` | `real` | 1.0 | Multiplier on the modeled response to control-surface motion. |
| 8 | `linearDownwash` | `text` | — | Downwash term used in the linear aerodynamic relation. |
| 9 | `referenceChord` | `real` | 1.0 | Chord length used to nondimensionalize aerodynamic quantities. |
| 10 | `referenceArea` | `real` | 1.0 | Reference area (length squared). |
| 11 | `deflectionLowerLimit` | `real` | — | Lower travel limit of the control surface. |
| 12 | `deflectionUpperLimit` | `real` | — | Upper travel limit of the control surface. |
| 13 | `hingeMomentLowerLimit` | `real` | — | Lower bound on the hinge moment of the control surface. |
| 14 | `hingeMomentUpperLimit` | `real` | — | Upper bound on the hinge moment of the control surface. |
| 15 | `lowerLimitTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 16 | `upperLimitTableId` | `integer` | 0 | Identifier addressing dynamic table data. |

Accepted words: `Constant`, `Element`, `LinearDownwash`, `NoLinearDownwash`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `boxListId2` — `boxListId2` is required with `frameId2`.
- `frameId2` — `frameId2` is required with `boxListId2`.
- `effectiveness` — `effectiveness` cannot be zero.
- `lowerLimitTableId` — `lowerLimitTableId` cannot be given together with `deflectionLowerLimit`.
- `upperLimitTableId` — `upperLimitTableId` cannot be given together with `deflectionUpperLimit`.

**Example record**

~~~text
AeroControlSurface;1211;AIL;10;1210
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1211`, `label = AIL`, `frameId1 = 10`, `boxListId1 = 1210`.

## AeroControlSurfaceNodes

The structural grid points that belong to a control surface, whose mass gives the moment of inertia of the surface about its hinge line (so that the hinge moments include the inertial forces).

**Record format and fields**

`AeroControlSurfaceNodes;id;label;nodeSetId1;nodeSetId2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 3 | `nodeSetId1` | `integer` | Required | Identifier of the set supplying the grid points. Entry 1. |
| 4 | `nodeSetId2` | `integer` | 0 | Identifier of the set supplying the grid points. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroControlSurfaceNodes;1221;ELEV;1220
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1221`, `label = ELEV`, `nodeSetId1 = 1220`.

## AeroControlVector

A vector of values of the aerodynamic extra points (the control surfaces, rigid body motions and general controllers of a trim), which the user defined forces of an [AeroDownwash](aero.md#aerodownwash), [AeroForceVector](aero.md#aeroforcevector) or [AeroPressureVector](aero.md#aeropressurevector) card are evaluated at.

**Record format and fields**

`AeroControlVector;id;<variables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `variables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 2 | `controlValue` | `real` | — | Setting of the associated aerodynamic control variable. |

Accepted words: `AngleOfAttack`, `Constant`, `Element`, `Intercept`, `PitchRate`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `SideSlip`, `Table`, `YawRate`.

**Example record**

~~~text
AeroControlVector;1412;VANE;1.;Intercept;0.
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1412`.

## AeroController

A general controller of a trim, an aerodynamic extra point whose forces come from the [AeroDownwash](aero.md#aerodownwash), [AeroForceVector](aero.md#aeroforcevector) and [AeroPressureVector](aero.md#aeropressurevector) cards that name it.

**Record format and fields**

`AeroController;id;label;units`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 3 | `units` | `text` | — | Measurement convention for the data to which the label applies. |

Accepted words: `AngleOfAttack`, `Constant`, `Element`, `PitchRate`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `SideSlip`, `Table`, `YawRate`.

**Example record**

~~~text
AeroController;1313;TIPLD;N
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1313`, `label = TIPLD`, `units = N`.

## AeroDivergence

The Mach numbers of a static aeroelastic divergence analysis.

**Record format and fields**

`AeroDivergence;id;rootCount;<machNumbers>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `rootCount` | `integer` | 1 | Number of root entries. |

**Repeated group `machNumbers`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber` | `real` | — | Ratio of flow speed to the local speed of sound. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `rootCount` — `rootCount` must be a positive integer.
- `machNumber1` — the card needs at least one Mach number (`machNumber1`).
- `machNumber` — the Mach numbers of the card must be distinct.

**Example record**

~~~text
AeroDivergence;70;2;0.5
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 70`, `rootCount = 2`.

## AeroDownwash

The normal wash (downwash) loading that goes with one control vector of the aerodynamic configuration.

**Record format and fields**

`AeroDownwash;machNumber;symmetricXz;symmetricXy;controlVectorId;matrixName;interpolationMatrixName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber` | `real` | Required | Ratio of flow speed to the local speed of sound. |
| 2 | `symmetricXz` | `text` | — | Symmetry convention for the aerodynamic model across the xz plane. |
| 3 | `symmetricXy` | `text` | — | Symmetry convention for the aerodynamic model across the xy plane. |
| 4 | `controlVectorId` | `integer` | Required | Identifier selecting the control vector record or set. |
| 5 | `matrixName` | `text` | — | Text naming the matrix. |
| 6 | `interpolationMatrixName` | `text` | — | Text naming the interpolation matrix. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `matrixName` — `matrixName` is required.
- `matrixName` — `matrixName` must be a nonempty matrix name without control characters.
- `interpolationMatrixName` — `interpolationMatrixName` must be a nonempty matrix name without control characters.

**Example record**

~~~text
AeroDownwash;0.5;Asymmetric;Asymmetric;20;DWJ;DWJI
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

Reading the example gives `machNumber = 0.5`, `symmetricXz = Asymmetric`, `symmetricXy = Asymmetric`, `controlVectorId = 20`.

## AeroFactorList

A list of real numbers that an aerodynamic card names by its set ID.

**Record format and fields**

`AeroFactorList;id;<factors>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `factors`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `factor` | `real` | — | Multiplier on the associated contribution. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `value1` — the card needs at least one number (`value1`).

**Example record**

~~~text
AeroFactorList;3010;0.;20.;25.;25.;15.
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

Reading the example gives `id = 3010`.

## AeroFiniteBeamSpline7

A finite beam spline that maps the motion of structural grid points to the boxes (or aerodynamic grid points) of an [AeroBoxList](aero.md#aeroboxlist) through a beam it builds, in all six degrees of freedom or in the three translations.

**Record format and fields**

`AeroFiniteBeamSpline7;id;aeroPanelId;aeroBoxListId;nodeSetId;linearFlexibility;bendingTorsionRatio;frameId;usage;method;rotationFlexibility;bendingExtensionRatio;minBeamLengthRatio`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | 0 | Identifier selecting the aero panel record or set. |
| 3 | `aeroBoxListId` | `integer` | Required | Identifier selecting the aero box list record or set. |
| 4 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 5 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 6 | `bendingTorsionRatio` | `real` | 1.0 | Relative measure of bending torsion. |
| 7 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 8 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 9 | `method` | `text` | — | Selects the method for AeroFiniteBeamSpline7. |
| 10 | `rotationFlexibility` | `real` | 0.0 | Rotational flexibility of the spline coupling. |
| 11 | `bendingExtensionRatio` | `real` | 1.0 | Relative measure of bending extension. |
| 12 | `minBeamLengthRatio` | `real` | 0.01 | Relative measure of minimum beam length. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `FiniteBeamSpline3`, `FiniteBeamSpline6`, `Force`, `Symmetric`, `Table`.

**Example record**

~~~text
AeroFiniteBeamSpline7;110;;111;112;0.;1.;20;Both;FiniteBeamSpline6
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 110`, `aeroBoxListId = 111`, `nodeSetId = 112`, `linearFlexibility = 0.`.

## AeroFiniteSurfaceSpline6

A finite surface spline between two meshes in 6 or 3 degrees of freedom.

**Record format and fields**

`AeroFiniteSurfaceSpline6;id;aeroPanelId;aeroBoxListId;nodeSetId;linearFlexibility;method;usage;surfaceKind;surfaceElemListId;independentPointCount;dependentPointCount;surfaceMethod;rotationFlexibility;connectionMethod;nodeCount;projectionTolerance;cycleCount;augmentationWeight`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | 0 | Identifier selecting the aero panel record or set. |
| 3 | `aeroBoxListId` | `integer` | Required | Identifier selecting the aero box list record or set. |
| 4 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 5 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 6 | `method` | `text` | — | Selects the method for AeroFiniteSurfaceSpline6. |
| 7 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 8 | `surfaceKind` | `text` | — | Selects the surface kind for AeroFiniteSurfaceSpline6. |
| 9 | `surfaceElemListId` | `integer` | 0 | Identifier selecting the surface element list record or set. |
| 10 | `independentPointCount` | `integer` | 3 | Number of independent point entries. |
| 11 | `dependentPointCount` | `integer` | 3 | Number of dependent point entries. |
| 12 | `surfaceMethod` | `text` | — | Selects the surface method for AeroFiniteSurfaceSpline6. |
| 13 | `rotationFlexibility` | `real` | 0.0 | Rotational flexibility of the spline coupling. |
| 14 | `connectionMethod` | `text` | — | Selects the connection method for AeroFiniteSurfaceSpline6. |
| 15 | `nodeCount` | `integer` | 1 | Number of node entries. |
| 16 | `projectionTolerance` | `real` | 100.0 | Permitted numerical deviation for projection. |
| 17 | `cycleCount` | `integer` | 3 | Number of cycle entries. |
| 18 | `augmentationWeight` | `real` | 0.0 | Weight of the additional term in the aerodynamic interpolation. |

Accepted words: `AeroMesh`, `Antisymmetric`, `Asymmetric`, `Both`, `CircularBias`, `Constant`, `Displacement`, `Element`, `FiniteSurfaceSpline3`, `FiniteSurfaceSpline6`, `Force`, `NodeProximity`, `Structure`, `Symmetric`, `Table`, `VibrationSimple3`, `VibrationSimple6`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `independentPointCount` — `independentPointCount` must be a positive integer.
- `dependentPointCount` — `dependentPointCount` must be a positive integer.
- `nodeCount` — `nodeCount` must be a positive integer.
- `cycleCount` — `cycleCount` must be a positive integer.

**Example record**

~~~text
AeroFiniteSurfaceSpline6;120;;126;112;0.;FiniteSurfaceSpline6;Both;AeroMesh;126
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 120`, `aeroBoxListId = 126`, `nodeSetId = 112`, `linearFlexibility = 0.`.

## AeroFlutter

Selects the flutter solution method and the factor tables that define the flight conditions.

**Record format and fields**

`AeroFlutter;id;method;densityFactorsId;machFactorsId;reducedFreqFactorsId;interpolationMethod;eigenvalueCount;maxFrequency;epsilon`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `method` | `text` | — | Selects the method for AeroFlutter. |
| 3 | `densityFactorsId` | `integer` | Required | Identifier addressing aero flutter factor data. |
| 4 | `machFactorsId` | `integer` | Required | Identifier addressing aero flutter factor data. |
| 5 | `reducedFreqFactorsId` | `integer` | Required | Identifier addressing aero flutter factor data. |
| 6 | `interpolationMethod` | `text` | — | Selects the interpolation method for AeroFlutter. |
| 7 | `eigenvalueCount` | `integer` | — | Number of eigenvalue entries. Alternative to `maxFrequency`. |
| 8 | `maxFrequency` | `real` | — | Maximum frequency (inverse time). Alternative to `eigenvalueCount`. |
| 9 | `epsilon` | `real` | — | Numerical perturbation or tolerance in the associated relation. |

Accepted words: `Constant`, `Element`, `KMethod`, `KMethodEfficient`, `Linear`, `PkMethod`, `PkMethodNoLoop`, `PkMethodNoLoopSweep`, `PkMethodSweep`, `Surface`, `Table`, `TermwiseCubic`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `eigenvalueCount` — `eigenvalueCount` must be a positive integer, or blank.

**Example record**

~~~text
AeroFlutter;81;PkMethod;1;2;3;Linear;6
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `id = 81`, `method = PkMethod`, `densityFactorsId = 1`, `machFactorsId = 2`.

## AeroFlutterFactors

A list of the density ratios, Mach numbers, reduced frequencies or velocities of a flutter analysis, that an [AeroFlutter](aero.md#aeroflutter) card names by its set ID.

**Record format and fields**

`AeroFlutterFactors;id;<factors>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `factors`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `factor` | `any` | — | Multiplier on the associated contribution. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `factor1` — the card needs at least one factor (`factor1`).
- `factorCount` — `factorCount` must be a positive integer.
- `factorCount` — `factorCount` is at most 1000000.

**Example record**

~~~text
AeroFlutterFactors;3;3.E+5;4.5E+5;6.E+5;7.5E+5;9.E+5
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `id = 3`.

## AeroForceVector

A vector of forces, absolute or per unit dynamic pressure, that goes with one control vector of the aerodynamic configuration and is used by the static aeroelastic trim.

**Record format and fields**

`AeroForceVector;machNumber;symmetricXz;symmetricXy;controlVectorId;mesh;loadSetId;matrixName;perUnitPressure`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber` | `real` | Required | Ratio of flow speed to the local speed of sound. |
| 2 | `symmetricXz` | `text` | — | Symmetry convention for the aerodynamic model across the xz plane. |
| 3 | `symmetricXy` | `text` | — | Symmetry convention for the aerodynamic model across the xy plane. |
| 4 | `controlVectorId` | `integer` | Required | Identifier selecting the control vector record or set. |
| 5 | `mesh` | `text` | — | Identifies the mesh or mesh option used for the selected interpolation. |
| 6 | `loadSetId` | `integer` | 0 | Identifier selecting the load set record or set. |
| 7 | `matrixName` | `text` | — | Text naming the matrix. |
| 8 | `perUnitPressure` | `text` | — | Sets the normalization of the aerodynamic data with respect to pressure. |

Accepted words: `AeroMesh`, `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `PerDynamicPressure`, `Structure`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `matrixName` — `matrixName` must be a nonempty matrix name without control characters.

**Example record**

~~~text
AeroForceVector;0.5;Asymmetric;Asymmetric;11;AeroMesh;;FRCK
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_direct_matrices.oos)

Reading the example gives `machNumber = 0.5`, `symmetricXz = Asymmetric`, `symmetricXy = Asymmetric`, `controlVectorId = 11`.

## AeroGust

A stationary vertical gust for the aeroelastic response analyses.

**Record format and fields**

`AeroGust;id;dynamicLoadId;gustScale;gustOriginX;velocity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dynamicLoadId` | `integer` | Required | Identifier addressing dynamic load set data. |
| 3 | `gustScale` | `real` | Required | Scale applied to the gust input. |
| 4 | `gustOriginX` | `real` | Required | Streamwise location defining the origin of the gust profile. |
| 5 | `velocity` | `real` | Required | Rate of displacement in the specified direction (length per time). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `gustScale` — `gustScale` must not be zero.

**Example record**

~~~text
AeroGust;91;92;0.01;0.;1.E+5
~~~

[Model containing this record](../../../validation/models/aero_sol144/sol146_gust_monitor.oos)

Reading the example gives `id = 91`, `dynamicLoadId = 92`, `gustScale = 0.01`, `gustOriginX = 0.`.

## AeroLabelList

Defines a named list of short labels for reference by other aeroelastic records.

**Record format and fields**

`AeroLabelList;id;<names>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `names`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroLabelList;1203;TPS;SMOOTH
~~~

[Model containing this record](../../../validation/models/read_only_aero/sol144_external_spline.oos)

Reading the example gives `id = 1203`.

## AeroLiftingPanel1

Defines a lifting-surface panel by its leading-edge endpoints and the chord at each end.

**Record format and fields**

`AeroLiftingPanel1;id;propId;positionFrameId;spanBoxCount;chordBoxCount;spanDivisionListId;chordDivisionListId;interferenceGroupId;xCoord1;yCoord1;zCoord1;rootChord;xCoord4;yCoord4;zCoord4;tipChord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `spanBoxCount` | `integer` | 0 | Number of span box entries. |
| 5 | `chordBoxCount` | `integer` | 0 | Number of chord box entries. |
| 6 | `spanDivisionListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 7 | `chordDivisionListId` | `integer` | 0 | Identifier addressing aero factor data. |
| 8 | `interferenceGroupId` | `integer` | Required | Identifier selecting the interference group record or set. |
| 9 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 10 | `yCoord1` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 1. |
| 11 | `zCoord1` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 1. |
| 12 | `rootChord` | `real` | 0.0 | Chord at the inboard end of the aerodynamic panel, in length units. |
| 13 | `xCoord4` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 4. |
| 14 | `yCoord4` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 4. |
| 15 | `zCoord4` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 4. |
| 16 | `tipChord` | `real` | 0.0 | Chord at the outboard end of the aerodynamic panel, in length units. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `spanBoxCount` — `spanBoxCount` cannot be negative.
- `chordBoxCount` — `chordBoxCount` cannot be negative.
- `spanBoxCount` — `spanBoxCount` or `spanDivisionListId` is required.
- `chordBoxCount` — `chordBoxCount` or `chordDivisionListId` is required.
- `xCoord1` — `xCoord1`, `yCoord1` and `zCoord1` must be finite numbers.
- `xCoord4` — `xCoord4`, `yCoord4` and `zCoord4` must be finite numbers.
- `rootChord` — `rootChord` and `tipChord` cannot both be zero.

**Example record**

~~~text
AeroLiftingPanel1;1001;1000;;4;4;;;1;0.;0.;0.;200.;0.;480.;0.;200.
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 1001`, `propId = 1000`, `spanBoxCount = 4`, `chordBoxCount = 4`.

**Referenced records in this example**

- [AeroLiftingPanelProp1](aero.md#aeroliftingpanelprop1) via `propId = 1000`.

## AeroLiftingPanelProp1

The property of the [AeroLiftingPanel1](aero.md#aeroliftingpanel1) panels that name it, which lists the aerodynamic bodies ([AeroBody2](aero.md#aerobody2) cards) that interact with them in the Doublet-Lattice method.

**Record format and fields**

`AeroLiftingPanelProp1;id;body1;body2;body3;body4;body5;body6`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero property namespace. |
| 2 | `body1` | `integer` | 0 | Identifier of aerodynamic body 1 associated with the panel property. |
| 3 | `body2` | `integer` | 0 | Identifier of aerodynamic body 2 associated with the panel property. |
| 4 | `body3` | `integer` | 0 | Identifier of aerodynamic body 3 associated with the panel property. |
| 5 | `body4` | `integer` | 0 | Identifier of aerodynamic body 4 associated with the panel property. |
| 6 | `body5` | `integer` | 0 | Identifier of aerodynamic body 5 associated with the panel property. |
| 7 | `body6` | `integer` | 0 | Identifier of aerodynamic body 6 associated with the panel property. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroLiftingPanelProp1;1000;3001
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 1000`, `body1 = 3001`.

## AeroMachBoxPanel3

The edges of an aerodynamic surface for the Mach box method.

**Record format and fields**

`AeroMachBoxPanel3;id;propId;positionFrameId;wingPointListId;controlPointListId1;controlPointListId2;xCoord1;yCoord1;zCoord1;rootChord;xCoord4;yCoord4;zCoord4;tipChord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `wingPointListId` | `integer` | Required | Identifier selecting the wing point list record or set. |
| 5 | `controlPointListId1` | `integer` | 0 | Identifier selecting the control point list record or set. |
| 6 | `controlPointListId2` | `integer` | 0 | Identifier selecting the control point list record or set. |
| 7 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 8 | `yCoord1` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 1. |
| 9 | `zCoord1` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 1. |
| 10 | `rootChord` | `real` | Required | Chord at the inboard end of the aerodynamic panel, in length units. |
| 11 | `xCoord4` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 4. |
| 12 | `yCoord4` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 4. |
| 13 | `zCoord4` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 4. |
| 14 | `tipChord` | `real` | 0.0 | Chord at the outboard end of the aerodynamic panel, in length units. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `xCoord1` — `xCoord1`, `yCoord1` and `zCoord1` must be finite numbers.
- `xCoord4` — `xCoord4`, `yCoord4` and `zCoord4` must be finite numbers.

**Example record**

~~~text
AeroMachBoxPanel3;2000;2001;0;2002;;;0.;0.;0.;200.;0.;1.E+3;0.;200.
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `id = 2000`, `propId = 2001`, `positionFrameId = 0`, `wingPointListId = 2002`.

## AeroMachBoxProp3

The property of the [AeroMachBoxPanel3](aero.md#aeromachboxpanel3) Mach box surfaces that name it, with the number of boxes in the flow direction and the cranks and control surfaces of the planform.

**Record format and fields**

`AeroMachBoxProp3;id;boxCount;controlSurfaceCount;pointX5;pointY5;pointX6;pointY6;pointX7;pointY7;pointX8;pointY8;pointX9;pointY9;pointX10;pointY10;pointX11;pointY11;pointX12;pointY12`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero property namespace. |
| 2 | `boxCount` | `integer` | Required | Number of box entries. |
| 3 | `controlSurfaceCount` | `integer` | Required | Number of control surface entries. |
| 4 | `pointX5` | `real` | — | X coordinate of the specified point at position 5. |
| 5 | `pointY5` | `real` | — | Y coordinate of the specified point at position 5. |
| 6 | `pointX6` | `real` | — | X coordinate of the specified point at position 6. |
| 7 | `pointY6` | `real` | — | Y coordinate of the specified point at position 6. |
| 8 | `pointX7` | `real` | — | X coordinate of the specified point at position 7. |
| 9 | `pointY7` | `real` | — | Y coordinate of the specified point at position 7. |
| 10 | `pointX8` | `real` | — | X coordinate of the specified point at position 8. |
| 11 | `pointY8` | `real` | — | Y coordinate of the specified point at position 8. |
| 12 | `pointX9` | `real` | — | X coordinate of the specified point at position 9. |
| 13 | `pointY9` | `real` | — | Y coordinate of the specified point at position 9. |
| 14 | `pointX10` | `real` | — | X coordinate of the specified point at position 10. |
| 15 | `pointY10` | `real` | — | Y coordinate of the specified point at position 10. |
| 16 | `pointX11` | `real` | — | X coordinate of the specified point at position 11. |
| 17 | `pointY11` | `real` | — | Y coordinate of the specified point at position 11. |
| 18 | `pointX12` | `real` | — | X coordinate of the specified point at position 12. |
| 19 | `pointY12` | `real` | — | Y coordinate of the specified point at position 12. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `boxCount` — `boxCount` must be an integer from 1 to 49.
- `controlSurfaceCount` — `controlSurfaceCount` must be 0, 1 or 2.

**Example record**

~~~text
AeroMachBoxProp3;2001;10;0;0.;-1.;0.;-1.
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `id = 2001`, `boxCount = 10`, `controlSurfaceCount = 0`, `pointX5 = 0.`.

## AeroMachFreqPairs2

A list of Mach number and reduced frequency pairs for the aerodynamic matrices.

**Record format and fields**

`AeroMachFreqPairs2;machNumber1;reducedFreq1;machNumber2;reducedFreq2;machNumber3;reducedFreq3;machNumber4;reducedFreq4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber1` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 1. |
| 2 | `reducedFreq1` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 1. |
| 3 | `machNumber2` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 2. |
| 4 | `reducedFreq2` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 2. |
| 5 | `machNumber3` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 3. |
| 6 | `reducedFreq3` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 3. |
| 7 | `machNumber4` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 4. |
| 8 | `reducedFreq4` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 4. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `machNumber1` — the card needs at least one pair (`machNumber1` and `reducedFreq1`).
- `machNumber` — the card holds at most 4 pairs; use several cards.

**Example record**

~~~text
AeroMachFreqPairs2;0.5;0.001;0.5;0.05;0.5;0.1;0.5;0.2
~~~

[Model containing this record](../../../validation/models/aero_models/sol146_strip_theory.oos)

Reading the example gives `machNumber1 = 0.5`, `reducedFreq1 = 0.001`, `machNumber2 = 0.5`, `reducedFreq2 = 0.05`.

## AeroMachFreqTable1

A table of Mach numbers and reduced frequencies at which the aerodynamic matrices are computed.

**Record format and fields**

`AeroMachFreqTable1;machNumber1;machNumber2;machNumber3;machNumber4;machNumber5;machNumber6;machNumber7;machNumber8;reducedFreq1;reducedFreq2;reducedFreq3;reducedFreq4;reducedFreq5;reducedFreq6;reducedFreq7;reducedFreq8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber1` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 1. |
| 2 | `machNumber2` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 2. |
| 3 | `machNumber3` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 3. |
| 4 | `machNumber4` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 4. |
| 5 | `machNumber5` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 5. |
| 6 | `machNumber6` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 6. |
| 7 | `machNumber7` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 7. |
| 8 | `machNumber8` | `real` | — | Ratio of flow speed to the local speed of sound. Entry 8. |
| 9 | `reducedFreq1` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 1. |
| 10 | `reducedFreq2` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 2. |
| 11 | `reducedFreq3` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 3. |
| 12 | `reducedFreq4` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 4. |
| 13 | `reducedFreq5` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 5. |
| 14 | `reducedFreq6` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 6. |
| 15 | `reducedFreq7` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 7. |
| 16 | `reducedFreq8` | `real` | — | Nondimensional oscillation frequency used for the unsteady aerodynamic model. Entry 8. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `machNumber1` — the card needs at least one Mach number (`machNumber1`).
- `machNumbers` — the card holds at most 8 Mach numbers; use several cards.
- `reducedFreq1` — the card needs at least one reduced frequency (`reducedFreq1`).
- `reducedFreqs` — the card holds at most 8 reduced frequencies; use several cards.

**Example record**

~~~text
AeroMachFreqTable1;0.5;;;;;;;;0.001;0.05;0.1;0.3;0.6;1.
~~~

[Model containing this record](../../../validation/models/aero_sol144/sol145_flutter.oos)

Reading the example gives `machNumber1 = 0.5`, `reducedFreq1 = 0.001`, `reducedFreq2 = 0.05`, `reducedFreq3 = 0.1`.

## AeroNode

A grid point of an aerodynamic mesh that the [AeroQuad4](aero.md#aeroquad4) and [AeroTria3](aero.md#aerotria3) cards connect.

**Record format and fields**

`AeroNode;id;positionFrameId;xCoord1;xCoord2;xCoord3;displacementFrameId;scaleId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 3 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 4 | `xCoord2` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 2. |
| 5 | `xCoord3` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 3. |
| 6 | `displacementFrameId` | `integer` | 0 | Coordinate system in which the displacement components are expressed. |
| 7 | `scaleId` | `integer` | 0 | Identifier selecting the scale record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroNode;5001;;0.;0.;0.;;5000
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 5001`, `xCoord1 = 0.`, `xCoord2 = 0.`, `xCoord3 = 0.`.

## AeroNodeScale

The reference lengths that scale the coordinates of the aerodynamic grid points ([AeroNode](aero.md#aeronode)) which name it.

**Record format and fields**

`AeroNodeScale;id;referenceLength1;referenceLength2;referenceLength3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceLength1` | `real` | 1.0 | Reference length 1 (length). |
| 3 | `referenceLength2` | `real` | 1.0 | Reference length 2 (length). |
| 4 | `referenceLength3` | `real` | 1.0 | Reference length 3 (length). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroNodeScale;5000;1.E+3;1.E+3;1.E+3
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 5000`, `referenceLength1 = 1.E+3`, `referenceLength2 = 1.E+3`, `referenceLength3 = 1.E+3`.

## AeroPistonPanel5

An aerodynamic macro element for piston theory, a panel cut into strips that span the whole chord.

**Record format and fields**

`AeroPistonPanel5;id;propId;positionFrameId;spanBoxCount;spanDivisionListId;theory;thicknessIntegralListId;xCoord1;yCoord1;zCoord1;rootChord;xCoord4;yCoord4;zCoord4;tipChord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `spanBoxCount` | `integer` | 0 | Number of span box entries. |
| 5 | `spanDivisionListId` | `integer` | 0 | Identifier selecting the span division list record or set. |
| 6 | `theory` | `integer` | 0 | Selects the constitutive or failure theory to apply. |
| 7 | `thicknessIntegralListId` | `integer` | 0 | Identifier selecting the thickness integral list record or set. |
| 8 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 9 | `yCoord1` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 1. |
| 10 | `zCoord1` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 1. |
| 11 | `rootChord` | `real` | 0.0 | Chord at the inboard end of the aerodynamic panel, in length units. |
| 12 | `xCoord4` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 4. |
| 13 | `yCoord4` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 4. |
| 14 | `zCoord4` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 4. |
| 15 | `tipChord` | `real` | 0.0 | Chord at the outboard end of the aerodynamic panel, in length units. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `spanBoxCount` — `spanBoxCount` cannot be negative.
- `spanBoxCount` — `spanBoxCount` or `spanDivisionListId` is required.
- `theory` — `theory` must be 0, 1 or 2.
- `xCoord1` — `xCoord1`, `yCoord1` and `zCoord1` must be finite numbers.
- `xCoord4` — `xCoord4`, `yCoord4` and `zCoord4` must be finite numbers.
- `rootChord` — `rootChord` and `tipChord` cannot both be zero.

**Example record**

~~~text
AeroPistonPanel5;7000;7001;0;4;;0;7002;0.;0.;0.;200.;0.;1.E+3;0.;200.
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_piston_theory.oos)

Reading the example gives `id = 7000`, `propId = 7001`, `positionFrameId = 0`, `spanBoxCount = 4`.

## AeroPistonProp5

The properties of the strips of an [AeroPistonPanel5](aero.md#aeropistonpanel5) panel (piston theory): the angle of attack, the chordwise coordinates and the thickness ratios that the [AeroFactorList](aero.md#aerofactorlist) cards list, and the control surface chord of every strip.

**Record format and fields**

`AeroPistonProp5;id;angleOfAttackCount;angleOfAttackListId;chordCoordCount;chordCoordListId;thicknessRatioCount;thicknessRatioListId;<controlChordRatios>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero property namespace. |
| 2 | `angleOfAttackCount` | `integer` | Required | Number of angle of attack entries. |
| 3 | `angleOfAttackListId` | `integer` | Required | Identifier selecting the angle of attack list record or set. |
| 4 | `chordCoordCount` | `integer` | 0 | Number of chord coordinate entries. |
| 5 | `chordCoordListId` | `integer` | 0 | Identifier selecting the chord coordinate list record or set. |
| 6 | `thicknessRatioCount` | `integer` | 0 | Number of thickness ratio entries. |
| 7 | `thicknessRatioListId` | `integer` | 0 | Identifier selecting the thickness ratio list record or set. |

**Repeated group `controlChordRatios`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `controlChordRatio` | `real` | — | Relative measure of control chord. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `angleOfAttackCount` — `angleOfAttackCount` must be a positive integer.
- `chordCoordCount` — `chordCoordCount` cannot be negative.
- `chordCoordListId` — `chordCoordListId` is required when `chordCoordCount` is not 0.
- `thicknessRatioCount` — `thicknessRatioCount` cannot be negative.
- `thicknessRatioListId` — `thicknessRatioListId` is required when `thicknessRatioCount` is not 0.
- `controlChordRatio1` — the continuation with `controlChordRatio1` is required.

**Example record**

~~~text
AeroPistonProp5;7001;1;7003;0;0;0;0;0.;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_piston_theory.oos)

Reading the example gives `id = 7001`, `angleOfAttackCount = 1`, `angleOfAttackListId = 7003`, `chordCoordCount = 0`.

## AeroPressureVector

A vector of pressure per unit dynamic pressure that goes with one control vector of the aerodynamic configuration.

**Record format and fields**

`AeroPressureVector;machNumber;symmetricXz;symmetricXy;controlVectorId;matrixName;interpolationMatrixName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `machNumber` | `real` | Required | Ratio of flow speed to the local speed of sound. |
| 2 | `symmetricXz` | `text` | — | Symmetry convention for the aerodynamic model across the xz plane. |
| 3 | `symmetricXy` | `text` | — | Symmetry convention for the aerodynamic model across the xy plane. |
| 4 | `controlVectorId` | `integer` | Required | Identifier selecting the control vector record or set. |
| 5 | `matrixName` | `text` | — | Text naming the matrix. |
| 6 | `interpolationMatrixName` | `text` | — | Text naming the interpolation matrix. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `matrixName` — `matrixName` is required.
- `matrixName` — `matrixName` must be a nonempty matrix name without control characters.
- `interpolationMatrixName` — `interpolationMatrixName` must be a nonempty matrix name without control characters.

**Example record**

~~~text
AeroPressureVector;0.5;Asymmetric;Asymmetric;10;PRSJ
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_direct_matrices.oos)

Reading the example gives `machNumber = 0.5`, `symmetricXz = Asymmetric`, `symmetricXy = Asymmetric`, `controlVectorId = 10`.

## AeroQuad4

A quadrilateral element of an aerodynamic mesh, given by four aerodynamic grid points ([AeroNode](aero.md#aeronode)).

**Record format and fields**

`AeroQuad4;id;componentId;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `componentId` | `integer` | Required | Identifier selecting the component record or set. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | Required | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | Required | Grid point to which this entry applies. Entry 4. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroQuad4;6001;1;5001;5002;5005;5004
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 6001`, `componentId = 1`, `node1 = 5001`, `node2 = 5002`.

## AeroRigidSpline

A rigid body spline that moves the boxes (or the aerodynamic grid points) of an [AeroBoxList](aero.md#aeroboxlist) like a rigid body whose motion is given by six structural degrees of freedom, whatever the aerodynamic geometry is.

**Record format and fields**

`AeroRigidSpline;id;aeroPanelId;aeroBoxListId;usage;node1;components1;node2;components2;node3;components3;node4;components4;node5;components5;node6;components6`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | 0 | Identifier selecting the aero panel record or set. |
| 3 | `aeroBoxListId` | `integer` | Required | Identifier selecting the aero box list record or set. |
| 4 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 5 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 6 | `components1` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 7 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 8 | `components2` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 9 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 10 | `components3` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |
| 11 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 12 | `components4` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 4. |
| 13 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 14 | `components5` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 5. |
| 15 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 16 | `components6` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 6. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1` — the card needs at least one (`node1`, `components1`) pair.
- `node1` — the card has at most six (`node1`, `components1`) pairs.
- `components1` — the (`node1`, `components1`) pairs must select exactly six degrees of freedom.

**Example record**

~~~text
AeroRigidSpline;150;;151;Both;12;123456
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 150`, `aeroBoxListId = 151`, `usage = Both`, `node1 = 12`.

## AeroRigidTrimVariable

A rigid body motion that is a variable of a static aeroelastic trim (the angle of attack, a rate, an acceleration of the aircraft).

**Record format and fields**

`AeroRigidTrimVariable;id;label`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |

Accepted words: `AngleOfAttack`, `Constant`, `Element`, `PitchRate`, `RigidAccelFamily`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `SideSlip`, `Table`, `YawRate`.

**Example record**

~~~text
AeroRigidTrimVariable;1301;AngleOfAttack
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 1301`, `label = AngleOfAttack`.

## AeroSplineCurveBlend

A curve based blend of two splines.

**Record format and fields**

`AeroSplineCurveBlend;id;splineId1;splineId2;option;aeroBoxListId;depth1;depth2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `splineId1` | `integer` | Required | Identifier selecting the spline record or set. |
| 3 | `splineId2` | `integer` | Required | Identifier selecting the spline record or set. |
| 4 | `option` | `text` | — | Selects how the current entry or group is interpreted. |
| 5 | `aeroBoxListId` | `integer` | Required | Identifier selecting the aero box list record or set. |
| 6 | `depth1` | `real` | Required | Distance over which spline 1 contributes to the blend. |
| 7 | `depth2` | `real` | Required | Distance over which spline 2 contributes to the blend. |

Accepted words: `Constant`, `Cubic`, `Element`, `Linear`, `Table`.

**Example record**

~~~text
AeroSplineCurveBlend;140;130;125;Linear;141;400.;1.E+3
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 140`, `splineId1 = 130`, `splineId2 = 125`, `option = Linear`.

## AeroSplineEquation3

A constraint equation that sets one component of motion of one aerodynamic box from the displacements of structural degrees of freedom, the way a control surface is tied to its actuator.

**Record format and fields**

`AeroSplineEquation3;id;aeroPanelId;boxId;component;node1;components1;coefficient1;usage;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier selecting the aero panel record or set. |
| 3 | `boxId` | `integer` | Required | Identifier selecting the box record or set. |
| 4 | `component` | `integer` | Required | Degree of freedom or response component addressed by this term. |
| 5 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 6 | `components1` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 7 | `coefficient1` | `real` | — | Coefficient 1 in the AeroSplineEquation3 relation. |
| 8 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `nodeComponent` | `integer` | — | Number of the degree of freedom at the associated point. |
| 3 | `coefficient` | `real` | — | Coefficient value in the AeroSplineEquation3 relation for points. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `component` — `component` must be an integer from 1 to 6.

**Example record**

~~~text
AeroSplineEquation3;1121;1101;1116;3;15;3;1.
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_wing_body_splines.oos)

Reading the example gives `id = 1121`, `aeroPanelId = 1101`, `boxId = 1116`, `component = 3`.

## AeroSplineRelaxation

The relaxation of a spline on its neighbour.

**Record format and fields**

`AeroSplineRelaxation;splineId1;splineId2;curvePointListId;referenceDistance;relaxedPointListId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `splineId1` | `integer` | Required | Identifier selecting the spline record or set. |
| 2 | `splineId2` | `integer` | Required | Identifier selecting the spline record or set. |
| 3 | `curvePointListId` | `integer` | Required | Identifier selecting the curve point list record or set. |
| 4 | `referenceDistance` | `real` | Required | Reference distance (length). |
| 5 | `relaxedPointListId` | `integer` | 0 | Identifier selecting the relaxed point list record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroSplineRelaxation;150;140;152;100.
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `splineId1 = 150`, `splineId2 = 140`, `curvePointListId = 152`, `referenceDistance = 100.`.

## AeroSplineStripBlend

A strip based blend of two splines, which the other splines name as their own (the blend has a spline ID of its own and may be blended again).

**Record format and fields**

`AeroSplineStripBlend;id;splineId1;splineId2;option;weight1;nodeId;depth1;depth2;directionX;directionY;directionZ;frameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `splineId1` | `integer` | Required | Identifier selecting the spline record or set. |
| 3 | `splineId2` | `integer` | Required | Identifier selecting the spline record or set. |
| 4 | `option` | `text` | — | Selects how the current entry or group is interpreted. |
| 5 | `weight1` | `real` | — | Relative contribution of this term to the specified combination. Entry 1. |
| 6 | `nodeId` | `integer` | 0 | Identifier of the grid point addressed by this record. |
| 7 | `depth1` | `real` | — | Distance over which spline 1 contributes to the blend. |
| 8 | `depth2` | `real` | — | Distance over which spline 2 contributes to the blend. |
| 9 | `directionX` | `real` | — | X component of the specified direction vector in its reference frame. |
| 10 | `directionY` | `real` | — | Y component of the specified direction vector in its reference frame. |
| 11 | `directionZ` | `real` | — | Z component of the specified direction vector in its reference frame. |
| 12 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |

Accepted words: `Constant`, `Cubic`, `Element`, `Linear`, `Table`, `WeightedAverage`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `weight1` — `weight1` must be greater than 0.0 and at most 1.0.

**Example record**

~~~text
AeroSplineStripBlend;130;110;120;WeightedAverage;0.5
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 130`, `splineId1 = 110`, `splineId2 = 120`, `option = WeightedAverage`.

## AeroStaticParams

The basic parameters of a static aeroelastic analysis (trim, divergence, stability derivatives).

**Record format and fields**

`AeroStaticParams;aeroFrameId;referenceFrameId;referenceChord;referenceSpan;referenceArea;symmetricXz;symmetricXy`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `aeroFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 2 | `referenceFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 3 | `referenceChord` | `real` | Required | Chord length used to nondimensionalize aerodynamic quantities. |
| 4 | `referenceSpan` | `real` | Required | Span used as the aerodynamic reference length. |
| 5 | `referenceArea` | `real` | Required | Reference area (length squared). |
| 6 | `symmetricXz` | `integer` | 0 | Symmetry convention for the aerodynamic model across the xz plane. |
| 7 | `symmetricXy` | `integer` | 0 | Symmetry convention for the aerodynamic model across the xy plane. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroStaticParams;;;200.;2.E+3;4.E+5;1
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `referenceChord = 200.`, `referenceSpan = 2.E+3`, `referenceArea = 4.E+5`, `symmetricXz = 1`.

## AeroStripPanel4

An aerodynamic macro element for strip theory, a panel cut into strips that span the whole chord.

**Record format and fields**

`AeroStripPanel4;id;propId;positionFrameId;spanBoxCount;spanDivisionListId;xCoord1;yCoord1;zCoord1;rootChord;xCoord4;yCoord4;zCoord4;tipChord`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `spanBoxCount` | `integer` | 0 | Number of span box entries. |
| 5 | `spanDivisionListId` | `integer` | 0 | Identifier selecting the span division list record or set. |
| 6 | `xCoord1` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 1. |
| 7 | `yCoord1` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 1. |
| 8 | `zCoord1` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 1. |
| 9 | `rootChord` | `real` | 0.0 | Chord at the inboard end of the aerodynamic panel, in length units. |
| 10 | `xCoord4` | `real` | 0.0 | X coordinate of the location in the specified frame. Entry 4. |
| 11 | `yCoord4` | `real` | 0.0 | Y coordinate of the location in the specified frame. Entry 4. |
| 12 | `zCoord4` | `real` | 0.0 | Z coordinate of the location in the specified frame. Entry 4. |
| 13 | `tipChord` | `real` | 0.0 | Chord at the outboard end of the aerodynamic panel, in length units. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `spanBoxCount` — `spanBoxCount` cannot be negative.
- `spanBoxCount` — `spanBoxCount` or `spanDivisionListId` is required.
- `xCoord1` — `xCoord1`, `yCoord1` and `zCoord1` must be finite numbers.
- `xCoord4` — `xCoord4`, `yCoord4` and `zCoord4` must be finite numbers.
- `rootChord` — `rootChord` and `tipChord` cannot both be zero.

**Example record**

~~~text
AeroStripPanel4;6000;6001;0;3;;0.;0.;0.;200.;0.;1.E+3;0.;200.
~~~

[Model containing this record](../../../validation/models/aero_models/sol146_strip_theory.oos)

Reading the example gives `id = 6000`, `propId = 6001`, `positionFrameId = 0`, `spanBoxCount = 3`.

## AeroStripProp4

The properties of the strips of an [AeroStripPanel4](aero.md#aerostrippanel4) panel (strip theory): the lift curve slope and lag function selections, and the control surface of every strip.

**Record format and fields**

`AeroStripProp4;id;liftSlopeOption;liftSlopeListId;circulationOption;circulationListId;<strips>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the aero property namespace. |
| 2 | `liftSlopeOption` | `integer` | 0 | Selects the lift slope option for AeroStripProp4. |
| 3 | `liftSlopeListId` | `integer` | 0 | Identifier selecting the lift slope list record or set. |
| 4 | `circulationOption` | `integer` | 0 | Selects the circulation option for AeroStripProp4. |
| 5 | `circulationListId` | `integer` | 0 | Identifier selecting the circulation list record or set. |

**Repeated group `strips`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `hingeOffsetRatio` | `real` | — | Relative measure of hinge offset. |
| 2 | `controlChordRatio` | `real` | — | Relative measure of control chord. |
| 3 | `gapRatio` | `real` | — | Relative measure of gap. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `liftSlopeOption` — `liftSlopeOption` must be -1, 0 or 1.
- `liftSlopeListId` — `liftSlopeListId` is required when `liftSlopeOption` is not 0.
- `circulationOption` — `circulationOption` must be 0, 1, 2 or 3.
- `circulationOption` — `circulationOption` must be 0 when `liftSlopeOption` is not 0.
- `circulationListId` — `circulationListId` is required when `circulationOption` is not 0.
- `hingeOffsetRatio1` — at least one strip (`hingeOffsetRatio1`, `controlChordRatio1`, `gapRatio1`) is required.

**Example record**

~~~text
AeroStripProp4;6001;0;0;0;0;0.;0.;0.;0.;0.;0.;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/aero_models/sol146_strip_theory.oos)

Reading the example gives `id = 6001`, `liftSlopeOption = 0`, `liftSlopeListId = 0`, `circulationOption = 0`.

## AeroSurfaceSpline1

A surface spline that carries the displacements of a set of structural grid points to a regular array of aerodynamic boxes, and the aerodynamic forces back to the grid points.

**Record format and fields**

`AeroSurfaceSpline1;id;aeroPanelId;firstBox;lastBox;nodeSetId;linearFlexibility;method;usage;elemCountX;elemCountY`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier addressing aero element data. |
| 3 | `firstBox` | `integer` | Required | Identifier addressing aero box data. |
| 4 | `lastBox` | `integer` | Required | Identifier addressing aero box data. |
| 5 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 6 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 7 | `method` | `text` | — | Selects the method for AeroSurfaceSpline1. |
| 8 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 9 | `elemCountX` | `integer` | — | Number of element subdivisions along X. |
| 10 | `elemCountY` | `integer` | — | Number of element subdivisions along Y. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `FiniteSurfaceSpline`, `Force`, `InfinitePlateSpline`, `Symmetric`, `Table`, `ThinPlateSpline`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `lastBox` — `lastBox` cannot be below `firstBox`.
- `elemCountX` — `elemCountX` must be a positive integer.
- `elemCountY` — `elemCountY` must be a positive integer.

**Example record**

~~~text
AeroSurfaceSpline1;1101;1001;1001;1032;1100
~~~

[Model containing this record](../../../validation/models/aero_sol144/aero_model.oos)

Reading the example gives `id = 1101`, `aeroPanelId = 1001`, `firstBox = 1001`, `lastBox = 1032`.

## AeroSurfaceSpline4

A surface spline like [AeroSurfaceSpline1](aero.md#aerosurfacespline1), for any aerodynamic geometry: the points it moves are listed in an [AeroBoxList](aero.md#aeroboxlist) instead of being a run of box numbers.

**Record format and fields**

`AeroSurfaceSpline4;id;aeroPanelId;aeroBoxListId;nodeSetId;linearFlexibility;method;usage;elemCountX;elemCountY;functionKind;coreRadius`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `aeroPanelId` | `integer` | Required | Identifier addressing aero panel or component data. |
| 3 | `aeroBoxListId` | `integer` | Required | Identifier addressing aero list data. |
| 4 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 5 | `linearFlexibility` | `real` | 0.0 | Translational flexibility of the spline coupling; controls how closely displacement follows the supporting structure. |
| 6 | `method` | `text` | — | Selects the method for AeroSurfaceSpline4. |
| 7 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 8 | `elemCountX` | `integer` | — | Number of element subdivisions along X. |
| 9 | `elemCountY` | `integer` | — | Number of element subdivisions along Y. |
| 10 | `functionKind` | `text` | — | Selects the function kind for AeroSurfaceSpline4. |
| 11 | `coreRadius` | `real` | — | Core radius (length). |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `FiniteSurfaceSpline`, `Force`, `InfinitePlateSpline`, `RigidSurfaceSpline`, `Symmetric`, `Table`, `ThinPlateSpline`, `WendlandFunction0`, `WendlandFunction2`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `elemCountX` — `elemCountX` must be a positive integer.
- `elemCountY` — `elemCountY` must be a positive integer.

**Example record**

~~~text
AeroSurfaceSpline4;2100;2000;2101;2102;0.;InfinitePlateSpline
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `id = 2100`, `aeroPanelId = 2000`, `aeroBoxListId = 2101`, `nodeSetId = 2102`.

## AeroTria3

A triangular element of an aerodynamic mesh, given by three aerodynamic grid points ([AeroNode](aero.md#aeronode)).

**Record format and fields**

`AeroTria3;id;componentId;node1;node2;node3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `componentId` | `integer` | Required | Identifier selecting the component record or set. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | Required | Grid point to which this entry applies. Entry 3. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroTria3;6101;2;5101;5102;5104
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 6101`, `componentId = 2`, `node1 = 5101`, `node2 = 5102`.

## AeroTrim

The flight condition of a static aeroelastic trim and the trim variables that are fixed in it.

**Record format and fields**

`AeroTrim;id;machNumber;dynamicPressure;label1;trimValue1;label2;trimValue2;equivalentAspectRatio;<variables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `machNumber` | `real` | Required | Ratio of flow speed to the local speed of sound. |
| 3 | `dynamicPressure` | `real` | Required | Dynamic pressure (force per area). |
| 4 | `label1` | `text` | — | Text identifying the entry to the user or to records which select it by label. Entry 1. |
| 5 | `trimValue1` | `real` | — | Prescribed value of the associated trim variable, in that variable’s units. Entry 1. |
| 6 | `label2` | `text` | — | Text identifying the entry to the user or to records which select it by label. Entry 2. |
| 7 | `trimValue2` | `real` | — | Prescribed value of the associated trim variable, in that variable’s units. Entry 2. |
| 8 | `equivalentAspectRatio` | `real` | 1.0 | Relative measure of equivalent aspect. |

**Repeated group `variables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 2 | `trimValue` | `real` | — | Prescribed value of the associated trim variable, in that variable’s units. |

Accepted words: `AngleOfAttack`, `Constant`, `Element`, `PitchRate`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `SideSlip`, `Table`, `YawRate`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `machNumber` — `machNumber` cannot be 1.0.

**Example record**

~~~text
AeroTrim;1;0.5;0.02;AngleOfAttack;0.05;ELEV;0.
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

Reading the example gives `id = 1`, `machNumber = 0.5`, `dynamicPressure = 0.02`, `label1 = AngleOfAttack`.

## AeroTrim2

Defines a flight condition and the values of its trim variables for static aeroelastic analysis.

**Record format and fields**

`AeroTrim2;id;machNumber;dynamicPressure;equivalentAspectRatio;<variables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `machNumber` | `real` | Required | Ratio of flow speed to the local speed of sound. |
| 3 | `dynamicPressure` | `real` | Required | Dynamic pressure (force per area). |
| 4 | `equivalentAspectRatio` | `real` | 1.0 | Relative measure of equivalent aspect. |

**Repeated group `variables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 2 | `trimValue` | `any` | — | Prescribed value of the associated trim variable, in that variable’s units. |

Accepted words: `AngleOfAttack`, `Constant`, `Element`, `Free`, `Linked`, `PitchRate`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `Scheduled`, `SideSlip`, `Table`, `YawRate`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `label` — a value is given without its `label`.
- `machNumber` — `machNumber` cannot be 1.0.

**Example record**

~~~text
AeroTrim2;1;0.5;2.E-4;;ALPHAU;0.02;FLAPU;0.05
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_external_mesh_blending.oos)

Reading the example gives `id = 1`, `machNumber = 0.5`, `dynamicPressure = 2.E-4`.

## AeroTrimLink

A linear relation that fixes one trim variable (the dependent one) as a combination of others, so that the trim does not solve for it.

**Record format and fields**

`AeroTrimLink;id;dependentLabel;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `any` | Required | Set identifier shared by entries in the same group. |
| 2 | `dependentLabel` | `text` | — | Text naming the dependent. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentLabel` | `text` | — | Text naming the independent. |
| 2 | `coefficient` | `real` | — | Coefficient value in the AeroTrimLink relation for terms. |

Accepted words: `Always`, `AngleOfAttack`, `Constant`, `Element`, `PitchRate`, `RigidAccelX`, `RigidAccelY`, `RigidAccelZ`, `RigidAngularAccelX`, `RigidAngularAccelY`, `RigidAngularAccelZ`, `RollRate`, `SideSlip`, `Table`, `YawRate`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `independentLabels` — the card needs at least one independent variable (`independentLabels`).

**Example record**

~~~text
AeroTrimLink;1;AIL;AngleOfAttack;-0.5
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `id = 1`, `dependentLabel = AIL`.

## AeroUnsteadyParams

The basic aerodynamic parameters of the unsteady analyses (flutter, frequency and transient response to a gust).

**Record format and fields**

`AeroUnsteadyParams;aeroFrameId;velocity;referenceChord;referenceDensity;symmetricXz;symmetricXy`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `aeroFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 2 | `velocity` | `real` | — | Rate of displacement in the specified direction (length per time). |
| 3 | `referenceChord` | `real` | Required | Chord length used to nondimensionalize aerodynamic quantities. |
| 4 | `referenceDensity` | `real` | Required | Flow density used as the aerodynamic reference. |
| 5 | `symmetricXz` | `integer` | 0 | Symmetry convention for the aerodynamic model across the xz plane. |
| 6 | `symmetricXy` | `integer` | 0 | Symmetry convention for the aerodynamic model across the xy plane. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AeroUnsteadyParams;;4.5E+5;200.;1.2E-12;1
~~~

[Model containing this record](../../../validation/models/aero_models/sol145_mach_box.oos)

Reading the example gives `velocity = 4.5E+5`, `referenceChord = 200.`, `referenceDensity = 1.2E-12`, `symmetricXz = 1`.

## AeroUserSpline

A spline that a program supplied by the user evaluates, instead of one of the methods of the format.

**Record format and fields**

`AeroUserSpline;id;groupName;dependentNodeComponent;independentNodeComponent;dependentElemComponent;independentElemComponent;usage;aeroBoxListId;factorListId;labelListId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `dependentNodeComponent` | `text` | — | Nodal component driven by the spline interpolation. |
| 4 | `independentNodeComponent` | `text` | — | Nodal component used as an input to the spline interpolation. |
| 5 | `dependentElemComponent` | `text` | — | Element component driven by the spline interpolation. |
| 6 | `independentElemComponent` | `text` | — | Element component used as an input to the spline interpolation. |
| 7 | `usage` | `text` | — | Selects transfer of displacement, force or both across the aerodynamic spline. |
| 8 | `aeroBoxListId` | `integer` | 0 | Identifier selecting the aero box list record or set. |
| 9 | `factorListId` | `integer` | 0 | Identifier selecting the factor list record or set. |
| 10 | `labelListId` | `integer` | 0 | Identifier selecting the label list record or set. |

Accepted words: `Antisymmetric`, `Asymmetric`, `Both`, `Constant`, `Displacement`, `Element`, `Force`, `Symmetric`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `groupName` — `groupName` is required.
- `dependentNodeComponent` — `dependentNodeComponent` and `dependentElemComponent` cannot both be blank.
- `independentNodeComponent` — `independentNodeComponent` and `independentElemComponent` cannot both be blank.

**Example record**

~~~text
AeroUserSpline;1101;SPLNSRV1;WINGA;WINGS;;;Both;1201;1202;1203
~~~

[Model containing this record](../../../validation/models/read_only_aero/sol144_external_spline.oos)

Reading the example gives `id = 1101`, `groupName = SPLNSRV1`, `dependentNodeComponent = WINGA`, `independentNodeComponent = WINGS`.

## TrimmedMaterialMatrices

The trimmed material matrices that an acoustic program exports for a frequency response analysis, with the complex factor that scales them.

**Record format and fields**

`TrimmedMaterialMatrices;name;mappedDataUnit;propertyMatrixUnit;scaleReal;scaleImaginary`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `name` | `text` | — | Upper case, up to 8 characters. |
| 2 | `mappedDataUnit` | `integer` | Required | Logical file unit carrying the mapped aerodynamic data. |
| 3 | `propertyMatrixUnit` | `integer` | Required | Logical file unit containing the matrix of aerodynamic properties. |
| 4 | `scaleReal` | `real` | — | Real part of the complex factor multiplying the supplied data. |
| 5 | `scaleImaginary` | `real` | — | Imaginary part of the complex factor multiplying the supplied data. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `name` — `name` is required.
- `name` — `name` must be a nonempty matrix name without control characters.
- `propertyMatrixUnit` — `mappedDataUnit` and `propertyMatrixUnit` must be different unit numbers.

**Example record**

~~~text
TrimmedMaterialMatrices;FLOOR;31;32;1.;0.1
~~~

[Model containing this record](../../../validation/models/read_only_aero/sol108_trim_matrices.oos)

Reading the example gives `name = FLOOR`, `mappedDataUnit = 31`, `propertyMatrixUnit = 32`, `scaleReal = 1.`.
