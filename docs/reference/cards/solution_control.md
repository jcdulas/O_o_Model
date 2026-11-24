# Solution controls

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## ArcLengthParams

The arc-length method of a nonlinear static analysis.

**Record format and fields**

`ArcLengthParams;id;constraintKind;minArcLengthRatio;maxArcLengthRatio;scaleFactor;designIteration;maxIncrements`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `constraintKind` | `text` | Crisfield | Selects the constraint kind for ArcLengthParams. |
| 3 | `minArcLengthRatio` | `real` | 0.25 | Relative measure of minimum arc length. |
| 4 | `maxArcLengthRatio` | `real` | 4.0 | Relative measure of maximum arc length. |
| 5 | `scaleFactor` | `real` | 0.0 | Multiplier applied to the quantity specified by the entry. |
| 6 | `designIteration` | `integer` | 12 | The iterations wanted for convergence. |
| 7 | `maxIncrements` | `integer` | 20 | The largest number of controlled increments of a subcase. |

Accepted words: `Crisfield`, `ModifiedRiks`, `Riks`.

**Example record**

~~~text
ArcLengthParams;10;Crisfield;0.25;4.;;6;40
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol106_arc_length_snap.oos)

Reading the example gives `id = 10`, `constraintKind = Crisfield`, `minArcLengthRatio = 0.25`, `maxArcLengthRatio = 4.`.

## CampbellDiagram

The parameters of the generation of a Campbell diagram and of the tracking of the modes along it.

**Record format and fields**

`CampbellDiagram;id;varyingParameter;discreteValuesId;speedUnit;modeTrackingMethod;correlationThreshold;trackingSwitch;trackedModeCount;printCorrelation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `varyingParameter` | `text` | — | Identifies the independent quantity varied during the sweep. |
| 3 | `discreteValuesId` | `integer` | Required | Identifier of the DesignDiscreteValues list of admissible values. |
| 4 | `speedUnit` | `text` | — | Unit used to express the specified speed. |
| 5 | `modeTrackingMethod` | `integer` | 0 | Selects the mode tracking method for CampbellDiagram. |
| 6 | `correlationThreshold` | `real` | 0.7 | Minimum correlation used when accepting or matching contributions. |
| 7 | `trackingSwitch` | `integer` | 0 | Controls tracking of the selected response through successive points. |
| 8 | `trackedModeCount` | `integer` | — | Number of tracked mode entries. |
| 9 | `printCorrelation` | `integer` | 0 | Controls printing of correlation results. |

Accepted words: `Constant`, `Element`, `Frequency`, `RevolutionsPerMinute`, `Speed`, `Table`.

**Example record**

~~~text
CampbellDiagram;15;Speed;16;RevolutionsPerMinute;1;0.7;1;4;0
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_campbell_sol107.oos)

Reading the example gives `id = 15`, `varyingParameter = Speed`, `discreteValuesId = 16`, `speedUnit = RevolutionsPerMinute`.

## CosimulationArea

The coupled area through which the solver exchanges data with a co-simulation partner.

**Record format and fields**

Forms: `points`, `volume`, `surface`.

### CosimulationArea: points

Form `points`, when `kind` is `Point`.

`CosimulationArea;id;kind;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | Surface | Selects the kind for CosimulationArea. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeIds` | `any` | — | Grid point identifiers defining the selected region. |

### CosimulationArea: volume

Form `volume`, when `kind` is `Volume`.

`CosimulationArea;id;kind;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | Surface | Selects the kind for CosimulationArea. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemIds` | `any` | — | Element identifiers defining the selected model region. |

### CosimulationArea: surface

Form `surface`, for every other record.

`CosimulationArea;id;kind;<faces>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | Surface | Selects the kind for CosimulationArea. |

**Repeated group `faces`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemIds` | `integer` | — | Element identifiers defining the selected model region. |
| 2 | `faceIds` | `integer` | — | Identifiers of the selected element faces. |

*Note*: a list of IDs may hold THRU between two IDs (a range).

Accepted words: `By`, `Constant`, `Element`, `Point`, `Surface`, `Table`, `Through`, `Volume`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `faceIds` — FaceID must be between 1 and 6.

**Example record**

~~~text
CosimulationArea;31;Surface;1;6;2;6;3;6;4;6
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_cosimulation.oos)

## CosimulationInputs

The physical quantities of input that the solver receives from the co-simulation partner.

**Record format and fields**

`CosimulationInputs;id;quantity1;quantity2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `quantity1` | `text` | Force | Physical quantity 1 exchanged across the co-simulation interface. |
| 3 | `quantity2` | `text` | — | Physical quantity 2 exchanged across the co-simulation interface. |

Accepted words: `Constant`, `Element`, `Force`, `Table`, `Temperature`.

**Example record**

~~~text
CosimulationInputs;41;Force
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_cosimulation.oos)

Reading the example gives `id = 41`, `quantity1 = Force`.

## CosimulationOutputs

The physical quantities of output that the solver provides to the co-simulation partner.

**Record format and fields**

`CosimulationOutputs;id;quantity1;quantity2;quantity3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `quantity1` | `text` | — | Physical quantity 1 exchanged across the co-simulation interface. |
| 3 | `quantity2` | `text` | — | Physical quantity 2 exchanged across the co-simulation interface. |
| 4 | `quantity3` | `text` | — | Physical quantity 3 exchanged across the co-simulation interface. |

Accepted words: `Acceleration`, `Constant`, `Displacement`, `Element`, `Table`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `quantity3` — the card has at most three quantities.
- `quantities` — a quantity is given twice.

**Example record**

~~~text
CosimulationOutputs;51;Displacement;Velocity
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_cosimulation.oos)

Reading the example gives `id = 51`, `quantity1 = Displacement`, `quantity2 = Velocity`.

## CosimulationSelection

The co-simulation services an analysis uses, listed by the number of their [CosimulationService](solution_control.md#cosimulationservice).

**Record format and fields**

`CosimulationSelection;id;serviceId1;serviceId2;serviceId3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `serviceId1` | `integer` | — | Identifier selecting the service record or set. |
| 3 | `serviceId2` | `integer` | — | Identifier selecting the service record or set. |
| 4 | `serviceId3` | `integer` | — | Identifier selecting the service record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `serviceId3` — the card has at most three services.

**Example record**

~~~text
CosimulationSelection;21;61
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_cosimulation.oos)

Reading the example gives `id = 21`, `serviceId1 = 61`.

## CosimulationService

A co-simulation service, with the coupled areas and the physical quantities it exchanges.

**Record format and fields**

`CosimulationService;id;serviceName;followerForces;inputAreaId;inputId;outputAreaId;outputId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `serviceName` | `text` | — | Text naming the service. |
| 3 | `followerForces` | `text` | NoFollower | Controls whether applied forces follow the changing geometry. |
| 4 | `inputAreaId` | `integer` | — | Identifier selecting the input area record or set. |
| 5 | `inputId` | `integer` | — | Identifier selecting the input record or set. |
| 6 | `outputAreaId` | `integer` | — | Identifier selecting the output area record or set. |
| 7 | `outputId` | `integer` | — | Identifier selecting the output record or set. |

Accepted words: `Constant`, `Element`, `Follower`, `NoFollower`, `Table`.

**Example record**

~~~text
CosimulationService;61;scFLOW;Follower;31;41;31;51
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_cosimulation.oos)

Reading the example gives `id = 61`, `serviceName = scFLOW`, `followerForces = Follower`, `inputAreaId = 31`.

## CrossSpectrumPair

Pairs two response quantities for cross-power spectral density or cross-correlation recovery.

**Record format and fields**

`CrossSpectrumPair;id;responseKind1;targetId1;component1;responseKind2;targetId2;component2;curveId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `responseKind1` | `text` | same as responseKind2 | Selects the response kind 1 for CrossSpectrumPair. |
| 3 | `targetId1` | `integer` | 0 | Identifier selecting the target record or set. |
| 4 | `component1` | `integer` | 0 | Degree of freedom or response component addressed by this term. Entry 1. |
| 5 | `responseKind2` | `text` | same as responseKind1 | Selects the response kind 2 for CrossSpectrumPair. |
| 6 | `targetId2` | `integer` | 0 | Identifier selecting the target record or set. |
| 7 | `component2` | `integer` | 0 | Degree of freedom or response component addressed by this term. Entry 2. |
| 8 | `curveId` | `integer` | 0 | Identifier selecting the curve record or set. |

