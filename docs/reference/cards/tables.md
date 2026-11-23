# Functions and tables

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## TableDynamic1

A function y(x) for dynamic loads (of time or of frequency), given by points.

**Record format and fields**

`TableDynamic1;id;xAxisKind;yAxisKind;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `xAxisKind` | `text` | — | Selects the x axis kind for TableDynamic1. |
| 3 | `yAxisKind` | `text` | — | Selects the y axis kind for TableDynamic1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableDynamic1;4;;;0.;1.;1.;1.;EndTable
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol700_explicit_springs.oos)

Reading the example gives `id = 4`.

## TableDynamic2

A function of x - X1 for dynamic loads, given by points: y = yT(x - X1).

**Record format and fields**

`TableDynamic2;id;abscissaShift;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `abscissaShift` | `real` | 0.0 | The table parameter: the value of x where the points' own x is 0. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableDynamic2;24;0.;0.;1.;500.;0.5;EndTable
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 24`, `abscissaShift = 0.`.

## TableDynamic3

A function of (x - X1) / X2 for dynamic loads, given by points: y = yT((x - X1) / X2).

**Record format and fields**

`TableDynamic3;id;abscissaShift;abscissaScale;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `abscissaShift` | `real` | Required | The table parameters. |
| 3 | `abscissaScale` | `real` | Required | Scale applied to the independent axis of the table. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableDynamic3;25;200.;100.;-2.;-45.;3.;90.;EndTable
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 25`, `abscissaShift = 200.`, `abscissaScale = 100.`.

## TableDynamic4

A polynomial for dynamic loads, y = sum of Ai * ((x - X1) / X2)^i for i = 0 to N, where x is first brought into [X3, X4].

**Record format and fields**

`TableDynamic4;id;abscissaShift;abscissaScale;abscissaMinimum;abscissaMaximum;<coefficients>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `abscissaShift` | `real` | Required | The table parameters. |
| 3 | `abscissaScale` | `real` | Required | Scale applied to the independent axis of the table. |
| 4 | `abscissaMinimum` | `real` | Required | Lower end of the interval on the independent axis. |
| 5 | `abscissaMaximum` | `real` | Required | Upper end of the interval on the independent axis. |

**Repeated group `coefficients`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coefficient` | `any` | — | Coefficient value in the TableDynamic4 relation for coefficients. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableDynamic4;28;0.;100.;0.;500.;1.;0.5;-0.1;EndTable
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 28`, `abscissaShift = 0.`, `abscissaScale = 100.`, `abscissaMinimum = 0.`.

## TableDynamic5

