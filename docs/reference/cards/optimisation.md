# Design and optimization

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## DesignBeadRegion

A design region of a topography (bead or stamp) optimisation: the nodes of the elements of one property, which the beads of the given size move.

**Record format and fields**

`DesignBeadRegion;id;propType;propId;minWidth;maxHeight;angle;bufferZone;skippedNodes;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propType` | `text` | — | Selects the property type for DesignBeadRegion. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `minWidth` | `real` | Required | Minimum width (length). |
| 5 | `maxHeight` | `real` | Required | Maximum permitted height in the design region (length). |
| 6 | `angle` | `real` | Required | Angular position or orientation relative to the reference on this card. |
| 7 | `bufferZone` | `text` | Yes | Extent of the transition zone surrounding the selected design region. |
| 8 | `skippedNodes` | `text` | Both | Grid points excluded from the operation on the design region. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `directionX` | `real` | — | X component of the specified direction vector in its reference frame. |
| 2 | `directionY` | `real` | — | Y component of the specified direction vector in its reference frame. |
| 3 | `directionZ` | `real` | — | Z component of the specified direction vector in its reference frame. |
| 4 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 5 | `lowerBound` | `real` | — | Lower limit expressed in the same units as the bounded quantity. |
| 6 | `upperBound` | `real` | — | Upper limit expressed in the same units as the bounded quantity. |
| 7 | `designVarMoveLimit` | `real` | — | Limits the change allowed for this design variable in one optimization update. |

**Section `Nodes`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `excludedNodeSetId` | `integer` | — | Identifier selecting the excluded node set record or set. |
| 2 | `addedNodeSetId` | `integer` | — | Identifier selecting the added node set record or set. |

Accepted words: `Both`, `BoundaryCondition`, `CompProp`, `CompPropGlobal`, `Constant`, `DesignVar`, `Element`, `ElementNormals`, `Load`, `No`, `Nodes`, `None`, `ShearPanelProp`, `ShellProp`, `Table`, `Yes`.

**Example record**

~~~text
DesignBeadRegion;3;ShellProp;3;20.;4.;60.;;;DesignVar;ElementNormals;;;;-1.;1.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_topology_topometry_topography.oos)

Reading the example gives `id = 3`, `propType = ShellProp`, `propId = 3`, `minWidth = 20.`.

## DesignBoundaryShape

A boundary shape vector, as a combination of the vectors that the load sequences of an auxiliary model give.

**Record format and fields**

`DesignBoundaryShape;designVarId;auxiliaryModified;column1;scaleFactor1;column2;scaleFactor2;column3;scaleFactor3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | Required | Identifier of the design variable supplying the independent value. |
| 2 | `auxiliaryModified` | `integer` | Required | Selection controlling how the auxiliary design data are modified. |
| 3 | `column1` | `integer` | — | Column identifier for contribution 1 of the displacement or shape basis. |
| 4 | `scaleFactor1` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 1. |
| 5 | `column2` | `integer` | — | Column identifier for contribution 2 of the displacement or shape basis. |
| 6 | `scaleFactor2` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 2. |
| 7 | `column3` | `integer` | — | Column identifier for contribution 3 of the displacement or shape basis. |
| 8 | `scaleFactor3` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 3. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignBoundaryShape;1;1;10;1.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/shape_boundary_bndgrid.oos)

Reading the example gives `designVarId = 1`, `auxiliaryModified = 1`, `column1 = 10`, `scaleFactor1 = 1.`.

## DesignConstants

Named real constants for the equations of the design relations and responses.

**Record format and fields**

`DesignConstants;<entries>`

This part of the record has no fixed fields.

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 2 | `constantValue` | `number` | — | Fixed value entering the design relation or response. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `label` — at least one constant is required.

**Example record**

~~~text
DesignConstants;KI1;0.5;KI2;0.01389;RATIO;6.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

## DesignConstr

The bounds of one response, in a set of design constraints.

**Record format and fields**

`DesignConstr;constraintSetId;responseId;lowerAllowable;lowerAllowableTableId;upperAllowable;upperAllowableTableId;lowFrequency;highFrequency`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constraintSetId` | `integer` | Required | Identifier selecting the constraint set record or set. |
| 2 | `responseId` | `integer` | Required | Identifier selecting the response record or set. |
| 3 | `lowerAllowable` | `real` | -1.0e20 | Lower admissible value of the constrained response. Alternative to `lowerAllowableTableId`. |
| 4 | `lowerAllowableTableId` | `integer` | — | Table supplying the variation of lower allowable. Alternative to `lowerAllowable`. |
| 5 | `upperAllowable` | `real` | 1.0e20 | Upper admissible value of the constrained response. Alternative to `upperAllowableTableId`. |
| 6 | `upperAllowableTableId` | `integer` | — | Table supplying the variation of upper allowable. Alternative to `upperAllowable`. |
| 7 | `lowFrequency` | `real` | 0.0 | Low frequency (inverse time). |
| 8 | `highFrequency` | `real` | 1.0e20 | High frequency (inverse time). |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignConstr;31;22;-1.;;1.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/shape_boundary_bndgrid.oos)