Accepted words: `Acceleration`, `AppliedLoad`, `ConstraintForce`, `Displacement`, `Force`, `MultiPointConstraintForce`, `Pressure`, `Strain`, `Stress`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.

**Example record**

~~~text
CrossSpectrumPair;95;Displacement;15;3;Displacement;5;3;1
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 95`, `responseKind1 = Displacement`, `targetId1 = 15`, `component1 = 3`.

## CyclicSymmetry

The parameters of a cyclic symmetry analysis.

**Record format and fields**

`CyclicSymmetry;segmentCount;symmetryKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `segmentCount` | `integer` | — | Number of segment entries. |
| 2 | `symmetryKind` | `text` | — | Selects the symmetry kind for CyclicSymmetry. |

Accepted words: `Axisymmetric`, `Constant`, `Dihedral`, `Element`, `Rotational`, `Table`.

**Example record**

~~~text
CyclicSymmetry;6;Rotational
~~~

[Model containing this record](../../../validation/models/cyclic_symmetry/cyclic_rot_buckling_sol116.oos)

Reading the example gives `segmentCount = 6`, `symmetryKind = Rotational`.

## DeactivatedElems

The elements that do not take part in the analysis, or in one physics pass of a coupled analysis.

**Record format and fields**

`DeactivatedElems;id;elemSetId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `elemSetId` | `integer` | Required | Identifier selecting the element set record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DeactivatedElems;7;8
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_rigid_tools.oos)

Reading the example gives `id = 7`, `elemSetId = 8`.

## EchoOffMarker

Marks the point of the Bulk Data from which the printed echo of the input file is deactivated.

**Record format and fields**

`EchoOffMarker`

This part of the record has no fixed fields.

**Example record**

~~~text
EchoOffMarker
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_echo_metadata_hdf5.oos)

## EchoOnMarker

Marks the point of the Bulk Data from which the printed echo of the input file is activated.

**Record format and fields**

`EchoOnMarker`

This part of the record has no fixed fields.

**Example record**

~~~text
EchoOnMarker
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_echo_metadata_hdf5.oos)

## FatigueDefinition

The elements of a fatigue analysis and the fatigue properties each has, and how much of the result is kept (the top percentage of the entities, the number of hot spots).

**Record format and fields**

`FatigueDefinition;id;topStressCount;fatiguePropIds;topDamageCount;maxEntities;maxOutputEntities;hotSpotCount;hotSpotGate;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `topStressCount` | `real` | — | Number of top stress entries. |
| 3 | `fatiguePropIds` | `integer` | 0 | Identifiers of the fatigue properties included in the definition. |
| 4 | `topDamageCount` | `real` | — | Number of top damage entries. |
| 5 | `maxEntities` | `integer` | — | The number of entities to report: positive by damage, negative by stress range. |
| 6 | `maxOutputEntities` | `integer` | 100 | Maximum number of model entities included in the output. |
| 7 | `hotSpotCount` | `integer` | — | Number of hot spot entries. |
| 8 | `hotSpotGate` | `integer` | 0 | The layers of elements kept around a hot spot. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ElemSet`**

**Repeated group `elemSets`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemSetId` | `integer` | — | Identifier selecting the element set record or set. |
| 2 | `fatiguePropId` | `integer` | — | Identifier selecting the fatigue property record or set. |

**Section `SpotWeld`**

**Repeated group `spotWelds`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemSetId` | `integer` | — | Identifier selecting the element set record or set. |
| 2 | `fatiguePropId` | `integer` | — | Identifier selecting the fatigue property record or set. |

**Section `SeamWeld`**

**Repeated group `seamWelds`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemSetId` | `integer` | — | Identifier selecting the element set record or set. |
| 2 | `fatiguePropId` | `integer` | — | Identifier selecting the fatigue property record or set. |
| 3 | `nodeSetId` | `integer` | — | Identifier of the set supplying the grid points. |
| 4 | `weldType` | `text` | — | Selects the weld type for seamWelds. |
| 5 | `weldLocation` | `text` | — | Position on the weld at which the requested quantity is evaluated. |

**Section `ExcludedElemSet`**

**Repeated group `excludedElemSets`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `excludedElemSetId` | `integer` | — | Identifier selecting the excluded element set record or set. |

Accepted words: `Constant`, `Edge`, `ElemSet`, `Element`, `ExcludedElemSet`, `FilletWeld`, `Generic`, `LaserWeld`, `OverlapWeld`, `RootWeld`, `SeamWeld`, `SpotWeld`, `Table`, `ThroatThickness`, `ToeWeld`.

**Example record**

~~~text
FatigueDefinition;1;;;;;;;;ElemSet;1;71;;ExcludedElemSet;1;72
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/fatigue_property_sets.oos)

Reading the example gives `id = 1`.

## FatigueEvent

Groups fatigue loading histories that act at the same time in a fatigue assessment.

**Record format and fields**

`FatigueEvent;id;<fatigueLoads>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `fatigueLoads`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fatigueLoadId` | `integer` | — | Identifier selecting the fatigue load record or set. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Name`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `eventName` | `text` | — | Text naming the event. Written as one text field. |

Accepted words: `Constant`, `Element`, `FatigueLoad`, `Name`, `Table`.

**Example record**

~~~text
FatigueEvent;21;2;201;202;Name;combined
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 21`.

## FatigueLoad

Describes a load history or spectrum contributing to a fatigue event.

**Record format and fields**

`FatigueLoad;id;tableId;loadCaseId;referenceLoadMagnitude;scaleFactor;offset;historyKind;channel;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 3 | `loadCaseId` | `integer` | Required | Identifier addressing random set data. |
| 4 | `referenceLoadMagnitude` | `real` | 1.0 | Reference load amplitude used for scaling the results. |
| 5 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |
| 6 | `offset` | `real` | — | Shift from the reference location or value in the convention of this entry. |
| 7 | `historyKind` | `text` | — | Selects the history kind for FatigueLoad. |
| 8 | `channel` | `integer` | 0 | Channel of the external data file supplying the sampled history. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Units`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `equivalentUnits` | `real` | 1.0 | Conversion factor between the unit conventions used by the two data sets. |
| 2 | `equivalentUnitName` | `text` | — | Text naming the equivalent unit. Written as one text field. |

**Section `DeterministicLoad`**

**Repeated group `bands`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bandFrequency` | `real` | — | Band frequency (inverse time). |
| 2 | `bandAmplitude` | `real` | — | Amplitude associated with the selected frequency band. |
| 3 | `bandWidth` | `real` | — | Band width (length). |

**Section `SweepLoad`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sweepStartFrequency` | `real` | — | Sweep start frequency (inverse time). |
| 2 | `sweepStartAmplitude` | `real` | — | Amplitude at the start of the requested sweep. |
| 3 | `sweepEndFrequency` | `real` | — | Sweep end frequency (inverse time). |
| 4 | `sweepEndAmplitude` | `real` | — | Amplitude at the end of the requested sweep. |
| 5 | `sweepKind` | `text` | FreqInHertz | Selects the sweep kind for sweep. |
| 6 | `sweepNumber` | `integer` | 50 | Identifier or index of the sweep being specified. |
| 7 | `sweepRate` | `real` | — | Rate at which the sweep progresses through its range. |
| 8 | `sweepCount` | `integer` | — | Number of sweep entries. |
| 9 | `transferFunctionQuantity` | `text` | Acceleration | Response quantity used in the transfer function calculation. |
| 10 | `loadQuantity` | `text` | Acceleration | Physical load quantity to use in the evaluation. |

Accepted words: `Acceleration`, `Constant`, `ConstantLoad`, `DataAcquisitionFile`, `Decibel`, `DeterministicLoad`, `Displacement`, `Element`, `Force`, `FreqInHertz`, `LoadHistoryFile`, `NarrowBand`, `Octave`, `SineLoad`, `SpectralDensityLoad`, `Static`, `SweepLoad`, `Table`, `Units`, `Velocity`.

**Example record**

