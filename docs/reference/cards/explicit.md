# Explicit analysis

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## BeltProp

The property of a belt element, a [Rod2](elements.md#rod2) that names the card in its property ID field.

**Record format and fields**

`BeltProp;id;loadingTableId;unloadingTableId;density;damping1;damping2;slackTableId;prestrainTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `loadingTableId` | `integer` | Required | Table supplying the variation of loading. |
| 3 | `unloadingTableId` | `integer` | Required | Table supplying the variation of unloading. |
| 4 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `damping1` | `real` | 0.1 | Dissipative coefficient of the selected connection, material or response law. Entry 1. |
| 6 | `damping2` | `real` | 0.1 | Dissipative coefficient of the selected connection, material or response law. Entry 2. |
| 7 | `slackTableId` | `integer` | 0 | Table supplying the variation of slack. |
| 8 | `prestrainTableId` | `integer` | 0 | Table supplying the variation of prestrain. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
BeltProp;4107;4207;4208;1.E-9;0.1;0.1
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4107`, `loadingTableId = 4207`, `unloadingTableId = 4208`, `density = 1.E-9`.

## CohesiveFriction

A cohesive friction, which lets friction and sticking act at the coupling surface while the Euler material pulls on it (tension).

**Record format and fields**

`CohesiveFriction;id;maxStress;friction;referenceVelocity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `maxStress` | `real` | 0.0 | Maximum stress (force per area). |
| 3 | `friction` | `real` | 0.0 | Controls tangential resistance to relative motion at the interface. |
| 4 | `referenceVelocity` | `real` | 0.0 | Reference velocity (length per time). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CohesiveFriction;1;0.05;0.01;1.E+3
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `maxStress = 0.05`, `friction = 0.01`, `referenceVelocity = 1.E+3`.

## ColdGasInflator

A cold gas inflator, a tank of compressed gas that empties into a gas bag ([GasBag](explicit.md#gasbag)) or an Euler coupling surface ([EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling)) through the [InflatorInlet](loads.md#inflatorinlet) that names the card.

**Record format and fields**

`ColdGasInflator;id;tankVolume;initialPressure;initialTemperature;initialMass;gasName;specificHeatRatio;specificHeatVolume;gasConstant;specificHeatPressure`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `tankVolume` | `real` | Required | Tank volume (length cubed). |
| 3 | `initialPressure` | `real` | — | Pressure assigned to the initial state. |
| 4 | `initialTemperature` | `real` | Required | Initial temperature (temperature). |
| 5 | `initialMass` | `real` | — | The initial mass of gas, greater than zero. |
| 6 | `gasName` | `integer` | — | Text naming the gas. Alternative to `specificHeatRatio`. |
| 7 | `specificHeatRatio` | `real` | — | Relative measure of specific heat. Alternative to `gasName`. |
| 8 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 9 | `gasConstant` | `real` | — | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 10 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |

Accepted words: `Constant`, `Element`, `InflatorGas`, `Table`.

**Example record**

~~~text
ColdGasInflator;3;1.E+4;10.;293.;;;1.4;;2.87E+8
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 3`, `tankVolume = 1.E+4`, `initialPressure = 10.`, `initialTemperature = 293.`.

## ConstantSpallation

The constant spallation model, in which the minimum pressure is constant.

**Record format and fields**

`ConstantSpallation;id;minPressure;volumeCutoffTolerance;maxVoidFraction`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `minPressure` | `real` | 0.0 | Minimum pressure (force per area). |
| 3 | `volumeCutoffTolerance` | `real` | 1.0E-4 | Permitted numerical deviation for volume cutoff. |
| 4 | `maxVoidFraction` | `real` | 0.0 | Largest void fraction under tension, not negative. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ConstantSpallation;1;-0.1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 1`, `minPressure = -0.1`.

## CouplingCohesiveFriction

A cohesive friction model on one part of the coupling surface of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling).

**Record format and fields**

`CouplingCohesiveFriction;id;setId;subsurfaceId;cohesiveFrictionModelId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 3 | `subsurfaceId` | `integer` | 0 | Identifier selecting the subsurface record or set. |
| 4 | `cohesiveFrictionModelId` | `integer` | Required | Identifier selecting the cohesive friction model record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CouplingCohesiveFriction;1;1;205;1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `setId = 1`, `subsurfaceId = 205`, `cohesiveFrictionModelId = 1`.

## CouplingFailedSegmentFlow

The state of the surroundings that flows through a segment of a coupling surface after the segment fails (the structure that carries it breaks).

**Record format and fields**

`CouplingFailedSegmentFlow;id;density;specificEnergy;xVelocity;yVelocity;zVelocity;pressure;matId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 3 | `specificEnergy` | `real` | — | Energy per unit mass. |
| 4 | `xVelocity` | `real` | — | X velocity (length per time). |
| 5 | `yVelocity` | `real` | — | Y velocity (length per time). |
| 6 | `zVelocity` | `real` | — | Z velocity (length per time). |
| 7 | `pressure` | `real` | — | Normal force per unit area, in the model’s pressure units. |
| 8 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CouplingFailedSegmentFlow;1;1.2E-12;2.083E+11;0.;0.;0.;;11
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_compartment_failure.oos)

Reading the example gives `id = 1`, `density = 1.2E-12`, `specificEnergy = 2.083E+11`, `xVelocity = 0.`.

## CouplingHoleToCoupling

A hole in a coupling surface through which gas flows to another coupling surface.

**Record format and fields**

`CouplingHoleToCoupling;id;holeSize;flowDirection;couplingId;matId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `holeSize` | `text` | Small | Dimension of the opening used to determine its effective flow area. |
| 3 | `flowDirection` | `text` | Both | Direction used for the flow through the boundary or region. |
| 4 | `couplingId` | `integer` | Required | Identifier selecting the coupling record or set. |
| 5 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
CouplingHoleToCoupling;3;Small;Both;2
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 3`, `holeSize = Small`, `flowDirection = Both`, `couplingId = 2`.

## CouplingHoleToGasBag

A hole in an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or [GasBag](explicit.md#gasbag) (sub)surface that is connected to another [GasBag](explicit.md#gasbag), to model the flow between two air bags (two GasBags, a [GasBag](explicit.md#gasbag) and an Eulerian air bag, or two Eulerian air bags).

**Record format and fields**

`CouplingHoleToGasBag;id;holeSize;flowDirection;gasBagId;matId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `holeSize` | `text` | Small | Dimension of the opening used to determine its effective flow area. |
| 3 | `flowDirection` | `text` | Both | Direction used for the flow through the boundary or region. |
| 4 | `gasBagId` | `integer` | Required | Identifier selecting the gas bag record or set. |
| 5 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
CouplingHoleToGasBag;4;Small;Both;3
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 4`, `holeSize = Small`, `flowDirection = Both`, `gasBagId = 3`.

## CouplingInteraction

An interaction between two coupling surfaces that becomes active when the structure that carries them fails.

**Record format and fields**

`CouplingInteraction;id;couplingId1;couplingId2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `couplingId1` | `integer` | Required | Identifier selecting the coupling record or set. |
| 3 | `couplingId2` | `integer` | 0 | Identifier selecting the coupling record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CouplingInteraction;1;1;2
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_compartment_failure.oos)

Reading the example gives `id = 1`, `couplingId1 = 1`, `couplingId2 = 2`.

## CouplingOptions

Special options of one part of the coupling surface of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling): the factor that scales the Eulerian pressure acting on it and a pressure load from the covered side.

**Record format and fields**

`CouplingOptions;id;setId;subsurfaceId;factorSource;factor;coverPressureSource;coverPressure`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 3 | `subsurfaceId` | `integer` | 0 | Identifier selecting the subsurface record or set. |
| 4 | `factorSource` | `text` | Constant | Selects how the multiplier is supplied. |
| 5 | `factor` | `real` | 1.0 | Multiplier on the associated contribution. |
| 6 | `coverPressureSource` | `text` | Constant | Selects how the pressure acting on the cover is supplied. |
| 7 | `coverPressure` | `any` | 0.0 | Pressure acting on the cover in the specified initial or loading condition. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
CouplingOptions;1;1;0;Constant;1.;Constant;0.1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `setId = 1`, `subsurfaceId = 0`, `factorSource = Constant`.

## CylinderShape

Defines a cylindrical region used to select Eulerian elements for initial conditions or body forces.

**Record format and fields**

`CylinderShape;id;centerX1;centerY1;centerZ1;centerX2;centerY2;centerZ2;radius`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `centerX1` | `real` | Required | X coordinate of the centre at position 1. |
| 3 | `centerY1` | `real` | Required | Y coordinate of the centre at position 1. |
| 4 | `centerZ1` | `real` | Required | Z coordinate of the centre at position 1. |
| 5 | `centerX2` | `real` | Required | X coordinate of the centre at position 2. |
| 6 | `centerY2` | `real` | Required | Y coordinate of the centre at position 2. |
| 7 | `centerZ2` | `real` | Required | Z coordinate of the centre at position 2. |
| 8 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `centerX2` — the two end points of the axis must be different.

**Example record**

~~~text
CylinderShape;41;-1.;10.;10.;20.;10.;10.;15.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 41`, `centerX1 = -1.`, `centerY1 = 10.`, `centerZ1 = 10.`.

## DeflagrationStateEquation

Stores a material equation-of-state definition for a reacting gas.

**Record format and fields**

`DeflagrationStateEquation;id;gammaCoefficient;coVolume;gasConstant;specificHeatVolume;specificHeatPressure;chemicalEnergy;referenceDensity;powderDensityRatio;burnRateCoefficient;burnRateExponent;surfaceToVolumeRatio;formParameterX;formParameterY`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `gammaCoefficient` | `real` | Required | Coefficient in the relation for gamma. |
| 3 | `coVolume` | `real` | Required | Co volume (length cubed). |
| 4 | `gasConstant` | `real` | — | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 5 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 6 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |
| 7 | `chemicalEnergy` | `real` | Required | Chemical energy per unit burned mass, greater than zero. |
| 8 | `referenceDensity` | `real` | Required | Flow density used as the aerodynamic reference. |
| 9 | `powderDensityRatio` | `real` | — | Relative measure of powder density. |
| 10 | `burnRateCoefficient` | `real` | Required | Coefficient in the relation for burn rate. |
| 11 | `burnRateExponent` | `real` | Required | Power in the law for burn rate. |
| 12 | `surfaceToVolumeRatio` | `real` | Required | Relative measure of surface to volume. |
| 13 | `formParameterX` | `real` | Required | Parameter of the form function, greater than zero. |
| 14 | `formParameterY` | `real` | Required | Parameter of the form function, not negative. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DeflagrationStateEquation;1;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.
~~~

Reading the example gives `id = 1`, `gammaCoefficient = 1.`, `coVolume = 1.`, `gasConstant = 1.`.

## ElasticShearModel

An elastic shear model with a constant shear modulus.

**Record format and fields**

`ElasticShearModel;id;shearModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `shearModulus` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ElasticShearModel;4;50.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 4`, `shearModulus = 50.`.

## EulerBarrier

Faces of an Euler mesh that material cannot cross.

**Record format and fields**

`EulerBarrier;id;contactBodyId;meshId;meshFace;skinFriction;minX;maxX;minY;maxY;minZ;maxZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `contactBodyId` | `integer` | 0 | Identifier selecting the contact body record or set. |
| 3 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 4 | `meshFace` | `text` | — | Face of the mesh on which the boundary condition or operation acts. |
| 5 | `skinFriction` | `real` | — | Tangential resistance at the bounding surface in the flow model. |
| 6 | `minX` | `real` | — | X coordinate of the lower spatial bound. |
| 7 | `maxX` | `real` | — | X coordinate of the upper spatial bound. |
| 8 | `minY` | `real` | — | Y coordinate of the lower spatial bound. |
| 9 | `maxY` | `real` | — | Y coordinate of the upper spatial bound. |
| 10 | `minZ` | `real` | — | Z coordinate of the lower spatial bound. |
| 11 | `maxZ` | `real` | — | Z coordinate of the upper spatial bound. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
EulerBarrier;1;;1;NegativeXDirection
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 1`, `meshId = 1`, `meshFace = NegativeXDirection`.

## EulerBodyForce

A body force (an acceleration per unit mass) on the Eulerian elements, in the direction of a vector, scaled by a number, by a table of time, or by both.

**Record format and fields**

`EulerBodyForce;id;frameId;scaleFactor;tableId;directionX;directionY;directionZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `scaleFactor` | `real` | 0.0 | Multiplier applied to the quantity specified by the entry. |
| 4 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 5 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 6 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 7 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
EulerBodyForce;1;;9810.;;0.;0.;-1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `scaleFactor = 9810.`, `directionX = 0.`, `directionY = 0.`.

## EulerBodyForceSet

The body force of the Eulerian regions of a set.

**Record format and fields**

`EulerBodyForceSet;id;regionSetId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `regionSetId` | `integer` | Required | Identifier selecting the region set record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
EulerBodyForceSet;30;31
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 30`, `regionSetId = 31`.

## EulerCyclicFlowBoundary

A cyclic (periodic) flow boundary of an Euler mesh.

**Record format and fields**