Reading the example gives `constraintSetId = 31`, `responseId = 22`, `lowerAllowable = -1.`, `upperAllowable = 1.`.

## DesignConstrScreen

The screening of the constraints of one response type, to the most critical ones.

**Record format and fields**

`DesignConstrScreen;responseKind;threshold;maxRetained`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `responseKind` | `text` | — | Selects the response kind for DesignConstrScreen. |
| 2 | `threshold` | `real` | -0.5 | Value at which the selected test changes state. |
| 3 | `maxRetained` | `integer` | 20 | Maximum number of responses or constraints kept by the screening operation. |

Accepted words: `AbsoluteDisplacement`, `AbsoluteStress`, `AcousticFieldIntensity`, `AcousticFieldPressure`, `AcousticFieldVelocity`, `AcousticIntensity`, `AcousticPower`, `All`, `BucklingFactor`, `ComplexEigenvalue`, `Compliance`, `CompositeFailure`, `CompositeStrain`, `CompositeStrengthRatio`, `CompositeStress`, `Constant`, `ConstraintForce`, `ContourDisplacement`, `ContourForce`, `CutLoad`, `DeflectionToThickness`, `DesignResp3`, `Displacement`, `Divergence`, `DynamicStiffness`, `Eigenvalue`, `Element`, `Equation`, `Fatigue`, `Flutter`, `Force`, `FractionalMass`, `FreqAcceleration`, `FreqConstraintForce`, `FreqDisplacement`, `FreqFatigue`, `FreqForce`, `FreqStress`, `FreqVelocity`, `Frequency`, `MeanDisplacement`, `NodeForce`, `NodeForcePanel`, `Pressure`, `RadiatedPower`, `RootMeanSquareAcceleration`, `RootMeanSquareDisplacement`, `RootMeanSquareVelocity`, `Rotation`, `SectionLoad`, `SpectralAcceleration`, `SpectralDisplacement`, `SpectralVelocity`, `StabilityDerivative`, `Strain`, `StrainEnergy`, `Stress`, `Table`, `TotalCompliance`, `TotalStrainEnergy`, `TransientAcceleration`, `TransientConstraintForce`, `TransientDisplacement`, `TransientForce`, `TransientStress`, `TransientVelocity`, `TrimVariable`, `Volume`, `Weight`, `WeightPerPropertyId`.

Accepted parameter names: `RetainedConstraintCount`, `ScreeningThreshold`.

**Example record**

~~~text
DesignConstrScreen;Stress;-0.6;3
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `responseKind = Stress`, `threshold = -0.6`, `maxRetained = 3`.

## DesignConstrUnion

The design constraints of a subcase as the union of several [DesignConstr](optimisation.md#designconstr) sets.

**Record format and fields**

`DesignConstrUnion;constraintSetId;<memberSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constraintSetId` | `integer` | Required | Identifier selecting the constraint set record or set. |

**Repeated group `memberSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberSetId` | `integer` | — | Identifier selecting the member set record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignConstrUnion;100;41;42
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `constraintSetId = 100`.

## DesignControlSurface

The setting of a control surface in a trim case as a design variable times a coefficient.

**Record format and fields**

`DesignControlSurface;id;controlSurfaceLabel;trimId;designVarId;coefficient`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `controlSurfaceLabel` | `text` | — | Text naming the control surface. |
| 3 | `trimId` | `integer` | Required | Identifier selecting the trim record or set. |
| 4 | `designVarId` | `integer` | Required | Identifier of the design variable supplying the independent value. |
| 5 | `coefficient` | `real` | Required | Coefficient value in the DesignControlSurface relation. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignControlSurface;11;ELEV;1;1;1.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_trim_control_surface.oos)

Reading the example gives `id = 11`, `controlSurfaceLabel = ELEV`, `trimId = 1`, `designVarId = 1`.

## DesignDiscreteValues

Defines a list of admissible values for discrete design variables, topometry or rotor-speed selections.

**Record format and fields**

`DesignDiscreteValues;id;<discreteValues>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `discreteValues`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `discreteValue` | `any` | — | One permitted value in the discrete design set. |

Accepted words: `By`, `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `values` — at least one value is required.
- `increment` — the range has more than a million values: check its increment.

**Example record**