~~~text
FatigueLoad;201;101;1;100.;1.;0.
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 201`, `tableId = 101`, `loadCaseId = 1`, `referenceLoadMagnitude = 100.`.

## FatigueParams

The parameters of a fatigue analysis (type, combination of the stresses, mean stress correction, location of the results, and the lines for rainflow counting, certainty of survival, factor of safety, spot welds, seam welds, multiaxial assessment, nodal averaging, and vibration fatigue).

**Record format and fields**

`FatigueParams;id;lifeModel;factor;threadCount;logLevel;layer;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `lifeModel` | `text` | StressLifeMethod | Selects the fatigue life relation. |
| 3 | `factor` | `real` | 1.0 | Multiplier on the associated contribution. |
| 4 | `threadCount` | `integer` | — | Number of thread entries. |
| 5 | `logLevel` | `integer` | 0 | Amount of diagnostic information requested. |
| 6 | `layer` | `integer` | 0 | Layer number selected for stress recovery or evaluation. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stress`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combination` | `text` | AbsoluteMaxPrincipal | Rule for combining the contributions included in the analysis. |
| 2 | `meanStressCorrection` | `text` | None | Selects the correction applied to fatigue life for the mean stress. |
| 3 | `plasticityCorrection` | `text` | Neuber | Selects the correction accounting for local plastic response in fatigue. |
| 4 | `resultLocation` | `text` | NodalAveraging | Entity or position at which the result is recovered. |
| 5 | `curveInterpolation` | `integer` | 0 | Specifies how intermediate values on the curve are recovered. |
| 6 | `stressRecovery` | `text` | — | Method or selection used to obtain stress results. |
| 7 | `surfaceResolved` | `text` | No | Selects quantities resolved into components on the specified surface. |
| 8 | `planeAngleCount` | `integer` | 36 | Number of plane angle entries. |

**Section `Strain`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combination` | `text` | AbsoluteMaxPrincipal | Rule for combining the contributions included in the analysis. |
| 2 | `meanStressCorrection` | `text` | None | Selects the correction applied to fatigue life for the mean stress. |
| 3 | `plasticityCorrection` | `text` | Neuber | Selects the correction accounting for local plastic response in fatigue. |
| 4 | `resultLocation` | `text` | NodalAveraging | Entity or position at which the result is recovered. |
| 5 | `curveInterpolation` | `integer` | 0 | Specifies how intermediate values on the curve are recovered. |
| 6 | `stressRecovery` | `text` | — | Method or selection used to obtain stress results. |
| 7 | `surfaceResolved` | `text` | No | Selects quantities resolved into components on the specified surface. |
| 8 | `planeAngleCount` | `integer` | 36 | Number of plane angle entries. |

**Section `RainflowCounting`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `responseKind` | `text` | — | Selects the response kind for rainflow. |

**Section `CertaintyOfSurvival`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `survivalCertainty` | `real` | 50.0 | Survival level associated with the fatigue calculation. |

**Section `FactorOfSafety`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `safetyFactorOption` | `text` | LifeResult | Selects the safety factor option for safetyFactor. |
| 2 | `targetLife` | `real` | — | Design life used as the reference for fatigue assessment. |
| 3 | `backCalculationAccuracy` | `real` | 1.0 | Accuracy requested when the fatigue calculation works back to a load or life value. |
| 4 | `maxSafetyFactor` | `real` | 5.0 | Multiplier for maximum safety. |
| 5 | `minSafetyFactor` | `real` | 0.2 | Multiplier for minimum safety. |

**Section `SpotWeld`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combination` | `text` | StandardCorrection | Rule for combining the contributions included in the analysis. |
| 2 | `meanStressCorrection` | `text` | None | Selects the correction applied to fatigue life for the mean stress. |
| 3 | `planeAngleCount` | `integer` | 18 | Number of plane angle entries. |
| 4 | `spotWeldLocation` | `integer` | 0 | Location of stress evaluation for the spot weld. |
| 5 | `middleSheets` | `integer` | 1 | Intermediate sheets considered in the welded connection. |
| 6 | `torsion` | `integer` | 0 | Selection or value for the torsional component of the response. |

**Section `SeamWeld`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combination` | `text` | AbsoluteMaxPrincipal | Rule for combining the contributions included in the analysis. |
| 2 | `meanStressCorrection` | `text` | None | Selects the correction applied to fatigue life for the mean stress. |
| 3 | `thicknessCorrection` | `integer` | 0 | Selects the correction to the fatigue calculation for material thickness. |
| 4 | `seamWeldLocation` | `text` | Node | Location along the seam at which weld response is evaluated. |
| 5 | `seamWeldResult` | `text` | — | Quantity requested for the seam weld. |

**Section `Multiaxial`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `multiaxialMethod` | `text` | — | Selects the multiaxial method for multiaxial. |
| 2 | `nonProportionalityLower` | `number` | — | Lower bound for classifying nonproportional loading in the fatigue evaluation. |
| 3 | `nonProportionalityUpper` | `number` | — | Upper bound for classifying nonproportional loading in the fatigue evaluation. |
| 4 | `biaxialityLower` | `number` | — | Lower bound for the fatigue model’s biaxiality classification. |
| 5 | `biaxialityMiddle` | `number` | — | Intermediate boundary for classifying biaxial stress states. |
| 6 | `biaxialityUpper` | `number` | — | Upper bound for the fatigue model’s biaxiality classification. |
| 7 | `zeroThreshold` | `number` | — | Magnitude below which the value is treated as zero. |
| 8 | `gateThreshold` | `number` | — | Threshold used to retain or discard small signal variations. |

**Section `NodeAverage`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `averagingMethod` | `text` | Topology | Selects the averaging method for averaging. |
| 2 | `output` | `integer` | 0 | Controls the information recovered or written for this entry. |
| 3 | `surfaceNormal` | `text` | RadiusVector | Direction or convention used for the outward normal of the surface. |

**Section `VibrationFatigue`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `spectrumMethod` | `text` | DirlikMethod | Selects the spectrum method for vibration. |
| 2 | `maxStressRms` | `real` | 10.0 | Upper bound on the root-mean-square stress. |
| 3 | `clipLevel` | `real` | same as maxStressRms | Signal level at which the supplied history is clipped. |
| 4 | `maxPeak` | `real` | — | Peak-value limit used in the fatigue evaluation. |
| 5 | `stressBins` | `integer` | — | Discretization used to group stress ranges or levels. |
| 6 | `maxFrequencyFraction` | `real` | 99.9 | Upper frequency fraction retained in the evaluation. |
| 7 | `binLifeMethod` | `text` | Average | Selects the bin life method for vibration. |

Accepted words: `AbsoluteMaxPrincipal`, `Automatic`, `Average`, `Axis1`, `Axis2`, `Axis3`, `BilinearFit`, `Center`, `CertaintyOfSurvival`, `ComponentXStress`, `ComponentXyStress`, `ComponentYStress`, `ComponentYzStress`, `ComponentZStress`, `ComponentZxStress`, `Constant`, `CornerPoints`, `CriticalPlane`, `CubicFit`, `DirlikMethod`, `Element`, `Elements`, `FactorOfSafety`, `FkmGuideline`, `GeometryOption`, `GerberCorrection`, `GerberTensionCorrection`, `GoodmanCorrection`, `GoodmanTensionCorrection`, `InterpolationMethod`, `LifeResult`, `Load`, `MetallicHandbookData`, `MidSurface`, `MorrowCorrection`, `Multiaxial`, `NarrowBand`, `Neuber`, `No`, `NodalAveraging`, `Node`, `NodeAverage`, `None`, `RadiusVector`, `RainflowCounting`, `ReversedAxis1`, `ReversedAxis2`, `ReversedAxis3`, `ReversedRadiusVector`, `SeamWeld`, `SignedMaxShear`, `SignedVonMises`, `Simple`, `SinesCorrection`, `SmithWatsonTopper`, `SpotWeld`, `Standard`, `StandardCorrection`, `SteinbergModel`, `Strain`, `StrainGageFit`, `StrainLifeMethod`, `Stress`, `StressLifeMethod`, `Table`, `Topology`, `UniversalSlopes`, `UpperKind`, `VibrationFatigue`, `WalkerCorrection`, `Yes`.

**Example record**

~~~text
FatigueParams;10;StressLifeMethod;;;;;Stress;AbsoluteMaxPrincipal;GoodmanCorrection;;Elements;;;;;CertaintyOfSurvival;90.
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 10`, `lifeModel = StressLifeMethod`.

## FatigueProp

