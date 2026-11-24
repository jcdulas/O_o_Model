# Materials

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AnisoMat2D

An anisotropic material for two-dimensional elements.

**Record format and fields**

`AnisoMat2D;id;stiffness11;stiffness12;stiffness13;stiffness22;stiffness23;stiffness33;density;thermalExpansion1;thermalExpansion2;thermalExpansion3;referenceTemperature;structuralDamping;tensionAllowable;compressionAllowable;shearAllowable;stressFrameId;structuralDamping11;structuralDamping12;structuralDamping13;structuralDamping22;structuralDamping23;structuralDamping33`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `stiffness11` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 11. |
| 3 | `stiffness12` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 12. |
| 4 | `stiffness13` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 13. |
| 5 | `stiffness22` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 22. |
| 6 | `stiffness23` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 23. |
| 7 | `stiffness33` | `real` | 0.0 | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 33. |
| 8 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 9 | `thermalExpansion1` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 10 | `thermalExpansion2` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 11 | `thermalExpansion3` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 3. |
| 12 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 13 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 14 | `tensionAllowable` | `real` | 0.0 | Allowable tensile stress, in force per area. |
| 15 | `compressionAllowable` | `real` | 0.0 | Allowable compressive stress, in force per area. |
| 16 | `shearAllowable` | `real` | 0.0 | Allowable shear stress, in force per area. |
| 17 | `stressFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 18 | `structuralDamping11` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 11. |
| 19 | `structuralDamping12` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 12. |
| 20 | `structuralDamping13` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 13. |
| 21 | `structuralDamping22` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 22. |
| 22 | `structuralDamping23` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 23. |
| 23 | `structuralDamping33` | `real` | 0.0 | Structural damping coefficient for the associated material or property. Entry 33. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the material ID must be a positive integer.

**Example record**

~~~text
AnisoMat2D;2;230769.;69231.;;230769.;;80769.;7.85E-9;;;;;0.02
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 2`, `stiffness11 = 230769.`, `stiffness12 = 69231.`, `stiffness22 = 230769.`.

## AnisoMat2DFreq