~~~text
DesignDiscreteValues;50;0.5;Through;2.;By;0.25
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 50`.

## DesignElemRelation1

A field of an element as a linear function of design variables.

**Record format and fields**

`DesignElemRelation1;id;kind;elemId;fieldName;minValue;maxValue;constant0;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignElemRelation1. |
| 3 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `constant0` | `real` | 0.0 | Coefficient 0 in the DesignElemRelation1 relation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |
| 2 | `coefficient` | `any` | — | Coefficient value in the DesignElemRelation1 relation for terms. |

Accepted words: `Constant`, `Element`, `PropertyValue`, `Table`.

**Example record**

~~~text
DesignElemRelation1;301;ShellQuad4;4;offset;-1.;1.;;5;1.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 301`, `kind = ShellQuad4`, `elemId = 4`, `fieldName = offset`.

## DesignElemRelation2

A field of an element as the value of a [DesignEquation](optimisation.md#designequation) equation of design variables and constants.

**Record format and fields**

`DesignElemRelation2;id;kind;elemId;fieldName;minValue;maxValue;equationId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignElemRelation2. |
| 3 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `equationId` | `integer` | Required | Identifier selecting the equation record or set. |

**Keyed sections in `variables`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constantLabel` | `text` | — | Text naming the constant. |

Accepted words: `Constant`, `DesignConstants`, `DesignVar`, `Element`, `Table`.

**Example record**

~~~text
DesignElemRelation2;24;Bar2;31;orientation3;;;23;DesignVar;1;5
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `id = 24`, `kind = Bar2`, `elemId = 31`, `fieldName = orientation3`.

## DesignEquation

A numbered set of equations.

**Record format and fields**

`DesignEquation;id;equation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `equation` | `text` | — | Expression or reference defining the response from its arguments. |

**Example record**

~~~text
DesignEquation;23;XV(A) = A
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `id = 23`, `equation = XV(A) = A`.

## DesignFieldConstants

Constants that are the value of a field of a property, a material or a connection of the analysis model (taken before the design variables change it).

**Record format and fields**

`DesignFieldConstants;<entries>`

This part of the record has no fixed fields.

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `label` | `text` | — | Text identifying the entry to the user or to records which select it by label. |
| 2 | `targetCard` | `text` | — | Type or identifier of the model entry to which the design relation applies. |
| 3 | `targetId` | `integer` | — | Identifier selecting the target record or set. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `label` — at least one constant is required.

**Example record**

~~~text
DesignFieldConstants;T1REF;ShellProp;1;thickness;T2REF;ShellProp;2;thickness
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

## DesignLoadRelation1

A value of a load as a linear function of design variables.

**Record format and fields**

`DesignLoadRelation1;id;kind;setId;fieldName;minValue;maxValue;constant0;attribute1;attribute2;attribute3;attribute4;attribute5;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignLoadRelation1. |
| 3 | `setId` | `integer` | Required | Identifier selecting the set record or set. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | -1.0e35 | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `constant0` | `real` | 0.0 | Coefficient 0 in the DesignLoadRelation1 relation. |
| 8 | `attribute1` | `integer` | — | Attribute of the indicated design target used in the response or relation. Entry 1. |
| 9 | `attribute2` | `integer` | — | Attribute of the indicated design target used in the response or relation. Entry 2. |
| 10 | `attribute3` | `integer` | — | Attribute of the indicated design target used in the response or relation. Entry 3. |
| 11 | `attribute4` | `integer` | — | Attribute of the indicated design target used in the response or relation. Entry 4. |
| 12 | `attribute5` | `integer` | — | Attribute of the indicated design target used in the response or relation. Entry 5. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |
| 2 | `coefficient` | `any` | — | Coefficient value in the DesignLoadRelation1 relation for terms. |

Accepted words: `Constant`, `Element`, `LoadCombination`, `PointForceLoad`, `PointMomentLoad`, `PropertyValue`, `Table`.

**Example record**

~~~text
DesignLoadRelation1;401;PointForceLoad;2;magnitude;;;;10;;;;;6;1.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 401`, `kind = PointForceLoad`, `setId = 2`, `fieldName = magnitude`.

## DesignMatRelation1

A field of a material as a linear function of design variables.

**Record format and fields**

`DesignMatRelation1;id;kind;matId;fieldName;minValue;maxValue;constant0;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignMatRelation1. |
| 3 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `constant0` | `real` | 0.0 | Coefficient 0 in the DesignMatRelation1 relation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |
| 2 | `coefficient` | `any` | — | Coefficient value in the DesignMatRelation1 relation for terms. |

Accepted words: `Constant`, `Element`, `PropertyValue`, `Table`.

**Example record**

~~~text
DesignMatRelation1;201;IsoMat;2;youngsModulus;6.E+4;8.E+4;;4;PropertyValue
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 201`, `kind = IsoMat`, `matId = 2`, `fieldName = youngsModulus`.

## DesignMatRelation2

