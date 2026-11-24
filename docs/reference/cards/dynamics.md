# Dynamics

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AcousticSourceLoad

An acoustic source given as power against frequency.

**Record format and fields**

`AcousticSourceLoad;id;excitationId;delayId;delay;phaseId;phase;powerTableId;power;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier addressing excitation set data. |
| 3 | `delayId` | `integer` | — | Identifier selecting the delay record or set. Alternative to `delay`. |
| 4 | `delay` | `real` | 0.0 | Time shift relative to the reference excitation, in model time units. Alternative to `delayId`. |
| 5 | `phaseId` | `integer` | — | Identifier selecting the phase record or set. Alternative to `phase`. |
| 6 | `phase` | `real` | 0.0 | Phase of the harmonic quantity relative to the reference oscillation. Alternative to `phaseId`. |
| 7 | `powerTableId` | `integer` | — | Table supplying the variation of power. Alternative to `power`. |
| 8 | `power` | `real` | — | Exponent applied to the dependent relation. Alternative to `powerTableId`. |
| 9 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 10 | `bulkModulus` | `real` | Required | Resistance to volumetric compression, expressed as pressure. |

Accepted words: `Acceleration`, `Displacement`, `Load`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the dynamic load set ID must be a positive integer.

**Example record**

~~~text
AcousticSourceLoad;30;31;;2.E-4;;10.;34;;1.2E-12;0.142
~~~

[Model containing this record](../../../validation/models/dynamics/freq_acoustic_source.oos)

Reading the example gives `id = 30`, `excitationId = 31`, `delay = 2.E-4`, `phase = 10.`.

## BucklingEigenMethod

Specifies the extraction data for a buckling eigenvalue problem.

**Record format and fields**

`BucklingEigenMethod;id;method;lowerEigenvalue;upperEigenvalue;estimatedModeCount;desiredPositiveModeCount;desiredNegativeModeCount;norm;normNode;normComponent`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the method namespace. |
| 2 | `method` | `text` | — | Selects the method for BucklingEigenMethod. |
| 3 | `lowerEigenvalue` | `real` | Required | Lower bound of the eigenvalue interval to search. |
| 4 | `upperEigenvalue` | `real` | Required | Upper bound of the eigenvalue interval to search. |
| 5 | `estimatedModeCount` | `integer` | 0 | Number of estimated mode entries. |
| 6 | `desiredPositiveModeCount` | `integer` | — | Number of desired positive mode entries. |
| 7 | `desiredNegativeModeCount` | `integer` | — | Number of desired negative mode entries. |
| 8 | `norm` | `text` | — | Norm used for scaling a mode shape. |
| 9 | `normNode` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 10 | `normComponent` | `integer` | 0 | Degree of freedom used as the normalization reference. |

Accepted words: `InverseIteration`, `Maximum`, `Point`, `SturmInverse`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the method ID must be a positive integer.

**Example record**

~~~text
BucklingEigenMethod;30;SturmInverse;0.;50.;;2;;Maximum
~~~

[Model containing this record](../../../validation/models/dynamics/buckling_eigb_sol105.oos)

Reading the example gives `id = 30`, `method = SturmInverse`, `lowerEigenvalue = 0.`, `upperEigenvalue = 50.`.

## ComplexEigenMethod

The data of a complex eigenvalue extraction.

**Record format and fields**

`ComplexEigenMethod;id;methodName;norm;normNode;normComponent;convergenceTolerance;desiredModeCount0;<regions>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `methodName` | `text` | — | Text naming the method. |
| 3 | `norm` | `text` | Maximum | Norm used for scaling a mode shape. |
| 4 | `normNode` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 5 | `normComponent` | `integer` | 0 | Degree of freedom used as the normalization reference. |
| 6 | `convergenceTolerance` | `real` | — | Permitted numerical deviation for convergence. |
| 7 | `desiredModeCount0` | `integer` | 0 | Number of desired mode entries. |

**Repeated group `regions`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `alphaA` | `real` | — | The real part of the region's first end point, or of the shift point. |
| 2 | `omegaA` | `real` | — | The imaginary part. |
| 3 | `alphaB` | `real` | — | The second end point (region form). |
| 4 | `omegaB` | `real` | — | Angular-frequency term associated with the second frequency parameter of the relation. |
| 5 | `regionWidth` | `real` | — | Region width (length). |
| 6 | `estimatedModeCount` | `integer` | — | Number of estimated mode entries. |
| 7 | `desiredModeCount` | `integer` | — | Number of desired mode entries. |

Accepted words: `ComplexLanczos`, `DeterminantMethod`, `HessenbergMethod`, `ImplicitRestartedArnoldi`, `InverseIteration`, `Maximum`, `Point`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the method ID must be a positive integer.
- `alphaA` — the coordinates of a search region must be finite numbers.

**Example record**

~~~text
ComplexEigenMethod;40;InverseIteration;Maximum;;;;;0.;0.;0.;3.E+3;500.;4;4
~~~

[Model containing this record](../../../validation/models/dynamics/complex_eigen_poles_sol107.oos)

Reading the example gives `id = 40`, `methodName = InverseIteration`, `norm = Maximum`.

## ComplexEigenPoles

Supplies one or two poles for the determinant-based complex eigenvalue method.

**Record format and fields**

`ComplexEigenPoles;id;realPart1;imaginaryPart1;multiplicity1;realPart2;imaginaryPart2;multiplicity2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `realPart1` | `real` | Required | In-phase component of the complex quantity. Entry 1. |
| 3 | `imaginaryPart1` | `real` | Required | Quadrature component of the complex quantity. Entry 1. |
| 4 | `multiplicity1` | `integer` | Required | Number of times the corresponding root or contribution is represented. Entry 1. |
| 5 | `realPart2` | `real` | Required | In-phase component of the complex quantity. Entry 2. |
| 6 | `imaginaryPart2` | `real` | Required | Quadrature component of the complex quantity. Entry 2. |
| 7 | `multiplicity2` | `integer` | Required | Number of times the corresponding root or contribution is represented. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `realPart1` — the coordinates of a pole must be finite numbers.
- `realPart2` — the coordinates of a pole must be finite numbers.

**Example record**

~~~text
ComplexEigenPoles;40;-10.;0.;1;-10.;500.;1
~~~

[Model containing this record](../../../validation/models/dynamics/complex_eigen_poles_sol107.oos)

Reading the example gives `id = 40`, `realPart1 = -10.`, `imaginaryPart1 = 0.`, `multiplicity1 = 1`.

## DynamicLoadCombination

A dynamic load made of other dynamic load sets, combined linearly.

**Record format and fields**

`DynamicLoadCombination;id;scaleFactor;<terms>`

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

- `id` — the dynamic load set ID must be a positive integer.
- `scaleFactor1` — the card needs at least one dynamic load set.
- `loadSetId1` — a dynamic load set ID must be a positive integer.
- `loadSetId1` — the card cannot refer to its own set ID.

**Example record**

~~~text
DynamicLoadCombination;1;1.;1.;31;1.;32
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol112_channel_file_loads.oos)

Reading the example gives `id = 1`, `scaleFactor = 1.`.

## DynamicLoadDelay

Time delays of a dynamic load on one or two degrees of freedom.

**Record format and fields**

`DynamicLoadDelay;id;point1;components1;delay1;point2;components2;delay2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `point1` | `integer` | Required | Identifier addressing node data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `delay1` | `real` | Required | Time shift relative to the reference excitation, in model time units. Entry 1. |
| 5 | `point2` | `integer` | Required | Identifier addressing node data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `delay2` | `real` | Required | Time shift relative to the reference excitation, in model time units. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `point1` — the point ID must be a positive integer.
- `point2` — the point ID must be a positive integer.

