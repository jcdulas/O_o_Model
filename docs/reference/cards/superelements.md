# Superelements

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AxisymConeSector

A sector of a conical shell.

**Record format and fields**

`AxisymConeSector;id;ringId;radius;phiAngle1;phiAngle2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `ringId` | `integer` | Required | Identifier addressing node data. |
| 3 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 4 | `phiAngle1` | `real` | Required | Angular coordinate or orientation denoted by phi in the local geometry. Entry 1. |
| 5 | `phiAngle2` | `real` | Required | Angular coordinate or orientation denoted by phi in the local geometry. Entry 2. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymConeSector;52;4;70.;80.;100.
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_static.oos)

Reading the example gives `id = 52`, `ringId = 4`, `radius = 70.`, `phiAngle1 = 80.`.

**Referenced records in this example**

- [AxisymConeRing](nodes.md#axisymconering) via `ringId = 4`.

## AxisymConeSupport

The fictitious supports of a conical shell free body, the determinate reactions of the analysis.

**Record format and fields**

`AxisymConeSupport;<dofs>`

This part of the record has no fixed fields.

**Repeated group `dofs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ringId` | `integer` | — | Identifier selecting the ring record or set. |
| 2 | `harmonicId` | `integer` | — | Identifier selecting the harmonic record or set. |
| 3 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Constant`, `Element`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `ringId` — the card has at most 12 degrees of freedom.

**Example record**

~~~text
AxisymConeSupport;1;0;23;1;1;13
~~~

[Model containing this record](../../../validation/models/axisymmetric_conical/conical_shell_free_modes.oos)

## FixedBoundaryDofs

Degrees of freedom of the fixed boundary set (b-set) for the generalized dynamic reduction and the component mode synthesis.

**Record format and fields**

`FixedBoundaryDofs;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
FixedBoundaryDofs;1;123456
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

## FixedBoundaryDofs1

The degrees of freedom C of a list of points in the fixed boundary set (b-set).

**Record format and fields**

`FixedBoundaryDofs1;components;<nodes>`

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
FixedBoundaryDofs1;456;4
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

Reading the example gives `components = 456`.

## FreeBoundaryDofs

Degrees of freedom of the free boundary set (c-set) for the generalized dynamic reduction and the component mode synthesis.

**Record format and fields**

`FreeBoundaryDofs;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Example record**

~~~text
FreeBoundaryDofs;4;12
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

## FreeBoundaryDofs1

The degrees of freedom C of a list of points in the free boundary set (c-set).

**Record format and fields**

`FreeBoundaryDofs1;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `components` | `any` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
FreeBoundaryDofs1;3;4
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

Reading the example gives `components = 3`.

## MassCaseCombination

The linear combination of mass cases that a subcase uses as its mass.

**Record format and fields**

`MassCaseCombination;id;overallScale;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `overallScale` | `real` | 0.0 | The overall scale factor. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `caseScale` | `real` | — | Multiplier applied to the contribution from this case. |
| 2 | `caseId` | `integer` | — | Identifier selecting the case record or set. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
MassCaseCombination;11;1.;1.;0;1.;101
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_parts_mirror_mass_sol103.oos)

Reading the example gives `id = 11`, `overallScale = 1.`.

## SuperelementAccessPoints

The grid points inside an external superelement whose motion the residual structure of the assembly keeps (the access points).

**Record format and fields**

`SuperelementAccessPoints;<nodes>`

This part of the record has no fixed fields.

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |

Accepted words: `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeId1` — the card needs at least one grid point.
- `nodeId1` — a grid point ID must be a positive integer.

**Example record**

~~~text
SuperelementAccessPoints;5
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_creation_access_sol103.oos)

## SuperelementBoundarySearch

Grid points of a part superelement for the automatic search of the boundary with another superelement, or with all the others.

**Record format and fields**

`SuperelementBoundarySearch;superelementIdA;superelementIdB;<boundaryNodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementIdA` | `integer` | Required | Identifier of the superelement on side A. |
| 2 | `superelementIdB` | `any` | — | Identifier of the superelement on side B. |