A field of a material as the value of a [DesignEquation](optimisation.md#designequation) equation of design variables and constants.

**Record format and fields**

`DesignMatRelation2;id;kind;matId;fieldName;minValue;maxValue;equationId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignMatRelation2. |
| 3 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `equationId` | `integer` | Required | Identifier selecting the equation record or set. |

**Keyed sections in `variables`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constantLabel` | `text` | — | Text naming the constant. |

Accepted words: `Constant`, `DesignConstants`, `DesignVar`, `Element`, `Table`.

**Example record**

~~~text
DesignMatRelation2;22;IsoMat;1;youngsModulus;;;21;DesignVar;1;4
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `id = 22`, `kind = IsoMat`, `matId = 1`, `fieldName = youngsModulus`.

## DesignNodeMove

How a design variable moves a grid point.

**Record format and fields**

`DesignNodeMove;designVarId;nodeId;frameId;coefficient;directionX;directionY;directionZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | Required | Identifier of the design variable supplying the independent value. |
| 2 | `nodeId` | `integer` | Required | Identifier of the grid point addressed by this record. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `coefficient` | `real` | 0.0 | Coefficient value in the DesignNodeMove relation. |
| 5 | `directionX` | `real` | 0.0 | X component of the specified direction vector in its reference frame. |
| 6 | `directionY` | `real` | 0.0 | Y component of the specified direction vector in its reference frame. |
| 7 | `directionZ` | `real` | 0.0 | Z component of the specified direction vector in its reference frame. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignNodeMove;3;5;0;1.;0.;0.;1.
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `designVarId = 3`, `nodeId = 5`, `frameId = 0`, `coefficient = 1.`.

## DesignOptimParams

Overrides named optimization controls in a design model.

**Record format and fields**

`DesignOptimParams;<parameters>`

This part of the record has no fixed fields.

**Repeated group `parameters`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `parameterName` | `text` | — | Selects the setting to assign. Use the spelling from this card’s parameter list. |
| 2 | `parameterValue` | `any` | — | Value assigned to the named parameter. Its interpretation depends on that name. |

Accepted words: `Constant`, `Element`, `Table`.

Accepted parameter names: `AbsoluteObjectiveChange`, `AbsoluteObjectiveConvergence`, `ApproximationMethod`, `AutomaticSuperelementCreation`, `ConstraintActiveThreshold`, `ConstraintScale`, `ConstraintViolationThreshold`, `DesignVarConvergence`, `DesignVarMoveLimit`, `DesignVarScaling`, `DiscreteMethod`, `DiscreteStartCycle`, `EquivalentLoadMaxCycles`, `EquivalentLoadMoveLimit`, `FiniteDifferenceStep`, `FullyStressedMaxCycles`, `FullyStressedRelaxation`, `MaxConstraintViolation`, `MaxDesignCycles`, `MaxDesignVarChange`, `MaxPropertyChange`, `MinDesignVarChange`, `MinPropertyChange`, `ObjectiveRelativeToStart`, `OptimizationMethod`, `OptimizerName`, `OptimizerPrintLevel`, `PenaltyFactor`, `PrintAnalysisEveryCycle`, `PrintApproximation`, `PrintBeadConstraints`, `PrintConstraintCount`, `PrintDiscreteVars`, `PrintInterval`, `PrintItems`, `PrintMaterialCount`, `PrintMaxRetained`, `PrintPropertyCount`, `PrintResponseCount`, `PrintResponseSet`, `PropertyConvergence`, `PropertyLimitViolation`, `PropertyMoveLimit`, `PropertyTolerance`, `RelativeObjectiveChange`, `RelativeObjectiveConvergence`, `StepScale`, `SuperelementStopRatio`, `TopologyCheckerboard`, `TopologyMinMember`, `TopologyRegion`, `TrustRegionGrowthFactor`, `TrustRegionHighRatio`, `TrustRegionLowRatio`, `TrustRegionMiddleRatio`, `TrustRegionShrinkFactor`, `ViolationTreatment`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `parameterName` — at least one parameter is required.

**Example record**

~~~text
DesignOptimParams;MaxDesignCycles;5;PrintInterval;1;PrintItems;15
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

## DesignPropRelation1

A field of a property as a linear function of design variables.

**Record format and fields**

`DesignPropRelation1;id;kind;propId;fieldName;minValue;maxValue;constant0;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignPropRelation1. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `constant0` | `real` | 0.0 | Coefficient 0 in the DesignPropRelation1 relation. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |
| 2 | `coefficient` | `any` | — | Coefficient value in the DesignPropRelation1 relation for terms. |

Accepted words: `Constant`, `Element`, `PropertyValue`, `Table`.

**Example record**

~~~text
DesignPropRelation1;11;ShellProp;1;thickness;;;;2;1.
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_auxmodel_dvbshap.oos)