`EulerCyclicFlowBoundary;id;contactBodyId;flowType;meshId;meshFace;pairedBoundaryId;minX;maxX;minY;maxY;minZ;maxZ;method;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `contactBodyId` | `integer` | 0 | Identifier selecting the contact body record or set. |
| 3 | `flowType` | `text` | — | Selects the flow type for EulerCyclicFlowBoundary. |
| 4 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 5 | `meshFace` | `text` | — | Face of the mesh on which the boundary condition or operation acts. |
| 6 | `pairedBoundaryId` | `integer` | Required | Identifier selecting the paired boundary record or set. |
| 7 | `minX` | `real` | — | X coordinate of the lower spatial bound. |
| 8 | `maxX` | `real` | — | X coordinate of the upper spatial bound. |
| 9 | `minY` | `real` | — | Y coordinate of the lower spatial bound. |
| 10 | `maxY` | `real` | — | Y coordinate of the upper spatial bound. |
| 11 | `minZ` | `real` | — | Z coordinate of the lower spatial bound. |
| 12 | `maxZ` | `real` | — | Z coordinate of the upper spatial bound. |
| 13 | `method` | `integer` | — | Selects the method for EulerCyclicFlowBoundary. |
| 14 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |

Accepted words: `Both`, `Constant`, `Density`, `Element`, `Flow`, `Hydrostatic`, `In`, `Inside`, `Large`, `Material`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Pressure`, `Small`, `SpecificInternalEnergy`, `Symmetry`, `Table`, `VelocityX`, `VelocityY`, `VelocityZ`.

**Example record**

~~~text
EulerCyclicFlowBoundary;3;;Both;;NegativeYDirection;4;;;;;;;2
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 3`, `flowType = Both`, `meshFace = NegativeYDirection`, `pairedBoundaryId = 4`.

## EulerDefaultFlowBoundary

The default flow boundary of an Euler mesh, which the free faces that no [EulerFlowBoundary](explicit.md#eulerflowboundary), [EulerTimeFlowBoundary](explicit.md#eulertimeflowboundary) or other boundary names take.

**Record format and fields**

`EulerDefaultFlowBoundary;id;solverType;<properties>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `solverType` | `text` | — | Selects the solver type for EulerDefaultFlowBoundary. |

**Repeated group `properties`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyKind` | `text` | — | Selects the property kind for properties. |
| 2 | `propertyValue` | `any` | — | Value of the property identified by this flow-boundary entry. |

Accepted words: `Both`, `Constant`, `Density`, `Element`, `FirstOrder`, `Flow`, `Hydrodynamic`, `Hydrostatic`, `In`, `Material`, `MultiMaterialHydrodynamic`, `MultiMaterialStrength`, `Out`, `Pressure`, `SecondOrder`, `SpecificInternalEnergy`, `Strength`, `Symmetry`, `Table`, `VelocityX`, `VelocityY`, `VelocityZ`.

**Example record**

~~~text
EulerDefaultFlowBoundary;5;MultiMaterialHydrodynamic;Flow;Out
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 5`, `solverType = MultiMaterialHydrodynamic`.

## EulerFlowBoundary

A flow boundary of an Euler mesh with the properties of the material at the boundary.

**Record format and fields**

`EulerFlowBoundary;setId;contactBodyId;meshId;meshFace;minX;maxX;minY;maxY;minZ;maxZ;propertyKind1;propertyValue1;propertyKind2;propertyValue2;propertyKind3;propertyValue3;propertyKind4;propertyValue4;propertyKind5;propertyValue5`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `contactBodyId` | `integer` | 0 | Identifier selecting the contact body record or set. |
| 3 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 4 | `meshFace` | `text` | — | Face of the mesh on which the boundary condition or operation acts. |
| 5 | `minX` | `real` | — | X coordinate of the lower spatial bound. |
| 6 | `maxX` | `real` | — | X coordinate of the upper spatial bound. |
| 7 | `minY` | `real` | — | Y coordinate of the lower spatial bound. |
| 8 | `maxY` | `real` | — | Y coordinate of the upper spatial bound. |
| 9 | `minZ` | `real` | — | Z coordinate of the lower spatial bound. |
| 10 | `maxZ` | `real` | — | Z coordinate of the upper spatial bound. |
| 11 | `propertyKind1` | `text` | — | Selects the property kind 1 for EulerFlowBoundary. |
| 12 | `propertyValue1` | `any` | — | Value of the property identified by this flow-boundary entry. Entry 1. |
| 13 | `propertyKind2` | `text` | — | Selects the property kind 2 for EulerFlowBoundary. |
| 14 | `propertyValue2` | `any` | — | Value of the property identified by this flow-boundary entry. Entry 2. |
| 15 | `propertyKind3` | `text` | — | Selects the property kind 3 for EulerFlowBoundary. |
| 16 | `propertyValue3` | `any` | — | Value of the property identified by this flow-boundary entry. Entry 3. |
| 17 | `propertyKind4` | `text` | — | Selects the property kind 4 for EulerFlowBoundary. |
| 18 | `propertyValue4` | `any` | — | Value of the property identified by this flow-boundary entry. Entry 4. |
| 19 | `propertyKind5` | `text` | — | Selects the property kind 5 for EulerFlowBoundary. |
| 20 | `propertyValue5` | `any` | — | Value of the property identified by this flow-boundary entry. Entry 5. |

Accepted words: `Both`, `Constant`, `Density`, `Element`, `Flow`, `Hydrostatic`, `In`, `Inside`, `Large`, `Material`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Pressure`, `Small`, `SpecificInternalEnergy`, `Symmetry`, `Table`, `VelocityX`, `VelocityY`, `VelocityZ`.

**Example record**

~~~text
EulerFlowBoundary;1;;;NegativeXDirection;;;;;;;Material;12;VelocityX;1.E+3;Density;1.E-9;SpecificInternalEnergy;0.;Flow;In
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `setId = 1`, `meshFace = NegativeXDirection`, `propertyKind1 = Material`, `propertyValue1 = 12`.

## EulerForceRegion

One Eulerian region (a shape and a material) with the time dependent acceleration that acts in it.

**Record format and fields**

`EulerForceRegion;id;setId;shapeType;shapeId;matId;accelX;accelY;accelZ;level`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 3 | `shapeType` | `text` | — | Selects the shape type for EulerForceRegion. |
| 4 | `shapeId` | `integer` | Required | Identifier selecting the shape record or set. |
| 5 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 6 | `accelX` | `integer` | Required | Component X of the acceleration vector (length per time squared). |
| 7 | `accelY` | `integer` | Required | Component Y of the acceleration vector (length per time squared). |
| 8 | `accelZ` | `integer` | Required | Component Z of the acceleration vector (length per time squared). |
| 9 | `level` | `real` | 0.0 | The level indicator of the region. |

Accepted words: `Box`, `Constant`, `Cylinder`, `Element`, `Elements`, `Sphere`, `Surface`, `Table`.

**Example record**

~~~text
EulerForceRegion;1;31;Cylinder;33;12;61;62;62
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 1`, `setId = 31`, `shapeType = Cylinder`, `shapeId = 33`.

## EulerHydrostaticPreset

Supplies the initial hydrostatic density distribution for an Eulerian fluid in a coupling region.

**Record format and fields**

`EulerHydrostaticPreset;id;matId;nodeId;frameId;surfacePointX;surfacePointY;surfacePointZ;surfacePressure`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `nodeId` | `integer` | 0 | Identifier of the grid point addressed by this record. |
| 4 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 5 | `surfacePointX` | `real` | — | X coordinate of the point on the surface. |
| 6 | `surfacePointY` | `real` | — | Y coordinate of the point on the surface. |
| 7 | `surfacePointZ` | `real` | — | Z coordinate of the point on the surface. |
| 8 | `surfacePressure` | `real` | Required | Surface pressure (force per area). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
EulerHydrostaticPreset;1;12;;;100.;50.;100.;0.1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 1`, `matId = 12`, `surfacePointX = 100.`, `surfacePointY = 50.`.

## EulerInitialRegions

The initial conditions of the Eulerian regions.

**Record format and fields**

`EulerInitialRegions;id;regionGroupId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `regionGroupId` | `integer` | Required | Identifier selecting the region group record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
EulerInitialRegions;20;21
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 20`, `regionGroupId = 21`.

## EulerLagrangeCoupling

A general coupling surface, the interface between an Eulerian domain (finite volume) and a Lagrangian one (finite elements).

**Record format and fields**

`EulerLagrangeCoupling;id;surfaceId;cover;reverseNormals;checkNormals;porosityId;optionId;couplingType;inflatorId;heatTransferId;staticFriction;kineticFriction;frictionDecay;initialGasId;elemSetId;meshId;deactivationTime;failedSegmentFlowId;hydrostaticId;skinFriction;cohesiveFrictionSetId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `surfaceId` | `integer` | Required | Identifier selecting the surface record or set. |
| 3 | `cover` | `text` | — | Definition of the cover associated with the surface or segment. |
| 4 | `reverseNormals` | `text` | — | Reverses the orientation of the selected normals. |
| 5 | `checkNormals` | `text` | — | Requests a consistency check on the orientation of surface normals. |
| 6 | `porosityId` | `integer` | 0 | Identifier selecting the porosity record or set. |
| 7 | `optionId` | `integer` | 0 | Identifier selecting the option record or set. |
| 8 | `couplingType` | `text` | — | Selects the coupling type for EulerLagrangeCoupling. |
| 9 | `inflatorId` | `integer` | 0 | Identifier selecting the inflator record or set. |
| 10 | `heatTransferId` | `integer` | 0 | Identifier selecting the heat transfer record or set. |
| 11 | `staticFriction` | `real` | 0.0 | Static friction coefficient. |
| 12 | `kineticFriction` | `real` | 0.0 | Kinetic friction coefficient. |
| 13 | `frictionDecay` | `real` | 0.0 | Exponential decay coefficient. |
| 14 | `initialGasId` | `integer` | 0 | Identifier selecting the initial gas record or set. |
| 15 | `elemSetId` | `integer` | 0 | Identifier selecting the element set record or set. |
| 16 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 17 | `deactivationTime` | `real` | — | Deactivation time (time). |
| 18 | `failedSegmentFlowId` | `integer` | 0 | Identifier selecting the failed segment flow record or set. |
| 19 | `hydrostaticId` | `integer` | 0 | Identifier selecting the hydrostatic record or set. |
| 20 | `skinFriction` | `real` | 0.0 | Tangential resistance at the bounding surface in the flow model. |
| 21 | `cohesiveFrictionSetId` | `integer` | 0 | Identifier selecting the cohesive friction set record or set. |

Accepted words: `AirbagCoupling`, `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Standard`, `Table`.

**Example record**

~~~text
EulerLagrangeCoupling;1;101;Inside;On;On;1
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 1`, `surfaceId = 101`, `cover = Inside`, `reverseNormals = On`.

## EulerMeshBias

Specifies how cell size varies along one direction of a generated Eulerian mesh.

**Record format and fields**

`EulerMeshBias;id;<intervals>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `intervals`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `intervalStart` | `real` | — | Coordinate marking the start of the interval. |
| 2 | `intervalGrowth` | `real` | — | Growth of the cell size across the interval. |
| 3 | `intervalElemCount` | `integer` | — | Number of interval element entries. |
| 4 | `intervalStartSize` | `real` | — | Cell size prescribed at the beginning of the interval. |
| 5 | `intervalEndSize` | `real` | — | Cell size at the end of the mesh-bias interval. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `intervalStart` — the card needs at least one interval.

**Example record**