**Repeated group `boundaryNodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `boundaryNodeId` | `any` | — | Identifier selecting the boundary node record or set. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementBoundarySearch;10;All;1001;1003;1006
~~~

[Model containing this record](../../../validation/models/superelements/se_parts_boundary_search.oos)

Reading the example gives `superelementIdA = 10`, `superelementIdB = All`.

## SuperelementBulkOptions

The boundary search options of a superelement, and what a repeated, mirrored or collector superelement is.

**Record format and fields**

`SuperelementBulkOptions;superelementId;partType;referenceSuperelementId;method;tolerance;location;unitNumber`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `partType` | `text` | — | Selects the part type for SuperelementBulkOptions. |
| 3 | `referenceSuperelementId` | `integer` | 0 | Identifier selecting the reference superelement record or set. |
| 4 | `method` | `text` | Automatic | Selects the method for SuperelementBulkOptions. |
| 5 | `tolerance` | `real` | 0.0 | Allowable change or residual for the selected numerical check. |
| 6 | `location` | `text` | Yes | Position at which the record is applied or the response is evaluated. |
| 7 | `unitNumber` | `integer` | 0 | Logical file unit used to identify an external resource. |

Accepted words: `All`, `Automatic`, `CollectorSuperelement`, `Constant`, `Element`, `External`, `ExternalBinaryResults`, `ExternalMatrixFile`, `ExternalPunchFile`, `ExternalReducedModel`, `Manual`, `Mirror`, `No`, `Primary`, `Repeat`, `Table`, `Through`, `Yes`.

**Example record**

~~~text
SuperelementBulkOptions;11;Repeat;10;Automatic
~~~

[Model containing this record](../../../validation/models/superelements/se_parts_repeat_tree.oos)

Reading the example gives `superelementId = 11`, `partType = Repeat`, `referenceSuperelementId = 10`, `method = Automatic`.

## SuperelementConnection

The boundary connection between two superelements, point by point.

**Record format and fields**

`SuperelementConnection;superelementIdA;superelementIdB;tolerance;location;<connections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementIdA` | `integer` | Required | Identifier of the superelement on side A. |
| 2 | `superelementIdB` | `integer` | Required | Identifier of the superelement on side B. |
| 3 | `tolerance` | `real` | 0.0 | Allowable change or residual for the selected numerical check. |
| 4 | `location` | `text` | Yes | Position at which the record is applied or the response is evaluated. |

**Repeated group `connections`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `connectionPoint` | `any` | — | Grid point or interface point through which parts connect. |

Accepted words: `All`, `Both`, `Constant`, `Element`, `Full`, `No`, `Off`, `On`, `Table`, `Through`, `Yes`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeIdA` — a grid or scalar point ID must be a positive integer.

**Example record**

~~~text
SuperelementConnection;30;0;;No;3001;1;3004;2
~~~

[Model containing this record](../../../validation/models/superelements/se_parts_boundary_search.oos)

Reading the example gives `superelementIdA = 30`, `superelementIdB = 0`, `location = No`.

## SuperelementCopyPoints

The exterior points of a secondary superelement (an identical or mirror image copy of another one, or one that comes from an external source).

**Record format and fields**

`SuperelementCopyPoints;superelementId;primarySuperelementId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `primarySuperelementId` | `integer` | 0 | Identifier addressing superelement data. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
SuperelementCopyPoints;3;1;4;5;9;10
~~~

[Model containing this record](../../../validation/models/superelements/se_main_bulk_list.oos)

Reading the example gives `superelementId = 3`, `primarySuperelementId = 1`.

## SuperelementCopySequence

The order of the exterior points of a primary superelement that an identical or mirror image copy of it follows.

**Record format and fields**

`SuperelementCopySequence;superelementId;primarySuperelementId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `primarySuperelementId` | `integer` | Required | Identifier selecting the primary superelement record or set. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementCopySequence;4;3;5;10
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 4`, `primarySuperelementId = 3`.

## SuperelementDesignLink

Defines a linear relationship between design variables belonging to different superelements.

**Record format and fields**

`SuperelementDesignLink;id;dependentSuperelementId;dependentVarId;constant0;multiplier;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dependentSuperelementId` | `integer` | Required | Identifier selecting the dependent superelement record or set. |
| 3 | `dependentVarId` | `integer` | Required | Identifier selecting the dependent var record or set. |
| 4 | `constant0` | `real` | 0.0 | Coefficient 0 in the SuperelementDesignLink relation. |
| 5 | `multiplier` | `real` | 1.0 | Factor applied to the associated term before assembly. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentSuperelementId` | `integer` | — | Identifier selecting the independent superelement record or set. |
| 2 | `independentVarId` | `integer` | — | Identifier selecting the independent var record or set. |
| 3 | `coefficient` | `real` | — | Coefficient value in the SuperelementDesignLink relation for terms. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementDesignLink;1;20;21;0.;1.;10;11;1.
~~~

