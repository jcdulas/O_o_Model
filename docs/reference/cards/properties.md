# Element properties

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AxisymHarmonicProp

The properties of the linear axisymmetric harmonic elements [AxisymQuad](elements.md#axisymquad) and [AxisymTria](elements.md#axisymtria).

**Record format and fields**

`AxisymHarmonicProp;id;matId;frameId;harmonicIndex;integration`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `harmonicIndex` | `integer` | — | Integer index specifying the harmonic represented. |
| 5 | `integration` | `integer` | 0 | Selects the rule used to integrate the element or section response. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
AxisymHarmonicProp;7;1;0;1
~~~

[Model containing this record](../../../validation/models/rotordynamics/rotor_axisymmetric_sol107.oos)

Reading the example gives `id = 7`, `matId = 1`, `frameId = 0`, `harmonicIndex = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## AxisymShellProp

The property of the axisymmetric line element [ShellAxisym](elements.md#shellaxisym).

**Record format and fields**

`AxisymShellProp;id;matId;thickness1;thickness2;analysisType`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness1` | `real` | — | Through-thickness dimension, in model length units. Entry 1. |
| 4 | `thickness2` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 2. |
| 5 | `analysisType` | `text` | — | Selects the analysis type for AxisymShellProp. |

Accepted words: `Constant`, `Element`, `Heat`, `Structural`, `StructuralAndHeat`, `Table`.

**Example record**

~~~text
AxisymShellProp;30;1;2.;;Structural
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_axisymmetric_cohesive.oos)

Reading the example gives `id = 30`, `matId = 1`, `thickness1 = 2.`, `analysisType = Structural`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## BarProp