A function f(x, y) of two variables for dynamic loads, given by a [TableDynamic1](tables.md#tabledynamic1) to [TableDynamic4](tables.md#tabledynamic4) table of y for each of several values of x.

**Record format and fields**

`TableDynamic5;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `table` | `integer` | — | Identifier or selection of the data table supplying this part of the function. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `tables` — x and the table IDs must have the same number of values.

**Example record**

~~~text
TableDynamic5;90;0.;91;100.;92;EndTable
~~~

[Model containing this record](../../../validation/models/dynamics/freq_direct_rload2_tf_damping.oos)

Reading the example gives `id = 90`.

## TableFatigueHistory

Defines a cyclic loading history as load values sampled over time for use by [FatigueLoad](solution_control.md#fatigueload).

**Record format and fields**

`TableFatigueHistory;id;<ordinates>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `ordinates`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ordinate` | `any` | — | Function value at the corresponding abscissa. |

Accepted words: `Constant`, `Element`, `EndTable`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `ordinate` — the table needs at least one value.

**Example record**

~~~text
TableFatigueHistory;101;0.;100.;-60.;80.;-100.;40.;-20.;0.;EndTable
~~~

[Model containing this record](../../../validation/models/fatigue/sol101_fatigue_duty_cycle.oos)

Reading the example gives `id = 101`.

## TableGustSpectrum

The power spectral density of a gust for an aeroelastic response analysis (referenced by the [RandomSpectralDensity](dynamics.md#randomspectraldensity) cards).

**Record format and fields**

`TableGustSpectrum;id;kind;turbulenceScaleRatio;gustVelocity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the random table namespace. |
| 2 | `kind` | `integer` | Required | Selects the kind for TableGustSpectrum. |
| 3 | `turbulenceScaleRatio` | `real` | Required | Relative measure of turbulence scale. |
| 4 | `gustVelocity` | `real` | Required | Gust velocity (length per time). |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableGustSpectrum;96;1;7.62;1.E+3
~~~

[Model containing this record](../../../validation/models/dynamics/random_gust_tabrndg_sol146.oos)

Reading the example gives `id = 96`, `kind = 1`, `turbulenceScaleRatio = 7.62`, `gustVelocity = 1.E+3`.

## TableHeat1

A function f(y) of one variable for the convection heat transfer coefficient or the Nusselt number that a [TableHeatTwoVariables](tables.md#tableheattwovariables) refers to, given by points.

**Record format and fields**

`TableHeat1;id;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the heat table namespace. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `x` — the independent variable must be ascending.

**Example record**

~~~text
TableHeat1;46;0.;0.006;200.;0.01;EndTable
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 46`.

## TableHeatTwoVariables

The heat transfer coefficient or the Nusselt number as a function of two variables, as a series of [TableHeat1](tables.md#tableheat1) tables, each for one value of the first variable.

**Record format and fields**

`TableHeatTwoVariables;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the heat table namespace. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `table` | `integer` | — | Identifier or selection of the data table supplying this part of the function. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `tables` — there must be one table ID for each value of x.
- `x` — a table needs at least one pair.
- `x` — x must be a finite number.
- `x` — the values of x must be listed in ascending order.
- `tables` — a table ID must be a positive integer.

**Example record**

~~~text
TableHeatTwoVariables;44;0.;45;100.;46;EndTable
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 44`.

## TableMaterial1

A function y(x) for material properties (of temperature), given by points.

**Record format and fields**

`TableMaterial1;id;xAxisKind;yAxisKind;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material table namespace. |
| 2 | `xAxisKind` | `text` | — | Selects the x axis kind for TableMaterial1. |
| 3 | `yAxisKind` | `text` | — | Selects the y axis kind for TableMaterial1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must not be zero.

**Example record**

~~~text
TableMaterial1;31;;;0.;1.;300.;0.9;EndTable
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 31`.

## TableMaterial2

A function of x - X1 for material properties, given by points: y = yT(x - X1).

**Record format and fields**

`TableMaterial2;id;abscissaShift;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material table namespace. |
| 2 | `abscissaShift` | `real` | 0.0 | The table parameter: the value of x where the points' own x is 0. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must not be zero.

**Example record**

~~~text
TableMaterial2;103;0.;20.;1.;420.;1.02;EndTable
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 103`, `abscissaShift = 0.`.

## TableMaterial3

A function of (x - X1) / X2 for material properties, given by points: y = yT((x - X1) / X2).

**Record format and fields**

`TableMaterial3;id;abscissaShift;abscissaScale;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material table namespace. |
| 2 | `abscissaShift` | `real` | Required | The table parameters. |
| 3 | `abscissaScale` | `real` | Required | Scale applied to the independent axis of the table. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must not be zero.

**Example record**

~~~text
TableMaterial3;202;20.;100.;0.;1.;2.;1.1;4.;1.2;EndTable
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 202`, `abscissaShift = 20.`, `abscissaScale = 100.`.

## TableMaterial4

A polynomial for material properties, y = sum of Ai * ((x - X1) / X2)^i for i = 0 to N, where x is first brought into [X3, X4].

**Record format and fields**

`TableMaterial4;id;abscissaShift;abscissaScale;abscissaMinimum;abscissaMaximum;<coefficients>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material table namespace. |
| 2 | `abscissaShift` | `real` | Required | The table parameters. |
| 3 | `abscissaScale` | `real` | Required | Scale applied to the independent axis of the table. |
| 4 | `abscissaMinimum` | `real` | Required | Lower end of the interval on the independent axis. |
| 5 | `abscissaMaximum` | `real` | Required | Upper end of the interval on the independent axis. |

**Repeated group `coefficients`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `coefficient` | `any` | — | Coefficient value in the TableMaterial4 relation for coefficients. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must not be zero.

**Example record**

~~~text
TableMaterial4;104;20.;100.;0.;500.;1.;0.05;EndTable
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 104`, `abscissaShift = 20.`, `abscissaScale = 100.`, `abscissaMinimum = 0.`.

## TableModalDamping1

Modal damping as a function of natural frequency.

**Record format and fields**

`TableModalDamping1;id;kind;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the hybrid damping rotor options table namespace. |
| 2 | `kind` | `text` | StructuralDamping | Selects the kind for TableModalDamping1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `CriticalDamping`, `EndTable`, `Linear`, `Logarithmic`, `QualityFactor`, `Skip`, `StructuralDamping`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `frequency` — a natural frequency must not be negative.

**Example record**

~~~text
TableModalDamping1;1;CriticalDamping;0.;0.02;5.E+3;0.02;EndTable
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol112_channel_file_loads.oos)

Reading the example gives `id = 1`, `kind = CriticalDamping`.

## TableMultiVariable0

Represents a tabulated function of one independent variable.

**Record format and fields**

`TableMultiVariable0;id;kind;extrapolation;belowRangeTableId;aboveRangeTableId;smoothing;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `integer` | Required | Selects the kind for TableMultiVariable0. |
| 3 | `extrapolation` | `integer` | — | Specifies how to obtain a value outside the sampled range. |
| 4 | `belowRangeTableId` | `integer` | 0 | Table supplying the variation of below range. |
| 5 | `aboveRangeTableId` | `integer` | 0 | Table supplying the variation of above range. |
| 6 | `smoothing` | `integer` | 0 | Smoothing option for interpolation along the independent variable. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `abscissa` | `real` | — | Independent coordinate at which the function is sampled. |
| 2 | `ordinate` | `real` | — | Function value at the corresponding abscissa. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TableMultiVariable0;31;12;;;;;20.;1.E-12;200.;2.E-12
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 31`, `kind = 12`.

## TableMultiVariable1

Defines a function of up to four independent variables on a grid, with an ordered array of response values.

**Record format and fields**

`TableMultiVariable1;id;variableCount;kind1;kind2;kind3;kind4;valueCount1;valueCount2;valueCount3;valueCount4;extrapolation1;extrapolation2;extrapolation3;extrapolation4;belowRangeTableId1;aboveRangeTableId1;belowRangeTableId2;aboveRangeTableId2;belowRangeTableId3;aboveRangeTableId3;belowRangeTableId4;aboveRangeTableId4;smoothing1;smoothing2;smoothing3;smoothing4;<xValues1>;<xValues2>;<xValues3>;<xValues4>;<yValues>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `variableCount` | `integer` | — | Number of independent variables used in the definition. |
| 3 | `kind1` | `integer` | — | Kind of independent variable or interpolation dimension 1 in the table. |
| 4 | `kind2` | `integer` | — | Kind of independent variable or interpolation dimension 2 in the table. |
| 5 | `kind3` | `integer` | — | Kind of independent variable or interpolation dimension 3 in the table. |
| 6 | `kind4` | `integer` | — | Kind of independent variable or interpolation dimension 4 in the table. |
| 7 | `valueCount1` | `integer` | — | Number of value entries. |
| 8 | `valueCount2` | `integer` | — | Number of value entries. |
| 9 | `valueCount3` | `integer` | — | Number of value entries. |
| 10 | `valueCount4` | `integer` | — | Number of value entries. |
| 11 | `extrapolation1` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 1. |
| 12 | `extrapolation2` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 2. |
| 13 | `extrapolation3` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 3. |
| 14 | `extrapolation4` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 4. |
| 15 | `belowRangeTableId1` | `integer` | — | Table supplying the variation of below range. |
| 16 | `aboveRangeTableId1` | `integer` | — | Table supplying the variation of above range. |
| 17 | `belowRangeTableId2` | `integer` | — | Table supplying the variation of below range. |
| 18 | `aboveRangeTableId2` | `integer` | — | Table supplying the variation of above range. |
| 19 | `belowRangeTableId3` | `integer` | — | Table supplying the variation of below range. |
| 20 | `aboveRangeTableId3` | `integer` | — | Table supplying the variation of above range. |
| 21 | `belowRangeTableId4` | `integer` | — | Table supplying the variation of below range. |
| 22 | `aboveRangeTableId4` | `integer` | — | Table supplying the variation of above range. |
| 23 | `smoothing1` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 1. |
| 24 | `smoothing2` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 2. |
| 25 | `smoothing3` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 3. |
| 26 | `smoothing4` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 4. |

**Repeated group `xValues1`**. The field `valueCount1` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues1` | `real` | — | Coordinates in the independent-variable grid. Entry 1. |

**Repeated group `xValues2`**. The field `valueCount2` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues2` | `real` | — | Coordinates in the independent-variable grid. Entry 2. |

**Repeated group `xValues3`**. The field `valueCount3` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues3` | `real` | — | Coordinates in the independent-variable grid. Entry 3. |

**Repeated group `xValues4`**. The field `valueCount4` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues4` | `real` | — | Coordinates in the independent-variable grid. Entry 4. |

**Repeated group `yValues`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ordinate` | `real` | — | Function value at the corresponding abscissa. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TableMultiVariable1;41;2;73;12;;;2;2;;;;;;;;;;;;;;;;;;;0.;0.01;20.;200.;2.E+5;1.9E+5;1.8E+5;1.7E+5
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 41`, `variableCount = 2`, `kind1 = 73`, `kind2 = 12`.

## TableMultiVariable2

Defines a function of up to four variables by giving the coordinates of the grid and a function value for each grid point.

**Record format and fields**

`TableMultiVariable2;id;variableCount;kind1;kind2;kind3;kind4;valueCount1;valueCount2;valueCount3;valueCount4;extrapolation1;extrapolation2;extrapolation3;extrapolation4;belowRangeTableId1;aboveRangeTableId1;belowRangeTableId2;aboveRangeTableId2;belowRangeTableId3;aboveRangeTableId3;belowRangeTableId4;aboveRangeTableId4;smoothing1;smoothing2;smoothing3;smoothing4;<xValues1>;<xValues2>;<xValues3>;<xValues4>;<yValues>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `variableCount` | `integer` | — | Number of independent variables used in the definition. |
| 3 | `kind1` | `integer` | — | Kind of independent variable or interpolation dimension 1 in the table. |
| 4 | `kind2` | `integer` | — | Kind of independent variable or interpolation dimension 2 in the table. |
| 5 | `kind3` | `integer` | — | Kind of independent variable or interpolation dimension 3 in the table. |
| 6 | `kind4` | `integer` | — | Kind of independent variable or interpolation dimension 4 in the table. |
| 7 | `valueCount1` | `integer` | — | Number of value entries. |
| 8 | `valueCount2` | `integer` | — | Number of value entries. |
| 9 | `valueCount3` | `integer` | — | Number of value entries. |
| 10 | `valueCount4` | `integer` | — | Number of value entries. |
| 11 | `extrapolation1` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 1. |
| 12 | `extrapolation2` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 2. |
| 13 | `extrapolation3` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 3. |
| 14 | `extrapolation4` | `integer` | — | Specifies how to obtain a value outside the sampled range. Entry 4. |
| 15 | `belowRangeTableId1` | `integer` | — | Table supplying the variation of below range. |
| 16 | `aboveRangeTableId1` | `integer` | — | Table supplying the variation of above range. |
| 17 | `belowRangeTableId2` | `integer` | — | Table supplying the variation of below range. |
| 18 | `aboveRangeTableId2` | `integer` | — | Table supplying the variation of above range. |
| 19 | `belowRangeTableId3` | `integer` | — | Table supplying the variation of below range. |
| 20 | `aboveRangeTableId3` | `integer` | — | Table supplying the variation of above range. |
| 21 | `belowRangeTableId4` | `integer` | — | Table supplying the variation of below range. |
| 22 | `aboveRangeTableId4` | `integer` | — | Table supplying the variation of above range. |
| 23 | `smoothing1` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 1. |
| 24 | `smoothing2` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 2. |
| 25 | `smoothing3` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 3. |
| 26 | `smoothing4` | `integer` | — | Selects the treatment of variation between adjacent table samples. Entry 4. |

**Repeated group `xValues1`**. The field `valueCount1` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues1` | `real` | — | Coordinates in the independent-variable grid. Entry 1. |

**Repeated group `xValues2`**. The field `valueCount2` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues2` | `real` | — | Coordinates in the independent-variable grid. Entry 2. |

**Repeated group `xValues3`**. The field `valueCount3` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues3` | `real` | — | Coordinates in the independent-variable grid. Entry 3. |

**Repeated group `xValues4`**. The field `valueCount4` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `variableValues4` | `real` | — | Coordinates in the independent-variable grid. Entry 4. |

**Repeated group `yValues`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ordinate` | `real` | — | Function value at the corresponding abscissa. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TableMultiVariable2;42;2;73;12;;;2;2;;;;;;;;;;;;;;;;;;;0.;0.01;20.;200.;1.5E+5;1.45E+5;1.4E+5;1.35E+5
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 42`, `variableCount = 2`, `kind1 = 73`, `kind2 = 12`.

## TableRandomSpectrum1

A power spectral density as a function of frequency, G(F), for random analysis (referenced by the [RandomSpectralDensity](dynamics.md#randomspectraldensity) cards).

**Record format and fields**

`TableRandomSpectrum1;id;xAxisKind;yAxisKind;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the random table namespace. |
| 2 | `xAxisKind` | `text` | — | Selects the x axis kind for TableRandomSpectrum1. |
| 3 | `yAxisKind` | `text` | — | Selects the y axis kind for TableRandomSpectrum1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `x` — the table needs at least two points.
- `frequency` — a frequency must not be negative.

**Example record**

~~~text
TableRandomSpectrum1;92;;;1.;1.;5.E+3;1.;EndTable
~~~

[Model containing this record](../../../validation/models/results_dynamics/acoustic_fluid_phase_random.oos)

Reading the example gives `id = 92`.

## TableScattered3D

Represents a function sampled at scattered points in three dimensions for a general coordinate system.

**Record format and fields**

`TableScattered3D;id;xOffset;yOffset;zOffset;valueOffset;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `xOffset` | `real` | 0.0 | Additive shift in the x coordinate of the tabulated function. |
| 3 | `yOffset` | `real` | 0.0 | Additive shift in the y coordinate of the tabulated function. |
| 4 | `zOffset` | `real` | 0.0 | Additive shift in the z coordinate of the tabulated function. |
| 5 | `valueOffset` | `real` | 0.0 | Additive shift to the value before it is used. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pointX` | `any` | — | X coordinate of the specified point. |
| 2 | `pointY` | `real` | — | Y coordinate of the specified point. |
| 3 | `pointZ` | `real` | — | Z coordinate of the specified point. |
| 4 | `pointValue` | `real` | — | Function value stored at this grid point. |

Accepted words: `Constant`, `Element`, `EndTable`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `pointX` — the table needs at least two points.
- `pointX` — the coordinates and the values of a point must be finite numbers.

**Example record**

~~~text
TableScattered3D;112;;;;;0.;0.;5.;0.;10.;0.;5.;0.;0.;10.;5.;0.;10.;10.;5.;0.;EndTable
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol101_layered_solid_cord3g.oos)

Reading the example gives `id = 112`.

## TableStress1

A function y(x) for stress dependent material properties (the stress-strain curve of an [IsoMatStressDependent](materials.md#isomatstressdependent), the creep parameters of a [CreepMat](materials.md#creepmat), the test data of a [HyperelasticPolynomialMat](materials.md#hyperelasticpolynomialmat)), given by points.

**Record format and fields**

`TableStress1;id;kind;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the stress table namespace. |
| 2 | `kind` | `integer` | 1 | Selects the kind for TableStress1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `x` | `any` | — | Independent sample coordinate along the table axis. |
| 2 | `y` | `real` | — | Tabulated response at the corresponding independent coordinate. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.

**Example record**

~~~text
TableStress1;402;;0.08;0.;0.15;35.;EndTable
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 402`.

## TableStressTemperature

The stress dependent tables of a nonlinear elastic material at several temperatures.

**Record format and fields**

`TableStressTemperature;id;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the stress table namespace. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `temperature` | `any` | — | Thermal state at the corresponding point or sample, in the selected temperature scale. |
| 2 | `table` | `integer` | — | Identifier or selection of the data table supplying this part of the function. |

Accepted words: `EndTable`, `Linear`, `Logarithmic`, `Skip`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the table ID must be a positive integer.
- `tables` — there must be one table ID for each temperature.
- `temperatures` — a table needs at least one temperature.
- `temperatures` — a temperature must be a finite number.
- `temperatures` — the temperatures must be listed in ascending order.
- `tables` — a table ID must be a positive integer.

**Example record**

~~~text
TableStressTemperature;13;20.;11;200.;12;EndTable
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 13`.

## TableTimeHistoryFile

Defines a function of time using a channel in an external history file identified by [UserFileName](solution_control.md#userfilename).

**Record format and fields**

`TableTimeHistoryFile;id;xAxisKind;yAxisKind;externalFileId;fileType;channel;totalTime;punch;<windows>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `xAxisKind` | `text` | Linear | Selects the x axis kind for TableTimeHistoryFile. |
| 3 | `yAxisKind` | `text` | Linear | Selects the y axis kind for TableTimeHistoryFile. |
| 4 | `externalFileId` | `integer` | Required | Identifier addressing user defined name data. |
| 5 | `fileType` | `text` | — | Selects the file type for TableTimeHistoryFile. |
| 6 | `channel` | `integer` | — | Channel of the external data file supplying the sampled history. |
| 7 | `totalTime` | `real` | — | Total time (time). |
| 8 | `punch` | `text` | No | Controls writing the selected table data as text records. |

**Repeated group `windows`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `windowStart` | `any` | — | Beginning of the interval retained from the input history. |
| 2 | `windowEnd` | `any` | — | End of the interval retained from the input history. |

Accepted words: `Constant`, `DataAcquisitionFile`, `Element`, `EndTable`, `Linear`, `LoadHistoryFile`, `Logarithmic`, `No`, `Skip`, `Table`, `Yes`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `windowStart` — the times of the pairs must be finite numbers.

**Example record**

~~~text
TableTimeHistoryFile;11;;;1;LoadHistoryFile;1;;;0.;2.;EndTable
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol112_channel_file_loads.oos)

Reading the example gives `id = 11`, `externalFileId = 1`, `fileType = LoadHistoryFile`, `channel = 1`.

## TableUserRoutine

A function that a user subroutine computes where a table would give it, so that a card of the explicit solver can name it by number like a table.

**Record format and fields**

`TableUserRoutine;id;groupName;routineName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the dynamic table namespace. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `routineName` | `text` | ExternalFunction | Text naming the routine. |

Accepted words: `Constant`, `Element`, `ExternalFunction`, `Table`.

**Example record**

~~~text
TableUserRoutine;81;myfunc;ExternalFunction
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 81`, `groupName = myfunc`, `routineName = ExternalFunction`.