Reading the example gives `id = 11`, `kind = ShellProp`, `propId = 1`, `fieldName = thickness`.

## DesignPropRelation2

A field of a property as the value of a [DesignEquation](optimisation.md#designequation) equation of design variables and constants.

**Record format and fields**

`DesignPropRelation2;id;kind;propId;fieldName;minValue;maxValue;equationId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignPropRelation2. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `minValue` | `real` | — | Smallest value retained or permitted for the selected quantity. |
| 6 | `maxValue` | `real` | 1.0e20 | Largest value retained or permitted for the selected quantity. |
| 7 | `equationId` | `integer` | Required | Identifier selecting the equation record or set. |

**Keyed sections in `variables`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constantLabel` | `text` | — | Text naming the constant. |

Accepted words: `Constant`, `DesignConstants`, `DesignVar`, `Element`, `Table`.

**Example record**

~~~text
DesignPropRelation2;103;BarProp;3;area;10.;100.;22;DesignVar;1;3
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 103`, `kind = BarProp`, `propId = 3`, `fieldName = area`.

## DesignResp1

Defines a structural response, such as weight, displacement, stress or frequency, for an optimization objective or constraint.

**Record format and fields**

`DesignResp1;id;entryLabel;responseKind;ownerKind;regionId;attributeA;attributeB;<attributes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `responseKind` | `text` | — | Selects the response kind for DesignResp1. |
| 4 | `ownerKind` | `any` | — | Selects the owner kind for DesignResp1. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 6 | `attributeA` | `any` | — | First attribute used to qualify the design response. |
| 7 | `attributeB` | `any` | — | Second attribute used to qualify the design response. |

**Repeated group `attributes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `attribute` | `any` | — | Attribute of the indicated design target used in the response or relation. |

Accepted words: `AbsoluteDisplacement`, `AbsoluteStress`, `AcousticFieldIntensity`, `AcousticFieldPressure`, `AcousticFieldVelocity`, `AcousticIntensity`, `AcousticPower`, `All`, `Alpha`, `Average`, `BucklingFactor`, `ComplexEigenvalue`, `Compliance`, `CompositeFailure`, `CompositeStrain`, `CompositeStrengthRatio`, `CompositeStress`, `Constant`, `ConstraintForce`, `ContourDisplacement`, `ContourForce`, `CutLoad`, `DeflectionToThickness`, `Displacement`, `Divergence`, `DynamicStiffness`, `Eigenvalue`, `Element`, `Elements`, `Fatigue`, `Fluid`, `Flutter`, `Force`, `FractionalMass`, `FreqAcceleration`, `FreqConstraintForce`, `FreqDisplacement`, `FreqFatigue`, `FreqForce`, `FreqStress`, `FreqVelocity`, `Frequency`, `KMethod`, `KMethodEfficient`, `MeanDisplacement`, `NodeForce`, `NodeForcePanel`, `Omega`, `PkMethod`, `PkMethodNoLoop`, `PkMethodNoLoopSweep`, `PkMethodSweep`, `Pressure`, `RadiatedPower`, `RootMeanSquareAcceleration`, `RootMeanSquareDisplacement`, `RootMeanSquareVelocity`, `Rotation`, `SectionLoad`, `SpectralAcceleration`, `SpectralDisplacement`, `SpectralVelocity`, `StabilityDerivative`, `Strain`, `StrainEnergy`, `Stress`, `Structure`, `Table`, `Through`, `TotalCompliance`, `TotalStrainEnergy`, `TransientAcceleration`, `TransientConstraintForce`, `TransientDisplacement`, `TransientForce`, `TransientStress`, `TransientVelocity`, `TrimVariable`, `Volume`, `Weight`, `WeightPerPropertyId`.

**Example record**

~~~text
DesignResp1;35;BARSA;Stress;BarProp;;7;;3
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 35`, `entryLabel = BARSA`, `responseKind = Stress`, `ownerKind = BarProp`.

## DesignResp2

Combines design variables, constants and other responses through a built-in function or a [DesignEquation](optimisation.md#designequation).

**Record format and fields**

`DesignResp2;id;entryLabel;equationId;function;regionId;methodName;constant1;constant2;constant3;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `equationId` | `integer` | — | Identifier selecting the equation record or set. Alternative to `function`. |
| 4 | `function` | `text` | — | Selects the function used to combine or evaluate the supplied arguments. Alternative to `equationId`. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 6 | `methodName` | `text` | — | Text naming the method. |
| 7 | `constant1` | `real` | 1.0 | Coefficient 1 in the DesignResp2 relation. |
| 8 | `constant2` | `real` | 0.005 | Coefficient 2 in the DesignResp2 relation. |
| 9 | `constant3` | `real` | 10.0 | Coefficient 3 in the DesignResp2 relation. |

**Keyed sections in `arguments`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constantLabel` | `text` | — | Text naming the constant. |

**Section `DesignResp1`**

**Repeated group `responses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `responseId` | `integer` | — | Identifier selecting the response record or set. |

**Section `DesignNodes`**

**Repeated group `nodeComponents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |
| 2 | `nodeComponent` | `integer` | — | Number of the degree of freedom at the associated point. |

**Section `DesignPropRelation1`**

**Repeated group `propRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propRelationId` | `integer` | — | Identifier selecting the property relation record or set. |

**Section `DesignElemRelation1`**

**Repeated group `elemRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemRelationId` | `integer` | — | Identifier selecting the element relation record or set. |

**Section `DesignMatRelation1`**

**Repeated group `matRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matRelationId` | `integer` | — | Identifier selecting the material relation record or set. |

**Section `DesignPropRelation2`**

**Repeated group `propRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propRelation2Id` | `integer` | — | Identifier selecting the property relation 2 record or set. |

**Section `DesignElemRelation2`**

**Repeated group `elemRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemRelation2Id` | `integer` | — | Identifier selecting the element relation 2 record or set. |

**Section `DesignMatRelation2`**

**Repeated group `matRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matRelation2Id` | `integer` | — | Identifier selecting the material relation 2 record or set. |

**Section `DesignResp2`**

**Repeated group `combinedResponses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combinedResponseId` | `integer` | — | Identifier selecting the combined response record or set. |

**Section `DesignLoadRelation1`**

**Repeated group `loadRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `loadRelationId` | `integer` | — | Identifier selecting the load relation record or set. |

Accepted words: `Average`, `BetaFunction`, `Constant`, `DesignConstants`, `DesignElemRelation1`, `DesignElemRelation2`, `DesignLoadRelation1`, `DesignMatRelation1`, `DesignMatRelation2`, `DesignNodes`, `DesignPropRelation1`, `DesignPropRelation2`, `DesignResp1`, `DesignResp2`, `DesignVar`, `Element`, `LeastSquares`, `MatchedResponses`, `Maximum`, `Minimum`, `RootSumSquare`, `SafetyFactorMax`, `Sum`, `SumOfSquares`, `Table`, `UserData`.

**Example record**

~~~text
DesignResp2;35;AVGDISP;34;;;;;;;DesignResp1;2;32;32
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `id = 35`, `entryLabel = AVGDISP`, `equationId = 34`.

## DesignResp3

A response computed by a routine of the user, from design variables, constants and other responses.

**Record format and fields**

`DesignResp3;id;entryLabel;groupName;kind;regionId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 4 | `kind` | `text` | — | Selects the kind for DesignResp3. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |

**Keyed sections in `arguments`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `constantLabel` | `text` | — | Text naming the constant. |

**Section `DesignResp1`**

**Repeated group `responses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `responseId` | `integer` | — | Identifier selecting the response record or set. |

**Section `DesignNodes`**

**Repeated group `nodeComponents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |
| 2 | `nodeComponent` | `integer` | — | Number of the degree of freedom at the associated point. |

**Section `DesignPropRelation1`**

**Repeated group `propRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propRelationId` | `integer` | — | Identifier selecting the property relation record or set. |

**Section `DesignElemRelation1`**

**Repeated group `elemRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemRelationId` | `integer` | — | Identifier selecting the element relation record or set. |

**Section `DesignMatRelation1`**

**Repeated group `matRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matRelationId` | `integer` | — | Identifier selecting the material relation record or set. |

**Section `DesignPropRelation2`**

**Repeated group `propRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propRelation2Id` | `integer` | — | Identifier selecting the property relation 2 record or set. |

**Section `DesignElemRelation2`**

**Repeated group `elemRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemRelation2Id` | `integer` | — | Identifier selecting the element relation 2 record or set. |

**Section `DesignMatRelation2`**

**Repeated group `matRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matRelation2Id` | `integer` | — | Identifier selecting the material relation 2 record or set. |

**Section `DesignResp2`**

**Repeated group `combinedResponses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `combinedResponseId` | `integer` | — | Identifier selecting the combined response record or set. |

**Section `DesignLoadRelation1`**

**Repeated group `loadRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `loadRelationId` | `integer` | — | Identifier selecting the load relation record or set. |

**Section `UserData`**

**Repeated group `userData`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `userText` | `text` | — | Free-form character data carried with the design entry. Written as one text field. |

Accepted words: `Constant`, `DesignConstants`, `DesignElemRelation1`, `DesignElemRelation2`, `DesignLoadRelation1`, `DesignMatRelation1`, `DesignMatRelation2`, `DesignNodes`, `DesignPropRelation1`, `DesignPropRelation2`, `DesignResp1`, `DesignResp2`, `DesignVar`, `Element`, `Table`, `UserData`.

**Example record**

~~~text
DesignResp3;33;BUCKMRG;PANEL;BUCK;;DesignVar;1;1;DesignConstants;3;EMOD;PLEN;PWID;DesignResp1;1;32;DesignNodes;1;10;1;DesignPropRelation1;1;11;UserData;1;simply supported edges along y
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol200_external_response.oos)

Reading the example gives `id = 33`, `entryLabel = BUCKMRG`, `groupName = PANEL`, `kind = BUCK`.

## DesignShapeBasis

Defines a shape basis vector as a linear combination of displacement-matrix columns from a previous analysis.

**Record format and fields**

`DesignShapeBasis;designVarId;column1;scaleFactor1;column2;scaleFactor2;column3;scaleFactor3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `designVarId` | `integer` | Required | Identifier of the design variable supplying the independent value. |
| 2 | `column1` | `integer` | — | Column identifier for contribution 1 of the displacement or shape basis. |
| 3 | `scaleFactor1` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 1. |
| 4 | `column2` | `integer` | — | Column identifier for contribution 2 of the displacement or shape basis. |
| 5 | `scaleFactor2` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 2. |
| 6 | `column3` | `integer` | — | Column identifier for contribution 3 of the displacement or shape basis. |
| 7 | `scaleFactor3` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. Entry 3. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignShapeBasis;2;2;0.5;1;0.5
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_dvshap_basis_vectors.oos)

Reading the example gives `designVarId = 2`, `column1 = 2`, `scaleFactor1 = 0.5`, `column2 = 1`.

## DesignTopologyRegion

A region of a topology optimisation, the elements of one property whose density the optimisation designs.

**Record format and fields**

`DesignTopologyRegion;id;entryLabel;propType;initialValue;lowerBound;designVarMoveLimit;penaltyPower;propId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `propType` | `text` | — | Selects the property type for DesignTopologyRegion. |
| 4 | `initialValue` | `real` | — | Starting value of the quantity before an update or iteration. |
| 5 | `lowerBound` | `real` | 0.001 | Lower limit expressed in the same units as the bounded quantity. |
| 6 | `designVarMoveLimit` | `real` | — | Limits the change allowed for this design variable in one optimization update. |
| 7 | `penaltyPower` | `real` | — | Exponent penalizing intermediate values in the design interpolation. |
| 8 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Symmetry`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 2 | `mirrorPlane1` | `text` | — | Plane of mirror symmetry applied to the design region, entry 1. |
| 3 | `mirrorPlane2` | `text` | — | Plane of mirror symmetry applied to the design region, entry 2. |
| 4 | `mirrorPlane3` | `text` | — | Plane of mirror symmetry applied to the design region, entry 3. |
| 5 | `cyclicAxis` | `text` | — | Axis around which the repeated sectors are arranged. |
| 6 | `cyclicSegments` | `integer` | — | Number of sectors in a full revolution. |

**Section `Casting`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 2 | `castDirection` | `text` | — | Draw direction specified for the casting constraint. |
| 3 | `dieCount` | `integer` | — | Number of die entries. |
| 4 | `alignment` | `text` | — | Alignment restriction on the manufacturing or design direction. |

**Section `Extrusion`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 2 | `extrusionDirection` | `text` | — | Direction along which the design cross-section is extruded. |
| 3 | `alignment` | `text` | — | Alignment restriction on the manufacturing or design direction. |

**Section `Overhang`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 2 | `overhangDirection` | `text` | — | Build direction used to measure an overhang constraint. |

**Section `MemberSize`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `minMemberSize` | `real` | — | Lower bound on the characteristic member dimension. |
| 2 | `maxMemberSize` | `real` | — | Upper bound on the characteristic member dimension. |

**Section `Stress`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressLimit` | `real` | — | Maximum or limiting stress in model stress units. |

Accepted words: `Casting`, `Constant`, `Element`, `Extrusion`, `MemberSize`, `NegativeXDirection`, `NegativeYDirection`, `NegativeZDirection`, `No`, `Overhang`, `PlaneXy`, `PlaneYz`, `PlaneZx`, `Stress`, `Symmetry`, `Table`, `XDirection`, `YDirection`, `Yes`, `ZDirection`.

**Example record**

~~~text
DesignTopologyRegion;1;MIDDLE;ShellProp;0.5;0.001;;;1
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_topology_topometry_topography.oos)