Assigns fatigue properties to elements selected by a [FatigueDefinition](solution_control.md#fatiguedefinition).

**Record format and fields**

`FatigueProp;id;surfaceFinish;finishFactor;fatigueNotchFactor;scaleFactor;offset;treatmentFactor;diameter;thickness1;thickness2;spotWeldFlag`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `surfaceFinish` | `text` | — | Surface-condition descriptor used by the fatigue model. |
| 3 | `finishFactor` | `real` | — | Multiplier for finish. |
| 4 | `fatigueNotchFactor` | `real` | 1.0 | Multiplier for fatigue notch. |
| 5 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |
| 6 | `offset` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. |
| 7 | `treatmentFactor` | `real` | 1.0 | Multiplier for treatment. |
| 8 | `diameter` | `real` | — | Diameter (length). |
| 9 | `thickness1` | `real` | — | Through-thickness dimension, in model length units. Entry 1. |
| 10 | `thickness2` | `real` | — | Through-thickness dimension, in model length units. Entry 2. |
| 11 | `spotWeldFlag` | `integer` | 0 | Selects the spot weld flag for FatigueProp. |

Accepted words: `Cast`, `Constant`, `Element`, `GroundSurface`, `MachinedSurface`, `None`, `PolishedSurface`, `PoorSurface`, `RolledSurface`, `RoughnessFactor`, `SurfaceFinishFactor`, `Table`.

**Example record**

~~~text
FatigueProp;51;MachinedSurface;;1.1
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 51`, `surfaceFinish = MachinedSurface`, `fatigueNotchFactor = 1.1`.

## FatigueSequence

The sequence of loading events of a fatigue analysis (pseudo-static, modal, modal transient or random vibration), each with the number of times it is repeated, and possibly other sequences.

**Record format and fields**

`FatigueSequence;id;eventOutput;combinationMethod;timeUnit;referenceLoadMagnitude;<sequenceItems>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `eventOutput` | `integer` | 0 | 1 asks the fatigue output of each event on its own. |
| 3 | `combinationMethod` | `integer` | 0 | Selects the combination method for FatigueSequence. |
| 4 | `timeUnit` | `text` | TimeInSeconds | Unit used for the time axis. |
| 5 | `referenceLoadMagnitude` | `real` | 1.0 | Reference load amplitude used for scaling the results. |

**Repeated group `sequenceItems`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `eventOrSequenceId` | `integer` | — | Identifier selecting the event or sequence record or set. |
| 2 | `repeats` | `real` | — | Number of times the specified event or history occurs. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Units`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `equivalentUnits` | `real` | 1.0 | Conversion factor between the unit conventions used by the two data sets. |
| 2 | `equivalentUnitName` | `text` | — | Text naming the equivalent unit. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`, `TimeInDays`, `TimeInHours`, `TimeInMinutes`, `TimeInMonths`, `TimeInSeconds`, `TimeInWeeks`, `TimeInYears`, `Units`.

**Example record**

~~~text
FatigueSequence;10;1;0;;;2;21;1.E+3;22;5.E+3;Units;1.;blocks
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 10`, `eventOutput = 1`, `combinationMethod = 0`.

## FluidStructureControl

Specifies the analysis mode of a coupled fluid–structure service.

**Record format and fields**

`FluidStructureControl;serviceName;couplingKind;frequency;interfaceKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `serviceName` | `text` | — | Text naming the service. |
| 2 | `couplingKind` | `text` | ExplicitSolver | Selects the coupling kind for FluidStructureControl. |
| 3 | `frequency` | `integer` | 1 | Number of coupling updates per time step. This is an integer update rate. |
| 4 | `interfaceKind` | `text` | DesignVariables | Selects the interface kind for FluidStructureControl. |

Accepted words: `Constant`, `DesignVariables`, `Displacement`, `Element`, `ExplicitSolver`, `ImplicitSolver`, `Table`.

**Example record**

~~~text
FluidStructureControl;fsisvc;ImplicitSolver;2;Displacement
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_fsi_coupling_control.oos)

Reading the example gives `serviceName = fsisvc`, `couplingKind = ImplicitSolver`, `frequency = 2`, `interfaceKind = Displacement`.

## InitialPlasticStrain

Initial equivalent plastic strain for a range of elements, integration points and layers.

**Record format and fields**

`InitialPlasticStrain;firstElemId;lastElemId;firstPoint;lastPoint;firstLayer;lastLayer;strain`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `firstElemId` | `integer` | — | Identifier selecting the first element record or set. |
| 2 | `lastElemId` | `integer` | — | Identifier selecting the last element record or set. |
| 3 | `firstPoint` | `integer` | — | First recovery or evaluation point included in the range. |
| 4 | `lastPoint` | `integer` | — | Last recovery or evaluation point included in the range. |
| 5 | `firstLayer` | `integer` | — | First layer in the requested through-thickness range. |
| 6 | `lastLayer` | `integer` | — | Last layer in the requested through-thickness range. |
| 7 | `strain` | `real` | 0.0 | Strain (dimensionless). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
InitialPlasticStrain;201;202;1;8;;;0.002
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solids_initial_state.oos)

Reading the example gives `firstElemId = 201`, `lastElemId = 202`, `firstPoint = 1`, `lastPoint = 8`.

## InitialStress

An initial stress, for the elements, integration points and layers of a range.

**Record format and fields**

`InitialStress;firstElemId;lastElemId;firstPoint;lastPoint;firstLayer;lastLayer;stress1;stress2;stress3;stress4;stress5;stress6;stress7;coordinate;frameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `firstElemId` | `integer` | — | Identifier selecting the first element record or set. |
| 2 | `lastElemId` | `integer` | — | Identifier selecting the last element record or set. |
| 3 | `firstPoint` | `integer` | — | First recovery or evaluation point included in the range. |
| 4 | `lastPoint` | `integer` | — | Last recovery or evaluation point included in the range. |
| 5 | `firstLayer` | `integer` | — | First layer in the requested through-thickness range. |
| 6 | `lastLayer` | `integer` | — | Last layer in the requested through-thickness range. |
| 7 | `stress1` | `real` | 0.0 | Stress 1 (force per area). |
| 8 | `stress2` | `real` | 0.0 | Stress 2 (force per area). |
| 9 | `stress3` | `real` | 0.0 | Stress 3 (force per area). |
| 10 | `stress4` | `real` | 0.0 | Stress 4 (force per area). |
| 11 | `stress5` | `real` | 0.0 | Stress 5 (force per area). |
| 12 | `stress6` | `real` | 0.0 | Stress 6 (force per area). |
| 13 | `stress7` | `real` | 0.0 | Stress 7 (force per area). |
| 14 | `coordinate` | `text` | — | Coordinate of the specified point in the selected frame. |
| 15 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |

Accepted words: `Constant`, `Coordinates`, `Element`, `Table`.

**Example record**

~~~text
InitialStress;101;102;1;8;;;20.;0.;0.;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solids_initial_state.oos)

Reading the example gives `firstElemId = 101`, `lastElemId = 102`, `firstPoint = 1`, `lastPoint = 8`.

## IterativeSolverOptions

Iterative solver options.

**Record format and fields**

`IterativeSolverOptions;id;<options>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `options`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `option` | `text` | — | Selects how the current entry or group is interpreted. |

Accepted words: `BlockIncompleteCholesky`, `BlockIncompleteCholeskyComplex`, `CacheAwareIncomplete`, `Constant`, `Element`, `EnergyNormCriterion`, `EnergyNormCriterionExtended`, `IncompleteCholesky`, `IncompleteCholeskyScaled`, `Jacobi`, `JacobiScaled`, `No`, `ResidualRatioCriterion`, `ResidualRatioCriterionExtended`, `RowIncompleteCholesky`, `RowIncompleteCholeskySymmetric`, `Table`, `User`, `Yes`.

Accepted parameter names: `ConvergenceCriteria`, `EstimateResourcesOnly`, `IterationMessages`, `IterationTolerance`, `MaxIterationSteps`, `PreconditionerExtractionLevel`, `PreconditionerKind`, `PreconditionerPadding`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `options` — an option name is a letter followed by letters, digits and underscores (at most 16).

**Example record**

~~~text
IterativeSolverOptions;50;PreconditionerKind=BlockIncompleteCholesky;IterationTolerance=1.0E-8;IterationMessages=Yes
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol101_connector_iterative.oos)

Reading the example gives `id = 50`.

## ModeTracking

The mode tracking of a design optimization.

**Record format and fields**

`ModeTracking;id;lowRange;highRange;trackingFilter`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `lowRange` | `integer` | 0 | The lowest mode number of the search range. |
| 3 | `highRange` | `integer` | 0 | Upper end of the range admitted to the evaluation. |
| 4 | `trackingFilter` | `real` | 0.9 | The filtering parameter of the cross orthogonality check. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.