**Example record**

~~~text
DynamicLoadDelay;22;15;3;5.E-4
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 22`, `point1 = 15`, `components1 = 3`, `delay1 = 5.E-4`.

## DynamicLoadPhase

Phase leads of a dynamic load on one or two degrees of freedom.

**Record format and fields**

`DynamicLoadPhase;id;point1;components1;phaseAngle1;point2;components2;phaseAngle2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `point1` | `integer` | Required | Identifier addressing node data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `phaseAngle1` | `real` | Required | Angular phase offset relative to the reference excitation. Entry 1. |
| 5 | `point2` | `integer` | Required | Identifier addressing node data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `phaseAngle2` | `real` | Required | Angular phase offset relative to the reference excitation. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `point1` — the point ID must be a positive integer.
- `point2` — the point ID must be a positive integer.

**Example record**

~~~text
DynamicLoadPhase;23;15;3;30.
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 23`, `point1 = 15`, `components1 = 3`, `phaseAngle1 = 30.`.

## DynamicLoadScale

Scale (area) factors of a load on one or two degrees of freedom.

**Record format and fields**

`DynamicLoadScale;id;point1;components1;scaleFactor1;point2;components2;scaleFactor2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `point1` | `integer` | Required | Identifier addressing node data. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `scaleFactor1` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 1. |
| 5 | `point2` | `integer` | Required | Identifier addressing node data. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `scaleFactor2` | `real` | Required | Multiplier applied to the quantity specified by the entry. Entry 2. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `point1` — the point ID must be a positive integer.
- `point2` — the point ID must be a positive integer.

**Example record**

~~~text
DynamicLoadScale;41;102;1;1.;213;3;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/frequency_dependent_freq.oos)

Reading the example gives `id = 41`, `point1 = 102`, `components1 = 1`, `scaleFactor1 = 1.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `point1 = 102`, `point2 = 213`.

## FreqBetweenModes3

Excitation frequencies between the modal frequencies of a range (modal frequency response).

**Record format and fields**

`FreqBetweenModes3;id;frequency1;frequency2;kind;frequencyCount;clustering`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frequency1` | `real` | Required | Number of cycles per unit time. Entry 1. |
| 3 | `frequency2` | `real` | same as frequency1 | Number of cycles per unit time. Entry 2. |
| 4 | `kind` | `text` | Linear | Selects the kind for FreqBetweenModes3. |
| 5 | `frequencyCount` | `integer` | 10 | Number of frequency entries. |
| 6 | `clustering` | `real` | 1.0 | Controls the concentration of frequency samples between the range limits. |

Accepted words: `Linear`, `Logarithmic`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.

**Example record**

~~~text
FreqBetweenModes3;40;10.;1.E+3;Linear;5;2.
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 40`, `frequency1 = 10.`, `frequency2 = 1.E+3`, `kind = Linear`.

## FreqLinearSteps1

Excitation frequencies at equal steps.

**Record format and fields**

`FreqLinearSteps1;id;frequency1;frequencyIncrement;incrementCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frequency1` | `real` | 0.0 | Number of cycles per unit time. Entry 1. |
| 3 | `frequencyIncrement` | `real` | Required | Separation between adjacent frequencies (inverse time). |
| 4 | `incrementCount` | `integer` | 1 | Number of increment entries. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.

**Example record**

~~~text
FreqLinearSteps1;2;50.;50.;9
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_perforated_shell_sol111.oos)

Reading the example gives `id = 2`, `frequency1 = 50.`, `frequencyIncrement = 50.`, `incrementCount = 9`.

## FreqList

A set of excitation frequencies listed one by one.

**Record format and fields**

`FreqList;id;<frequencies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `frequencies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frequency` | `real` | — | Number of cycles per unit time. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.
- `frequency1` — the card needs at least one frequency.
- `frequencies` — a frequency must not be negative.

**Example record**

~~~text
FreqList;40;5.;10.;20.;38.;40.;42.;80.;120.;250.
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 40`.

## FreqLogSteps2

Excitation frequencies at equal logarithmic steps.

**Record format and fields**

`FreqLogSteps2;id;frequency1;frequency2;intervalCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frequency1` | `real` | Required | Number of cycles per unit time. Entry 1. |
| 3 | `frequency2` | `real` | Required | Number of cycles per unit time. Entry 2. |
| 4 | `intervalCount` | `integer` | 1 | Number of interval entries. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.

**Example record**

~~~text
FreqLogSteps2;40;2.;400.;24
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 40`, `frequency1 = 2.`, `frequency2 = 400.`, `intervalCount = 24`.

## FreqModeFractions5

Fractions of the modal frequencies of a range (modal frequency response).

**Record format and fields**

`FreqModeFractions5;id;frequency1;frequency2;<fractions>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frequency1` | `real` | 0.0 | Number of cycles per unit time. Entry 1. |
| 3 | `frequency2` | `real` | 1.0E20 | Number of cycles per unit time. Entry 2. |

**Repeated group `fractions`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fraction` | `real` | — | Portion of the corresponding total, expressed as a ratio. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.
- `fraction1` — the card needs at least one fraction.
- `fractions` — a fraction of a natural frequency must be greater than zero.

**Example record**

~~~text
FreqModeFractions5;40;10.;1.E+3;0.8;0.9;1.;1.1;1.2
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 40`, `frequency1 = 10.`, `frequency2 = 1.E+3`.

## FreqResponseLoad1

A frequency response excitation P(f) = A * (C(f) + i * D(f)) * exp(i * (phi - 2 * pi * f * tau)).