Reading the example gives `id = 1`, `entryLabel = MIDDLE`, `propType = ShellProp`, `initialValue = 0.5`.

## DesignTopometryRegion

A design region of a topometry optimisation, in which the thickness or another property value of every element of one property is a design variable of its own.

**Record format and fields**

`DesignTopometryRegion;id;kind;propId;fieldName;initialValue;lowerBound;upperBound;designVarMoveLimit;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `kind` | `text` | — | Selects the kind for DesignTopometryRegion. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `initialValue` | `real` | — | Starting value of the quantity before an update or iteration. |
| 6 | `lowerBound` | `real` | — | Lower limit expressed in the same units as the bounded quantity. |
| 7 | `upperBound` | `real` | — | Upper limit expressed in the same units as the bounded quantity. |
| 8 | `designVarMoveLimit` | `real` | 0.5 | Limits the change allowed for this design variable in one optimization update. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVarLink`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `tableId` | `integer` | — | Identifier of the tabulated function to evaluate. |
| 2 | `constant0` | `real` | — | Coefficient 0 in the DesignTopometryRegion relation for link. |
| 3 | `coefficient1` | `real` | — | Coefficient 1 in the DesignTopometryRegion relation for link. |

**Section `DesignDiscreteValues`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `discreteValuesId` | `integer` | — | Identifier of the DesignDiscreteValues list of admissible values. |

