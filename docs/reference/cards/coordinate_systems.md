# Coordinate systems

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## CylindricalFrame1

One cylindrical coordinate system defined by three grid points.

**Record format and fields**

`CylindricalFrame1;frameIdA;node1A;node2A;node3A;frameIdB;node1B;node2B;node3B`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameIdA` | `integer` | — | Identifier of coordinate system A defined by this record. |
| 2 | `node1A` | `integer` | — | Grid point defining the origin of frame A. |
| 3 | `node2A` | `integer` | — | Grid point defining the point on the positive z-axis of frame A. |
| 4 | `node3A` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame A. |
| 5 | `frameIdB` | `integer` | — | Identifier of coordinate system B defined by this record. |
| 6 | `node1B` | `integer` | — | Grid point defining the origin of frame B. |
| 7 | `node2B` | `integer` | — | Grid point defining the point on the positive z-axis of frame B. |
| 8 | `node3B` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame B. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.

**Example record**

~~~text
CylindricalFrame1;10;1001;1002;1003
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `frameIdA = 10`, `node1A = 1001`, `node2A = 1002`, `node3A = 1003`.

## CylindricalFrame2

A cylindrical coordinate system defined by three points.

**Record format and fields**

`CylindricalFrame2;id;referenceFrameId;pointA1;pointA2;pointA3;pointB1;pointB2;pointB3;pointC1;pointC2;pointC3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the coordinate namespace. |
| 2 | `referenceFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 3 | `pointA1` | `real` | 0.0 | Coordinate 1 of the origin, expressed in the reference frame. |
| 4 | `pointA2` | `real` | 0.0 | Coordinate 2 of the origin, expressed in the reference frame. |
| 5 | `pointA3` | `real` | 0.0 | Coordinate 3 of the origin, expressed in the reference frame. |
| 6 | `pointB1` | `real` | 0.0 | Coordinate 1 of the point on the positive z-axis, expressed in the reference frame. |
| 7 | `pointB2` | `real` | 0.0 | Coordinate 2 of the point on the positive z-axis, expressed in the reference frame. |
| 8 | `pointB3` | `real` | 0.0 | Coordinate 3 of the point on the positive z-axis, expressed in the reference frame. |
| 9 | `pointC1` | `real` | 0.0 | Coordinate 1 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 10 | `pointC2` | `real` | 0.0 | Coordinate 2 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 11 | `pointC3` | `real` | 0.0 | Coordinate 3 of the point in the positive x–z half-plane, expressed in the reference frame. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `referenceFrameId` — `referenceFrameId` must be 0 or a coordinate system ID.
- `referenceFrameId` — a coordinate system cannot be defined with respect to itself.

**Example record**

~~~text
CylindricalFrame2;1;;0.;0.;0.;0.;0.;1.;1.;0.;0.
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 1`, `pointA1 = 0.`, `pointA2 = 0.`, `pointA3 = 0.`.

## GeneralFrame3

A general coordinate system whose three rotation angles are functions of the coordinates in the reference system.

**Record format and fields**