**Record format and fields**

`FreqResponseLoad1;id;excitationId;delayId;delay;phaseId;phase;realTableId;realValue;imaginaryTableId;imaginaryValue;kind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier selecting the excitation record or set. |
| 3 | `delayId` | `integer` | — | Identifier selecting the delay record or set. Alternative to `delay`. |
| 4 | `delay` | `real` | 0.0 | Time shift relative to the reference excitation, in model time units. Alternative to `delayId`. |
| 5 | `phaseId` | `integer` | — | Identifier selecting the phase record or set. Alternative to `phase`. |
| 6 | `phase` | `real` | 0.0 | Phase of the harmonic quantity relative to the reference oscillation. Alternative to `phaseId`. |
| 7 | `realTableId` | `integer` | — | Table supplying the variation of real. Alternative to `realValue`. |
| 8 | `realValue` | `real` | 0.0 | Real scalar value or real part of the complex quantity. Alternative to `realTableId`. |
| 9 | `imaginaryTableId` | `integer` | — | Table supplying the variation of imaginary. Alternative to `imaginaryValue`. |
| 10 | `imaginaryValue` | `real` | 0.0 | Imaginary part paired with the real component. Alternative to `imaginaryTableId`. |
| 11 | `kind` | `any` | Load | Selects the kind for FreqResponseLoad1. |

Accepted words: `Acceleration`, `Displacement`, `Load`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the dynamic load set ID must be a positive integer.

**Example record**

~~~text
FreqResponseLoad1;3;4;;;;;5
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_perforated_shell_sol111.oos)

Reading the example gives `id = 3`, `excitationId = 4`, `realTableId = 5`.

## FreqResponseLoad2

A frequency response excitation P(f) = A * B(f) * exp(i * (phi(f) + phase - 2 * pi * f * tau)).

**Record format and fields**

`FreqResponseLoad2;id;excitationId;delayId;delay;phaseId;phase;amplitudeTableId;amplitude;phaseTableId;phaseAngle;kind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier selecting the excitation record or set. |
| 3 | `delayId` | `integer` | — | Identifier selecting the delay record or set. Alternative to `delay`. |
| 4 | `delay` | `real` | 0.0 | Time shift relative to the reference excitation, in model time units. Alternative to `delayId`. |
| 5 | `phaseId` | `integer` | — | Identifier selecting the phase record or set. Alternative to `phase`. |
| 6 | `phase` | `real` | 0.0 | Phase of the harmonic quantity relative to the reference oscillation. Alternative to `phaseId`. |
| 7 | `amplitudeTableId` | `integer` | — | Table supplying the variation of amplitude. Alternative to `amplitude`. |
| 8 | `amplitude` | `real` | — | Size of the excitation or response before applying its phase. Alternative to `amplitudeTableId`. |
| 9 | `phaseTableId` | `integer` | — | Table supplying the variation of phase. Alternative to `phaseAngle`. |
| 10 | `phaseAngle` | `real` | 0.0 | Angular phase offset relative to the reference excitation. Alternative to `phaseTableId`. |
| 11 | `kind` | `any` | Load | Selects the kind for FreqResponseLoad2. |

Accepted words: `Acceleration`, `Displacement`, `Load`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the dynamic load set ID must be a positive integer.

**Example record**

~~~text
FreqResponseLoad2;21;1;22;;23;;24;;25;;Load
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 21`, `excitationId = 1`, `delayId = 22`, `phaseId = 23`.

## FreqSpreadAroundModes4

A spread of frequencies around each modal frequency of a range (modal frequency response).

**Record format and fields**

`FreqSpreadAroundModes4;id;frequency1;frequency2;frequencySpread;frequencyCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frequency1` | `real` | 0.0 | Number of cycles per unit time. Entry 1. |
| 3 | `frequency2` | `real` | 1.0E20 | Number of cycles per unit time. Entry 2. |
| 4 | `frequencySpread` | `real` | 0.10 | The fractional spread on each side of a modal frequency. |
| 5 | `frequencyCount` | `integer` | 3 | Number of frequency entries. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the frequency set ID must be a positive integer.

**Example record**

~~~text
FreqSpreadAroundModes4;40;10.;1.E+3;0.1;3
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 40`, `frequency1 = 10.`, `frequency2 = 1.E+3`, `frequencySpread = 0.1`.

## FrfAssemblyLoadDelay

The time delay of a dynamic load on one degree of freedom of an FRF component, in an FRF based assembly (FBA).

**Record format and fields**

`FrfAssemblyLoadDelay;id;frfComponent;pointId;components;delay`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frfComponent` | `any` | — | Identifier addressing frf component data. |
| 3 | `pointId` | `integer` | Required | Identifier of the point to which this entry applies. |
| 4 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 5 | `delay` | `real` | Required | Time shift relative to the reference excitation, in model time units. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfAssemblyLoadDelay;402;PLATE;15;3;5.E-4
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 402`, `frfComponent = PLATE`, `pointId = 15`, `components = 3`.

## FrfAssemblyLoadPhase

The phase lead of a dynamic load on one degree of freedom of an FRF component, in an FRF based assembly (FBA).

**Record format and fields**

`FrfAssemblyLoadPhase;id;frfComponent;pointId;components;phase`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frfComponent` | `any` | — | Identifier addressing frf component data. |
| 3 | `pointId` | `integer` | Required | Identifier of the point to which this entry applies. |
| 4 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 5 | `phase` | `real` | Required | Phase of the harmonic quantity relative to the reference oscillation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfAssemblyLoadPhase;403;PLATE;15;3;20.
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 403`, `frfComponent = PLATE`, `pointId = 15`, `components = 3`.

## FrfAssemblyLoadScale

The scale factor of a dynamic load on one degree of freedom of an FRF component, in an FRF based assembly (FBA).

**Record format and fields**

`FrfAssemblyLoadScale;id;frfComponent;pointId;components;scaleFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frfComponent` | `any` | — | Identifier addressing frf component data. |
| 3 | `pointId` | `integer` | Required | Identifier of the point to which this entry applies. |
| 4 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 5 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfAssemblyLoadScale;401;PLATE;15;3;1.
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 401`, `frfComponent = PLATE`, `pointId = 15`, `components = 3`.

## FrfComponent

A component whose frequency response functions were made by an earlier run and that an FRF based assembly (FBA) puts together with others.

**Record format and fields**

`FrfComponent;id;componentName;medium;unitNumber;lengthScaleFactor;forceScaleFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `componentName` | `text` | — | Text naming the component. |
| 3 | `medium` | `text` | — | Storage medium supplying the component frequency response functions. |
| 4 | `unitNumber` | `integer` | 0 | Logical file unit used to identify an external resource. |
| 5 | `lengthScaleFactor` | `real` | 1.0 | Multiplier for length scale. |
| 6 | `forceScaleFactor` | `real` | 1.0 | Multiplier for force scale. |