~~~text
EulerMeshBias;1;-60.;0.5;3;;;-20.;;4;;;20.;2.;3
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`.

## EulerMeshGenerator

The generator of an Eulerian mesh, either a box of elements or a mesh that adapts around a coupling surface.

**Record format and fields**

`EulerMeshGenerator;id;meshType;elemSizeX;elemSizeY;elemSizeZ;xReference;yReference;zReference;originX;originY;originZ;widthX;widthY;widthZ;elemCountX;elemCountY;elemCountZ;subMeshId;firstNodeId;firstElemId;propKind;propId;resize;resizeTableIdX;resizeTableIdY;resizeTableIdZ;remeshMethod;biasStart;growthX;growthY;growthZ;biasIdX;biasIdY;biasIdZ;boxOriginX;boxOriginY;boxOriginZ;boxWidthX;boxWidthY;boxWidthZ;frameId;elemsPerCube;cubeCountX;cubeCountY;cubeCountZ;partitionDirection;partitionCountX;partitionCountY;partitionCountZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `meshType` | `text` | — | Selects the mesh type for EulerMeshGenerator. |
| 3 | `elemSizeX` | `real` | — | Size of the element size dimension along X in length units. |
| 4 | `elemSizeY` | `real` | — | Size of the element size dimension along Y in length units. |
| 5 | `elemSizeZ` | `real` | — | Size of the element size dimension along Z in length units. |
| 6 | `xReference` | `real` | — | Reference point. |
| 7 | `yReference` | `real` | — | Y coordinate of the point from which the definition is measured. |
| 8 | `zReference` | `real` | — | Z coordinate of the point from which the definition is measured. |
| 9 | `originX` | `real` | — | X coordinate of the origin. |
| 10 | `originY` | `real` | — | Y coordinate of the origin. |
| 11 | `originZ` | `real` | — | Z coordinate of the origin. |
| 12 | `widthX` | `real` | — | Size of the width dimension along X in length units. |
| 13 | `widthY` | `real` | — | Size of the width dimension along Y in length units. |
| 14 | `widthZ` | `real` | — | Size of the width dimension along Z in length units. |
| 15 | `elemCountX` | `integer` | — | Number of element subdivisions along X. |
| 16 | `elemCountY` | `integer` | — | Number of element subdivisions along Y. |
| 17 | `elemCountZ` | `integer` | — | Number of element subdivisions along Z. |
| 18 | `subMeshId` | `integer` | 0 | Identifier selecting the sub mesh record or set. |
| 19 | `firstNodeId` | `integer` | 0 | Identifier selecting the first node record or set. |
| 20 | `firstElemId` | `integer` | 0 | Identifier selecting the first element record or set. |
| 21 | `propKind` | `text` | — | Selects the property kind for EulerMeshGenerator. |
| 22 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 23 | `resize` | `text` | — | Selects whether and how mesh resizing is applied. |
| 24 | `resizeTableIdX` | `integer` | 0 | Table controlling resizing of the Eulerian mesh in direction X. |
| 25 | `resizeTableIdY` | `integer` | 0 | Table controlling resizing of the Eulerian mesh in direction Y. |
| 26 | `resizeTableIdZ` | `integer` | 0 | Table controlling resizing of the Eulerian mesh in direction Z. |
| 27 | `remeshMethod` | `text` | — | Selects the remesh method for EulerMeshGenerator. |
| 28 | `biasStart` | `text` | — | Start of the interval over which the mesh bias is applied. |
| 29 | `growthX` | `real` | — | Ratio of the finest to the coarsest element size. |
| 30 | `growthY` | `real` | — | Variation of cell size in the y direction of the Eulerian mesh. |
| 31 | `growthZ` | `real` | — | Variation of cell size in the z direction of the Eulerian mesh. |
| 32 | `biasIdX` | `integer` | 0 | Identifier of the mesh-bias definition in direction X. |
| 33 | `biasIdY` | `integer` | 0 | Identifier of the mesh-bias definition in direction Y. |
| 34 | `biasIdZ` | `integer` | 0 | Identifier of the mesh-bias definition in direction Z. |
| 35 | `boxOriginX` | `real` | — | X coordinate of the box origin. |
| 36 | `boxOriginY` | `real` | — | Y coordinate of the box origin. |
| 37 | `boxOriginZ` | `real` | — | Z coordinate of the box origin. |
| 38 | `boxWidthX` | `real` | — | Size of the box width dimension along X in length units. |
| 39 | `boxWidthY` | `real` | — | Size of the box width dimension along Y in length units. |
| 40 | `boxWidthZ` | `real` | — | Size of the box width dimension along Z in length units. |
| 41 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 42 | `elemsPerCube` | `integer` | 1 | Guideline for the number of elements per cube. |
| 43 | `cubeCountX` | `integer` | — | Number of cube subdivisions along X. |
| 44 | `cubeCountY` | `integer` | — | Number of cube subdivisions along Y. |
| 45 | `cubeCountZ` | `integer` | — | Number of cube subdivisions along Z. |
| 46 | `partitionDirection` | `text` | — | Direction used to divide the mesh into partitions. |
| 47 | `partitionCountX` | `integer` | — | Number of partition subdivisions along X. |
| 48 | `partitionCountY` | `integer` | — | Number of partition subdivisions along Y. |
| 49 | `partitionCountZ` | `integer` | — | Number of partition subdivisions along Z. |

Accepted words: `Adaptive`, `All`, `Box`, `Center`, `Constant`, `Element`, `Euler`, `Length`, `Material`, `None`, `Reference`, `Scale`, `Simple`, `Table`, `User`, `XDirection`, `YDirection`, `ZDirection`.

**Example record**

~~~text
EulerMeshGenerator;1;Box;;;;;;;0.;0.;0.;400.;100.;100.;16;4;4;;;;Euler;10
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 1`, `meshType = Box`, `originX = 0.`, `originY = 0.`.

## EulerProp

The property of the Eulerian elements ([SolidHexa](elements.md#solidhexa) and the elements an [EulerMeshGenerator](explicit.md#eulermeshgenerator) generates) that name its property ID.

**Record format and fields**

`EulerProp;id;matId;solverType`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `solverType` | `text` | Hydrodynamic | Selects the solver type for EulerProp. |

Accepted words: `Constant`, `Element`, `FirstOrder`, `Hydrodynamic`, `MultiMaterialHydrodynamic`, `MultiMaterialStrength`, `SecondOrder`, `Strength`, `Table`.

**Example record**

~~~text
EulerProp;2;3;Hydrodynamic
~~~

[Model containing this record](../../../validation/models/dynamics/explicit_initial_conditions_sol700.oos)

Reading the example gives `id = 2`, `matId = 3`, `solverType = Hydrodynamic`.

## EulerRegionProp

The property of Eulerian elements whose initial conditions are given in geometric regions (an [EulerInitialRegions](explicit.md#eulerinitialregions)) instead of one material, as an [EulerProp](explicit.md#eulerprop) does.

**Record format and fields**

`EulerRegionProp;id;solverType;initialRegionsId;bodyForceSetId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `solverType` | `text` | — | Selects the solver type for EulerRegionProp. |
| 3 | `initialRegionsId` | `integer` | Required | Identifier selecting the initial regions record or set. |
| 4 | `bodyForceSetId` | `integer` | 0 | Identifier selecting the body force set record or set. |

Accepted words: `Constant`, `Element`, `FirstOrder`, `Hydrodynamic`, `MultiMaterialHydrodynamic`, `MultiMaterialStrength`, `SecondOrder`, `Strength`, `Table`.

**Example record**

~~~text
EulerRegionProp;10;MultiMaterialHydrodynamic;20;30
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 10`, `solverType = MultiMaterialHydrodynamic`, `initialRegionsId = 20`, `bodyForceSetId = 30`.

## EulerTimeFlowBoundary

A flow boundary of an Euler mesh whose inflow velocity, pressure and material properties may depend on time.

**Record format and fields**

`EulerTimeFlowBoundary;id;contactBodyId;flowType;meshId;meshFace;minX;maxX;minY;maxY;minZ;maxZ;velocitySource;velocity;pressureSource;pressure;matId;densitySource;density;energySource;specificEnergy`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `contactBodyId` | `integer` | 0 | Identifier selecting the contact body record or set. |
| 3 | `flowType` | `text` | — | Selects the flow type for EulerTimeFlowBoundary. |
| 4 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 5 | `meshFace` | `text` | — | Face of the mesh on which the boundary condition or operation acts. |
| 6 | `minX` | `real` | — | X coordinate of the lower spatial bound. |
| 7 | `maxX` | `real` | — | X coordinate of the upper spatial bound. |
| 8 | `minY` | `real` | — | Y coordinate of the lower spatial bound. |
| 9 | `maxY` | `real` | — | Y coordinate of the upper spatial bound. |
| 10 | `minZ` | `real` | — | Z coordinate of the lower spatial bound. |
| 11 | `maxZ` | `real` | — | Z coordinate of the upper spatial bound. |
| 12 | `velocitySource` | `text` | Element | Selects the source used to supply the velocity. |
| 13 | `velocity` | `any` | — | Rate of displacement in the specified direction (length per time). |
| 14 | `pressureSource` | `text` | Element | Selects the source used to supply the pressure. |
| 15 | `pressure` | `any` | — | Normal force per unit area, in the model’s pressure units. |
| 16 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 17 | `densitySource` | `text` | Element | Selects the source used to supply the density. |
| 18 | `density` | `any` | — | Mass per unit volume for a volumetric material or fluid density. |
| 19 | `energySource` | `text` | Element | Selects the source used to supply the energy history. |
| 20 | `specificEnergy` | `any` | — | Energy per unit mass. |

Accepted words: `Both`, `Constant`, `Density`, `Element`, `Flow`, `Hydrostatic`, `In`, `Inside`, `Large`, `Material`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Pressure`, `Small`, `SpecificInternalEnergy`, `Symmetry`, `Table`, `VelocityX`, `VelocityY`, `VelocityZ`.

**Example record**

~~~text
EulerTimeFlowBoundary;2;;Out;;PositiveXDirection
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 2`, `flowType = Out`, `meshFace = PositiveXDirection`.

## EulerUserFlowBoundary

A flow boundary of an Euler mesh that a user subroutine computes.

**Record format and fields**

`EulerUserFlowBoundary;setId;groupName;userRoutineName;contactBodyId;meshId;meshFace;minX;maxX;minY;maxY;minZ;maxZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |
| 4 | `contactBodyId` | `integer` | 0 | Identifier selecting the contact body record or set. |
| 5 | `meshId` | `integer` | 0 | Identifier selecting the mesh record or set. |
| 6 | `meshFace` | `text` | — | Face of the mesh on which the boundary condition or operation acts. |
| 7 | `minX` | `real` | — | X coordinate of the lower spatial bound. |
| 8 | `maxX` | `real` | — | X coordinate of the upper spatial bound. |
| 9 | `minY` | `real` | — | Y coordinate of the lower spatial bound. |
| 10 | `maxY` | `real` | — | Y coordinate of the upper spatial bound. |
| 11 | `minZ` | `real` | — | Z coordinate of the lower spatial bound. |
| 12 | `maxZ` | `real` | — | Z coordinate of the upper spatial bound. |

Accepted words: `Both`, `Constant`, `Element`, `ExternalFlow`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
EulerUserFlowBoundary;51;myflow;ExternalFlow;;1;NegativeXDirection
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `setId = 51`, `groupName = myflow`, `userRoutineName = ExternalFlow`, `meshId = 1`.

## ExplicitParam

A named parameter of the explicit solver.

**Record format and fields**

`ExplicitParam;entryName;<fieldValues>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |

**Repeated group `fieldValues`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fieldValue` | `any` | — | Value of the selected field at the point or region identified in this entry. |

Accepted words: `All`, `Automatic`, `AutomaticSize`, `Average`, `AverageDisplacement`, `AxialMesh`, `BatchSize`, `BeamEntities`, `Belt`, `BeltElem1`, `BelytschkoLinTsay`, `Both`, `CheckEulerElems`, `CodeV4`, `ContactOutput`, `CoupleSurface`, `CouplingPorosity`, `Cover`, `DampingForce`, `DampingKind`, `DrawBeadContact`, `ElemView`, `Elements`, `Euler`, `EulerPressure`, `EulerSubcyclesMax`, `EulerType9`, `ExternalExplicitProgram`, `ExternalExplicitSolver`, `FaceEntities`, `FacetSurface`, `FailureCriterion`, `Fiber`, `FlanaganBelytschkoStiffness`, `FlanaganBelytschkoViscous`, `FluidStructureCouplingKind`, `Force`, `Full`, `GapKind`, `ImpulseLoad`, `InPlaneMesh`, `InfoParameters`, `InformationKind`, `InternalKind`, `Iterative`, `KeywordHoff`, `LagrangePressure`, `LimitsKind`, `Link`, `MatrixMergeKind`, `MaxForceFactor`, `MaximumUncoupled`, `MembraneKind`, `Metal`, `MidsideNodes`, `NearOnlyKind`, `No`, `NoCheckEulerElems`, `NoFailure`, `NoLink`, `NoOffset`, `NodeOutputOff`, `NodeOutputOn`, `NonMetal`, `None`, `Off`, `On`, `OrbitKind`, `PlaneXy`, `PlaneYz`, `PlaneZx`, `PolynomialPacking`, `PolynomialPackingShort`, `PorousKind`, `ProcessorInformation`, `ProcessorLoopCount`, `Radial`, `RectRegion`, `Reduced`, `RemoveKind`, `RoeScheme`, `SharedMemoryParallel`, `ShellEntities`, `Side21Kind`, `Simple`, `SolidEntities`, `SphericalKind`, `Steps`, `Sum`, `TableDynamic1`, `ThicknessKind`, `User`, `Vector`, `VersionKind`, `XAxis`, `YAxis`, `Yes`, `ZAxis`, `Zero`.