[Model containing this record](../../../validation/models/read_only_superelements/se_parts_design_external_response_sol200.oos)

Reading the example gives `id = 1`, `dependentSuperelementId = 20`, `dependentVarId = 21`, `constant0 = 0.`.

## SuperelementDesignResp2

A response computed from design variables, constants and responses of several part superelements, by a [DesignEquation](optimisation.md#designequation) equation or by a function, as a [DesignResp2](optimisation.md#designresp2) does for one model.

**Record format and fields**

`SuperelementDesignResp2;id;entryLabel;equationId;function;regionId;methodName;constant1;constant2;constant3;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `equationId` | `integer` | — | Identifier selecting the equation record or set. Alternative to `function`. |
| 4 | `function` | `text` | — | Selects the function used to combine or evaluate the supplied arguments. Alternative to `equationId`. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 6 | `methodName` | `text` | — | Text naming the method. |
| 7 | `constant1` | `real` | 100.0 | Coefficient 1 in the SuperelementDesignResp2 relation. |
| 8 | `constant2` | `real` | 0.005 | Coefficient 2 in the SuperelementDesignResp2 relation. |
| 9 | `constant3` | `real` | 10.0 | Coefficient 3 in the SuperelementDesignResp2 relation. |

**Keyed sections in `groups`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `constantLabel` | `text` | — | Text naming the constant. |

**Section `DesignResp1`**

**Repeated group `responses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `responseId` | `integer` | — | Identifier selecting the response record or set. |

**Section `DesignNodes`**

**Repeated group `designNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |
| 3 | `nodeComponents` | `integer` | — | Degrees of freedom selected at the associated grid point. |

**Section `DesignPropRelation1`**

**Repeated group `propRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `propRelationId` | `integer` | — | Identifier selecting the property relation record or set. |

**Section `DesignElemRelation1`**

**Repeated group `elemRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `elemRelationId` | `integer` | — | Identifier selecting the element relation record or set. |

**Section `DesignMatRelation1`**

**Repeated group `matRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `matRelationId` | `integer` | — | Identifier selecting the material relation record or set. |

**Section `DesignPropRelation2`**

**Repeated group `propRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `propRelation2Id` | `integer` | — | Identifier selecting the property relation 2 record or set. |

**Section `DesignElemRelation2`**

**Repeated group `elemRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `elemRelation2Id` | `integer` | — | Identifier selecting the element relation 2 record or set. |

**Section `DesignMatRelation2`**

**Repeated group `matRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `matRelation2Id` | `integer` | — | Identifier selecting the material relation 2 record or set. |

Accepted words: `All`, `Average`, `BetaFunction`, `Constant`, `DesignConstants`, `DesignElemRelation1`, `DesignElemRelation2`, `DesignMatRelation1`, `DesignMatRelation2`, `DesignNodes`, `DesignPropRelation1`, `DesignPropRelation2`, `DesignResp1`, `DesignVar`, `Element`, `MatchedResponses`, `Maximum`, `Minimum`, `RootSumSquare`, `SafetyFactorMax`, `Sum`, `SumOfSquares`, `Table`, `Through`.

**Example record**

~~~text
SuperelementDesignResp2;101;TIPDZ;;Sum;;;;;;DesignResp1;1;10;14
~~~

[Model containing this record](../../../validation/models/read_only_superelements/se_parts_design_external_response_sol200.oos)

Reading the example gives `id = 101`, `entryLabel = TIPDZ`, `function = Sum`.

## SuperelementDesignResp3

An external response, computed by a routine of the user from design variables, constants and responses of several part superelements, as a [DesignResp3](optimisation.md#designresp3) does for one model.

**Record format and fields**

`SuperelementDesignResp3;id;entryLabel;groupName;kind;regionId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. |
| 3 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 4 | `kind` | `text` | — | Selects the kind for SuperelementDesignResp3. |
| 5 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |

**Keyed sections in `groups`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DesignVar`**

**Repeated group `designVariables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `designVarId` | `integer` | — | Identifier of the design variable supplying the independent value. |

**Section `DesignConstants`**

**Repeated group `constants`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `constantLabel` | `text` | — | Text naming the constant. |

**Section `DesignResp1`**

**Repeated group `responses`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `responseId` | `integer` | — | Identifier selecting the response record or set. |

**Section `DesignNodes`**

**Repeated group `designNodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |
| 3 | `nodeComponents` | `integer` | — | Degrees of freedom selected at the associated grid point. |

**Section `DesignPropRelation1`**

**Repeated group `propRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `propRelationId` | `integer` | — | Identifier selecting the property relation record or set. |

**Section `DesignElemRelation1`**

**Repeated group `elemRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `elemRelationId` | `integer` | — | Identifier selecting the element relation record or set. |

**Section `DesignMatRelation1`**

**Repeated group `matRelations`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `matRelationId` | `integer` | — | Identifier selecting the material relation record or set. |

**Section `DesignPropRelation2`**

**Repeated group `propRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `propRelation2Id` | `integer` | — | Identifier selecting the property relation 2 record or set. |

**Section `DesignElemRelation2`**

**Repeated group `elemRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `elemRelation2Id` | `integer` | — | Identifier selecting the element relation 2 record or set. |

**Section `DesignMatRelation2`**

**Repeated group `matRelations2`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `matRelation2Id` | `integer` | — | Identifier selecting the material relation 2 record or set. |

**Section `UserData`**

**Repeated group `userDataLines`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `userData` | `text` | — | Application-defined data supplied to the consumer in record order. Written as one text field. |

Accepted words: `All`, `Constant`, `DesignConstants`, `DesignElemRelation1`, `DesignElemRelation2`, `DesignMatRelation1`, `DesignMatRelation2`, `DesignNodes`, `DesignPropRelation1`, `DesignPropRelation2`, `DesignResp1`, `DesignVar`, `Element`, `Table`, `Through`, `UserData`.

**Example record**

~~~text
SuperelementDesignResp3;200;USRW;USRWT;WTUSER;;DesignVar;2;10;11;20;21;DesignResp1;2;10;13;20;23;UserData;1;SCALE1
~~~

[Model containing this record](../../../validation/models/read_only_superelements/se_parts_design_external_response_sol200.oos)

Reading the example gives `id = 200`, `entryLabel = USRW`, `groupName = USRWT`, `kind = WTUSER`.

## SuperelementElemTransfer

Elements that a superelement takes from the one downstream of it.

**Record format and fields**

`SuperelementElemTransfer;superelementId;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `element` | `any` | — | Identifier of the element selected in this group. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementElemTransfer;1;60
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`.

## SuperelementExcludedNodes

Grid points of a part superelement that are left out of its connection to another superelement, or to all the others.

**Record format and fields**

`SuperelementExcludedNodes;superelementIdA;superelementIdB;<excludedNodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementIdA` | `integer` | Required | Identifier of the superelement on side A. |
| 2 | `superelementIdB` | `any` | — | Identifier of the superelement on side B. |

**Repeated group `excludedNodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `excludedNodeId` | `any` | — | Identifier selecting the excluded node record or set. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementExcludedNodes;20;10;2004
~~~

[Model containing this record](../../../validation/models/superelements/se_parts_boundary_search.oos)

Reading the example gives `superelementIdA = 20`, `superelementIdB = 10`.

## SuperelementExteriorPoints

The exterior points of a primary superelement.

**Record format and fields**

`SuperelementExteriorPoints;superelementId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementExteriorPoints;1;500
~~~

[Model containing this record](../../../validation/models/superelements/se_main_bulk_list.oos)

Reading the example gives `superelementId = 1`.

## SuperelementExternalBoundary

The boundary connection of an external superelement.

**Record format and fields**

`SuperelementExternalBoundary;<pairs>`

This part of the record has no fixed fields.

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nodeId` | `integer` | — | Identifier of the grid point addressed by this record. |
| 2 | `components` | `any` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Through`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `nodeId` — a grid or scalar point ID must be a positive integer.

**Example record**

~~~text
SuperelementExternalBoundary;1001;123456;1004;123456;1007;123456
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_extrn_seload_sol101.oos)

## SuperelementFixedDofSet

Degrees of freedom of the exterior points of a superelement that are fixed (b-set) in the component mode synthesis.

**Record format and fields**

`SuperelementFixedDofSet;superelementId;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementFixedDofSet;1;2;123456
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `node1 = 2`, `components1 = 123456`.

## SuperelementFixedDofSet1

The degrees of freedom C of a list of exterior points of a superelement that are fixed (b-set).

**Record format and fields**

`SuperelementFixedDofSet1;superelementId;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementFixedDofSet1;1;123456;3
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `components = 123456`.

## SuperelementFreeDofSet

Degrees of freedom of the exterior points of a superelement that are free (c-set) in the component mode synthesis.

**Record format and fields**

`SuperelementFreeDofSet;superelementId;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementFreeDofSet;1;4;123456
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `node1 = 4`, `components1 = 123456`.

## SuperelementFreeDofSet1

The degrees of freedom C of a list of exterior points of a superelement that are free (c-set).

**Record format and fields**

`SuperelementFreeDofSet1;superelementId;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `components` | `any` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementFreeDofSet1;2;123456;12;13
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 2`, `components = 123456`.

## SuperelementGeneralizedDofSet

The generalized degrees of freedom (q-set) a superelement uses in the generalized dynamic reduction or the component mode synthesis.

**Record format and fields**

`SuperelementGeneralizedDofSet;superelementId;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementGeneralizedDofSet;1;1006;0
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `node1 = 1006`, `components1 = 0`.

## SuperelementGeneralizedDofSet1

The degrees of freedom C of a list of points that a superelement uses as generalized degrees of freedom (q-set).

**Record format and fields**

`SuperelementGeneralizedDofSet1;superelementId;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementGeneralizedDofSet1;1;0;1001;Through;1005
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `components = 0`.

## SuperelementGeneralizedPointCount

How many scalar points a superelement generates for its dynamic reduction.

**Record format and fields**

`SuperelementGeneralizedPointCount;superelementId;count`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `any` | — | Identifier of the superelement associated with the entry. |
| 2 | `count` | `integer` | 0 | Number of entries to process in this group. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementGeneralizedPointCount;All;4
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_parts_mirror_mass_sol103.oos)