**Section `Stress`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressLimit` | `real` | — | Maximum or limiting stress in model stress units. |

**Section `Symmetry`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameId` | `integer` | — | Coordinate system in which this entry is expressed. |
| 2 | `mirrorPlane1` | `text` | — | Plane of mirror symmetry applied to the design region, entry 1. |
| 3 | `mirrorPlane2` | `text` | — | Plane of mirror symmetry applied to the design region, entry 2. |
| 4 | `mirrorPlane3` | `text` | — | Plane of mirror symmetry applied to the design region, entry 3. |
| 5 | `cyclicAxis` | `text` | — | Axis around which the repeated sectors are arranged. |
| 6 | `cyclicSegments` | `integer` | — | Number of sectors in a full revolution. |
| 7 | `firstSymmetryPropId` | `integer` | — | Identifier selecting the first symmetry property record or set. |

**Section with an empty key**

**Repeated group `symmetryProps`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `symmetryPropId` | `integer` | — | Identifier selecting the symmetry property record or set. |

Accepted words: `Constant`, `DesignDiscreteValues`, `DesignVarLink`, `Element`, `PlaneXy`, `PlaneYz`, `PlaneZx`, `Stress`, `Symmetry`, `Table`, `XDirection`, `YDirection`, `ZDirection`.

