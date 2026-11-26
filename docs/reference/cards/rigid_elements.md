# Rigid elements

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## RigidAxisymConnection

A rigid connection between a point of an axisymmetric harmonic element ([AxisymQuad](elements.md#axisymquad) or [AxisymTria](elements.md#axisymtria)) and a point of the three-dimensional model on the axis of symmetry.

**Record format and fields**

`RigidAxisymConnection;id;node3D;axisymNode`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `node3D` | `integer` | Required | Identifier addressing node data. |
| 3 | `axisymNode` | `integer` | Required | Identifier addressing node data. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be an integer from 1 to 99999999.

**Example record**

~~~text
RigidAxisymConnection;301;6;101
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/harmonic_disc_shaft_modes.oos)

Reading the example gives `id = 301`, `node3D = 6`, `axisymNode = 101`.

**Referenced records in this example**

- [Node](nodes.md#node) via `node3D = 6`, `axisymNode = 101`.

## RigidBar

A rigid bar with six degrees of freedom at each end.

**Record format and fields**

`RigidBar;id;nodeA;nodeB;independentComponentsA;independentComponentsB;componentsAtA;componentsAtB;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `independentComponentsA` | `integer` | 0 | Independent degrees of freedom at point A. |
| 5 | `independentComponentsB` | `integer` | 0 | Independent degrees of freedom at point B. |
| 6 | `componentsAtA` | `integer` | 0 | Selected degrees of freedom at point A. |
| 7 | `componentsAtB` | `integer` | 0 | Selected degrees of freedom at point B. |
| 8 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 9 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidBar;501;14;401;123456;;;123456
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 501`, `nodeA = 14`, `nodeB = 401`, `independentComponentsA = 123456`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 14`, `nodeB = 401`.

## RigidBar1

Ties selected motion components of the second endpoint of a rigid bar to the first.

**Record format and fields**

`RigidBar1;id;nodeA;nodeB;componentsB;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `componentsB` | `integer` | 123456 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |
| 5 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidBar1;503;406;407;123456
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 503`, `nodeA = 406`, `nodeB = 407`, `componentsB = 123456`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 406`, `nodeB = 407`.

## RigidBodyMulti

A rigid body connected to any number of grid points, with its independent components given point by point.

**Record format and fields**

`RigidBodyMulti;id;<independents>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |

**Repeated group `independents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentNode` | `integer` | — | Point supplying an independent motion in the constraint. |
| 2 | `independentComponents` | `integer` | — | Component digits supplying the independent motion of a constraint. |

**Keyed sections in `dependentLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DependentDofs`**

**Repeated group `dependents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentNode` | `number` | — | Point whose selected motions are expressed through other degrees of freedom. |
| 2 | `dependentComponents` | `number` | — | Component digits whose motion is determined by the constraint. |

Accepted words: `DependentDofs`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `independentNode1` — the element needs at least one independent point.
- `independentNode1` — the element has at most six independent points.
- `dependentNode1` — the element needs at least one dependent point.
- `independentNode1` — an independent grid point ID must be a positive integer.
- `dependentNode1` — a dependent grid point ID must be a positive integer.
- `dependentComponents1` — a component cannot be both independent and dependent at a grid point.

**Example record**

~~~text
RigidBodyMulti;504;1;407;123456;DependentDofs;2;408;123456;409;123
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 504`.

## RigidBodySearched

A [RigidBodyStar](rigid_elements.md#rigidbodystar) that the solver builds itself.

**Record format and fields**

`RigidBodySearched;id;spotNode;kind;referenceTemperature;radius;dependentComponents;alphaCoefficient;xStation;yStation;zStation;<independentList>;<dependentList>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `spotNode` | `integer` | 0 | Grid point locating the connection spot. |
| 3 | `kind` | `text` | — | Selects the kind for RigidBodySearched. |
| 4 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 5 | `radius` | `real` | Required | Radial dimension measured from the centre or axis (length). |
| 6 | `dependentComponents` | `integer` | 123456 | Component digits whose motion is determined by the constraint. |
| 7 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 8 | `xStation` | `real` | — | X coordinate of the evaluation station. |
| 9 | `yStation` | `real` | — | Y coordinate of the evaluation station. |
| 10 | `zStation` | `real` | — | Z coordinate of the evaluation station. |

**Repeated group `independentList`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `independentNodes` | `any` | — | GNi: grids that may not be the independent grid. |

**Repeated group `dependentList`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentNodes` | `any` | — | GMj: grids that may not be the dependent grid. |

*Note*: a list of nodes may hold THRU between two nodes (a range).

Accepted words: `ClosestRigidBodyStars`, `ClosestRigidBodyStarsSwapped`, `Constant`, `Element`, `EndList`, `Swapped`, `Table`, `Through`.

**Example record**

~~~text
RigidBodySearched;509;406;;;1.
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 509`, `spotNode = 406`, `radius = 1.`.

## RigidBodyStar

A rigid body whose independent degrees of freedom are the six of one grid point and whose dependent degrees of freedom are some components of any number of other grid points.

**Record format and fields**

`RigidBodyStar;id;independentNode;dependentComponents;<dependentNodes>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `independentNode` | `integer` | Required | Identifier addressing node data. |
| 3 | `dependentComponents` | `integer` | Required | Component digits whose motion is determined by the constraint. |

**Repeated group `dependentNodes`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentNode` | `number` | — | Identifier addressing node data. |

*Note*: the list may end with the thermal expansion coefficient, or with that coefficient then the reference temperature: reals, written with a decimal point or an exponent, where a node is an integer.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `dependentNode1` — the element needs at least one dependent grid point.
- `dependentNode1` — a dependent grid point ID must be a positive integer.

**Example record**

~~~text
RigidBodyStar;101;100;123456;5;10
~~~

[Model containing this record](../../../validation/models/hdf5_layouts/hdf5_model.oos)

Reading the example gives `id = 101`, `independentNode = 100`, `dependentComponents = 123456`.

## RigidInterpolation

The motion of a reference grid point is the weighted average of the motion of other grid points.

**Record format and fields**

`RigidInterpolation;id;referenceNode;referenceComponents;<terms>;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `referenceNode` | `integer` | Required | Identifier of the grid point serving as the reference for this definition. |
| 3 | `referenceComponents` | `integer` | Required | Degrees of freedom used as the reference motion. |

**Repeated group `terms`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `weight` | `real` | — | Relative contribution of this term to the specified combination. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

**Repeated group `nodes`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |

**Keyed sections in `parts`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `DependentDofs`**

**Repeated group `dependents`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dependentNode` | `integer` | — | Identifier addressing node data. |
| 2 | `dependentComponents` | `integer` | — | Component digits whose motion is determined by the constraint. |

**Section `ThermalExpansion`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `alphaCoefficient` | `real` | — | Coefficient in the relation for alpha. |
| 2 | `referenceTemperature` | `real` | — | Temperature defining the reference state for these data, in the model’s temperature scale. |

Accepted words: `DependentDofs`, `ThermalExpansion`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `referenceNode` — the reference grid point must be a positive integer.
- `weight1` — the element needs at least one weighted group.
- `node1` — a weighted group needs at least one grid point.
- `node1` — a grid point ID must be a positive integer.

**Example record**

~~~text
RigidInterpolation;5;5;123456;1;1.;123;4;1;2;3;4
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol103_tire_selection.oos)

Reading the example gives `id = 5`, `referenceNode = 5`, `referenceComponents = 123456`.

**Referenced records in this example**

- [Node](nodes.md#node) via `referenceNode = 5`.

## RigidInterpolationOverride

Sets a perturbation for coincident points of selected rigid interpolation elements.

**Record format and fields**

`RigidInterpolationOverride;<elements>`

This part of the record has no fixed fields.

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `integer` | — | Identifier of the element addressed by this record. |
| 2 | `perturbationX` | `real` | — | The perturbation of the X coordinate. |
| 3 | `perturbationY` | `real` | — | ... of the Y coordinate. |
| 4 | `perturbationZ` | `real` | — | ... of the Z coordinate. |
| 5 | `toleranceAdjustment` | `real` | — | Adjustment to the geometric tolerance used when connecting points. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `elemId` — the card needs at least one element.

**Example record**

~~~text
RigidInterpolationOverride;40;0.01;0.02;0.03
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/sol400_spcr_rbe3_coincident.oos)

## RigidJoint

A rigid joint connecting two coinciding grid points.

**Record format and fields**

`RigidJoint;id;nodeA;nodeB;componentsB`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `componentsB` | `integer` | 123456 | Component mask at the indicated endpoint or point. Structural translations use 1–3 and rotations use 4–6. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidJoint;502;404;405
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 502`, `nodeA = 404`, `nodeB = 405`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 404`, `nodeB = 405`.

## RigidMeshConnection

A rigid connection that ties two parts of Lagrangian meshes together (two surfaces, grid points to a surface, or the edge of shells to a shell surface).

**Record format and fields**

`RigidMeshConnection;id;secondaryType;primaryType;secondaryId;primaryId;option;closeGaps;gapMeasure;gapValue`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `secondaryType` | `text` | — | Selects the secondary type for RigidMeshConnection. |
| 3 | `primaryType` | `text` | — | Selects the primary type for RigidMeshConnection. |
| 4 | `secondaryId` | `integer` | Required | Identifier selecting the secondary record or set. |
| 5 | `primaryId` | `integer` | Required | Identifier selecting the primary record or set. |
| 6 | `option` | `text` | — | Selects how the current entry or group is interpreted. |
| 7 | `closeGaps` | `text` | — | Selects whether initial separations are closed when establishing the connection. |
| 8 | `gapMeasure` | `text` | — | Convention used to measure initial separation. |
| 9 | `gapValue` | `real` | — | Specified initial separation in length units. |

Accepted words: `Constant`, `Distance`, `Element`, `No`, `Node`, `Normal`, `Shell`, `Surface`, `Table`, `Yes`.

**Example record**

~~~text
RigidMeshConnection;1;Node;Surface;5;6;Shell
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/sol700_tied_shell_edge.oos)

Reading the example gives `id = 1`, `secondaryType = Node`, `primaryType = Surface`, `secondaryId = 5`.

## RigidRod

A pin-ended element that is rigid in translation.

**Record format and fields**

`RigidRod;id;nodeA;nodeB;componentsAtA;componentsAtB;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `componentsAtA` | `integer` | 0 | Selected degrees of freedom at point A. |
| 5 | `componentsAtB` | `integer` | 0 | Selected degrees of freedom at point B. |
| 6 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 7 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidRod;505;13;402;;2
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 505`, `nodeA = 13`, `nodeB = 402`, `componentsAtB = 2`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 13`, `nodeB = 402`.

## RigidShellSolidConnection

A clamped connection between a shell and a solid element (multipoint constraints).

**Record format and fields**

`RigidShellSolidConnection;id;kind;shellId1;solidIdA1;solidIdB1;shellId2;solidIdA2;solidIdB2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `kind` | `text` | — | Selects the kind for RigidShellSolidConnection. |
| 3 | `shellId1` | `integer` | — | Identifier selecting the shell record or set. |
| 4 | `solidIdA1` | `integer` | — | Identifier of the solid on side A at position 1. |
| 5 | `solidIdB1` | `integer` | — | Identifier of the solid on side B at position 1. |
| 6 | `shellId2` | `integer` | — | Identifier selecting the shell record or set. |
| 7 | `solidIdA2` | `integer` | — | Identifier of the solid on side A at position 2. |
| 8 | `solidIdB2` | `integer` | — | Identifier of the solid on side B at position 2. |

Accepted words: `Constant`, `Element`, `Elements`, `Node`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidShellSolidConnection;301;Node;5;101;102;10;103;104
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 301`, `kind = Node`, `shellId1 = 5`, `solidIdA1 = 101`.

## RigidSpline

Multipoint constraints that interpolate the displacements of grid points along an elastic beam.

**Record format and fields**

`RigidSpline;id;diameterRatio;node1;<points>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `diameterRatio` | `real` | 0.1 | Relative measure of diameter. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |

**Repeated group `points`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `node` | `integer` | — | Grid point to which this entry applies. |
| 2 | `components` | `integer` | — | Degrees of freedom selected at the associated points. For structural grid points, digits 1–3 denote translations and 4–6 denote rotations. |

Accepted words: `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node2` — the element needs at least two grid points.
- `node1` — a grid point ID must be a positive integer.
- `components1` — the first grid point is independent: it has no components field.
- `components` — the last grid point is independent: it has no components field.

**Example record**

~~~text
RigidSpline;508;0.1;429;441;123456;403
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 508`, `diameterRatio = 0.1`, `node1 = 429`.

## RigidTriaPlate

A rigid triangular plate.

**Record format and fields**

`RigidTriaPlate;id;nodeA;nodeB;nodeC;independentComponentsA;independentComponentsB;independentComponentsC;componentsAtA;componentsAtB;componentsAtC;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | — | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | — | Identifier addressing node data. |
| 4 | `nodeC` | `integer` | — | Identifier addressing node data. |
| 5 | `independentComponentsA` | `integer` | — | Independent degrees of freedom at point A. |
| 6 | `independentComponentsB` | `integer` | — | Independent degrees of freedom at point B. |
| 7 | `independentComponentsC` | `integer` | — | Independent degrees of freedom at point C. |
| 8 | `componentsAtA` | `integer` | — | Selected degrees of freedom at point A. |
| 9 | `componentsAtB` | `integer` | — | Selected degrees of freedom at point B. |
| 10 | `componentsAtC` | `integer` | — | Selected degrees of freedom at point C. |
| 11 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 12 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `independentComponentsA` — the plate has no independent component.

**Example record**

~~~text
RigidTriaPlate;506;12;421;423;123456;;;;123456;123456
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 506`, `nodeA = 12`, `nodeB = 421`, `nodeC = 423`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 12`, `nodeB = 421`, `nodeC = 423`.

## RigidTriaPlate1

Ties selected motion components of the second and third points of a rigid triangular plate to the first point.

**Record format and fields**

`RigidTriaPlate1;id;nodeA;nodeB;nodeC;componentsAtB;componentsAtC;alphaCoefficient;referenceTemperature`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `nodeA` | `integer` | Required | Identifier addressing node data. |
| 3 | `nodeB` | `integer` | Required | Identifier addressing node data. |
| 4 | `nodeC` | `integer` | Required | Identifier addressing node data. |
| 5 | `componentsAtB` | `integer` | 123456 | Selected degrees of freedom at point B. |
| 6 | `componentsAtC` | `integer` | 123456 | Selected degrees of freedom at point C. |
| 7 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 8 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.

**Example record**

~~~text
RigidTriaPlate1;507;428;431;432;123456;123
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/rigid_elements_static.oos)

Reading the example gives `id = 507`, `nodeA = 428`, `nodeB = 431`, `nodeC = 432`.

**Referenced records in this example**

- [Node](nodes.md#node) via `nodeA = 428`, `nodeB = 431`, `nodeC = 432`.