`GeneralFrame3;id;methodName;matrixForm;angleFunctionId1;angleFunctionId2;angleFunctionId3;referenceFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the coordinate namespace. |
| 2 | `methodName` | `text` | EulerAngles313 | Rotation convention and axis sequence used to construct the moving frame. |
| 3 | `matrixForm` | `text` | EquationForm | Selects whether angles are supplied by equations or by multidimensional tables. |
| 4 | `angleFunctionId1` | `integer` | — | Identifier selecting the angle function record or set. |
| 5 | `angleFunctionId2` | `integer` | — | Identifier selecting the angle function record or set. |
| 6 | `angleFunctionId3` | `integer` | — | Identifier selecting the angle function record or set. |
| 7 | `referenceFrameId` | `integer` | 0 | Identifier addressing coordinate data. |

Accepted words: `EquationForm`, `EulerAngles313`, `SpaceFixed321`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `methodName` — `methodName` must be EulerAngles or SpaceFixed followed by three digits (EulerAngles313, SpaceFixed321).
- `matrixForm` — `matrixForm` must be EquationForm or Table.
- `referenceFrameId` — `referenceFrameId` must be 0 or a coordinate system ID.
- `referenceFrameId` — a coordinate system cannot be defined with respect to itself.

**Example record**

~~~text
GeneralFrame3;100;EulerAngles313;Table;111;112;113;0
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol101_layered_solid_cord3g.oos)

Reading the example gives `id = 100`, `methodName = EulerAngles313`, `matrixForm = Table`, `angleFunctionId1 = 111`.

## RectFrame1

One rectangular coordinate system defined by three grid points.

**Record format and fields**

`RectFrame1;frameIdA;node1A;node2A;node3A;frameIdB;node1B;node2B;node3B`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameIdA` | `integer` | — | Identifier of coordinate system A defined by this record. |
| 2 | `node1A` | `integer` | — | Grid point defining the origin of frame A. |
| 3 | `node2A` | `integer` | — | Grid point defining the point on the positive z-axis of frame A. |
| 4 | `node3A` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame A. |
| 5 | `frameIdB` | `integer` | — | Identifier of coordinate system B defined by this record. |
| 6 | `node1B` | `integer` | — | Grid point defining the origin of frame B. |
| 7 | `node2B` | `integer` | — | Grid point defining the point on the positive z-axis of frame B. |
| 8 | `node3B` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame B. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.

**Example record**

~~~text
RectFrame1;20;1104;1124;1103
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `frameIdA = 20`, `node1A = 1104`, `node2A = 1124`, `node3A = 1103`.

## RectFrame2

A rectangular coordinate system defined by three points.

**Record format and fields**

`RectFrame2;id;referenceFrameId;pointA1;pointA2;pointA3;pointB1;pointB2;pointB3;pointC1;pointC2;pointC3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the coordinate namespace. |
| 2 | `referenceFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 3 | `pointA1` | `real` | 0.0 | Coordinate 1 of the origin, expressed in the reference frame. |
| 4 | `pointA2` | `real` | 0.0 | Coordinate 2 of the origin, expressed in the reference frame. |
| 5 | `pointA3` | `real` | 0.0 | Coordinate 3 of the origin, expressed in the reference frame. |
| 6 | `pointB1` | `real` | 0.0 | Coordinate 1 of the point on the positive z-axis, expressed in the reference frame. |
| 7 | `pointB2` | `real` | 0.0 | Coordinate 2 of the point on the positive z-axis, expressed in the reference frame. |
| 8 | `pointB3` | `real` | 0.0 | Coordinate 3 of the point on the positive z-axis, expressed in the reference frame. |
| 9 | `pointC1` | `real` | 0.0 | Coordinate 1 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 10 | `pointC2` | `real` | 0.0 | Coordinate 2 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 11 | `pointC3` | `real` | 0.0 | Coordinate 3 of the point in the positive x–z half-plane, expressed in the reference frame. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `referenceFrameId` — `referenceFrameId` must be 0 or a coordinate system ID.
- `referenceFrameId` — a coordinate system cannot be defined with respect to itself.

**Example record**

~~~text
RectFrame2;7;;0.;0.;0.;0.;0.;1.;1.;1.;0.
~~~

[Model containing this record](../../../validation/models/frames/frames_shell_model.oos)

Reading the example gives `id = 7`, `pointA1 = 0.`, `pointA2 = 0.`, `pointA3 = 0.`.

## RectFrame3

One moving rectangular coordinate system defined by three grid points.

**Record format and fields**