**Example record**

~~~text
ModeTracking;100;1;6;0.8
~~~

[Model containing this record](../../../validation/models/dynamics/design_modtrak_sol200.oos)

Reading the example gives `id = 100`, `lowRange = 1`, `highRange = 6`, `trackingFilter = 0.8`.

## ModelParams

Parameters that affect the solution of the structural model.

**Record format and fields**

`ModelParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `ElemOffsetZ`, `ElemOffsetsOnly`, `HarderShearPanel`, `LoadRecoveryOffsets`, `NoDampingOffsets`, `NoMassOffsets`, `NoOffsetDifference`, `NoTemperatureGradientOffsets`, `NoThermalOffsets`.

Accepted parameter names: `BeamLibraryShearFactor`, `OffsetDefinition`, `OffsetDisplacementLoad`, `ShearPanelFormulation`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterNames` — the card needs at least one parameter and its value.

**Example record**

~~~text
ModelParams;HDF5;1
~~~

[Model containing this record](../../../validation/models/hdf5_layouts/hdf5_default_settings.oos)

## ModuleResultFileParams

Records module-specific output settings that extend the model-level [ResultFileParams](solution_control.md#resultfileparams) definition.

**Record format and fields**

`ModuleResultFileParams;moduleId;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | Required | Identifier selecting the module record or set. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BloscCompression`, `CompressionLevel`, `CompressionMethod`, `GzipCompression`, `InputData`, `LoadConstraintTables`, `Lz4Compression`, `MatrixData`, `ModalMatrixOutput`, `No`, `NodeElementTables`, `None`, `Precision`, `RotationalDofs`, `RunInformation`, `SeparateModelFile`, `Yes`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterNames` — the card needs at least one parameter and its value.

**Example record**

~~~text
ModuleResultFileParams;0;LoadConstraintTables;1
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_echo_metadata_hdf5.oos)

Reading the example gives `moduleId = 0`.

## NonlinearHarmonicSolverParams

Values for the parameters of the nonlinear frequency response analysis.

**Record format and fields**

`NonlinearHarmonicSolverParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Both`, `Constant`, `Element`, `Full`, `LdlDecomposition`, `LowerUpperDecomposition`, `No`, `Off`, `On`, `QrDecomposition`, `Table`, `Yes`.

Accepted parameter names: `ContinuationMethod`, `DecompositionMethod`, `ExtraSamplingPoints`, `InitialConditionOutput`, `LineSearchStepFactor`, `MaxFrequencyInterval`, `MaxNonConvergedFrequencies`, `MaxNonConvergedSteps`, `NonlinearHarmonicDiagnostic`, `NonlinearHarmonicReduction`, `NonlinearHarmonicTolerance`, `StepHalvingIterations`.

**Example record**

~~~text
NonlinearHarmonicSolverParams;ContinuationMethod;2;DecompositionMethod;QrDecomposition;StepHalvingIterations;8
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

## NonlinearStaticParams

The iteration strategy of a nonlinear static analysis.

**Record format and fields**

`NonlinearStaticParams;id;incrementCount;timeStep;stiffnessMethod;stiffnessUpdateStep;maxIterations;convergenceFlags;intermediateOutput;epsilonU;epsilonP;epsilonW;maxDivergences;maxQuasiNewtonVectors;maxLineSearches;stressSubincrementFraction;lineSearchTolerance;maxBisections;maxRotationRatio;rotationTolerance;minIterations`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `incrementCount` | `integer` | — | Number of increment entries. |
| 3 | `timeStep` | `real` | 0.0 | Time increment between successive states, in model time units. |
| 4 | `stiffnessMethod` | `text` | — | Selects the stiffness method for NonlinearStaticParams. |
| 5 | `stiffnessUpdateStep` | `integer` | — | Step interval or stage at which the tangent stiffness is updated. |
| 6 | `maxIterations` | `integer` | 25 | Maximum number of iterations permitted at this stage. |
| 7 | `convergenceFlags` | `text` | — | Selects the residual, displacement, work or other convergence checks to apply. |
| 8 | `intermediateOutput` | `text` | No | Controls output at intermediate increments or stations. |
| 9 | `epsilonU` | `real` | — | Tolerance on the displacement increment in the nonlinear convergence test. |
| 10 | `epsilonP` | `real` | — | Tolerance on the load or force residual in the nonlinear convergence test. |
| 11 | `epsilonW` | `real` | — | Tolerance on incremental work in the nonlinear convergence test. |
| 12 | `maxDivergences` | `integer` | 3 | Number of divergence events allowed before changing or rejecting the step. |
| 13 | `maxQuasiNewtonVectors` | `integer` | — | Limit on the vectors retained in a quasi-Newton update. |
| 14 | `maxLineSearches` | `integer` | — | Maximum line-search updates in an iteration. |
| 15 | `stressSubincrementFraction` | `real` | 0.2 | Fraction of the stress change allowed within a subincrement. |
| 16 | `lineSearchTolerance` | `real` | 0.5 | Permitted numerical deviation for line search. |
| 17 | `maxBisections` | `integer` | — | Maximum permitted subdivisions of an increment by bisection. |
| 18 | `maxRotationRatio` | `real` | 20.0 | Relative measure of maximum rotation. |
| 19 | `rotationTolerance` | `real` | 20.0 | Permitted numerical deviation for rotation. |
| 20 | `minIterations` | `integer` | — | Minimum number of iterations before the convergence decision. |

Accepted words: `All`, `Automatic`, `FullNewtonTangent`, `Iterative`, `No`, `PseudoFullNewtonTangent`, `Semi`, `Yes`.

**Example record**

~~~text
NonlinearStaticParams;30;5;;Automatic;;25;PW;No
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_beam_segment_contact.oos)

Reading the example gives `id = 30`, `incrementCount = 5`, `stiffnessMethod = Automatic`, `maxIterations = 25`.

## NonlinearTimeSteps

The controls of a nonlinear transient analysis.

**Record format and fields**

`NonlinearTimeSteps;id;stepCount;timeStep;outputInterval;method;stiffnessUpdateStep;maxIterations;convergenceFlags;epsilonU;epsilonP;epsilonW;maxDivergences;maxQuasiNewtonVectors;maxLineSearches;stressSubincrementFraction;maxBisections;adjustInterval;minStepsPerCycle;stepBounds;maxRotationRatio;displacementTolerance;rotationTolerance;minIterations`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stepCount` | `integer` | Required | Number of step entries. |
| 3 | `timeStep` | `real` | Required | Time increment between successive states, in model time units. |
| 4 | `outputInterval` | `integer` | 1 | Spacing between successive output requests. |
| 5 | `method` | `text` | — | Selects the method for NonlinearTimeSteps. |
| 6 | `stiffnessUpdateStep` | `integer` | — | Step interval or stage at which the tangent stiffness is updated. |
| 7 | `maxIterations` | `integer` | — | Maximum number of iterations permitted at this stage. |
| 8 | `convergenceFlags` | `text` | — | Selects the residual, displacement, work or other convergence checks to apply. |
| 9 | `epsilonU` | `real` | — | Tolerance on the displacement increment in the nonlinear convergence test. |
| 10 | `epsilonP` | `real` | — | Tolerance on the load or force residual in the nonlinear convergence test. |
| 11 | `epsilonW` | `real` | — | Tolerance on incremental work in the nonlinear convergence test. |
| 12 | `maxDivergences` | `integer` | 2 | Number of divergence events allowed before changing or rejecting the step. |
| 13 | `maxQuasiNewtonVectors` | `integer` | — | Limit on the vectors retained in a quasi-Newton update. |
| 14 | `maxLineSearches` | `integer` | — | Maximum line-search updates in an iteration. |
| 15 | `stressSubincrementFraction` | `real` | 0.2 | Fraction of the stress change allowed within a subincrement. |
| 16 | `maxBisections` | `integer` | — | Maximum permitted subdivisions of an increment by bisection. |
| 17 | `adjustInterval` | `integer` | 5 | Interval between checks at which the time-step controller may adjust the increment. |
| 18 | `minStepsPerCycle` | `integer` | — | Minimum number of increments used to resolve one oscillation cycle. |
| 19 | `stepBounds` | `real` | 0.6 | Limits imposed on the size of the step. |
| 20 | `maxRotationRatio` | `real` | 32.0 | Relative measure of maximum rotation. |
| 21 | `displacementTolerance` | `real` | 0.1 | Permitted numerical deviation for displacement. |
| 22 | `rotationTolerance` | `real` | 20.0 | Permitted numerical deviation for rotation. |
| 23 | `minIterations` | `integer` | — | Minimum number of iterations before the convergence decision. |

Accepted words: `Adaptive`, `Automatic`, `FullNewtonTangent`, `Iterative`, `PseudoFullNewtonTangent`, `Semi`.

**Example record**

~~~text
NonlinearTimeSteps;61;10;0.01;1;Adaptive;2;10;PW;0.01;0.001;1.E-6;2;10;2;0.02;5;5;;0.75;16.;0.1;20.
~~~

[Model containing this record](../../../validation/models/hdf5_layouts/hdf5_input_eigc_tstepnl.oos)

Reading the example gives `id = 61`, `stepCount = 10`, `timeStep = 0.01`, `outputInterval = 1`.

## ReferenceRotor

The reference rotor of the non-reference rotors of the residual structure, for a complex eigenvalue analysis.

**Record format and fields**

`ReferenceRotor;id;referenceRotorId;<nonFollowingRotors>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `referenceRotorId` | `integer` | Required | Identifier selecting the reference rotor record or set. |

**Repeated group `nonFollowingRotors`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nonFollowingRotorId` | `any` | — | Identifier selecting the non following rotor record or set. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nonFollowingRotorIds` — the card needs at least one non-reference rotor.

**Example record**

~~~text
ReferenceRotor;100;10;20
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_campbell_sol107.oos)

Reading the example gives `id = 100`, `referenceRotorId = 10`.

## ResidualVectorDofs

Degrees of freedom where unit loads are applied to get the static solutions that the residual vector computation uses.

**Record format and fields**

`ResidualVectorDofs;<dofs>`

This part of the record has no fixed fields.

**Repeated group `dofs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
ResidualVectorDofs;15;3;5;3
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

## ResidualVectorDofs1

The degrees of freedom C of a list of points where unit loads are applied to get the static solutions that the residual vector computation uses.

**Record format and fields**

`ResidualVectorDofs1;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `Through`.

**Example record**

~~~text
ResidualVectorDofs1;12;5;10;15
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `components = 12`.

## ResultFileModules

Selects separate or appended results files for individual model modules.

**Record format and fields**

`ResultFileModules;id;configuration;<modules>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `configuration` | `integer` | 0 | Selects the model configuration used by this calculation. |

**Repeated group `modules`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `moduleId` | `integer` | — | Identifier selecting the module record or set. |
| 2 | `userNameId` | `integer` | — | Identifier selecting the user name record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
ResultFileModules;17;0;0;100;1;101
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_echo_metadata_hdf5.oos)

