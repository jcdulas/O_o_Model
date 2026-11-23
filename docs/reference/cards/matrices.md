# Matrices

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## DirectMatrix

Either the header of a matrix (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrix: header

Form `header`, when `columnIndex` is `0`.

`DirectMatrix;entryName;columnIndex;matrixForm;inputType;outputType;rowCount;columnCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `columnIndex` | `integer` | Required | Column of the matrix to which the following terms belong. |
| 3 | `matrixForm` | `integer` | Required | Matrix organization, including the assumed relation between its rows and columns. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrix. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrix. |
| 6 | `rowCount` | `integer` | Required | Number of row entries. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

### DirectMatrix: column

Form `column`, for every other record.

`DirectMatrix;entryName;columnIndex;firstRow;<values>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `columnIndex` | `integer` | Required | Column of the matrix to which the following terms belong. |
| 3 | `firstRow` | `integer` | Required | Row at which the supplied matrix data begin. |

**Repeated group `values`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `value` | `any` | — | Scalar or literal data attached to the current entry; its kind is given in the type column. |

*Note*: a value of a column is a real (the element of the next row), an integer (the row of the element that follows) or THRU then a row (the element above repeated down to it).

Accepted words: `AeroPressureMatrix`, `AeroWeightingFactor`, `AeroWeightingMatrix`, `DownwashMatrix`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `columnIndex` — a header card has no column elements.
- `value` — an element of the matrix must be a finite number.
- `row` — a row number must be a positive integer.

**Example record**

~~~text
DirectMatrix;DownwashMatrix;0;2;1;0;32;1
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_direct_matrices.oos)

## DirectMatrixAeroJ

Either the header of a matrix at the js-set of the aerodynamic mesh (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrixAeroJ: header

Form `header`, when `nodeJ` is `0`.

`DirectMatrixAeroJ;entryName;nodeJ;matrixShape;inputType;outputType;polarFlag;columnCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `matrixShape` | `integer` | Required | Shape or symmetry convention used to interpret the stored matrix entries. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrixAeroJ. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrixAeroJ. |
| 6 | `polarFlag` | `integer` | 0 | Selects the polar flag for DirectMatrixAeroJ. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

### DirectMatrixAeroJ: column

Form `column`, for every other record.

`DirectMatrixAeroJ;entryName;nodeJ;componentsJ;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 4 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

Accepted words: `AeroPressureMatrix`, `DownwashMatrix`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeJ` — a header card has no column or terms.
- `node` — a mesh point identification number must be a positive integer.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (B is blank).

**Example record**

~~~text
DirectMatrixAeroJ;DWJ;0;9;1;0;;1
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

## DirectMatrixAeroJInterference

Either the header of a matrix at the js-set of the aerodynamic mesh of the interference body of a [AeroBody2](aero.md#aerobody2) (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrixAeroJInterference: header

Form `header`, when `nodeJ` is `0`.

`DirectMatrixAeroJInterference;entryName;nodeJ;matrixShape;inputType;outputType;polarFlag;columnCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `matrixShape` | `integer` | Required | Shape or symmetry convention used to interpret the stored matrix entries. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrixAeroJInterference. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrixAeroJInterference. |
| 6 | `polarFlag` | `integer` | 0 | Selects the polar flag for DirectMatrixAeroJInterference. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

### DirectMatrixAeroJInterference: column

Form `column`, for every other record.

`DirectMatrixAeroJInterference;entryName;nodeJ;componentsJ;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 4 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

Accepted words: `AeroPressureMatrix`, `DownwashMatrix`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeJ` — a header card has no column or terms.
- `node` — a mesh point identification number must be a positive integer.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (B is blank).

**Example record**

~~~text
DirectMatrixAeroJInterference;DWJI;0;9;1;0;;1
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_body_downwash.oos)

## DirectMatrixAeroK