Accepted words: `All`, `Assembly`, `BinaryResultsFile`, `Component`, `ConnectionInfo`, `Constant`, `Database`, `Element`, `Table`, `UniversalFile`.

**Example record**

~~~text
FrfComponent;10;PLATE;BinaryResultsFile;25
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 10`, `componentName = PLATE`, `medium = BinaryResultsFile`, `unitNumber = 25`.

## FrfConnection

An explicit connection between a point of one FRF component and a point of another, in an FRF based assembly (FBA).

**Record format and fields**

`FrfConnection;id;frfComponent1;point1;frfComponent2;point2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `frfComponent1` | `any` | — | Frequency-response component on side 1 of the assembly connection. |
| 3 | `point1` | `integer` | — | Point at position 1 in the ordered FrfConnection data. |
| 4 | `frfComponent2` | `any` | — | Frequency-response component on side 2 of the assembly connection. |
| 5 | `point2` | `integer` | — | Point at position 2 in the ordered FrfConnection data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfConnection;1;PLATE;5;STRUT;201
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 1`, `frfComponent1 = PLATE`, `point1 = 5`, `frfComponent2 = STRUT`.

## FrfExcitationDof

A degree of freedom where a unit load generates a frequency-response function. pointId identifies a node or scalar point. components is 1 to 6 for a node, 0 or blank for a scalar point. entryLabel is a required literal text value, preserved whole regardless of its length.

**Record format and fields**

`FrfExcitationDof;pointId;components;entryLabel`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointId` | `integer` | Required | Identifier of the point to which this entry applies. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `entryLabel` | `text` | — | User label associated with the entry. Written as one text field. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfExcitationDof;13;3;UNIT LOAD AT GRID POINT 13 ALONG Z
~~~

[Model containing this record](../../../validation/models/dynamics/frf_gen_plate.oos)

Reading the example gives `pointId = 13`, `components = 3`, `entryLabel = UNIT LOAD AT GRID POINT 13 ALONG Z`.

## FrfExcitationDofList

Degrees of freedom where unit loads are applied to generate frequency response functions, for a list of points that share their components.

**Record format and fields**

`FrfExcitationDofList;components;<pointIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `pointIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointId` | `any` | — | Identifier of the point to which this entry applies. |

Accepted words: `Through`.

**Example record**

~~~text
FrfExcitationDofList;1;202;212
~~~

[Model containing this record](../../../validation/models/dynamics/frf_gen_strut.oos)

Reading the example gives `components = 1`.

## FrfFlexibleConnection

The stiffness, damping and structural damping of a flexible connection between a point of one FRF component and a point of another, in an FRF based assembly (FBA).

**Record format and fields**

`FrfFlexibleConnection;id;components;frfComponent1;point1;frfComponent2;point2;stiffnessTableId;stiffness;dampingTableId;damping;structuralDampingTableId;structuralDamping`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `frfComponent1` | `any` | — | Frequency-response component on side 1 of the assembly connection. |
| 4 | `point1` | `integer` | — | Point at position 1 in the ordered FrfFlexibleConnection data. |
| 5 | `frfComponent2` | `any` | — | Frequency-response component on side 2 of the assembly connection. |
| 6 | `point2` | `integer` | — | Point at position 2 in the ordered FrfFlexibleConnection data. |
| 7 | `stiffnessTableId` | `integer` | — | Table supplying the variation of stiffness. Alternative to `stiffness`. |
| 8 | `stiffness` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Alternative to `stiffnessTableId`. |
| 9 | `dampingTableId` | `integer` | — | Table supplying the variation of damping. Alternative to `damping`. |
| 10 | `damping` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Alternative to `dampingTableId`. |
| 11 | `structuralDampingTableId` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Alternative to `structuralDamping`. |
| 12 | `structuralDamping` | `real` | — | Structural damping coefficient for the associated material or property. Alternative to `structuralDampingTableId`. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
FrfFlexibleConnection;2;3;PLATE;5;STRUT;201;;1.E+3;;0.5;;0.02
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 2`, `components = 3`, `frfComponent1 = PLATE`, `point1 = 5`.

## FrfReleasedDofs

Degrees of freedom of the connection grid points of FRF components that an FRF based assembly (FBA) does not connect.

**Record format and fields**

`FrfReleasedDofs;id;components;frfComponent1;node1;frfComponent2;node2;frfComponent3;node3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `frfComponent1` | `any` | — | Frequency-response component on side 1 of the assembly connection. |
| 4 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 5 | `frfComponent2` | `any` | — | Frequency-response component on side 2 of the assembly connection. |
| 6 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 7 | `frfComponent3` | `any` | — | Frequency-response component on side 3 of the assembly connection. |
| 8 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |

Accepted words: `Constant`, `Element`, `NodePoint2`, `NodePoint3`, `Table`.

**Example record**

~~~text
FrfReleasedDofs;3;456;STRUT;211
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 3`, `components = 456`, `frfComponent1 = STRUT`, `node1 = 211`.

## FrfSinglePointConstr

Single-point constraints on connection points of FRF components in an FRF based assembly (FBA).

**Record format and fields**

`FrfSinglePointConstr;id;components;frfComponent1;point1;frfComponent2;point2;frfComponent3;point3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `frfComponent1` | `any` | — | Frequency-response component on side 1 of the assembly connection. |
| 4 | `point1` | `integer` | — | Point at position 1 in the ordered FrfSinglePointConstr data. |
| 5 | `frfComponent2` | `any` | — | Frequency-response component on side 2 of the assembly connection. |
| 6 | `point2` | `integer` | — | Point at position 2 in the ordered FrfSinglePointConstr data. |
| 7 | `frfComponent3` | `any` | — | Frequency-response component on side 3 of the assembly connection. |
| 8 | `point3` | `integer` | — | Point at position 3 in the ordered FrfSinglePointConstr data. |

Accepted words: `Constant`, `Element`, `Point3Kind`, `Table`.

**Example record**

~~~text
FrfSinglePointConstr;300;1;PLATE;15
~~~

[Model containing this record](../../../validation/models/dynamics/frf_assembly_fba.oos)

Reading the example gives `id = 300`, `components = 1`, `frfComponent1 = PLATE`, `point1 = 15`.

## HeatShellNodalLoad

Concentrated static loads, a power input, on the grid points of heat shell elements (those of a [ShellPropNonlinear](properties.md#shellpropnonlinear) heat transfer property) with a linear or quadratic temperature distribution through the thickness.

**Record format and fields**

`HeatShellNodalLoad;id;node1;components1;heatFlux1;node2;components2;heatFlux2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node1` | `integer` | — | Identifier addressing node data. |
| 3 | `components1` | `integer` | 1 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `heatFlux1` | `real` | — | Thermal energy crossing unit area per unit time. Entry 1. |
| 5 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 6 | `components2` | `integer` | 1 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `heatFlux2` | `real` | — | Thermal energy crossing unit area per unit time. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1` — the card needs at least one load.
- `node2` — the card gives the loads on at most two grid points.