Reading the example gives `superelementId = All`, `count = 4`.

## SuperelementInteriorNodes

The interior grid points of a (list) superelement.

**Record format and fields**

`SuperelementInteriorNodes;superelementId;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementInteriorNodes;2;201;202;203;300
~~~

[Model containing this record](../../../validation/models/superelements/se_main_bulk_list.oos)

Reading the example gives `superelementId = 2`.

## SuperelementLabel

The label a superelement carries in the headings of the output.

**Record format and fields**

`SuperelementLabel;superelementId;entryLabel`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `entryLabel` | `text` | — | User label associated with the entry. Written as one text field. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementLabel;10;Upper panel
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_parts_mirror_mass_sol103.oos)

Reading the example gives `superelementId = 10`, `entryLabel = Upper panel`.

## SuperelementLoadScale

Selects and scales the loads of external superelements.

**Record format and fields**

`SuperelementLoadScale;id;scaleFactor;<entries>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | — | Identifier of the superelement associated with the entry. |
| 2 | `entryScaleFactor` | `real` | — | Multiplier for entry scale. |
| 3 | `labelKind` | `text` | — | Selects the label kind for entries. |
| 4 | `labelledId` | `any` | — | Identifier selecting the labelled record or set. Written as one text field. |

Accepted words: `All`, `Column`, `ColumnNumber`, `Constant`, `Element`, `Label`, `LoadId`, `Subcase`, `SubcaseId`, `Table`, `Through`.