Accepted parameter names: `AccelerationX`, `AccelerationY`, `AccelerationZ`, `ActiveState`, `AlignmentOption`, `AreaTolerance`, `AutoCoupling`, `AxialRemap`, `AxialSymmetry`, `AxialSymmetryAxis`, `BoxCountX`, `BoxCountY`, `BoxCountZ`, `BulkViscosityKind`, `CenterX`, `CenterY`, `CenterZ`, `CleanupOption`, `ClumpEnergy`, `ClumpFlowLimit`, `CohesionOption`, `ContactDefaults`, `CouplingFriction`, `CouplingSubcycleMaxTime`, `CubeLimit`, `CycleCount`, `DensityCutoff`, `DistributedParallelOptions`, `DummySegments`, `DummyValue`, `ElemsPerCube`, `EntityKind`, `EulerCubeBlocks`, `EulerPartitioning`, `EulerSubcycles`, `EulerSubcyclesMax`, `EulerTransport`, `FailureOption`, `FailureOutput`, `FailureTimeStep`, `FastCoupling`, `FirstRigidBodyName`, `FlowMethod`, `FrictionCoefficient`, `FullRigidCoupling`, `GasMixing`, `GeometryCheckOption`, `GravityAcceleration`, `HourglassCoefficient`, `HourglassKind`, `HourglassMembraneCoefficient`, `HourglassShell`, `HourglassSolid`, `HourglassSolidCoefficient`, `HourglassTwistCoefficient`, `HourglassWarpCoefficient`, `HydroVolumeFailure`, `HydrostaticBody`, `HydrostaticInitialGravity`, `InfoObjects`, `InfoParameters`, `InitialMetricMethod`, `InitialStep`, `InternalOption`, `JonesWilkinsLeeDetonation`, `KeyName`, `KindChoice`, `LagrangePartitioning`, `LimiterKind`, `LinearBulkViscosity`, `MassScaling`, `MaxPercent`, `MaxStepSize`, `MaxStress`, `MaxSubcycles`, `MaxVelocity`, `MaxVelocity1`, `MaxVelocityAdapted`, `MaxVelocityChange`, `MaxVelocityTime`, `MaximumX`, `MaximumY`, `MaximumZ`, `MeshKind`, `MeshPlane`, `MinPressureFailure`, `MinStepSize`, `MinTimeStep`, `MinimumX`, `MinimumY`, `MinimumZ`, `NextRigidBodyName`, `NormalX`, `NormalY`, `NormalZ`, `OccupantAccelerationOutput`, `OccupantHistoryOutput`, `OccupantTimeOutput`, `OldLagrangeTime`, `OriginX`, `OriginY`, `OriginZ`, `OutputChoice`, `ParallelOption`, `PartitionCountX`, `PartitionCountY`, `PartitionCountZ`, `PartitionDirection`, `PartitionMethod`, `PhiValue`, `PhiValue2`, `PlasticCoverCut`, `PointMassOutput`, `ProcessorLoopCount`, `QuadraticBulkViscosity`, `RadialAxis`, `ReferenceVelocity`, `RemapRange`, `RigidBodyMerge`, `RigidBodyMerge1`, `RigidBodyStarInfo`, `RigidJointStiffness`, `ScaleFactor`, `SelectedElems`, `SharedMemoryParallel`, `ShellElemSystem`, `ShellFormulation`, `ShellPlasticity`, `ShellStrainDefinition`, `ShellThicknessUpdate`, `SmallestTimeStepElemCount`, `SoundSpeedLimit`, `SphericalRemap`, `SphericalSymmetry`, `StepCount`, `StrainOutput`, `SubcycleLink`, `SymmetryPlane`, `ToleranceCheck`, `VectorX`, `VectorY`, `VectorZ`, `VelocityDamping`, `Viscoplasticity`, `ZeroNodeVelocity`.

**Example record**

~~~text
ExplicitParam;FastCoupling;InPlaneMesh;FailureCriterion
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_compartment_failure.oos)

Reading the example gives `entryName = FastCoupling`.

Rigid-body designators of RigidBodyMerge and RigidBodyMerge1 use RigidAssembly(id) or RigidMat(id), with a positive ID and exact case.

## ExplicitTextEnd