`RectFrame3;frameIdA;node1A;node2A;node3A;frameIdB;node1B;node2B;node3B`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameIdA` | `integer` | — | Identifier of coordinate system A defined by this record. |
| 2 | `node1A` | `integer` | — | Grid point defining the origin of frame A. |
| 3 | `node2A` | `integer` | — | Grid point defining the point on the positive z-axis of frame A. |
| 4 | `node3A` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame A. |
| 5 | `frameIdB` | `integer` | — | Identifier of coordinate system B defined by this record. |
| 6 | `node1B` | `integer` | — | Grid point defining the origin of frame B. |
| 7 | `node2B` | `integer` | — | Grid point defining the point on the positive z-axis of frame B. |
| 8 | `node3B` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame B. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.

**Example record**

~~~text
RectFrame3;50;201;207;203
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/sol700_tied_shell_edge.oos)

Reading the example gives `frameIdA = 50`, `node1A = 201`, `node2A = 207`, `node3A = 203`.

## SphericalFrame1

One spherical coordinate system defined by three grid points.

**Record format and fields**

`SphericalFrame1;frameIdA;node1A;node2A;node3A;frameIdB;node1B;node2B;node3B`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `frameIdA` | `integer` | — | Identifier of coordinate system A defined by this record. |
| 2 | `node1A` | `integer` | — | Grid point defining the origin of frame A. |
| 3 | `node2A` | `integer` | — | Grid point defining the point on the positive z-axis of frame A. |
| 4 | `node3A` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame A. |
| 5 | `frameIdB` | `integer` | — | Identifier of coordinate system B defined by this record. |
| 6 | `node1B` | `integer` | — | Grid point defining the origin of frame B. |
| 7 | `node2B` | `integer` | — | Grid point defining the point on the positive z-axis of frame B. |
| 8 | `node3B` | `integer` | — | Grid point defining the point in the positive x–z half-plane of frame B. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `node1` — the grid point IDs must be positive integers.
- `node1` — the three grid points must all be different.

**Example record**

~~~text
SphericalFrame1;30;1001;1002;1003;31;1001;1003;1002
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `frameIdA = 30`, `node1A = 1001`, `node2A = 1002`, `node3A = 1003`.

## SphericalFrame2

A spherical coordinate system defined by three points.

**Record format and fields**

`SphericalFrame2;id;referenceFrameId;pointA1;pointA2;pointA3;pointB1;pointB2;pointB3;pointC1;pointC2;pointC3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the coordinate namespace. |
| 2 | `referenceFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 3 | `pointA1` | `real` | 0.0 | Coordinate 1 of the origin, expressed in the reference frame. |
| 4 | `pointA2` | `real` | 0.0 | Coordinate 2 of the origin, expressed in the reference frame. |
| 5 | `pointA3` | `real` | 0.0 | Coordinate 3 of the origin, expressed in the reference frame. |
| 6 | `pointB1` | `real` | 0.0 | Coordinate 1 of the point on the positive z-axis, expressed in the reference frame. |
| 7 | `pointB2` | `real` | 0.0 | Coordinate 2 of the point on the positive z-axis, expressed in the reference frame. |
| 8 | `pointB3` | `real` | 0.0 | Coordinate 3 of the point on the positive z-axis, expressed in the reference frame. |
| 9 | `pointC1` | `real` | 0.0 | Coordinate 1 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 10 | `pointC2` | `real` | 0.0 | Coordinate 2 of the point in the positive x–z half-plane, expressed in the reference frame. |
| 11 | `pointC3` | `real` | 0.0 | Coordinate 3 of the point in the positive x–z half-plane, expressed in the reference frame. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the coordinate system ID must be a positive integer.
- `referenceFrameId` — `referenceFrameId` must be 0 or a coordinate system ID.
- `referenceFrameId` — a coordinate system cannot be defined with respect to itself.

**Example record**

~~~text
SphericalFrame2;2;;0.;0.;0.;0.;0.;1.;1.;0.;0.
~~~

[Model containing this record](../../../validation/models/mass_geometry/geometry_orientation_cd.oos)

Reading the example gives `id = 2`, `pointA1 = 0.`, `pointA2 = 0.`, `pointA3 = 0.`.