**Example record**

~~~text
SuperelementLoadScale;11;1.;100;1.;ColumnNumber;1
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_external_extrn_seload_sol101.oos)

Reading the example gives `id = 11`, `scaleFactor = 1.`.

## SuperelementLocation

Where a part superelement is placed, by three of its points and the three points they go to.

**Record format and fields**

`SuperelementLocation;superelementId;pointA1;pointA2;pointA3;pointB1;pointB2;pointB3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `pointA1` | `integer` | — | Grid or geometric point 1 in the original interface frame of the part to be positioned. |
| 3 | `pointA2` | `integer` | — | Grid or geometric point 2 in the original interface frame of the part to be positioned. |
| 4 | `pointA3` | `integer` | — | Grid or geometric point 3 in the original interface frame of the part to be positioned. |
| 5 | `pointB1` | `integer` | — | Matching point 1 in the receiving frame after positioning the part. |
| 6 | `pointB2` | `integer` | — | Matching point 2 in the receiving frame after positioning the part. |
| 7 | `pointB3` | `integer` | — | Matching point 3 in the receiving frame after positioning the part. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementLocation;11;1001;1002;1004;901;902;903
~~~

[Model containing this record](../../../validation/models/superelements/se_parts_repeat_tree.oos)

Reading the example gives `superelementId = 11`, `pointA1 = 1001`, `pointA2 = 1002`, `pointA3 = 1004`.

## SuperelementMirrorPlane

The mirror plane of a part superelement, by three points.

**Record format and fields**

`SuperelementMirrorPlane;superelementId;plane;point1;point2;point3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `plane` | `text` | — | Reference plane used for the geometric definition. |
| 3 | `point1` | `integer` | — | Point at position 1 in the ordered SuperelementMirrorPlane data. |
| 4 | `point2` | `integer` | — | Point at position 2 in the ordered SuperelementMirrorPlane data. |
| 5 | `point3` | `integer` | — | Point at position 3 in the ordered SuperelementMirrorPlane data. |