Reading the example gives `id = 17`, `configuration = 0`.

## ResultFileParams

Stores named results-file settings such as precision, compression and output selection.

**Record format and fields**

Forms: `numbered`, `plain`.

### ResultFileParams: numbered

Form `numbered`, when `number` is an integer.

`ResultFileParams;number;<parameters>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `number` | `integer` | — | Identification number for the selected entry or output stream. |

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

### ResultFileParams: plain

Form `plain`, for every other record.

`ResultFileParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `BloscCompression`, `CompressionLevel`, `CompressionMethod`, `Constant`, `Element`, `GzipCompression`, `InputData`, `LoadConstraintTables`, `Lz4Compression`, `MatrixData`, `ModalMatrixOutput`, `No`, `NodeElementTables`, `None`, `Precision`, `RotationalDofs`, `RunInformation`, `SeparateModelFile`, `Table`, `Yes`.

Accepted parameter names: `CompressionLevel`, `CompressionMethod`, `InputData`, `LoadConstraintTables`, `MatrixData`, `ModalMatrixOutput`, `NodeElementTables`, `Precision`, `RotationalDofs`, `RunInformation`, `SeparateModelFile`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterName` — the number before the parameters must not be negative.
- `parameterName` — the card needs at least one parameter and its value.

**Example record**

~~~text
ResultFileParams;Precision;64;CompressionMethod;GzipCompression
~~~

[Model containing this record](../../../validation/models/aero_sol144/sol144_trim_monitor.oos)

## ResultMetadata

Attaches user-supplied descriptive metadata to analysis results.

**Record format and fields**

`ResultMetadata;metadataName;<metadataLines>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataName` | `text` | — | Text naming the metadata. Written as one text field. |

**Repeated group `metadataLines`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `metadataInfo` | `text` | — | Descriptive information carried with the result metadata. Written as one text field. |

**Example record**

~~~text
ResultMetadata;plate_metadata;O_o_Model test model of the solution control cards;units mm N t s and an aluminium plate 2 mm thick
~~~

[Model containing this record](../../../validation/models/solution_control/sol101_echo_metadata_hdf5.oos)

Reading the example gives `metadataName = plate_metadata`.

## RotorAxisym

The elements, the properties or the grid points that make an axisymmetric rotor.

**Record format and fields**

`RotorAxisym;id;listType;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `listType` | `text` | — | Selects the list type for RotorAxisym. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `any` | — | Identifier of the grid point addressed by this record. |

Accepted words: `By`, `Constant`, `Element`, `Elements`, `Node`, `Property`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeIds` — the card needs at least one ID.

**Example record**

~~~text
RotorAxisym;30;Node;5001;5002;5003;5004
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_axisymmetric_sol107.oos)

Reading the example gives `id = 30`, `listType = Node`.

## RotorInitialBend

The initial deformation of a rotor, made of kinks and offsets, which the rotor takes on before it is pulled onto its bearing and analysed.

**Record format and fields**

`RotorInitialBend;bendTableId;rotorId;loadId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bendTableId` | `integer` | Required | Table supplying the variation of bend. |
| 2 | `rotorId` | `integer` | Required | Identifier selecting the rotor record or set. |
| 3 | `loadId` | `integer` | Required | Identifier selecting the load record or set. |

**Keyed sections in `rows`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `UnbalanceFrame`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coordinate1` | `real` | — | Coordinate of the specified point in the selected frame. Entry 1. |
| 2 | `coordinate2` | `real` | — | Coordinate of the specified point in the selected frame. Entry 2. |
| 3 | `coordinate3` | `real` | — | Coordinate of the specified point in the selected frame. Entry 3. |

**Section `KinkDeformation`**

**Repeated group `kinks`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `station` | `real` | — | Position along the member or sampled path. |
| 2 | `angle` | `real` | — | Angular position or orientation relative to the reference on this card. |
| 3 | `phase` | `real` | — | Phase of the harmonic quantity relative to the reference oscillation. |

**Section `Offset`**

**Repeated group `offsets`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `station` | `real` | — | Position along the member or sampled path. |
| 2 | `offset` | `real` | — | Shift from the reference location or value in the convention of this entry. |
| 3 | `phase` | `real` | — | Phase of the harmonic quantity relative to the reference oscillation. |

**Section `BearingDeflectionProfile`**

**Repeated group `bearings`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `rotorNode` | `integer` | — | Grid point belonging to the rotating side. |
| 2 | `statorNode` | `integer` | — | Grid point belonging to the stationary side. |

Accepted words: `BearingDeflectionProfile`, `Constant`, `Element`, `KinkDeformation`, `Offset`, `Table`, `UnbalanceFrame`.

**Example record**

~~~text
RotorInitialBend;700;10;99;UnbalanceFrame;0.;1.;0.;KinkDeformation;1;200.;0.05;0.;BearingDeflectionProfile;2;1001;3001;1005;3005
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_bent_sol400.oos)

Reading the example gives `bendTableId = 700`, `rotorId = 10`, `loadId = 99`.

## RotorLineNodes

The grids that make the line model of a rotor.

**Record format and fields**

`RotorLineNodes;id;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `any` | — | Identifier of the grid point addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the rotor ID must be a positive integer.
- `nodeIds` — the card needs at least one grid.
- `nodeIds` — the grids must be positive integers.
- `increment` — a single grid has no increment.

**Example record**

~~~text
RotorLineNodes;1;101;Through;105
~~~

[Model containing this record](../../../validation/models/linear_elements/rotor_bush2d_freq.oos)

Reading the example gives `id = 1`.

## RotorModel3D

The 3D model of a rotor, as the elements or the properties that make it and the grid points of its axis of rotation.

**Record format and fields**

`RotorModel3D;id;frame;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frame` | `text` | FixedEnd | Specifies the coordinate frame in which values are resolved. |

**Keyed sections in `lists`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Elements`**