The frequency dependence of the properties of an [AnisoMat2D](materials.md#anisomat2d) (a shell element anisotropic material).

**Record format and fields**

`AnisoMat2DFreq;id;stiffness11TableId;stiffness12TableId;stiffness13TableId;stiffness22TableId;stiffness23TableId;stiffness33TableId;structuralDampingTableId;structuralDamping11TableId;structuralDamping12TableId;structuralDamping13TableId;structuralDamping22TableId;structuralDamping23TableId;structuralDamping33TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stiffness11TableId` | `integer` | — | Table supplying the variation of stiffness 11. |
| 3 | `stiffness12TableId` | `integer` | — | Table supplying the variation of stiffness 12. |
| 4 | `stiffness13TableId` | `integer` | — | Table supplying the variation of stiffness 13. |
| 5 | `stiffness22TableId` | `integer` | — | Table supplying the variation of stiffness 22. |
| 6 | `stiffness23TableId` | `integer` | — | Table supplying the variation of stiffness 23. |
| 7 | `stiffness33TableId` | `integer` | — | Table supplying the variation of stiffness 33. |
| 8 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 9 | `structuralDamping11TableId` | `integer` | — | Table supplying the variation of structural damping 11. |
| 10 | `structuralDamping12TableId` | `integer` | — | Table supplying the variation of structural damping 12. |
| 11 | `structuralDamping13TableId` | `integer` | — | Table supplying the variation of structural damping 13. |
| 12 | `structuralDamping22TableId` | `integer` | — | Table supplying the variation of structural damping 22. |
| 13 | `structuralDamping23TableId` | `integer` | — | Table supplying the variation of structural damping 23. |
| 14 | `structuralDamping33TableId` | `integer` | — | Table supplying the variation of structural damping 33. |

**Example record**

~~~text
AnisoMat2DFreq;2;21;;;21;;22;23
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 2`, `stiffness11TableId = 21`, `stiffness22TableId = 21`, `stiffness33TableId = 22`.

**Referenced records in this example**

- [AnisoMat2D](materials.md#anisomat2d) via `id = 2`.

## AnisoMat2DTemperature

The temperature dependent properties of an [AnisoMat2D](materials.md#anisomat2d).

**Record format and fields**

`AnisoMat2DTemperature;id;stiffness11TableId;stiffness12TableId;stiffness13TableId;stiffness22TableId;stiffness23TableId;stiffness33TableId;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId;structuralDampingTableId;tensionAllowableTableId;compressionAllowableTableId;shearAllowableTableId;structuralDamping11TableId;structuralDamping12TableId;structuralDamping13TableId;structuralDamping22TableId;structuralDamping23TableId;structuralDamping33TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stiffness11TableId` | `integer` | — | Table supplying the variation of stiffness 11. |
| 3 | `stiffness12TableId` | `integer` | — | Table supplying the variation of stiffness 12. |
| 4 | `stiffness13TableId` | `integer` | — | Table supplying the variation of stiffness 13. |
| 5 | `stiffness22TableId` | `integer` | — | Table supplying the variation of stiffness 22. |
| 6 | `stiffness23TableId` | `integer` | — | Table supplying the variation of stiffness 23. |
| 7 | `stiffness33TableId` | `integer` | — | Table supplying the variation of stiffness 33. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `thermalExpansion1TableId` | `integer` | — | Table supplying the variation of thermal expansion 1. |
| 10 | `thermalExpansion2TableId` | `integer` | — | Table supplying the variation of thermal expansion 2. |
| 11 | `thermalExpansion3TableId` | `integer` | — | Table supplying the variation of thermal expansion 3. |
| 12 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 13 | `tensionAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |
| 14 | `compressionAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |
| 15 | `shearAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |
| 16 | `structuralDamping11TableId` | `integer` | — | Table supplying the variation of structural damping 11. |
| 17 | `structuralDamping12TableId` | `integer` | — | Table supplying the variation of structural damping 12. |
| 18 | `structuralDamping13TableId` | `integer` | — | Table supplying the variation of structural damping 13. |
| 19 | `structuralDamping22TableId` | `integer` | — | Table supplying the variation of structural damping 22. |
| 20 | `structuralDamping23TableId` | `integer` | — | Table supplying the variation of structural damping 23. |
| 21 | `structuralDamping33TableId` | `integer` | — | Table supplying the variation of structural damping 33. |

**Example record**

~~~text
AnisoMat2DTemperature;2;201;201;;201;;201;;202;202
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 2`, `stiffness11TableId = 201`, `stiffness12TableId = 201`, `stiffness22TableId = 201`.

**Referenced records in this example**

- [AnisoMat2D](materials.md#anisomat2d) via `id = 2`.

## AnisoMat3D

An anisotropic material for solid elements.

**Record format and fields**

`AnisoMat3D;id;stiffness11;stiffness12;stiffness13;stiffness14;stiffness15;stiffness16;stiffness22;stiffness23;stiffness24;stiffness25;stiffness26;stiffness33;stiffness34;stiffness35;stiffness36;stiffness44;stiffness45;stiffness46;stiffness55;stiffness56;stiffness66;density;thermalExpansion1;thermalExpansion2;thermalExpansion3;thermalExpansion4;thermalExpansion5;thermalExpansion6;referenceTemperature;structuralDamping;structuralDamping11;structuralDamping12;structuralDamping13;structuralDamping14;structuralDamping15;structuralDamping16;structuralDamping22;structuralDamping23;structuralDamping24;structuralDamping25;structuralDamping26;structuralDamping33;structuralDamping34;structuralDamping35;structuralDamping36;structuralDamping44;structuralDamping45;structuralDamping46;structuralDamping55;structuralDamping56;structuralDamping66`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `stiffness11` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 11. |
| 3 | `stiffness12` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 12. |
| 4 | `stiffness13` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 13. |
| 5 | `stiffness14` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 14. |
| 6 | `stiffness15` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 15. |
| 7 | `stiffness16` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 16. |
| 8 | `stiffness22` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 22. |
| 9 | `stiffness23` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 23. |
| 10 | `stiffness24` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 24. |
| 11 | `stiffness25` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 25. |
| 12 | `stiffness26` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 26. |
| 13 | `stiffness33` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 33. |
| 14 | `stiffness34` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 34. |
| 15 | `stiffness35` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 35. |
| 16 | `stiffness36` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 36. |
| 17 | `stiffness44` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 44. |
| 18 | `stiffness45` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 45. |
| 19 | `stiffness46` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 46. |
| 20 | `stiffness55` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 55. |
| 21 | `stiffness56` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 56. |
| 22 | `stiffness66` | `real` | — | Elastic restoring coefficient relating generalized force to the associated displacement. Entry 66. |
| 23 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 24 | `thermalExpansion1` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 25 | `thermalExpansion2` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 26 | `thermalExpansion3` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 3. |
| 27 | `thermalExpansion4` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 4. |
| 28 | `thermalExpansion5` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 5. |
| 29 | `thermalExpansion6` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 6. |
| 30 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 31 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 32 | `structuralDamping11` | `real` | — | Structural damping coefficient for the associated material or property. Entry 11. |
| 33 | `structuralDamping12` | `real` | — | Structural damping coefficient for the associated material or property. Entry 12. |
| 34 | `structuralDamping13` | `real` | — | Structural damping coefficient for the associated material or property. Entry 13. |
| 35 | `structuralDamping14` | `real` | — | Structural damping coefficient for the associated material or property. Entry 14. |
| 36 | `structuralDamping15` | `real` | — | Structural damping coefficient for the associated material or property. Entry 15. |
| 37 | `structuralDamping16` | `real` | — | Structural damping coefficient for the associated material or property. Entry 16. |
| 38 | `structuralDamping22` | `real` | — | Structural damping coefficient for the associated material or property. Entry 22. |
| 39 | `structuralDamping23` | `real` | — | Structural damping coefficient for the associated material or property. Entry 23. |
| 40 | `structuralDamping24` | `real` | — | Structural damping coefficient for the associated material or property. Entry 24. |
| 41 | `structuralDamping25` | `real` | — | Structural damping coefficient for the associated material or property. Entry 25. |
| 42 | `structuralDamping26` | `real` | — | Structural damping coefficient for the associated material or property. Entry 26. |
| 43 | `structuralDamping33` | `real` | — | Structural damping coefficient for the associated material or property. Entry 33. |
| 44 | `structuralDamping34` | `real` | — | Structural damping coefficient for the associated material or property. Entry 34. |
| 45 | `structuralDamping35` | `real` | — | Structural damping coefficient for the associated material or property. Entry 35. |
| 46 | `structuralDamping36` | `real` | — | Structural damping coefficient for the associated material or property. Entry 36. |
| 47 | `structuralDamping44` | `real` | — | Structural damping coefficient for the associated material or property. Entry 44. |
| 48 | `structuralDamping45` | `real` | — | Structural damping coefficient for the associated material or property. Entry 45. |
| 49 | `structuralDamping46` | `real` | — | Structural damping coefficient for the associated material or property. Entry 46. |
| 50 | `structuralDamping55` | `real` | — | Structural damping coefficient for the associated material or property. Entry 55. |
| 51 | `structuralDamping56` | `real` | — | Structural damping coefficient for the associated material or property. Entry 56. |
| 52 | `structuralDamping66` | `real` | — | Structural damping coefficient for the associated material or property. Entry 66. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `stiffness11` — the terms of the material property matrix must be finite numbers.
- `structuralDamping11` — the terms of the damping matrix must be finite numbers.

**Example record**

~~~text
AnisoMat3D;1;137755.;4592.;4592.;;;;10867.;4439.;;;;10867.;;;;5.E+3;;;3200.;;5.E+3;1.6E-9
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol101_layered_solid_cord3g.oos)

Reading the example gives `id = 1`, `stiffness11 = 137755.`, `stiffness12 = 4592.`, `stiffness13 = 4592.`.

## AnisoMat3DFreq

The frequency dependence of the properties of an [AnisoMat3D](materials.md#anisomat3d) (a solid element anisotropic material).

**Record format and fields**

`AnisoMat3DFreq;id;stiffness11TableId;stiffness12TableId;stiffness13TableId;stiffness14TableId;stiffness15TableId;stiffness16TableId;stiffness22TableId;stiffness23TableId;stiffness24TableId;stiffness25TableId;stiffness26TableId;stiffness33TableId;stiffness34TableId;stiffness35TableId;stiffness36TableId;stiffness44TableId;stiffness45TableId;stiffness46TableId;stiffness55TableId;stiffness56TableId;stiffness66TableId;structuralDampingTableId;structuralDamping11TableId;structuralDamping12TableId;structuralDamping13TableId;structuralDamping14TableId;structuralDamping15TableId;structuralDamping16TableId;structuralDamping22TableId;structuralDamping23TableId;structuralDamping24TableId;structuralDamping25TableId;structuralDamping26TableId;structuralDamping33TableId;structuralDamping34TableId;structuralDamping35TableId;structuralDamping36TableId;structuralDamping44TableId;structuralDamping45TableId;structuralDamping46TableId;structuralDamping55TableId;structuralDamping56TableId;structuralDamping66TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stiffness11TableId` | `integer` | — | Table supplying the variation of stiffness 11. |
| 3 | `stiffness12TableId` | `integer` | — | Table supplying the variation of stiffness 12. |
| 4 | `stiffness13TableId` | `integer` | — | Table supplying the variation of stiffness 13. |
| 5 | `stiffness14TableId` | `integer` | — | Table supplying the variation of stiffness 14. |
| 6 | `stiffness15TableId` | `integer` | — | Table supplying the variation of stiffness 15. |
| 7 | `stiffness16TableId` | `integer` | — | Table supplying the variation of stiffness 16. |
| 8 | `stiffness22TableId` | `integer` | — | Table supplying the variation of stiffness 22. |
| 9 | `stiffness23TableId` | `integer` | — | Table supplying the variation of stiffness 23. |
| 10 | `stiffness24TableId` | `integer` | — | Table supplying the variation of stiffness 24. |
| 11 | `stiffness25TableId` | `integer` | — | Table supplying the variation of stiffness 25. |
| 12 | `stiffness26TableId` | `integer` | — | Table supplying the variation of stiffness 26. |
| 13 | `stiffness33TableId` | `integer` | — | Table supplying the variation of stiffness 33. |
| 14 | `stiffness34TableId` | `integer` | — | Table supplying the variation of stiffness 34. |
| 15 | `stiffness35TableId` | `integer` | — | Table supplying the variation of stiffness 35. |
| 16 | `stiffness36TableId` | `integer` | — | Table supplying the variation of stiffness 36. |
| 17 | `stiffness44TableId` | `integer` | — | Table supplying the variation of stiffness 44. |
| 18 | `stiffness45TableId` | `integer` | — | Table supplying the variation of stiffness 45. |
| 19 | `stiffness46TableId` | `integer` | — | Table supplying the variation of stiffness 46. |
| 20 | `stiffness55TableId` | `integer` | — | Table supplying the variation of stiffness 55. |
| 21 | `stiffness56TableId` | `integer` | — | Table supplying the variation of stiffness 56. |
| 22 | `stiffness66TableId` | `integer` | — | Table supplying the variation of stiffness 66. |
| 23 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 24 | `structuralDamping11TableId` | `integer` | — | Table supplying the variation of structural damping 11. |
| 25 | `structuralDamping12TableId` | `integer` | — | Table supplying the variation of structural damping 12. |
| 26 | `structuralDamping13TableId` | `integer` | — | Table supplying the variation of structural damping 13. |
| 27 | `structuralDamping14TableId` | `integer` | — | Table supplying the variation of structural damping 14. |
| 28 | `structuralDamping15TableId` | `integer` | — | Table supplying the variation of structural damping 15. |
| 29 | `structuralDamping16TableId` | `integer` | — | Table supplying the variation of structural damping 16. |
| 30 | `structuralDamping22TableId` | `integer` | — | Table supplying the variation of structural damping 22. |
| 31 | `structuralDamping23TableId` | `integer` | — | Table supplying the variation of structural damping 23. |
| 32 | `structuralDamping24TableId` | `integer` | — | Table supplying the variation of structural damping 24. |
| 33 | `structuralDamping25TableId` | `integer` | — | Table supplying the variation of structural damping 25. |
| 34 | `structuralDamping26TableId` | `integer` | — | Table supplying the variation of structural damping 26. |
| 35 | `structuralDamping33TableId` | `integer` | — | Table supplying the variation of structural damping 33. |
| 36 | `structuralDamping34TableId` | `integer` | — | Table supplying the variation of structural damping 34. |
| 37 | `structuralDamping35TableId` | `integer` | — | Table supplying the variation of structural damping 35. |
| 38 | `structuralDamping36TableId` | `integer` | — | Table supplying the variation of structural damping 36. |
| 39 | `structuralDamping44TableId` | `integer` | — | Table supplying the variation of structural damping 44. |
| 40 | `structuralDamping45TableId` | `integer` | — | Table supplying the variation of structural damping 45. |
| 41 | `structuralDamping46TableId` | `integer` | — | Table supplying the variation of structural damping 46. |
| 42 | `structuralDamping55TableId` | `integer` | — | Table supplying the variation of structural damping 55. |
| 43 | `structuralDamping56TableId` | `integer` | — | Table supplying the variation of structural damping 56. |
| 44 | `structuralDamping66TableId` | `integer` | — | Table supplying the variation of structural damping 66. |

**Example record**

~~~text
AnisoMat3DFreq;4;41;;;;;;;;;;;;;;;;;;;;;42
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 4`, `stiffness11TableId = 41`, `structuralDampingTableId = 42`.

**Referenced records in this example**

- [AnisoMat3D](materials.md#anisomat3d) via `id = 4`.

## AnisoMat3DTemperature

The temperature dependent properties of an [AnisoMat3D](materials.md#anisomat3d).

**Record format and fields**

`AnisoMat3DTemperature;id;stiffness11TableId;stiffness12TableId;stiffness13TableId;stiffness14TableId;stiffness15TableId;stiffness16TableId;stiffness22TableId;stiffness23TableId;stiffness24TableId;stiffness25TableId;stiffness26TableId;stiffness33TableId;stiffness34TableId;stiffness35TableId;stiffness36TableId;stiffness44TableId;stiffness45TableId;stiffness46TableId;stiffness55TableId;stiffness56TableId;stiffness66TableId;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId;thermalExpansion4TableId;thermalExpansion5TableId;thermalExpansion6TableId;structuralDampingTableId;structuralDamping11TableId;structuralDamping12TableId;structuralDamping13TableId;structuralDamping14TableId;structuralDamping15TableId;structuralDamping16TableId;structuralDamping22TableId;structuralDamping23TableId;structuralDamping24TableId;structuralDamping25TableId;structuralDamping26TableId;structuralDamping33TableId;structuralDamping34TableId;structuralDamping35TableId;structuralDamping36TableId;structuralDamping44TableId;structuralDamping45TableId;structuralDamping46TableId;structuralDamping55TableId;structuralDamping56TableId;structuralDamping66TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stiffness11TableId` | `integer` | — | Table supplying the variation of stiffness 11. |
| 3 | `stiffness12TableId` | `integer` | — | Table supplying the variation of stiffness 12. |
| 4 | `stiffness13TableId` | `integer` | — | Table supplying the variation of stiffness 13. |
| 5 | `stiffness14TableId` | `integer` | — | Table supplying the variation of stiffness 14. |
| 6 | `stiffness15TableId` | `integer` | — | Table supplying the variation of stiffness 15. |
| 7 | `stiffness16TableId` | `integer` | — | Table supplying the variation of stiffness 16. |
| 8 | `stiffness22TableId` | `integer` | — | Table supplying the variation of stiffness 22. |
| 9 | `stiffness23TableId` | `integer` | — | Table supplying the variation of stiffness 23. |
| 10 | `stiffness24TableId` | `integer` | — | Table supplying the variation of stiffness 24. |
| 11 | `stiffness25TableId` | `integer` | — | Table supplying the variation of stiffness 25. |
| 12 | `stiffness26TableId` | `integer` | — | Table supplying the variation of stiffness 26. |
| 13 | `stiffness33TableId` | `integer` | — | Table supplying the variation of stiffness 33. |
| 14 | `stiffness34TableId` | `integer` | — | Table supplying the variation of stiffness 34. |
| 15 | `stiffness35TableId` | `integer` | — | Table supplying the variation of stiffness 35. |
| 16 | `stiffness36TableId` | `integer` | — | Table supplying the variation of stiffness 36. |
| 17 | `stiffness44TableId` | `integer` | — | Table supplying the variation of stiffness 44. |
| 18 | `stiffness45TableId` | `integer` | — | Table supplying the variation of stiffness 45. |
| 19 | `stiffness46TableId` | `integer` | — | Table supplying the variation of stiffness 46. |
| 20 | `stiffness55TableId` | `integer` | — | Table supplying the variation of stiffness 55. |
| 21 | `stiffness56TableId` | `integer` | — | Table supplying the variation of stiffness 56. |
| 22 | `stiffness66TableId` | `integer` | — | Table supplying the variation of stiffness 66. |
| 23 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 24 | `thermalExpansion1TableId` | `integer` | — | Table supplying the variation of thermal expansion 1. |
| 25 | `thermalExpansion2TableId` | `integer` | — | Table supplying the variation of thermal expansion 2. |
| 26 | `thermalExpansion3TableId` | `integer` | — | Table supplying the variation of thermal expansion 3. |
| 27 | `thermalExpansion4TableId` | `integer` | — | Table supplying the variation of thermal expansion 4. |
| 28 | `thermalExpansion5TableId` | `integer` | — | Table supplying the variation of thermal expansion 5. |
| 29 | `thermalExpansion6TableId` | `integer` | — | Table supplying the variation of thermal expansion 6. |
| 30 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 31 | `structuralDamping11TableId` | `integer` | — | Table supplying the variation of structural damping 11. |
| 32 | `structuralDamping12TableId` | `integer` | — | Table supplying the variation of structural damping 12. |
| 33 | `structuralDamping13TableId` | `integer` | — | Table supplying the variation of structural damping 13. |
| 34 | `structuralDamping14TableId` | `integer` | — | Table supplying the variation of structural damping 14. |
| 35 | `structuralDamping15TableId` | `integer` | — | Table supplying the variation of structural damping 15. |
| 36 | `structuralDamping16TableId` | `integer` | — | Table supplying the variation of structural damping 16. |
| 37 | `structuralDamping22TableId` | `integer` | — | Table supplying the variation of structural damping 22. |
| 38 | `structuralDamping23TableId` | `integer` | — | Table supplying the variation of structural damping 23. |
| 39 | `structuralDamping24TableId` | `integer` | — | Table supplying the variation of structural damping 24. |
| 40 | `structuralDamping25TableId` | `integer` | — | Table supplying the variation of structural damping 25. |
| 41 | `structuralDamping26TableId` | `integer` | — | Table supplying the variation of structural damping 26. |
| 42 | `structuralDamping33TableId` | `integer` | — | Table supplying the variation of structural damping 33. |
| 43 | `structuralDamping34TableId` | `integer` | — | Table supplying the variation of structural damping 34. |
| 44 | `structuralDamping35TableId` | `integer` | — | Table supplying the variation of structural damping 35. |
| 45 | `structuralDamping36TableId` | `integer` | — | Table supplying the variation of structural damping 36. |
| 46 | `structuralDamping44TableId` | `integer` | — | Table supplying the variation of structural damping 44. |
| 47 | `structuralDamping45TableId` | `integer` | — | Table supplying the variation of structural damping 45. |
| 48 | `structuralDamping46TableId` | `integer` | — | Table supplying the variation of structural damping 46. |
| 49 | `structuralDamping55TableId` | `integer` | — | Table supplying the variation of structural damping 55. |
| 50 | `structuralDamping56TableId` | `integer` | — | Table supplying the variation of structural damping 56. |
| 51 | `structuralDamping66TableId` | `integer` | — | Table supplying the variation of structural damping 66. |

**Example record**

~~~text
AnisoMat3DTemperature;4;401;401;401;;;;401;401;;;;401;;;;401;;;401;;401
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 4`, `stiffness11TableId = 401`, `stiffness12TableId = 401`, `stiffness13TableId = 401`.

**Referenced records in this example**

- [AnisoMat3D](materials.md#anisomat3d) via `id = 4`.

## AxisymOrthoMat

A linear orthotropic material for the axisymmetric elements ([AxisymTria6](elements.md#axisymtria6)) and the [PlaneCompProp](properties.md#planecompprop) and [PlanePropNonlinearExt](properties.md#planepropnonlinearext) entries; x, theta (the azimuthal direction) and z are the material axes.

**Record format and fields**

`AxisymOrthoMat;id;youngsModulusX;youngsModulusTheta;youngsModulusZ;poissonRatioXth;poissonRatioThz;poissonRatioZx;density;shearModulusZx;thermalExpansionX;thermalExpansionTheta;thermalExpansionZ;referenceTemperature;structuralDamping`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `youngsModulusX` | `real` | Required | Uniaxial elastic modulus (force per area) in the X material or local axes. |
| 3 | `youngsModulusTheta` | `real` | Required | Uniaxial elastic modulus (force per area) in the Theta material or local axes. |
| 4 | `youngsModulusZ` | `real` | Required | Uniaxial elastic modulus (force per area) in the Z material or local axes. |
| 5 | `poissonRatioXth` | `real` | 0.0 | Transverse contraction ratio in the Xth material or local axes. |
| 6 | `poissonRatioThz` | `real` | 0.0 | Transverse contraction ratio in the Thz material or local axes. |
| 7 | `poissonRatioZx` | `real` | 0.0 | Transverse contraction ratio in the Zx material or local axes. |
| 8 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 9 | `shearModulusZx` | `real` | Required | Shear modulus (force per area) in the Zx material or local axes. |
| 10 | `thermalExpansionX` | `real` | 0.0 | Thermal expansion coefficient (inverse temperature) in the X material or local axes. |
| 11 | `thermalExpansionTheta` | `real` | 0.0 | Thermal expansion coefficient (inverse temperature) in the Theta material or local axes. |
| 12 | `thermalExpansionZ` | `real` | 0.0 | Thermal expansion coefficient (inverse temperature) in the Z material or local axes. |
| 13 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 14 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |

**Example record**

~~~text
AxisymOrthoMat;31;1.E+4;1.2E+4;1.1E+4;0.3;0.25;0.27;1.5E-9;4.E+3
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_axisymmetric_mats3_plcomp.oos)

Reading the example gives `id = 31`, `youngsModulusX = 1.E+4`, `youngsModulusTheta = 1.2E+4`, `youngsModulusZ = 1.1E+4`.

## AxisymOrthoMatStressDependent

Extends an axisymmetric orthotropic material with nonlinear elastic data.

**Record format and fields**

`AxisymOrthoMatStressDependent;id;youngsModulusXTableId;youngsModulusThetaTableId;youngsModulusZTableId;poissonRatioXthTableId;poissonRatioThzTableId;poissonRatioZxTableId;densityTableId;shearModulusZxTableId;thermalExpansionXTableId;thermalExpansionThetaTableId;thermalExpansionZTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulusXTableId` | `integer` | 0 | Uniaxial elastic modulus (force per area) in the XTableId material or local axes. |
| 3 | `youngsModulusThetaTableId` | `integer` | 0 | Uniaxial elastic modulus (force per area) in the ThetaTableId material or local axes. |
| 4 | `youngsModulusZTableId` | `integer` | 0 | Uniaxial elastic modulus (force per area) in the ZTableId material or local axes. |
| 5 | `poissonRatioXthTableId` | `integer` | 0 | Transverse contraction ratio in the XthTableId material or local axes. |
| 6 | `poissonRatioThzTableId` | `integer` | 0 | Transverse contraction ratio in the ThzTableId material or local axes. |
| 7 | `poissonRatioZxTableId` | `integer` | 0 | Transverse contraction ratio in the ZxTableId material or local axes. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `shearModulusZxTableId` | `integer` | 0 | Shear modulus (force per area) in the ZxTableId material or local axes. |
| 10 | `thermalExpansionXTableId` | `integer` | 0 | Thermal expansion coefficient (inverse temperature) in the XTableId material or local axes. |
| 11 | `thermalExpansionThetaTableId` | `integer` | 0 | Thermal expansion coefficient (inverse temperature) in the ThetaTableId material or local axes. |
| 12 | `thermalExpansionZTableId` | `integer` | 0 | Thermal expansion coefficient (inverse temperature) in the ZTableId material or local axes. |

**Example record**

~~~text
AxisymOrthoMatStressDependent;31;301
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_axisymmetric_mats3_plcomp.oos)

Reading the example gives `id = 31`, `youngsModulusXTableId = 301`.

**Referenced records in this example**

- [AxisymOrthoMat](materials.md#axisymorthomat) via `id = 31`.

## AxisymOrthoMatTemperature

The temperature dependent properties of an [AxisymOrthoMat](materials.md#axisymorthomat).

**Record format and fields**

`AxisymOrthoMatTemperature;id;youngsModulusXTableId;youngsModulusThetaTableId;youngsModulusZTableId;poissonRatioXthTableId;poissonRatioThzTableId;poissonRatioZxTableId;densityTableId;shearModulusZxTableId;thermalExpansionXTableId;thermalExpansionThetaTableId;thermalExpansionZTableId;structuralDampingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulusXTableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `youngsModulusThetaTableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `youngsModulusZTableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `poissonRatioXthTableId` | `integer` | 0 | Identifier addressing material table data. |
| 6 | `poissonRatioThzTableId` | `integer` | 0 | Identifier addressing material table data. |
| 7 | `poissonRatioZxTableId` | `integer` | 0 | Identifier addressing material table data. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `shearModulusZxTableId` | `integer` | 0 | Identifier addressing material table data. |
| 10 | `thermalExpansionXTableId` | `integer` | 0 | Identifier addressing material table data. |
| 11 | `thermalExpansionThetaTableId` | `integer` | 0 | Identifier addressing material table data. |
| 12 | `thermalExpansionZTableId` | `integer` | 0 | Identifier addressing material table data. |
| 13 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |

**Example record**

~~~text
AxisymOrthoMatTemperature;5;401;401;401;;;;;401;104
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 5`, `youngsModulusXTableId = 401`, `youngsModulusThetaTableId = 401`, `youngsModulusZTableId = 401`.

**Referenced records in this example**

- [AxisymOrthoMat](materials.md#axisymorthomat) via `id = 5`.
- [TableMaterial3](tables.md#tablematerial3) via `youngsModulusXTableId = 401`, `youngsModulusThetaTableId = 401`, `youngsModulusZTableId = 401`, `shearModulusZxTableId = 401`.
- [TableMaterial4](tables.md#tablematerial4) via `thermalExpansionXTableId = 104`.

## BulkViscosityMat

The bulk viscosity of a material.

**Record format and fields**

`BulkViscosityMat;id;bulkViscosityKind;quadraticBulkViscosity;linearBulkViscosity;compressionScale;membraneDamping;initialMetricRelaxation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bulkViscosityKind` | `text` | — | Selects the bulk viscosity kind for BulkViscosityMat. |
| 3 | `quadraticBulkViscosity` | `real` | 0.0 | Coefficient of the quadratic artificial bulk-viscosity term. |
| 4 | `linearBulkViscosity` | `real` | 1.0 | Coefficient of the linear artificial bulk-viscosity term. |
| 5 | `compressionScale` | `real` | 1.0 | Multiplier applied to the compressive branch of the response. |
| 6 | `membraneDamping` | `real` | 0.0 | Damping associated with in-plane membrane deformation. |
| 7 | `initialMetricRelaxation` | `real` | — | Initial relaxation of the reference metric in the constitutive model. |

Accepted words: `ExternalExplicitProgram`, `ExternalExplicitSolver`.

**Example record**

~~~text
BulkViscosityMat;1;ExternalExplicitProgram;1.5;0.06
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol700_bulk_viscosity_fabric_rigid.oos)

Reading the example gives `id = 1`, `bulkViscosityKind = ExternalExplicitProgram`, `quadraticBulkViscosity = 1.5`, `linearBulkViscosity = 0.06`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.

## CreepMat

The creep characteristics of an [IsoMat](materials.md#isomat), [AnisoMat2D](materials.md#anisomat2d) or [AnisoMat3D](materials.md#anisomat3d), from an empirical creep law or from tables.

**Record format and fields**

`CreepMat;id;referenceTemperature;exponent;form;primaryStiffnessTableId;primaryDampingTableId;secondaryDampingTableId;threshold;kind;coefficientA;coefficientB;coefficientC;coefficientD;coefficientE;coefficientF;coefficientG`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 3 | `exponent` | `real` | — | Power applied to the associated variable in the stated relation. |
| 4 | `form` | `text` | — | Selects the form for CreepMat. |
| 5 | `primaryStiffnessTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 6 | `primaryDampingTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 7 | `secondaryDampingTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 8 | `threshold` | `real` | — | Value at which the selected test changes state. |
| 9 | `kind` | `integer` | 0 | Selects the kind for CreepMat. |
| 10 | `coefficientA` | `real` | — | Coefficient A in the CreepMat relation. |
| 11 | `coefficientB` | `real` | — | Coefficient B in the CreepMat relation. |
| 12 | `coefficientC` | `real` | — | Coefficient C in the CreepMat relation. |
| 13 | `coefficientD` | `real` | — | Coefficient D in the CreepMat relation. |
| 14 | `coefficientE` | `real` | — | Coefficient E in the CreepMat relation. |
| 15 | `coefficientF` | `real` | — | Coefficient F in the CreepMat relation. |
| 16 | `coefficientG` | `real` | — | Coefficient G in the CreepMat relation. |

Accepted words: `CreepLaw`, `Table`.

**Example record**

~~~text
CreepMat;1;;;CreepLaw;;;;;112;1.E-9;2.;1.E-4;1.;1.E-9;0.01
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol106_creep_rod.oos)

Reading the example gives `id = 1`, `form = CreepLaw`, `kind = 112`, `coefficientA = 1.E-9`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.

## ElastoPlasticMat

The elasto-plastic properties of a material (it extends an [IsoMat](materials.md#isomat), [AnisoMat2D](materials.md#anisomat2d), [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear), [OrthoMat2D](materials.md#orthomat2d) or [AnisoMat3D](materials.md#anisomat3d)).

**Record format and fields**

`ElastoPlasticMat;id;form;yieldStress;stressStrainTableId;yieldCriterion;workHardening;hardeningSlope;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `form` | `text` | Slope | Selects the form for ElastoPlasticMat. |
| 3 | `yieldStress` | `real` | — | Yield stress (force per area). |
| 4 | `stressStrainTableId` | `integer` | 0 | Identifier addressing stress or multi dimensional table data. |
| 5 | `yieldCriterion` | `text` | VonMises | Rule for determining when a stress state reaches yield. |
| 6 | `workHardening` | `text` | IsotropicHardening | Change in strength associated with accumulated plastic deformation. |
| 7 | `hardeningSlope` | `real` | 0.0 | Slope of the material hardening curve. |

**Keyed sections in `groups`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `RateEffect`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `groupOption` | `text` | Table | Selects the group option for rateDependence. |
| 2 | `strainRateTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 3 | `hardeningOrRateCoefficient` | `real` | 1.0 | Coefficient in the relation for hardening or rate. |
| 4 | `cowperExponent` | `real` | 1.0 | Power in the law for cowper. |

**Section `AnisotropicYield`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `anisotropyRatio11` | `real` | 1.0 | Relative measure of anisotropy. |
| 2 | `anisotropyRatio22` | `real` | 1.0 | Relative measure of anisotropy. |
| 3 | `anisotropyRatio33` | `real` | 1.0 | Relative measure of anisotropy. |
| 4 | `anisotropyRatio12` | `real` | 1.0 | Relative measure of anisotropy. |
| 5 | `anisotropyRatio23` | `real` | 1.0 | Relative measure of anisotropy. |
| 6 | `anisotropyRatio31` | `real` | 1.0 | Relative measure of anisotropy. |

**Section `PressureDependence`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `groupOption` | `text` | Linear | Selects the group option for pressureDependence. |
| 2 | `mohrCoulombAlpha` | `real` | — | The parameter alpha of the linear model. |
| 3 | `mohrCoulombBeta` | `real` | — | The parameter beta of the parabolic model. |

**Section `ChabocheHardening`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `chabocheYieldStress` | `real` | 0.0 | Chaboche yield stress (force per area). |
| 2 | `saturatedIsotropicHardening` | `real` | 0.0 | Limiting isotropic hardening reached under continued inelastic straining. |
| 3 | `hardeningCoefficient` | `real` | 0.0 | Coefficient in the relation for hardening. |
| 4 | `hardeningOrRateCoefficient` | `real` | 0.0 | Coefficient in the relation for hardening or rate. |
| 5 | `kinematicRecallRate` | `real` | 0.0 | Rate controlling recovery of the kinematic hardening contribution. |
| 6 | `viscousCoefficient` | `real` | 0.0 | Coefficient in the relation for viscous. |
| 7 | `hardeningOrViscousExponent` | `real` | 0.0 | Power in the law for hardening or viscous. |
| 8 | `memoryHardeningLimit` | `real` | 0.0 | Bound on the retained hardening history in the constitutive law. |
| 9 | `memoryHardeningCoefficient` | `real` | 0.0 | Coefficient in the relation for memory hardening. |
| 10 | `memoryEvolutionFactor` | `real` | 0.0 | Multiplier for memory evolution. |

**Section `JohnsonCookHardening`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `johnsonCookYieldStress` | `real` | 0.0 | Johnson cook yield stress (force per area). |
| 2 | `hardeningCoefficient` | `real` | 0.0 | Coefficient in the relation for hardening. |
| 3 | `hardeningOrViscousExponent` | `real` | 0.0 | Power in the law for hardening or viscous. |
| 4 | `hardeningOrRateCoefficient` | `real` | 0.0 | Coefficient in the relation for hardening or rate. |
| 5 | `thermalSofteningExponent` | `real` | 0.0 | Power in the law for thermal softening. |
| 6 | `meltTemperature` | `real` | 0.0 | Temperature at which the material reaches its melting state. |
| 7 | `roomTemperature` | `real` | 0.0 | Ambient reference temperature of the material. |
| 8 | `referenceStrainRate` | `real` | 0.0 | Rate against which the current strain rate is compared (inverse time). |

**Section `ImplicitCreep`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `creepEquivalentStress` | `real` | — | Creep equivalent stress (force per area). |

Accepted words: `AnisotropicYield`, `BarlatYield`, `ChabocheHardening`, `CombinedHardening`, `CowperSymonds`, `Hill`, `ImplicitCreep`, `IsotropicHardening`, `JohnsonCookHardening`, `KinematicHardening`, `Linear`, `LinearMohrCoulomb`, `Parabolic`, `ParabolicMohrCoulomb`, `PerfectPlasticity`, `PressureDependence`, `RateEffect`, `Slope`, `Table`, `VonMises`.

**Example record**

~~~text
ElastoPlasticMat;2;Slope;250.;;VonMises;CombinedHardening;2.E+3
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 2`, `form = Slope`, `yieldStress = 250.`, `yieldCriterion = VonMises`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 2`.

## ElastoPlasticMatTemperature

The temperature dependence of the properties of an [ElastoPlasticMat](materials.md#elastoplasticmat).

**Record format and fields**

`ElastoPlasticMatTemperature;id;yieldStressTableId;stressStrainCurvesTableId;hardeningSlopeTableId;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `yieldStressTableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `stressStrainCurvesTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 4 | `hardeningSlopeTableId` | `integer` | 0 | Identifier addressing material table data. |

**Keyed sections in `groups`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `ChabocheHardening`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `chabocheYieldStressTableId` | `integer` | 0 | Table supplying the variation of chaboche yield stress. |
| 2 | `saturatedIsotropicHardeningTableId` | `integer` | 0 | Table supplying the variation of saturated isotropic hardening. |
| 3 | `isotropicHardeningRateTableId` | `integer` | 0 | Table supplying the variation of isotropic hardening rate. |
| 4 | `kinematicHardeningModulusTableId` | `integer` | 0 | Table supplying the variation of kinematic hardening modulus. |
| 5 | `kinematicRecallRateTableId` | `integer` | 0 | Table supplying the variation of kinematic recall rate. |
| 6 | `viscousCoefficientTableId` | `integer` | 0 | Table supplying the variation of viscous coefficient. |
| 7 | `viscousExponentTableId` | `integer` | 0 | Table supplying the variation of viscous exponent. |
| 8 | `memoryHardeningLimitTableId` | `integer` | 0 | Table supplying the variation of memory hardening limit. |
| 9 | `memoryHardeningCoefficientTableId` | `integer` | 0 | Table supplying the variation of memory hardening coefficient. |
| 10 | `memoryEvolutionFactorTableId` | `integer` | 0 | Table supplying the variation of memory evolution factor. |

Accepted words: `ChabocheHardening`.

**Example record**

~~~text
ElastoPlasticMatTemperature;1;;13
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 1`, `stressStrainCurvesTableId = 13`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.
- [TableStressTemperature](tables.md#tablestresstemperature) via `stressStrainCurvesTableId = 13`.

## EulerMat

A general constitutive model for an Eulerian material: an equation of state, a shear model, a yield model, a failure model and a spall model.

**Record format and fields**

`EulerMat;id;density;equationOfStateId;shearModelId;yieldModelId;failureModelId;spallModelId;linearBulkViscosity;quadraticBulkViscosity;bulkViscosityKind`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 3 | `equationOfStateId` | `integer` | Required | Identifier selecting the equation of state record or set. |
| 4 | `shearModelId` | `integer` | 0 | Identifier selecting the shear model record or set. |
| 5 | `yieldModelId` | `integer` | 0 | Identifier selecting the yield model record or set. |
| 6 | `failureModelId` | `integer` | 0 | Identifier selecting the failure model record or set. |
| 7 | `spallModelId` | `integer` | 0 | Identifier selecting the spall model record or set. |
| 8 | `linearBulkViscosity` | `real` | 0.0 | Coefficient of the linear artificial bulk-viscosity term. |
| 9 | `quadraticBulkViscosity` | `real` | 1.0 | Coefficient of the quadratic artificial bulk-viscosity term. |
| 10 | `bulkViscosityKind` | `text` | — | Selects the bulk viscosity kind for EulerMat. |

Accepted words: `Constant`, `Element`, `ExternalExplicitProgram`, `ExternalExplicitSolver`, `Table`.

**Example record**

~~~text
EulerMat;12;1.5E-9;2;2;2;2
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 12`, `density = 1.5E-9`, `equationOfStateId = 2`, `shearModelId = 2`.

## FabricMat

A bi-directional woven fabric material for shell elements, a fabric with an optional coating.

**Record format and fields**

`FabricMat;id;density;coatingYoungsModulus;coatingPoissonRatio;coatingShearModulus;coatingDamping;coatingCompressionScale;coatingThicknessPercent;warpModulusLinear;warpModulusQuadratic;warpAngle;warpDirectionX;warpDirectionY;warpDirectionZ;weftModulusLinear;weftModulusQuadratic;weftAngle;weftDirectionX;weftDirectionY;weftDirectionZ;shearFriction;shearModulus12;fiberDamping;fiberCompressionScale;lockAngle1;lockAngle2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 3 | `coatingYoungsModulus` | `real` | — | Coating youngs modulus (force per area). |
| 4 | `coatingPoissonRatio` | `real` | — | Relative measure of coating poisson. |
| 5 | `coatingShearModulus` | `real` | — | Coating shear modulus (force per area). |
| 6 | `coatingDamping` | `real` | 0.1 | Dissipative response assigned to the coating. |
| 7 | `coatingCompressionScale` | `real` | 1.0 | Multiplier applied to the coating response in compression. |
| 8 | `coatingThicknessPercent` | `real` | 0.0 | Coating thickness expressed as a percentage of the reference thickness. |
| 9 | `warpModulusLinear` | `real` | — | Linear tensile response coefficient along the fabric warp. |
| 10 | `warpModulusQuadratic` | `real` | 0.0 | Quadratic tensile response coefficient along the fabric warp. |
| 11 | `warpAngle` | `real` | — | Orientation angle of the fabric warp direction. |
| 12 | `warpDirectionX` | `real` | 1.0 | Component X of the warp direction vector. |
| 13 | `warpDirectionY` | `real` | 0.0 | Component Y of the warp direction vector. |
| 14 | `warpDirectionZ` | `real` | 0.0 | Component Z of the warp direction vector. |
| 15 | `weftModulusLinear` | `real` | — | Linear tensile response coefficient along the fabric weft. |
| 16 | `weftModulusQuadratic` | `real` | 0.0 | Quadratic tensile response coefficient along the fabric weft. |
| 17 | `weftAngle` | `real` | — | Orientation angle of the fabric weft direction. |
| 18 | `weftDirectionX` | `real` | 0.0 | Component X of the weft direction vector. |
| 19 | `weftDirectionY` | `real` | 1.0 | Component Y of the weft direction vector. |
| 20 | `weftDirectionZ` | `real` | 0.0 | Component Z of the weft direction vector. |
| 21 | `shearFriction` | `real` | 0.0 | Coefficient controlling frictional resistance in shear. |
| 22 | `shearModulus12` | `real` | — | Elastic shear stress divided by engineering shear strain (force per area). Entry 12. |
| 23 | `fiberDamping` | `real` | 0.1 | Dissipation attributed to the fibre reinforcement. |
| 24 | `fiberCompressionScale` | `real` | 1.0 | Scale setting for the compression response of the fiber constituent. |
| 25 | `lockAngle1` | `real` | 10.0 | Fabric locking angle for shear branch or entry 1. |
| 26 | `lockAngle2` | `real` | 15.0 | Fabric locking angle for shear branch or entry 2. |

**Example record**

~~~text
FabricMat;2;8.5E-10;;;;;;;216.;;;1.;0.;0.;216.;;;0.;1.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol700_bulk_viscosity_fabric_rigid.oos)

Reading the example gives `id = 2`, `density = 8.5E-10`, `warpModulusLinear = 216.`, `warpDirectionX = 1.`.

## FailureMat

The failure model of the linear elastic material with the same ID.

**Record format and fields**

`FailureMat;id;degradationKind;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `degradationKind` | `integer` | 0 | Selects the degradation kind for FailureMat. |

**Keyed sections in `lines`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Criterion`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `criterion` | `integer` | — | 1 maximum stress, 2 maximum strain, 3 Hill, 4 Hoffman, 5 Tsai-Wu, 7 Hashin, 8 Puck, 10. |
| 2 | `criterionValue1` | `real` | — | Value in position 1 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 3 | `criterionValue2` | `real` | — | Value in position 2 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 4 | `criterionValue3` | `real` | — | Value in position 3 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 5 | `criterionValue4` | `real` | — | Value in position 4 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 6 | `criterionValue5` | `real` | — | Value in position 5 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 7 | `criterionValue6` | `real` | — | Value in position 6 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 8 | `criterionValue7` | `real` | — | Value in position 7 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 9 | `criterionValue8` | `real` | — | Value in position 8 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 10 | `criterionValue9` | `real` | — | Value in position 9 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 11 | `failureIndexScale` | `real` | — | Multiplier applied to the calculated failure index. |
| 12 | `criterionValue10` | `real` | — | Value in position 10 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 13 | `criterionValue11` | `any` | — | Value in position 11 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 14 | `criterionValue12` | `any` | — | Value in position 12 of the selected material failure criterion. Its physical interpretation depends on the criterion. |
| 15 | `strainLimit1` | `any` | — | Limiting strain for material component or criterion entry 1. |
| 16 | `strainLimit2` | `real` | — | Limiting strain for material component or criterion entry 2. |
| 17 | `strainLimit3` | `real` | — | Limiting strain for material component or criterion entry 3. |
| 18 | `strainLimit4` | `real` | — | Limiting strain for material component or criterion entry 4. |
| 19 | `strainLimit5` | `real` | — | Limiting strain for material component or criterion entry 5. |
| 20 | `strainLimit6` | `real` | — | Limiting strain for material component or criterion entry 6. |
| 21 | `strainLimit7` | `real` | — | Limiting strain for material component or criterion entry 7. |
| 22 | `strainLimit8` | `real` | — | Limiting strain for material component or criterion entry 8. |
| 23 | `strainLimit9` | `real` | — | Limiting strain for material component or criterion entry 9. |

**Section `ProgressiveFailure`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `residualStiffness` | `real` | — | Stiffness retained after degradation according to the material model. |
| 2 | `degradationParameter2` | `real` | — | Parameter 2 of the degradation parameter relation for this material. |
| 3 | `degradationParameter3` | `real` | — | Parameter 3 of the degradation parameter relation for this material. |
| 4 | `degradationParameter4` | `real` | — | Parameter 4 of the degradation parameter relation for this material. |
| 5 | `degradationParameter5` | `real` | — | Parameter 5 of the degradation parameter relation for this material. |

*Note*: criterionValue11, criterionValue12 and strainLimit1 hold a word for the criteria that take one there (102: the failure method; 105: the cap type and the iteration).

Accepted words: `Continue`, `Criterion`, `Discard`, `FullIterations`, `ProgressiveFailure`, `RockModel`, `SoilModel`, `VectorizedIterations`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `criteria` — the card has from one to three criteria.
- `criterionValue` — the values of a criterion must be finite numbers.

**Example record**

~~~text
FailureMat;2;0;Criterion;1;1500.;1200.;50.;200.;50.;200.;70.;70.;70.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol101_layered_solid_cord3g.oos)

Reading the example gives `id = 2`, `degradationKind = 0`.

**Referenced records in this example**

- [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) via `id = 2`.

## FailureMatTemperature

The variation (with the temperature) of the failure properties of the [FailureMat](materials.md#failuremat) with the same ID.

**Record format and fields**

`FailureMatTemperature;id;bondShearAllowableTableId;<blocks>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bondShearAllowableTableId` | `integer` | 0 | Table supplying the variation of bond shear allowable. |

**Repeated group `blocks`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `integer` | — | Selects the kind for blocks. |
| 2 | `criterion` | `integer` | — | The criterion of the FailureMat (for reference only). |
| 3 | `failurePropertyTableId1` | `integer` | — | Table supplying the variation of failure property. |
| 4 | `failurePropertyTableId2` | `integer` | — | Table supplying the variation of failure property. |
| 5 | `failurePropertyTableId3` | `integer` | — | Table supplying the variation of failure property. |
| 6 | `failurePropertyTableId4` | `integer` | — | Table supplying the variation of failure property. |
| 7 | `failurePropertyTableId5` | `integer` | — | Table supplying the variation of failure property. |
| 8 | `failurePropertyTableId6` | `integer` | — | Table supplying the variation of failure property. |
| 9 | `failurePropertyTableId7` | `integer` | — | Table supplying the variation of failure property. |
| 10 | `failurePropertyTableId8` | `integer` | — | Table supplying the variation of failure property. |
| 11 | `failurePropertyTableId9` | `integer` | — | Table supplying the variation of failure property. |
| 12 | `failurePropertyTableId10` | `integer` | — | Table supplying the variation of failure property. |
| 13 | `failurePropertyTableId11` | `integer` | — | Table supplying the variation of failure property. |
| 14 | `failurePropertyTableId12` | `integer` | — | Table supplying the variation of failure property. |
| 15 | `failurePropertyTableId13` | `integer` | — | Table supplying the variation of failure property. |
| 16 | `failurePropertyTableId14` | `integer` | — | Table supplying the variation of failure property. |
| 17 | `failurePropertyTableId15` | `integer` | — | Table supplying the variation of failure property. |
| 18 | `failurePropertyTableId16` | `integer` | — | Table supplying the variation of failure property. |
| 19 | `failurePropertyTableId17` | `integer` | — | Table supplying the variation of failure property. |
| 20 | `failurePropertyTableId18` | `integer` | — | Table supplying the variation of failure property. |
| 21 | `failurePropertyTableId19` | `integer` | — | Table supplying the variation of failure property. |
| 22 | `failurePropertyTableId20` | `integer` | — | Table supplying the variation of failure property. |
| 23 | `failurePropertyTableId21` | `integer` | — | Table supplying the variation of failure property. |
| 24 | `failurePropertyTableId22` | `integer` | — | Table supplying the variation of failure property. |

**Example record**

~~~text
FailureMatTemperature;10;;12;1;103
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 10`.

**Referenced records in this example**

- [OrthoMat2D](materials.md#orthomat2d) via `id = 10`.

## FatigueMat

The fatigue properties of an isotropic metal.

**Record format and fields**

`FatigueMat;id;stressUnitFactor;debugOutput;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `stressUnitFactor` | `real` | 1.0 | Multiplier for stress unit. |
| 3 | `debugOutput` | `integer` | 0 | Selects diagnostic output for this model or operation. |

**Keyed sections in `blocks`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Static`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `yieldStrength` | `real` | — | Stress marking the onset of yield under the selected criterion. |
| 2 | `ultimateTensileStrength` | `real` | — | Maximum tensile stress used in the material strength model. |
| 3 | `materialCode` | `integer` | — | The material code of the table (SOLs 101, 103, 112). |
| 4 | `curveKind` | `text` | — | Selects the curve kind for staticProperties. |
| 5 | `testStressRatio` | `real` | — | Relative measure of test stress. |
| 6 | `standardError` | `real` | — | Dispersion measure used by the statistical material relation. |
| 7 | `plasticPoissonRatio` | `real` | — | Relative measure of plastic poisson. |
| 8 | `areaReduction` | `real` | — | The percentage reduction in area, on the second line. |

**Section `StressLifeMethod`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `snCurveTerm1` | `real` | — | Parameter 1 of the sn curve term relation for this material. |
| 2 | `snCurveTerm2` | `real` | — | Parameter 2 of the sn curve term relation for this material. |
| 3 | `snCurveTerm3` | `real` | — | Parameter 3 of the sn curve term relation for this material. |
| 4 | `snCurveTerm4` | `real` | — | Parameter 4 of the sn curve term relation for this material. |
| 5 | `snCurveTerm5` | `real` | — | Parameter 5 of the sn curve term relation for this material. |
| 6 | `snCurveTerm6` | `real` | — | Parameter 6 of the sn curve term relation for this material. |
| 7 | `snCurveTerm7` | `real` | — | Parameter 7 of the sn curve term relation for this material. |
| 8 | `meanStressTerm1` | `real` | — | Parameter 1 of the mean stress term relation for this material. |
| 9 | `meanStressTerm2` | `real` | — | Parameter 2 of the mean stress term relation for this material. |
| 10 | `meanStressTerm3` | `real` | — | Parameter 3 of the mean stress term relation for this material. |
| 11 | `meanStressTerm4` | `real` | — | Parameter 4 of the mean stress term relation for this material. |
| 12 | `meanStressTerm5` | `real` | — | Parameter 5 of the mean stress term relation for this material. |
| 13 | `meanStressTerm6` | `real` | — | Parameter 6 of the mean stress term relation for this material. |
| 14 | `meanStressTerm7` | `real` | — | Parameter 7 of the mean stress term relation for this material. |
| 15 | `spotWeldTerm1` | `real` | — | Parameter 1 of the spot weld term relation for this material. |
| 16 | `spotWeldTerm2` | `real` | — | Parameter 2 of the spot weld term relation for this material. |
| 17 | `spotWeldTerm3` | `real` | — | Parameter 3 of the spot weld term relation for this material. |
| 18 | `spotWeldTerm4` | `real` | — | Parameter 4 of the spot weld term relation for this material. |
| 19 | `spotWeldTerm5` | `real` | — | Parameter 5 of the spot weld term relation for this material. |
| 20 | `spotWeldTerm6` | `real` | — | Parameter 6 of the spot weld term relation for this material. |
| 21 | `spotWeldTerm7` | `real` | — | Parameter 7 of the spot weld term relation for this material. |
| 22 | `spotWeldTerm8` | `real` | — | Parameter 8 of the spot weld term relation for this material. |
| 23 | `spotWeldTerm9` | `real` | — | Parameter 9 of the spot weld term relation for this material. |
| 24 | `spotWeldTerm10` | `real` | — | Parameter 10 of the spot weld term relation for this material. |
| 25 | `spotWeldTerm11` | `real` | — | Parameter 11 of the spot weld term relation for this material. |
| 26 | `spotWeldTerm12` | `real` | — | Parameter 12 of the spot weld term relation for this material. |

**Section `StressLifeSegment1`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `snCurveTerm1` | `real` | — | Parameter 1 of the sn curve term relation for this material. |
| 2 | `snCurveTerm2` | `real` | — | Parameter 2 of the sn curve term relation for this material. |
| 3 | `snCurveTerm3` | `real` | — | Parameter 3 of the sn curve term relation for this material. |
| 4 | `snCurveTerm4` | `real` | — | Parameter 4 of the sn curve term relation for this material. |
| 5 | `snCurveTerm5` | `real` | — | Parameter 5 of the sn curve term relation for this material. |
| 6 | `snCurveTerm6` | `real` | — | Parameter 6 of the sn curve term relation for this material. |
| 7 | `snCurveTerm7` | `real` | — | Parameter 7 of the sn curve term relation for this material. |
| 8 | `meanStressTerm1` | `real` | — | Parameter 1 of the mean stress term relation for this material. |
| 9 | `meanStressTerm2` | `real` | — | Parameter 2 of the mean stress term relation for this material. |
| 10 | `meanStressTerm3` | `real` | — | Parameter 3 of the mean stress term relation for this material. |
| 11 | `meanStressTerm4` | `real` | — | Parameter 4 of the mean stress term relation for this material. |
| 12 | `meanStressTerm5` | `real` | — | Parameter 5 of the mean stress term relation for this material. |
| 13 | `meanStressTerm6` | `real` | — | Parameter 6 of the mean stress term relation for this material. |
| 14 | `meanStressTerm7` | `real` | — | Parameter 7 of the mean stress term relation for this material. |
| 15 | `spotWeldTerm1` | `real` | — | Parameter 1 of the spot weld term relation for this material. |
| 16 | `spotWeldTerm2` | `real` | — | Parameter 2 of the spot weld term relation for this material. |
| 17 | `spotWeldTerm3` | `real` | — | Parameter 3 of the spot weld term relation for this material. |
| 18 | `spotWeldTerm4` | `real` | — | Parameter 4 of the spot weld term relation for this material. |
| 19 | `spotWeldTerm5` | `real` | — | Parameter 5 of the spot weld term relation for this material. |
| 20 | `spotWeldTerm6` | `real` | — | Parameter 6 of the spot weld term relation for this material. |
| 21 | `spotWeldTerm7` | `real` | — | Parameter 7 of the spot weld term relation for this material. |
| 22 | `spotWeldTerm8` | `real` | — | Parameter 8 of the spot weld term relation for this material. |
| 23 | `spotWeldTerm9` | `real` | — | Parameter 9 of the spot weld term relation for this material. |
| 24 | `spotWeldTerm10` | `real` | — | Parameter 10 of the spot weld term relation for this material. |
| 25 | `spotWeldTerm11` | `real` | — | Parameter 11 of the spot weld term relation for this material. |
| 26 | `spotWeldTerm12` | `real` | — | Parameter 12 of the spot weld term relation for this material. |

**Section `StressLifeSegment2`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `snCurveTerm1` | `real` | — | Parameter 1 of the sn curve term relation for this material. |
| 2 | `snCurveTerm2` | `real` | — | Parameter 2 of the sn curve term relation for this material. |
| 3 | `snCurveTerm3` | `real` | — | Parameter 3 of the sn curve term relation for this material. |
| 4 | `snCurveTerm4` | `real` | — | Parameter 4 of the sn curve term relation for this material. |
| 5 | `snCurveTerm5` | `real` | — | Parameter 5 of the sn curve term relation for this material. |
| 6 | `snCurveTerm6` | `real` | — | Parameter 6 of the sn curve term relation for this material. |
| 7 | `snCurveTerm7` | `real` | — | Parameter 7 of the sn curve term relation for this material. |
| 8 | `meanStressTerm1` | `real` | — | Parameter 1 of the mean stress term relation for this material. |
| 9 | `meanStressTerm2` | `real` | — | Parameter 2 of the mean stress term relation for this material. |
| 10 | `meanStressTerm3` | `real` | — | Parameter 3 of the mean stress term relation for this material. |
| 11 | `meanStressTerm4` | `real` | — | Parameter 4 of the mean stress term relation for this material. |
| 12 | `meanStressTerm5` | `real` | — | Parameter 5 of the mean stress term relation for this material. |
| 13 | `meanStressTerm6` | `real` | — | Parameter 6 of the mean stress term relation for this material. |
| 14 | `meanStressTerm7` | `real` | — | Parameter 7 of the mean stress term relation for this material. |
| 15 | `spotWeldTerm1` | `real` | — | Parameter 1 of the spot weld term relation for this material. |
| 16 | `spotWeldTerm2` | `real` | — | Parameter 2 of the spot weld term relation for this material. |
| 17 | `spotWeldTerm3` | `real` | — | Parameter 3 of the spot weld term relation for this material. |
| 18 | `spotWeldTerm4` | `real` | — | Parameter 4 of the spot weld term relation for this material. |
| 19 | `spotWeldTerm5` | `real` | — | Parameter 5 of the spot weld term relation for this material. |
| 20 | `spotWeldTerm6` | `real` | — | Parameter 6 of the spot weld term relation for this material. |
| 21 | `spotWeldTerm7` | `real` | — | Parameter 7 of the spot weld term relation for this material. |
| 22 | `spotWeldTerm8` | `real` | — | Parameter 8 of the spot weld term relation for this material. |
| 23 | `spotWeldTerm9` | `real` | — | Parameter 9 of the spot weld term relation for this material. |
| 24 | `spotWeldTerm10` | `real` | — | Parameter 10 of the spot weld term relation for this material. |
| 25 | `spotWeldTerm11` | `real` | — | Parameter 11 of the spot weld term relation for this material. |
| 26 | `spotWeldTerm12` | `real` | — | Parameter 12 of the spot weld term relation for this material. |

**Section `StressLifeBranch1`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `snCurveTerm1` | `real` | — | Parameter 1 of the sn curve term relation for this material. |
| 2 | `snCurveTerm2` | `real` | — | Parameter 2 of the sn curve term relation for this material. |
| 3 | `snCurveTerm3` | `real` | — | Parameter 3 of the sn curve term relation for this material. |
| 4 | `snCurveTerm4` | `real` | — | Parameter 4 of the sn curve term relation for this material. |
| 5 | `snCurveTerm5` | `real` | — | Parameter 5 of the sn curve term relation for this material. |
| 6 | `snCurveTerm6` | `real` | — | Parameter 6 of the sn curve term relation for this material. |
| 7 | `snCurveTerm7` | `real` | — | Parameter 7 of the sn curve term relation for this material. |
| 8 | `meanStressTerm1` | `real` | — | Parameter 1 of the mean stress term relation for this material. |
| 9 | `meanStressTerm2` | `real` | — | Parameter 2 of the mean stress term relation for this material. |
| 10 | `meanStressTerm3` | `real` | — | Parameter 3 of the mean stress term relation for this material. |
| 11 | `meanStressTerm4` | `real` | — | Parameter 4 of the mean stress term relation for this material. |
| 12 | `meanStressTerm5` | `real` | — | Parameter 5 of the mean stress term relation for this material. |
| 13 | `meanStressTerm6` | `real` | — | Parameter 6 of the mean stress term relation for this material. |
| 14 | `meanStressTerm7` | `real` | — | Parameter 7 of the mean stress term relation for this material. |
| 15 | `spotWeldTerm1` | `real` | — | Parameter 1 of the spot weld term relation for this material. |
| 16 | `spotWeldTerm2` | `real` | — | Parameter 2 of the spot weld term relation for this material. |
| 17 | `spotWeldTerm3` | `real` | — | Parameter 3 of the spot weld term relation for this material. |
| 18 | `spotWeldTerm4` | `real` | — | Parameter 4 of the spot weld term relation for this material. |
| 19 | `spotWeldTerm5` | `real` | — | Parameter 5 of the spot weld term relation for this material. |
| 20 | `spotWeldTerm6` | `real` | — | Parameter 6 of the spot weld term relation for this material. |
| 21 | `spotWeldTerm7` | `real` | — | Parameter 7 of the spot weld term relation for this material. |
| 22 | `spotWeldTerm8` | `real` | — | Parameter 8 of the spot weld term relation for this material. |
| 23 | `spotWeldTerm9` | `real` | — | Parameter 9 of the spot weld term relation for this material. |
| 24 | `spotWeldTerm10` | `real` | — | Parameter 10 of the spot weld term relation for this material. |
| 25 | `spotWeldTerm11` | `real` | — | Parameter 11 of the spot weld term relation for this material. |
| 26 | `spotWeldTerm12` | `real` | — | Parameter 12 of the spot weld term relation for this material. |

**Section `StressLifeBranch0`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `snCurveTerm1` | `real` | — | Parameter 1 of the sn curve term relation for this material. |
| 2 | `snCurveTerm2` | `real` | — | Parameter 2 of the sn curve term relation for this material. |
| 3 | `snCurveTerm3` | `real` | — | Parameter 3 of the sn curve term relation for this material. |
| 4 | `snCurveTerm4` | `real` | — | Parameter 4 of the sn curve term relation for this material. |
| 5 | `snCurveTerm5` | `real` | — | Parameter 5 of the sn curve term relation for this material. |
| 6 | `snCurveTerm6` | `real` | — | Parameter 6 of the sn curve term relation for this material. |
| 7 | `snCurveTerm7` | `real` | — | Parameter 7 of the sn curve term relation for this material. |
| 8 | `meanStressTerm1` | `real` | — | Parameter 1 of the mean stress term relation for this material. |
| 9 | `meanStressTerm2` | `real` | — | Parameter 2 of the mean stress term relation for this material. |
| 10 | `meanStressTerm3` | `real` | — | Parameter 3 of the mean stress term relation for this material. |
| 11 | `meanStressTerm4` | `real` | — | Parameter 4 of the mean stress term relation for this material. |
| 12 | `meanStressTerm5` | `real` | — | Parameter 5 of the mean stress term relation for this material. |
| 13 | `meanStressTerm6` | `real` | — | Parameter 6 of the mean stress term relation for this material. |
| 14 | `meanStressTerm7` | `real` | — | Parameter 7 of the mean stress term relation for this material. |
| 15 | `spotWeldTerm1` | `real` | — | Parameter 1 of the spot weld term relation for this material. |
| 16 | `spotWeldTerm2` | `real` | — | Parameter 2 of the spot weld term relation for this material. |
| 17 | `spotWeldTerm3` | `real` | — | Parameter 3 of the spot weld term relation for this material. |
| 18 | `spotWeldTerm4` | `real` | — | Parameter 4 of the spot weld term relation for this material. |
| 19 | `spotWeldTerm5` | `real` | — | Parameter 5 of the spot weld term relation for this material. |
| 20 | `spotWeldTerm6` | `real` | — | Parameter 6 of the spot weld term relation for this material. |
| 21 | `spotWeldTerm7` | `real` | — | Parameter 7 of the spot weld term relation for this material. |
| 22 | `spotWeldTerm8` | `real` | — | Parameter 8 of the spot weld term relation for this material. |
| 23 | `spotWeldTerm9` | `real` | — | Parameter 9 of the spot weld term relation for this material. |
| 24 | `spotWeldTerm10` | `real` | — | Parameter 10 of the spot weld term relation for this material. |
| 25 | `spotWeldTerm11` | `real` | — | Parameter 11 of the spot weld term relation for this material. |
| 26 | `spotWeldTerm12` | `real` | — | Parameter 12 of the spot weld term relation for this material. |

**Section `Table`**

**Repeated group `tables`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `tableKeyValue` | `real` | — | Value selecting the corresponding set of tabulated material data. |
| 2 | `tableId` | `integer` | — | Identifier of the tabulated function to evaluate. |

**Section `MetallicHandbookData`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `handbookCoefficient1` | `real` | — | Coefficient in the relation for handbook. |
| 2 | `handbookCoefficient2` | `real` | — | Coefficient in the relation for handbook. |
| 3 | `handbookCoefficient3` | `real` | — | Coefficient in the relation for handbook. |
| 4 | `handbookCoefficient4` | `real` | — | Coefficient in the relation for handbook. |

**Section `StrainLifeMethod`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `strainLifeTerm1` | `real` | — | Parameter 1 of the strain life term relation for this material. |
| 2 | `strainLifeTerm2` | `real` | — | Parameter 2 of the strain life term relation for this material. |
| 3 | `strainLifeTerm3` | `real` | — | Parameter 3 of the strain life term relation for this material. |
| 4 | `strainLifeTerm4` | `real` | — | Parameter 4 of the strain life term relation for this material. |
| 5 | `strainLifeTerm5` | `real` | — | Parameter 5 of the strain life term relation for this material. |
| 6 | `strainLifeTerm6` | `real` | — | Parameter 6 of the strain life term relation for this material. |
| 7 | `strainLifeTerm7` | `real` | — | Parameter 7 of the strain life term relation for this material. |
| 8 | `strainLifeError1` | `real` | — | Parameter 1 of the strain life error relation for this material. |
| 9 | `strainLifeError2` | `real` | — | Parameter 2 of the strain life error relation for this material. |
| 10 | `strainLifeError3` | `real` | — | Parameter 3 of the strain life error relation for this material. |
| 11 | `strainLifeError4` | `real` | — | Parameter 4 of the strain life error relation for this material. |
| 12 | `tolerance` | `real` | — | Allowable change or residual for the selected numerical check. |

**Section `MatIds`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `youngsModulus` | `real` | — | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). |
| 2 | `poissonRatio` | `real` | — | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). |

**Section with an empty key**

**Repeated group `matIdList`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `matIds` | `any` | — | Identifier addressing material data. |

Accepted words: `Amplitude`, `AmplitudeConstantLife`, `AmplitudeMeanStress`, `AmplitudeStressRatio`, `ConstantLife`, `MatIds`, `MeanStress`, `MetallicHandbookData`, `Range`, `Static`, `StrainLifeMethod`, `StressLifeBranch0`, `StressLifeBranch1`, `StressLifeMethod`, `StressLifeSegment1`, `StressLifeSegment2`, `StressRatio`, `Table`, `Through`.

**Example record**

~~~text
FatigueMat;1;;;Static;430.;682.;;;;;;;StressLifeMethod;3095.;-0.1339;1.E+8
~~~

[Model containing this record](../../../validation/models/constraints_sets_rigid/fatigue_property_sets.oos)

Reading the example gives `id = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.

## FluidMat

The material of a fluid element in a coupled fluid-structure analysis.

**Record format and fields**

`FluidMat;id;bulkModulus;density;soundSpeed;structuralDamping;normalizedAdmittance`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 3 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 4 | `soundSpeed` | `real` | — | Sound speed (length per time). |
| 5 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 6 | `normalizedAdmittance` | `real` | — | Admittance expressed relative to the reference acoustic admittance. |

**Example record**

~~~text
FluidMat;2;0.142;1.2E-12;;0.01
~~~

[Model containing this record](../../../validation/models/acoustics/plate_cavity_model.oos)

Reading the example gives `id = 2`, `bulkModulus = 0.142`, `density = 1.2E-12`, `structuralDamping = 0.01`.

## FluidMatFreq

The frequency dependence of the properties of a [FluidMat](materials.md#fluidmat) (a fluid material).

**Record format and fields**

`FluidMatFreq;id;bulkModulusTableId;densityTableId;soundSpeedTableId;structuralDampingTableId;normalizedAdmittanceTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `bulkModulusTableId` | `integer` | 0 | Table supplying the variation of bulk modulus. |
| 3 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 4 | `soundSpeedTableId` | `integer` | 0 | Table supplying the variation of sound speed. |
| 5 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 6 | `normalizedAdmittanceTableId` | `integer` | 0 | Table supplying the variation of normalized admittance. |

**Example record**

~~~text
FluidMatFreq;2;34;;;35
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 2`, `bulkModulusTableId = 34`, `structuralDampingTableId = 35`.

## GasketMat

Defines the nonlinear through-thickness compression response of a gasket and references the isotropic material supplying its membrane behavior.

**Record format and fields**

`GasketMat;id;membraneMatId;behaviorKind;loadingTableId;unloadingTableId1;unloadingTableId2;unloadingTableId3;unloadingTableId4;unloadingTableId5;unloadingTableId6;unloadingTableId7;unloadingTableId8;unloadingTableId9;unloadingTableId10;yieldPressure;tensileModulus;transverseShearModulus;initialGap;yieldPressureTableId;tensileModulusTableId;transverseShearModulusTableId;initialGapTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `membraneMatId` | `integer` | Required | Identifier addressing material data. |
| 3 | `behaviorKind` | `integer` | 0 | Selects the behavior kind for GasketMat. |
| 4 | `loadingTableId` | `integer` | Required | Identifier addressing stress table data. |
| 5 | `unloadingTableId1` | `integer` | — | Table supplying the variation of unloading. |
| 6 | `unloadingTableId2` | `integer` | — | Table supplying the variation of unloading. |
| 7 | `unloadingTableId3` | `integer` | — | Table supplying the variation of unloading. |
| 8 | `unloadingTableId4` | `integer` | — | Table supplying the variation of unloading. |
| 9 | `unloadingTableId5` | `integer` | — | Table supplying the variation of unloading. |
| 10 | `unloadingTableId6` | `integer` | — | Table supplying the variation of unloading. |
| 11 | `unloadingTableId7` | `integer` | — | Table supplying the variation of unloading. |
| 12 | `unloadingTableId8` | `integer` | — | Table supplying the variation of unloading. |
| 13 | `unloadingTableId9` | `integer` | — | Table supplying the variation of unloading. |
| 14 | `unloadingTableId10` | `integer` | — | Table supplying the variation of unloading. |
| 15 | `yieldPressure` | `real` | Required | Yield pressure (force per area). |
| 16 | `tensileModulus` | `real` | Required | Tensile modulus (force per area). |
| 17 | `transverseShearModulus` | `real` | Required | Transverse shear modulus (force per area). |
| 18 | `initialGap` | `real` | 0.0 | The initial gap. |
| 19 | `yieldPressureTableId` | `integer` | 0 | Table supplying the variation of yield pressure. |
| 20 | `tensileModulusTableId` | `integer` | 0 | Table supplying the variation of tensile modulus. |
| 21 | `transverseShearModulusTableId` | `integer` | 0 | Table supplying the variation of transverse shear modulus. |
| 22 | `initialGapTableId` | `integer` | 0 | Table supplying the variation of initial gap. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `yieldPressureTableId` — a table ID must not be negative.

**Example record**

~~~text
GasketMat;40;41;0;401;402;;;;;;;;;;30.;1.E+3;50.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 40`, `membraneMatId = 41`, `behaviorKind = 0`, `loadingTableId = 401`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `membraneMatId = 41`.
- [TableStress1](tables.md#tablestress1) via `loadingTableId = 401`.

## GasketMatTemperature

The temperature dependence of the properties of a [GasketMat](materials.md#gasketmat).

**Record format and fields**

`GasketMatTemperature;id;membraneYoungsModulusTableId;membranePoissonRatioTableId;membraneDensityTableId;loadingTableId;unloadingTableId1;unloadingTableId2;unloadingTableId3;unloadingTableId4;unloadingTableId5;unloadingTableId6;unloadingTableId7;unloadingTableId8;unloadingTableId9;unloadingTableId10;yieldPressureTableId;tensileModulusTableId;transverseShearModulusTableId;initialGapTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `membraneYoungsModulusTableId` | `integer` | 0 | Table supplying the variation of membrane youngs modulus. |
| 3 | `membranePoissonRatioTableId` | `integer` | 0 | Table supplying the variation of membrane poisson ratio. |
| 4 | `membraneDensityTableId` | `integer` | 0 | Table supplying the variation of membrane density. |
| 5 | `loadingTableId` | `integer` | 0 | Table supplying the variation of loading. |
| 6 | `unloadingTableId1` | `integer` | — | Table supplying the variation of unloading. |
| 7 | `unloadingTableId2` | `integer` | — | Table supplying the variation of unloading. |
| 8 | `unloadingTableId3` | `integer` | — | Table supplying the variation of unloading. |
| 9 | `unloadingTableId4` | `integer` | — | Table supplying the variation of unloading. |
| 10 | `unloadingTableId5` | `integer` | — | Table supplying the variation of unloading. |
| 11 | `unloadingTableId6` | `integer` | — | Table supplying the variation of unloading. |
| 12 | `unloadingTableId7` | `integer` | — | Table supplying the variation of unloading. |
| 13 | `unloadingTableId8` | `integer` | — | Table supplying the variation of unloading. |
| 14 | `unloadingTableId9` | `integer` | — | Table supplying the variation of unloading. |
| 15 | `unloadingTableId10` | `integer` | — | Table supplying the variation of unloading. |
| 16 | `yieldPressureTableId` | `integer` | 0 | Table supplying the variation of yield pressure. |
| 17 | `tensileModulusTableId` | `integer` | 0 | Table supplying the variation of tensile modulus. |
| 18 | `transverseShearModulusTableId` | `integer` | 0 | Table supplying the variation of transverse shear modulus. |
| 19 | `initialGapTableId` | `integer` | 0 | Table supplying the variation of initial gap. |

**Example record**

~~~text
GasketMatTemperature;40;403
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 40`, `membraneYoungsModulusTableId = 403`.

**Referenced records in this example**

- [GasketMat](materials.md#gasketmat) via `id = 40`.

## HeatAnisoMatTemperature

The temperature dependent properties of a [HeatAnisoMat](thermal.md#heatanisomat) (anisotropic thermal conductivity).

**Record format and fields**

`HeatAnisoMatTemperature;id;conductivityXxTableId;conductivityXyTableId;conductivityXzTableId;conductivityYyTableId;conductivityYzTableId;conductivityZzTableId;specificHeatTableId;heatGenerationFactorTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `conductivityXxTableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `conductivityXyTableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `conductivityXzTableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `conductivityYyTableId` | `integer` | 0 | Identifier addressing material table data. |
| 6 | `conductivityYzTableId` | `integer` | 0 | Identifier addressing material table data. |
| 7 | `conductivityZzTableId` | `integer` | 0 | Identifier addressing material table data. |
| 8 | `specificHeatTableId` | `integer` | 0 | Identifier addressing material table data. |
| 9 | `heatGenerationFactorTableId` | `integer` | 0 | Identifier addressing material table data. |

**Example record**

~~~text
HeatAnisoMatTemperature;5;32
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 5`, `conductivityXxTableId = 32`.

**Referenced records in this example**

- [HeatAnisoMat](thermal.md#heatanisomat) via `id = 5`.
- [TableMaterial1](tables.md#tablematerial1) via `conductivityXxTableId = 32`.

## HeatIsoMatTemperature

The temperature dependent properties of a [HeatIsoMat](thermal.md#heatisomat) (thermal conductivity and related properties).

**Record format and fields**

`HeatIsoMatTemperature;id;conductivityTableId;specificHeatTableId;convectionCoefficientTableId;viscosityTableId;heatGenerationFactorTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `conductivityTableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `specificHeatTableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `convectionCoefficientTableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `viscosityTableId` | `integer` | 0 | Identifier addressing material table data. |
| 6 | `heatGenerationFactorTableId` | `integer` | 0 | Identifier addressing material table data. |

**Example record**

~~~text
HeatIsoMatTemperature;2;31
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 2`, `conductivityTableId = 31`.

**Referenced records in this example**

- [HeatIsoMat](thermal.md#heatisomat) via `id = 2`.
- [TableMaterial1](tables.md#tablematerial1) via `conductivityTableId = 31`.

## HyperelasticMat

A hyperelastic (rubber-like) material.

**Record format and fields**

Forms: `ogden`, `boyceOrGent`, `generalized`, `mooney`.

### HyperelasticMat: ogden

Form `ogden`, when `modelName` is `Ogden`, `Foam`.

`HyperelasticMat;id;modelName;termCount;bulkModulus;density;thermalExpansion;referenceTemperature;structuralDamping;ogdenModulus1;alphaCoefficient1;betaCoefficient1;ogdenModulus2;alphaCoefficient2;betaCoefficient2;ogdenModulus3;alphaCoefficient3;betaCoefficient3;ogdenModulus4;alphaCoefficient4;betaCoefficient4;ogdenModulus5;alphaCoefficient5;betaCoefficient5;coefficientD1;coefficientD2;coefficientD3;coefficientD4;coefficientD5`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `modelName` | `text` | MooneyRivlin | Text naming the model. |
| 3 | `termCount` | `integer` | 1 | Number of term entries. |
| 4 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 5 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 6 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 7 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 8 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 9 | `ogdenModulus1` | `real` | 0.0 | Ogden modulus 1 (force per area). |
| 10 | `alphaCoefficient1` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 11 | `betaCoefficient1` | `real` | 0.0 | Coefficient in the relation for beta. |
| 12 | `ogdenModulus2` | `real` | 0.0 | Ogden modulus 2 (force per area). |
| 13 | `alphaCoefficient2` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 14 | `betaCoefficient2` | `real` | 0.0 | Coefficient in the relation for beta. |
| 15 | `ogdenModulus3` | `real` | 0.0 | Ogden modulus 3 (force per area). |
| 16 | `alphaCoefficient3` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 17 | `betaCoefficient3` | `real` | 0.0 | Coefficient in the relation for beta. |
| 18 | `ogdenModulus4` | `real` | 0.0 | Ogden modulus 4 (force per area). |
| 19 | `alphaCoefficient4` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 20 | `betaCoefficient4` | `real` | 0.0 | Coefficient in the relation for beta. |
| 21 | `ogdenModulus5` | `real` | 0.0 | Ogden modulus 5 (force per area). |
| 22 | `alphaCoefficient5` | `real` | 0.0 | Coefficient in the relation for alpha. |
| 23 | `betaCoefficient5` | `real` | 0.0 | Coefficient in the relation for beta. |
| 24 | `coefficientD1` | `real` | 0.0 | Coefficient D1 in the HyperelasticMat relation. |
| 25 | `coefficientD2` | `real` | 0.0 | Coefficient D2 in the HyperelasticMat relation. |
| 26 | `coefficientD3` | `real` | 0.0 | Coefficient D3 in the HyperelasticMat relation. |
| 27 | `coefficientD4` | `real` | 0.0 | Coefficient D4 in the HyperelasticMat relation. |
| 28 | `coefficientD5` | `real` | 0.0 | Coefficient D5 in the HyperelasticMat relation. |

### HyperelasticMat: boyceOrGent

Form `boyceOrGent`, when `modelName` is `ArrudaBoyce`, `Gent`.

`HyperelasticMat;id;modelName;bulkModulus;density;thermalExpansion;referenceTemperature;structuralDamping;rubberModulus;exponentOrModulus;invariantLimit;coefficientD1;coefficientD2;coefficientD3;coefficientD4;coefficientD5`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `modelName` | `text` | MooneyRivlin | Text naming the model. |
| 3 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 4 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 8 | `rubberModulus` | `real` | 1.0 | Rubber modulus (force per area). |
| 9 | `exponentOrModulus` | `real` | 1.0 | Exponent or modulus (force per area). |
| 10 | `invariantLimit` | `real` | 0.0 | Limit imposed on the selected strain or stress invariant. |
| 11 | `coefficientD1` | `real` | 0.0 | Coefficient D1 in the HyperelasticMat relation. |
| 12 | `coefficientD2` | `real` | 0.0 | Coefficient D2 in the HyperelasticMat relation. |
| 13 | `coefficientD3` | `real` | 0.0 | Coefficient D3 in the HyperelasticMat relation. |
| 14 | `coefficientD4` | `real` | 0.0 | Coefficient D4 in the HyperelasticMat relation. |
| 15 | `coefficientD5` | `real` | 0.0 | Coefficient D5 in the HyperelasticMat relation. |

### HyperelasticMat: generalized

Form `generalized`, when `modelName` is `GeneralHyperelasticModel1`, `GeneralHyperelasticModel2`, `GeneralHyperelasticModel3`, `GeneralHyperelasticModel4`, `GeneralHyperelasticModel5`, `GeneralHyperelasticModel6`.

`HyperelasticMat;id;modelName;bulkModulus;density;thermalExpansion;referenceTemperature;structuralDamping`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `modelName` | `text` | MooneyRivlin | Text naming the model. |
| 3 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 4 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |

### HyperelasticMat: mooney

Form `mooney`, for every other record.

`HyperelasticMat;id;modelName;bulkModulus;density;thermalExpansion;referenceTemperature;structuralDamping;coefficientC10;coefficientC01;coefficientD1;tensionTableId;equibiaxialTableId;simpleShearTableId;pureShearTableId;volumetricTableId;coefficientC20;coefficientC11;coefficientC02;coefficientD2;distortionalOrder;volumetricOrder;coefficientC30;coefficientC21;coefficientC12;coefficientC03;coefficientD3;coefficientC40;coefficientC31;coefficientC22;coefficientC13;coefficientC04;coefficientD4;coefficientC50;coefficientC41;coefficientC32;coefficientC23;coefficientC14;coefficientC05;coefficientD5`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `modelName` | `text` | MooneyRivlin | Text naming the model. |
| 3 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 4 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 6 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 7 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 8 | `coefficientC10` | `real` | 0.0 | Coefficient C10 in the HyperelasticMat relation. |
| 9 | `coefficientC01` | `real` | 0.0 | Coefficient C01 in the HyperelasticMat relation. |
| 10 | `coefficientD1` | `real` | 0.0 | Coefficient D1 in the HyperelasticMat relation. |
| 11 | `tensionTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 12 | `equibiaxialTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 13 | `simpleShearTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 14 | `pureShearTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 15 | `volumetricTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 16 | `coefficientC20` | `real` | 0.0 | Coefficient C20 in the HyperelasticMat relation. |
| 17 | `coefficientC11` | `real` | 0.0 | Coefficient C11 in the HyperelasticMat relation. |
| 18 | `coefficientC02` | `real` | 0.0 | Coefficient C02 in the HyperelasticMat relation. |
| 19 | `coefficientD2` | `real` | 0.0 | Coefficient D2 in the HyperelasticMat relation. |
| 20 | `distortionalOrder` | `integer` | 2 | Order used for the distortional part of the constitutive expansion. |
| 21 | `volumetricOrder` | `integer` | 1 | Order used for the volume-change part of the constitutive expansion. |
| 22 | `coefficientC30` | `real` | 0.0 | Coefficient C30 in the HyperelasticMat relation. |
| 23 | `coefficientC21` | `real` | 0.0 | Coefficient C21 in the HyperelasticMat relation. |
| 24 | `coefficientC12` | `real` | 0.0 | Coefficient C12 in the HyperelasticMat relation. |
| 25 | `coefficientC03` | `real` | 0.0 | Coefficient C03 in the HyperelasticMat relation. |
| 26 | `coefficientD3` | `real` | 0.0 | Coefficient D3 in the HyperelasticMat relation. |
| 27 | `coefficientC40` | `real` | 0.0 | Coefficient C40 in the HyperelasticMat relation. |
| 28 | `coefficientC31` | `real` | 0.0 | Coefficient C31 in the HyperelasticMat relation. |
| 29 | `coefficientC22` | `real` | 0.0 | Coefficient C22 in the HyperelasticMat relation. |
| 30 | `coefficientC13` | `real` | 0.0 | Coefficient C13 in the HyperelasticMat relation. |
| 31 | `coefficientC04` | `real` | 0.0 | Coefficient C04 in the HyperelasticMat relation. |
| 32 | `coefficientD4` | `real` | 0.0 | Coefficient D4 in the HyperelasticMat relation. |
| 33 | `coefficientC50` | `real` | 0.0 | Coefficient C50 in the HyperelasticMat relation. |
| 34 | `coefficientC41` | `real` | 0.0 | Coefficient C41 in the HyperelasticMat relation. |
| 35 | `coefficientC32` | `real` | 0.0 | Coefficient C32 in the HyperelasticMat relation. |
| 36 | `coefficientC23` | `real` | 0.0 | Coefficient C23 in the HyperelasticMat relation. |
| 37 | `coefficientC14` | `real` | 0.0 | Coefficient C14 in the HyperelasticMat relation. |
| 38 | `coefficientC05` | `real` | 0.0 | Coefficient C05 in the HyperelasticMat relation. |
| 39 | `coefficientD5` | `real` | 0.0 | Coefficient D5 in the HyperelasticMat relation. |

Accepted words: `ArrudaBoyce`, `Foam`, `GeneralHyperelasticModel1`, `GeneralHyperelasticModel2`, `GeneralHyperelasticModel3`, `GeneralHyperelasticModel4`, `GeneralHyperelasticModel5`, `GeneralHyperelasticModel6`, `Gent`, `MooneyRivlin`, `Ogden`.

**Example record**

~~~text
HyperelasticMat;1;MooneyRivlin;600.;1.1E-9;2.E-4;20.;;0.5;0.1
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_rubber_viscoelastic_sma.oos)

## HyperelasticMatTemperature

The temperature dependence of the coefficients of a [HyperelasticMat](materials.md#hyperelasticmat).

**Record format and fields**

`HyperelasticMatTemperature;id;modelName;bulkModulusTableId;densityTableId;thermalExpansionTableId;structuralDampingTableId;coefficientC10TableIdOrCoefficientD1TableIdOrRubberModulusTableId;coefficientC01TableIdOrCoefficientD2TableIdOrExponentOrModulusTableId;coefficientD1TableIdOrCoefficientD3TableIdOrInvariantLimitTableId;coefficientD4TableIdOfOgden;coefficientD5TableIdOfOgden;coefficientC20TableIdOrCoefficientD1TableId;coefficientC11TableIdOrCoefficientD2TableId;coefficientC02TableIdOrCoefficientD3TableId;coefficientD2TableIdOrCoefficientD4TableId;coefficientD5TableIdOfBoyce;coefficientC30TableId;coefficientC21TableId;coefficientC12TableId;coefficientC03TableId;coefficientD3TableId;coefficientC40TableIdOrCoefficientD1TableId;coefficientC31TableIdOrCoefficientD2TableId;coefficientC22TableIdOrCoefficientD3TableId;coefficientC13TableIdOrCoefficientD4TableId;coefficientC04TableIdOrCoefficientD5TableId;coefficientD4TableId;coefficientC50TableId;coefficientC41TableId;coefficientC32TableId;coefficientC23TableId;coefficientC14TableId;coefficientC05TableId;coefficientD5TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `modelName` | `text` | MooneyRivlin | Text naming the model. |
| 3 | `bulkModulusTableId` | `integer` | 0 | Table supplying the variation of bulk modulus. |
| 4 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 5 | `thermalExpansionTableId` | `integer` | 0 | Thermal expansion coefficient (inverse temperature) in the TableId material or local axes. |
| 6 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 7 | `coefficientC10TableIdOrCoefficientD1TableIdOrRubberModulusTableId` | `integer` | 0 | Table supplying the variation of coefficient c 10 table ID or coefficient d 1 table ID or rubber modulus. |
| 8 | `coefficientC01TableIdOrCoefficientD2TableIdOrExponentOrModulusTableId` | `integer` | 0 | Table supplying the variation of coefficient c 01 table ID or coefficient d 2 table ID or exponent or modulus. |
| 9 | `coefficientD1TableIdOrCoefficientD3TableIdOrInvariantLimitTableId` | `integer` | 0 | Table supplying the variation of coefficient d 1 table ID or coefficient d 3 table ID or invariant limit. |
| 10 | `coefficientD4TableIdOfOgden` | `integer` | 0 | Table supplying the variation of coefficient D4 for the Ogden constitutive law. |
| 11 | `coefficientD5TableIdOfOgden` | `integer` | 0 | Table supplying the variation of coefficient D5 for the Ogden constitutive law. |
| 12 | `coefficientC20TableIdOrCoefficientD1TableId` | `integer` | 0 | Table supplying the variation of coefficient c 20 table ID or coefficient d 1. |
| 13 | `coefficientC11TableIdOrCoefficientD2TableId` | `integer` | 0 | Table supplying the variation of coefficient c 11 table ID or coefficient d 2. |
| 14 | `coefficientC02TableIdOrCoefficientD3TableId` | `integer` | 0 | Table supplying the variation of coefficient c 02 table ID or coefficient d 3. |
| 15 | `coefficientD2TableIdOrCoefficientD4TableId` | `integer` | 0 | Table supplying the variation of coefficient d 2 table ID or coefficient d 4. |
| 16 | `coefficientD5TableIdOfBoyce` | `integer` | 0 | Table supplying the variation of coefficient D5 for the Boyce constitutive law. |
| 17 | `coefficientC30TableId` | `integer` | 0 | Table supplying the variation of coefficient c 30. |
| 18 | `coefficientC21TableId` | `integer` | 0 | Table supplying the variation of coefficient c 21. |
| 19 | `coefficientC12TableId` | `integer` | 0 | Table supplying the variation of coefficient c 12. |
| 20 | `coefficientC03TableId` | `integer` | 0 | Table supplying the variation of coefficient c 03. |
| 21 | `coefficientD3TableId` | `integer` | 0 | Table supplying the variation of coefficient d 3. |
| 22 | `coefficientC40TableIdOrCoefficientD1TableId` | `integer` | 0 | Table supplying the variation of coefficient c 40 table ID or coefficient d 1. |
| 23 | `coefficientC31TableIdOrCoefficientD2TableId` | `integer` | 0 | Table supplying the variation of coefficient c 31 table ID or coefficient d 2. |
| 24 | `coefficientC22TableIdOrCoefficientD3TableId` | `integer` | 0 | Table supplying the variation of coefficient c 22 table ID or coefficient d 3. |
| 25 | `coefficientC13TableIdOrCoefficientD4TableId` | `integer` | 0 | Table supplying the variation of coefficient c 13 table ID or coefficient d 4. |
| 26 | `coefficientC04TableIdOrCoefficientD5TableId` | `integer` | 0 | Table supplying the variation of coefficient c 04 table ID or coefficient d 5. |
| 27 | `coefficientD4TableId` | `integer` | 0 | Table supplying the variation of coefficient d 4. |
| 28 | `coefficientC50TableId` | `integer` | 0 | Table supplying the variation of coefficient c 50. |
| 29 | `coefficientC41TableId` | `integer` | 0 | Table supplying the variation of coefficient c 41. |
| 30 | `coefficientC32TableId` | `integer` | 0 | Table supplying the variation of coefficient c 32. |
| 31 | `coefficientC23TableId` | `integer` | 0 | Table supplying the variation of coefficient c 23. |
| 32 | `coefficientC14TableId` | `integer` | 0 | Table supplying the variation of coefficient c 14. |
| 33 | `coefficientC05TableId` | `integer` | 0 | Table supplying the variation of coefficient c 05. |
| 34 | `coefficientD5TableId` | `integer` | 0 | Table supplying the variation of coefficient d 5. |

Accepted words: `ArrudaBoyce`, `Foam`, `Gent`, `MooneyRivlin`, `Ogden`.

**Example record**

~~~text
HyperelasticMatTemperature;1;MooneyRivlin;;;;;101;102
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_rubber_viscoelastic_sma.oos)

Reading the example gives `id = 1`, `modelName = MooneyRivlin`, `coefficientC10TableIdOrCoefficientD1TableIdOrRubberModulusTableId = 101`, `coefficientC01TableIdOrCoefficientD2TableIdOrExponentOrModulusTableId = 102`.

## HyperelasticPolynomialMat

A hyperelastic (rubber-like) material, the generalised Mooney-Rivlin strain energy function.

**Record format and fields**

`HyperelasticPolynomialMat;id;coefficientA10;coefficientA01;coefficientD1;density;thermalExpansion;referenceTemperature;structuralDamping;distortionalOrder;volumetricOrder;coefficientA20;coefficientA11;coefficientA02;coefficientD2;coefficientA30;coefficientA21;coefficientA12;coefficientA03;coefficientD3;coefficientA40;coefficientA31;coefficientA22;coefficientA13;coefficientA04;coefficientD4;coefficientA50;coefficientA41;coefficientA32;coefficientA23;coefficientA14;coefficientA05;coefficientD5;tensionTableId;equibiaxialTableId;simpleShearTableId;pureShearTableId;volumetricTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `coefficientA10` | `real` | 0.0 | Coefficient A10 in the HyperelasticPolynomialMat relation. |
| 3 | `coefficientA01` | `real` | 0.0 | Coefficient A01 in the HyperelasticPolynomialMat relation. |
| 4 | `coefficientD1` | `real` | — | Coefficient D1 in the HyperelasticPolynomialMat relation. |
| 5 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 6 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 7 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 8 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 9 | `distortionalOrder` | `integer` | 1 | Order used for the distortional part of the constitutive expansion. |
| 10 | `volumetricOrder` | `integer` | 1 | Order used for the volume-change part of the constitutive expansion. |
| 11 | `coefficientA20` | `real` | — | Coefficient A20 in the HyperelasticPolynomialMat relation. |
| 12 | `coefficientA11` | `real` | — | Coefficient A11 in the HyperelasticPolynomialMat relation. |
| 13 | `coefficientA02` | `real` | — | Coefficient A02 in the HyperelasticPolynomialMat relation. |
| 14 | `coefficientD2` | `real` | — | Coefficient D2 in the HyperelasticPolynomialMat relation. |
| 15 | `coefficientA30` | `real` | — | Coefficient A30 in the HyperelasticPolynomialMat relation. |
| 16 | `coefficientA21` | `real` | — | Coefficient A21 in the HyperelasticPolynomialMat relation. |
| 17 | `coefficientA12` | `real` | — | Coefficient A12 in the HyperelasticPolynomialMat relation. |
| 18 | `coefficientA03` | `real` | — | Coefficient A03 in the HyperelasticPolynomialMat relation. |
| 19 | `coefficientD3` | `real` | — | Coefficient D3 in the HyperelasticPolynomialMat relation. |
| 20 | `coefficientA40` | `real` | — | Coefficient A40 in the HyperelasticPolynomialMat relation. |
| 21 | `coefficientA31` | `real` | — | Coefficient A31 in the HyperelasticPolynomialMat relation. |
| 22 | `coefficientA22` | `real` | — | Coefficient A22 in the HyperelasticPolynomialMat relation. |
| 23 | `coefficientA13` | `real` | — | Coefficient A13 in the HyperelasticPolynomialMat relation. |
| 24 | `coefficientA04` | `real` | — | Coefficient A04 in the HyperelasticPolynomialMat relation. |
| 25 | `coefficientD4` | `real` | — | Coefficient D4 in the HyperelasticPolynomialMat relation. |
| 26 | `coefficientA50` | `real` | — | Coefficient A50 in the HyperelasticPolynomialMat relation. |
| 27 | `coefficientA41` | `real` | — | Coefficient A41 in the HyperelasticPolynomialMat relation. |
| 28 | `coefficientA32` | `real` | — | Coefficient A32 in the HyperelasticPolynomialMat relation. |
| 29 | `coefficientA23` | `real` | — | Coefficient A23 in the HyperelasticPolynomialMat relation. |
| 30 | `coefficientA14` | `real` | — | Coefficient A14 in the HyperelasticPolynomialMat relation. |
| 31 | `coefficientA05` | `real` | — | Coefficient A05 in the HyperelasticPolynomialMat relation. |
| 32 | `coefficientD5` | `real` | — | Coefficient D5 in the HyperelasticPolynomialMat relation. |
| 33 | `tensionTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 34 | `equibiaxialTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 35 | `simpleShearTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 36 | `pureShearTableId` | `integer` | 0 | Identifier addressing stress table data. |
| 37 | `volumetricTableId` | `integer` | 0 | Identifier addressing stress table data. |

**Example record**

~~~text
HyperelasticPolynomialMat;3;0.5;0.1;50.;1.1E-9
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_solids_initial_state.oos)

Reading the example gives `id = 3`, `coefficientA10 = 0.5`, `coefficientA01 = 0.1`, `coefficientD1 = 50.`.

## IsoMat

An isotropic elastic material shared by element properties. Young’s modulus, shear modulus and Poisson’s ratio describe its elastic response.

**Record format and fields**

`IsoMat;id;youngsModulus;shearModulus;poissonRatio;density;thermalExpansion;referenceTemperature;structuralDamping;tensionAllowable;compressionAllowable;shearAllowable;stressFrameId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `youngsModulus` | `real` | — | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). |
| 3 | `shearModulus` | `real` | — | Elastic shear stress divided by engineering shear strain (force per area). |
| 4 | `poissonRatio` | `real` | — | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). |
| 5 | `density` | `real` | 0.0 | Mass per unit volume for inertia and gravity loads. |
| 6 | `thermalExpansion` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). |
| 7 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 8 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 9 | `tensionAllowable` | `real` | 0.0 | Allowable tensile stress, in force per area. |
| 10 | `compressionAllowable` | `real` | 0.0 | Allowable compressive stress, in force per area. |
| 11 | `shearAllowable` | `real` | 0.0 | Allowable shear stress, in force per area. |
| 12 | `stressFrameId` | `integer` | 0 | Coordinate system used for material stress output. |

Designable field descriptors: youngsModulus, shearModulus, poissonRatio, density, thermalExpansion, referenceTemperature, structuralDamping, tensionAllowable, compressionAllowable, shearAllowable.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the material ID must be a positive integer.

**Example record**

~~~text
IsoMat;41;200.;;0.3;1.5E-9;1.E-4;20.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 41`, `youngsModulus = 200.`, `poissonRatio = 0.3`, `density = 1.5E-9`.

## IsoMatExplicitExt

The additional properties of an [IsoMat](materials.md#isomat) for solid elements: the equation of state.

**Record format and fields**

`IsoMatExplicitExt;id;equationOfStateId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `equationOfStateId` | `integer` | Required | Identifier addressing equation of state data. |

**Example record**

~~~text
IsoMatExplicitExt;1;11
~~~

[Model containing this record](../../../validation/models/read_only_materials/sol700_mat1a_mat8a.oos)

Reading the example gives `id = 1`, `equationOfStateId = 11`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.

## IsoMatFreq

The frequency dependence of the properties of an [IsoMat](materials.md#isomat) (an isotropic material).

**Record format and fields**

`IsoMatFreq;id;youngsModulusTableId;shearModulusTableId;poissonRatioTableId;structuralDampingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulusTableId` | `integer` | 0 | Uniaxial elastic modulus (force per area) in the TableId material or local axes. |
| 3 | `shearModulusTableId` | `integer` | 0 | Shear modulus (force per area) in the TableId material or local axes. |
| 4 | `poissonRatioTableId` | `integer` | 0 | Transverse contraction ratio in the TableId material or local axes. |
| 5 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |

**Example record**

~~~text
IsoMatFreq;1;11;12;13;14
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 1`, `youngsModulusTableId = 11`, `shearModulusTableId = 12`, `poissonRatioTableId = 13`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.

## IsoMatStressDependent

The stress dependent properties of an [IsoMat](materials.md#isomat) (nonlinear elasticity or plasticity).

**Record format and fields**

`IsoMatStressDependent;id;tableId;kind;hardeningSlope;yieldFunction;hardeningRule;initialYieldStress;frictionAngle`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 3 | `kind` | `text` | — | Selects the kind for IsoMatStressDependent. |
| 4 | `hardeningSlope` | `real` | — | Slope of the material hardening curve. |
| 5 | `yieldFunction` | `integer` | 1 | Function defining the material yield surface. |
| 6 | `hardeningRule` | `integer` | 1 | Selects how the yield surface evolves with accumulated plastic deformation. |
| 7 | `initialYieldStress` | `real` | — | Initial yield stress (force per area). |
| 8 | `frictionAngle` | `real` | — | Internal friction angle in the material yield or flow law. |

Accepted words: `NonlinearElastic`, `Plastic`.

**Example record**

~~~text
IsoMatStressDependent;2;;Plastic;1.E+3;1;1;150.
~~~

[Model containing this record](../../../validation/models/nonlinear_elements/sol400_property_extensions.oos)

Reading the example gives `id = 2`, `kind = Plastic`, `hardeningSlope = 1.E+3`, `yieldFunction = 1`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 2`.

## IsoMatTemperature

The temperature dependent properties of an [IsoMat](materials.md#isomat).

**Record format and fields**

`IsoMatTemperature;id;youngsModulusTableId;shearModulusTableId;poissonRatioTableId;densityTableId;thermalExpansionTableId;structuralDampingTableId;tensionAllowableTableId;compressionAllowableTableId;shearAllowableTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulusTableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `shearModulusTableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `poissonRatioTableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 6 | `thermalExpansionTableId` | `integer` | 0 | Identifier addressing material table data. |
| 7 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 8 | `tensionAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |
| 9 | `compressionAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |
| 10 | `shearAllowableTableId` | `integer` | 0 | Identifier addressing material table data. |

**Example record**

~~~text
IsoMatTemperature;1;101;102;103;;104
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 1`, `youngsModulusTableId = 101`, `shearModulusTableId = 102`, `poissonRatioTableId = 103`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1`.
- [TableMaterial1](tables.md#tablematerial1) via `youngsModulusTableId = 101`, `shearModulusTableId = 102`.
- [TableMaterial2](tables.md#tablematerial2) via `poissonRatioTableId = 103`.
- [TableMaterial4](tables.md#tablematerial4) via `thermalExpansionTableId = 104`.

## MicromechanicsCompositeMat

The material data of an advanced composite modelled by a micromechanics tool.

**Record format and fields**

`MicromechanicsCompositeMat;id;userDefinedNameId;density`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `userDefinedNameId` | `integer` | Required | Identifier addressing user defined name data. |
| 3 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |

**Example record**

~~~text
MicromechanicsCompositeMat;1;10;1.36E-9
~~~

[Model containing this record](../../../validation/models/read_only_materials/sol400_matdigi.oos)

Reading the example gives `id = 1`, `userDefinedNameId = 10`, `density = 1.36E-9`.

## NonlinearMatOptions

The nonlinear material, composite and control options.

**Record format and fields**

`NonlinearMatOptions;<keyed sections>`

This part of the record has no fixed fields.

**Keyed sections in `options`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Creep`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `explicitCreepModel` | `integer` | 0 | Selects the creep relation used in explicit integration. |
| 2 | `explicitCreepOption` | `integer` | 0 | Selects the explicit creep option for creepOption. |
| 3 | `implicitCreep` | `integer` | 0 | Selects implicit integration of the creep response. |
| 4 | `implicitCreepTangent` | `integer` | 0 | Selects the tangent used in implicit creep integration. |

**Section `AssumedStrainOption`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `assumedStrain` | `text` | — | Selects use of an assumed strain field in the element formulation. |

**Section `TransverseShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `transverseShear` | `text` | — | Shear response perpendicular to the reference plane. |

**Section `LargeStrain`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `largeStrain` | `integer` | 0 | Selects treatment of finite deformation in the material response. |

**Section `Hemicube`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `viewFactorMethod` | `integer` | 0 | Selects the view factor method for hemicubeOption. |
| 2 | `pixelCount` | `integer` | — | Number of pixel entries. |
| 3 | `viewFactorCutoff` | `real` | 0.0 | Minimum retained radiative view-factor contribution. |
| 4 | `implicitFraction` | `real` | — | Fraction assigned to the implicit contribution in the integration. |
| 5 | `explicitReflection` | `integer` | 0 | Controls reflection treatment in the explicit response. |
| 6 | `reflectionTolerance` | `real` | — | Permitted numerical deviation for reflection. |

**Section `TemperatureDistribution`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `temperatureDistribution` | `text` | — | Selects the spatial distribution used for temperature-dependent response. |

**Section `GridMapping`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `gridMapping` | `text` | — | Specifies how properties are mapped between material and grid locations. |

**Section `PropertyMap`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `propertyMapping` | `integer` | 0 | Rule for assigning the supplied property data to model locations. |
| 2 | `propertyBehaviour` | `text` | — | Selects the behavior associated with the supplied property data. |
| 3 | `layerDirection` | `integer` | 1 | Direction in which the material layers are defined. |
| 4 | `outOfPlaneThickness` | `real` | 1.0 | Out of plane thickness (length). |
| 5 | `printFlag` | `integer` | 0 | Selects the print flag for propertyMapOption. |

**Section `ConstraintRamp`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `spcRamp` | `integer` | 0 | Specifies how the prescribed constraint is ramped over the increment. |

**Section `Deactivation`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `deactivationRule` | `integer` | — | Criterion that determines when material or element contributions are deactivated. |
| 2 | `deactivationOutput` | `integer` | 0 | Selects output concerning deactivated material or elements. |

**Section `Enthalpy`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `capacitanceScheme` | `integer` | 0 | Selects how thermal capacitance is represented in the model. |
| 2 | `enthalpyScheme` | `integer` | 0 | Selects the treatment of enthalpy in the thermal formulation. |

**Section `MapTolerance`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `mapTolerance` | `real` | 0.2 | Permitted numerical deviation for map. |

**Section `Interlaminar`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `interlaminarFrame` | `text` | — | Coordinate system for quantities resolved between layers. |
| 2 | `axisProjection` | `text` | Off | Selects how the material axes are projected into the local basis. |
| 3 | `strainOutput` | `integer` | 0 | Controls whether strains are recovered at the associated location. |

Accepted words: `AssumedStrain`, `AssumedStrainOption`, `Axisymmetric`, `BottomSurface`, `Constant`, `ConstraintRamp`, `Creep`, `Deactivation`, `Enthalpy`, `GridMapping`, `Hemicube`, `Interlaminar`, `LargeStrain`, `Linear`, `MapTolerance`, `No`, `Off`, `On`, `OneDimensional`, `PlaneStrain`, `PlaneStress`, `PropertyMap`, `Quadratic`, `TemperatureDistribution`, `ThreeDimensional`, `Top`, `TransverseShear`, `Yes`.

**Example record**

~~~text
NonlinearMatOptions;Creep;0
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

## OrthoMat2D

An orthotropic material for shell elements.

**Record format and fields**

`OrthoMat2D;id;youngsModulus1;youngsModulus2;poissonRatio12;shearModulus12;shearModulus1Z;shearModulus2Z;density;thermalExpansion1;thermalExpansion2;referenceTemperature;tensionStrength1;compressionStrength1;tensionStrength2;compressionStrength2;shearStrength;structuralDamping;interactionTerm12;strainAllowables;hashinUnidirectional;hashinUnidirectional1;hashinUnidirectional2;hashinUnidirectional3;hashinUnidirectional4;hashinUnidirectional10;hashinUnidirectional11;hashinTape;hashinTape1;hashinTape2;hashinTape3;hashinTape4;hashinTape5;hashinTape6;hashinTape10;hashinTape11;hashinTape12;hashinFabric;hashinFabric1;hashinFabric2;hashinFabric3;hashinFabric4;hashinFabric5;hashinFabric6;hashinFabric10;hashinFabric11;hashinFabric12`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `youngsModulus1` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 1. |
| 3 | `youngsModulus2` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 2. |
| 4 | `poissonRatio12` | `real` | 0.0 | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 12. |
| 5 | `shearModulus12` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 12. |
| 6 | `shearModulus1Z` | `real` | — | Elastic shear modulus in the material plane spanned by direction 1 and z (force per area). |
| 7 | `shearModulus2Z` | `real` | — | Elastic shear modulus in the material plane spanned by direction 2 and z (force per area). |
| 8 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 9 | `thermalExpansion1` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 10 | `thermalExpansion2` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 11 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 12 | `tensionStrength1` | `real` | 0.0 | Allowables in tension and compression, longitudinal and lateral, and in shear. |
| 13 | `compressionStrength1` | `real` | same as tensionStrength1 | Strength limit in compression for material direction or entry 1 (force per area). |
| 14 | `tensionStrength2` | `real` | 0.0 | Strength limit in tension for material direction or entry 2 (force per area). |
| 15 | `compressionStrength2` | `real` | same as tensionStrength2 | Strength limit in compression for material direction or entry 2 (force per area). |
| 16 | `shearStrength` | `real` | 0.0 | Limiting shear stress of the material. |
| 17 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 18 | `interactionTerm12` | `real` | 0.0 | Parameter 12 of the interaction term relation for this material. |
| 19 | `strainAllowables` | `real` | 0.0 | Selects or supplies the limiting strains for the material criterion. |
| 20 | `hashinUnidirectional` | `text` | — | Parameter value of the hashin unidirectional relation for this material. |
| 21 | `hashinUnidirectional1` | `real` | — | Parameter 1 of the hashin unidirectional relation for this material. |
| 22 | `hashinUnidirectional2` | `real` | same as hashinUnidirectional1 | Parameter 2 of the hashin unidirectional relation for this material. |
| 23 | `hashinUnidirectional3` | `real` | — | Parameter 3 of the hashin unidirectional relation for this material. |
| 24 | `hashinUnidirectional4` | `real` | same as hashinUnidirectional3 | Parameter 4 of the hashin unidirectional relation for this material. |
| 25 | `hashinUnidirectional10` | `real` | — | Parameter 10 of the hashin unidirectional relation for this material. |
| 26 | `hashinUnidirectional11` | `real` | same as hashinUnidirectional10 | Parameter 11 of the hashin unidirectional relation for this material. |
| 27 | `hashinTape` | `text` | — | Parameter value of the hashin tape relation for this material. |
| 28 | `hashinTape1` | `real` | — | Parameter 1 of the hashin tape relation for this material. |
| 29 | `hashinTape2` | `real` | same as hashinTape1 | Parameter 2 of the hashin tape relation for this material. |
| 30 | `hashinTape3` | `real` | — | Parameter 3 of the hashin tape relation for this material. |
| 31 | `hashinTape4` | `real` | same as hashinTape3 | Parameter 4 of the hashin tape relation for this material. |
| 32 | `hashinTape5` | `real` | 0.0 | Parameter 5 of the hashin tape relation for this material. |
| 33 | `hashinTape6` | `real` | 0.0 | Parameter 6 of the hashin tape relation for this material. |
| 34 | `hashinTape10` | `real` | — | Parameter 10 of the hashin tape relation for this material. |
| 35 | `hashinTape11` | `real` | same as hashinTape10 | Parameter 11 of the hashin tape relation for this material. |
| 36 | `hashinTape12` | `real` | same as hashinTape11 | Parameter 12 of the hashin tape relation for this material. |
| 37 | `hashinFabric` | `text` | — | Parameter value of the hashin fabric relation for this material. |
| 38 | `hashinFabric1` | `real` | — | Parameter 1 of the hashin fabric relation for this material. |
| 39 | `hashinFabric2` | `real` | same as hashinFabric1 | Parameter 2 of the hashin fabric relation for this material. |
| 40 | `hashinFabric3` | `real` | — | Parameter 3 of the hashin fabric relation for this material. |
| 41 | `hashinFabric4` | `real` | same as hashinFabric3 | Parameter 4 of the hashin fabric relation for this material. |
| 42 | `hashinFabric5` | `real` | — | Parameter 5 of the hashin fabric relation for this material. |
| 43 | `hashinFabric6` | `real` | same as hashinFabric5 | Parameter 6 of the hashin fabric relation for this material. |
| 44 | `hashinFabric10` | `real` | — | Parameter 10 of the hashin fabric relation for this material. |
| 45 | `hashinFabric11` | `real` | same as hashinFabric10 | Parameter 11 of the hashin fabric relation for this material. |
| 46 | `hashinFabric12` | `real` | same as hashinFabric11 | Parameter 12 of the hashin fabric relation for this material. |

Accepted words: `HashinCriterion`, `HashinFabricFailure`, `HashinTape`.

Designable field descriptors: youngsModulus1, youngsModulus2, poissonRatio12, shearModulus12, shearModulus1Z, shearModulus2Z, density, thermalExpansion1, thermalExpansion2, referenceTemperature, tensionStrength1, compressionStrength1, tensionStrength2, compressionStrength2, shearStrength, structuralDamping, interactionTerm12, strainAllowables.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the material ID must be an integer from 1 to 99999999.

**Example record**

~~~text
OrthoMat2D;3;1.4E+5;1.E+4;0.3;5.E+3;5.E+3;4.E+3;1.6E-9
~~~

[Model containing this record](../../../validation/models/explicit_structures/tube_impact_wall.oos)

Reading the example gives `id = 3`, `youngsModulus1 = 1.4E+5`, `youngsModulus2 = 1.E+4`, `poissonRatio12 = 0.3`.

## OrthoMat2DFailure

The failure properties of an orthotropic material for shell elements; the [OrthoMat2D](materials.md#orthomat2d) with the same ID holds the elastic constants.

**Record format and fields**

`OrthoMat2DFailure;id;theory;historyVariableCount;shearStrength;nonlinearShearCoefficient;transverseShear;interactionTerm12;tensionStrength1;compressionStrength1;tensionStrength2;compressionStrength2;degradation;degradationParameter;degradationStart;fiberTensionTheory;fiberCompressionTheory;matrixTensionTheory;matrixCompressionTheory;matrixShearTheory;fiberTensionDegradation;fiberCompressionDegradation;matrixTensionDegradation;matrixCompressionDegradation;matrixShearDegradation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `theory` | `text` | — | Selects the constitutive or failure theory to apply. |
| 3 | `historyVariableCount` | `integer` | 0 | Number of history variable entries. |
| 4 | `shearStrength` | `real` | — | Limiting shear stress of the material. |
| 5 | `nonlinearShearCoefficient` | `real` | 0.0 | Coefficient in the relation for nonlinear shear. |
| 6 | `transverseShear` | `text` | — | Shear response perpendicular to the reference plane. |
| 7 | `interactionTerm12` | `real` | 0.0 | Parameter 12 of the interaction term relation for this material. |
| 8 | `tensionStrength1` | `real` | 0.0 | Strength limit in tension for material direction or entry 1 (force per area). |
| 9 | `compressionStrength1` | `real` | 0.0 | Strength limit in compression for material direction or entry 1 (force per area). |
| 10 | `tensionStrength2` | `real` | 0.0 | Strength limit in tension for material direction or entry 2 (force per area). |
| 11 | `compressionStrength2` | `real` | 0.0 | Strength limit in compression for material direction or entry 2 (force per area). |
| 12 | `degradation` | `text` | — | Reduction of material response after a damage criterion is met. |
| 13 | `degradationParameter` | `real` | 100.0 | Parameter value of the degradation parameter relation for this material. |
| 14 | `degradationStart` | `text` | — | Condition at which degradation begins. |
| 15 | `fiberTensionTheory` | `text` | — | Theory setting for the tension response of the fiber constituent. |
| 16 | `fiberCompressionTheory` | `text` | — | Theory setting for the compression response of the fiber constituent. |
| 17 | `matrixTensionTheory` | `text` | — | Theory setting for the tension response of the matrix constituent. |
| 18 | `matrixCompressionTheory` | `text` | — | Theory setting for the compression response of the matrix constituent. |
| 19 | `matrixShearTheory` | `text` | — | Theory setting for the shear response of the matrix constituent. |
| 20 | `fiberTensionDegradation` | `text` | — | Degradation setting for the tension response of the fiber constituent. |
| 21 | `fiberCompressionDegradation` | `text` | — | Degradation setting for the compression response of the fiber constituent. |
| 22 | `matrixTensionDegradation` | `text` | — | Degradation setting for the tension response of the matrix constituent. |
| 23 | `matrixCompressionDegradation` | `text` | — | Degradation setting for the compression response of the matrix constituent. |
| 24 | `matrixShearDegradation` | `text` | — | Degradation setting for the shear response of the matrix constituent. |

Accepted words: `All`, `ChangChangFailure`, `CombinedFailure`, `Elements`, `HashinFailure`, `Hill`, `IndividualDegradation`, `ModifiedTsaiWu`, `Steps`, `StressTheory`, `SublaminateShear`, `Time`, `TsaiWu`, `Velocity`.

**Example record**

~~~text
OrthoMat2DFailure;2;HashinFailure;;70.;;;;1500.;1200.;50.;200.
~~~

[Model containing this record](../../../validation/models/read_only_materials/sol700_mat1a_mat8a.oos)

Reading the example gives `id = 2`, `theory = HashinFailure`, `shearStrength = 70.`, `tensionStrength1 = 1500.`.

**Referenced records in this example**

- [OrthoMat2D](materials.md#orthomat2d) via `id = 2`.

## OrthoMat2DFreq

The frequency dependence of the properties of an [OrthoMat2D](materials.md#orthomat2d) (a shell element orthotropic material).

**Record format and fields**

`OrthoMat2DFreq;id;youngsModulus1TableId;youngsModulus2TableId;poissonRatio12TableId;shearModulus12TableId;shearModulus1ZTableId;shearModulus2ZTableId;structuralDampingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 1. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 2. |
| 4 | `poissonRatio12TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 12. |
| 5 | `shearModulus12TableId` | `integer` | 0 | Table supplying the variation of shear modulus 12. |
| 6 | `shearModulus1ZTableId` | `integer` | 0 | Table supplying the variation of shear modulus 1 z. |
| 7 | `shearModulus2ZTableId` | `integer` | 0 | Table supplying the variation of shear modulus 2 z. |
| 8 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |

**Example record**

~~~text
OrthoMat2DFreq;3;31;;;;;;32
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_frequency_dependent_materials.oos)

Reading the example gives `id = 3`, `youngsModulus1TableId = 31`, `structuralDampingTableId = 32`.

**Referenced records in this example**

- [OrthoMat2D](materials.md#orthomat2d) via `id = 3`.

## OrthoMat2DStressDependent

Adds nonlinear elastic behavior to an [OrthoMat2D](materials.md#orthomat2d) material used in shells or plane stress.

**Record format and fields**

`OrthoMat2DStressDependent;id;youngsModulus1TableId;youngsModulus2TableId;poissonRatio12TableId;shearModulus12TableId;shearModulus1ZTableId;shearModulus2ZTableId;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 1. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 2. |
| 4 | `poissonRatio12TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 12. |
| 5 | `shearModulus12TableId` | `integer` | 0 | Table supplying the variation of shear modulus 12. |
| 6 | `shearModulus1ZTableId` | `integer` | 0 | Table supplying the variation of shear modulus 1 z. |
| 7 | `shearModulus2ZTableId` | `integer` | 0 | Table supplying the variation of shear modulus 2 z. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `thermalExpansion1TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 1. |
| 10 | `thermalExpansion2TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 2. |

**Example record**

~~~text
OrthoMat2DStressDependent;20;201
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 20`, `youngsModulus1TableId = 201`.

**Referenced records in this example**

- [OrthoMat2D](materials.md#orthomat2d) via `id = 20`.

## OrthoMat2DTemperature

The temperature dependent properties of an [OrthoMat2D](materials.md#orthomat2d).

**Record format and fields**

`OrthoMat2DTemperature;id;youngsModulus1TableId;youngsModulus2TableId;poissonRatio12TableId;shearModulus12TableId;shearModulus1ZTableId;shearModulus2ZTableId;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId;tensionStrength1TableId;compressionStrength1TableId;tensionStrength2TableId;compressionStrength2TableId;shearStrengthTableId;structuralDampingTableId;interactionTerm12TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `poissonRatio12TableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `shearModulus12TableId` | `integer` | 0 | Identifier addressing material table data. |
| 6 | `shearModulus1ZTableId` | `integer` | 0 | Identifier addressing material table data. |
| 7 | `shearModulus2ZTableId` | `integer` | 0 | Identifier addressing material table data. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `thermalExpansion1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 10 | `thermalExpansion2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 11 | `tensionStrength1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 12 | `compressionStrength1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 13 | `tensionStrength2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 14 | `compressionStrength2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 15 | `shearStrengthTableId` | `integer` | 0 | Identifier addressing material table data. |
| 16 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 17 | `interactionTerm12TableId` | `integer` | 0 | Identifier addressing material table data. |

**Example record**

~~~text
OrthoMat2DTemperature;3;301;302;;201
~~~

[Model containing this record](../../../validation/models/linear_elements/materials_temperature_static.oos)

Reading the example gives `id = 3`, `youngsModulus1TableId = 301`, `youngsModulus2TableId = 302`, `shearModulus12TableId = 201`.

**Referenced records in this example**

- [OrthoMat2D](materials.md#orthomat2d) via `id = 3`.
- [TableMaterial4](tables.md#tablematerial4) via `youngsModulus1TableId = 301`.
- [TableMaterial1](tables.md#tablematerial1) via `youngsModulus2TableId = 302`.
- [TableMaterial2](tables.md#tablematerial2) via `shearModulus12TableId = 201`.

## OrthoMat3D

Defines orthotropic elastic properties for a solid material in its three material directions.

**Record format and fields**

`OrthoMat3D;id;youngsModulus1;youngsModulus2;youngsModulus3;poissonRatio12;poissonRatio13;poissonRatio23;shearModulus12;shearModulus13;shearModulus23;density;thermalExpansion1;thermalExpansion2;thermalExpansion3;referenceTemperature;structuralDamping`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `youngsModulus1` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 1. |
| 3 | `youngsModulus2` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 2. |
| 4 | `youngsModulus3` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 3. |
| 5 | `poissonRatio12` | `real` | Required | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 12. |
| 6 | `poissonRatio13` | `real` | Required | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 13. |
| 7 | `poissonRatio23` | `real` | Required | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 23. |
| 8 | `shearModulus12` | `real` | Required | Elastic shear stress divided by engineering shear strain (force per area). Entry 12. |
| 9 | `shearModulus13` | `real` | Required | Elastic shear stress divided by engineering shear strain (force per area). Entry 13. |
| 10 | `shearModulus23` | `real` | Required | Elastic shear stress divided by engineering shear strain (force per area). Entry 23. |
| 11 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 12 | `thermalExpansion1` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 13 | `thermalExpansion2` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 14 | `thermalExpansion3` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 3. |
| 15 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 16 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |

**Example record**

~~~text
OrthoMat3D;2;1.35E+5;9.E+3;9.E+3;0.3;0.3;0.4;5.E+3;5.E+3;3500.;1.6E-9
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `id = 2`, `youngsModulus1 = 1.35E+5`, `youngsModulus2 = 9.E+3`, `youngsModulus3 = 9.E+3`.

## OrthoMat3DNonlinear

Defines a three-dimensional orthotropic material with optional plastic yielding for nonlinear solid elements.

**Record format and fields**

`OrthoMat3DNonlinear;id;youngsModulus1;youngsModulus2;youngsModulus3;poissonRatio12;poissonRatio23;poissonRatio31;density;shearModulus12;shearModulus23;shearModulus31;thermalExpansion1;thermalExpansion2;thermalExpansion3;referenceTemperature;structuralDamping;yieldCriterion;hardeningRule;yieldStress;yieldStressRatio11;yieldStressRatio22;yieldStressRatio33;yieldStressRatio12;yieldStressRatio23;yieldStressRatio31;materialAxes;propertiesFile;vector1X;vector1Y;vector1Z;vector2X;vector2Y;vector2Z`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `youngsModulus1` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 1. |
| 3 | `youngsModulus2` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 2. |
| 4 | `youngsModulus3` | `real` | Required | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 3. |
| 5 | `poissonRatio12` | `real` | Required | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 12. |
| 6 | `poissonRatio23` | `real` | 0.0 | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 23. |
| 7 | `poissonRatio31` | `real` | same as poissonRatio23 | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 31. |
| 8 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |
| 9 | `shearModulus12` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 12. |
| 10 | `shearModulus23` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 23. |
| 11 | `shearModulus31` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 31. |
| 12 | `thermalExpansion1` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 13 | `thermalExpansion2` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 14 | `thermalExpansion3` | `real` | 0.0 | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 3. |
| 15 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 16 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 17 | `yieldCriterion` | `integer` | 1 | Rule for determining when a stress state reaches yield. |
| 18 | `hardeningRule` | `integer` | 1 | Selects how the yield surface evolves with accumulated plastic deformation. |
| 19 | `yieldStress` | `real` | — | Yield stress (force per area). |
| 20 | `yieldStressRatio11` | `real` | — | Relative measure of yield stress. |
| 21 | `yieldStressRatio22` | `real` | — | Relative measure of yield stress. |
| 22 | `yieldStressRatio33` | `real` | — | Relative measure of yield stress. |
| 23 | `yieldStressRatio12` | `real` | — | Relative measure of yield stress. |
| 24 | `yieldStressRatio23` | `real` | — | Relative measure of yield stress. |
| 25 | `yieldStressRatio31` | `real` | — | Relative measure of yield stress. |
| 26 | `materialAxes` | `text` | — | Convention specifying the axes in which material properties are expressed. |
| 27 | `propertiesFile` | `text` | — | External file supplying the material property data. |
| 28 | `vector1X` | `real` | — | Component X of orientation vector 1. |
| 29 | `vector1Y` | `real` | — | Component Y of orientation vector 1. |
| 30 | `vector1Z` | `real` | — | Component Z of orientation vector 1. |
| 31 | `vector2X` | `real` | — | Component X of orientation vector 2. |
| 32 | `vector2Y` | `real` | — | Component Y of orientation vector 2. |
| 33 | `vector2Z` | `real` | — | Component Z of orientation vector 2. |

Accepted words: `ElemMatOrientation`, `ElemPropOrientation`, `Elements`, `Vector`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `poissonRatio12` — a Poisson's ratio must be a finite number.
- `shearModulus12` — a shear modulus must not be negative.

**Example record**

~~~text
OrthoMat3DNonlinear;2;1.35E+5;9.E+3;9.E+3;0.3;0.4;0.02;1.6E-9;5.E+3;3200.;5.E+3
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol101_layered_solid_cord3g.oos)

Reading the example gives `id = 2`, `youngsModulus1 = 1.35E+5`, `youngsModulus2 = 9.E+3`, `youngsModulus3 = 9.E+3`.

## OrthoMat3DNonlinearStressDependent

Adds nonlinear elastic behavior to an [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) solid material.

**Record format and fields**

`OrthoMat3DNonlinearStressDependent;id;youngsModulus1TableId;youngsModulus2TableId;youngsModulus3TableId;poissonRatio12TableId;poissonRatio23TableId;poissonRatio31TableId;densityTableId;shearModulus12TableId;shearModulus23TableId;shearModulus31TableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 1. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 2. |
| 4 | `youngsModulus3TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 3. |
| 5 | `poissonRatio12TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 12. |
| 6 | `poissonRatio23TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 23. |
| 7 | `poissonRatio31TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 31. |
| 8 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 9 | `shearModulus12TableId` | `integer` | 0 | Table supplying the variation of shear modulus 12. |
| 10 | `shearModulus23TableId` | `integer` | 0 | Table supplying the variation of shear modulus 23. |
| 11 | `shearModulus31TableId` | `integer` | 0 | Table supplying the variation of shear modulus 31. |
| 12 | `thermalExpansion1TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 1. |
| 13 | `thermalExpansion2TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 2. |
| 14 | `thermalExpansion3TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 3. |

**Example record**

~~~text
OrthoMat3DNonlinearStressDependent;4;41;42
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 4`, `youngsModulus1TableId = 41`, `youngsModulus2TableId = 42`.

**Referenced records in this example**

- [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) via `id = 4`.

## OrthoMat3DNonlinearTemperature

The temperature dependent properties of an [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear).

**Record format and fields**

`OrthoMat3DNonlinearTemperature;id;youngsModulus1TableId;youngsModulus2TableId;youngsModulus3TableId;poissonRatio12TableId;poissonRatio23TableId;poissonRatio31TableId;shearModulus12TableId;shearModulus23TableId;shearModulus31TableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 1. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 2. |
| 4 | `youngsModulus3TableId` | `integer` | 0 | Table supplying the variation of youngs modulus 3. |
| 5 | `poissonRatio12TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 12. |
| 6 | `poissonRatio23TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 23. |
| 7 | `poissonRatio31TableId` | `integer` | 0 | Table supplying the variation of poisson ratio 31. |
| 8 | `shearModulus12TableId` | `integer` | 0 | Table supplying the variation of shear modulus 12. |
| 9 | `shearModulus23TableId` | `integer` | 0 | Table supplying the variation of shear modulus 23. |
| 10 | `shearModulus31TableId` | `integer` | 0 | Table supplying the variation of shear modulus 31. |
| 11 | `thermalExpansion1TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 1. |
| 12 | `thermalExpansion2TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 2. |
| 13 | `thermalExpansion3TableId` | `integer` | 0 | Table supplying the variation of thermal expansion 3. |

**Example record**

~~~text
OrthoMat3DNonlinearTemperature;5;51;52;53
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)

Reading the example gives `id = 5`, `youngsModulus1TableId = 51`, `youngsModulus2TableId = 52`, `youngsModulus3TableId = 53`.

**Referenced records in this example**

- [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) via `id = 5`.

## OrthoMat3DTemperature

The temperature dependent properties of an [OrthoMat3D](materials.md#orthomat3d).

**Record format and fields**

`OrthoMat3DTemperature;id;youngsModulus1TableId;youngsModulus2TableId;youngsModulus3TableId;poissonRatio12TableId;poissonRatio13TableId;poissonRatio23TableId;shearModulus12TableId;shearModulus13TableId;shearModulus23TableId;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId;structuralDampingTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulus1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 3 | `youngsModulus2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 4 | `youngsModulus3TableId` | `integer` | 0 | Identifier addressing material table data. |
| 5 | `poissonRatio12TableId` | `integer` | 0 | Identifier addressing material table data. |
| 6 | `poissonRatio13TableId` | `integer` | 0 | Identifier addressing material table data. |
| 7 | `poissonRatio23TableId` | `integer` | 0 | Identifier addressing material table data. |
| 8 | `shearModulus12TableId` | `integer` | 0 | Identifier addressing material table data. |
| 9 | `shearModulus13TableId` | `integer` | 0 | Identifier addressing material table data. |
| 10 | `shearModulus23TableId` | `integer` | 0 | Identifier addressing material table data. |
| 11 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 12 | `thermalExpansion1TableId` | `integer` | 0 | Identifier addressing material table data. |
| 13 | `thermalExpansion2TableId` | `integer` | 0 | Identifier addressing material table data. |
| 14 | `thermalExpansion3TableId` | `integer` | 0 | Identifier addressing material table data. |
| 15 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |

**Example record**

~~~text
OrthoMat3DTemperature;2;41;41;41
~~~

[Model containing this record](../../../validation/models/read_only_linear_elements/cards_outside_qrg.oos)

Reading the example gives `id = 2`, `youngsModulus1TableId = 41`, `youngsModulus2TableId = 41`, `youngsModulus3TableId = 41`.

**Referenced records in this example**

- [OrthoMat3D](materials.md#orthomat3d) via `id = 2`.
- [TableMaterial1](tables.md#tablematerial1) via `youngsModulus1TableId = 41`, `youngsModulus2TableId = 41`, `youngsModulus3TableId = 41`.

## PoroElasticMat

An isotropic poroelastic material (the solid skeleton and the fluid of a porous medium), referenced by the [SolidProp](properties.md#solidprop) of a poroelastic solid.

**Record format and fields**

`PoroElasticMat;id;solidMatId;fluidMatId;biotFactor;simplifiedModel;solidDensity;viscosity;specificHeatRatio;prandtlNumber;porosity;tortuosity;flowResistivity;viscousLength;thermalLength`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `solidMatId` | `integer` | 0 | Identifier addressing material data. |
| 3 | `fluidMatId` | `integer` | Required | Identifier addressing material data. |
| 4 | `biotFactor` | `real` | 1.0 | Multiplier for biot. |
| 5 | `simplifiedModel` | `text` | — | Selects the simplified form of the material model. |
| 6 | `solidDensity` | `real` | 0.0 | Mass per unit volume of the solid phase. |
| 7 | `viscosity` | `real` | 0.0 | Viscous response coefficient in the selected constitutive or flow law. |
| 8 | `specificHeatRatio` | `real` | 1.402 | Relative measure of specific heat. |
| 9 | `prandtlNumber` | `real` | 0.71 | The Prandtl number of the fluid. |
| 10 | `porosity` | `real` | 0.0 | Fraction of bulk volume occupied by voids. |
| 11 | `tortuosity` | `real` | 1.0 | Measure of the effective path length through a porous material relative to a straight path. |
| 12 | `flowResistivity` | `real` | Required | The air flow resistivity. |
| 13 | `viscousLength` | `real` | 0.0 | Viscous length (length). |
| 14 | `thermalLength` | `real` | 0.0 | Thermal length (length). |

Accepted words: `DelanyBazleyModel`, `LumpedMass`, `MikiModel`, `Rigid`.

**Example record**

~~~text
PoroElasticMat;201;202;203;;;;1.84E-11;1.4;0.71;0.95;1.4;2.5E-8;0.1;0.2
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_1d_sol111.oos)

Reading the example gives `id = 201`, `solidMatId = 202`, `fluidMatId = 203`, `viscosity = 1.84E-11`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `solidMatId = 202`.
- [FluidMat](materials.md#fluidmat) via `fluidMatId = 203`.

## PoroElasticMatFreq

The frequency dependent properties of an isotropic poroelastic material (it extends the [IsoMat](materials.md#isomat) with the same ID, and a [PoroElasticMat](materials.md#poroelasticmat) refers to it).

**Record format and fields**

`PoroElasticMatFreq;id;youngsModulusTableId;shearModulusTableId;poissonRatioTableId;densityTableId;thermalExpansionTableId;structuralDampingTableId;tensionAllowableTableId;compressionAllowableTableId;shearAllowableTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `youngsModulusTableId` | `integer` | 0 | Uniaxial elastic modulus (force per area) in the TableId material or local axes. |
| 3 | `shearModulusTableId` | `integer` | 0 | Shear modulus (force per area) in the TableId material or local axes. |
| 4 | `poissonRatioTableId` | `integer` | 0 | Transverse contraction ratio in the TableId material or local axes. |
| 5 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 6 | `thermalExpansionTableId` | `integer` | 0 | Thermal expansion coefficient (inverse temperature) in the TableId material or local axes. |
| 7 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 8 | `tensionAllowableTableId` | `integer` | 0 | Table supplying the variation of tension allowable. |
| 9 | `compressionAllowableTableId` | `integer` | 0 | Table supplying the variation of compression allowable. |
| 10 | `shearAllowableTableId` | `integer` | 0 | Table supplying the variation of shear allowable. |

**Example record**

~~~text
PoroElasticMatFreq;1002;1101;;;;;1102
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol108_poroelastic_trim.oos)

Reading the example gives `id = 1002`, `youngsModulusTableId = 1101`, `structuralDampingTableId = 1102`.

**Referenced records in this example**

- [IsoMat](materials.md#isomat) via `id = 1002`.

## ProgressiveFailureMat

The progressive failure properties of an orthotropic material by the Cuntze-Bold material model (2D and 3D).

**Record format and fields**

`ProgressiveFailureMat;id;failure;density;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `failure` | `text` | — | Selects or specifies the failure behavior of this material. |
| 3 | `density` | `real` | 0.0 | Mass per unit volume for a volumetric material or fluid density. |

**Keyed sections in `entries`**

Begin each section with its key, then write its fixed fields and any counted list.

**Section `Temperature`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `Unidirectional`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `WovenFabric`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `FiberDirection`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 7 | `entryValue7` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 8 | `entryValue8` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 9 | `entryValue9` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `CrossDirection`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 7 | `entryValue7` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 8 | `entryValue8` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 9 | `entryValue9` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `ThicknessDirection`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 7 | `entryValue7` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 8 | `entryValue8` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 9 | `entryValue9` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `WarpDirection`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 7 | `entryValue7` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 8 | `entryValue8` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 9 | `entryValue9` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `FiberCrossShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `CrossThicknessShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `ThicknessFiberShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `WarpFiberShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `FiberThicknessShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

**Section `ThicknessWarpShear`**

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `entryValue1` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 2 | `entryValue2` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 3 | `entryValue3` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 4 | `entryValue4` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 5 | `entryValue5` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |
| 6 | `entryValue6` | `real` | — | Positional input to the selected entry. Its interpretation is defined by the entry type or user routine. |

Accepted words: `CrossDirection`, `CrossThicknessShear`, `CuntzeBold`, `FiberCrossShear`, `FiberDirection`, `FiberThicknessShear`, `Temperature`, `ThicknessDirection`, `ThicknessFiberShear`, `ThicknessWarpShear`, `Unidirectional`, `WarpDirection`, `WarpFiberShear`, `WovenFabric`.

**Example record**

~~~text
ProgressiveFailureMat;21;CuntzeBold;1.6E-9;Unidirectional;0.1;0.1;0.1;2.5;FiberDirection;157413.;2413.;0.0135;1275.;0.2;1.55E+5;580.;0.02;62.;CrossDirection;7703.;31.8;0.0041;127.;0.2;1.E+4;199.;0.03103;47.;ThicknessDirection;7703.;31.8;0.0041;141.;0.18;10500.;300.;0.0275;47.;FiberCrossShear;4599.;70.7;0.03584;300.;0.02;0.01;CrossThicknessShear;450.;70.7;0.02584;250.;0.01;1.;ThicknessWarpShear;4599.;70.7;0.03584;300.;0.02;0.01
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_laminates_failure_gasket.oos)

Reading the example gives `id = 21`, `failure = CuntzeBold`, `density = 1.6E-9`.

## RigidMat

A rigid material (a rigid body is the elements whose properties name it).

**Record format and fields**

`RigidMat;id;density;youngsModulus;poissonRatio;mass;centerX;centerY;centerZ;inertiaXx;inertiaXy;inertiaXz;inertiaYy;inertiaYz;inertiaZz;frameId;velocityX;velocityY;velocityZ;angularVelocityX;angularVelocityY;angularVelocityZ;localCenterX;localCenterY;localCenterZ`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `density` | `real` | 1.0 | Mass per unit volume for a volumetric material or fluid density. |
| 3 | `youngsModulus` | `real` | 1.0 | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). |
| 4 | `poissonRatio` | `real` | 0.2 | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). |
| 5 | `mass` | `real` | — | Inertial mass associated with the selected component or body. |
| 6 | `centerX` | `real` | — | X coordinate of the centre. |
| 7 | `centerY` | `real` | — | Y coordinate of the centre. |
| 8 | `centerZ` | `real` | — | Z coordinate of the centre. |
| 9 | `inertiaXx` | `real` | — | Component of the inertia tensor in the Xx material or local axes. |
| 10 | `inertiaXy` | `real` | — | Component of the inertia tensor in the Xy material or local axes. |
| 11 | `inertiaXz` | `real` | — | Component of the inertia tensor in the Xz material or local axes. |
| 12 | `inertiaYy` | `real` | — | Component of the inertia tensor in the Yy material or local axes. |
| 13 | `inertiaYz` | `real` | — | Component of the inertia tensor in the Yz material or local axes. |
| 14 | `inertiaZz` | `real` | — | Component of the inertia tensor in the Zz material or local axes. |
| 15 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 16 | `velocityX` | `real` | — | Component X of the velocity vector (length per time). |
| 17 | `velocityY` | `real` | — | Component Y of the velocity vector (length per time). |
| 18 | `velocityZ` | `real` | — | Component Z of the velocity vector (length per time). |
| 19 | `angularVelocityX` | `real` | — | Component X of the angular velocity vector. |
| 20 | `angularVelocityY` | `real` | — | Component Y of the angular velocity vector. |
| 21 | `angularVelocityZ` | `real` | — | Component Z of the angular velocity vector. |
| 22 | `localCenterX` | `real` | — | X coordinate of the centre in local axes. |
| 23 | `localCenterY` | `real` | — | Y coordinate of the centre in local axes. |
| 24 | `localCenterZ` | `real` | — | Z coordinate of the centre in local axes. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `centerX` — a coordinate, an inertia or a velocity must be a finite number.

**Example record**

~~~text
RigidMat;3;7.85E-9;2.1E+5;0.3;;;;;;;;;;;;1.E+3;0.;0.;0.;0.;0.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol700_bulk_viscosity_fabric_rigid.oos)

Reading the example gives `id = 3`, `density = 7.85E-9`, `youngsModulus = 2.1E+5`, `poissonRatio = 0.3`.

## ShapeMemoryMat

A shape memory alloy.

**Record format and fields**

`ShapeMemoryMat;id;model;referenceTemperature;maximumDetwinningStrain;austeniteYoungsModulus;austenitePoissonRatio;austeniteThermalExpansion;austeniteStressLimit;austeniteDensity;transformationStartStress;transformationFinishStress;austeniteStressSlope;martensiteYoungsModulus;martensitePoissonRatio;martensiteThermalExpansion;martensiteStressLimit;martensiteDensity;reverseStartStress;reverseFinishStress;martensiteStressSlope;transformationVolumeChange;martensiteFraction;effectiveStressLimit;maximumStress;gFunction0;gFunctionA;gFunctionB;gFunctionC;gFunctionD;gFunctionE;gFunctionF;gFunctionMaximum`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `model` | `integer` | Required | Selects the constitutive model or the corresponding form of the record. |
| 3 | `referenceTemperature` | `real` | Required | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 4 | `maximumDetwinningStrain` | `real` | Required | Maximum detwinning strain (dimensionless). |
| 5 | `austeniteYoungsModulus` | `real` | 0.0 | Austenite youngs modulus (force per area). |
| 6 | `austenitePoissonRatio` | `real` | 0.0 | Relative measure of austenite poisson. |
| 7 | `austeniteThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its austenite phase. |
| 8 | `austeniteStressLimit` | `real` | 0.0 | Stress limit of the material in its austenite phase. |
| 9 | `austeniteDensity` | `real` | 0.0 | Density of the material in its austenite phase. |
| 10 | `transformationStartStress` | `real` | 0.0 | Transformation start stress (force per area). |
| 11 | `transformationFinishStress` | `real` | 0.0 | Transformation finish stress (force per area). |
| 12 | `austeniteStressSlope` | `real` | 0.0 | Stress slope of the material in its austenite phase. |
| 13 | `martensiteYoungsModulus` | `real` | 0.0 | Martensite youngs modulus (force per area). |
| 14 | `martensitePoissonRatio` | `real` | 0.0 | Relative measure of martensite poisson. |
| 15 | `martensiteThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its martensite phase. |
| 16 | `martensiteStressLimit` | `real` | 0.0 | Stress limit of the material in its martensite phase. |
| 17 | `martensiteDensity` | `real` | 0.0 | Density of the material in its martensite phase. |
| 18 | `reverseStartStress` | `real` | 0.0 | Reverse start stress (force per area). |
| 19 | `reverseFinishStress` | `real` | 0.0 | Reverse finish stress (force per area). |
| 20 | `martensiteStressSlope` | `real` | 0.0 | Stress slope of the material in its martensite phase. |
| 21 | `transformationVolumeChange` | `real` | 0.0 | Change of volume associated with phase transformation. |
| 22 | `martensiteFraction` | `real` | 0.0 | Fraction of the material in the martensitic phase. |
| 23 | `effectiveStressLimit` | `real` | 0.0 | Limiting equivalent stress for the selected material criterion. |
| 24 | `maximumStress` | `real` | 0.0 | Maximum stress (force per area). |
| 25 | `gFunction0` | `real` | 0.0 | Coefficient 0 of the material hardening function. |
| 26 | `gFunctionA` | `real` | 0.0 | Coefficient A of the material hardening function. |
| 27 | `gFunctionB` | `real` | 0.0 | Coefficient B of the material hardening function. |
| 28 | `gFunctionC` | `real` | 0.0 | Coefficient C of the material hardening function. |
| 29 | `gFunctionD` | `real` | 0.0 | Coefficient D of the material hardening function. |
| 30 | `gFunctionE` | `real` | 0.0 | Coefficient E of the material hardening function. |
| 31 | `gFunctionF` | `real` | 0.0 | Coefficient F of the material hardening function. |
| 32 | `gFunctionMaximum` | `real` | 0.0 | Upper bound of the hardening function in the constitutive relation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `austeniteYoungsModulus` — a property of the alloy must be a finite number.

**Example record**

~~~text
ShapeMemoryMat;3;1;20.;0.05;5.E+4;0.33;1.E-5;1.E+20;6.45E-9;520.;600.;8.66;5.E+4;0.33;1.E-5;1.E+20;6.45E-9;300.;200.;6.66
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_rubber_viscoelastic_sma.oos)

Reading the example gives `id = 3`, `model = 1`, `referenceTemperature = 20.`, `maximumDetwinningStrain = 0.05`.

## UserCompositeFailureMat

An orthotropic material of shell composites with its failure model and property degradation, whose failure is computed by a user subroutine.

**Record format and fields**

`UserCompositeFailureMat;id;groupName;userRoutineName;youngsModulus1;youngsModulus2;poissonRatio12;shearModulus12;shearModulus1Z;shearModulus2Z;density;historyVariableCount;shearStrength;nonlinearShearCoefficient;transverseShear;interactionTerm12;tensionStrength1;compressionStrength1;tensionStrength2;compressionStrength2;degradation;degradationParameter;degradationStart;fiberTensionTheory;fiberCompressionTheory;matrixTensionTheory;matrixCompressionTheory;matrixShearTheory;fiberTensionDegradation;fiberCompressionDegradation;matrixTensionDegradation;matrixCompressionDegradation;matrixShearDegradation`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 3 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |
| 4 | `youngsModulus1` | `real` | — | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 1. |
| 5 | `youngsModulus2` | `real` | — | Uniaxial elastic stress divided by uniaxial elastic strain (force per area). Entry 2. |
| 6 | `poissonRatio12` | `real` | — | Negative ratio of transverse strain to axial strain under uniaxial stress (dimensionless). Entry 12. |
| 7 | `shearModulus12` | `real` | — | Elastic shear stress divided by engineering shear strain (force per area). Entry 12. |
| 8 | `shearModulus1Z` | `real` | same as shearModulus12 | Elastic shear modulus in the material plane spanned by direction 1 and z (force per area). |
| 9 | `shearModulus2Z` | `real` | same as shearModulus12 | Elastic shear modulus in the material plane spanned by direction 2 and z (force per area). |
| 10 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 11 | `historyVariableCount` | `integer` | 0 | Number of history variable entries. |
| 12 | `shearStrength` | `real` | 0.0 | Limiting shear stress of the material. |
| 13 | `nonlinearShearCoefficient` | `real` | 0.0 | Coefficient in the relation for nonlinear shear. |
| 14 | `transverseShear` | `text` | — | Shear response perpendicular to the reference plane. |
| 15 | `interactionTerm12` | `real` | 0.0 | Parameter 12 of the interaction term relation for this material. |
| 16 | `tensionStrength1` | `real` | — | Strength limit in tension for material direction or entry 1 (force per area). |
| 17 | `compressionStrength1` | `real` | — | Strength limit in compression for material direction or entry 1 (force per area). |
| 18 | `tensionStrength2` | `real` | — | Strength limit in tension for material direction or entry 2 (force per area). |
| 19 | `compressionStrength2` | `real` | — | Strength limit in compression for material direction or entry 2 (force per area). |
| 20 | `degradation` | `text` | — | Reduction of material response after a damage criterion is met. |
| 21 | `degradationParameter` | `real` | — | Parameter value of the degradation parameter relation for this material. |
| 22 | `degradationStart` | `text` | — | Condition at which degradation begins. |
| 23 | `fiberTensionTheory` | `text` | — | Theory setting for the tension response of the fiber constituent. |
| 24 | `fiberCompressionTheory` | `text` | — | Theory setting for the compression response of the fiber constituent. |
| 25 | `matrixTensionTheory` | `text` | — | Theory setting for the tension response of the matrix constituent. |
| 26 | `matrixCompressionTheory` | `text` | — | Theory setting for the compression response of the matrix constituent. |
| 27 | `matrixShearTheory` | `text` | — | Theory setting for the shear response of the matrix constituent. |
| 28 | `fiberTensionDegradation` | `text` | — | Degradation setting for the tension response of the fiber constituent. |
| 29 | `fiberCompressionDegradation` | `text` | — | Degradation setting for the compression response of the fiber constituent. |
| 30 | `matrixTensionDegradation` | `text` | — | Degradation setting for the tension response of the matrix constituent. |
| 31 | `matrixCompressionDegradation` | `text` | — | Degradation setting for the compression response of the matrix constituent. |
| 32 | `matrixShearDegradation` | `text` | — | Degradation setting for the shear response of the matrix constituent. |

Accepted words: `All`, `Constant`, `Element`, `Elements`, `IndividualDegradation`, `Steps`, `SublaminateShear`, `Table`, `Time`, `Velocity`.

**Example record**

~~~text
UserCompositeFailureMat;1;excomp;EXCOMP;1.35E+5;9.E+3;0.3;5.E+3;5.E+3;3500.;1.6E-9;0;60.;;;;1500.;1200.;50.;200.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol700_user_services.oos)

Reading the example gives `id = 1`, `groupName = excomp`, `userRoutineName = EXCOMP`, `youngsModulus1 = 1.35E+5`.

## UserMat

The generic properties of a user defined material (hypoelastic or user material model); the [UserMatService](materials.md#usermatservice) card with the same ID activates the user subroutine.

**Record format and fields**

`UserMat;id;userFrameFlag;kinematicQuantities;density;thermalExpansion1;thermalExpansion2;thermalExpansion3;referenceTemperature;structuralDamping;tensionAllowable;compressionAllowable;shearAllowable`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the material namespace. |
| 2 | `userFrameFlag` | `integer` | 0 | Selects the user frame flag for UserMat. |
| 3 | `kinematicQuantities` | `integer` | 0 | Selects the kinematic measures used in the constitutive evaluation. |
| 4 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `thermalExpansion1` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 1. |
| 6 | `thermalExpansion2` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 2. |
| 7 | `thermalExpansion3` | `real` | — | Coefficient relating free thermal strain to a temperature change (inverse temperature). Entry 3. |
| 8 | `referenceTemperature` | `real` | 0.0 | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 9 | `structuralDamping` | `real` | 0.0 | Structural damping coefficient for the associated material or property. |
| 10 | `tensionAllowable` | `real` | 0.0 | Allowable tensile stress, in force per area. |
| 11 | `compressionAllowable` | `real` | 0.0 | Allowable compressive stress, in force per area. |
| 12 | `shearAllowable` | `real` | 0.0 | Allowable shear stress, in force per area. |

**Example record**

~~~text
UserMat;1;0;1;2.7E-9;2.3E-5;;;20.
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `id = 1`, `userFrameFlag = 0`, `kinematicQuantities = 1`, `density = 2.7E-9`.

## UserMatService

Associates a material with its user-supplied constitutive routine.

**Record format and fields**

`UserMatService;id;materialCardType;groupName;userRoutineName;<keyed sections>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `materialCardType` | `text` | — | Selects the material card type for UserMatService. |
| 3 | `groupName` | `text` | — | Text identifier selecting or naming the associated group. |
| 4 | `userRoutineName` | `text` | — | Name used to identify the user-supplied routine. |

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

**Repeated group `texts`**. Give the number of entries before their values.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `textData` | `text` | — | Payload passed in the declared type and order to the consumer of the record. |

Accepted words: `IntegerBlock`, `RealBlock`, `TextBlock`.

**Example record**

~~~text
UserMatService;1;UserMat;MATERIAL;HYPELA2;RealBlock;2;7.E+4;0.33
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `id = 1`, `materialCardType = UserMat`, `groupName = MATERIAL`, `userRoutineName = HYPELA2`.

**Referenced records in this example**

- [UserMat](materials.md#usermat) via `id = 1`.

## UserMatTable

The table variation of the properties of a [UserMat](materials.md#usermat).

**Record format and fields**

`UserMatTable;id;densityTableId;thermalExpansion1TableId;thermalExpansion2TableId;thermalExpansion3TableId;structuralDampingTableId;tensionAllowableTableId;compressionAllowableTableId;shearAllowableTableId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `densityTableId` | `integer` | 0 | Identifier of the table supplying density as a function of its independent variable. |
| 3 | `thermalExpansion1TableId` | `integer` | — | Table supplying the variation of thermal expansion 1. |
| 4 | `thermalExpansion2TableId` | `integer` | — | Table supplying the variation of thermal expansion 2. |
| 5 | `thermalExpansion3TableId` | `integer` | — | Table supplying the variation of thermal expansion 3. |
| 6 | `structuralDampingTableId` | `integer` | 0 | Identifier of the table supplying the structural damping coefficient. |
| 7 | `tensionAllowableTableId` | `integer` | 0 | Table supplying the variation of tension allowable. |
| 8 | `compressionAllowableTableId` | `integer` | 0 | Table supplying the variation of compression allowable. |
| 9 | `shearAllowableTableId` | `integer` | 0 | Table supplying the variation of shear allowable. |

**Example record**

~~~text
UserMatTable;1;31;32
~~~

[Model containing this record](../../../validation/models/read_only_user_defined/sol400_user_services.oos)

Reading the example gives `id = 1`, `densityTableId = 31`, `thermalExpansion1TableId = 32`.

**Referenced records in this example**

- [UserMat](materials.md#usermat) via `id = 1`.

## ViscoElasticMat

The viscoelastic properties of a material as a Prony series (it extends an [IsoMat](materials.md#isomat), [AxisymOrthoMat](materials.md#axisymorthomat), [OrthoMat2D](materials.md#orthomat2d), [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) or [HyperelasticMat](materials.md#hyperelasticmat)).

**Record format and fields**

Forms: `linearIsotropic`, `orthotropic`, `fiveTerms`, `termLines`.

### ViscoElasticMat: linearIsotropic

Form `linearIsotropic`, when `model` is `IsotropicLinear`.

`ViscoElasticMat;id;model;shortTimeShearModulus;longTimeShearModulus;decayConstant;viscosity`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `model` | `text` | IsotropicForm1 | Selects the constitutive model or the corresponding form of the record. |
| 3 | `shortTimeShearModulus` | `real` | 0.0 | Short time shear modulus (force per area). |
| 4 | `longTimeShearModulus` | `real` | 0.0 | Long time shear modulus (force per area). |
| 5 | `decayConstant` | `real` | 0.0 | Controls the decay of the corresponding term in the material response. |
| 6 | `viscosity` | `real` | 0.0 | Viscous response coefficient in the selected constitutive or flow law. |

### ViscoElasticMat: orthotropic

Form `orthotropic`, when `model` is `OrthotropicForm`.

`ViscoElasticMat;id;model;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `model` | `text` | IsotropicForm1 | Selects the constitutive model or the corresponding form of the record. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `deviatoricRelaxationTime` | `real` | — | Deviatoric relaxation time (time). |
| 2 | `youngsModulusX` | `real` | — | Uniaxial elastic modulus (force per area) in the X material or local axes. |
| 3 | `youngsModulusY` | `real` | — | Uniaxial elastic modulus (force per area) in the Y material or local axes. |
| 4 | `youngsModulusZ` | `real` | — | Uniaxial elastic modulus (force per area) in the Z material or local axes. |
| 5 | `poissonRatioXY` | `real` | — | Transverse contraction ratio in the XY material or local axes. |
| 6 | `poissonRatioYZ` | `real` | — | Transverse contraction ratio in the YZ material or local axes. |
| 7 | `poissonRatioZX` | `real` | — | Transverse contraction ratio in the ZX material or local axes. |
| 8 | `shearModulusXY` | `real` | — | Shear modulus (force per area) in the XY material or local axes. |
| 9 | `shearModulusYZ` | `real` | — | Shear modulus (force per area) in the YZ material or local axes. |
| 10 | `shearModulusZX` | `real` | — | Shear modulus (force per area) in the ZX material or local axes. |

### ViscoElasticMat: fiveTerms

Form `fiveTerms`, when `model` is `IsotropicForm`, `MooneyRivlin`, `Ogden`, `Foam`.

`ViscoElasticMat;id;model;solidThermalExpansion;liquidThermalExpansion;shearModulus1;deviatoricRelaxationTime1;bulkModulus1;volumetricRelaxationTime1;shearModulus2;deviatoricRelaxationTime2;bulkModulus2;volumetricRelaxationTime2;shearModulus3;deviatoricRelaxationTime3;bulkModulus3;volumetricRelaxationTime3;shearModulus4;deviatoricRelaxationTime4;bulkModulus4;volumetricRelaxationTime4;shearModulus5;deviatoricRelaxationTime5;bulkModulus5;volumetricRelaxationTime5`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `model` | `text` | IsotropicForm1 | Selects the constitutive model or the corresponding form of the record. |
| 3 | `solidThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its solid phase. |
| 4 | `liquidThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its liquid phase. |
| 5 | `shearModulus1` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 1. |
| 6 | `deviatoricRelaxationTime1` | `real` | 0.0 | Deviatoric relaxation time 1 (time). |
| 7 | `bulkModulus1` | `real` | 0.0 | Resistance to volumetric compression, expressed as pressure. Entry 1. |
| 8 | `volumetricRelaxationTime1` | `real` | 0.0 | Volumetric relaxation time 1 (time). |
| 9 | `shearModulus2` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 2. |
| 10 | `deviatoricRelaxationTime2` | `real` | 0.0 | Deviatoric relaxation time 2 (time). |
| 11 | `bulkModulus2` | `real` | 0.0 | Resistance to volumetric compression, expressed as pressure. Entry 2. |
| 12 | `volumetricRelaxationTime2` | `real` | 0.0 | Volumetric relaxation time 2 (time). |
| 13 | `shearModulus3` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 3. |
| 14 | `deviatoricRelaxationTime3` | `real` | 0.0 | Deviatoric relaxation time 3 (time). |
| 15 | `bulkModulus3` | `real` | 0.0 | Resistance to volumetric compression, expressed as pressure. Entry 3. |
| 16 | `volumetricRelaxationTime3` | `real` | 0.0 | Volumetric relaxation time 3 (time). |
| 17 | `shearModulus4` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 4. |
| 18 | `deviatoricRelaxationTime4` | `real` | 0.0 | Deviatoric relaxation time 4 (time). |
| 19 | `bulkModulus4` | `real` | 0.0 | Resistance to volumetric compression, expressed as pressure. Entry 4. |
| 20 | `volumetricRelaxationTime4` | `real` | 0.0 | Volumetric relaxation time 4 (time). |
| 21 | `shearModulus5` | `real` | 0.0 | Elastic shear stress divided by engineering shear strain (force per area). Entry 5. |
| 22 | `deviatoricRelaxationTime5` | `real` | 0.0 | Deviatoric relaxation time 5 (time). |
| 23 | `bulkModulus5` | `real` | 0.0 | Resistance to volumetric compression, expressed as pressure. Entry 5. |
| 24 | `volumetricRelaxationTime5` | `real` | 0.0 | Volumetric relaxation time 5 (time). |

### ViscoElasticMat: termLines

Form `termLines`, for every other record.

`ViscoElasticMat;id;model;solidThermalExpansion;liquidThermalExpansion;<terms>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `model` | `text` | IsotropicForm1 | Selects the constitutive model or the corresponding form of the record. |
| 3 | `solidThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its solid phase. |
| 4 | `liquidThermalExpansion` | `real` | 0.0 | Thermal expansion of the material in its liquid phase. |

**Repeated group `terms`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `shearModulus` | `real` | — | Elastic shear stress divided by engineering shear strain (force per area). |
| 2 | `deviatoricRelaxationTime` | `real` | — | Deviatoric relaxation time (time). |
| 3 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |
| 4 | `volumetricRelaxationTime` | `real` | — | Volumetric relaxation time (time). |

Accepted words: `Foam`, `FoamMaterial1`, `IsotropicForm`, `IsotropicForm1`, `IsotropicLinear`, `Linear`, `MooneyRivlin`, `MooneyRivlinModel1`, `Ogden`, `OgdenModel1`, `OrthotropicForm`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `shearModulus` — the values of a term must be finite numbers.

**Example record**

~~~text
ViscoElasticMat;2;IsotropicForm1;;;500.;0.2
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_rubber_viscoelastic_sma.oos)

## ViscoElasticMatTemperature

The temperature dependent viscoelastic properties of the material of the [ViscoElasticMat](materials.md#viscoelasticmat) with the same ID.

**Record format and fields**

`ViscoElasticMatTemperature;id;shiftFunction;shiftReferenceTemperature;activationEnergy;structuralFraction;temperatureDifference;referenceTemperature;termCount;wlfConstant1;wlfConstant2;<series>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `shiftFunction` | `text` | WilliamsLandelFerry | Selects the shift relation used to move between material response curves. |
| 3 | `shiftReferenceTemperature` | `real` | 0.0 | Shift reference temperature (temperature). |
| 4 | `activationEnergy` | `real` | — | Energy barrier in the temperature-dependent rate law. |
| 5 | `structuralFraction` | `real` | — | Fraction assigned to the structural constituent. |
| 6 | `temperatureDifference` | `real` | — | Thermal increment measured relative to the reference state. |
| 7 | `referenceTemperature` | `real` | — | Temperature defining the reference state for these data, in the model’s temperature scale. |
| 8 | `termCount` | `integer` | 0 | Number of term entries. |
| 9 | `wlfConstant1` | `real` | 0.0 | Coefficient 1 in the temperature shift relation for viscoelastic response. |
| 10 | `wlfConstant2` | `real` | 0.0 | Coefficient 2 in the temperature shift relation for viscoelastic response. |

**Repeated group `series`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `seriesTerm` | `number` | — | Contribution at the indicated order of the material expansion. |

Accepted words: `Narayanaswamy`, `PowerLaw`, `User`, `WilliamsLandelFerry`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `shiftReferenceTemperature` — a temperature, a constant or a coefficient must be a finite number.

**Example record**

~~~text
ViscoElasticMatTemperature;1;WilliamsLandelFerry;20.;;;;;;17.44;51.6
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_rubber_viscoelastic_sma.oos)

Reading the example gives `id = 1`, `shiftFunction = WilliamsLandelFerry`, `shiftReferenceTemperature = 20.`, `wlfConstant1 = 17.44`.

## ViscoPlasticMat

The viscoplastic or creep properties of the material of the [IsoMat](materials.md#isomat), [AnisoMat2D](materials.md#anisomat2d), [OrthoMat3DNonlinear](materials.md#orthomat3dnonlinear) or [AnisoMat3D](materials.md#anisomat3d) with the same ID.

**Record format and fields**

Forms: `anand`, `powerLaw`.

### ViscoPlasticMat: anand

Form `anand`, when `model` is `AnandModel`.

`ViscoPlasticMat;id;model;preExponentialFactor;activationEnergy;stressMultiplier;strainRateSensitivity;saturationCoefficient;saturationRateSensitivity;hardeningConstant;hardeningSensitivity;initialDeformationResistance`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `model` | `text` | — | Selects the constitutive model or the corresponding form of the record. |
| 3 | `preExponentialFactor` | `real` | — | Multiplier for pre exponential. |
| 4 | `activationEnergy` | `real` | — | Energy barrier in the temperature-dependent rate law. |
| 5 | `stressMultiplier` | `real` | — | Factor applied to the stress in the response relation. |
| 6 | `strainRateSensitivity` | `real` | — | Dependence of the constitutive response on strain rate. |
| 7 | `saturationCoefficient` | `real` | — | Coefficient in the relation for saturation. |
| 8 | `saturationRateSensitivity` | `real` | — | Sensitivity of the approach to saturation in the material law. |
| 9 | `hardeningConstant` | `real` | — | Coefficient controlling the evolution of strength during hardening. |
| 10 | `hardeningSensitivity` | `real` | — | Sensitivity of the hardening law to its driving variable. |
| 11 | `initialDeformationResistance` | `real` | — | Resistance to inelastic deformation at the initial state. |

### ViscoPlasticMat: powerLaw

Form `powerLaw`, for every other record.

`ViscoPlasticMat;id;rateCoefficient;rateTableId;stressExponent;strainExponent;temperatureExponent;timeExponent;userSubroutineFlag`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `rateCoefficient` | `real` | 0.0 | Coefficient in the relation for rate. |
| 3 | `rateTableId` | `integer` | 0 | Identifier addressing multi dimensional table data. |
| 4 | `stressExponent` | `real` | 0.0 | Power in the law for stress. |
| 5 | `strainExponent` | `real` | 0.0 | Power in the law for strain. |
| 6 | `temperatureExponent` | `real` | 0.0 | Power in the law for temperature. |
| 7 | `timeExponent` | `real` | 0.0 | Power in the law for time. |
| 8 | `userSubroutineFlag` | `integer` | 0 | Selects the user subroutine flag for ViscoPlasticMat. |

Accepted words: `AnandModel`.

**Example record**

~~~text
ViscoPlasticMat;3;1.;31;3.
~~~

[Model containing this record](../../../validation/models/nonlinear_materials/sol400_plasticity_creep_tables.oos)