Accepted words: `All`, `Constant`, `Element`, `Plane`, `Table`, `Through`.

**Example record**

~~~text
SuperelementMirrorPlane;20;Plane;901;902;903
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_parts_mirror_mass_sol103.oos)

Reading the example gives `superelementId = 20`, `plane = Plane`, `point1 = 901`, `point2 = 902`.

## SuperelementReleasedDofs

Degrees of freedom of exterior grid points of a superelement that its connection leaves free.

**Record format and fields**

`SuperelementReleasedDofs;superelementId;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `components` | `integer` | Required | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementReleasedDofs;2;4;3
~~~

[Model containing this record](../../../validation/models/superelements/se_main_bulk_list.oos)

Reading the example gives `superelementId = 2`, `components = 4`.

## SuperelementSupport

The fictitious supports of a superelement, the determinate reactions of a free-body analysis.

**Record format and fields**

`SuperelementSupport;superelementId;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 3 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 6 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 7 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementSupport;2;14;123456
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 2`, `node1 = 14`, `components1 = 123456`.

## SuperelementTree

The superelements that are upstream of one, which gives the order of the reduction.

**Record format and fields**

`SuperelementTree;superelementId;<upstreamSuperelements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |

**Repeated group `upstreamSuperelements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `upstreamSuperelementId` | `integer` | — | Identifier selecting the upstream superelement record or set. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementTree;0;1;2;3
~~~

[Model containing this record](../../../validation/models/superelements/se_main_bulk_list.oos)

Reading the example gives `superelementId = 0`.

## SuperelementUserDofSet

Degrees of freedom of a superelement in a set the user names.

**Record format and fields**

`SuperelementUserDofSet;superelementId;setName;node1;components1;node2;components2;node3;components3;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `setName` | `text` | — | Text naming the set. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `components1` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 1. |
| 5 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 6 | `components2` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 2. |
| 7 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 8 | `components3` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. Entry 3. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `All`, `Constant`, `Element`, `Table`, `Through`.

**Example record**

~~~text
SuperelementUserDofSet;1;U4;101;123456;102;3
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `setName = U4`, `node1 = 101`, `components1 = 123456`.

## SuperelementUserDofSet1

The degrees of freedom C of a list of points of a superelement in a set the user names.

**Record format and fields**

`SuperelementUserDofSet1;superelementId;setName;components;<nodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `superelementId` | `integer` | Required | Identifier of the superelement associated with the entry. |
| 2 | `setName` | `text` | — | Text naming the set. |
| 3 | `components` | `integer` | 0 | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `any` | — | Grid point to which this entry applies. |

Accepted words: `All`, `Through`.

**Example record**

~~~text
SuperelementUserDofSet1;1;U4;3;104;Through;106
~~~

[Model containing this record](../../../validation/models/superelements_parts/se_list_cms_sets_sol103.oos)

Reading the example gives `superelementId = 1`, `setName = U4`, `components = 3`.