**Repeated group `elements`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

**Section `Property`**

**Repeated group `properties`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `any` | — | Identifier of the property from which the element obtains its section or constitutive data. |

**Section `Axis`**

**Repeated group `axisNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `axisNode` | `integer` | — | Grid point used to define the axis of the specified rotor or rotation. |

Accepted words: `Axis`, `By`, `Constant`, `Element`, `Elements`, `FixedEnd`, `Property`, `Rotation`, `Table`, `Through`.

**Example record**

~~~text
RotorModel3D;10;FixedEnd;Elements;5;1001;1002;1003;1004;1010;Axis;5;1001;1002;1003;1004;1005
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_bent_sol400.oos)

Reading the example gives `id = 10`, `frame = FixedEnd`.

## RotorRelativeSpin

The spin rate of a rotor relative to the others, for a complex eigenvalue, a frequency response or a static analysis, and the damping of the rotor.

**Record format and fields**

`RotorRelativeSpin;rotorId;nodeA;nodeB;speedUnit;spinTableId;spinRate;rotorSuperelementId;node;massDampingFactor;stiffnessDampingFactor;viscousDampingFrequency;structuralDampingFrequency;hybridDampingFrequency`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `rotorId` | `integer` | Required | Identifier selecting the rotor record or set. |
| 2 | `nodeA` | `integer` | Required | Grid point identifier at connectivity position A. |
| 3 | `nodeB` | `integer` | Required | Grid point identifier at connectivity position B. |
| 4 | `speedUnit` | `text` | — | Unit used to express the specified speed. |
| 5 | `spinTableId` | `integer` | — | Table supplying the variation of spin. Alternative to `spinRate`. |
| 6 | `spinRate` | `real` | — | Angular speed of the rotating component. Alternative to `spinTableId`. |
| 7 | `rotorSuperelementId` | `integer` | 0 | Identifier selecting the rotor superelement record or set. |
| 8 | `node` | `real` | 0.0 | Grid point to which this entry applies. |
| 9 | `massDampingFactor` | `real` | 0.0 | Multiplier for mass damping. |
| 10 | `stiffnessDampingFactor` | `real` | 0.0 | Multiplier for stiffness damping. |
| 11 | `viscousDampingFrequency` | `real` | 0.0 | Viscous damping frequency (inverse time). |
| 12 | `structuralDampingFrequency` | `real` | 0.0 | Structural damping frequency (inverse time). |
| 13 | `hybridDampingFrequency` | `real` | 0.0 | Hybrid damping frequency (inverse time). |

Accepted words: `Constant`, `DesignDiscreteValues`, `Element`, `Frequency`, `RevolutionsPerMinute`, `Table`.

**Example record**

~~~text
RotorRelativeSpin;10;1001;1005;RevolutionsPerMinute;;1.;1
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_superelement_sol110.oos)

Reading the example gives `rotorId = 10`, `nodeA = 1001`, `nodeB = 1005`, `speedUnit = RevolutionsPerMinute`.

## RotorSuperelement

The rotor line model of a rotor that is placed in a superelement (the alternative to a [RotorLineNodes](solution_control.md#rotorlinenodes) when superelements are used).

**Record format and fields**

`RotorSuperelement;id;superelementId;superelementOption`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 3 | `superelementOption` | `integer` | 1 | Selects the superelement option for RotorSuperelement. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
RotorSuperelement;10;1;2
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_superelement_sol110.oos)

Reading the example gives `id = 10`, `superelementId = 1`, `superelementOption = 2`.

## RotorTransientSpin

The spin rate of a rotor in a transient analysis, and the damping of the rotor.

**Record format and fields**

`RotorTransientSpin;rotorId;nodeA;nodeB;speedUnit;spinTableId;speedOutput;rotorSuperelementId;node;massDampingFactor;stiffnessDampingFactor;viscousDampingFrequency;structuralDampingFrequency;hybridDampingFrequency`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `rotorId` | `integer` | Required | Identifier selecting the rotor record or set. |
| 2 | `nodeA` | `integer` | Required | Grid point identifier at connectivity position A. |
| 3 | `nodeB` | `integer` | Required | Grid point identifier at connectivity position B. |
| 4 | `speedUnit` | `text` | — | Unit used to express the specified speed. |
| 5 | `spinTableId` | `integer` | Required | Table supplying the variation of spin. |
| 6 | `speedOutput` | `integer` | 0 | Selects output of rotational speed data. |
| 7 | `rotorSuperelementId` | `integer` | 0 | Identifier selecting the rotor superelement record or set. |
| 8 | `node` | `real` | 0.0 | Grid point to which this entry applies. |
| 9 | `massDampingFactor` | `real` | 0.0 | Multiplier for mass damping. |
| 10 | `stiffnessDampingFactor` | `real` | 0.0 | Multiplier for stiffness damping. |
| 11 | `viscousDampingFrequency` | `real` | 0.0 | Viscous damping frequency (inverse time). |
| 12 | `structuralDampingFrequency` | `real` | 0.0 | Structural damping frequency (inverse time). |
| 13 | `hybridDampingFrequency` | `real` | 0.0 | Hybrid damping frequency (inverse time). |

Accepted words: `Constant`, `Element`, `Frequency`, `RevolutionsPerMinute`, `Table`.

**Example record**

~~~text
RotorTransientSpin;10;1001;1005;RevolutionsPerMinute;401;4001
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_transient_sol109.oos)

Reading the example gives `rotorId = 10`, `nodeA = 1001`, `nodeB = 1005`, `speedUnit = RevolutionsPerMinute`.

## RotordynamicParams

The parameters of a rotordynamic analysis.

**Record format and fields**

`RotordynamicParams;id;synchronous;referenceRotorId;speedUnit;speedLow;speedHigh;speed;rotorSuperelementId;viscousDampingFrequency;structuralDampingFrequency;hybridDampingFrequency`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `synchronous` | `text` | — | Selects operation synchronized to the reference rotational frequency. |
| 3 | `referenceRotorId` | `integer` | Required | Identifier selecting the reference rotor record or set. |
| 4 | `speedUnit` | `text` | — | Unit used to express the specified speed. |
| 5 | `speedLow` | `real` | 0.0 | Minimum rotational speed in the selected range. |
| 6 | `speedHigh` | `real` | 99999.0 | Maximum rotational speed in the selected range. |
| 7 | `speed` | `real` | 0.0 | Speed (length per time). |
| 8 | `rotorSuperelementId` | `integer` | 0 | Identifier selecting the rotor superelement record or set. |
| 9 | `viscousDampingFrequency` | `real` | 0.0 | Viscous damping frequency (inverse time). |
| 10 | `structuralDampingFrequency` | `real` | 0.0 | Structural damping frequency (inverse time). |
| 11 | `hybridDampingFrequency` | `real` | 0.0 | Hybrid damping frequency (inverse time). |

Accepted words: `AsynchronousWhirl`, `Constant`, `Element`, `Frequency`, `RevolutionsPerMinute`, `SynchronousWhirl`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.
- `speedLow` — the speeds must be finite numbers.
- `viscousDampingFrequency` — the whirl frequencies must be finite numbers.

**Example record**

~~~text
RotordynamicParams;500;AsynchronousWhirl;20;RevolutionsPerMinute;;;3.E+3;0
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_superelement_sol110.oos)

Reading the example gives `id = 500`, `synchronous = AsynchronousWhirl`, `referenceRotorId = 20`, `speedUnit = RevolutionsPerMinute`.

## StochasticParams

The statistics used to randomize selected model parameters.

**Record format and fields**

`StochasticParams;id;<randomGroups>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `randomGroups`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `flag` | `text` | — | Selects the option associated with this field in the current record or block. |
| 2 | `distribution` | `text` | — | Selects the distribution used for the input data or response. |
| 3 | `variationCoefficient` | `real` | — | Coefficient in the relation for variation. |
| 4 | `standardDeviations` | `real` | — | M: the number of standard deviations, greater than 0. |

Accepted words: `ConnectivityEntries`, `Constant`, `Element`, `EnforcedMotionConstr`, `Gauss`, `LoadEntries`, `MaterialEntries`, `PropertyEntries`, `Table`.

**Example record**

~~~text
StochasticParams;10;PropertyEntries;Gauss;0.05;3.;MaterialEntries;Gauss;0.03;2.
~~~