**Example record**

~~~text
HeatShellNodalLoad;10;3;1;50.;6;2;50.
~~~

[Model containing this record](../../../validation/models/dynamics/heat_shell_sloadn1_sol400.oos)

Reading the example gives `id = 10`, `node1 = 3`, `components1 = 1`, `heatFlux1 = 50.`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node1 = 3`.

## HybridDamping

The hybrid modal damping of a direct dynamic solution.

**Record format and fields**

`HybridDamping;id;methodId;modalDampingTableId;dampingInStiffness;printEigenvalues`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `methodId` | `integer` | Required | Identifier selecting the method record or set. |
| 3 | `modalDampingTableId` | `integer` | Required | Table supplying the variation of modal damping. |
| 4 | `dampingInStiffness` | `text` | — | Specifies inclusion of damping contributions in the stiffness representation. |
| 5 | `printEigenvalues` | `text` | — | Switch controlling the listing of the extracted roots. |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
HybridDamping;71;72;73;Yes
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 71`, `methodId = 72`, `modalDampingTableId = 73`, `dampingInStiffness = Yes`.

## HybridDampingRotorOptions

Selects structural, material and Rayleigh damping contributions for hybrid modal damping of a rotor.

**Record format and fields**

`HybridDampingRotorOptions;id;structuralDamping;alphaCoefficient1;alphaCoefficient2;hybridDampingId;structuralDampingFactor;rotorSeparation;structuralDampingFrequency;materialDampingFrequency;hybridDampingFrequency`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 3 | `alphaCoefficient1` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 4 | `alphaCoefficient2` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 5 | `hybridDampingId` | `integer` | 0 | Identifier selecting the hybrid damping record or set. |
| 6 | `structuralDampingFactor` | `real` | 1.0 | Multiplier for structural damping. |
| 7 | `rotorSeparation` | `text` | — | Separation used in the rotor representation, in length units. |
| 8 | `structuralDampingFrequency` | `real` | 0.0 | Structural damping frequency (inverse time). |
| 9 | `materialDampingFrequency` | `real` | 0.0 | Material damping frequency (inverse time). |
| 10 | `hybridDampingFrequency` | `real` | 0.0 | Hybrid damping frequency (inverse time). |

Accepted words: `Constant`, `Element`, `No`, `Table`, `Yes`.

**Example record**

~~~text
HybridDampingRotorOptions;70;0.01;;;71
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 70`, `structuralDamping = 0.01`, `hybridDampingId = 71`.

## InitialElemValues

The initial values of element variables of the elements of an [IdListSet1](sets.md#idlistset1), at the start of the analysis.

**Record format and fields**

`InitialElemValues;id;elementSetId;<variables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elementSetId` | `integer` | Required | Identifier selecting the element set record or set. |

**Repeated group `variables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableName` | `text` | — | Text naming the variable. |
| 2 | `variableValue` | `real` | — | Value of the independent or design variable at the selected evaluation point. |

Accepted words: `ArtificialViscosity`, `CenterX`, `CenterY`, `CenterZ`, `Constant`, `Decay`, `Density`, `Divergence`, `Element`, `MaterialFraction`, `MomentumX`, `MomentumY`, `MomentumZ`, `RadialVelocity`, `SpecificInternalEnergy`, `Table`, `TableDynamic1`, `VelocityX`, `VelocityY`, `VelocityZ`, `VoidFraction`.

**Example record**

~~~text
InitialElemValues;81;5;Density;1.2E-11;SpecificInternalEnergy;2.08E+11
~~~

[Model containing this record](../../../validation/models/dynamics/explicit_initial_conditions_sol700.oos)

Reading the example gives `id = 81`, `elementSetId = 5`.

## InitialValuesUserRoutine

Initial values of element or grid point variables that a user written subroutine computes.

**Record format and fields**

`InitialValuesUserRoutine;id;group;routineName;elementSetId;target`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `group` | `text` | — | Grouping key for entries treated together. |
| 3 | `routineName` | `text` | — | Text naming the routine. |
| 4 | `elementSetId` | `integer` | Required | Identifier selecting the element set record or set. |
| 5 | `target` | `text` | — | Requested target of the selected search or output operation. |

Accepted words: `Constant`, `Element`, `ExternalInitialValues`, `Node`, `Table`.

**Example record**

~~~text
InitialValuesUserRoutine;30;initex;ExternalInitialValues;31;Node
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 30`, `group = initex`, `routineName = ExternalInitialValues`, `elementSetId = 31`.

## InitialVelocityField

An initial velocity field of grid points made of a translation and a rotation about a grid point.

**Record format and fields**

`InitialVelocityField;id;node;scaleFactor;xVelocity;yVelocity;zVelocity;xRotation;yRotation;zRotation;<initializedNodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |
| 4 | `xVelocity` | `real` | 0.0 | X velocity (length per time). |
| 5 | `yVelocity` | `real` | 0.0 | Y velocity (length per time). |
| 6 | `zVelocity` | `real` | 0.0 | Z velocity (length per time). |
| 7 | `xRotation` | `real` | 0.0 | The rotation velocity about G. |
| 8 | `yRotation` | `real` | 0.0 | Rotation about the y axis of the specified reference frame. |
| 9 | `zRotation` | `real` | 0.0 | Rotation about the z axis of the specified reference frame. |

**Repeated group `initializedNodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `initializedNode` | `any` | — | Grid point whose dynamic initial state is being assigned. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `node1` — the card needs the grid points to initialize.

**Example record**

~~~text
InitialVelocityField;81;1;1.;1.E+4;0.;0.;0.;0.;0.;1;Through;8
~~~

[Model containing this record](../../../validation/models/dynamics/explicit_initial_conditions_sol700.oos)

Reading the example gives `id = 81`, `node = 1`, `scaleFactor = 1.`, `xVelocity = 1.E+4`.

## LanczosEigenMethod

