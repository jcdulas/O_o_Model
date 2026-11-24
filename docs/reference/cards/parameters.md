# Model parameters

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## Parameter

A named parameter of the analysis.

**Record format and fields**

`Parameter;parameterName;parameterValue;imaginaryValue`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |
| 3 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

Accepted words: `Absolute`, `All`, `AugmentedModes`, `Automatic`, `BackwardDifference`, `Beta`, `Both`, `ClassicFormulation`, `DataCheckOnly`, `DirectMethod`, `ElemNumbering`, `ElemOffsetZ`, `ElemOffsetsOnly`, `Element`, `Extrapolate`, `False`, `ForwardDifference`, `FreeDofSet`, `Given`, `GlobalDofSet`, `HarderShearPanel`, `IntegralMethod`, `Iterative`, `KrylovMethod`, `Linear`, `Link`, `LoadRecoveryOffsets`, `Log10`, `LogLogScale`, `LowerUpperSolution`, `Manual`, `Mass`, `MinVolume`, `ModalFormulation`, `ModalMethod`, `New`, `No`, `NoDampingOffsets`, `NoFreqAdjust`, `NoLink`, `NoMassOffsets`, `NoOffsetDifference`, `NoStaticAdjust`, `NoTemperatureGradientOffsets`, `NoThermalOffsets`, `NonSmeared`, `None`, `Off`, `Old`, `On`, `PanelMethodCoupling`, `PeakValue`, `Physical`, `Print`, `Punch`, `Relative`, `ResidualModes`, `ResidualOnly`, `RitzVectors`, `RootMeanSquare`, `Same`, `SecantMethod`, `Select`, `Semi`, `StaticModalFormulation`, `SuperelementMap`, `SuperelementMapAll`, `SuperelementMapConnected`, `SuperelementMapEstimate`, `SuperelementMapPunch`, `SuperelementRecovery`, `SupersonicLiftingSurface`, `TimoshenkoBeam`, `TimoshenkoForce`, `Total`, `True`, `Volume`, `Yes`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterName` — the card needs a name.

**Example record**

~~~text
Parameter;StressSign;1
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `parameterName = StressSign`, `parameterValue = 1`.