**Example record**

~~~text
DesignTopometryRegion;2;ShellProp;2;thickness;2.;1.;4.
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_topology_topometry_topography.oos)

Reading the example gives `id = 2`, `kind = ShellProp`, `propId = 2`, `fieldName = thickness`.

## DesignVar

Defines a design variable by its label, starting value and bounds. Design relations use its ID to vary model properties.

**Record format and fields**

`DesignVar;id;entryLabel;initialValue;lowerBound;upperBound;designVarMoveLimit;discreteValuesId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier referenced by design relations and responses. |
| 2 | `entryLabel` | `text` | — | Name used to identify the variable in an optimization study. |
| 3 | `initialValue` | `real` | Required | Starting design coordinate. Use the same units for its bounds and discrete values. |
| 4 | `lowerBound` | `real` | — | Lower limit expressed in the same units as the bounded quantity. |
| 5 | `upperBound` | `real` | — | Upper limit expressed in the same units as the bounded quantity. |
| 6 | `designVarMoveLimit` | `real` | — | Limits the change allowed for this design variable in one optimization update. |
| 7 | `discreteValuesId` | `integer` | 0 | Identifier of the DesignDiscreteValues list of admissible values. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
DesignVar;1;FAC1;1.;0.5;2.;;50
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 1`, `entryLabel = FAC1`, `initialValue = 1.`, `lowerBound = 0.5`.

## DesignVarLink

A design variable that is a linear function of other design variables.

**Record format and fields**

`DesignVarLink;id;dependentVarId;constant0;multiplier;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dependentVarId` | `integer` | Required | Identifier selecting the dependent var record or set. |
| 3 | `constant0` | `real` | 0.0 | Coefficient 0 in the DesignVarLink relation. |
| 4 | `multiplier` | `real` | 1.0 | Factor applied to the associated term before assembly. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentId` | `integer` | — | Identifier selecting the independent record or set. |
| 2 | `coefficient` | `real` | — | Coefficient value in the DesignVarLink relation for terms. |

Accepted words: `Constant`, `Element`, `PropertyValue`, `Table`.

**Example record**

~~~text
DesignVarLink;7;2;0.;1.;1;0.8
~~~

[Model containing this record](../../../validation/models/design_optimisation/sol200_sizing_relations.oos)

Reading the example gives `id = 7`, `dependentVarId = 2`, `constant0 = 0.`, `multiplier = 1.`.