[Model containing this record](../../../validation/models/solution_control/sol103_stochastic_parameters.oos)

Reading the example gives `id = 10`.

## SuperelementReferenceRotor

The reference rotor of the non-reference rotors of any superelement, for a complex eigenvalue analysis.

**Record format and fields**

`SuperelementReferenceRotor;id;referenceRotorId;referenceSuperelementId;<rotors>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `referenceRotorId` | `integer` | Required | Identifier selecting the reference rotor record or set. |
| 3 | `referenceSuperelementId` | `integer` | 0 | Identifier selecting the reference superelement record or set. |

**Repeated group `rotors`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nonFollowingRotorId` | `integer` | — | Identifier selecting the non following rotor record or set. |
| 2 | `nonFollowingSuperelementId` | `integer` | — | Identifier selecting the non following superelement record or set. |

Accepted words: `Constant`, `Element`, `Frequency`, `RevolutionsPerMinute`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nonFollowingRotorIds` — the card needs at least one non-reference rotor.

**Example record**

~~~text
SuperelementReferenceRotor;500;20;0;10;1
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_superelement_sol110.oos)

Reading the example gives `id = 500`, `referenceRotorId = 20`, `referenceSuperelementId = 0`.

## TimeToSpectrum

The conversion of time histories to power spectral densities, the Fast Fourier Transformation that a random vibration fatigue analysis uses when its loads are given as time signals.

**Record format and fields**

`TimeToSpectrum;id;samplingRate;window;fileFormat;meanStress;skipCount;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `samplingRate` | `real` | Required | Samples per second. |
| 3 | `window` | `text` | HanningWindow | Selects the window applied to the sampled signal. |
| 4 | `fileFormat` | `text` | CommaSeparatedFile | Encoding of the external file identified by this entry. |
| 5 | `meanStress` | `text` | No | Average stress about which the alternating stress varies. |
| 6 | `skipCount` | `integer` | 0 | Number of skip entries. |

**Keyed sections in `sections`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Event`**

**Repeated group `events`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `eventId` | `integer` | — | Identifier selecting the event record or set. |
| 2 | `sliceTime` | `real` | — | Slice time (time). |
| 3 | `sliceDuration` | `real` | — | Length of the time window used for one slice of the signal. |

**Section `Delete`**

**Repeated group `deletions`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `eventId` | `integer` | — | Identifier selecting the event record or set. |
| 2 | `sliceStart1` | `real` | — | Start of time slice 1 in the evaluation history. |
| 3 | `sliceEnd1` | `real` | — | End of time slice 1 in the evaluation history. |
| 4 | `sliceStart2` | `real` | — | Start of time slice 2 in the evaluation history. |
| 5 | `sliceEnd2` | `real` | — | End of time slice 2 in the evaluation history. |
| 6 | `sliceStart3` | `real` | — | Start of time slice 3 in the evaluation history. |
| 7 | `sliceEnd3` | `real` | — | End of time slice 3 in the evaluation history. |

**Section `Map`**

**Repeated group `channels`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `loadCaseId` | `integer` | — | Identifier selecting the load case record or set. |
| 2 | `channel` | `integer` | — | Channel of the external data file supplying the sampled history. |

Accepted words: `CommaSeparatedFile`, `Constant`, `Delete`, `Element`, `Event`, `HanningWindow`, `LoadHistoryFile`, `Map`, `No`, `None`, `Table`, `Yes`.

**Example record**

~~~text
TimeToSpectrum;10;256.;HanningWindow;CommaSeparatedFile;No;0;Event;1;13;1.;0.5;Map;1;1;1
~~~

[Model containing this record](../../../validation/models/dynamics/fatigue_tim2psd_sol111.oos)

Reading the example gives `id = 10`, `samplingRate = 256.`, `window = HanningWindow`, `fileFormat = CommaSeparatedFile`.

## TireSelection

The selection of the external tire models that take part in a simulation.

**Record format and fields**

`TireSelection;id;tireFileKeyword;<tires>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `tireFileKeyword` | `text` | — | Keyword selecting the associated tire data in the external file. |

**Repeated group `tires`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `tireName` | `text` | — | Text naming the tire. |

Accepted words: `Constant`, `Element`, `ExternalTireModel`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `tireNames` — the card needs the name of at least one tire.

**Example record**

~~~text
TireSelection;100;ExternalTireModel;WHEELFL;WHEELFR;WHEELRL;WHEELRR
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol103_tire_selection.oos)

Reading the example gives `id = 100`, `tireFileKeyword = ExternalTireModel`.

## TransferPathSetup

The set-up of a transfer path analysis (TPA).

**Record format and fields**

`TransferPathSetup;id;nodeSetId;unit;<responses>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `nodeSetId` | `integer` | — | Identifier of the set supplying the grid points. |
| 3 | `unit` | `integer` | 24 | Logical unit or measurement convention as defined by the record. |

**Repeated group `responses`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `responseKind` | `text` | — | Selects the response kind for responses. |
| 2 | `outputSet` | `integer` | — | A TypedListSet3 of the response grid points, required. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TransferPathSetup;100;1001;;A;2002
~~~

[Model containing this record](../../../validation/models/solution_control/sol111_transfer_path_definition.oos)

Reading the example gives `id = 100`, `nodeSetId = 1001`.

## TransientTimeSteps

The time steps of a linear transient analysis.

**Record format and fields**

`TransientTimeSteps;id;<intervals>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `intervals`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stepCount` | `integer` | — | Number of step entries. |
| 2 | `timeStep` | `real` | — | Time increment between successive states, in model time units. |
| 3 | `outputInterval` | `integer` | — | Spacing between successive output requests. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the ID must be a positive integer.
- `stepCounts` — Ni must be a positive integer.

**Example record**

~~~text
TransientTimeSteps;61;50;1.E-4;5
~~~

[Model containing this record](../../../validation/models/results_dynamics/acoustic_fluid_transient_sort2.oos)

Reading the example gives `id = 61`.

## UserFileName

Associates a file path with an identifier that other records use to locate external data.

**Record format and fields**

In the source layout, the form is called `nameOnFirstLine` when field 2 of the old layout is filled. Its compact field sequence is the one shown below.

Forms: `nameOnSecondLine`.

### UserFileName: nameOnSecondLine

Form `nameOnSecondLine`, for every compact record.

`UserFileName;id;entryName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryName` | `text` | — | File name or path associated with this file identifier. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
UserFileName;1;road-loads.rsp
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol112_channel_file_loads.oos)

## WettedElemNodes

A wetted element of an external fluid-structure simulation, given by its shape and its grid points.

**Record format and fields**

`WettedElemNodes;id;kind;node1;node2;node3;node4;node5;node6;node7;node8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for WettedElemNodes. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |

Accepted words: `Constant`, `Element`, `Line2Nodes`, `Line3Nodes`, `Quad4Shape`, `Quad8Shape`, `Table`, `Tria3Shape`, `Tria6Shape`.

**Example record**

~~~text
WettedElemNodes;103;Quad4Shape;4;5;8;7
~~~

[Model containing this record](../../../validation/models/read_only_thermal_acoustic/fsi_wetted_surface_sol400.oos)

Reading the example gives `id = 103`, `kind = Quad4Shape`, `node1 = 4`, `node2 = 5`.

## WettedElemSide

A wetted element of an external fluid-structure simulation, given as a side of a structural element.

**Record format and fields**

`WettedElemSide;id;elemId;sideCode`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `sideCode` | `integer` | Required | Selects one side of the join, element or interface in the record’s local ordering. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
WettedElemSide;101;1;1
~~~

[Model containing this record](../../../validation/models/read_only_thermal_acoustic/fsi_wetted_surface_sol400.oos)

Reading the example gives `id = 101`, `elemId = 1`, `sideCode = 1`.

## WettedSurface

A wetted surface of a fluid-structure co-simulation, a list of wetted elements.

**Record format and fields**

`WettedSurface;id;wettedTag;<wettedElems>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `wettedTag` | `text` | — | Tag identifying the surface exposed to the coupled fluid. |

**Repeated group `wettedElems`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `wettedElemId` | `any` | — | Identifier selecting the wetted element record or set. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
WettedSurface;1;plate;101;Through;104
~~~

[Model containing this record](../../../validation/models/read_only_thermal_acoustic/fsi_wetted_surface_sol400.oos)

Reading the example gives `id = 1`, `wettedTag = plate`.