Real eigenvalue extraction by the Lanczos method.

**Record format and fields**

`LanczosEigenMethod;id;lowerFrequency;upperFrequency;desiredModeCount;messageLevel;maximumSet;shiftScale;norm;<options>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the method namespace. |
| 2 | `lowerFrequency` | `real` | — | Lower frequency (inverse time). |
| 3 | `upperFrequency` | `real` | — | Upper frequency (inverse time). |
| 4 | `desiredModeCount` | `integer` | 0 | Number of desired mode entries. |
| 5 | `messageLevel` | `integer` | 0 | Diagnostic level. |
| 6 | `maximumSet` | `integer` | 0 | Maximum Lanczos block size. A blank field leaves the block size to the implementation. |
| 7 | `shiftScale` | `real` | — | Multiplier applied to the eigenvalue search shift. |
| 8 | `norm` | `text` | — | Norm used for scaling a mode shape. |

**Repeated group `options`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `option` | `text` | — | Selects how the current entry or group is interpreted. |

Accepted words: `Mass`, `Maximum`.

Accepted parameter names: `Alpha`, `DesiredModeCount`, `FrequencySegmentCount`, `LowerFrequency`, `MaximumSet`, `MessageLevel`, `Normalization`, `SegmentFrequency1`, `SegmentFrequency10`, `SegmentFrequency11`, `SegmentFrequency12`, `SegmentFrequency13`, `SegmentFrequency14`, `SegmentFrequency15`, `SegmentFrequency2`, `SegmentFrequency3`, `SegmentFrequency4`, `SegmentFrequency5`, `SegmentFrequency6`, `SegmentFrequency7`, `SegmentFrequency8`, `SegmentFrequency9`, `ShiftScale`, `UpperFrequency`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the method ID must be a positive integer.

**Example record**

~~~text
LanczosEigenMethod;1;;3.E+3;4
~~~

[Model containing this record](../../../validation/models/nonlinear_harmonic/sol128_bushing_continuation.oos)

Reading the example gives `id = 1`, `upperFrequency = 3.E+3`, `desiredModeCount = 4`.

## NonlinearNegativePowerLoad4

A nonlinear load that is a negative variable raised to a power.

**Record format and fields**

`NonlinearNegativePowerLoad4;id;nodeI;componentsI;scaleFactor;nodeJ;componentsJ;exponent`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nodeI` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsI` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 7 | `exponent` | `real` | Required | Power applied to the associated variable in the stated relation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the nonlinear load set ID must be a positive integer.
- `nodeI` — the point ID must be a positive integer.
- `nodeJ` — the point ID must be a positive integer.

**Example record**

~~~text
NonlinearNegativePowerLoad4;70;5;3;-0.5;5;3;3.
~~~

[Model containing this record](../../../validation/models/dynamics/transient_direct_nolin_sol109.oos)

Reading the example gives `id = 70`, `nodeI = 5`, `componentsI = 3`, `scaleFactor = -0.5`.

## NonlinearPositivePowerLoad3

A nonlinear load that is a positive variable raised to a power.

**Record format and fields**

`NonlinearPositivePowerLoad3;id;nodeI;componentsI;scaleFactor;nodeJ;componentsJ;exponent`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nodeI` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsI` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 7 | `exponent` | `real` | Required | Power applied to the associated variable in the stated relation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the nonlinear load set ID must be a positive integer.
- `nodeI` — the point ID must be a positive integer.
- `nodeJ` — the point ID must be a positive integer.

**Example record**

~~~text
NonlinearPositivePowerLoad3;70;5;3;-0.5;5;3;3.
~~~

[Model containing this record](../../../validation/models/dynamics/transient_direct_nolin_sol109.oos)

Reading the example gives `id = 70`, `nodeI = 5`, `componentsI = 3`, `scaleFactor = -0.5`.

## NonlinearProductLoad2

A nonlinear load that is the product of two variables.

**Record format and fields**

`NonlinearProductLoad2;id;nodeI;componentsI;scaleFactor;nodeJ;componentsJ;nodeK;componentsK`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nodeI` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsI` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 7 | `nodeK` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 8 | `componentsK` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the nonlinear load set ID must be a positive integer.
- `nodeI` — the point ID must be a positive integer.
- `nodeJ` — the point ID must be a positive integer.
- `nodeK` — the point ID must be a positive integer.

**Example record**

~~~text
NonlinearProductLoad2;70;10;3;-0.001;10;13;10;3
~~~

[Model containing this record](../../../validation/models/dynamics/transient_direct_nolin_sol109.oos)

Reading the example gives `id = 70`, `nodeI = 10`, `componentsI = 3`, `scaleFactor = -0.001`.

## NonlinearTableLoad1

A nonlinear load that is a tabular function of a displacement or a velocity.

**Record format and fields**

`NonlinearTableLoad1;id;nodeI;componentsI;scaleFactor;nodeJ;componentsJ;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nodeI` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsI` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `scaleFactor` | `real` | Required | Multiplier applied to the quantity specified by the entry. |
| 5 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 7 | `tableId` | `integer` | Required | Identifier of the tabulated function to evaluate. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the nonlinear load set ID must be a positive integer.
- `nodeI` — the point ID must be a positive integer.
- `nodeJ` — the point ID must be a positive integer.
- `tableId` — the table ID must be a positive integer.

**Example record**

~~~text
NonlinearTableLoad1;70;15;3;1.;15;3;73
~~~

[Model containing this record](../../../validation/models/dynamics/transient_direct_nolin_sol109.oos)

Reading the example gives `id = 70`, `nodeI = 15`, `componentsI = 3`, `scaleFactor = 1.`.

**Referenced records in this example**