The property of a simple beam element ([Bar2](elements.md#bar2)).

**Record format and fields**

`BarProp;id;matId;area;bendingInertia1;bendingInertia2;torsionConstant;nonStructMass;stressPointCy;stressPointCz;stressPointDy;stressPointDz;stressPointEy;stressPointEz;stressPointFy;stressPointFz;shearFactor1;shearFactor2;productInertia12`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | 0.0 | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertia1` | `real` | 0.0 | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertia2` | `real` | 0.0 | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 7 | `nonStructMass` | `real` | 0.0 | Additional mass per unit bar length. |
| 8 | `stressPointCy` | `real` | — | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 9 | `stressPointCz` | `real` | — | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stressPointDy` | `real` | — | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 11 | `stressPointDz` | `real` | — | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stressPointEy` | `real` | — | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 13 | `stressPointEz` | `real` | — | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stressPointFy` | `real` | — | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 15 | `stressPointFz` | `real` | — | Local z coordinate of stress-recovery point F in the cross-section (length). |
| 16 | `shearFactor1` | `real` | — | Multiplier for shear. |
| 17 | `shearFactor2` | `real` | — | Multiplier for shear. |
| 18 | `productInertia12` | `real` | 0.0 | Product of section area about the local bending axes (length to the fourth power). |

Designable field descriptors: area, bendingInertia1, bendingInertia2, torsionConstant, nonStructMass, stressPointCy, stressPointCz, stressPointDy, stressPointDz, stressPointEy, stressPointEz, stressPointFy, stressPointFz, shearFactor1, shearFactor2, productInertia12.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
BarProp;8;1;20.;40.;30.;50.
~~~

[Model containing this record](../../../validation/models/card_namespaces/namespace_celas2_cbar.oos)

Reading the example gives `id = 8`, `matId = 1`, `area = 20.`, `bendingInertia1 = 40.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## BarPropNonlinear

The nonlinear extension of the [BarProp](properties.md#barprop) or [BarShapeProp](properties.md#barshapeprop) with the same property ID.

**Record format and fields**

`BarPropNonlinear;id;matId;sectionIntegration;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionIntegration` | `text` | — | Integration convention for recovering the section response. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `TwoNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior2` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 2. |
| 2 | `integration2` | `text` | — | Selects the rule used to integrate the element or section response. Entry 2. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `Element`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `TwoNodeElems`.

**Example record**

~~~text
BarPropNonlinear;201;;Smeared;TwoNodeElems;Bar;LinearCubic
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_property_extensions.oos)

Reading the example gives `id = 201`, `sectionIntegration = Smeared`.

**Referenced records in this example**

- [BarProp](properties.md#barprop) via `id = 201`.

## BarShapeProp

A simple beam property given by the dimensions of its cross-section.

**Record format and fields**

`BarShapeProp;id;matId;sectionGroup;kind;<dimensions>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BarShapeProp. |

**Repeated group `dimensions`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dimension` | `real` | — | Spatial dimension or section dimension according to the selected entry. |

Accepted words: `Bar`, `Box`, `Box1`, `Channel`, `Channel1`, `Channel2`, `Cross`, `DoubleBoxSection`, `HSection`, `Hat`, `Hat1`, `Hexagon`, `ISection`, `ISection1`, `LSection`, `Rod`, `StandardSectionLibrary`, `TSection`, `TSection1`, `TSection2`, `Tube`, `Tube2`, `ZSection`.

Designable field descriptors: dimension(1), dimension(2), ... and nonStructMass.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
BarShapeProp;107;1;;Box;20.;15.;1.5;2.
~~~

[Model containing this record](../../../validation/models/sections/sections_model.oos)

Reading the example gives `id = 107`, `matId = 1`, `kind = Box`.

## BeamLumpedAreaProp

The alternate form of a [BeamProp](properties.md#beamprop) for a uniform beam, with the lumped areas of its cross-section.

**Record format and fields**

`BeamLumpedAreaProp;id;matId;area;bendingInertia1;bendingInertia2;productInertia12;torsionConstant;nonStructMass;shearFactor1;shearFactor2;nsmCenterY;nsmCenterZ;neutralAxisY;neutralAxisZ;symmetricOption;<areas>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | Required | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertia1` | `real` | 0.0 | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertia2` | `real` | 0.0 | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `productInertia12` | `real` | 0.0 | Product of section area about the local bending axes (length to the fourth power). |
| 7 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 9 | `shearFactor1` | `real` | 1.0 | Multiplier for shear. |
| 10 | `shearFactor2` | `real` | 1.0 | Multiplier for shear. |
| 11 | `nsmCenterY` | `real` | 0.0 | Local Y coordinate of the centre of nonstructural mass (length). |
| 12 | `nsmCenterZ` | `real` | 0.0 | Local Z coordinate of the centre of nonstructural mass (length). |
| 13 | `neutralAxisY` | `real` | 0.0 | Local Y coordinate of the elastic neutral axis (length). |
| 14 | `neutralAxisZ` | `real` | 0.0 | Local Z coordinate of the elastic neutral axis (length). |
| 15 | `symmetricOption` | `integer` | 0 | Selects the symmetric option for BeamLumpedAreaProp. |

**Repeated group `areas`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `areaY` | `real` | — | Section area associated with the local y direction (length squared). |
| 2 | `areaZ` | `real` | — | Section area associated with the local z direction (length squared). |
| 3 | `areaFraction` | `real` | — | Portion of the reference area participating in the model. |
| 4 | `areaMatId` | `integer` | — | Identifier addressing material data. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `areaY` — the card has at most 20 lumped areas.
- `areaMatId` — a lumped area needs a material ID.

**Example record**

~~~text
BeamLumpedAreaProp;41;1;100.;833.3;833.3;0.;1406.;;;;;;;;1;2.887;2.887;0.25;1
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `id = 41`, `matId = 1`, `area = 100.`, `bendingInertia1 = 833.3`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## BeamProp

The property of a beam element ([Beam2](elements.md#beam2)) that may taper.

**Record format and fields**

Forms: `noStressPointsAtEndA`, `stressPointsAtEndA`.

### BeamProp: noStressPointsAtEndA

Form `noStressPointsAtEndA`, when `stations` is a word.

`BeamProp;id;matId;area;bendingInertia1;bendingInertia2;productInertia12;torsionConstant;nonStructMass;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | — | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `productInertia12` | `real` | 0.0 | Product of section area about the local bending axes (length to the fourth power). |
| 7 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass per unit beam length. |

**Keyed sections in `stations`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Yes`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |
| 8 | `stationStressPointCy` | `real` | — | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 9 | `stationStressPointCz` | `real` | — | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stationStressPointDy` | `real` | — | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 11 | `stationStressPointDz` | `real` | — | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stationStressPointEy` | `real` | — | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 13 | `stationStressPointEz` | `real` | — | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stationStressPointFy` | `real` | — | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 15 | `stationStressPointFz` | `real` | — | Local z coordinate of stress-recovery point F in the cross-section (length). |

**Section `YesSameAsEndA`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

**Section `No`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `shearFactor1` | `real` | — | Multiplier for shear. |
| 2 | `shearFactor2` | `real` | — | Multiplier for shear. |
| 3 | `shearRelief1` | `real` | — | Shear relief coefficients due to taper. |
| 4 | `shearRelief2` | `real` | — | Shear-relief coefficient for section direction 2, accounting for taper. |
| 5 | `nsmInertiaA` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end A, about the indicated local axes. |
| 6 | `nsmInertiaB` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end B, about the indicated local axes. |
| 7 | `warpingCoefficientA` | `real` | — | Section coefficient for restrained warping at end A. |
| 8 | `warpingCoefficientB` | `real` | — | Section coefficient for restrained warping at end B. |
| 9 | `nsmCenterYA` | `real` | — | Local Y coordinate of the centre of nonstructural mass at end A (length). |
| 10 | `nsmCenterZA` | `real` | — | Local Z coordinate of the centre of nonstructural mass at end A (length). |
| 11 | `nsmCenterYB` | `real` | — | Local Y coordinate of the centre of nonstructural mass at end B (length). |
| 12 | `nsmCenterZB` | `real` | — | Local Z coordinate of the centre of nonstructural mass at end B (length). |
| 13 | `neutralAxisYA` | `real` | — | Local Y coordinate of the elastic neutral axis at end A (length). |
| 14 | `neutralAxisZA` | `real` | — | Local Z coordinate of the elastic neutral axis at end A (length). |
| 15 | `neutralAxisYB` | `real` | — | Local Y coordinate of the elastic neutral axis at end B (length). |
| 16 | `neutralAxisZB` | `real` | — | Local Z coordinate of the elastic neutral axis at end B (length). |

### BeamProp: stressPointsAtEndA

Form `stressPointsAtEndA`, for every other record.

`BeamProp;id;matId;area;bendingInertia1;bendingInertia2;productInertia12;torsionConstant;nonStructMass;stressPointCy;stressPointCz;stressPointDy;stressPointDz;stressPointEy;stressPointEz;stressPointFy;stressPointFz;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | — | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `productInertia12` | `real` | 0.0 | Product of section area about the local bending axes (length to the fourth power). |
| 7 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass per unit beam length. |
| 9 | `stressPointCy` | `real` | 0.0 | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stressPointCz` | `real` | 0.0 | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 11 | `stressPointDy` | `real` | 0.0 | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stressPointDz` | `real` | 0.0 | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 13 | `stressPointEy` | `real` | 0.0 | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stressPointEz` | `real` | 0.0 | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 15 | `stressPointFy` | `real` | 0.0 | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 16 | `stressPointFz` | `real` | 0.0 | Local z coordinate of stress-recovery point F in the cross-section (length). |

**Keyed sections in `stations`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Yes`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |
| 8 | `stationStressPointCy` | `real` | — | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 9 | `stationStressPointCz` | `real` | — | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stationStressPointDy` | `real` | — | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 11 | `stationStressPointDz` | `real` | — | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stationStressPointEy` | `real` | — | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 13 | `stationStressPointEz` | `real` | — | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stationStressPointFy` | `real` | — | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 15 | `stationStressPointFz` | `real` | — | Local z coordinate of stress-recovery point F in the cross-section (length). |

**Section `YesSameAsEndA`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

**Section `No`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 2 | `stationArea` | `real` | — | Station area (length squared). |
| 3 | `stationBendingInertia1` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 4 | `stationBendingInertia2` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `stationProductInertia12` | `real` | — | Product of section area about the local bending axes (length to the fourth power). |
| 6 | `stationTorsionConstant` | `real` | — | Section torsion constant; it multiplies the shear modulus in the torsional rigidity. |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `shearFactor1` | `real` | — | Multiplier for shear. |
| 2 | `shearFactor2` | `real` | — | Multiplier for shear. |
| 3 | `shearRelief1` | `real` | — | Shear relief coefficients due to taper. |
| 4 | `shearRelief2` | `real` | — | Shear-relief coefficient for section direction 2, accounting for taper. |
| 5 | `nsmInertiaA` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end A, about the indicated local axes. |
| 6 | `nsmInertiaB` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end B, about the indicated local axes. |
| 7 | `warpingCoefficientA` | `real` | — | Section coefficient for restrained warping at end A. |
| 8 | `warpingCoefficientB` | `real` | — | Section coefficient for restrained warping at end B. |
| 9 | `nsmCenterYA` | `real` | — | Local Y coordinate of the centre of nonstructural mass at end A (length). |
| 10 | `nsmCenterZA` | `real` | — | Local Z coordinate of the centre of nonstructural mass at end A (length). |
| 11 | `nsmCenterYB` | `real` | — | Local Y coordinate of the centre of nonstructural mass at end B (length). |
| 12 | `nsmCenterZB` | `real` | — | Local Z coordinate of the centre of nonstructural mass at end B (length). |
| 13 | `neutralAxisYA` | `real` | — | Local Y coordinate of the elastic neutral axis at end A (length). |
| 14 | `neutralAxisZA` | `real` | — | Local Z coordinate of the elastic neutral axis at end A (length). |
| 15 | `neutralAxisYB` | `real` | — | Local Y coordinate of the elastic neutral axis at end B (length). |
| 16 | `neutralAxisZB` | `real` | — | Local Z coordinate of the elastic neutral axis at end B (length). |

Accepted words: `No`, `Yes`, `YesSameAsEndA`.

Designable field descriptors: area, bendingInertia1, bendingInertia2, productInertia12, torsionConstant, nonStructMass, stressPointCy to stressPointFz with a station (EndA), (EndB) or (i), and shearFactor1, shearFactor2, shearRelief1, shearRelief2, nsmInertia(EndA), nsmInertia(EndB), warpingCoefficient(EndA), warpingCoefficient(EndB), nsmCenterY(EndA), nsmCenterZ(EndA), nsmCenterY(EndB), nsmCenterZ(EndB), neutralAxisY(EndA), neutralAxisZ(EndA), neutralAxisY(EndB), neutralAxisZ(EndB).

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `stationRatio` — the card has end A and at most ten more stations.
- `stressOutput` — the line of stress points at end A can only be left out when other stations follow.

**Example record**

~~~text
BeamProp;2;1;20.;40.;30.;0.;50.
~~~

[Model containing this record](../../../validation/models/mass_geometry/geometry_orientation_cd.oos)

## BeamProp3

The property of a three-node beam element ([Beam3](elements.md#beam3)).

**Record format and fields**

`BeamProp3;id;matId;area;bendingInertiaZ;bendingInertiaY;productInertiaYZ;torsionConstant;nonStructMass;stressPointCy;stressPointCz;stressPointDy;stressPointDz;stressPointEy;stressPointEz;stressPointFy;stressPointFz;stressOutputEndB;areaEndB;bendingInertiaZEndB;bendingInertiaYEndB;productInertiaYZEndB;torsionConstantEndB;nonStructMassEndB;stressPointCyEndB;stressPointCzEndB;stressPointDyEndB;stressPointDzEndB;stressPointEyEndB;stressPointEzEndB;stressPointFyEndB;stressPointFzEndB;stressOutputNodeC;areaNodeC;bendingInertiaZNodeC;bendingInertiaYNodeC;productInertiaYZNodeC;torsionConstantNodeC;nonStructMassNodeC;stressPointCyNodeC;stressPointCzNodeC;stressPointDyNodeC;stressPointDzNodeC;stressPointEyNodeC;stressPointEzNodeC;stressPointFyNodeC;stressPointFzNodeC;shearFactorY;shearFactorZ;neutralAxisY;neutralAxisZ;neutralAxisYEndB;neutralAxisZEndB;neutralAxisYNodeC;neutralAxisZNodeC;nsmCenterY;nsmCenterZ;nsmCenterYEndB;nsmCenterZEndB;nsmCenterYNodeC;nsmCenterZNodeC;nsmInertiaY;nsmInertiaZ;nsmInertiaYZ;nsmInertiaYEndB;nsmInertiaZEndB;nsmInertiaYZEndB;nsmInertiaYNodeC;nsmInertiaZNodeC;nsmInertiaYZNodeC;warpingCoefficient;warpingCoefficientEndB;warpingCoefficientNodeC;stressLocation;warpingAtC;warpingGradientYAtC;warpingGradientZAtC;warpingAtD;warpingGradientYAtD;warpingGradientZAtD;warpingAtE;warpingGradientYAtE;warpingGradientZAtE;warpingAtF;warpingGradientYAtF;warpingGradientZAtF;warpingAtCEndB;warpingGradientYAtCEndB;warpingGradientZAtCEndB;warpingAtDEndB;warpingGradientYAtDEndB;warpingGradientZAtDEndB;warpingAtEEndB;warpingGradientYAtEEndB;warpingGradientZAtEEndB;warpingAtFEndB;warpingGradientYAtFEndB;warpingGradientZAtFEndB;warpingAtCNodeC;warpingGradientYAtCNodeC;warpingGradientZAtCNodeC;warpingAtDNodeC;warpingGradientYAtDNodeC;warpingGradientZAtDNodeC;warpingAtENodeC;warpingGradientYAtENodeC;warpingGradientZAtENodeC;warpingAtFNodeC;warpingGradientYAtFNodeC;warpingGradientZAtFNodeC`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | Required | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertiaZ` | `real` | Required | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertiaY` | `real` | Required | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `productInertiaYZ` | `real` | 0.0 | Product of section area about the local bending axes (length to the fourth power). |
| 7 | `torsionConstant` | `real` | — | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 9 | `stressPointCy` | `real` | 0.0 | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stressPointCz` | `real` | 0.0 | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 11 | `stressPointDy` | `real` | 0.0 | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stressPointDz` | `real` | 0.0 | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 13 | `stressPointEy` | `real` | 0.0 | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stressPointEz` | `real` | 0.0 | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 15 | `stressPointFy` | `real` | 0.0 | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 16 | `stressPointFz` | `real` | 0.0 | Local z coordinate of stress-recovery point F in the cross-section (length). |
| 17 | `stressOutputEndB` | `text` | — | Controls stress recovery at the specified section location at end B. |
| 18 | `areaEndB` | `real` | — | Cross-sectional area at end B (length squared). |
| 19 | `bendingInertiaZEndB` | `real` | — | Second moment of the section area for bending about the indicated local axis at end B (length to the fourth power). |
| 20 | `bendingInertiaYEndB` | `real` | — | Second moment of the section area for bending about the indicated local axis at end B (length to the fourth power). |
| 21 | `productInertiaYZEndB` | `real` | — | Product of section area about the local bending axes at end B (length to the fourth power). |
| 22 | `torsionConstantEndB` | `real` | — | Section torsion constant at end B; it multiplies the shear modulus in the torsional rigidity. |
| 23 | `nonStructMassEndB` | `real` | — | Additional mass per unit member length at end B. |
| 24 | `stressPointCyEndB` | `real` | 0.0 | Local y coordinate of stress-recovery point C at end B in the cross-section (length). |
| 25 | `stressPointCzEndB` | `real` | 0.0 | Local z coordinate of stress-recovery point C at end B in the cross-section (length). |
| 26 | `stressPointDyEndB` | `real` | 0.0 | Local y coordinate of stress-recovery point D at end B in the cross-section (length). |
| 27 | `stressPointDzEndB` | `real` | 0.0 | Local z coordinate of stress-recovery point D at end B in the cross-section (length). |
| 28 | `stressPointEyEndB` | `real` | 0.0 | Local y coordinate of stress-recovery point E at end B in the cross-section (length). |
| 29 | `stressPointEzEndB` | `real` | 0.0 | Local z coordinate of stress-recovery point E at end B in the cross-section (length). |
| 30 | `stressPointFyEndB` | `real` | 0.0 | Local y coordinate of stress-recovery point F at end B in the cross-section (length). |
| 31 | `stressPointFzEndB` | `real` | 0.0 | Local z coordinate of stress-recovery point F at end B in the cross-section (length). |
| 32 | `stressOutputNodeC` | `text` | — | Controls stress recovery at the specified section location at node C. |
| 33 | `areaNodeC` | `real` | — | Cross-sectional area at node C (length squared). |
| 34 | `bendingInertiaZNodeC` | `real` | — | Second moment of the section area for bending about the indicated local axis at node C (length to the fourth power). |
| 35 | `bendingInertiaYNodeC` | `real` | — | Second moment of the section area for bending about the indicated local axis at node C (length to the fourth power). |
| 36 | `productInertiaYZNodeC` | `real` | — | Product of section area about the local bending axes at node C (length to the fourth power). |
| 37 | `torsionConstantNodeC` | `real` | — | Section torsion constant at node C; it multiplies the shear modulus in the torsional rigidity. |
| 38 | `nonStructMassNodeC` | `real` | — | Additional mass per unit member length at node C. |
| 39 | `stressPointCyNodeC` | `real` | 0.0 | Local y coordinate of stress-recovery point C at node C in the cross-section (length). |
| 40 | `stressPointCzNodeC` | `real` | 0.0 | Local z coordinate of stress-recovery point C at node C in the cross-section (length). |
| 41 | `stressPointDyNodeC` | `real` | 0.0 | Local y coordinate of stress-recovery point D at node C in the cross-section (length). |
| 42 | `stressPointDzNodeC` | `real` | 0.0 | Local z coordinate of stress-recovery point D at node C in the cross-section (length). |
| 43 | `stressPointEyNodeC` | `real` | 0.0 | Local y coordinate of stress-recovery point E at node C in the cross-section (length). |
| 44 | `stressPointEzNodeC` | `real` | 0.0 | Local z coordinate of stress-recovery point E at node C in the cross-section (length). |
| 45 | `stressPointFyNodeC` | `real` | 0.0 | Local y coordinate of stress-recovery point F at node C in the cross-section (length). |
| 46 | `stressPointFzNodeC` | `real` | 0.0 | Local z coordinate of stress-recovery point F at node C in the cross-section (length). |
| 47 | `shearFactorY` | `real` | 1.0 | Shear effectiveness factors in the local y and z directions. |
| 48 | `shearFactorZ` | `real` | 1.0 | Correction multiplying the section shear response in local z. |
| 49 | `neutralAxisY` | `real` | — | Local Y coordinate of the elastic neutral axis (length). |
| 50 | `neutralAxisZ` | `real` | — | Local Z coordinate of the elastic neutral axis (length). |
| 51 | `neutralAxisYEndB` | `real` | — | Local Y coordinate of the elastic neutral axis at end B (length). |
| 52 | `neutralAxisZEndB` | `real` | — | Local Z coordinate of the elastic neutral axis at end B (length). |
| 53 | `neutralAxisYNodeC` | `real` | — | Local Y coordinate of the elastic neutral axis at node C (length). |
| 54 | `neutralAxisZNodeC` | `real` | — | Local Z coordinate of the elastic neutral axis at node C (length). |
| 55 | `nsmCenterY` | `real` | — | Local Y coordinate of the centre of nonstructural mass (length). |
| 56 | `nsmCenterZ` | `real` | — | Local Z coordinate of the centre of nonstructural mass (length). |
| 57 | `nsmCenterYEndB` | `real` | — | Local Y coordinate of the centre of nonstructural mass at end B (length). |
| 58 | `nsmCenterZEndB` | `real` | — | Local Z coordinate of the centre of nonstructural mass at end B (length). |
| 59 | `nsmCenterYNodeC` | `real` | — | Local Y coordinate of the centre of nonstructural mass at node C (length). |
| 60 | `nsmCenterZNodeC` | `real` | — | Local Z coordinate of the centre of nonstructural mass at node C (length). |
| 61 | `nsmInertiaY` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass, about the indicated local axes. |
| 62 | `nsmInertiaZ` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass, about the indicated local axes. |
| 63 | `nsmInertiaYZ` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass, about the indicated local axes. |
| 64 | `nsmInertiaYEndB` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end B, about the indicated local axes. |
| 65 | `nsmInertiaZEndB` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end B, about the indicated local axes. |
| 66 | `nsmInertiaYZEndB` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at end B, about the indicated local axes. |
| 67 | `nsmInertiaYNodeC` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at node C, about the indicated local axes. |
| 68 | `nsmInertiaZNodeC` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at node C, about the indicated local axes. |
| 69 | `nsmInertiaYZNodeC` | `real` | — | Sectional mass moment or product of inertia of the nonstructural mass at node C, about the indicated local axes. |
| 70 | `warpingCoefficient` | `real` | — | Section coefficient for restrained warping. |
| 71 | `warpingCoefficientEndB` | `real` | — | Section coefficient for restrained warping at end B. |
| 72 | `warpingCoefficientNodeC` | `real` | — | Section coefficient for restrained warping at node C. |
| 73 | `stressLocation` | `text` | — | Location in the element or section at which stress is evaluated. |
| 74 | `warpingAtC` | `real` | — | Section warping function at recovery point C. |
| 75 | `warpingGradientYAtC` | `real` | — | Derivative of the section warping function in local Y at recovery point C. |
| 76 | `warpingGradientZAtC` | `real` | — | Derivative of the section warping function in local Z at recovery point C. |
| 77 | `warpingAtD` | `real` | — | Section warping function at recovery point D. |
| 78 | `warpingGradientYAtD` | `real` | — | Derivative of the section warping function in local Y at recovery point D. |
| 79 | `warpingGradientZAtD` | `real` | — | Derivative of the section warping function in local Z at recovery point D. |
| 80 | `warpingAtE` | `real` | — | Section warping function at recovery point E. |
| 81 | `warpingGradientYAtE` | `real` | — | Derivative of the section warping function in local Y at recovery point E. |
| 82 | `warpingGradientZAtE` | `real` | — | Derivative of the section warping function in local Z at recovery point E. |
| 83 | `warpingAtF` | `real` | — | Section warping function at recovery point F. |
| 84 | `warpingGradientYAtF` | `real` | — | Derivative of the section warping function in local Y at recovery point F. |
| 85 | `warpingGradientZAtF` | `real` | — | Derivative of the section warping function in local Z at recovery point F. |
| 86 | `warpingAtCEndB` | `real` | — | Section warping function at recovery point C at end B. |
| 87 | `warpingGradientYAtCEndB` | `real` | — | Derivative of the section warping function in local Y at recovery point C at end B. |
| 88 | `warpingGradientZAtCEndB` | `real` | — | Derivative of the section warping function in local Z at recovery point C at end B. |
| 89 | `warpingAtDEndB` | `real` | — | Section warping function at recovery point D at end B. |
| 90 | `warpingGradientYAtDEndB` | `real` | — | Derivative of the section warping function in local Y at recovery point D at end B. |
| 91 | `warpingGradientZAtDEndB` | `real` | — | Derivative of the section warping function in local Z at recovery point D at end B. |
| 92 | `warpingAtEEndB` | `real` | — | Section warping function at recovery point E at end B. |
| 93 | `warpingGradientYAtEEndB` | `real` | — | Derivative of the section warping function in local Y at recovery point E at end B. |
| 94 | `warpingGradientZAtEEndB` | `real` | — | Derivative of the section warping function in local Z at recovery point E at end B. |
| 95 | `warpingAtFEndB` | `real` | — | Section warping function at recovery point F at end B. |
| 96 | `warpingGradientYAtFEndB` | `real` | — | Derivative of the section warping function in local Y at recovery point F at end B. |
| 97 | `warpingGradientZAtFEndB` | `real` | — | Derivative of the section warping function in local Z at recovery point F at end B. |
| 98 | `warpingAtCNodeC` | `real` | — | Section warping function at recovery point C at node C. |
| 99 | `warpingGradientYAtCNodeC` | `real` | — | Derivative of the section warping function in local Y at recovery point C at node C. |
| 100 | `warpingGradientZAtCNodeC` | `real` | — | Derivative of the section warping function in local Z at recovery point C at node C. |
| 101 | `warpingAtDNodeC` | `real` | — | Section warping function at recovery point D at node C. |
| 102 | `warpingGradientYAtDNodeC` | `real` | — | Derivative of the section warping function in local Y at recovery point D at node C. |
| 103 | `warpingGradientZAtDNodeC` | `real` | — | Derivative of the section warping function in local Z at recovery point D at node C. |
| 104 | `warpingAtENodeC` | `real` | — | Section warping function at recovery point E at node C. |
| 105 | `warpingGradientYAtENodeC` | `real` | — | Derivative of the section warping function in local Y at recovery point E at node C. |
| 106 | `warpingGradientZAtENodeC` | `real` | — | Derivative of the section warping function in local Z at recovery point E at node C. |
| 107 | `warpingAtFNodeC` | `real` | — | Section warping function at recovery point F at node C. |
| 108 | `warpingGradientYAtFNodeC` | `real` | — | Derivative of the section warping function in local Y at recovery point F at node C. |
| 109 | `warpingGradientZAtFNodeC` | `real` | — | Derivative of the section warping function in local Z at recovery point F at node C. |

Accepted words: `GaussPoints`, `Nodes`, `Yes`, `YesSameAsEndA`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `warpingAtC` — a warping value needs the warping fields to be given.

**Example record**

~~~text
BeamProp3;3;1;20.;40.;30.;0.;50.;0.001
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

Reading the example gives `id = 3`, `matId = 1`, `area = 20.`, `bendingInertiaZ = 40.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## BeamShapeProp

A beam property given by the dimensions of its cross-section, possibly different at several stations along the element.

**Record format and fields**

Forms: `oneDimension`, `twoDimensions`, `threeDimensions`, `fiveDimensions`, `sixDimensions`, `tenDimensions`, `fourDimensions`.

### BeamShapeProp: oneDimension

Form `oneDimension`, when `kind` is `Rod`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: twoDimensions

Form `twoDimensions`, when `kind` is `Tube`, `Tube2`, `Bar`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: threeDimensions

Form `threeDimensions`, when `kind` is `Hexagon`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;dimension3;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `dimension3` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 3. |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationDimension3` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 6 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: fiveDimensions

Form `fiveDimensions`, when `kind` is `Hat1`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;dimension3;dimension4;dimension5;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `dimension3` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 3. |
| 8 | `dimension4` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 4. |
| 9 | `dimension5` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 5. |
| 10 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationDimension3` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 6 | `stationDimension4` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 7 | `stationDimension5` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 8 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: sixDimensions

Form `sixDimensions`, when `kind` is `ISection`, `Box1`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;dimension3;dimension4;dimension5;dimension6;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `dimension3` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 3. |
| 8 | `dimension4` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 4. |
| 9 | `dimension5` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 5. |
| 10 | `dimension6` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 6. |
| 11 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationDimension3` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 6 | `stationDimension4` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 7 | `stationDimension5` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 8 | `stationDimension6` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 9 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: tenDimensions

Form `tenDimensions`, when `kind` is `DoubleBoxSection`.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;dimension3;dimension4;dimension5;dimension6;dimension7;dimension8;dimension9;dimension10;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `dimension3` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 3. |
| 8 | `dimension4` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 4. |
| 9 | `dimension5` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 5. |
| 10 | `dimension6` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 6. |
| 11 | `dimension7` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 7. |
| 12 | `dimension8` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 8. |
| 13 | `dimension9` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 9. |
| 14 | `dimension10` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 10. |
| 15 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationDimension3` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 6 | `stationDimension4` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 7 | `stationDimension5` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 8 | `stationDimension6` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 9 | `stationDimension7` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 10 | `stationDimension8` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 11 | `stationDimension9` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 12 | `stationDimension10` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 13 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

### BeamShapeProp: fourDimensions

Form `fourDimensions`, for every other record.

`BeamShapeProp;id;matId;sectionGroup;kind;dimension1;dimension2;dimension3;dimension4;nonStructMass;<stations>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `sectionGroup` | `text` | — | Selects the section family used to interpret the dimensions. |
| 4 | `kind` | `text` | — | Selects the kind for BeamShapeProp. |
| 5 | `dimension1` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 1. |
| 6 | `dimension2` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 2. |
| 7 | `dimension3` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 3. |
| 8 | `dimension4` | `real` | — | Spatial dimension or section dimension according to the selected entry. Entry 4. |
| 9 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `stations`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressOutput` | `text` | — | Controls whether stresses are recovered at the associated location. |
| 2 | `stationRatio` | `real` | — | Position of the station expressed as a fraction of the member length. |
| 3 | `stationDimension1` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 4 | `stationDimension2` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 5 | `stationDimension3` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 6 | `stationDimension4` | `real` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 7 | `stationNonStructMass` | `real` | — | Additional mass per unit member length at this station. |

Accepted words: `Bar`, `Box`, `Box1`, `Channel`, `Channel1`, `Channel2`, `Cross`, `DoubleBoxSection`, `HSection`, `Hat`, `Hat1`, `Hexagon`, `ISection`, `ISection1`, `LSection`, `No`, `Rod`, `StandardSectionLibrary`, `TSection`, `TSection1`, `TSection2`, `Tube`, `Tube2`, `Yes`, `ZSection`.

Designable field descriptors: dimension(1), dimension(2), ... and nonStructMass, each with an optional station (EndA), (EndB) or (i).

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `dimension1` — the card needs at least end A.
- `dimension1` — the total number of dimensions at all stations must be less than 200.

**Example record**

~~~text
BeamShapeProp;207;1;;Box;20.;15.;1.5;2.
~~~

[Model containing this record](../../../validation/models/sections/sections_model.oos)

## BushProp

The property of a generalized spring-and-damper ([Bushing](elements.md#bushing)).

**Record format and fields**

`BushProp;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stiffness`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffness1` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 1. |
| 2 | `stiffness2` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 2. |
| 3 | `stiffness3` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 3. |
| 4 | `stiffness4` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 4. |
| 5 | `stiffness5` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 5. |
| 6 | `stiffness6` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 6. |

**Section `Damping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `damping1` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 1. |
| 2 | `damping2` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 2. |
| 3 | `damping3` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 3. |
| 4 | `damping4` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 4. |
| 5 | `damping5` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 5. |
| 6 | `damping6` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 6. |

**Section `StructuralDamping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `structuralDamping1` | `real` | — | Structural damping coefficient for the associated material or property. Entry 1. |
| 2 | `structuralDamping2` | `real` | — | Structural damping coefficient for the associated material or property. Entry 2. |
| 3 | `structuralDamping3` | `real` | — | Structural damping coefficient for the associated material or property. Entry 3. |
| 4 | `structuralDamping4` | `real` | — | Structural damping coefficient for the associated material or property. Entry 4. |
| 5 | `structuralDamping5` | `real` | — | Structural damping coefficient for the associated material or property. Entry 5. |
| 6 | `structuralDamping6` | `real` | — | Structural damping coefficient for the associated material or property. Entry 6. |

**Section `Recovery`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stressFactorTranslational` | `real` | — | Stress recovery coefficients, translations and rotations. |
| 2 | `stressFactorRotational` | `real` | — | Factor converting rotational loading to a reported stress measure. |
| 3 | `strainFactorTranslational` | `real` | — | Strain recovery coefficients, translations and rotations. |
| 4 | `strainFactorRotational` | `real` | — | Factor converting relative rotation to a reported strain measure. |

**Section `Mass`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `mass` | `real` | — | Inertial mass associated with the selected component or body. |

**Section `Thermal`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `alphaCoefficient` | `real` | — | Coefficient in the relation for alpha. |
| 2 | `referenceTemperature` | `real` | — | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 3 | `coincidentLength` | `real` | — | Coincident length (length). |

Accepted words: `Damping`, `Mass`, `Recovery`, `Stiffness`, `StructuralDamping`, `Thermal`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
BushProp;34;Stiffness;100.;100.;100.;100.;100.;100.
~~~

[Model containing this record](../../../validation/models/modules/modules_connectors_sol101.oos)

Reading the example gives `id = 34`.

## BushProp1D

The property of a rod type spring-and-damper ([Bushing1D](elements.md#bushing1d)).

**Record format and fields**

`BushProp1D;id;stiffness;damping;mass;stressFactor;strainFactor;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `stiffness` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 3 | `damping` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. |
| 4 | `mass` | `real` | 0.0 | Inertial mass associated with the selected component or body. |
| 5 | `stressFactor` | `real` | 0.0 | Multiplier for stress. |
| 6 | `strainFactor` | `real` | 0.0 | Multiplier for strain. |

**Keyed sections in `behaviors`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ShockAbsorber`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for shockAbsorber. |
| 2 | `dampingTension` | `real` | — | Damping on the tensile branch of the force–velocity relation. |
| 3 | `dampingCompression` | `real` | — | Damping on the compressive branch of the force–velocity relation. |
| 4 | `velocityExponentTension` | `real` | — | Exponent on velocity in the tensile damping law. |
| 5 | `velocityExponentCompression` | `real` | — | Exponent on velocity in the compressive damping law. |
| 6 | `scaleTableId` | `integer` | — | Table supplying the variation of scale. |
| 7 | `scaleTensionEquationId` | `integer` | — | Identifier selecting the scale tension equation record or set. |
| 8 | `scaleCompressionEquationId` | `integer` | — | Identifier selecting the scale compression equation record or set. |
| 9 | `scaleTensionDerivativeEquationId` | `integer` | — | Identifier selecting the scale tension derivative equation record or set. |
| 10 | `scaleCompressionDerivativeEquationId` | `integer` | — | Identifier selecting the scale compression derivative equation record or set. |

**Section `Spring`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for spring. |
| 2 | `tensionCurveId` | `integer` | — | Identifier selecting the tension curve record or set. |
| 3 | `compressionCurveId` | `integer` | — | Identifier selecting the compression curve record or set. |
| 4 | `tensionDisplacementDerivativeId` | `integer` | — | Identifier selecting the tension displacement derivative record or set. |
| 5 | `compressionDisplacementDerivativeId` | `integer` | — | Identifier selecting the compression displacement derivative record or set. |

**Section `Damper`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for damper. |
| 2 | `tensionCurveId` | `integer` | — | Identifier selecting the tension curve record or set. |
| 3 | `compressionCurveId` | `integer` | — | Identifier selecting the compression curve record or set. |
| 4 | `tensionVelocityDerivativeId` | `integer` | — | Identifier selecting the tension velocity derivative record or set. |
| 5 | `compressionVelocityDerivativeId` | `integer` | — | Identifier selecting the compression velocity derivative record or set. |

**Section `General`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for general. |
| 2 | `tensionCurveId` | `integer` | — | Identifier selecting the tension curve record or set. |
| 3 | `compressionCurveId` | `integer` | — | Identifier selecting the compression curve record or set. |
| 4 | `tensionDisplacementDerivativeId` | `integer` | — | Identifier selecting the tension displacement derivative record or set. |
| 5 | `compressionDisplacementDerivativeId` | `integer` | — | Identifier selecting the compression displacement derivative record or set. |
| 6 | `tensionVelocityDerivativeId` | `integer` | — | Identifier selecting the tension velocity derivative record or set. |
| 7 | `compressionVelocityDerivativeId` | `integer` | — | Identifier selecting the compression velocity derivative record or set. |

Accepted words: `Damper`, `Equation`, `General`, `ShockAbsorber`, `Spring`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `scaleTableId` — the table and equation IDs must not be negative.

**Example record**

~~~text
BushProp1D;20;5.E+4;2.;;0.5;2.
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 20`, `stiffness = 5.E+4`, `damping = 2.`, `stressFactor = 0.5`.

## BushProp2D

The linear and nonlinear properties of the two-dimensional bush [Bushing2D](elements.md#bushing2d).

**Record format and fields**

Forms: `squeezeFilm`, `crossTerms`, `plain`.

### BushProp2D: squeezeFilm

Form `squeezeFilm`, when `secondLineOption` is `SqueezeFilm`.

`BushProp2D;id;stiffness11;stiffness22;damping11;damping22;mass11;mass22;secondLineOption;bearingDiameter;bearingLength;bearingClearance;bearingModel;viscosity;vaporPressure;portCount;pressure1;portAngle1;pressure2;portAngle2;offset1;offset2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `stiffness11` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 11. |
| 3 | `stiffness22` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 22. |
| 4 | `damping11` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 11. |
| 5 | `damping22` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 22. |
| 6 | `mass11` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 11. |
| 7 | `mass22` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 22. |
| 8 | `secondLineOption` | `text` | — | Selects the second line option for BushProp2D. |
| 9 | `bearingDiameter` | `real` | Required | Bearing diameter (length). |
| 10 | `bearingLength` | `real` | Required | Bearing length (length). |
| 11 | `bearingClearance` | `real` | Required | Clearance between the bearing and journal surfaces (length). |
| 12 | `bearingModel` | `text` | Long | Selects the formulation used to evaluate the bearing response. |
| 13 | `viscosity` | `real` | Required | Viscous response coefficient in the selected constitutive or flow law. |
| 14 | `vaporPressure` | `real` | Required | Vapor pressure (force per area). |
| 15 | `portCount` | `integer` | Required | Number of port entries. |
| 16 | `pressure1` | `real` | Required | Normal force per unit area, in the model’s pressure units. Entry 1. |
| 17 | `portAngle1` | `real` | Required | Angular position of lubricant port 1 around the bearing. |
| 18 | `pressure2` | `real` | — | Normal force per unit area, in the model’s pressure units. Entry 2. |
| 19 | `portAngle2` | `real` | — | Angular position of lubricant port 2 around the bearing. |
| 20 | `offset1` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 1. |
| 21 | `offset2` | `real` | 0.0 | Shift from the reference location or value in the convention of this entry. Entry 2. |

### BushProp2D: crossTerms

Form `crossTerms`, when `secondLineOption` is `Cross`.

`BushProp2D;id;stiffness11;stiffness22;damping11;damping22;mass11;mass22;secondLineOption;stiffness12;stiffness21;damping12;damping21;mass12;mass21`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `stiffness11` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 11. |
| 3 | `stiffness22` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 22. |
| 4 | `damping11` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 11. |
| 5 | `damping22` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 22. |
| 6 | `mass11` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 11. |
| 7 | `mass22` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 22. |
| 8 | `secondLineOption` | `text` | — | Selects the second line option for BushProp2D. |
| 9 | `stiffness12` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 12. |
| 10 | `stiffness21` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 21. |
| 11 | `damping12` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 12. |
| 12 | `damping21` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 21. |
| 13 | `mass12` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 12. |
| 14 | `mass21` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 21. |

### BushProp2D: plain

Form `plain`, for every other record.

`BushProp2D;id;stiffness11;stiffness22;damping11;damping22;mass11;mass22`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `stiffness11` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 11. |
| 3 | `stiffness22` | `real` | Required | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 22. |
| 4 | `damping11` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 11. |
| 5 | `damping22` | `real` | 0.0 | Dissipative coefficient of the selected connection, material or response law. Entry 22. |
| 6 | `mass11` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 11. |
| 7 | `mass22` | `real` | 0.0 | Inertial mass associated with the selected component or body. Entry 22. |

Accepted words: `Constant`, `Cross`, `Element`, `Long`, `Short`, `SqueezeFilm`, `Table`.

**Example record**

~~~text
BushProp2D;21;1.E+4;1.E+4;1.;1.
~~~

[Model containing this record](../../../validation/models/linear_elements/rotor_bush2d_freq.oos)

## BushProp2DFreq

The frequency dependent stiffness, damping and mass of the [BushProp2D](properties.md#bushprop2d) with the same ID, each term given by the [TableDynamic1](tables.md#tabledynamic1) that holds its variation against frequency.

**Record format and fields**

`BushProp2DFreq;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stiffness`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffnessTableId11` | `integer` | — | Table supplying the variation of stiffness. |
| 2 | `stiffnessTableId22` | `integer` | — | Table supplying the variation of stiffness. |
| 3 | `stiffnessTableId12` | `integer` | — | Table supplying the variation of stiffness. |
| 4 | `stiffnessTableId21` | `integer` | — | Table supplying the variation of stiffness. |

**Section `Damping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dampingTableId11` | `integer` | — | Table supplying the variation of damping. |
| 2 | `dampingTableId22` | `integer` | — | Table supplying the variation of damping. |
| 3 | `dampingTableId12` | `integer` | — | Table supplying the variation of damping. |
| 4 | `dampingTableId21` | `integer` | — | Table supplying the variation of damping. |

**Section `Mass`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `massTableId11` | `integer` | — | Table supplying the variation of mass. |
| 2 | `massTableId22` | `integer` | — | Table supplying the variation of mass. |
| 3 | `massTableId12` | `integer` | — | Table supplying the variation of mass. |
| 4 | `massTableId21` | `integer` | — | Table supplying the variation of mass. |

Accepted words: `Damping`, `Mass`, `Stiffness`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
BushProp2DFreq;21;Stiffness;22;22
~~~

[Model containing this record](../../../validation/models/linear_elements/rotor_bush2d_freq.oos)

Reading the example gives `id = 21`.

## BushPropFreq

The frequency dependent or nonlinear properties of the [BushProp](properties.md#bushprop) with the same ID.

**Record format and fields**

`BushPropFreq;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stiffness`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffnessTableId1` | `integer` | — | Table supplying the variation of stiffness. |
| 2 | `stiffnessTableId2` | `integer` | — | Table supplying the variation of stiffness. |
| 3 | `stiffnessTableId3` | `integer` | — | Table supplying the variation of stiffness. |
| 4 | `stiffnessTableId4` | `integer` | — | Table supplying the variation of stiffness. |
| 5 | `stiffnessTableId5` | `integer` | — | Table supplying the variation of stiffness. |
| 6 | `stiffnessTableId6` | `integer` | — | Table supplying the variation of stiffness. |

**Section `Damping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `dampingTableId1` | `integer` | — | Table supplying the variation of damping. |
| 2 | `dampingTableId2` | `integer` | — | Table supplying the variation of damping. |
| 3 | `dampingTableId3` | `integer` | — | Table supplying the variation of damping. |
| 4 | `dampingTableId4` | `integer` | — | Table supplying the variation of damping. |
| 5 | `dampingTableId5` | `integer` | — | Table supplying the variation of damping. |
| 6 | `dampingTableId6` | `integer` | — | Table supplying the variation of damping. |

**Section `StructuralDamping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `structuralDampingTableId1` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 1. |
| 2 | `structuralDampingTableId2` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 2. |
| 3 | `structuralDampingTableId3` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 3. |
| 4 | `structuralDampingTableId4` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 4. |
| 5 | `structuralDampingTableId5` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 5. |
| 6 | `structuralDampingTableId6` | `integer` | — | Identifier of the table supplying the structural damping coefficient. Entry 6. |

**Section `NonlinearForce`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nonlinearForceTableId1` | `integer` | — | Table supplying the variation of nonlinear force. |
| 2 | `nonlinearForceTableId2` | `integer` | — | Table supplying the variation of nonlinear force. |
| 3 | `nonlinearForceTableId3` | `integer` | — | Table supplying the variation of nonlinear force. |
| 4 | `nonlinearForceTableId4` | `integer` | — | Table supplying the variation of nonlinear force. |
| 5 | `nonlinearForceTableId5` | `integer` | — | Table supplying the variation of nonlinear force. |
| 6 | `nonlinearForceTableId6` | `integer` | — | Table supplying the variation of nonlinear force. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `forceDeflectionRule` | `text` | — | Defines how force is evaluated from deflection. |
| 2 | `fuseMode` | `integer` | — | 0: always active, 1: deactivated at failure (kept for post processing), 2: deactivated and removed. |
| 3 | `direction` | `integer` | — | Orientation in which the specified quantity acts or is measured. |
| 4 | `fuseOption` | `text` | — | Selects the fuse option for fuse. |
| 5 | `lowerBound` | `real` | — | Lower limit expressed in the same units as the bounded quantity. |
| 6 | `upperBound` | `real` | — | Upper limit expressed in the same units as the bounded quantity. |
| 7 | `fuseStiffnessRetention` | `real` | — | Fuse stiffness retention factor. |
| 8 | `largeRotationEndA` | `integer` | — | Large rotation at end A. |

Accepted words: `ActualUltimateLoad`, `Damping`, `NonlinearForce`, `NonlinearResponse`, `RelativeDisplacement`, `Stiffness`, `StructuralDamping`, `TransverseShear`, `TransverseXy`, `TransverseXz`, `TransverseYz`, `UltimateLoad`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
BushPropFreq;101;Stiffness;111;111;111
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id = 101`.

**Referenced records in this example**

- [BushProp](properties.md#bushprop) via `id = 101`.

## CompProp

The property of a layered composite shell.

**Record format and fields**

`CompProp;id;bottomOffset;nonStructMass;bondAllowable;failureTheory;referenceTemperature;structuralDamping;laminateOption;<plies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `bottomOffset` | `real` | — | Distance from the reference surface to the bottom of the laminate. |
| 3 | `nonStructMass` | `real` | 0.0 | Additional mass per unit laminate area. |
| 4 | `bondAllowable` | `real` | 0.0 | Limiting stress for the bond between adjacent constituents. |
| 5 | `failureTheory` | `text` | — | Selects the criterion used to evaluate failure from the material response. |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 8 | `laminateOption` | `text` | — | Selects how the supplied ply sequence defines the laminate. |

**Repeated group `plies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `plyMatId` | `integer` | — | Identifier addressing material data. |
| 2 | `plyThickness` | `real` | — | Ply thickness (length). |
| 3 | `plyAngle` | `real` | — | Orientation of the ply relative to the laminate material reference direction. |
| 4 | `plyStressOutput` | `text` | — | Controls stress recovery for the associated ply. |

Accepted words: `BendingOnly`, `HashinCriterion`, `HashinFabricFailure`, `HashinTape`, `Hill`, `Hoffman`, `MembraneOnly`, `No`, `SandwichCore`, `SmearedLaminate`, `StrainTheory`, `Symmetry`, `TsaiWu`, `Yes`.

Designable field descriptors: bottomOffset, nonStructMass, bondAllowable, referenceTemperature, structuralDamping, plyThickness(1), plyThickness(2), ..., plyAngle(1), plyAngle(2), ....

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `plyMatId1` — a laminate needs at least one ply.
- `plyMatId1` — a ply needs a material ID.
- `plyThickness1` — the thickness of a ply must not be negative.

**Example record**

~~~text
CompProp;2;;;;;;;;2;0.5;0.;Yes;2;0.5;90.;Yes
~~~

[Model containing this record](../../../validation/models/design_sol200/sol200_shape_relations.oos)

Reading the example gives `id = 2`.

## CompPropExplicit

The additional data of a [CompProp](properties.md#compprop), with the options of the explicit shell elements.

**Record format and fields**

`CompPropExplicit;id;formulation;shearFactor;referenceSurface;stressDefinition;skipFiberTimeStep;strainOutput;laminationTheory;spinCorrection`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `formulation` | `text` | — | Selects the mathematical treatment of the property or element behavior. |
| 3 | `shearFactor` | `real` | — | Multiplier for shear. |
| 4 | `referenceSurface` | `text` | — | Through-thickness surface from which section locations are measured. |
| 5 | `stressDefinition` | `text` | — | Convention used to recover or interpret stress. |
| 6 | `skipFiberTimeStep` | `text` | — | Controls whether the fibre contribution enters time-step estimation. |
| 7 | `strainOutput` | `text` | — | Controls whether strains are recovered at the associated location. |
| 8 | `laminationTheory` | `integer` | 0 | Selects the formulation used to combine layer properties. |
| 9 | `spinCorrection` | `text` | — | Selects the correction associated with rotation or spin of the section. |

Accepted words: `BelytschkoLinTsay`, `BelytschkoWongChiang`, `Bottom`, `Constant`, `Element`, `Elements`, `Fiber`, `KeyHoff`, `MidSurface`, `No`, `Table`, `Top`, `Yes`.

**Example record**

~~~text
CompPropExplicit;30;BelytschkoLinTsay;0.83333;MidSurface;Fiber;No;Yes;0;No
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 30`, `formulation = BelytschkoLinTsay`, `shearFactor = 0.83333`, `referenceSurface = MidSurface`.

## CompPropFreqDamping

The frequency dependent structural damping of the [CompProp](properties.md#compprop) or [CompPropGlobal](properties.md#comppropglobal) with the same property ID.

**Record format and fields**

`CompPropFreqDamping;id;structuralDamping`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `structuralDamping` | `integer` | 0 | Structural damping coefficient for the associated material or property. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `Element`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`.

**Example record**

~~~text
CompPropFreqDamping;3;33
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 3`, `structuralDamping = 33`.

**Referenced records in this example**

- [CompProp](properties.md#compprop) via `id = 3`.
- [TableDynamic1](tables.md#tabledynamic1) via `structuralDamping = 33`.

## CompPropGlobal

The property of a layered composite shell whose plies have global ply IDs.

**Record format and fields**

`CompPropGlobal;id;bottomOffset;nonStructMass;bondAllowable;failureTheory;referenceTemperature;structuralDamping;laminateOption;<plies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `bottomOffset` | `real` | — | Distance from the reference surface to the bottom of the laminate. |
| 3 | `nonStructMass` | `real` | 0.0 | Additional mass per unit laminate area. |
| 4 | `bondAllowable` | `real` | 0.0 | Limiting stress for the bond between adjacent constituents. |
| 5 | `failureTheory` | `text` | — | Selects the criterion used to evaluate failure from the material response. |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 8 | `laminateOption` | `text` | — | Selects how the supplied ply sequence defines the laminate. |

**Repeated group `plies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `globalPlyId` | `integer` | — | Identifier selecting the global ply record or set. |
| 2 | `plyMatId` | `integer` | — | Identifier addressing material data. |
| 3 | `plyThickness` | `real` | — | Ply thickness (length). |
| 4 | `plyAngle` | `real` | — | Orientation of the ply relative to the laminate material reference direction. |
| 5 | `plyStressOutput` | `text` | — | Controls stress recovery for the associated ply. |
| 6 | `structuralDampingFlag` | `integer` | — | Selects the structural damping flag for plies. |

Accepted words: `BendingOnly`, `HashinCriterion`, `HashinFabricFailure`, `HashinTape`, `Hill`, `Hoffman`, `MembraneOnly`, `No`, `SandwichCore`, `SmearedLaminate`, `StrainTheory`, `Symmetry`, `TsaiWu`, `Yes`.

Designable field descriptors: bottomOffset, nonStructMass, bondAllowable, referenceTemperature, structuralDamping, plyThickness(1), plyThickness(2), ..., plyAngle(1), plyAngle(2), ....

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `globalPlyId1` — a laminate needs at least one ply.
- `globalPlyId1` — a ply needs a global ply ID greater than 0.
- `globalPlyId1` — the global ply IDs must be different in a card.
- `plyMatId1` — a ply needs a material ID.
- `plyThickness1` — the thickness of a ply must not be negative.

**Example record**

~~~text
CompPropGlobal;10;;;;;20.;;;1001;10;0.25;0.;Yes;;1002;10;0.25;90.;Yes;;1003;10;0.25;90.;Yes;;1004;10;0.25;0.;Yes
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 10`, `referenceTemperature = 20.`.

## CompPropIntegration

The through-the-thickness integration procedure of the composite shells whose [CompProp](properties.md#compprop) or [CompPropGlobal](properties.md#comppropglobal) is in the list.

**Record format and fields**

`CompPropIntegration;integration;<propIds>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `integration` | `integer` | 1 | Selects the rule used to integrate the element or section response. |

**Repeated group `propIds`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propId` | `any` | — | Identifier of the property from which the element obtains its section or constitutive data. |

Accepted words: `All`, `By`, `Constant`, `Element`, `Table`, `Through`, `ToKeyword`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `increment` — the BY increment must not be zero.

**Example record**

~~~text
CompPropIntegration;1;10;20
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `integration = 1`.

## CompSolidProp

The property of a layered composite solid, which a solid element names.

**Record format and fields**

`CompSolidProp;id;matFrameId;stackingDirection;bondAllowable;normalBondAllowable;referenceTemperature;structuralDamping;<plies>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matFrameId` | `integer` | 0 | Coordinate system defining the material directions. |
| 3 | `stackingDirection` | `integer` | 13 | Direction in which the ordered layers are assembled. |
| 4 | `bondAllowable` | `real` | — | Limiting stress for the bond between adjacent constituents. |
| 5 | `normalBondAllowable` | `real` | — | Limiting normal traction of the bond. |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |

**Repeated group `plies`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `globalPlyId` | `integer` | — | Identifier selecting the global ply record or set. |
| 2 | `matId` | `integer` | — | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 4 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. |
| 5 | `failureTheory` | `text` | — | Selects the criterion used to evaluate failure from the material response. |
| 6 | `interlaminarTheory` | `text` | — | Selects the failure or interaction criterion between layers. |
| 7 | `plyStressOutput` | `text` | — | Controls stress recovery for the associated ply. |
| 8 | `plyTail` | `text` | — | Additional data following the ply definition. |

Accepted words: `Absolute`, `Constant`, `Element`, `Hill`, `Hoffman`, `MaximumShearStress`, `No`, `ProgressiveFailure`, `StrainTheory`, `Table`, `TsaiWu`, `Yes`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `globalPlyId` — a laminate needs at least one ply.
- `globalPlyId` — a ply needs a global ply ID greater than 0.
- `globalPlyId` — the global ply IDs must be different in a card.
- `matId` — a ply needs a material ID greater than 0.

**Example record**

~~~text
CompSolidProp;1;0;13;;;;;1;1;0.5;0.;;;;;2;2;0.5;0.
~~~

[Model containing this record](../../../validation/models/read_only_materials/sol101_layered_solid_pcomps.oos)

Reading the example gives `id = 1`, `matFrameId = 0`, `stackingDirection = 13`.

## CompSolidPropNonlinear

The property of a layered solid composite, which a [SolidHexa](elements.md#solidhexa) names.

**Record format and fields**

`CompSolidPropNonlinear;id;direction;matFrameId;bondAllowable;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `direction` | `integer` | 1 | Orientation in which the specified quantity acts or is measured. |
| 3 | `matFrameId` | `integer` | 0 | Coordinate system defining the material directions. |
| 4 | `bondAllowable` | `real` | — | Limiting stress for the bond between adjacent constituents. |
| 5 | `analysisType` | `text` | — | Selects the analysis type for CompSolidPropNonlinear. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `EightNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior8` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 8. |
| 2 | `integration8` | `text` | — | Selects the rule used to integrate the element or section response. Entry 8. |
| 3 | `heatBehavior8` | `text` | — | Heat behavior setting for the element configuration identified by 8. |
| 4 | `heatIntegration8` | `text` | — | Heat integration setting for the element configuration identified by 8. |

**Section `TwentyNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior20` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 20. |
| 2 | `integration20` | `text` | — | Selects the rule used to integrate the element or section response. Entry 20. |
| 3 | `heatBehavior20` | `text` | — | Heat behavior setting for the element configuration identified by 20. |
| 4 | `heatIntegration20` | `text` | — | Heat integration setting for the element configuration identified by 20. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `globalPlyId` | `integer` | — | Identifier selecting the global ply record or set. |
| 2 | `plyMatId` | `integer` | — | Identifier selecting the ply material record or set. |
| 3 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 4 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `EightNodeElems`, `Element`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `TwentyNodeElems`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `globalPlyId1` — a laminate needs at least one ply.
- `globalPlyId1` — a ply needs a global ply ID greater than 0.
- `globalPlyId1` — the global ply IDs must be different in a card.
- `matId1` — a ply needs a material ID greater than 0.

**Example record**

~~~text
CompSolidPropNonlinear;40;1;0;;;;4001;40;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 40`, `direction = 1`, `matFrameId = 0`.

## CurvedBeamProp

The property of a curved beam, curved pipe or elbow ([CurvedBeam2](elements.md#curvedbeam2)).

**Record format and fields**

Forms: `pipe`, `section`.

### CurvedBeamProp: pipe

Form `pipe`, when `flexibilityOption` is an integer.

`CurvedBeamProp;id;matId;flexibilityOption;meanRadius;thickness;internalPressure;bendRadius;arcAngle;nonStructMass;centroidRadialOffset;centerZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `flexibilityOption` | `integer` | — | Selects the flexibility option for CurvedBeamProp. |
| 4 | `meanRadius` | `real` | Required | Mean radius (length). |
| 5 | `thickness` | `real` | Required | Through-thickness dimension, in model length units. |
| 6 | `internalPressure` | `real` | — | Pressure applied on the inside of the section or cavity (force per area). |
| 7 | `bendRadius` | `real` | — | Bend radius (length). |
| 8 | `arcAngle` | `real` | — | Arc angle of the element, in degrees. |
| 9 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 10 | `centroidRadialOffset` | `real` | 0.0 | Radial distance from the reference line to the centroid. |
| 11 | `centerZ` | `real` | 0.0 | Z coordinate of the centre. |

### CurvedBeamProp: section

Form `section`, for every other record.

`CurvedBeamProp;id;matId;area;bendingInertia1;bendingInertia2;torsionConstant;bendRadius;arcAngle;stressPointCy;stressPointCz;stressPointDy;stressPointDz;stressPointEy;stressPointEz;stressPointFy;stressPointFz;shearFactor1;shearFactor2;nonStructMass;centroidRadialOffset;centerZ;neutralAxisOffset`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | — | Surface or cross-sectional measure, in squared model length units. |
| 4 | `bendingInertia1` | `real` | Required | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 5 | `bendingInertia2` | `real` | Required | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |
| 6 | `torsionConstant` | `real` | Required | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 7 | `bendRadius` | `real` | — | Bend radius (length). |
| 8 | `arcAngle` | `real` | — | Arc angle of the element, in degrees. |
| 9 | `stressPointCy` | `real` | 0.0 | Local y coordinate of stress-recovery point C in the cross-section (length). |
| 10 | `stressPointCz` | `real` | 0.0 | Local z coordinate of stress-recovery point C in the cross-section (length). |
| 11 | `stressPointDy` | `real` | 0.0 | Local y coordinate of stress-recovery point D in the cross-section (length). |
| 12 | `stressPointDz` | `real` | 0.0 | Local z coordinate of stress-recovery point D in the cross-section (length). |
| 13 | `stressPointEy` | `real` | 0.0 | Local y coordinate of stress-recovery point E in the cross-section (length). |
| 14 | `stressPointEz` | `real` | 0.0 | Local z coordinate of stress-recovery point E in the cross-section (length). |
| 15 | `stressPointFy` | `real` | 0.0 | Local y coordinate of stress-recovery point F in the cross-section (length). |
| 16 | `stressPointFz` | `real` | 0.0 | Local z coordinate of stress-recovery point F in the cross-section (length). |
| 17 | `shearFactor1` | `real` | 0.0 | Multiplier for shear. |
| 18 | `shearFactor2` | `real` | 0.0 | Multiplier for shear. |
| 19 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 20 | `centroidRadialOffset` | `real` | 0.0 | Radial distance from the reference line to the centroid. |
| 21 | `centerZ` | `real` | 0.0 | Z coordinate of the centre. |
| 22 | `neutralAxisOffset` | `real` | — | Radial offset of the neutral axis from the geometric centroid. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
CurvedBeamProp;4;1;20.;40.;30.;50.
~~~

[Model containing this record](../../../validation/models/mass_geometry/mass_gpwg_elements.oos)

## DamperProp

Supplies the viscous damping coefficient for scalar dampers that reference this property.

**Record format and fields**

`DamperProp;id1;damping1;id2;damping2;id3;damping3;id4;damping4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered DamperProp data. |
| 2 | `damping1` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 1. |
| 3 | `id2` | `integer` | — | Identifier at position 2 in the ordered DamperProp data. |
| 4 | `damping2` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 2. |
| 5 | `id3` | `integer` | — | Identifier at position 3 in the ordered DamperProp data. |
| 6 | `damping3` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 3. |
| 7 | `id4` | `integer` | — | Identifier at position 4 in the ordered DamperProp data. |
| 8 | `damping4` | `real` | — | Dissipative coefficient of the selected connection, material or response law. Entry 4. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
DamperProp;185;0.5;187;0.3
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id1 = 185`, `damping1 = 0.5`, `id2 = 187`, `damping2 = 0.3`.

## DamperPropFreq

The frequency dependent property of the [DamperProp](properties.md#damperprop) with the same ID.

**Record format and fields**

`DamperPropFreq;id;dampingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `dampingTableId` | `integer` | 0 | Identifier addressing dynamic table data. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
DamperPropFreq;12;13
~~~

[Model containing this record](../../../validation/models/linear_elements/frequency_dependent_freq.oos)

Reading the example gives `id = 12`, `dampingTableId = 13`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `dampingTableId = 13`.

## FastenerProp

The property of a fastener element ([Fastener](elements.md#fastener)).

**Record format and fields**

`FastenerProp;id;diameter;matFrameId;absoluteFrame;translationalStiffness1;translationalStiffness2;translationalStiffness3;rotationalStiffness1;rotationalStiffness2;rotationalStiffness3;mass;structuralDamping;alphaCoefficient;referenceTemperature;coincidentLength`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `diameter` | `real` | Required | Diameter (length). |
| 3 | `matFrameId` | `integer` | — | Coordinate system defining the material directions. |
| 4 | `absoluteFrame` | `integer` | 0 | Reference frame for quantities specified in absolute coordinates. |
| 5 | `translationalStiffness1` | `real` | — | Entry 1 of the translational stiffness coefficients in the local component order. |
| 6 | `translationalStiffness2` | `real` | — | Entry 2 of the translational stiffness coefficients in the local component order. |
| 7 | `translationalStiffness3` | `real` | — | Entry 3 of the translational stiffness coefficients in the local component order. |
| 8 | `rotationalStiffness1` | `real` | 0.0 | Entry 1 of the rotational stiffness coefficients in the local component order. |
| 9 | `rotationalStiffness2` | `real` | 0.0 | Entry 2 of the rotational stiffness coefficients in the local component order. |
| 10 | `rotationalStiffness3` | `real` | 0.0 | Entry 3 of the rotational stiffness coefficients in the local component order. |
| 11 | `mass` | `real` | 0.0 | Inertial mass associated with the selected component or body. |
| 12 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 13 | `alphaCoefficient` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 14 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 15 | `coincidentLength` | `real` | 0.0 | Coincident length (length). |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
FastenerProp;1;3.;-1;;2.E+4;1.E+4;1.E+4;100.;100.;100.
~~~

[Model containing this record](../../../validation/models/fasteners/cfast_forms.oos)

Reading the example gives `id = 1`, `diameter = 3.`, `matFrameId = -1`, `translationalStiffness1 = 2.E+4`.

## FastenerPropFreq

The frequency dependent and nonlinear properties of the [FastenerProp](properties.md#fastenerprop) with the same ID.

**Record format and fields**

`FastenerPropFreq;id;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Stiffness`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `stiffnessTableId1` | `integer` | — | Table supplying the variation of stiffness. |
| 2 | `stiffnessTableId2` | `integer` | — | Table supplying the variation of stiffness. |
| 3 | `stiffnessTableId3` | `integer` | — | Table supplying the variation of stiffness. |
| 4 | `stiffnessTableId4` | `integer` | — | Table supplying the variation of stiffness. |
| 5 | `stiffnessTableId5` | `integer` | — | Table supplying the variation of stiffness. |
| 6 | `stiffnessTableId6` | `integer` | — | Table supplying the variation of stiffness. |

**Section `StructuralDamping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `structuralDampingTableId` | `integer` | — | Identifier of the table supplying the structural damping coefficient. |

**Section `NonlinearForce`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `nonlinearForceTableId1` | `integer` | — | Table supplying the variation of nonlinear force. |
| 2 | `nonlinearForceTableId2` | `integer` | — | Table supplying the variation of nonlinear force. |
| 3 | `nonlinearForceTableId3` | `integer` | — | Table supplying the variation of nonlinear force. |
| 4 | `nonlinearForceTableId4` | `integer` | — | Table supplying the variation of nonlinear force. |
| 5 | `nonlinearForceTableId5` | `integer` | — | Table supplying the variation of nonlinear force. |
| 6 | `nonlinearForceTableId6` | `integer` | — | Table supplying the variation of nonlinear force. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `forceDeflectionRule` | `text` | — | Defines how force is evaluated from deflection. |
| 2 | `fuseMode` | `integer` | — | 0: always active, 1: deactivated at failure (kept for post processing), 2: deactivated and removed. |
| 3 | `direction` | `integer` | — | Orientation in which the specified quantity acts or is measured. |
| 4 | `fuseOption` | `text` | — | Selects the fuse option for fuse. |
| 5 | `lowerBound` | `real` | — | Lower limit expressed in the same units as the bounded quantity. |
| 6 | `upperBound` | `real` | — | Upper limit expressed in the same units as the bounded quantity. |
| 7 | `fuseStiffnessRetention` | `real` | — | Fuse stiffness retention factor. |
| 8 | `largeRotationEndA` | `integer` | — | Large rotation at end A. |

Accepted words: `ActualUltimateLoad`, `NonlinearForce`, `NonlinearResponse`, `RelativeDisplacement`, `Stiffness`, `StructuralDamping`, `TransverseShear`, `TransverseXy`, `TransverseXz`, `TransverseYz`, `UltimateLoad`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `stiffnessTableId1` — the table IDs must not be negative.
- `nonlinearForceTableId1` — the table IDs must not be negative.

**Example record**

~~~text
FastenerPropFreq;23;Stiffness;24;25;25;;;;StructuralDamping;26
~~~

[Model containing this record](../../../validation/models/linear_elements/frequency_dependent_freq.oos)

Reading the example gives `id = 23`.

**Referenced records in this example**

- [FastenerProp](properties.md#fastenerprop) via `id = 23`.

## GapProp

The property of a gap element ([Gap2](elements.md#gap2)).

**Record format and fields**

`GapProp;id;initialOpening;preload;closedStiffness;openStiffness;transverseStiffness;frictionCoeff1;frictionCoeff2;maxPenetration;maxAdjustmentRatio;minPenetrationRatio`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `initialOpening` | `real` | 0.0 | Initial gap opening. |
| 3 | `preload` | `real` | 0.0 | Load or initial bias present before the operating load is applied. |
| 4 | `closedStiffness` | `real` | — | Axial stiffness of the closed gap. |
| 5 | `openStiffness` | `real` | — | Axial stiffness of the open gap. |
| 6 | `transverseStiffness` | `real` | — | Transverse stiffness of the closed gap. |
| 7 | `frictionCoeff1` | `real` | 0.0 | Coefficient of static friction (adaptive gap) or of friction in the y direction. |
| 8 | `frictionCoeff2` | `real` | same as frictionCoeff1 | Coefficient of kinetic friction (adaptive gap) or of friction in the z direction. |
| 9 | `maxPenetration` | `real` | 0.0 | Largest accepted penetration between the contacting surfaces. |
| 10 | `maxAdjustmentRatio` | `real` | — | Relative measure of maximum adjustment. |
| 11 | `minPenetrationRatio` | `real` | — | Relative measure of minimum penetration. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
GapProp;5;0.;0.;1.E+5;0.001;1.E+3
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 5`, `initialOpening = 0.`, `preload = 0.`, `closedStiffness = 1.E+5`.

## HeatCapacityProp5

The property of a [HeatCapacity2](elements.md#heatcapacity2) (a heat transfer damper: the mass that multiplies the heat capacity of a [HeatIsoMat](thermal.md#heatisomat) or [HeatAnisoMat](thermal.md#heatanisomat) material).

**Record format and fields**

`HeatCapacityProp5;id;matId;heatCapacity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `heatCapacity` | `real` | Required | Damping multiplier. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
HeatCapacityProp5;2;1;1.E-6
~~~

[Model containing this record](../../../validation/models/linear_elements/heat_capacity_transient.oos)

Reading the example gives `id = 2`, `matId = 1`, `heatCapacity = 1.E-6`.

## MassProp

One scalar mass property of a MassProp card.

**Record format and fields**

`MassProp;id1;mass1;id2;mass2;id3;mass3;id4;mass4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered MassProp data. |
| 2 | `mass1` | `real` | — | Inertial mass associated with the selected component or body. Entry 1. |
| 3 | `id2` | `integer` | — | Identifier at position 2 in the ordered MassProp data. |
| 4 | `mass2` | `real` | — | Inertial mass associated with the selected component or body. Entry 2. |
| 5 | `id3` | `integer` | — | Identifier at position 3 in the ordered MassProp data. |
| 6 | `mass3` | `real` | — | Inertial mass associated with the selected component or body. Entry 3. |
| 7 | `id4` | `integer` | — | Identifier at position 4 in the ordered MassProp data. |
| 8 | `mass4` | `real` | — | Inertial mass associated with the selected component or body. Entry 4. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
MassProp;21;0.001;22;5.E-4
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id1 = 21`, `mass1 = 0.001`, `id2 = 22`, `mass2 = 5.E-4`.

## NonStructMass

A set of non-structural mass, given per unit area or length on properties or elements.

**Record format and fields**

`NonStructMass;id;type;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `type` | `text` | — | Selects the type for NonStructMass. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `targetId` | `integer` | — | Identifier selecting the target record or set. |
| 2 | `targetValue` | `real` | — | Prescribed value sought during the update. |

Accepted words: `All`, `BarProp`, `BarShapeProp`, `BeamLumpedAreaProp`, `BeamProp`, `BeamShapeProp`, `By`, `CompProp`, `CompPropGlobal`, `ConicalShellProp`, `CrackTipProp2D`, `CurvedBeamProp`, `Element`, `Rod2InlineSection`, `RodProp`, `ShearPanelProp`, `ShellProp`, `Through`, `TubeProp`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the non-structural mass set ID must be a positive integer.

**Example record**

~~~text
NonStructMass;10;ShellProp;31;5.E-9
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 10`, `type = ShellProp`.

## NonStructMass1

Assigns one nonstructural mass value to a list of properties or elements.

**Record format and fields**

`NonStructMass1;id;type;nonStructMass;<targets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `type` | `text` | — | Selects the type for NonStructMass1. |
| 3 | `nonStructMass` | `real` | Required | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `targets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `targetId` | `any` | — | Identifier selecting the target record or set. |

Accepted words: `All`, `BarProp`, `BarShapeProp`, `BeamLumpedAreaProp`, `BeamProp`, `BeamShapeProp`, `By`, `CompProp`, `CompPropGlobal`, `ConicalShellProp`, `CrackTipProp2D`, `CurvedBeamProp`, `Element`, `Rod2InlineSection`, `RodProp`, `ShearPanelProp`, `ShellProp`, `Through`, `TubeProp`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the non-structural mass set ID must be a positive integer.

**Example record**

~~~text
NonStructMass1;11;Element;2.E-9;301;302
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 11`, `type = Element`, `nonStructMass = 2.E-9`.

## NonStructMassLumped

A set of lumped non-structural mass, given as a total on properties or elements.

**Record format and fields**

`NonStructMassLumped;id;type;<pairs>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `type` | `text` | — | Selects the type for NonStructMassLumped. |

**Repeated group `pairs`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `targetId` | `integer` | — | Identifier selecting the target record or set. |
| 2 | `targetValue` | `real` | — | Prescribed value sought during the update. |

Accepted words: `All`, `BarProp`, `BarShapeProp`, `BeamLumpedAreaProp`, `BeamProp`, `BeamShapeProp`, `By`, `CompProp`, `CompPropGlobal`, `ConicalShellProp`, `CrackTipProp2D`, `CurvedBeamProp`, `Element`, `Rod2InlineSection`, `RodProp`, `ShearPanelProp`, `ShellProp`, `Through`, `TubeProp`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the non-structural mass set ID must be a positive integer.

**Example record**

~~~text
NonStructMassLumped;12;BarProp;32;1.E-4
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 12`, `type = BarProp`.

## NonStructMassLumped1

The alternate form of [NonStructMassLumped](properties.md#nonstructmasslumped), one lumped non-structural mass shared by a list of properties or elements.

**Record format and fields**

`NonStructMassLumped1;id;type;nonStructMass;<targets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `type` | `text` | — | Selects the type for NonStructMassLumped1. |
| 3 | `nonStructMass` | `real` | Required | Additional mass distributed with the element or property; its geometric basis follows the section definition. |

**Repeated group `targets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `targetId` | `any` | — | Identifier selecting the target record or set. |

Accepted words: `All`, `BarProp`, `BarShapeProp`, `BeamLumpedAreaProp`, `BeamProp`, `BeamShapeProp`, `By`, `CompProp`, `CompPropGlobal`, `ConicalShellProp`, `CrackTipProp2D`, `CurvedBeamProp`, `Element`, `Rod2InlineSection`, `RodProp`, `ShearPanelProp`, `ShellProp`, `Through`, `TubeProp`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the non-structural mass set ID must be a positive integer.

**Example record**

~~~text
NonStructMassLumped1;13;Element;1.E-4;303;304
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 13`, `type = Element`, `nonStructMass = 1.E-4`.

## NonStructMassUnion

A set of non-structural mass that is the sum of other sets.

**Record format and fields**

`NonStructMassUnion;id;<memberSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `memberSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `memberSetId` | `integer` | — | Identifier selecting the member set record or set. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the non-structural mass set ID must be a positive integer.
- `memberSetId1` — the card needs at least one set.
- `memberSetId1` — a set ID must be a positive integer.

**Example record**

~~~text
NonStructMassUnion;20;10;11;12;13
~~~

[Model containing this record](../../../validation/models/linear_elements/special_elements_modes.oos)

Reading the example gives `id = 20`.

## PerforatedShellProp

Defines a perforated shell property for a porous elastic trim layer.

**Record format and fields**

`PerforatedShellProp;id;matId;thickness;holeSpacing;holeRadius;topology;fluidDensity;fluidViscosity;homogenization`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness` | `real` | Required | Through-thickness dimension, in model length units. |
| 4 | `holeSpacing` | `real` | Required | Centre-to-centre spacing of perforations (length). |
| 5 | `holeRadius` | `real` | Required | Hole radius (length). |
| 6 | `topology` | `text` | — | Describes the arrangement or connectivity of the selected entities. |
| 7 | `fluidDensity` | `real` | Required | Mass per unit volume of the fluid. |
| 8 | `fluidViscosity` | `real` | Required | Viscosity used in the fluid constitutive response. |
| 9 | `homogenization` | `integer` | 1 | Selects how constituent properties are combined into an effective response. |

Accepted words: `Constant`, `Element`, `Hexagonal`, `Square`, `Table`, `Triangular`.

**Example record**

~~~text
PerforatedShellProp;20;21;8.E-4;0.01;0.001;Square;1.21;1.84E-5
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_perforated_shell_sol111.oos)

Reading the example gives `id = 20`, `matId = 21`, `thickness = 8.E-4`, `holeSpacing = 0.01`.

## PlaneCompProp

The property of a plane strain or axisymmetric composite, which a [PlaneStrainQuad](elements.md#planestrainquad), [ShellQuad4](elements.md#shellquad4), [ShellQuad8](elements.md#shellquad8) or [AxisymQuad](elements.md#axisymquad) names.

**Record format and fields**

`PlaneCompProp;id;direction;thicknessOption;bondAllowable;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `direction` | `integer` | 1 | Orientation in which the specified quantity acts or is measured. |
| 3 | `thicknessOption` | `real` | 1.0 | Selects the thickness option for PlaneCompProp. |
| 4 | `bondAllowable` | `real` | — | Limiting stress for the bond between adjacent constituents. |
| 5 | `analysisType` | `text` | — | Selects the analysis type for PlaneCompProp. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `FourNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior4` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 4. |
| 2 | `integration4` | `text` | — | Selects the rule used to integrate the element or section response. Entry 4. |
| 3 | `heatBehavior4` | `text` | — | Heat behavior setting for the element configuration identified by 4. |
| 4 | `heatIntegration4` | `text` | — | Heat integration setting for the element configuration identified by 4. |

**Section `EightNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior8` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 8. |
| 2 | `integration8` | `text` | — | Selects the rule used to integrate the element or section response. Entry 8. |
| 3 | `heatBehavior8` | `text` | — | Heat behavior setting for the element configuration identified by 8. |
| 4 | `heatIntegration8` | `text` | — | Heat integration setting for the element configuration identified by 8. |

**Section with an empty key**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `globalPlyId` | `integer` | — | Identifier selecting the global ply record or set. |
| 2 | `plyMatId` | `integer` | — | Identifier selecting the ply material record or set. |
| 3 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 4 | `materialAngle` | `real` | — | Angle defining the material orientation relative to the reference element axes. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `EightNodeElems`, `Element`, `FourNodeElems`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `globalPlyId1` — a laminate needs at least one ply.
- `globalPlyId1` — a ply needs a global ply ID greater than 0.
- `globalPlyId1` — the global ply IDs must be different in a card.
- `matId1` — a ply needs a material ID greater than 0.

**Example record**

~~~text
PlaneCompProp;32;1;;;ImplicitStructural;FourNodeElems;AxisymComposite;Linear;;;;3201;33;0.5;0.;;3202;34;0.5;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_axisymmetric_mats3_plcomp.oos)

Reading the example gives `id = 32`, `direction = 1`, `analysisType = ImplicitStructural`.

## PlaneProp

Supplies thickness and nonstructural mass for a plane stress or plane strain element.

**Record format and fields**

`PlaneProp;id;matId;thickness;nonStructMass;formulationOption`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 4 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 5 | `formulationOption` | `integer` | 0 | Selects the formulation option for PlaneProp. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
PlaneProp;2;1;2.;0.;0
~~~

[Model containing this record](../../../validation/models/read_only_elements_nl/other_plane_axisymmetric_elements.oos)

Reading the example gives `id = 2`, `matId = 1`, `thickness = 2.`, `nonStructMass = 0.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## PlanePropNonlinear

The property of a fully nonlinear plane strain, plane stress or axisymmetric element.

**Record format and fields**

`PlanePropNonlinear;id;matId;frameId;stressLocation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 4 | `stressLocation` | `text` | — | Location in the element or section at which stress is evaluated. |

Accepted words: `Gauss`, `Node`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
PlanePropNonlinear;1;3
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 1`, `matId = 3`.

**Referenced records in this example**

- [HyperelasticPolynomialMat](materials.md#hyperelasticpolynomialmat) via `matId = 3`.

## PlanePropNonlinearExt

The nonlinear extension of the [PlanePropNonlinear](properties.md#planepropnonlinear) with the same property ID, for the plane stress, plane strain and axisymmetric elements ([ShellQuad4](elements.md#shellquad4), [PlaneStrainQuad](elements.md#planestrainquad), [ShellQuad8](elements.md#shellquad8), [ShellTria3](elements.md#shelltria3), [ShellTria6](elements.md#shelltria6), [AxisymQuad](elements.md#axisymquad), [AxisymTria](elements.md#axisymtria)) that name it.

**Record format and fields**

`PlanePropNonlinearExt;id;matId;direction;thickness;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `direction` | `integer` | 1 | Orientation in which the specified quantity acts or is measured. |
| 4 | `thickness` | `real` | 1.0 | Through-thickness dimension, in model length units. |
| 5 | `analysisType` | `text` | — | Selects the analysis type for PlanePropNonlinearExt. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ThreeNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior3` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 3. |
| 2 | `integration3` | `text` | — | Selects the rule used to integrate the element or section response. Entry 3. |
| 3 | `heatBehavior3` | `text` | — | Heat behavior setting for the element configuration identified by 3. |
| 4 | `heatIntegration3` | `text` | — | Heat integration setting for the element configuration identified by 3. |

**Section `FourNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior4` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 4. |
| 2 | `integration4` | `text` | — | Selects the rule used to integrate the element or section response. Entry 4. |
| 3 | `heatBehavior4` | `text` | — | Heat behavior setting for the element configuration identified by 4. |
| 4 | `heatIntegration4` | `text` | — | Heat integration setting for the element configuration identified by 4. |

**Section `SixNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior6` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 6. |
| 2 | `integration6` | `text` | — | Selects the rule used to integrate the element or section response. Entry 6. |
| 3 | `heatBehavior6` | `text` | — | Heat behavior setting for the element configuration identified by 6. |
| 4 | `heatIntegration6` | `text` | — | Heat integration setting for the element configuration identified by 6. |

**Section `EightNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior8` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 8. |
| 2 | `integration8` | `text` | — | Selects the rule used to integrate the element or section response. Entry 8. |
| 3 | `heatBehavior8` | `text` | — | Heat behavior setting for the element configuration identified by 8. |
| 4 | `heatIntegration8` | `text` | — | Heat integration setting for the element configuration identified by 8. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `AxisymSolid`, `Bar`, `Beam`, `Constant`, `EightNodeElems`, `Element`, `FourNodeElems`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleAxisym`, `IncompressiblePlaneStrain`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearDiscreteKirchhoff`, `LinearReducedHourglass`, `LinearShear`, `LinearTwist`, `Membrane`, `Numerical`, `PlaneStrain`, `PlaneStrainComposite`, `PlaneStress`, `Quadratic`, `QuadraticReduced`, `QuadraticTwist`, `Rod`, `SixNodeElems`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `ThickShell`, `ThinShell`, `ThreeNodeElems`.

**Example record**

~~~text
PlanePropNonlinearExt;1;1;;1.;ImplicitStructural;FourNodeElems;PlaneStrain;Linear
~~~

[Model containing this record](../../../validation/models/nonlinear_contact/sol400_planar_rigid_curves.oos)

Reading the example gives `id = 1`, `matId = 1`, `thickness = 1.`, `analysisType = ImplicitStructural`.

**Referenced records in this example**

- [PlanePropNonlinear](properties.md#planepropnonlinear) via `id = 1`.

## PropDistribution

A spatial distribution of one datum of a property.

**Record format and fields**

`PropDistribution;id;type;propId;fieldName;locationNumber;scaleFactor;valueOffset;<entries>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `type` | `text` | — | Selects the type for PropDistribution. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `fieldName` | `text` | — | Name of the field addressed by this entry. |
| 5 | `locationNumber` | `integer` | — | The ply or station, not negative. |
| 6 | `scaleFactor` | `real` | 1.0 | Multiplier applied to the quantity specified by the entry. |
| 7 | `valueOffset` | `real` | 0.0 | Additive shift to the value before it is used. |

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `integer` | — | Identifier of the element addressed by this record. |
| 2 | `elemValue` | `number` | — | Value assigned at the individual element. |

Accepted words: `BarProp`, `BeamProp`, `BeamProp3`, `CompProp`, `CompPropGlobal`, `Constant`, `Element`, `RodProp`, `ShearPanelProp`, `ShellProp`, `SolidProp`, `Table`, `TubeProp`, `area`, `bendingInertia1`, `bendingInertia2`, `bendingInertiaY`, `bendingInertiaZ`, `bendingStiffnessRatio`, `bondAllowable`, `bottomOffset`, `extensionalFactor1`, `extensionalFactor2`, `fiberDistance1`, `fiberDistance2`, `matFrameId`, `nonStructMass`, `outerDiameter`, `outerDiameter2`, `plyAngle`, `plyStressOutput`, `plyThickness`, `productInertia12`, `productInertiaYZ`, `referenceTemperature`, `shearFactor1`, `shearFactor2`, `shearFactorY`, `shearFactorZ`, `shearThicknessRatio`, `structuralDamping`, `thickness`, `torsionConstant`, `warpingCoefficient`.

**Example record**

~~~text
PropDistribution;1;BarProp;11;area;;;;102;150.
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `id = 1`, `type = BarProp`, `propId = 11`, `fieldName = area`.

## PropMatDistribution

A spatial distribution of one material of a property.

**Record format and fields**

`PropMatDistribution;id;type;propId;materialIndex;<entries>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `type` | `text` | — | Selects the type for PropMatDistribution. |
| 3 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 4 | `materialIndex` | `integer` | 1 | Position or identifier selecting a constituent in the material definition. |

**Repeated group `entries`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `integer` | — | Identifier of the element addressed by this record. |
| 2 | `elemMatId` | `integer` | — | Identifier selecting the element material record or set. |

Accepted words: `BarProp`, `BeamProp`, `BeamProp3`, `CompProp`, `CompPropGlobal`, `Constant`, `Element`, `RodProp`, `ShearPanelProp`, `ShellProp`, `SolidProp`, `Table`, `TubeProp`.

**Example record**

~~~text
PropMatDistribution;3;ShellProp;61;1;603;2
~~~

[Model containing this record](../../../validation/models/linear_elements/sections_defaults_static.oos)

Reading the example gives `id = 3`, `type = ShellProp`, `propId = 61`, `materialIndex = 1`.

## RodProp

Defines the material, cross-sectional area and torsional constants for rod elements.

**Record format and fields**

`RodProp;id;matId;area;torsionConstant;torsionStressCoefficient;nonStructMass`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `area` | `real` | Required | Surface or cross-sectional measure, in squared model length units. |
| 4 | `torsionConstant` | `real` | 0.0 | Section constant multiplying the shear modulus in torsional rigidity (length to the fourth power). |
| 5 | `torsionStressCoefficient` | `real` | 0.0 | Section factor used in recovering the outer-fibre shear stress from the torsional moment. |
| 6 | `nonStructMass` | `real` | 0.0 | Additional mass per unit rod length. |

Designable field descriptors: area, torsionConstant, torsionStressCoefficient, nonStructMass.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
RodProp;1302;1;20.;30.
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id = 1302`, `matId = 1`, `area = 20.`, `torsionConstant = 30.`.

## RodPropNonlinear

The nonlinear extension of the [RodProp](properties.md#rodprop) with the same property ID.

**Record format and fields**

`RodPropNonlinear;id;matId;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `analysisType` | `text` | — | Selects the analysis type for RodPropNonlinear. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `TwoNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior2` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 2. |
| 2 | `integration2` | `text` | — | Selects the rule used to integrate the element or section response. Entry 2. |
| 3 | `heatBehavior2` | `text` | — | Heat behavior setting for the element configuration identified by 2. |
| 4 | `heatIntegration2` | `text` | — | Heat integration setting for the element configuration identified by 2. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `Element`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `TwoNodeElems`.

**Example record**

~~~text
RodPropNonlinear;101;2;ImplicitStructural;TwoNodeElems;Rod;Linear
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_property_extensions.oos)

Reading the example gives `id = 101`, `matId = 2`, `analysisType = ImplicitStructural`.

**Referenced records in this example**

- [RodProp](properties.md#rodprop) via `id = 101`.

## ShearPanelProp

The property of a shear panel ([ShearPanel4](elements.md#shearpanel4)).

**Record format and fields**

`ShearPanelProp;id;matId;thickness;nonStructMass;extensionalFactor1;extensionalFactor2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `thickness` | `real` | Required | Through-thickness dimension, in model length units. |
| 4 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 5 | `extensionalFactor1` | `real` | 0.0 | Multiplier for extensional. |
| 6 | `extensionalFactor2` | `real` | 0.0 | Multiplier for extensional. |

Designable field descriptors: thickness, nonStructMass, extensionalFactor1, extensionalFactor2.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.
- `thickness` — T must not be negative.
- `extensionalFactor1` — F1 must not be negative.
- `extensionalFactor2` — F2 must not be negative.

**Example record**

~~~text
ShearPanelProp;2;1;2.
~~~

[Model containing this record](../../../validation/models/mass_geometry/quality_geomcheck.oos)

Reading the example gives `id = 2`, `matId = 1`, `thickness = 2.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## ShearPanelPropNonlinear

The nonlinear extension of the [ShearPanelProp](properties.md#shearpanelprop) with the same property ID.

**Record format and fields**

`ShearPanelPropNonlinear;id;matId;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `analysisType` | `text` | — | Selects the analysis type for ShearPanelPropNonlinear. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `FourNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior4` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 4. |
| 2 | `integration4` | `text` | — | Selects the rule used to integrate the element or section response. Entry 4. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `Bar`, `Beam`, `Constant`, `Element`, `FourNodeElems`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearReducedHourglass`, `LinearShear`, `Membrane`, `Numerical`, `PlaneStrainComposite`, `Quadratic`, `QuadraticReduced`, `Rod`, `Smeared`, `Solid`, `SolidComposite`, `Table`.

**Example record**

~~~text
ShearPanelPropNonlinear;401;1;ImplicitStructural;FourNodeElems;Membrane;Linear
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_property_extensions.oos)

Reading the example gives `id = 401`, `matId = 1`, `analysisType = ImplicitStructural`.

**Referenced records in this example**

- [ShearPanelProp](properties.md#shearpanelprop) via `id = 401`.

## ShellProp

Defines the membrane, bending and transverse-shear material associations and the reference thickness of a shell.

**Record format and fields**

`ShellProp;id;membraneMatId;thickness;bendingMatId;bendingStiffnessRatio;shearMatId;shearThicknessRatio;nonStructMass;fiberDistance1;fiberDistance2;couplingMatId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `membraneMatId` | `integer` | 0 | Identifier selecting the membrane material record or set. |
| 3 | `thickness` | `real` | 0.0 | Through-thickness dimension, in model length units. |
| 4 | `bendingMatId` | `integer` | 0 | Identifier selecting the bending material record or set. |
| 5 | `bendingStiffnessRatio` | `real` | 1.0 | Relative measure of bending stiffness. |
| 6 | `shearMatId` | `integer` | 0 | Identifier selecting the shear material record or set. |
| 7 | `shearThicknessRatio` | `real` | 0.833333 | Relative measure of shear thickness. |
| 8 | `nonStructMass` | `real` | 0.0 | Additional mass per unit shell area. |
| 9 | `fiberDistance1` | `real` | — | Fiber distance 1 (length). |
| 10 | `fiberDistance2` | `real` | — | Fiber distance 2 (length). |
| 11 | `couplingMatId` | `integer` | 0 | Identifier selecting the coupling material record or set. |

Designable field descriptors: thickness, shearThicknessRatio, nonStructMass, fiberDistance1, fiberDistance2 and bendingStiffnessRatio.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `thickness` — T must not be negative.

**Example record**

~~~text
ShellProp;1;1;2.;1;;1
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 1`, `membraneMatId = 1`, `thickness = 2.`, `bendingMatId = 1`.

## ShellPropNodal

The property of a shell with a thickness at each grid point, a formulation and the options of the explicit shell elements.

**Record format and fields**

`ShellPropNodal;id;matId;formulation;quadrature;integrationPointCount;shearFactor;referenceSurface;spinCorrection;thickness1;thickness2;thickness3;thickness4;transverseShear;shearLocking`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `formulation` | `text` | — | Selects the mathematical treatment of the property or element behavior. |
| 4 | `quadrature` | `text` | — | Selects the quadrature rule for evaluation of the integral. |
| 5 | `integrationPointCount` | `integer` | — | Number of integration point entries. |
| 6 | `shearFactor` | `real` | — | Multiplier for shear. |
| 7 | `referenceSurface` | `text` | — | Through-thickness surface from which section locations are measured. |
| 8 | `spinCorrection` | `text` | — | Selects the correction associated with rotation or spin of the section. |
| 9 | `thickness1` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 1. |
| 10 | `thickness2` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 2. |
| 11 | `thickness3` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 3. |
| 12 | `thickness4` | `real` | 0.0 | Through-thickness dimension, in model length units. Entry 4. |
| 13 | `transverseShear` | `text` | — | Shear response perpendicular to the reference plane. |
| 14 | `shearLocking` | `text` | — | Selects the treatment of excessive shear constraint in bending. |

Accepted words: `AvoidShearLocking`, `BelytschkoLinTsay`, `Bottom`, `C0Triangle`, `Constant`, `ConstantApproximation`, `Dummy`, `Element`, `Gauss`, `HughesLiu`, `KeyHoff`, `Linear`, `LobattoPoints`, `Membrane`, `MidSurface`, `No`, `NoAvoidShearLocking`, `Table`, `Top`, `Yes`.

**Example record**

~~~text
ShellPropNodal;2;2;Membrane;;;;;;0.3;0.3;0.3;0.3
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol700_bulk_viscosity_fabric_rigid.oos)

Reading the example gives `id = 2`, `matId = 2`, `formulation = Membrane`, `thickness1 = 0.3`.

## ShellPropNonlinear

The nonlinear extension of the [ShellProp](properties.md#shellprop), [CompProp](properties.md#compprop) or [CompPropGlobal](properties.md#comppropglobal) with the same property ID, for the shell elements ([ShellQuad4](elements.md#shellquad4), [ShellQuad4Drilling](elements.md#shellquad4drilling), [ShellQuad8](elements.md#shellquad8), [ShellTria3](elements.md#shelltria3), [ShellTria3Drilling](elements.md#shelltria3drilling), [ShellTria6](elements.md#shelltria6)) that name it.

**Record format and fields**

`ShellPropNonlinear;id;matId1;matId2;analysisType;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId1` | `integer` | 0 | Material identifier used to retrieve the constitutive data. Entry 1. |
| 3 | `matId2` | `integer` | 0 | Material identifier used to retrieve the constitutive data. Entry 2. |
| 4 | `analysisType` | `text` | — | Selects the analysis type for ShellPropNonlinear. |

**Keyed sections in `behaviorLines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ThreeNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior3` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 3. |
| 2 | `integration3` | `text` | — | Selects the rule used to integrate the element or section response. Entry 3. |
| 3 | `heatBehavior3` | `text` | — | Heat behavior setting for the element configuration identified by 3. |
| 4 | `heatIntegration3` | `text` | — | Heat integration setting for the element configuration identified by 3. |

**Section `FourNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior4` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 4. |
| 2 | `integration4` | `text` | — | Selects the rule used to integrate the element or section response. Entry 4. |
| 3 | `heatBehavior4` | `text` | — | Heat behavior setting for the element configuration identified by 4. |
| 4 | `heatIntegration4` | `text` | — | Heat integration setting for the element configuration identified by 4. |

**Section `SixNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior6` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 6. |
| 2 | `integration6` | `text` | — | Selects the rule used to integrate the element or section response. Entry 6. |
| 3 | `heatBehavior6` | `text` | — | Heat behavior setting for the element configuration identified by 6. |
| 4 | `heatIntegration6` | `text` | — | Heat integration setting for the element configuration identified by 6. |

**Section `EightNodeElems`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `behavior8` | `text` | — | Selects the assumed response of the body or contact formulation. Entry 8. |
| 2 | `integration8` | `text` | — | Selects the rule used to integrate the element or section response. Entry 8. |
| 3 | `heatBehavior8` | `text` | — | Heat behavior setting for the element configuration identified by 8. |
| 4 | `heatIntegration8` | `text` | — | Heat integration setting for the element configuration identified by 8. |

Accepted words: `AssumedStrain`, `AxisymComposite`, `AxisymSolid`, `Bar`, `Beam`, `Constant`, `EightNodeElems`, `Element`, `FourNodeElems`, `ImplicitHeat`, `ImplicitStructural`, `ImplicitStructuralHeat`, `IncompressibleAxisym`, `IncompressiblePlaneStrain`, `IncompressibleSolid`, `Linear`, `LinearCubic`, `LinearCubicClosed`, `LinearCubicOpen`, `LinearDiscreteKirchhoff`, `LinearReducedHourglass`, `LinearShear`, `LinearTwist`, `Membrane`, `Numerical`, `PlaneStrain`, `PlaneStrainComposite`, `PlaneStress`, `Quadratic`, `QuadraticReduced`, `QuadraticTwist`, `Rod`, `SixNodeElems`, `Smeared`, `Solid`, `SolidComposite`, `Table`, `ThickShell`, `ThinShell`, `ThreeNodeElems`.

**Example record**

~~~text
ShellPropNonlinear;1;;;ImplicitHeat;FourNodeElems;;;ThickShell;Linear
~~~

[Model containing this record](../../../validation/models/dynamics/heat_shell_sloadn1_sol400.oos)

Reading the example gives `id = 1`, `analysisType = ImplicitHeat`.

**Referenced records in this example**

- [ShellProp](properties.md#shellprop) via `id = 1`.

## SolidProp

The property of solid elements ([SolidHexa](elements.md#solidhexa), [SolidPenta](elements.md#solidpenta), [SolidTetra](elements.md#solidtetra)).

**Record format and fields**

`SolidProp;id;matId;matFrameId;integration;stressLocation;integrationOrder;elementFunction`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `matFrameId` | `integer` | 0 | Coordinate system defining the material directions. |
| 4 | `integration` | `any` | — | Selects the integration scheme of solid elements using the property. |
| 5 | `stressLocation` | `any` | — | Selects the locations where element stresses are recovered. |
| 6 | `integrationOrder` | `any` | — | Specifies the integration order for the associated solid elements. |
| 7 | `elementFunction` | `text` | — | Selects the element formulation associated with the property. |

Accepted words: `BubbleFunctions`, `FreeFluid`, `Full`, `Gauss`, `Node`, `Poroelastic`, `PressureFluid`, `Reduced`, `SolidMechanics`, `SolidShell`, `ThreePoints`, `TwoPoints`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
SolidProp;3;9;40
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/coordinates_monitor_static.oos)

Reading the example gives `id = 3`, `matId = 9`, `matFrameId = 40`.

**Referenced records in this example**

- [AnisoMat3D](materials.md#anisomat3d) via `matId = 9`.
- [GeneralFrame3](coordinate_systems.md#generalframe3) via `matFrameId = 40`.

## SolidPropHyperelastic

The property of a fully nonlinear hyperelastic solid element.

**Record format and fields**

`SolidPropHyperelastic;id;matId;stressLocation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `stressLocation` | `text` | — | Location in the element or section at which stress is evaluated. |

Accepted words: `Gauss`, `Node`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
SolidPropHyperelastic;3;3;Node
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solids_initial_state.oos)

Reading the example gives `id = 3`, `matId = 3`, `stressLocation = Node`.

**Referenced records in this example**

- [HyperelasticPolynomialMat](materials.md#hyperelasticpolynomialmat) via `matId = 3`.

## SpringOffsetProp

The property of a translational spring element [SpringOffsetExplicit](elements.md#springoffsetexplicit), linear or nonlinear.

**Record format and fields**

`SpringOffsetProp;id;stiffness;tensileFailureForce;compressiveFailureForce;loadingTableId;unloadingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `stiffness` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. |
| 3 | `tensileFailureForce` | `real` | — | Tensile failure force (force). |
| 4 | `compressiveFailureForce` | `real` | — | Compressive failure force (force). |
| 5 | `loadingTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 6 | `unloadingTableId` | `integer` | 0 | Identifier addressing dynamic table data. |

Accepted words: `Constant`, `Element`, `Table`, `TableDynamic1`.

**Example record**

~~~text
SpringOffsetProp;4105;20.;2.E+3;2.E+3
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4105`, `stiffness = 20.`, `tensileFailureForce = 2.E+3`, `compressiveFailureForce = 2.E+3`.

## SpringProp

Supplies scalar spring stiffness and optional damping and stress-recovery data.

**Record format and fields**

`SpringProp;id1;stiffness1;structuralDamping1;stressCoefficient1;id2;stiffness2;structuralDamping2;stressCoefficient2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered SpringProp data. |
| 2 | `stiffness1` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 1. |
| 3 | `structuralDamping1` | `real` | — | Structural damping coefficient for the associated material or property. Entry 1. |
| 4 | `stressCoefficient1` | `real` | — | Coefficient used to recover stress from the element force or section response. Entry 1. |
| 5 | `id2` | `integer` | — | Identifier at position 2 in the ordered SpringProp data. |
| 6 | `stiffness2` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 2. |
| 7 | `structuralDamping2` | `real` | — | Structural damping coefficient for the associated material or property. Entry 2. |
| 8 | `stressCoefficient2` | `real` | — | Coefficient used to recover stress from the element force or section response. Entry 2. |

Designable field descriptors: stiffness, structuralDamping or stressCoefficient.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
SpringProp;201;1.E+3;;1.;202;1.E+3;;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id1 = 201`, `stiffness1 = 1.E+3`, `stressCoefficient1 = 1.`, `id2 = 202`.

## SpringPropFreq

The frequency dependent or nonlinear properties of the [SpringProp](properties.md#springprop) with the same ID.

**Record format and fields**

`SpringPropFreq;id;stiffnessTableId;structuralDampingTableId;nonlinearForceTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stiffnessTableId` | `integer` | 0 | Identifier addressing dynamic table data. |
| 3 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 4 | `nonlinearForceTableId` | `integer` | 0 | Identifier addressing dynamic table data. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
SpringPropFreq;201;111
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol400_nonlinear_elements.oos)

Reading the example gives `id = 201`, `stiffnessTableId = 111`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `stiffnessTableId = 111`.

## SpringPropTable

The property of a springwhose force-deflection curve is a [TableDynamic1](tables.md#tabledynamic1).

**Record format and fields**

`SpringPropTable;id;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `tableId` | `integer` | Required | Identifier of the tabulated function to evaluate. |

Accepted words: `TableDynamic1`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
SpringPropTable;10;12
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol700_explicit_springs.oos)

Reading the example gives `id = 10`, `tableId = 12`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `tableId = 12`.

## TiltingPadBearingProp

Supplies tilting-pad journal bearing data to the external service associated with a two-dimensional bushing.

**Record format and fields**

`TiltingPadBearingProp;id;timeLimit;title1;title2;journalRadius;radialClearance;padOuterRadius;bearingLength;padModulus;padExpansion;journalExpansion;housingExpansion;padCount;elementCount;eccentricityInput;<pads>;<afterPads>;<cases>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | — | Identifier in the namespace of this card type. |
| 2 | `timeLimit` | `real` | — | Longest permitted duration of the specified operation. |
| 3 | `title1` | `text` | — | Descriptive title field 1 retained with the bearing definition. Written as one text field. |
| 4 | `title2` | `text` | — | Descriptive title field 2 retained with the bearing definition. Written as one text field. |
| 5 | `journalRadius` | `real` | — | Journal radius (length). |
| 6 | `radialClearance` | `real` | — | Gap in the radial direction between mating surfaces (length). |
| 7 | `padOuterRadius` | `real` | — | Pad outer radius (length). |
| 8 | `bearingLength` | `real` | — | Bearing length (length). |
| 9 | `padModulus` | `real` | — | Pad modulus (force per area). |
| 10 | `padExpansion` | `real` | — | Expansion of the pad under a temperature change. |
| 11 | `journalExpansion` | `real` | — | Thermal expansion contribution of the journal. |
| 12 | `housingExpansion` | `real` | — | Thermal expansion contribution of the bearing housing. |
| 13 | `padCount` | `integer` | — | Number of pad entries. |
| 14 | `elementCount` | `integer` | — | Number of element entries. |
| 15 | `eccentricityInput` | `integer` | — | Specifies how bearing eccentricity is supplied. |

**Repeated group `pads`**. The field `padCount` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `padArc` | `real` | — | Angular span of one bearing pad. |
| 2 | `pivotOffset` | `real` | — | Displacement of the pad pivot relative to the reference position. |
| 3 | `preload` | `real` | — | Load or initial bias present before the operating load is applied. |
| 4 | `pivotAngle` | `real` | — | Angular location of the bearing-pad pivot. |
| 5 | `padPolarInertia` | `real` | — | Polar mass moment of inertia of the bearing pad. |
| 6 | `pivotStiffness` | `real` | — | Translational restoring force per unit pivot displacement. |
| 7 | `padMass` | `real` | — | Mass assigned to the bearing pad. |
| 8 | `padBendingInertia` | `real` | — | Second moment of the section area for bending about the indicated local axis (length to the fourth power). |

**Repeated group `afterPads`**. The layout contains 1 repetition(s).

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `oilConductivity` | `real` | — | Thermal conductivity of the lubricant. |
| 2 | `padConductivity` | `real` | — | Thermal conductivity of the pad material. |
| 3 | `padBackTemperature` | `real` | — | Pad back temperature (temperature). |
| 4 | `journalTemperature` | `real` | — | Journal temperature (temperature). |
| 5 | `sumpPressure` | `real` | — | Sump pressure (force per area). |
| 6 | `inletTemperature` | `real` | — | Inlet temperature (temperature). |
| 7 | `cavitationConductivity` | `real` | — | Thermal conductivity used in the cavitated region of the film. |
| 8 | `cavitationSpecificHeat` | `real` | — | Heat capacity per unit mass used in the cavitated region. |
| 9 | `oilDensity` | `real` | — | Mass per unit volume of the lubricant. |
| 10 | `oilSpecificHeat` | `real` | — | Heat capacity per unit mass of the lubricant. |
| 11 | `viscosityTemperatureA` | `real` | — | Temperature corresponding to the first viscosity value. |
| 12 | `viscosityA` | `real` | — | First viscosity value used to define the temperature dependence. |
| 13 | `viscosityTemperatureB` | `real` | — | Temperature corresponding to the second viscosity value. |
| 14 | `viscosityB` | `real` | — | Second viscosity value used to define the temperature dependence. |
| 15 | `sumpMixingFactor` | `real` | — | Multiplier for sump mixing. |
| 16 | `manufacturingTemperature` | `real` | — | Manufacturing temperature (temperature). |
| 17 | `convergenceTolerance` | `real` | — | Permitted numerical deviation for convergence. |
| 18 | `initialPositionX` | `real` | — | Component X of the initial position. |
| 19 | `initialPositionY` | `real` | — | Component Y of the initial position. |
| 20 | `axialNodeCount` | `real` | — | Number of axial node entries. |
| 21 | `pressureRelaxation` | `real` | — | Relaxation applied to the pressure update during iteration. |
| 22 | `temperatureRelaxation` | `real` | — | Relaxation applied to the temperature update during iteration. |
| 23 | `journalThermalModel` | `integer` | — | Selects how temperature in the journal is represented. |
| 24 | `inletThermalBoundary` | `integer` | — | Thermal boundary condition at the lubricant inlet. |
| 25 | `turbulence` | `integer` | — | Selects treatment of turbulent flow in the lubricant film. |
| 26 | `dimensionalOutput` | `integer` | — | Cross-section dimension in the order specified by the selected section shape (length). |
| 27 | `padConduction` | `integer` | — | Selects treatment of heat conduction within the pad. |
| 28 | `padBackThermal` | `integer` | — | Thermal condition on the back surface of the pad. |
| 29 | `journalThermalGradient` | `integer` | — | Temperature gradient imposed or computed in the journal. |
| 30 | `cavitation` | `integer` | — | Specifies how loss of liquid continuity is treated in the bearing film. |
| 31 | `crossCoupling` | `integer` | — | Controls off-diagonal coupling between response components. |
| 32 | `padDeformation` | `integer` | — | Selects treatment of elastic deformation of the pad. |
| 33 | `pivotFlexibility` | `integer` | — | Compliance at the pad support, inverse to the corresponding stiffness. |
| 34 | `unitSystem` | `integer` | — | Consistent measurement convention for quantities on this record. |
| 35 | `floodedSump` | `integer` | — | Selects the flooded-sump lubricant boundary condition. |
| 36 | `pivotRotationStiffness` | `real` | — | Restoring moment per unit rotation at the pivot. |
| 37 | `initialPivotDeflection` | `real` | — | Initial displacement assigned at the bearing-pad pivot. |
| 38 | `hotOilCarryOver` | `real` | — | Fraction or option for recirculating heated lubricant into the film. |
| 39 | `coldOilCarryOver` | `real` | — | Fraction or option for mixing cold incoming lubricant with the film. |
| 40 | `caseCount` | `integer` | — | Number of case entries. |
| 41 | `maxIterations` | `real` | — | Maximum number of iterations permitted at this stage. |
| 42 | `stiffnessSmoothing` | `real` | — | Controls smoothing of the force–deflection slope. |

**Repeated group `cases`**. The field `caseCount` gives the number of repetitions.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `speed` | `real` | — | Speed (length per time). |
| 2 | `loadX` | `real` | — | Component X of the applied load. |
| 3 | `loadY` | `real` | — | Component Y of the applied load. |
| 4 | `whirlRatio` | `real` | — | Relative measure of whirl. |
| 5 | `positionRelaxation` | `real` | — | Relaxation applied to the position update during iteration. |
| 6 | `oilFlow` | `real` | — | Lubricant flow supplied to the bearing. |
| 7 | `deformationRelaxation` | `real` | — | Relaxation applied to the deformation update during iteration. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TiltingPadBearingProp;21;600.;BRG1;LOADPAD;2.;0.004;3.;2.5;3.1E+7;6.E-6;7.E-6;8.E-6;2;20;0;60.;0.5;0.3;90.;0.001;0.;0.;0.;60.;0.5;0.3;270.;0.001;0.;0.;0.;2.E-6;6.7E-4;120.;160.;0.;150.;5.;0.;8.E-5;180.;100.;4.1E-6;210.;6.8E-7;1.;75.;0.001;0.2;0.2;2.;100.;100.;0;2;1;0;0;0;0;1;0;2;0;0;0;0.;0.;100.;0.;1;100;100;3.E+3;0.;500.;1.;1.;0.;1.
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/service_and_paa_cards.oos)

Reading the example gives `id = 21`, `timeLimit = 600.`, `title1 = BRG1`, `title2 = LOADPAD`.

## TubeProp

The property of a thin-walled cylindrical tube ([Tube2](elements.md#tube2)).

**Record format and fields**

`TubeProp;id;matId;outerDiameter;thickness;nonStructMass;outerDiameter2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `outerDiameter` | `real` | Required | Outer diameter (length). |
| 4 | `thickness` | `real` | — | Through-thickness dimension, in model length units. |
| 5 | `nonStructMass` | `real` | 0.0 | Additional mass distributed with the element or property; its geometric basis follows the section definition. |
| 6 | `outerDiameter2` | `real` | same as outerDiameter | Outer diameter 2 (length). |

Designable field descriptors: outerDiameter, thickness, nonStructMass, outerDiameter2.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
TubeProp;3;1;6.;1.
~~~

[Model containing this record](../../../validation/models/nonlinear_sol400/sol106_plastic_elements.oos)

Reading the example gives `id = 3`, `matId = 1`, `outerDiameter = 6.`, `thickness = 1.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.

## UserElemService

Connects a two-dimensional bushing property to the user routine supplying its stiffness, mass and damping.

**Record format and fields**

`UserElemService;id;propType;groupName;userRoutineName;dependence;nominalSpeed;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `propType` | `text` | — | Selects the property type for UserElemService. |
| 3 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 4 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |
| 5 | `dependence` | `text` | — | Selects the independent quantity governing the property variation. |
| 6 | `nominalSpeed` | `real` | — | Nominal speed (length per time). |

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

Accepted words: `BushProp2D`, `Constant`, `Element`, `Frequency`, `IntegerBlock`, `NoMassDependence`, `RealBlock`, `Table`, `TextBlock`.

**Example record**

~~~text
UserElemService;50;BushProp2D;ELEMENT;UBEAR;Frequency;60.;RealBlock;2;0.05;0.01
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `id = 50`, `propType = BushProp2D`, `groupName = ELEMENT`, `userRoutineName = UBEAR`.

## ViscousDamperProp

Defines translational and rotational damping coefficients for a viscous damper.

**Record format and fields**

`ViscousDamperProp;id1;extensionalDamping1;rotationalDamping1;id2;extensionalDamping2;rotationalDamping2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id1` | `integer` | — | Identifier at position 1 in the ordered ViscousDamperProp data. |
| 2 | `extensionalDamping1` | `real` | — | Entry 1 of the extensional damping coefficients in the local component order. |
| 3 | `rotationalDamping1` | `real` | — | Entry 1 of the rotational damping coefficients in the local component order. |
| 4 | `id2` | `integer` | — | Identifier at position 2 in the ordered ViscousDamperProp data. |
| 5 | `extensionalDamping2` | `real` | — | Entry 2 of the extensional damping coefficients in the local component order. |
| 6 | `rotationalDamping2` | `real` | — | Entry 2 of the rotational damping coefficients in the local component order. |

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
ViscousDamperProp;189;0.6;0.
~~~

[Model containing this record](../../../validation/models/common/elements_model.oos)

Reading the example gives `id1 = 189`, `extensionalDamping1 = 0.6`, `rotationalDamping1 = 0.`.

## ViscousDamperPropNonlinear

The property of a nonlinear damper whose force depends on the velocity through a [TableDynamic1](tables.md#tabledynamic1) (the x values of the table are velocities, the y values forces; the values between are interpolated).

**Record format and fields**

`ViscousDamperPropNonlinear;id;tableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `tableId` | `integer` | Required | Identifier of the tabulated function to evaluate. |

Accepted words: `TableDynamic1`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
ViscousDamperPropNonlinear;4106;4206
~~~

[Model containing this record](../../../validation/models/explicit_structures/hinged_flap_discrete.oos)

Reading the example gives `id = 4106`, `tableId = 4206`.

**Referenced records in this example**

- [TableDynamic1](tables.md#tabledynamic1) via `tableId = 4206`.

## WeldProp

The property of a connector element ([Weld](elements.md#weld)).

**Record format and fields**

`WeldProp;id;matId;diameter;eliminateConstraints;kind;minLengthRatio;maxLengthRatio`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `diameter` | `real` | Required | Diameter (length). |
| 4 | `eliminateConstraints` | `text` | — | Controls elimination of the indicated constraint equations. |
| 5 | `kind` | `text` | — | Selects the kind for WeldProp. |
| 6 | `minLengthRatio` | `real` | — | Relative measure of minimum length. |
| 7 | `maxLengthRatio` | `real` | — | Relative measure of maximum length. |

Accepted words: `Off`, `On`, `SpotWeld`.

**Reader diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
WeldProp;1;1;3.
~~~

[Model containing this record](../../../validation/models/fasteners/cweld_forms.oos)

Reading the example gives `id = 1`, `matId = 1`, `diameter = 3.`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `matId = 1`.