Either the header of a matrix at the ks-set of the aerodynamic mesh (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrixAeroK: header

Form `header`, when `nodeJ` is `0`.

`DirectMatrixAeroK;entryName;nodeJ;matrixShape;inputType;outputType;polarFlag;columnCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `matrixShape` | `integer` | Required | Shape or symmetry convention used to interpret the stored matrix entries. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrixAeroK. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrixAeroK. |
| 6 | `polarFlag` | `integer` | 0 | Selects the polar flag for DirectMatrixAeroK. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

### DirectMatrixAeroK: column

Form `column`, for every other record.

`DirectMatrixAeroK;entryName;nodeJ;componentsJ;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Grid point identifier at connectivity position J. |
| 3 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 4 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

Accepted words: `AeroWeightingFactor`, `AeroWeightingMatrix`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeJ` — a header card has no column or terms.
- `node` — a mesh point identification number must be a positive integer.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (B is blank).

**Example record**

~~~text
DirectMatrixAeroK;FRCK;0;9;1;0;;1
~~~

[Model containing this record](../../../validation/models/linear_loads/aero_direct_matrices.oos)

## DirectMatrixAxisym

The matrix input of an axisymmetric analysis (a model with an [AxisymFluidControl](nodes.md#axisymfluidcontrol) entry), either the header of a matrix (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrixAxisym: header

Form `header`, when `nodeJ` is `0`.

`DirectMatrixAxisym;entryName;nodeJ;matrixShape;inputType;outputType`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `matrixShape` | `integer` | Required | Shape or symmetry convention used to interpret the stored matrix entries. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrixAxisym. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrixAxisym. |

### DirectMatrixAxisym: column

Form `column`, for every other record.

`DirectMatrixAxisym;entryName;nodeJ;componentsJ;harmonicJ;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 4 | `harmonicJ` | `integer` | — | Harmonic index of the matrix column or second quantity. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `harmonic` | `integer` | — | Index identifying the spatial or temporal harmonic. |
| 4 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 5 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeJ` — a header card has no column or terms.
- `node` — a point identification number must be a positive integer.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (B is blank).

**Example record**

~~~text
DirectMatrixAxisym;KTOP;602;1;;602;1;;100.
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

## DirectMatrixNodal

Either the header of a matrix (the second field is the integer 0) or one column of it.

**Record format and fields**

Forms: `header`, `column`.

### DirectMatrixNodal: header

Form `header`, when `nodeJ` is `0`.

`DirectMatrixNodal;entryName;nodeJ;matrixShape;inputType;outputType;polarFlag;columnCount`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `matrixShape` | `integer` | Required | Shape or symmetry convention used to interpret the stored matrix entries. |
| 4 | `inputType` | `integer` | Required | Selects the input type for DirectMatrixNodal. |
| 5 | `outputType` | `integer` | 0 | Selects the output type for DirectMatrixNodal. |
| 6 | `polarFlag` | `integer` | 0 | Selects the polar flag for DirectMatrixNodal. |
| 7 | `columnCount` | `integer` | 0 | Number of column entries. |

### DirectMatrixNodal: column

Form `column`, for every other record.

`DirectMatrixNodal;entryName;nodeJ;componentsJ;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `nodeJ` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 3 | `componentsJ` | `integer` | 0 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |
| 3 | `realValue` | `real` | — | Real scalar value or real part of the complex quantity. |
| 4 | `imaginaryValue` | `real` | — | Imaginary part paired with the real component. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeJ` — a header card has no column or terms.
- `node` — a grid, scalar or extra point ID must be a positive integer.
- `realValue` — a term of the matrix must be a finite number.
- `imaginaryValue` — a column of a real matrix has no imaginary parts (B is blank).

**Example record**

~~~text
DirectMatrixNodal;PLDS;0;9;1;0;;13
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

## DirectTable

Supplies a record of user data to a named table, preserving the order of its fields.

**Record format and fields**

`DirectTable;entryName;recordNumber;<recordValues>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `recordNumber` | `integer` | Required | Index identifying the record in the containing table or file. |

**Repeated group `recordValues`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `recordValue` | `any` | — | Value stored at the current table record and position. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `values` — a value must be a finite number.
- `values` — a word value is empty.
- `values` — a record must end with a nonblank value.

**Example record**

~~~text
DirectTable;INDTA;1;33;17;34;14;ENDREC
~~~

[Model containing this record](../../../validation/models/linear_loads/static_load_forms.oos)

Reading the example gives `entryName = INDTA`, `recordNumber = 1`.

## MonitorChordNormalCoeffs

A monitor point of the stripwise normal force and pitching moment coefficients of the chordwise strips of [AeroLiftingPanel1](aero.md#aeroliftingpanel1) panels (flutter and aeroelastic response).

**Record format and fields**

`MonitorChordNormalCoeffs;entryName;label;momentChordFraction;<aeroPanelIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `momentChordFraction` | `real` | 0.25 | Position of the moment reference along the chord, as a fraction of its length. |

**Repeated group `aeroPanelIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `aeroPanelId` | `any` | — | Identifier selecting the aero panel record or set. |

Accepted words: `All`, `Constant`, `Element`, `Table`.

**Example record**

~~~text
MonitorChordNormalCoeffs;WINGCN;strip coefficients of the wing;0.25;1001
~~~

[Model containing this record](../../../validation/models/aero_models/sol144_user_controllers.oos)

Reading the example gives `entryName = WINGCN`, `label = strip coefficients of the wing`, `momentChordFraction = 0.25`.

## MonitorDisplacement

A displacement monitor point.

**Record format and fields**

`MonitorDisplacement;entryName;label;outputAxes;component;positionFrameId;xCoord;yCoord;zCoord;displacementFrameId;sampledComponents`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `outputAxes` | `integer` | Required | The components to monitor: digits 1 to 6, each at most once. |
| 4 | `component` | `text` | — | Degree of freedom or response component addressed by this term. |
| 5 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 6 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 7 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 8 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 9 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |
| 10 | `sampledComponents` | `integer` | — | The components of the grids that define the point. |

**Example record**

~~~text
MonitorDisplacement;TIPDSP;tip displacement;3;WINGS;0;200.;1.E+3;0.
~~~

[Model containing this record](../../../validation/models/aero_sol144/aero_model.oos)

Reading the example gives `entryName = TIPDSP`, `label = tip displacement`, `outputAxes = 3`, `component = WINGS`.

## MonitorElemLoad2

An internal load monitor point.

**Record format and fields**

`MonitorElemLoad2;entryName;label;resultTable;kind;resultItem;elemId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `resultTable` | `text` | — | Stress, Force or Strain. |
| 4 | `kind` | `text` | — | Selects the kind for MonitorElemLoad2. |
| 5 | `resultItem` | `text` | — | Identifies the result quantity included in the selection. |
| 6 | `elemId` | `integer` | 0 | Identifier of the element addressed by this record. |

Accepted words: `Force`, `Strain`, `Stress`.

**Example record**

~~~text
MonitorElemLoad2;M2BMX;bending moment x of the root element;Force;ShellQuad4;BMX;1201
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `entryName = M2BMX`, `label = bending moment x of the root element`, `resultTable = Force`, `kind = ShellQuad4`.

## MonitorGroup

A collection of monitor points that is available to the postprocessing.

**Record format and fields**

`MonitorGroup;groupName;label;<members>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |

**Repeated group `members`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberName` | `text` | — | Text naming the member. |
| 2 | `monitorClass` | `text` | — | Class of monitored quantity selected by this entry. |
| 3 | `realAttribute` | `real` | — | Payload passed in the declared type and order to the consumer of the record. |
| 4 | `integerAttribute` | `integer` | — | Payload passed in the declared type and order to the consumer of the record. |
| 5 | `textAttribute` | `text` | — | Payload passed in the declared type and order to the consumer of the record. Written as one text field. |

Accepted words: `AeroMonitorDisplacement`, `AeroMonitorIntegratedLoad`, `Constant`, `Element`, `MonitorElemLoad2`, `MonitorNodeForceSum3`, `StructMonitorDisplacement`, `StructMonitorIntegratedLoad`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `memberName` — a monitor group needs at least one `memberName`.
- `monitorClass` — the aerodynamic and the structural monitor points cannot be mixed in a group.

**Example record**

~~~text
MonitorGroup;PANEL;monitor points of the panel;M3CUT20;MonitorNodeForceSum3;20.;;CUT20;M3CUT40;MonitorNodeForceSum3;40.;;CUT40;M2SX;MonitorElemLoad2;;1201;ROOTSX;M2BMX;MonitorElemLoad2;;1201;ROOTBMX
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `groupName = PANEL`, `label = monitor points of the panel`.

## MonitorIntegratedLoad1

An integrated load monitor point.

**Record format and fields**

`MonitorIntegratedLoad1;entryName;label;outputAxes;component;positionFrameId;xCoord;yCoord;zCoord;displacementFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `outputAxes` | `integer` | Required | The components to monitor: digits 1 to 6, each at most once. |
| 4 | `component` | `text` | — | Degree of freedom or response component addressed by this term. |
| 5 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 6 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 7 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 8 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 9 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |

**Example record**

~~~text
MonitorIntegratedLoad1;ROOTS;wing root on the structure;123456;WINGS;0;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/aero_sol144/aero_model.oos)

Reading the example gives `entryName = ROOTS`, `label = wing root on the structure`, `outputAxes = 123456`, `component = WINGS`.

## MonitorNodeForceSum3

An integrated load monitor point that sums selected grid point forces.

**Record format and fields**

`MonitorNodeForceSum3;entryName;label;outputAxes;nodeSetId;elementSetId;positionFrameId;xCoord;yCoord;zCoord;excludedForces;displacementFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `outputAxes` | `integer` | Required | The components to sum: digits 1 to 6, each at most once. |
| 4 | `nodeSetId` | `integer` | Required | Identifier of the set supplying the grid points. |
| 5 | `elementSetId` | `integer` | 0 | Identifier addressing set data. |
| 6 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 7 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 8 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 9 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 10 | `excludedForces` | `text` | — | Force contributions to omit from the requested result. |
| 11 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |

Accepted words: `AlphaLetter`.

**Example record**

~~~text
MonitorNodeForceSum3;M3ALPHA;cut at x 40 no element set;123456;71;;0;40.;10.;0.
~~~

[Model containing this record](../../../validation/models/cuts_monitor_points/cuts_model.oos)

Reading the example gives `entryName = M3ALPHA`, `label = cut at x 40 no element set`, `outputAxes = 123456`, `nodeSetId = 71`.

## MonitorSum

A new monitor result that is the weighted sum of existing monitor results (the SOLs that have monitor points: 101, 103, 108, 109, 111, 112, 144, 146, 200 and 400).

**Record format and fields**

Forms: `typeFirst`, `axesFirst`.

### MonitorSum: typeFirst

Form `typeFirst`, when `termType` is a word.

`MonitorSum;entryName;label;<lines>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |

**Repeated group `lines`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `termType` | `text` | — | Selects the term type for lines. |
| 2 | `newAxes` | `integer` | — | Axes of the transformed or newly formed response. |
| 3 | `termNames` | `text` | — | Names identifying the contributing terms. |
| 4 | `termAxes` | `integer` | — | Axes in which the components of the contributing term are resolved. |
| 5 | `termCoefficient` | `real` | — | Coefficient in the relation for term. |
| 6 | `secondTermNames` | `text` | — | Names identifying the second set of contributing terms. |
| 7 | `secondTermAxes` | `integer` | — | Axes used to resolve the second contributing term. |
| 8 | `secondTermCoefficient` | `real` | — | Coefficient in the relation for second term. |

### MonitorSum: axesFirst

Form `axesFirst`, for every other record.

`MonitorSum;entryName;label;<lines>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |

**Repeated group `lines`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `newAxes` | `integer` | — | Axes of the transformed or newly formed response. |
| 2 | `termType` | `text` | — | Selects the term type for lines. |
| 3 | `termNames` | `text` | — | Names identifying the contributing terms. |
| 4 | `termAxes` | `integer` | — | Axes in which the components of the contributing term are resolved. |
| 5 | `termCoefficient` | `real` | — | Coefficient in the relation for term. |
| 6 | `secondTermNames` | `text` | — | Names identifying the second set of contributing terms. |
| 7 | `secondTermAxes` | `integer` | — | Axes used to resolve the second contributing term. |
| 8 | `secondTermCoefficient` | `real` | — | Coefficient in the relation for second term. |

Accepted words: `AeroMonitorDisplacement`, `AeroMonitorIntegratedLoad`, `Constant`, `Element`, `MonitorNodeForceSum3`, `StructMonitorDisplacement`, `StructMonitorIntegratedLoad`, `Table`.

**Example record**

~~~text
MonitorSum;M3DIFF;difference of the panel cuts;123;MonitorNodeForceSum3;M3CUT20;123;1.;M3CUT40;123;-1.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

## MonitorSumLocated

A new monitor result that is the weighted sum of existing monitor results, with a location.

**Record format and fields**

Forms: `typeFirst`, `axesFirst`.

### MonitorSumLocated: typeFirst

Form `typeFirst`, when `termType` is a word.

`MonitorSumLocated;entryName;label;positionFrameId;xCoord;yCoord;zCoord;displacementFrameId;<lines>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 5 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 6 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 7 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |

**Repeated group `lines`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `termType` | `text` | — | Selects the term type for lines. |
| 2 | `newAxes` | `integer` | — | Axes of the transformed or newly formed response. |
| 3 | `termNames` | `text` | — | Names identifying the contributing terms. |
| 4 | `termAxes` | `integer` | — | Axes in which the components of the contributing term are resolved. |
| 5 | `termCoefficient` | `real` | — | Coefficient in the relation for term. |
| 6 | `secondTermNames` | `text` | — | Names identifying the second set of contributing terms. |
| 7 | `secondTermAxes` | `integer` | — | Axes used to resolve the second contributing term. |
| 8 | `secondTermCoefficient` | `real` | — | Coefficient in the relation for second term. |

### MonitorSumLocated: axesFirst

Form `axesFirst`, for every other record.

`MonitorSumLocated;entryName;label;positionFrameId;xCoord;yCoord;zCoord;displacementFrameId;<lines>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 4 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 5 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 6 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 7 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |

**Repeated group `lines`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `newAxes` | `integer` | — | Axes of the transformed or newly formed response. |
| 2 | `termType` | `text` | — | Selects the term type for lines. |
| 3 | `termNames` | `text` | — | Names identifying the contributing terms. |
| 4 | `termAxes` | `integer` | — | Axes in which the components of the contributing term are resolved. |
| 5 | `termCoefficient` | `real` | — | Coefficient in the relation for term. |
| 6 | `secondTermNames` | `text` | — | Names identifying the second set of contributing terms. |
| 7 | `secondTermAxes` | `integer` | — | Axes used to resolve the second contributing term. |
| 8 | `secondTermCoefficient` | `real` | — | Coefficient in the relation for second term. |

Accepted words: `AeroMonitorDisplacement`, `AeroMonitorIntegratedLoad`, `Constant`, `Element`, `MonitorNodeForceSum3`, `StructMonitorDisplacement`, `StructMonitorIntegratedLoad`, `Table`.

**Example record**

~~~text
MonitorSumLocated;M3AVG;average of the panel cuts at mid panel;10;100.;30.;20.;20;123456;MonitorNodeForceSum3;M3CUT20;123456;0.5;M3CUT40;123456;0.5
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

## MonitorSumTotal

Combines monitored forces and moments and transfers the moments to a common reference point.

**Record format and fields**

`MonitorSumTotal;entryName;label;outputAxes;positionFrameId;xCoord;yCoord;zCoord;displacementFrameId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryName` | `text` | — | Name identifying the associated item in the list. |
| 2 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. Written as one text field. |
| 3 | `outputAxes` | `integer` | — | The components of the new result: digits 1 to 6, each at most once. |
| 4 | `positionFrameId` | `integer` | 0 | Coordinate system used to interpret the position coordinates. |
| 5 | `xCoord` | `real` | 0.0 | X coordinate of the location in the specified frame. |
| 6 | `yCoord` | `real` | 0.0 | Y coordinate of the location in the specified frame. |
| 7 | `zCoord` | `real` | 0.0 | Z coordinate of the location in the specified frame. |
| 8 | `displacementFrameId` | `integer` | same as positionFrameId | Coordinate system in which the displacement components are expressed. |

**Keyed sections in `memberLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `AeroMonitorIntegratedLoad`**

**Repeated group `members`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberName` | `text` | — | Text naming the member. |

**Section `StructMonitorIntegratedLoad`**

**Repeated group `members`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberName` | `text` | — | Text naming the member. |

**Section `MonitorNodeForceSum3`**

**Repeated group `members`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberName` | `text` | — | Text naming the member. |

Accepted words: `AeroMonitorDisplacement`, `AeroMonitorIntegratedLoad`, `Constant`, `Element`, `MonitorNodeForceSum3`, `StructMonitorDisplacement`, `StructMonitorIntegratedLoad`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `entryName` — at least one monitor result to sum is required.

**Example record**

~~~text
MonitorSumTotal;M3MOVE;sum of the panel cuts moved to mid panel;123456;10;100.;30.;20.;0;MonitorNodeForceSum3;2;M3CUT20;M3CUT40
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `entryName = M3MOVE`, `label = sum of the panel cuts moved to mid panel`, `outputAxes = 123456`, `positionFrameId = 10`.

## MonteCarloParams

The parameters of a Monte-Carlo simulation by the non-parametric variability method.

**Record format and fields**

`MonteCarloParams;id;variabilityType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `variabilityType` | `text` | AlphaVariation | Selects the variability type for MonteCarloParams. |

**Keyed sections in `variabilities`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `StructuralVariation`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `structuralMassVariability` | `real` | — | Variation assigned to the Mass contribution of the structural subsystem. |
| 2 | `structuralStiffnessVariability` | `real` | — | Variation assigned to the Stiffness contribution of the structural subsystem. |
| 3 | `structuralDampingVariability` | `real` | — | Variation assigned to the Damping contribution of the structural subsystem. |

**Section `FluidVariation`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fluidMassVariability` | `real` | — | Variation assigned to the Mass contribution of the fluid subsystem. |
| 2 | `fluidStiffnessVariability` | `real` | — | Variation assigned to the Stiffness contribution of the fluid subsystem. |
| 3 | `fluidDampingVariability` | `real` | — | Variation assigned to the Damping contribution of the fluid subsystem. |

Accepted words: `AlphaVariation`, `BodyForceVariation`, `BulkSpeedVariation`, `Constant`, `DeltaVariation`, `Element`, `FluidVariation`, `MassFactorVariation`, `MassScaleVariation`, `StiffnessFactorVariation`, `StiffnessScaleVariation`, `StructuralVariation`, `Table`.

**Example record**

~~~text
MonteCarloParams;1;;StructuralVariation;0.01;0.01;0.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/monte_carlo_frequency.oos)

Reading the example gives `id = 1`.