Closes the opaque group opened by [ExplicitTextStart](explicit.md#explicittextstart).

**Record format and fields**

`ExplicitTextEnd`

This part of the record has no fixed fields.

**Example record**

~~~text
ExplicitTextEnd
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

## ExplicitTextStart

Opens an opaque group of records for an external explicit solver.

**Record format and fields**

`ExplicitTextStart`

This part of the record has no fixed fields.

**Example record**

~~~text
ExplicitTextStart
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

## FluidFilledContainer

The pressure inside a closed volume that holds a fluid and a gas, for containers where the motion of the fluid does not matter (loading a bottle from the top, hot filling).

**Record format and fields**

`FluidFilledContainer;id;surfaceId;fluidVolume;atmosphericPressure;temperatureTableId;densityTableId;activationTime`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `surfaceId` | `integer` | Required | Identifier selecting the surface record or set. |
| 3 | `fluidVolume` | `real` | Required | Fluid volume (length cubed). |
| 4 | `atmosphericPressure` | `real` | Required | Atmospheric pressure (force per area). |
| 5 | `temperatureTableId` | `integer` | 0 | Table supplying the variation of temperature. |
| 6 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 7 | `activationTime` | `real` | — | Activation time (time). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FluidFilledContainer;1;104;6.E+5;0.1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 1`, `surfaceId = 104`, `fluidVolume = 6.E+5`, `atmosphericPressure = 0.1`.

## FluidStructureSwitch

The switch that turns the fluid-structure interaction and the Euler solver on and off in time.

**Record format and fields**

`FluidStructureSwitch;id;tableId;eulerInitialization`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 3 | `eulerInitialization` | `text` | — | Selects the initial-state treatment of the Eulerian mesh. |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
FluidStructureSwitch;81;82;No
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 81`, `tableId = 82`, `eulerInitialization = No`.

## GammaLawStateEquation

The gamma law equation of state of a gas, p = (gamma - 1) rho e.

**Record format and fields**

`GammaLawStateEquation;id;gammaCoefficient;gasConstant;specificHeatVolume;specificHeatPressure;viscosity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `gammaCoefficient` | `real` | — | Coefficient in the relation for gamma. |
| 3 | `gasConstant` | `real` | — | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 4 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 5 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |
| 6 | `viscosity` | `real` | — | Viscous response coefficient in the selected constitutive or flow law. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
GammaLawStateEquation;1;1.4;287.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_detonation_mm.oos)

Reading the example gives `id = 1`, `gammaCoefficient = 1.4`, `gasConstant = 287.`.

## GasBag

Represents the uniform pressure within a closed volume enclosed by a coupling surface.

**Record format and fields**

`GasBag;id;surfaceId;trigger;triggerOffset;porosityId;inflatorId;heatTransferId;initialGasId;specificHeatSource;specificHeatPressure;gasConstant;environmentPressure;reverseNormals;checkNormals;initialPressure;initialTemperature;environmentTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `surfaceId` | `integer` | Required | Identifier selecting the surface record or set. |
| 3 | `trigger` | `text` | — | Condition or signal that initiates the specified event. |
| 4 | `triggerOffset` | `real` | 0.0 | The offset in time, 0.0 for none. |
| 5 | `porosityId` | `integer` | 0 | Identifier selecting the porosity record or set. |
| 6 | `inflatorId` | `integer` | 0 | Identifier selecting the inflator record or set. |
| 7 | `heatTransferId` | `integer` | 0 | Identifier selecting the heat transfer record or set. |
| 8 | `initialGasId` | `integer` | 0 | Identifier selecting the initial gas record or set. |
| 9 | `specificHeatSource` | `text` | — | Selects how the heat capacity is supplied. |
| 10 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |
| 11 | `gasConstant` | `real` | Required | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 12 | `environmentPressure` | `real` | Required | Environment pressure (force per area). |
| 13 | `reverseNormals` | `text` | — | Reverses the orientation of the selected normals. |
| 14 | `checkNormals` | `text` | — | Requests a consistency check on the orientation of surface normals. |
| 15 | `initialPressure` | `real` | same as environmentPressure | Pressure assigned to the initial state. |
| 16 | `initialTemperature` | `real` | Required | Initial temperature (temperature). |
| 17 | `environmentTemperature` | `real` | same as initialTemperature | Environment temperature (temperature). |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`, `Time`.

**Example record**

~~~text
GasBag;2;102;;;12;22;;;Constant;1.005E+9;2.87E+8;0.1;On;On;;293.;293.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 2`, `surfaceId = 102`, `porosityId = 12`, `inflatorId = 22`.

## GasBagConvection

The heat transfer through convection from an air bag to its environment, through the surface of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or a [GasBag](explicit.md#gasbag).

**Record format and fields**

`GasBagConvection;id;coefficient;coefficientTableId;environmentTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficient` | `real` | — | Coefficient value in the GasBagConvection relation. |
| 3 | `coefficientTableId` | `integer` | 0 | Table supplying the variation of coefficient. |
| 4 | `environmentTemperature` | `real` | Required | Environment temperature (temperature). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
GasBagConvection;1;0.025;;293.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 1`, `coefficient = 0.025`, `environmentTemperature = 293.`.

## GasBagHeatTransfer

A heat transfer definition of a part of the surface of a [GasBag](explicit.md#gasbag) or an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling), which names the card that describes the transfer (a convection [GasBagConvection](explicit.md#gasbagconvection), a radiation [GasBagRadiation](explicit.md#gasbagradiation)).

**Record format and fields**

`GasBagHeatTransfer;id;setId;subsurfaceId;modelKind;modelId;coefficientSource;coefficient`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 3 | `subsurfaceId` | `integer` | 0 | Identifier selecting the subsurface record or set. |
| 4 | `modelKind` | `text` | — | Selects the model kind for GasBagHeatTransfer. |
| 5 | `modelId` | `integer` | Required | Identifier selecting the model record or set. |
| 6 | `coefficientSource` | `text` | — | Selects the source of the coefficient used in the material or flow relation. |
| 7 | `coefficient` | `any` | — | Coefficient value in the GasBagHeatTransfer relation. |

Accepted words: `Constant`, `Element`, `GasBagConvection`, `GasBagRadiation`, `Table`.

**Example record**

~~~text
GasBagHeatTransfer;3;32;0;GasBagConvection;1;Constant;1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 3`, `setId = 32`, `subsurfaceId = 0`, `modelKind = GasBagConvection`.

## GasBagLeakage

A porosity definition of a part of the surface of a [GasBag](explicit.md#gasbag) or an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling), which names the card that describes the flow (a hole, a permeable material, a flow boundary).

**Record format and fields**

`GasBagLeakage;id;setId;subsurfaceId;porosityKind;porosityModelId;coefficientSource;coefficient`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 3 | `subsurfaceId` | `integer` | 0 | Identifier selecting the subsurface record or set. |
| 4 | `porosityKind` | `text` | — | Selects the porosity kind for GasBagLeakage. |
| 5 | `porosityModelId` | `integer` | Required | Identifier selecting the porosity model record or set. |
| 6 | `coefficientSource` | `text` | — | Selects the source of the coefficient used in the material or flow relation. |
| 7 | `coefficient` | `any` | — | Coefficient value in the GasBagLeakage relation. |

Accepted words: `Constant`, `CouplingHoleToCoupling`, `CouplingHoleToGasBag`, `Element`, `GasBagPermeableLink`, `GasBagVentHole`, `PorousFlowBoundary`, `PorousHydrostaticBoundary`, `PorousTimeFlowBoundary`, `PorousUserBoundary`, `SurfacePermeability`, `Table`.

**Example record**

~~~text
GasBagLeakage;1;1;201;GasBagVentHole;1;Constant;1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `setId = 1`, `subsurfaceId = 201`, `porosityKind = GasBagVentHole`.

## GasBagPermeableLink

A permeable area of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or [GasBag](explicit.md#gasbag) surface that is connected to another [GasBag](explicit.md#gasbag).

**Record format and fields**

`GasBagPermeableLink;id;permeability;permeabilityTableId;flowDirection;gasBagId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `permeability` | `real` | — | The linear coefficient, zero or more. |
| 3 | `permeabilityTableId` | `integer` | 0 | Table supplying the variation of permeability. |
| 4 | `flowDirection` | `text` | — | Direction used for the flow through the boundary or region. |
| 5 | `gasBagId` | `integer` | Required | Identifier selecting the gas bag record or set. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
GasBagPermeableLink;5;1.E+3;;Both;3
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 5`, `permeability = 1.E+3`, `flowDirection = Both`, `gasBagId = 3`.

## GasBagRadiation

The heat transfer through radiation from an air bag to its environment, through the surface of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or a [GasBag](explicit.md#gasbag).

**Record format and fields**

`GasBagRadiation;id;emissivity;emissivityTableId;environmentTemperature;stefanBoltzmann`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `emissivity` | `real` | — | Ratio of emitted radiation to that of a black body at the same temperature. |
| 3 | `emissivityTableId` | `integer` | 0 | Table supplying the variation of emissivity. |
| 4 | `environmentTemperature` | `real` | Required | Environment temperature (temperature). |
| 5 | `stefanBoltzmann` | `real` | Required | The Stefan-Boltzmann constant. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
GasBagRadiation;2;0.15;;293.;5.67E-11
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 2`, `emissivity = 0.15`, `environmentTemperature = 293.`, `stefanBoltzmann = 5.67E-11`.

## GasBagSwitch

The switch of an air bag from full gas dynamics (an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling), the Euler-Lagrange coupling) to the uniform pressure formulation (a [GasBag](explicit.md#gasbag)).

**Record format and fields**

`GasBagSwitch;id;couplingId;gasBagId;startTime;validityPercent`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `couplingId` | `integer` | Required | Identifier selecting the coupling record or set. |
| 3 | `gasBagId` | `integer` | 0 | Identifier selecting the gas bag record or set. |
| 4 | `startTime` | `real` | 0.0 | Start time (time). |
| 5 | `validityPercent` | `real` | 0.0 | The value of the validity check, in percent. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
GasBagSwitch;1;2;2;0.002;5.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 1`, `couplingId = 2`, `gasBagId = 2`, `startTime = 0.002`.

## GasBagVentHole

A hole in an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or [GasBag](explicit.md#gasbag) surface through which gas flows to the environment (a vent of an air bag).

**Record format and fields**

`GasBagVentHole;id;holeSize;flowDirection;environmentPressure;environmentDensity;environmentEnergy;environmentSpecificHeat;matId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `holeSize` | `text` | — | Dimension of the opening used to determine its effective flow area. |
| 3 | `flowDirection` | `text` | — | Direction used for the flow through the boundary or region. |
| 4 | `environmentPressure` | `real` | Required | Environment pressure (force per area). |
| 5 | `environmentDensity` | `real` | Required | The environment density. |
| 6 | `environmentEnergy` | `real` | Required | The environment specific internal energy. |
| 7 | `environmentSpecificHeat` | `real` | — | The environment specific heat at constant pressure. |
| 8 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
GasBagVentHole;1;Small;Both;0.1;1.2E-12;2.083E+11
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 1`, `holeSize = Small`, `flowDirection = Both`, `environmentPressure = 0.1`.

## HourglassSuppression

The hourglass suppression method and the damping coefficients of the elements of one property.

**Record format and fields**

`HourglassSuppression;id;propKind;propId;method;membraneCoefficient;warpCoefficient;twistCoefficient;solidCoefficient;rotationCorrection;stepCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propKind` | `text` | — | Selects the property kind for HourglassSuppression. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `method` | `text` | — | Selects the method for HourglassSuppression. |
| 5 | `membraneCoefficient` | `real` | — | Coefficient in the relation for membrane. |
| 6 | `warpCoefficient` | `real` | — | Coefficient in the relation for warp. |
| 7 | `twistCoefficient` | `real` | — | Coefficient in the relation for twist. |
| 8 | `solidCoefficient` | `real` | — | Coefficient in the relation for solid. |
| 9 | `rotationCorrection` | `text` | — | Selects the correction for rotation of the moving system. |
| 10 | `stepCount` | `integer` | 0 | Number of step entries. |

Accepted words: `Bar`, `Beam`, `Belt`, `Composite`, `Constant`, `Damper`, `Elastic`, `Element`, `Euler`, `ExternalExplicitProgram`, `FlanaganBelytschkoStiffness`, `FlanaganBelytschkoViscous`, `No`, `Rod`, `Shell`, `Solid`, `Table`, `Yes`.

**Example record**

~~~text
HourglassSuppression;1;Shell;10;FlanaganBelytschkoViscous;0.1;0.1;0.1
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 1`, `propKind = Shell`, `propId = 10`, `method = FlanaganBelytschkoViscous`.

## HybridInflator

A hybrid airbag inflator, which blows a mixture of gases into a [GasBag](explicit.md#gasbag) or an Euler coupling surface ([EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling)) through the [InflatorInlet](loads.md#inflatorinlet) that names the card.

**Record format and fields**

`HybridInflator;id;massFlowTableId;temperatureTableId;temperature;fractionId;<gases>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `massFlowTableId` | `integer` | Required | Table supplying the variation of mass flow. |
| 3 | `temperatureTableId` | `integer` | 0 | Table supplying the variation of temperature. |
| 4 | `temperature` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. |
| 5 | `fractionId` | `integer` | Required | Identifier selecting the fraction record or set. |

**Repeated group `gases`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `gasId` | `integer` | — | Identifier selecting the gas record or set. |

Accepted words: `Constant`, `Element`, `InflatorGas`, `Table`.

**Example record**

~~~text
HybridInflator;2;71;;500.;61;51;52
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 2`, `massFlowTableId = 71`, `temperature = 500.`, `fractionId = 61`.

## HybridInflatorFractions

Defines the time variation of constituent gas fractions for a [HybridInflator](explicit.md#hybridinflator).

**Record format and fields**

`HybridInflatorFractions;id;basis;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `basis` | `text` | Mass | Basis used to express the input data or initial state. |

**Keyed sections in `steps`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `TimeStep`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `time` | `real` | — | Time (time). |

**Repeated group `fractions`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fraction` | `real` | — | Portion of the corresponding total, expressed as a ratio. |

Accepted words: `Constant`, `Element`, `Mass`, `MolarFraction`, `Table`, `TimeStep`.

**Example record**

~~~text
HybridInflatorFractions;61;;TimeStep;0.;2;0.8;0.2;TimeStep;0.005;2;0.5;0.5
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 61`.

## HydrodynamicYield

The hydrodynamic yield model, a yield model whose yield stress is zero.

**Record format and fields**

`HydrodynamicYield;id`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
HydrodynamicYield;3
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 3`.

## IgnitionGrowthStateEquation

Identifies a reactive equation-of-state record in the material data of an explicit model.

**Record format and fields**

`IgnitionGrowthStateEquation;id;inputUnits;explosiveDatabase;outputUnits;unreactedA;unreactedB;unreactedR1;unreactedR2;unreactedOmega;ignitionCoefficient;growthCoefficient;ignitionDensityCoefficient;productA;productB;productR1;productR2;productOmega;burnExponentX;burnExponentY;pressureExponent;densityExponent;chemicalEnergy;pressureTolerance;maxIterations`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `inputUnits` | `text` | — | Unit convention of the supplied data. |
| 3 | `explosiveDatabase` | `text` | — | Optional material-data label. Omit it when supplying coefficients explicitly. |
| 4 | `outputUnits` | `text` | — | Unit convention of the requested output. |
| 5 | `unreactedA` | `real` | — | Material coefficient A of the unreacted-phase equation of state. |
| 6 | `unreactedB` | `real` | — | Material coefficient B of the unreacted-phase equation of state. |
| 7 | `unreactedR1` | `real` | — | Coefficient R1 for the unreacted phase of the material equation of state. |
| 8 | `unreactedR2` | `real` | — | Coefficient R2 for the unreacted phase of the material equation of state. |
| 9 | `unreactedOmega` | `real` | — | Dimensionless omega coefficient in the unreacted-phase equation of state. |
| 10 | `ignitionCoefficient` | `real` | — | Coefficient in the relation for ignition. |
| 11 | `growthCoefficient` | `real` | — | Coefficient in the relation for growth. |
| 12 | `ignitionDensityCoefficient` | `real` | — | Coefficient in the relation for ignition density. |
| 13 | `productA` | `real` | — | Material coefficient A of the product-phase equation of state. |
| 14 | `productB` | `real` | — | Material coefficient B of the product-phase equation of state. |
| 15 | `productR1` | `real` | — | Coefficient R1 for the product phase of the material equation of state. |
| 16 | `productR2` | `real` | — | Coefficient R2 for the product phase of the material equation of state. |
| 17 | `productOmega` | `real` | — | Dimensionless omega coefficient in the product-phase equation of state. |
| 18 | `burnExponentX` | `real` | — | Surface burning exponent. |
| 19 | `burnExponentY` | `real` | — | Surface burning exponent. |
| 20 | `pressureExponent` | `real` | — | Power in the law for pressure. |
| 21 | `densityExponent` | `real` | — | Power in the law for density. |
| 22 | `chemicalEnergy` | `real` | — | Chemical energy of the explosive per unit mass. |
| 23 | `pressureTolerance` | `real` | — | Permitted numerical deviation for pressure. |
| 24 | `maxIterations` | `integer` | — | Maximum number of iterations permitted at this stage. |

Accepted words: `CentimeterGramMicrosecond`, `Constant`, `Element`, `Explosive94A`, `Explosive94B`, `ImperialUnits`, `InsensitiveExplosive17`, `LengthCompressionB`, `MassCompressionB`, `MetricUnits`, `MillimeterMilligramMicrosecond`, `No`, `PentaShape`, `SiUnits`, `Table`, `TriaminotrinitrobenzeneData`, `TrinitrotolueneData`.

**Example record**

~~~text
IgnitionGrowthStateEquation;1;;;;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1.;1
~~~

Reading the example gives `id = 1`, `unreactedA = 1.`, `unreactedB = 1.`, `unreactedR1 = 1.`.

## InflatorGas

Defines a thermally ideal gas used in a gas mixture or inflator model.

**Record format and fields**

`InflatorGas;id;constantKind;constantValue;heatLaw;heatCoefficient1;heatCoefficient2;heatCoefficient3;heatCoefficient4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `constantKind` | `text` | — | Selects the constant kind for InflatorGas. |
| 3 | `constantValue` | `real` | Required | Fixed value entering the design relation or response. |
| 4 | `heatLaw` | `text` | Constant | Selects the constitutive relation governing the thermal response. |
| 5 | `heatCoefficient1` | `any` | Required | Coefficient in the relation for heat. |
| 6 | `heatCoefficient2` | `real` | 0.0 | Coefficient in the relation for heat. |
| 7 | `heatCoefficient3` | `real` | 0.0 | Coefficient in the relation for heat. |
| 8 | `heatCoefficient4` | `real` | 0.0 | Coefficient in the relation for heat. |

Accepted words: `Constant`, `Element`, `MolecularWeight`, `Polynomial`, `ResponseSpectrum`, `Table`.

**Example record**

~~~text
InflatorGas;52;ResponseSpectrum;2.081E+8;Constant;5.2E+8
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 52`, `constantKind = ResponseSpectrum`, `constantValue = 2.081E+8`, `heatLaw = Constant`.

## InitialConditionRegion

One Eulerian region (a shape and a material) with the set of initial values that its material starts with.

**Record format and fields**

`InitialConditionRegion;id;groupId;shapeType;shapeId;matId;valuesId;level`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `groupId` | `integer` | Required | Identifier selecting the group record or set. |
| 3 | `shapeType` | `text` | — | Selects the shape type for InitialConditionRegion. |
| 4 | `shapeId` | `integer` | Required | Identifier selecting the shape record or set. |
| 5 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 6 | `valuesId` | `integer` | 0 | Identifier selecting the values record or set. |
| 7 | `level` | `real` | 0.0 | The level indicator of the region. |

Accepted words: `Box`, `Constant`, `Cylinder`, `Element`, `Elements`, `Sphere`, `Surface`, `Table`.

**Example record**

~~~text
InitialConditionRegion;2;21;Box;32;12;82;1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_channel_flow_boundaries.oos)

Reading the example gives `id = 2`, `groupId = 21`, `shapeType = Box`, `shapeId = 32`.

## InitialConditionValues

The initial values of an Eulerian region, a list of variables and the value each starts with.

**Record format and fields**

`InitialConditionValues;id;method;<variables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `method` | `text` | — | Selects the method for InitialConditionValues. |

**Repeated group `variables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableName` | `text` | — | Text naming the variable. |
| 2 | `variableValue` | `any` | — | Value of the independent or design variable at the selected evaluation point. |

Accepted words: `ArtificialViscosity`, `CenterX`, `CenterY`, `CenterZ`, `Constant`, `Decay`, `Density`, `Divergence`, `Element`, `MaterialFraction`, `MomentumX`, `MomentumY`, `MomentumZ`, `Normal`, `Radial`, `RadialVelocity`, `SpecificInternalEnergy`, `Table`, `TableDynamic1`, `VelocityX`, `VelocityY`, `VelocityZ`, `VoidFraction`.

**Example record**

~~~text
InitialConditionValues;51;;Density;7.85E-9;VelocityX;2.E+5
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 51`.

## InitialGasComposition

Specifies the initial mixture inside a [GasBag](explicit.md#gasbag) or an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) surface.

**Record format and fields**

`InitialGasComposition;id;<gases>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `gases`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `gasId` | `integer` | — | Identifier selecting the gas record or set. |
| 2 | `fraction` | `real` | — | Portion of the corresponding total, expressed as a ratio. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
InitialGasComposition;41;53;1.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 41`.

## InitialSurfaceVolume

An initialization surface, a closed volume (made of the segments of a [ContactElemSurface](nonlinear_contact.md#contactelemsurface)) that a [EulerInitialRegions](explicit.md#eulerinitialregions) region or an [EulerForceRegion](explicit.md#eulerforceregion) region uses to give initial conditions to the Eulerian elements inside or outside it.

**Record format and fields**

`InitialSurfaceVolume;id;surfaceId;cover;reverseNormals;checkNormals`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `surfaceId` | `integer` | Required | Identifier selecting the surface record or set. |
| 3 | `cover` | `text` | — | Definition of the cover associated with the surface or segment. |
| 4 | `reverseNormals` | `text` | On | Reverses the orientation of the selected normals. |
| 5 | `checkNormals` | `text` | On | Requests a consistency check on the orientation of surface normals. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
InitialSurfaceVolume;33;301;Inside;On;On
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 33`, `surfaceId = 301`, `cover = Inside`, `reverseNormals = On`.

## JohnsonCookFailure

The Johnson-Cook failure model.

**Record format and fields**

`JohnsonCookFailure;id;coefficientD1;coefficientD2;coefficientD3;coefficientD4;coefficientD5;referenceStrainRate;roomTemperature;meltTemperature;specificHeat;method`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientD1` | `real` | 0.0 | Coefficient D1 in the JohnsonCookFailure relation. |
| 3 | `coefficientD2` | `real` | 0.0 | Coefficient D2 in the JohnsonCookFailure relation. |
| 4 | `coefficientD3` | `real` | 0.0 | Coefficient D3 in the JohnsonCookFailure relation. |
| 5 | `coefficientD4` | `real` | 0.0 | Coefficient D4 in the JohnsonCookFailure relation. |
| 6 | `coefficientD5` | `real` | 0.0 | Coefficient D5 in the JohnsonCookFailure relation. |
| 7 | `referenceStrainRate` | `real` | 1.0 | Rate against which the current strain rate is compared (inverse time). |
| 8 | `roomTemperature` | `real` | 0.0 | Ambient reference temperature of the material. |
| 9 | `meltTemperature` | `real` | 1.0E20 | Temperature at which the material reaches its melting state. |
| 10 | `specificHeat` | `real` | 1.0E20 | Energy per unit mass required for one unit of temperature change. |
| 11 | `method` | `text` | — | Selects the method for JohnsonCookFailure. |

Accepted words: `Constant`, `Continue`, `Discard`, `Element`, `NoFailure`, `Table`.

**Example record**

~~~text
JohnsonCookFailure;1;0.05;3.44;-2.12;0.002;0.61;1.;293.;1800.;4.5E+8;Continue
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 1`, `coefficientD1 = 0.05`, `coefficientD2 = 3.44`, `coefficientD3 = -2.12`.

## JohnsonCookYield

The Johnson-Cook yield model.

**Record format and fields**

`JohnsonCookYield;id;coefficientA;coefficientB;coefficientN;coefficientC;coefficientM;referenceStrainRate;specificHeat;meltTemperature;roomTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | Required | Coefficient A in the JohnsonCookYield relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the JohnsonCookYield relation. |
| 4 | `coefficientN` | `real` | 1.0 | Coefficient N in the JohnsonCookYield relation. |
| 5 | `coefficientC` | `real` | 0.0 | Coefficient C in the JohnsonCookYield relation. |
| 6 | `coefficientM` | `real` | 1.0 | Coefficient M in the JohnsonCookYield relation. |
| 7 | `referenceStrainRate` | `real` | 1.0 | Rate against which the current strain rate is compared (inverse time). |
| 8 | `specificHeat` | `real` | — | Energy per unit mass required for one unit of temperature change. |
| 9 | `meltTemperature` | `real` | — | Temperature at which the material reaches its melting state. |
| 10 | `roomTemperature` | `real` | — | Ambient reference temperature of the material. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
JohnsonCookYield;1;350.;275.;0.36;0.022;1.;1.;4.5E+8;1800.;293.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 1`, `coefficientA = 350.`, `coefficientB = 275.`, `coefficientN = 0.36`.

## JonesWilkinsLeeStateEquation

Stores a pressure–volume–energy equation-of-state definition for a material in an explicit model.

**Record format and fields**

`JonesWilkinsLeeStateEquation;id;coefficientA;coefficientB;coefficientR1;coefficientR2;omega;initialPressure;afterburnEnergy;afterburnRate;coefficientM;coefficientN`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | 0.0 | Coefficient A in the JonesWilkinsLeeStateEquation relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the JonesWilkinsLeeStateEquation relation. |
| 4 | `coefficientR1` | `real` | 0.0 | Coefficient R1 in the JonesWilkinsLeeStateEquation relation. |
| 5 | `coefficientR2` | `real` | 0.0 | Coefficient R2 in the JonesWilkinsLeeStateEquation relation. |
| 6 | `omega` | `real` | 0.0 | Material coefficient of the selected equation of state. |
| 7 | `initialPressure` | `real` | 0.0 | Pressure assigned to the initial state. |
| 8 | `afterburnEnergy` | `real` | 0.0 | Afterburning energy constant, not negative. |
| 9 | `afterburnRate` | `real` | 0.0 | Afterburning rate coefficient (the second line's a). |
| 10 | `coefficientM` | `real` | 0.0 | Coefficient M in the JonesWilkinsLeeStateEquation relation. |
| 11 | `coefficientN` | `real` | 0.0 | Coefficient N in the JonesWilkinsLeeStateEquation relation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
JonesWilkinsLeeStateEquation;1
~~~

Reading the example gives `id = 1`.

## MarkerBody

A marker element with two grid points, a line along which the Euler domain records its variables (time histories).

**Record format and fields**

`MarkerBody;id;propId;node1;node2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | Required | Grid point to which this entry applies. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node2` — the two grid points must be different.

**Example record**

~~~text
MarkerBody;70002;72;60002;60003
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 70002`, `propId = 72`, `node1 = 60002`, `node2 = 60003`.

## MarkerNode

A marker element with one grid point, a point at which the Euler domain records its variables (time histories).

**Record format and fields**

`MarkerNode;id;propId;node1`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MarkerNode;70001;71;60001
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 70001`, `propId = 71`, `node1 = 60001`.

## MarkerProp

The property of the marker elements ([MarkerBody](explicit.md#markerbody) and [MarkerNode](explicit.md#markernode)), which record the variables of the Euler domain at a point or along a line.

**Record format and fields**

`MarkerProp;id;markerKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `markerKind` | `text` | — | Selects the marker kind for MarkerProp. |

Accepted words: `Constant`, `Element`, `Fixed`, `Moving`, `Table`.

**Example record**

~~~text
MarkerProp;71;Fixed
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 71`, `markerKind = Fixed`.

## MaxPlasticStrainFailure

The maximum plastic strain failure model.

**Record format and fields**

`MaxPlasticStrainFailure;id;maxPlasticStrain`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `maxPlasticStrain` | `real` | Required | Maximum plastic strain (dimensionless). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MaxPlasticStrainFailure;2;0.3
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 2`, `maxPlasticStrain = 0.3`.

## MieGruneisenStateEquation

The Mie-Gruneisen equation of state, used for the pressure of solids under high strain rates (shock Hugoniot form).

**Record format and fields**

`MieGruneisenStateEquation;id;soundSpeed;shockSlope;gruneisenParameter;densityCutoff`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `soundSpeed` | `real` | Required | Sound speed (length per time). |
| 3 | `shockSlope` | `real` | Required | Linear shock velocity slope. |
| 4 | `gruneisenParameter` | `real` | Required | Gruneisen parameter at the reference density. |
| 5 | `densityCutoff` | `real` | Required | Cut-off value of the density. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MieGruneisenStateEquation;4;3940.;1.49;2.;2.5E+4
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_detonation_mm.oos)

Reading the example gives `id = 4`, `soundSpeed = 3940.`, `shockSlope = 1.49`, `gruneisenParameter = 2.`.

## MohrCoulombYield

The Mohr-Coulomb yield model.

**Record format and fields**

`MohrCoulombYield;id;maxYieldStress;cohesion;internalFriction`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `maxYieldStress` | `real` | Required | Upper stress limit of the yield law. |
| 3 | `cohesion` | `real` | Required | Shear strength intercept in the selected material or interface law. |
| 4 | `internalFriction` | `real` | Required | Resistance to shear associated with internal friction of the material. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MohrCoulombYield;4;50.;0.1;0.6
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 4`, `maxYieldStress = 50.`, `cohesion = 0.1`, `internalFriction = 0.6`.

## NobleAbelStateEquation

The Noble-Abel equation of state of a gas, p = (gamma - 1) rho e / (1 - b rho), the ideal gas law corrected by the co-volume of the molecules.

**Record format and fields**

`NobleAbelStateEquation;id;gammaCoefficient;coVolume;gasConstant;specificHeatVolume;specificHeatPressure`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `gammaCoefficient` | `real` | Required | Coefficient in the relation for gamma. |
| 3 | `coVolume` | `real` | 0.0 | Co volume (length cubed). |
| 4 | `gasConstant` | `real` | — | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 5 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 6 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
NobleAbelStateEquation;5;1.25;0.001;300.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_detonation_mm.oos)

Reading the example gives `id = 5`, `gammaCoefficient = 1.25`, `coVolume = 0.001`, `gasConstant = 300.`.

## OccupantAccelField

An acceleration field, usually a crash pulse, that is applied to segments of the dummy of an external occupant model.

**Record format and fields**

`OccupantAccelField;setId;scaleFactor;directionX;directionY;directionZ;<segmentNames>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |
| 3 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 4 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 5 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

**Repeated group `segmentNames`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `segmentName` | `text` | — | Text naming the segment. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `directionX` — at least one component of the direction must not be zero.

**Example record**

~~~text
OccupantAccelField;5;1.96E+5;-1.;0.;0.;HEAD;NECK
~~~

[Model containing this record](../../../validation/models/read_only_explicit_structures/atb_dummy_interface.oos)

Reading the example gives `setId = 5`, `scaleFactor = 1.96E+5`, `directionX = -1.`, `directionY = 0.`.

## OccupantJoint

The interface to one joint of the dummy of an external occupant model.

**Record format and fields**

`OccupantJoint;id;jointName;orientationNode;node1;node2;node3;elemId1;elemId2;elemId3;node4;node5;node6;node7;elemId4;elemId5;elemId6`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `jointName` | `text` | — | Text naming the joint. |
| 3 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. |
| 4 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 5 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `elemId1` | `integer` | — | Identifier of the element addressed by this record. Entry 1. |
| 8 | `elemId2` | `integer` | — | Identifier of the element addressed by this record. Entry 2. |
| 9 | `elemId3` | `integer` | — | Identifier of the element addressed by this record. Entry 3. |
| 10 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 11 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 12 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 13 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 14 | `elemId4` | `integer` | — | Identifier of the element addressed by this record. Entry 4. |
| 15 | `elemId5` | `integer` | — | Identifier of the element addressed by this record. Entry 5. |
| 16 | `elemId6` | `integer` | — | Identifier of the element addressed by this record. Entry 6. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
OccupantJoint;1;HN;1021;1022;1023;1024;;;;1031;1032;1033;1034
~~~

[Model containing this record](../../../validation/models/read_only_explicit_structures/atb_dummy_interface.oos)

Reading the example gives `id = 1`, `jointName = HN`, `orientationNode = 1021`, `node1 = 1022`.

## OccupantSegment

Defines the position, orientation and identification of a segment in an occupant model.

**Record format and fields**

`OccupantSegment;id;segmentName;cover;elemCount;firstNodeId;firstElemId;matId;coverPropId;orientationNode;node1;node2;node3;elemId1;elemId2;elemId3;centerOfGravityPropId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `segmentName` | `text` | — | Text naming the segment. |
| 3 | `cover` | `text` | — | Definition of the cover associated with the surface or segment. |
| 4 | `elemCount` | `integer` | 0 | Number of element entries. |
| 5 | `firstNodeId` | `integer` | 0 | Identifier selecting the first node record or set. |
| 6 | `firstElemId` | `integer` | 0 | Identifier selecting the first element record or set. |
| 7 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 8 | `coverPropId` | `integer` | 0 | Identifier selecting the cover property record or set. |
| 9 | `orientationNode` | `integer` | — | Grid point defining the orientation direction in place of explicit vector components. |
| 10 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 11 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 12 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 13 | `elemId1` | `integer` | 0 | Identifier of the element addressed by this record. Entry 1. |
| 14 | `elemId2` | `integer` | 0 | Identifier of the element addressed by this record. Entry 2. |
| 15 | `elemId3` | `integer` | 0 | Identifier of the element addressed by this record. Entry 3. |
| 16 | `centerOfGravityPropId` | `integer` | 0 | Identifier selecting the center of gravity property record or set. |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
OccupantSegment;1;HEAD;;;;;;;1001;1002;1003;1004
~~~

[Model containing this record](../../../validation/models/read_only_explicit_structures/atb_dummy_interface.oos)

Reading the example gives `id = 1`, `segmentName = HEAD`, `orientationNode = 1001`, `node1 = 1002`.

## PolynomialShearModel

An elastic shear model whose modulus is a cubic polynomial of the effective plastic shear strain gamma: G = G0 + G1 gamma + G2 gamma^2 + G3 gamma^3.

**Record format and fields**

`PolynomialShearModel;id;shearModulus0;shearModulus1;shearModulus2;shearModulus3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `shearModulus0` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 0. |
| 3 | `shearModulus1` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 1. |
| 4 | `shearModulus2` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 2. |
| 5 | `shearModulus3` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 3. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PolynomialShearModel;4;2.6E+4;500.;-100.;10.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 4`, `shearModulus0 = 2.6E+4`, `shearModulus1 = 500.`, `shearModulus2 = -100.`.

## PolynomialStateEquation

The polynomial equation of state of a solid.

**Record format and fields**

`PolynomialStateEquation;id;coefficientA1;coefficientA2;coefficientA3;coefficientB0;coefficientB1;coefficientB2;coefficientB3;volumeLimit;viscosity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA1` | `real` | 0.0 | Coefficient A1 in the PolynomialStateEquation relation. |
| 3 | `coefficientA2` | `real` | 0.0 | Coefficient A2 in the PolynomialStateEquation relation. |
| 4 | `coefficientA3` | `real` | 0.0 | Coefficient A3 in the PolynomialStateEquation relation. |
| 5 | `coefficientB0` | `real` | 0.0 | Coefficient B0 in the PolynomialStateEquation relation. |
| 6 | `coefficientB1` | `real` | 0.0 | Coefficient B1 in the PolynomialStateEquation relation. |
| 7 | `coefficientB2` | `real` | 0.0 | Coefficient B2 in the PolynomialStateEquation relation. |
| 8 | `coefficientB3` | `real` | 0.0 | Coefficient B3 in the PolynomialStateEquation relation. |
| 9 | `volumeLimit` | `real` | 1.1 | Hydrodynamic volume limit, greater than 1. |
| 10 | `viscosity` | `real` | 0.0 | Viscous response coefficient in the selected constitutive or flow law. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PolynomialStateEquation;5;1.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 5`, `coefficientA1 = 1.`.

## PolynomialYield

The polynomial yield model.

**Record format and fields**

`PolynomialYield;id;coefficientA;coefficientB;coefficientC;coefficientD;coefficientE;coefficientF;maxYieldStress`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | Required | Coefficient A in the PolynomialYield relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the PolynomialYield relation. |
| 4 | `coefficientC` | `real` | 0.0 | Coefficient C in the PolynomialYield relation. |
| 5 | `coefficientD` | `real` | 0.0 | Coefficient D in the PolynomialYield relation. |
| 6 | `coefficientE` | `real` | 0.0 | Coefficient E in the PolynomialYield relation. |
| 7 | `coefficientF` | `real` | 0.0 | Coefficient F in the PolynomialYield relation. |
| 8 | `maxYieldStress` | `real` | — | Upper stress limit of the yield law. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PolynomialYield;2;250.;500.;-200.;;;;600.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 2`, `coefficientA = 250.`, `coefficientB = 500.`, `coefficientC = -200.`.

## PorousFlowBoundary

The properties of a flow of material through a porous part of a coupling surface (a constant flow boundary): the velocity, pressure, density and energy of what flows, the material and the kind of boundary.

**Record format and fields**

`PorousFlowBoundary;id;<properties>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `properties`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyKind` | `text` | — | Selects the property kind for properties. |
| 2 | `propertyValue` | `any` | — | Value of the property identified by this flow-boundary entry. |

Accepted words: `Both`, `Constant`, `Density`, `Element`, `FlowDirection`, `In`, `Inside`, `Large`, `Material`, `Method`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `PressureQuantity`, `Small`, `SpecificInternalEnergy`, `Table`, `VelocityQuantity`, `VelocityX`, `VelocityY`, `VelocityZ`.

**Example record**

~~~text
PorousFlowBoundary;3;FlowDirection;Out;Method;VelocityQuantity
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 3`.

## PorousHydrostaticBoundary

A porous flow boundary that prescribes a hydrostatic pressure profile on a part of a coupling surface.

**Record format and fields**

`PorousHydrostaticBoundary;id`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PorousHydrostaticBoundary;1
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_water_tank_mm.oos)

Reading the example gives `id = 1`.

## PorousTimeFlowBoundary

A flow boundary through a porous part of a coupling surface whose velocity, pressure, density and energy vary with time.

**Record format and fields**

`PorousTimeFlowBoundary;id;flowDirection;velocitySource;velocity;pressureSource;pressure;matId;densitySource;density;energySource;specificEnergy`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `flowDirection` | `text` | Both | Direction used for the flow through the boundary or region. |
| 3 | `velocitySource` | `text` | Element | Selects the source used to supply the velocity. |
| 4 | `velocity` | `any` | — | Rate of displacement in the specified direction (length per time). |
| 5 | `pressureSource` | `text` | Element | Selects the source used to supply the pressure. |
| 6 | `pressure` | `any` | — | Normal force per unit area, in the model’s pressure units. |
| 7 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 8 | `densitySource` | `text` | Element | Selects the source used to supply the density. |
| 9 | `density` | `any` | — | Mass per unit volume for a volumetric material or fluid density. |
| 10 | `energySource` | `text` | Element | Selects the source used to supply the energy history. |
| 11 | `specificEnergy` | `any` | — | Energy per unit mass. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
PorousTimeFlowBoundary;4;In;Table;52
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 4`, `flowDirection = In`, `velocitySource = Table`, `velocity = 52`.

## PorousUserBoundary

A porosity model of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) surface written by the user as a subroutine, served by a user defined service.

**Record format and fields**

`PorousUserBoundary;id;groupName;userRoutineName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

Accepted words: `Constant`, `Element`, `ExternalPorosity`, `Table`.

**Example record**

~~~text
PorousUserBoundary;41;myflow;ExternalPorosity
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 41`, `groupName = myflow`, `userRoutineName = ExternalPorosity`.

## RatePowerLawYield

The rate power law yield model.

**Record format and fields**

`RatePowerLawYield;id;coefficientA;coefficientB;coefficientN;coefficientM;coefficientC`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | Required | Coefficient A in the RatePowerLawYield relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the RatePowerLawYield relation. |
| 4 | `coefficientN` | `real` | 1.0 | Coefficient N in the RatePowerLawYield relation. |
| 5 | `coefficientM` | `real` | 1.0 | Coefficient M in the RatePowerLawYield relation. |
| 6 | `coefficientC` | `real` | — | Coefficient C in the RatePowerLawYield relation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
RatePowerLawYield;5;250.;400.;0.3;0.02;200.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 5`, `coefficientA = 250.`, `coefficientB = 400.`, `coefficientN = 0.3`.

## RigidBodyJoint

A joint between two rigid bodies.

**Record format and fields**

`RigidBodyJoint;id;jointType;node1;node2;node3;node4;node5;node6;penaltyScale`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `jointType` | `text` | — | Selects the joint type for RigidBodyJoint. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `penaltyScale` | `real` | 1.0 | Relative penalty stiffness, not negative. |

Accepted words: `Constant`, `CylindricalJoint`, `Element`, `PlanarJoint`, `RevoluteJoint`, `SphericalJoint`, `Table`, `TranslationalJoint`, `UniversalJoint`.

**Example record**

~~~text
RigidBodyJoint;1;RevoluteJoint;3002;3011;3003;3014
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 1`, `jointType = RevoluteJoint`, `node1 = 3002`, `node2 = 3011`.

## RigidEllipsoidExternal

The external definition of a rigid ellipsoid, whose properties and motion come from another program.

**Record format and fields**

`RigidEllipsoidExternal;ellipsoidName;programName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ellipsoidName` | `text` | — | Text naming the ellipsoid. |
| 2 | `programName` | `text` | — | Text naming the program. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
RigidEllipsoidExternal;HEAD;ATB
~~~

[Model containing this record](../../../validation/models/read_only_explicit_structures/atb_dummy_interface.oos)

Reading the example gives `ellipsoidName = HEAD`, `programName = ATB`.

## RigidWall

Defines an infinite fixed plane serving as a contact boundary for a set of grid points.

**Record format and fields**

`RigidWall;id;pointX;pointY;pointZ;normalX;normalY;normalZ;nodeSetId;method;staticFriction;kineticFriction;frictionDecay`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `pointX` | `real` | 0.0 | X coordinate of the specified point. |
| 3 | `pointY` | `real` | 0.0 | Y coordinate of the specified point. |
| 4 | `pointZ` | `real` | 0.0 | Z coordinate of the specified point. |
| 5 | `normalX` | `real` | 0.0 | X component of the surface or plane normal. |
| 6 | `normalY` | `real` | 0.0 | Y component of the surface or plane normal. |
| 7 | `normalZ` | `real` | 0.0 | Z component of the surface or plane normal. |
| 8 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 9 | `method` | `text` | — | Selects the method for RigidWall. |
| 10 | `staticFriction` | `real` | 0.0 | Static coefficient of friction, not negative. |
| 11 | `kineticFriction` | `real` | 0.0 | Kinetic coefficient of friction, not negative. |
| 12 | `frictionDecay` | `real` | 0.0 | Exponential decay coefficient, not negative. |

Accepted words: `Constant`, `Element`, `Kinematic`, `PenaltyMethod`, `Table`.

**Example record**

~~~text
RigidWall;1;0.;0.;0.;0.;0.;1.;21;PenaltyMethod;0.2;0.1
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 1`, `pointX = 0.`, `pointY = 0.`, `pointZ = 0.`.

## SnowMultiSurfaceYield

The multi-surface yield model of snow.

**Record format and fields**

`SnowMultiSurfaceYield;id;coefficientKc;coefficientT;coefficientCc;coefficientAc;coefficientBc;coefficientFc;coefficientFtu;initialAlpha;coefficientDs`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientKc` | `real` | Required | Coefficient Kc in the SnowMultiSurfaceYield relation. |
| 3 | `coefficientT` | `real` | Required | Coefficient T in the SnowMultiSurfaceYield relation. |
| 4 | `coefficientCc` | `real` | Required | Coefficient Cc in the SnowMultiSurfaceYield relation. |
| 5 | `coefficientAc` | `real` | — | Coefficient Ac in the SnowMultiSurfaceYield relation. |
| 6 | `coefficientBc` | `real` | — | Coefficient Bc in the SnowMultiSurfaceYield relation. |
| 7 | `coefficientFc` | `real` | — | Coefficient Fc in the SnowMultiSurfaceYield relation. |
| 8 | `coefficientFtu` | `real` | — | Hydrostatic tensile strength of the snow yield model (force per area). |
| 9 | `initialAlpha` | `real` | — | Initial value of the alpha state variable of the material law. |
| 10 | `coefficientDs` | `real` | 0.0 | Coefficient Ds in the SnowMultiSurfaceYield relation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SnowMultiSurfaceYield;5;0.149;8.2E-5;1.E-5;0.09;0.2;0.99;2.7E-5;-0.37;0.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 5`, `coefficientKc = 0.149`, `coefficientT = 8.2E-5`, `coefficientCc = 1.E-5`.

## SphereShape

Defines a spherical region used to select Eulerian elements for initial conditions or body forces.

**Record format and fields**

`SphereShape;id;centerX;centerY;centerZ;radius`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `centerX` | `real` | 0.0 | X coordinate of the centre. |
| 3 | `centerY` | `real` | 0.0 | Y coordinate of the centre. |
| 4 | `centerZ` | `real` | 0.0 | Z coordinate of the centre. |
| 5 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SphereShape;31;0.;0.;0.;500.
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 31`, `centerX = 0.`, `centerY = 0.`, `centerZ = 0.`.

## SphericalDetonation

Stores the spherical source definition referenced by an explicit material model.

**Record format and fields**

`SphericalDetonation;id;matId;pointX;pointY;pointZ;detonationSpeed;detonationTime`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `pointX` | `real` | 0.0 | X coordinate of the specified point. |
| 4 | `pointY` | `real` | 0.0 | Y coordinate of the specified point. |
| 5 | `pointZ` | `real` | 0.0 | Z coordinate of the specified point. |
| 6 | `detonationSpeed` | `real` | 0.0 | Detonation speed (length per time). |
| 7 | `detonationTime` | `real` | 0.0 | Detonation time (time). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SphericalDetonation;1;1
~~~

Reading the example gives `id = 1`, `matId = 1`.

## SpotweldJoinPairs

Pairs of grid points of one-dimensional or shell elements that are joined (a spotweld) until the failure criterion of the pair is met.

**Record format and fields**

`SpotweldJoinPairs;id;nodeSetId;tolerance;failureKind;tensileFailureForce;shearFailureForce;multiplePairs;failureTime`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 3 | `tolerance` | `real` | — | Allowable change or residual for the selected numerical check. |
| 4 | `failureKind` | `text` | — | Selects the failure kind for SpotweldJoinPairs. |
| 5 | `tensileFailureForce` | `real` | — | Tensile failure force (force). |
| 6 | `shearFailureForce` | `real` | — | Shear failure force (force). |
| 7 | `multiplePairs` | `text` | — | Controls whether more than one pair may contribute to the interaction. |
| 8 | `failureTime` | `real` | — | Failure time (time). |

Accepted words: `Constant`, `Element`, `No`, `SpotWeld`, `Table`, `Yes`.

**Example record**

~~~text
SpotweldJoinPairs;1;22;;SpotWeld;5.E+3;3.E+3
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 1`, `nodeSetId = 22`, `failureKind = SpotWeld`, `tensileFailureForce = 5.E+3`.

## StandardInflator

A standard airbag inflator.

**Record format and fields**

`StandardInflator;id;massFlowTableId;temperatureTableId;temperature;gasName;specificHeatRatio;specificHeatVolume;gasConstant;specificHeatPressure;matId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `massFlowTableId` | `integer` | Required | Table supplying the variation of mass flow. |
| 3 | `temperatureTableId` | `integer` | 0 | Table supplying the variation of temperature. |
| 4 | `temperature` | `real` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. |
| 5 | `gasName` | `integer` | — | Text naming the gas. Alternative to `specificHeatRatio`. |
| 6 | `specificHeatRatio` | `real` | — | Relative measure of specific heat. Alternative to `gasName`. |
| 7 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 8 | `gasConstant` | `real` | — | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 9 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |
| 10 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |

Accepted words: `Constant`, `Element`, `InflatorGas`, `Table`.

**Example record**

~~~text
StandardInflator;1;72;;600.;;1.4;;2.87E+8
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 1`, `massFlowTableId = 72`, `temperature = 600.`, `specificHeatRatio = 1.4`.

## SteinbergGuinanYield

The Steinberg-Guinan yield model, for metals over a wide range of strain rates.

**Record format and fields**

`SteinbergGuinanYield;id;coefficientA1;coefficientA2;coefficientA3;coefficientA4;coefficientH;coefficientB;specificHeat;meltTemperature;roomTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA1` | `real` | Required | Coefficient A1 in the SteinbergGuinanYield relation. |
| 3 | `coefficientA2` | `real` | Required | Coefficient A2 in the SteinbergGuinanYield relation. |
| 4 | `coefficientA3` | `real` | Required | Coefficient A3 in the SteinbergGuinanYield relation. |
| 5 | `coefficientA4` | `real` | Required | Coefficient A4 in the SteinbergGuinanYield relation. |
| 6 | `coefficientH` | `real` | 0.0 | Coefficient H in the SteinbergGuinanYield relation. |
| 7 | `coefficientB` | `real` | 0.0 | Coefficient B in the SteinbergGuinanYield relation. |
| 8 | `specificHeat` | `real` | 1.0E20 | Energy per unit mass required for one unit of temperature change. |
| 9 | `meltTemperature` | `real` | 1.0E20 | Temperature at which the material reaches its melting state. |
| 10 | `roomTemperature` | `real` | 293.0 | Ambient reference temperature of the material. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SteinbergGuinanYield;2;340.;2500.;43.;0.35;;;4.5E+8;1800.;293.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 2`, `coefficientA1 = 340.`, `coefficientA2 = 2500.`, `coefficientA3 = 43.`.

## SurfacePermeability

The permeability of an [EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling) or [GasBag](explicit.md#gasbag) (sub)surface, the velocity of the gas that flows through it as a function of the pressure difference between the inside and the environment (a linear law, or a table).

**Record format and fields**

`SurfacePermeability;id;permeability;permeabilityTableId;flowDirection;environmentPressure;environmentDensity;environmentEnergy;environmentSpecificHeat`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `permeability` | `real` | — | The linear coefficient, zero or more. |
| 3 | `permeabilityTableId` | `integer` | 0 | Table supplying the variation of permeability. |
| 4 | `flowDirection` | `text` | — | Direction used for the flow through the boundary or region. |
| 5 | `environmentPressure` | `real` | Required | Environment pressure (force per area). |
| 6 | `environmentDensity` | `real` | Required | The environment density. |
| 7 | `environmentEnergy` | `real` | Required | The environment specific internal energy. |
| 8 | `environmentSpecificHeat` | `real` | — | The environment specific heat at constant pressure. |

Accepted words: `Both`, `Constant`, `Element`, `In`, `Inside`, `Large`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `None`, `Off`, `On`, `Out`, `Outside`, `PositiveXDirection`, `PositiveYDirection`, `PositiveZDirection`, `Small`, `Table`.

**Example record**

~~~text
SurfacePermeability;2;1.E+3;;Out;0.1;1.2E-12;2.083E+11
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/euler_gas_box_porosity.oos)

Reading the example gives `id = 2`, `permeability = 1.E+3`, `flowDirection = Out`, `environmentPressure = 0.1`.

## TanimuraMimuraYield

The Tanimura-Mimura yield model, for metals over a wide range of strain rates.

**Record format and fields**

`TanimuraMimuraYield;id;coefficientA;coefficientB;coefficientC;coefficientD;coefficientM;quasiStaticStrainRate;specificHeat;meltTemperature;roomTemperature;criticalStress;coefficientE;coefficientK;referenceStrainRate`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | Required | Coefficient A in the TanimuraMimuraYield relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the TanimuraMimuraYield relation. |
| 4 | `coefficientC` | `real` | 0.0 | Coefficient C in the TanimuraMimuraYield relation. |
| 5 | `coefficientD` | `real` | 0.0 | Coefficient D in the TanimuraMimuraYield relation. |
| 6 | `coefficientM` | `real` | 0.0 | Coefficient M in the TanimuraMimuraYield relation. |
| 7 | `quasiStaticStrainRate` | `real` | 1.0 | Quasi-static strain rate, greater than zero. |
| 8 | `specificHeat` | `real` | — | Energy per unit mass required for one unit of temperature change. |
| 9 | `meltTemperature` | `real` | — | Temperature at which the material reaches its melting state. |
| 10 | `roomTemperature` | `real` | — | Ambient reference temperature of the material. |
| 11 | `criticalStress` | `real` | 1.0 | Critical stress (force per area). |
| 12 | `coefficientE` | `real` | 0.0 | Coefficient E in the TanimuraMimuraYield relation. |
| 13 | `coefficientK` | `real` | 1.0 | Coefficient K in the TanimuraMimuraYield relation. |
| 14 | `referenceStrainRate` | `real` | 1.0 | Rate against which the current strain rate is compared (inverse time). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TanimuraMimuraYield;3;300.;200.;0.1;0.01;1.;1.;4.5E+8;1800.;293.;4.E+3;2100.;0.5;1.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 3`, `coefficientA = 300.`, `coefficientB = 200.`, `coefficientC = 0.1`.

## TankTestInflator

An inflator described by what a tank test measured: the pressure in the tank against time gives the mass flow rate and the temperature of the gas that the inflator blows into a [GasBag](explicit.md#gasbag) or an Euler coupling surface ([EulerLagrangeCoupling](explicit.md#eulerlagrangecoupling)) through the [InflatorInlet](loads.md#inflatorinlet) that names the card.

**Record format and fields**

`TankTestInflator;id;method;tankPressureTableId;tankVolume;inflatorMass;initialPressure;endPressure;initialTemperature;endTemperature;gammaCoefficient;specificHeatVolume;gasConstant;specificHeatPressure;inflatorPressureTableId;inflatorPressure;inflatorTemperature;inflatorArea;tankPressureScale;inflatorPressureScale`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `method` | `text` | — | Selects the method for TankTestInflator. |
| 3 | `tankPressureTableId` | `integer` | Required | Table supplying the variation of tank pressure. |
| 4 | `tankVolume` | `real` | Required | Tank volume (length cubed). |
| 5 | `inflatorMass` | `real` | Required | The mass of gas the inflator generates, greater than zero. |
| 6 | `initialPressure` | `real` | Required | Pressure assigned to the initial state. |
| 7 | `endPressure` | `real` | — | End pressure (force per area). |
| 8 | `initialTemperature` | `real` | — | Initial temperature (temperature). |
| 9 | `endTemperature` | `real` | — | End temperature (temperature). |
| 10 | `gammaCoefficient` | `real` | — | Coefficient in the relation for gamma. |
| 11 | `specificHeatVolume` | `real` | — | Heat capacity per unit mass at constant volume. |
| 12 | `gasConstant` | `real` | Required | Constant relating temperature to the pressure–density response of the gas; use the basis of the selected gas model. |
| 13 | `specificHeatPressure` | `real` | — | Heat capacity per unit mass at constant pressure. |
| 14 | `inflatorPressureTableId` | `integer` | 0 | Table supplying the variation of inflator pressure. |
| 15 | `inflatorPressure` | `real` | — | Inflator pressure (force per area). |
| 16 | `inflatorTemperature` | `any` | AtmosphereUnit | Temperature of the gas delivered by the inflator. |
| 17 | `inflatorArea` | `real` | — | Inflator area (length squared). |
| 18 | `tankPressureScale` | `real` | 1.0 | Multiplier on the measured or tabulated tank pressure. |
| 19 | `inflatorPressureScale` | `real` | 1.0 | Multiplier on the supplied inflator pressure. |

Accepted words: `AtmosphereUnit`, `AverageTemperatureMethod`, `Constant`, `Element`, `InfinitePressure`, `Table`.

**Example record**

~~~text
TankTestInflator;4;AverageTemperatureMethod;73;2.E+6;1.7E-6;0.1;;;;1.4;;2.87E+8
~~~

[Model containing this record](../../../validation/models/explicit_euler_airbag/airbag_three_chambers.oos)

Reading the example gives `id = 4`, `method = AverageTemperatureMethod`, `tankPressureTableId = 73`, `tankVolume = 2.E+6`.

## UserEnforcedVelocity

Enforced velocities at grid points that a user subroutine computes.

**Record format and fields**

`UserEnforcedVelocity;setId;groupName;userRoutineName;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `By`, `Constant`, `Element`, `ExternalVelocity`, `Table`, `Through`.

**Example record**

~~~text
UserEnforcedVelocity;61;extvel;ExternalVelocity;2;3;6;7
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `setId = 61`, `groupName = extvel`, `userRoutineName = ExternalVelocity`.

## UserFailureModel

A failure model that a user subroutine computes.

**Record format and fields**

`UserFailureModel;id;groupName;userRoutineName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

Accepted words: `Constant`, `Element`, `ExternalFailure`, `Table`.

**Example record**

~~~text
UserFailureModel;2;usrmat;ExternalFailure
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 2`, `groupName = usrmat`, `userRoutineName = ExternalFailure`.

## UserServiceData

Integer, real and character data that is handed to the notify method of a user service at the start and the end of a load case and of an increment.

**Record format and fields**

`UserServiceData;serviceId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `serviceId` | `text` | — | Identifier selecting the service record or set. |

**Keyed sections in `blocks`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `IntegerBlock`**

**Repeated group `integers`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `integerData` | `integer` | — | Payload passed in the declared type and order to the consumer of the record. |

**Section `RealBlock`**

**Repeated group `reals`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `realData` | `real` | — | Payload passed in the declared type and order to the consumer of the record. |

**Section `TextBlock`**

**Repeated group `words`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `textData` | `text` | — | Payload passed in the declared type and order to the consumer of the record. |

Accepted words: `Constant`, `Element`, `IntegerBlock`, `RealBlock`, `Table`, `TextBlock`.

**Example record**

~~~text
UserServiceData;NOTIFY;IntegerBlock;2;1;10;TextBlock;1;LOG
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `serviceId = NOTIFY`.

## UserShearModel

A shear model whose modulus is computed by a user subroutine.

**Record format and fields**

`UserShearModel;id;groupName;userRoutineName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

Accepted words: `Constant`, `Element`, `ExternalShear`, `Table`.

**Example record**

~~~text
UserShearModel;2;usrmat;ExternalShear
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 2`, `groupName = usrmat`, `userRoutineName = ExternalShear`.

## UserStateEquation

An equation of state computed by a user subroutine.

**Record format and fields**

`UserStateEquation;id;groupName;userRoutineName;viscosity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |
| 4 | `viscosity` | `real` | — | Viscous response coefficient in the selected constitutive or flow law. |

Accepted words: `Constant`, `Element`, `ExternalStateEquation`, `Table`.

**Example record**

~~~text
UserStateEquation;2;usrmat;ExternalStateEquation;0.01
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 2`, `groupName = usrmat`, `userRoutineName = ExternalStateEquation`, `viscosity = 0.01`.

## UserStateVariables

Declares the number and names of state variables carried by a user material routine.

**Record format and fields**

`UserStateVariables;variableCount;<stateVariables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableCount` | `integer` | — | Number of independent variables used in the definition. |

**Repeated group `stateVariables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableLabel` | `text` | — | Text naming the variable. |
| 2 | `variableName` | `text` | — | Text naming the variable. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `variableLabel` — a state variable is named twice.

**Example record**

~~~text
UserStateVariables;3;SV2;EQPLAS;SV3;DAMAGE
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `variableCount = 3`.

## UserYield

A yield model that a user subroutine computes.

**Record format and fields**

`UserYield;id;groupName;userRoutineName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

Accepted words: `Constant`, `Element`, `ExternalYield`, `Table`.

**Example record**

~~~text
UserYield;2;usrmat;ExternalYield
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 2`, `groupName = usrmat`, `userRoutineName = ExternalYield`.

## VonMisesYield

The von Mises yield model with isotropic hardening.

**Record format and fields**

`VonMisesYield;id;yieldStress;hardeningModulus;tableId;curveType;rateScaleTableId;rateCoefficientD;rateExponentP`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `yieldStress` | `real` | — | Yield stress (force per area). |
| 3 | `hardeningModulus` | `real` | 0.0 | Increment of yield stress per unit plastic strain in the hardening relation. |
| 4 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 5 | `curveType` | `text` | — | Selects the curve type for VonMisesYield. |
| 6 | `rateScaleTableId` | `integer` | 0 | Table supplying the variation of rate scale. |
| 7 | `rateCoefficientD` | `real` | 0.0 | Cowper-Symonds factor D, not negative. |
| 8 | `rateExponentP` | `real` | 0.0 | Cowper-Symonds factor P, not negative. |

Accepted words: `Constant`, `Element`, `EngineeringStrain`, `Plasticity`, `PowerModel`, `Table`, `True`.

**Example record**

~~~text
VonMisesYield;1;250.
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_soil_fluid_yield.oos)

Reading the example gives `id = 1`, `yieldStress = 250.`.

## ZerilliArmstrongYield

The Zerilli-Armstrong yield model.

**Record format and fields**

`ZerilliArmstrongYield;id;coefficientA;coefficientB;coefficientN;coefficientC;coefficientM;referenceStrainRate;specificHeat;coefficientD`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `coefficientA` | `real` | Required | Coefficient A in the ZerilliArmstrongYield relation. |
| 3 | `coefficientB` | `real` | 0.0 | Coefficient B in the ZerilliArmstrongYield relation. |
| 4 | `coefficientN` | `real` | 0.0 | Coefficient N in the ZerilliArmstrongYield relation. |
| 5 | `coefficientC` | `real` | 1.0 | Coefficient C in the ZerilliArmstrongYield relation. |
| 6 | `coefficientM` | `real` | 1.0 | Coefficient M in the ZerilliArmstrongYield relation. |
| 7 | `referenceStrainRate` | `real` | 1.0 | Rate against which the current strain rate is compared (inverse time). |
| 8 | `specificHeat` | `real` | — | Energy per unit mass required for one unit of temperature change. |
| 9 | `coefficientD` | `real` | — | Coefficient D in the ZerilliArmstrongYield relation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ZerilliArmstrongYield;4;65.;890.;0.5;1.15E-4;0.0028;1.;3.85E+8
~~~

[Model containing this record](../../../validation/models/explicit_structures/euler_metal_yield.oos)

Reading the example gives `id = 4`, `coefficientA = 65.`, `coefficientB = 890.`, `coefficientN = 0.5`.