- [TableDynamic2](tables.md#tabledynamic2) via `tableId = 73`.

## RandomSpectralDensity

A power spectral density factor of a random analysis.

**Record format and fields**

`RandomSpectralDensity;id;subcaseJ;subcaseK;realPart;imaginaryPart;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `subcaseJ` | `integer` | Required | The subcase of the excited load set. |
| 3 | `subcaseK` | `integer` | Required | The subcase of the applied load set (K >= J). |
| 4 | `realPart` | `real` | 0.0 | In-phase component of the complex quantity. |
| 5 | `imaginaryPart` | `real` | 0.0 | Quadrature component of the complex quantity. |
| 6 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the random analysis set ID must be a positive integer.

**Example record**

~~~text
RandomSpectralDensity;90;1;1;1.;0.;91
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 90`, `subcaseJ = 1`, `subcaseK = 1`, `realPart = 1.`.

**Referenced records in this example**

- [TableRandomSpectrum1](tables.md#tablerandomspectrum1) via `tableId = 91`.

## RandomTimeLags

The time lags of the autocorrelation function of a random analysis.

**Record format and fields**

`RandomTimeLags;id;count;startTime;maximumTime`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `count` | `integer` | Required | Number of entries to process in this group. |
| 3 | `startTime` | `real` | Required | Start time (time). |
| 4 | `maximumTime` | `real` | Required | Maximum time (time). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the random analysis set ID must be a positive integer.

**Example record**

~~~text
RandomTimeLags;90;10;0.001;0.05
~~~

[Model containing this record](../../../validation/models/dynamics/freq_modal_forms_random.oos)

Reading the example gives `id = 90`, `count = 10`, `startTime = 0.001`, `maximumTime = 0.05`.

## RealEigenMethod

Real eigenvalue extraction, with the method named on the card.

**Record format and fields**

`RealEigenMethod;id;method;frequency1;frequency2;estimatedModeCount;desiredModeCount;normalization;normNode;normComponent`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the method namespace. |
| 2 | `method` | `text` | Lanczos | Selects the method for RealEigenMethod. |
| 3 | `frequency1` | `real` | — | Number of cycles per unit time. Entry 1. |
| 4 | `frequency2` | `real` | — | Number of cycles per unit time. Entry 2. |
| 5 | `estimatedModeCount` | `integer` | 0 | Number of estimated mode entries. |
| 6 | `desiredModeCount` | `integer` | — | Number of desired mode entries. |
| 7 | `normalization` | `text` | Mass | Rule used to scale the amplitude of an eigenvector. |
| 8 | `normNode` | `integer` | 0 | Identifier addressing node data. |
| 9 | `normComponent` | `integer` | 0 | Degree of freedom used as the normalization reference. |

Accepted words: `AutomaticGivens`, `AutomaticHouseholder`, `Givens`, `Householder`, `InverseIteration`, `Lanczos`, `Mass`, `Maximum`, `ModifiedGivens`, `ModifiedHouseholder`, `Point`, `SturmInverse`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the method ID must be a positive integer.

**Example record**

~~~text
RealEigenMethod;71;Lanczos;;;;8;Mass
~~~

[Model containing this record](../../../validation/models/dynamics/complex_eigen_modal_sol110.oos)

Reading the example gives `id = 71`, `method = Lanczos`, `desiredModeCount = 8`, `normalization = Mass`.

## RotorHybridDamping

Associates individual rotors with their hybrid modal damping definitions.

**Record format and fields**

`RotorHybridDamping;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `rotorId` | `integer` | — | Identifier selecting the rotor record or set. |
| 2 | `hybridDampingId` | `integer` | — | Identifier selecting the hybrid damping record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `rotorId1` — the card needs at least one pair of a rotor and a hybrid damping.

**Example record**

~~~text
RotorHybridDamping;10;11
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_unbalance_sol108.oos)

## RotorUnbalanceLoad

A rotating unbalance load of a rotordynamic transient or frequency response analysis.

**Record format and fields**

`RotorUnbalanceLoad;id;massTableId;mass;nodeId;directionX;directionY;directionZ;radialOffsetTableId;radialOffset;angularPosition;axialOffsetTableId;axialOffset;startTimeOrFrequency;stopTimeOrFrequency;correctionFlag;forcePointT1;forcePointT2;forcePointT3;forcePointR1;forcePointR2;forcePointR3;massCorrectionPointT1;massCorrectionPointT2;massCorrectionPointT3;massCorrectionPointR1;massCorrectionPointR2;massCorrectionPointR3;speedCorrectionPoint1;speedCorrectionPoint2;speedCorrectionPoint3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `massTableId` | `integer` | — | Table supplying the variation of mass. Alternative to `mass`. |
| 3 | `mass` | `real` | — | Inertial mass associated with the selected component or body. Alternative to `massTableId`. |
| 4 | `nodeId` | `integer` | Required | Identifier of the grid point addressed by this record. |
| 5 | `directionX` | `real` | Required | X component of the specified direction vector in its reference frame. |
| 6 | `directionY` | `real` | Required | Y component of the specified direction vector in its reference frame. |
| 7 | `directionZ` | `real` | Required | Z component of the specified direction vector in its reference frame. |
| 8 | `radialOffsetTableId` | `integer` | — | Table supplying the variation of radial offset. Alternative to `radialOffset`. |
| 9 | `radialOffset` | `real` | 1.0 | Distance from the reference axis in the radial direction. Alternative to `radialOffsetTableId`. |
| 10 | `angularPosition` | `real` | 0.0 | The angular position of the mass, in degrees. |
| 11 | `axialOffsetTableId` | `integer` | — | Table supplying the variation of axial offset. Alternative to `axialOffset`. |
| 12 | `axialOffset` | `real` | 0.0 | Distance from the reference position measured along the rotation axis. Alternative to `axialOffsetTableId`. |
| 13 | `startTimeOrFrequency` | `real` | 0.0 | Start time or frequency (inverse time). |
| 14 | `stopTimeOrFrequency` | `real` | 999999.0 | Stop time or frequency (inverse time). |
| 15 | `correctionFlag` | `text` | None | Selects the correction flag for RotorUnbalanceLoad. |
| 16 | `forcePointT1` | `integer` | 0 | Extra point for unbalance force output, component 1 of the T group (T for translations, R for rotations). |
| 17 | `forcePointT2` | `integer` | 0 | Extra point for unbalance force output, component 2 of the T group (T for translations, R for rotations). |
| 18 | `forcePointT3` | `integer` | 0 | Extra point for unbalance force output, component 3 of the T group (T for translations, R for rotations). |
| 19 | `forcePointR1` | `integer` | 0 | Extra point for unbalance force output, component 1 of the R group (T for translations, R for rotations). |
| 20 | `forcePointR2` | `integer` | 0 | Extra point for unbalance force output, component 2 of the R group (T for translations, R for rotations). |
| 21 | `forcePointR3` | `integer` | 0 | Extra point for unbalance force output, component 3 of the R group (T for translations, R for rotations). |
| 22 | `massCorrectionPointT1` | `integer` | 0 | Extra point for the mass correction, component 1 of the T group (T for translations, R for rotations). |
| 23 | `massCorrectionPointT2` | `integer` | 0 | Extra point for the mass correction, component 2 of the T group (T for translations, R for rotations). |
| 24 | `massCorrectionPointT3` | `integer` | 0 | Extra point for the mass correction, component 3 of the T group (T for translations, R for rotations). |
| 25 | `massCorrectionPointR1` | `integer` | 0 | Extra point for the mass correction, component 1 of the R group (T for translations, R for rotations). |
| 26 | `massCorrectionPointR2` | `integer` | 0 | Extra point for the mass correction, component 2 of the R group (T for translations, R for rotations). |
| 27 | `massCorrectionPointR3` | `integer` | 0 | Extra point for the mass correction, component 3 of the R group (T for translations, R for rotations). |
| 28 | `speedCorrectionPoint1` | `integer` | 0 | Extra point for spin-rate correction component 1. |
| 29 | `speedCorrectionPoint2` | `integer` | 0 | Extra point for spin-rate correction component 2. |
| 30 | `speedCorrectionPoint3` | `integer` | 0 | Extra point for spin-rate correction component 3. |

Accepted words: `Acceleration`, `Both`, `Displacement`, `Load`, `Mass`, `None`, `Speed`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.

**Example record**

~~~text
RotorUnbalanceLoad;300;;1.E-5;1003;0.;1.;0.;;10.;0.;;0.
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_unbalance_sol108.oos)

Reading the example gives `id = 300`, `mass = 1.E-5`, `nodeId = 1003`, `directionX = 0.`.

## TransferFunction

Relates a dependent degree of freedom to independent inputs using coefficients of the value and its first two time derivatives.

**Record format and fields**

`TransferFunction;id;nodeD;componentsD;coefficientB0;coefficientB1;coefficientB2;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `nodeD` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsD` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `coefficientB0` | `real` | 0.0 | Coefficient B0 in the TransferFunction relation. |
| 5 | `coefficientB1` | `real` | 0.0 | Coefficient B1 in the TransferFunction relation. |
| 6 | `coefficientB2` | `real` | 0.0 | Coefficient B2 in the TransferFunction relation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `termNode` | `integer` | — | Point identifier for the associated term. |
| 2 | `termComponents` | `integer` | — | Degrees of freedom involved in the associated term. |
| 3 | `coefficientA0` | `real` | — | Coefficient A0 in the TransferFunction relation for terms. |
| 4 | `coefficientA1` | `real` | — | Coefficient A1 in the TransferFunction relation for terms. |
| 5 | `coefficientA2` | `real` | — | Coefficient A2 in the TransferFunction relation for terms. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.

**Example record**

~~~text
TransferFunction;60;901;;1.;;;15;3;-1.
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 60`, `nodeD = 901`, `coefficientB0 = 1.`.

## TransientFormulaLoad2

A transient excitation given by a formula, for T1 <= t <= T2 and zero elsewhere: P(t) = A * t'^B * exp(C * t') * cos(2 * pi * F * t' + P),  with t' = t - T1 - tau.

**Record format and fields**

`TransientFormulaLoad2;id;excitationId;delayId;delay;kind;time1;time2;frequency;phase;coefficientC;exponentB;initialDisplacementFactor;initialVelocityFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier selecting the excitation record or set. |
| 3 | `delayId` | `integer` | — | Identifier selecting the delay record or set. Alternative to `delay`. |
| 4 | `delay` | `real` | 0.0 | Time shift relative to the reference excitation, in model time units. Alternative to `delayId`. |
| 5 | `kind` | `any` | Load | Selects the kind for TransientFormulaLoad2. |
| 6 | `time1` | `real` | 0.0 | Time 1 (time). |
| 7 | `time2` | `real` | same as time1 | Time 2 (time). |
| 8 | `frequency` | `real` | 0.0 | Number of cycles per unit time. |
| 9 | `phase` | `real` | 0.0 | Phase of the harmonic quantity relative to the reference oscillation. |
| 10 | `coefficientC` | `real` | 0.0 | Coefficient C in the TransientFormulaLoad2 relation. |
| 11 | `exponentB` | `real` | 0.0 | The growth coefficient. |
| 12 | `initialDisplacementFactor` | `real` | 0.0 | Multiplier for initial displacement. |
| 13 | `initialVelocityFactor` | `real` | 0.0 | Multiplier for initial velocity. |

Accepted words: `Acceleration`, `Displacement`, `Load`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the dynamic load set ID must be a positive integer.

**Example record**

~~~text
TransientFormulaLoad2;51;2;;;Load;0.;0.05;0.;0.
~~~

[Model containing this record](../../../validation/models/dynamics/transient_nonlinear_sol129.oos)

Reading the example gives `id = 51`, `excitationId = 2`, `kind = Load`, `time1 = 0.`.

## TransientInitialCondition

The initial displacement and velocity of one degree of freedom of a transient analysis.

**Record format and fields**

`TransientInitialCondition;id;node;components;initialDisplacement;initialVelocity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `node` | `integer` | Required | Grid point to which this entry applies. |
| 3 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 4 | `initialDisplacement` | `real` | 0.0 | The initial displacement. |
| 5 | `initialVelocity` | `real` | 0.0 | Initial velocity (length per time). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.

**Example record**

~~~text
TransientInitialCondition;81;15;3;0.;50.
~~~

[Model containing this record](../../../validation/models/dynamics/transient_direct_nolin_sol109.oos)

Reading the example gives `id = 81`, `node = 15`, `components = 3`, `initialDisplacement = 0.`.

## TransientTableLoad1

A transient excitation P(t) = A * F(t - tau), where F is a table.

**Record format and fields**

`TransientTableLoad1;id;excitationId;delayId;delay;kind;tableId;functionValue;initialDisplacementFactor;initialVelocityFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `excitationId` | `integer` | Required | Identifier selecting the excitation record or set. |
| 3 | `delayId` | `integer` | — | Identifier selecting the delay record or set. Alternative to `delay`. |
| 4 | `delay` | `real` | 0.0 | Time shift relative to the reference excitation, in model time units. Alternative to `delayId`. |
| 5 | `kind` | `any` | Load | Selects the kind for TransientTableLoad1. |
| 6 | `tableId` | `integer` | — | Identifier of the tabulated function to evaluate. Alternative to `functionValue`. |
| 7 | `functionValue` | `real` | 0.0 | Value of the tabulated function at this sample. Alternative to `tableId`. |
| 8 | `initialDisplacementFactor` | `real` | 0.0 | Multiplier for initial displacement. |
| 9 | `initialVelocityFactor` | `real` | 0.0 | Multiplier for initial velocity. |

Accepted words: `Acceleration`, `Displacement`, `Load`, `Velocity`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the dynamic load set ID must be a positive integer.

**Example record**

~~~text
TransientTableLoad1;1;2;;;0;3
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/sol700_tied_shell_edge.oos)

Reading the example gives `id = 1`, `excitationId = 2`, `kind = 0`, `tableId = 3`.
