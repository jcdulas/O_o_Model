# Heat transfer

[All card families and alphabetical index](../../model-format-cards.md)

Read field positions from left to right within each table. A dash means the layout supplies no fixed default. Use a consistent system of units for dimensional quantities.

## AcousticAbsorber

A frequency-dependent acoustic absorber element on the fluid-structure boundary.

**Record format and fields**

`AcousticAbsorber;id;propId;node1;node2;node3;node4`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | same as id | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | Required | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | 0 | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | 0 | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | 0 | Grid point to which this entry applies. Entry 4. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node` — a grid point ID cannot be negative.

**Example record**

~~~text
AcousticAbsorber;401;31;1001;1101;1106;1006
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 401`, `propId = 31`, `node1 = 1001`, `node2 = 1101`.

**Referenced records in this example**

- [AcousticAbsorberProp](elements.md#acousticabsorberprop) via `propId = 31`.

## AcousticAbsorberBrickProp

The property of an [AcousticAbsorberHexa](thermal.md#acousticabsorberhexa) acoustic absorber element.

**Record format and fields**

`AcousticAbsorberBrickProp;id;synthesize;resistanceTableId;reactanceTableId;weightingTableId;reservedValue;cutoffFrequency;damping;stiffness;mass`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `synthesize` | `text` | — | Selects between an equivalent response derived from tables and directly supplied coefficients. |
| 3 | `resistanceTableId` | `integer` | 0 | Table defining the resistive part of the acoustic response. |
| 4 | `reactanceTableId` | `integer` | 0 | Table defining the reactive part of the acoustic response. |
| 5 | `weightingTableId` | `integer` | 0 | Optional frequency weighting table used in coefficient synthesis. |
| 6 | `reservedValue` | `real` | — | Optional value retained at a reserved position when the record is read and written. |
| 7 | `cutoffFrequency` | `real` | — | Frequency at which the specified range of the response ends (inverse time). |
| 8 | `damping` | `real` | — | Equivalent damping per unit surface area. |
| 9 | `stiffness` | `real` | — | Equivalent stiffness per unit surface area. |
| 10 | `mass` | `real` | — | Equivalent mass per unit surface area. |

Accepted words: `No`, `Yes`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.
- `resistanceTableId` — a table ID cannot be negative.

**Example record**

~~~text
AcousticAbsorberBrickProp;21;No;;;;;;1.E-6;0.01;3.E-10
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 21`, `synthesize = No`, `damping = 1.E-6`, `stiffness = 0.01`.

## AcousticAbsorberHexa

An acoustic absorber element, a brick of the coupled fluid-structure analysis.

**Record format and fields**

`AcousticAbsorberHexa;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node17;node18;node19;node20`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node17` | `integer` | — | Grid point to which this entry applies. Entry 17. |
| 16 | `node18` | `integer` | — | Grid point to which this entry applies. Entry 18. |
| 17 | `node19` | `integer` | — | Grid point to which this entry applies. Entry 19. |
| 18 | `node20` | `integer` | — | Grid point to which this entry applies. Entry 20. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node` — a grid point ID cannot be negative.
- `node` — a grid point is repeated in the element.

**Example record**

~~~text
AcousticAbsorberHexa;301;21;101;102;107;106;501;502;507;506
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 301`, `propId = 21`, `node1 = 101`, `node2 = 102`.

**Referenced records in this example**

- [AcousticAbsorberBrickProp](thermal.md#acousticabsorberbrickprop) via `propId = 21`.

## AcousticBarrierHexa

An acoustic barrier element, a brick of the coupled fluid-structure analysis.

**Record format and fields**

`AcousticBarrierHexa;id;propId;node1;node2;node3;node4;node5;node6;node7;node8;node9;node10;node11;node12;node17;node18;node19;node20`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `node1` | `integer` | — | Grid point to which this entry applies. Entry 1. |
| 4 | `node2` | `integer` | — | Grid point to which this entry applies. Entry 2. |
| 5 | `node3` | `integer` | — | Grid point to which this entry applies. Entry 3. |
| 6 | `node4` | `integer` | — | Grid point to which this entry applies. Entry 4. |
| 7 | `node5` | `integer` | — | Grid point to which this entry applies. Entry 5. |
| 8 | `node6` | `integer` | — | Grid point to which this entry applies. Entry 6. |
| 9 | `node7` | `integer` | — | Grid point to which this entry applies. Entry 7. |
| 10 | `node8` | `integer` | — | Grid point to which this entry applies. Entry 8. |
| 11 | `node9` | `integer` | — | Grid point to which this entry applies. Entry 9. |
| 12 | `node10` | `integer` | — | Grid point to which this entry applies. Entry 10. |
| 13 | `node11` | `integer` | — | Grid point to which this entry applies. Entry 11. |
| 14 | `node12` | `integer` | — | Grid point to which this entry applies. Entry 12. |
| 15 | `node17` | `integer` | — | Grid point to which this entry applies. Entry 17. |
| 16 | `node18` | `integer` | — | Grid point to which this entry applies. Entry 18. |
| 17 | `node19` | `integer` | — | Grid point to which this entry applies. Entry 19. |
| 18 | `node20` | `integer` | — | Grid point to which this entry applies. Entry 20. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the property ID must be a positive integer.
- `node` — a grid point ID cannot be negative.
- `node` — a grid point is repeated in the element.

**Example record**

~~~text
AcousticBarrierHexa;309;22;111;112;117;116;511;512;517;516
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 309`, `propId = 22`, `node1 = 111`, `node2 = 112`.

**Referenced records in this example**

- [AcousticBarrierProp](thermal.md#acousticbarrierprop) via `propId = 22`.

## AcousticBarrierProp

The property of an [AcousticBarrierHexa](thermal.md#acousticbarrierhexa) acoustic barrier element.

**Record format and fields**

`AcousticBarrierProp;id;backingMass;septumMass;resonanceFrequency;resonanceStiffness`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the property namespace. |
| 2 | `backingMass` | `real` | Required | Mass assigned to the backing layer of the acoustic treatment. |
| 3 | `septumMass` | `real` | Required | Mass assigned to the separating septum in the acoustic treatment. |
| 4 | `resonanceFrequency` | `real` | — | Resonance frequency (inverse time). |
| 5 | `resonanceStiffness` | `real` | — | Stiffness governing the resonant response of the acoustic layer. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
AcousticBarrierProp;22;2.E-9;1.E-9;300.
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

Reading the example gives `id = 22`, `backingMass = 2.E-9`, `septumMass = 1.E-9`, `resonanceFrequency = 300.`.

## AcousticSlotBoundary

The list of the [AcousticSlotSurfacePoint](nodes.md#acousticslotsurfacepoint) slot points on the boundary of a slot cavity with the axisymmetric fluid cavity.

**Record format and fields**

`AcousticSlotBoundary;density;slotCount;<slotPoints>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 2 | `slotCount` | `integer` | — | Number of slot entries. |

**Repeated group `slotPoints`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `slotPoint` | `integer` | — | Point defining the location on the acoustic slot. |

Accepted words: `Constant`, `Element`, `Table`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `slotPoint2` — the card needs at least two slot points.

**Example record**

~~~text
AcousticSlotBoundary;;;21;22;23
~~~

[Model containing this record](../../../validation/models/acoustics/cavity_slots_sol103.oos)

## AxisymFluid2

Defines an axisymmetric fluid element generated by revolving a two-corner cross-section.

**Record format and fields**

`AxisymFluid2;id;fluidPointId1;fluidPointId2;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | — | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | — | Identifier selecting the fluid point record or set. |
| 4 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `fluidPointId` — a fluid point ID must be between 1 and 499999.
- `fluidPointId` — the rings of an element are different.

**Example record**

~~~text
AxisymFluid2;101;1;3
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 101`, `fluidPointId1 = 1`, `fluidPointId2 = 3`.

## AxisymFluid3

Defines an axisymmetric fluid element generated by revolving a triangular cross-section.

**Record format and fields**

`AxisymFluid3;id;fluidPointId1;fluidPointId2;fluidPointId3;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | — | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | — | Identifier selecting the fluid point record or set. |
| 4 | `fluidPointId3` | `integer` | — | Identifier selecting the fluid point record or set. |
| 5 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 6 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `fluidPointId` — a fluid point ID must be between 1 and 499999.
- `fluidPointId` — the rings of an element are different.

**Example record**

~~~text
AxisymFluid3;104;3;4;6
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 104`, `fluidPointId1 = 3`, `fluidPointId2 = 4`, `fluidPointId3 = 6`.

## AxisymFluid4

Defines an axisymmetric fluid element generated by revolving a quadrilateral cross-section.

**Record format and fields**

`AxisymFluid4;id;fluidPointId1;fluidPointId2;fluidPointId3;fluidPointId4;density;bulkModulus`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the element namespace. |
| 2 | `fluidPointId1` | `integer` | — | Identifier selecting the fluid point record or set. |
| 3 | `fluidPointId2` | `integer` | — | Identifier selecting the fluid point record or set. |
| 4 | `fluidPointId3` | `integer` | — | Identifier selecting the fluid point record or set. |
| 5 | `fluidPointId4` | `integer` | — | Identifier selecting the fluid point record or set. |
| 6 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |
| 7 | `bulkModulus` | `real` | — | Resistance to volumetric compression, expressed as pressure. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `fluidPointId` — a fluid point ID must be between 1 and 499999.
- `fluidPointId` — the rings of an element are different.

**Example record**

~~~text
AxisymFluid4;103;1;2;4;3
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `id = 103`, `fluidPointId1 = 1`, `fluidPointId2 = 2`, `fluidPointId3 = 4`.

## AxisymFluidBoundaryList

The fluid points ([AxisymFluidRing](nodes.md#axisymfluidring)) of the boundary between an axisymmetric fluid and a structure.

**Record format and fields**

`AxisymFluidBoundaryList;density;<fluidPoints>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |

**Repeated group `fluidPoints`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fluidPointId` | `any` | — | Identifier selecting the fluid point record or set. |

Accepted words: `Axis`, `LocalAxis`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `fluidPointId` — the card needs at least one fluid point.
- `fluidPointId` — a fluid point ID must be a positive integer.

**Example record**

~~~text
AxisymFluidBoundaryList;0.;11;12;13
~~~

[Model containing this record](../../../validation/models/linear_elements/fluid_boundary_gridb_modes.oos)

Reading the example gives `density = 0.`.

## AxisymFluidFreeSurface

The fluid points ([AxisymFluidRing](nodes.md#axisymfluidring)) of a free surface boundary of an axisymmetric fluid model.

**Record format and fields**

`AxisymFluidFreeSurface;density;<fluidPoints>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `density` | `real` | — | Mass per unit volume for a volumetric material or fluid density. |

**Repeated group `fluidPoints`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `fluidPointId` | `any` | — | Identifier selecting the fluid point record or set. |

Accepted words: `Axis`, `LocalAxis`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `fluidPointId` — the card needs at least one fluid point.
- `fluidPointId` — a fluid point ID must be a positive integer.

**Example record**

~~~text
AxisymFluidFreeSurface;;Axis;5;6
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

## AxisymFluidSymmetry

The symmetry of the structural boundary of an axisymmetric fluid model.

**Record format and fields**

`AxisymFluidSymmetry;sectionCount;planeSymmetry1;planeSymmetry2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `sectionCount` | `integer` | Required | Number of section entries. |
| 2 | `planeSymmetry1` | `text` | — | Symmetry condition on reference plane 1 in the fluid model. |
| 3 | `planeSymmetry2` | `text` | — | Symmetry condition on reference plane 2 in the fluid model. |

Accepted words: `Antisymmetric`, `Symmetric`.

**Example record**

~~~text
AxisymFluidSymmetry;4;Symmetric;Symmetric
~~~

[Model containing this record](../../../validation/models/acoustics/hydroelastic_tank_sol103.oos)

Reading the example gives `sectionCount = 4`, `planeSymmetry1 = Symmetric`, `planeSymmetry2 = Symmetric`.

## FluidMassElemList

A list of [ShellQuad4](elements.md#shellquad4) and [ShellTria3](elements.md#shelltria3) elements for the virtual fluid mass of a [FluidVirtualMass](thermal.md#fluidvirtualmass).

**Record format and fields**

`FluidMassElemList;id;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `Constant`, `Element`, `Table`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `elemId1` — the card needs at least one element.
- `elemId1` — an element ID must not be zero (a minus sign gives the wetted side).

**Example record**

~~~text
FluidMassElemList;1;1;Through;4;-11;Through;-18;-21;Through;-28
~~~

[Model containing this record](../../../validation/models/acoustics/virtual_fluid_mass_sol103.oos)

Reading the example gives `id = 1`.

## FluidStructureInterface

Fluid-structure interface parameters.

**Record format and fields**

`FluidStructureInterface;interfaceKind;interfaceInput;fluidSetId;structureSetId;normalTolerance;methodName;skinTolerance;skinToleranceIncrement;interfaceTolerance;wholeStructureSet;searchUnit`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `interfaceKind` | `text` | — | Selects the interface kind for FluidStructureInterface. |
| 2 | `interfaceInput` | `text` | — | Selects the input data supplied at the coupled interface. |
| 3 | `fluidSetId` | `integer` | 0 | Identifier addressing set data. |
| 4 | `structureSetId` | `integer` | 0 | Identifier addressing set data. |
| 5 | `normalTolerance` | `real` | — | Permitted numerical deviation for normal. |
| 6 | `methodName` | `text` | SurfaceCoupling | Text naming the method. |
| 7 | `skinTolerance` | `real` | 0.5 | Permitted numerical deviation for skin. |
| 8 | `skinToleranceIncrement` | `real` | 0.75 | Increment applied to the skin tolerance in the surface search. |
| 9 | `interfaceTolerance` | `real` | 0.5 | Permitted numerical deviation for interface. |
| 10 | `wholeStructureSet` | `text` | — | Set containing all structural entities used in this coupling. |
| 11 | `searchUnit` | `text` | — | Logical unit or search setting used by the associated integration routine. |

Accepted words: `Absolute`, `All`, `ClosedPressure`, `DifferenceForm`, `ElemsList`, `IdenticalMesh`, `No`, `NodesList`, `None`, `Relative`, `ScaledSurfaceCoupling`, `SurfaceCoupling`, `Yes`.

**Example record**

~~~text
FluidStructureInterface;DifferenceForm;None;;;0.5;SurfaceCoupling;0.5;0.75;0.5;No;Absolute
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_1d_sol111.oos)

Reading the example gives `interfaceKind = DifferenceForm`, `interfaceInput = None`, `normalTolerance = 0.5`, `methodName = SurfaceCoupling`.

## FluidStructurePanels

Panels of the structure for the panel participation of a coupled fluid-structure analysis.

**Record format and fields**

`FluidStructurePanels;<panels>`

This part of the record has no fixed fields.

**Repeated group `panels`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `panelName` | `text` | — | Text naming the panel. |
| 2 | `panelSetId` | `integer` | — | Identifier addressing set data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `panelName` — the card needs at least one panel.
- `panelSetId` — the card has one set ID for each name.
- `panelName` — the name of a panel cannot be blank.
- `panelSetId` — a set ID must be a positive integer.

**Example record**

~~~text
FluidStructurePanels;FLOOR;41
~~~

[Model containing this record](../../../validation/models/acoustics/absorbers_barriers_sol108.oos)

## FluidVirtualMass

The properties of an incompressible fluid volume, for the virtual mass matrix.

**Record format and fields**

`FluidVirtualMass;id;frameId;freeSurfaceZ;density;oneSideElemListId;bothSidesElemListId;planeSymmetry1;planeSymmetry2;characteristicLength;exactIntegrationRatio`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `frameId` | `integer` | 0 | Coordinate system in which this entry is expressed. |
| 3 | `freeSurfaceZ` | `real` | — | Vertical coordinate of the free surface in the specified frame. |
| 4 | `density` | `real` | Required | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `oneSideElemListId` | `integer` | 0 | Identifier addressing element list data. |
| 6 | `bothSidesElemListId` | `integer` | 0 | Identifier addressing element list data. |
| 7 | `planeSymmetry1` | `text` | — | Symmetry condition on reference plane 1 in the fluid model. |
| 8 | `planeSymmetry2` | `text` | — | Symmetry condition on reference plane 2 in the fluid model. |
| 9 | `characteristicLength` | `real` | 1.0e10 | Characteristic length (length). |
| 10 | `exactIntegrationRatio` | `real` | 1.0e-15 | Relative measure of exact integration. |

Accepted words: `Antisymmetric`, `NoSymmetry`, `Symmetric`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the set ID must be a positive integer.
- `oneSideElemListId` — an element list ID cannot be negative.

**Example record**

~~~text
FluidVirtualMass;1;;80.;1.E-9;1;;NoSymmetry;NoSymmetry
~~~

[Model containing this record](../../../validation/models/acoustics/virtual_fluid_mass_sol103.oos)

Reading the example gives `id = 1`, `freeSurfaceZ = 80.`, `density = 1.E-9`, `oneSideElemListId = 1`.

## ForcedConvection

Applies forced convection to a tube-type heat-transfer surface.

**Record format and fields**

`ForcedConvection;id;convectionPropId;filmNode;massFlowNode;ambientNode1;ambientNode2;massFlowFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `convectionPropId` | `integer` | Required | Identifier addressing forced convection property data. |
| 3 | `filmNode` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `massFlowNode` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 5 | `ambientNode1` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `ambientNode2` | `integer` | same as ambientNode1 | Identifier addressing scalar or grid point data. |
| 7 | `massFlowFactor` | `real` | 1.0 | Multiplier for mass flow. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the surface element ID must be a positive integer.
- `convectionPropId` — the forced convection property ID must be a positive integer.

**Example record**

~~~text
ForcedConvection;21;22;;;11;12;1.E-5
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 21`, `convectionPropId = 22`, `ambientNode1 = 11`, `ambientNode2 = 12`.

**Referenced records in this example**

- [HeatSurfaceProperty](thermal.md#heatsurfaceproperty) via `id = 21`.

## ForcedConvectionProp

The forced convection property of the surface elements a [ForcedConvection](thermal.md#forcedconvection) names.

**Record format and fields**

`ForcedConvectionProp;id;matId;matrixForm;massFlowConvection;coefficient;reynoldsExponent;prandtlExponentInner;prandtlExponentOuter`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | Required | Material identifier used to retrieve the constitutive data. |
| 3 | `matrixForm` | `integer` | 0 | Matrix organization, including the assumed relation between its rows and columns. |
| 4 | `massFlowConvection` | `integer` | 0 | Controls the contribution of convective transport associated with mass flow. |
| 5 | `coefficient` | `real` | Required | Coefficient value in the ForcedConvectionProp relation. |
| 6 | `reynoldsExponent` | `real` | 0.0 | Power in the law for reynolds. |
| 7 | `prandtlExponentInner` | `real` | 0.0 | Exponent on the Prandtl number in the inner convection correlation. |
| 8 | `prandtlExponentOuter` | `real` | 0.0 | Exponent on the Prandtl number in the outer convection correlation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the convection property ID must be a positive integer.
- `matId` — the material ID must be a positive integer.

**Example record**

~~~text
ForcedConvectionProp;22;3;1;1;0.023;0.8;0.4;0.3
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 22`, `matId = 3`, `matrixForm = 1`, `massFlowConvection = 1`.

**Referenced records in this example**

- [HeatIsoMat](thermal.md#heatisomat) via `matId = 3`.

## FreeConvection

The free convection boundary condition of a surface element.

**Record format and fields**

`FreeConvection;id;convectionPropId;filmNode;controlNode;ambientNode1;ambientNode2;ambientNode3;ambientNode4;ambientNode5;ambientNode6;ambientNode7;ambientNode8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `convectionPropId` | `integer` | Required | Identifier addressing convection property data. |
| 3 | `filmNode` | `integer` | 0 | Identifier addressing scalar or grid point data. |
| 4 | `controlNode` | `integer` | 0 | Identifier of the grid point through which this definition is controlled. |
| 5 | `ambientNode1` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 6 | `ambientNode2` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 2. |
| 7 | `ambientNode3` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 3. |
| 8 | `ambientNode4` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 4. |
| 9 | `ambientNode5` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 5. |
| 10 | `ambientNode6` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 6. |
| 11 | `ambientNode7` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 7. |
| 12 | `ambientNode8` | `integer` | same as ambientNode1 | Grid or scalar point supplying ambient temperature for boundary term 8. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the surface element ID must be a positive integer.
- `convectionPropId` — the free convection property ID must be a positive integer.

**Example record**

~~~text
FreeConvection;41;43;;;99
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 41`, `convectionPropId = 43`, `ambientNode1 = 99`.

**Referenced records in this example**

- [HeatSurfaceSide](thermal.md#heatsurfaceside) via `id = 41`.

## FreeConvectionProp

The free convection property of the surface elements a [FreeConvection](thermal.md#freeconvection) names.

**Record format and fields**

Forms: `coefficients`, `standard`.

### FreeConvectionProp: coefficients

Form `coefficients`, when `formulaKind` is `3`.

`FreeConvectionProp;id;matId;matrixForm;convectionExponent;formulaKind;convectionCoefficient1;convectionCoefficient2;convectionCoefficient3;convectionCoefficient4;convectionCoefficient5;convectionCoefficient6;convectionCoefficient7;convectionCoefficient8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `matrixForm` | `integer` | 0 | Matrix organization, including the assumed relation between its rows and columns. |
| 4 | `convectionExponent` | `real` | 0.0 | Power in the law for convection. |
| 5 | `formulaKind` | `integer` | 0 | Selects the formula kind for FreeConvectionProp. |
| 6 | `convectionCoefficient1` | `real` | Required | Coefficient in the relation for convection. |
| 7 | `convectionCoefficient2` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 8 | `convectionCoefficient3` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 9 | `convectionCoefficient4` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 10 | `convectionCoefficient5` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 11 | `convectionCoefficient6` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 12 | `convectionCoefficient7` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |
| 13 | `convectionCoefficient8` | `real` | same as convectionCoefficient1 | Coefficient in the relation for convection. |

### FreeConvectionProp: standard

Form `standard`, for every other record.

`FreeConvectionProp;id;matId;matrixForm;convectionExponent;formulaKind;tableId;characteristicLength;inletNode;directionFrameId;direction1;direction2;direction3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `matId` | `integer` | 0 | Material identifier used to retrieve the constitutive data. |
| 3 | `matrixForm` | `integer` | 0 | Matrix organization, including the assumed relation between its rows and columns. |
| 4 | `convectionExponent` | `real` | 0.0 | Power in the law for convection. |
| 5 | `formulaKind` | `integer` | 0 | Selects the formula kind for FreeConvectionProp. |
| 6 | `tableId` | `integer` | 0 | Identifier of the tabulated function to evaluate. |
| 7 | `characteristicLength` | `real` | — | Characteristic length (length). |
| 8 | `inletNode` | `integer` | 0 | Identifier addressing node data. |
| 9 | `directionFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 10 | `direction1` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 1. |
| 11 | `direction2` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 2. |
| 12 | `direction3` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 3. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the convection property ID must be a positive integer.
- `matId` — the material ID must be positive (or blank).

**Example record**

~~~text
FreeConvectionProp;1;1;0;0.
~~~

[Model containing this record](../../../validation/models/thermal/thermal_model.oos)

## HeatAnisoMat

The anisotropic heat transfer material of a conduction element.

**Record format and fields**

`HeatAnisoMat;id;conductivityXx;conductivityXy;conductivityXz;conductivityYy;conductivityYz;conductivityZz;specificHeat;density;heatGenerationFactor`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the thermal material namespace. |
| 2 | `conductivityXx` | `real` | 0.0 | Thermal conductivity tensor component in the Xx material or local axes. |
| 3 | `conductivityXy` | `real` | 0.0 | Thermal conductivity tensor component in the Xy material or local axes. |
| 4 | `conductivityXz` | `real` | 0.0 | Thermal conductivity tensor component in the Xz material or local axes. |
| 5 | `conductivityYy` | `real` | 0.0 | Thermal conductivity tensor component in the Yy material or local axes. |
| 6 | `conductivityYz` | `real` | 0.0 | Thermal conductivity tensor component in the Yz material or local axes. |
| 7 | `conductivityZz` | `real` | 0.0 | Thermal conductivity tensor component in the Zz material or local axes. |
| 8 | `specificHeat` | `real` | 0.0 | Energy per unit mass required for one unit of temperature change. |
| 9 | `density` | `real` | 1.0 | Mass per unit volume for a volumetric material or fluid density. |
| 10 | `heatGenerationFactor` | `real` | 1.0 | Multiplier for heat generation. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the material ID must be a positive integer.

**Example record**

~~~text
HeatAnisoMat;5;150.;0.;0.;50.;0.;50.;9.E+8;2.7E-9
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 5`, `conductivityXx = 150.`, `conductivityXy = 0.`, `conductivityXz = 0.`.

## HeatController

Identifies the control applied to a surface or volume heat source, convection condition or radiating boundary.

**Record format and fields**

`HeatController;id;sensorNode;sensorForm;controllerKind;lowerLimit;upperLimit;controlLaw;initialState;timeStep;delayTime;timeConstant`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `sensorNode` | `integer` | Required | A grid point or a scalar point. |
| 3 | `sensorForm` | `text` | — | Specifies the representation of the sensor used by the thermal control law. |
| 4 | `controllerKind` | `text` | — | Selects the controller kind for HeatController. |
| 5 | `lowerLimit` | `real` | Required | Lowest admissible or requested value in the selected range. |
| 6 | `upperLimit` | `real` | Required | Highest admissible or requested value in the selected range. |
| 7 | `controlLaw` | `integer` | Required | Relation used to determine the controlled response from its input. |
| 8 | `initialState` | `real` | 0.0 | State assigned before stepping the model forward. |
| 9 | `timeStep` | `real` | 0.0 | Time increment between successive states, in model time units. |
| 10 | `delayTime` | `real` | 0.0 | Delay time (time). |
| 11 | `timeConstant` | `real` | 0.0 | Characteristic time scale of the response. |

Accepted words: `Constant`, `Element`, `Table`, `Temperature`, `Thermostat`.

**Example record**

~~~text
HeatController;900;5;Temperature;Thermostat;40.;45.;1;0.
~~~

[Model containing this record](../../../validation/models/thermal_radiation/thermostat_sol159.oos)

Reading the example gives `id = 900`, `sensorNode = 5`, `sensorForm = Temperature`, `controllerKind = Thermostat`.

## HeatFluxBoundaryLoad3

A uniform heat flux (or its multiplier) into a boundary surface.

**Record format and fields**

`HeatFluxBoundaryLoad3;id;heatFlux;controlNode;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `heatFlux` | `real` | Required | Thermal energy crossing unit area per unit time. |
| 3 | `controlNode` | `integer` | 0 | Identifier of the grid point through which this definition is controlled. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.

**Example record**

~~~text
HeatFluxBoundaryLoad3;10;0.4;900;21;Through;24
~~~

[Model containing this record](../../../validation/models/thermal_radiation/thermostat_sol159.oos)

Reading the example gives `id = 10`, `heatFlux = 0.4`, `controlNode = 900`.

## HeatFluxNodalLoad2

The heat flux at each grid point of one surface element.

**Record format and fields**

`HeatFluxNodalLoad2;id;elemId;heatFlux1;heatFlux2;heatFlux3;heatFlux4;heatFlux5;heatFlux6;heatFlux7;heatFlux8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `elemId` | `integer` | Required | Identifier of the element addressed by this record. |
| 3 | `heatFlux1` | `real` | — | Thermal energy crossing unit area per unit time. Entry 1. |
| 4 | `heatFlux2` | `real` | — | Thermal energy crossing unit area per unit time. Entry 2. |
| 5 | `heatFlux3` | `real` | — | Thermal energy crossing unit area per unit time. Entry 3. |
| 6 | `heatFlux4` | `real` | — | Thermal energy crossing unit area per unit time. Entry 4. |
| 7 | `heatFlux5` | `real` | — | Thermal energy crossing unit area per unit time. Entry 5. |
| 8 | `heatFlux6` | `real` | — | Thermal energy crossing unit area per unit time. Entry 6. |
| 9 | `heatFlux7` | `real` | — | Thermal energy crossing unit area per unit time. Entry 7. |
| 10 | `heatFlux8` | `real` | — | Thermal energy crossing unit area per unit time. Entry 8. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `elemId` — the surface element ID must be a positive integer.

**Example record**

~~~text
HeatFluxNodalLoad2;1;241;0.3;0.3;0.4;0.4
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `elemId = 241`, `heatFlux1 = 0.3`, `heatFlux2 = 0.3`.

**Referenced records in this example**

- [HeatSurfaceNodes](thermal.md#heatsurfacenodes) via `elemId = 241`.

## HeatFluxNodeSetLoad

A uniform heat flux into a set of grid points.

**Record format and fields**

`HeatFluxNodeSetLoad;id;faceKind;heatFlux;area;node1;node2;node3;node4;node5;node6;node7;node8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `faceKind` | `text` | — | Selects the face kind for HeatFluxNodeSetLoad. |
| 3 | `heatFlux` | `real` | Required | Thermal energy crossing unit area per unit time. |
| 4 | `area` | `real` | — | Surface or cross-sectional measure, in squared model length units. |
| 5 | `node1` | `integer` | 0 | Grid point to which this entry applies. Entry 1. |
| 6 | `node2` | `integer` | 0 | Grid point to which this entry applies. Entry 2. |
| 7 | `node3` | `integer` | 0 | Grid point to which this entry applies. Entry 3. |
| 8 | `node4` | `integer` | 0 | Grid point to which this entry applies. Entry 4. |
| 9 | `node5` | `integer` | 0 | Grid point to which this entry applies. Entry 5. |
| 10 | `node6` | `integer` | 0 | Grid point to which this entry applies. Entry 6. |
| 11 | `node7` | `integer` | 0 | Grid point to which this entry applies. Entry 7. |
| 12 | `node8` | `integer` | 0 | Grid point to which this entry applies. Entry 8. |

Accepted words: `AreaQuad4`, `AreaQuad8`, `AreaTria3`, `AreaTria6`, `Line`, `Point`, `ReversedNormal`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `node` — a grid point ID cannot be negative.

**Example record**

~~~text
HeatFluxNodeSetLoad;1;AreaQuad4;0.2;;203;207;206;202
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `faceKind = AreaQuad4`, `heatFlux = 0.2`, `node1 = 203`.

## HeatFluxSurfaceLoad1

A uniform heat flux into surface elements.

**Record format and fields**

`HeatFluxSurfaceLoad1;id;heatFlux;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `heatFlux` | `real` | Required | Thermal energy crossing unit area per unit time. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.

**Example record**

~~~text
HeatFluxSurfaceLoad1;1;0.01;751;752;851;951;1051
~~~

[Model containing this record](../../../validation/models/thermal/thermal_model.oos)

Reading the example gives `id = 1`, `heatFlux = 0.01`.

## HeatFluxVectorLoad

The thermal vector flux from a distant source into the faces of surface elements.

**Record format and fields**

`HeatFluxVectorLoad;id;heatFlux;sourceTemperature;directionFrameId;direction1;tableId1;direction2;tableId2;direction3;tableId3;controlNode;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `heatFlux` | `real` | — | Thermal energy crossing unit area per unit time. |
| 3 | `sourceTemperature` | `real` | — | Source temperature (temperature). |
| 4 | `directionFrameId` | `integer` | — | Identifier addressing coordinate data. |
| 5 | `direction1` | `real` | 0.0 | Orientation in which the specified quantity acts or is measured. Entry 1. Alternative to `tableId1`. |
| 6 | `tableId1` | `integer` | — | Identifier of the tabulated function to evaluate. Entry 1. Alternative to `direction1`. |
| 7 | `direction2` | `real` | 0.0 | Orientation in which the specified quantity acts or is measured. Entry 2. Alternative to `tableId2`. |
| 8 | `tableId2` | `integer` | — | Identifier of the tabulated function to evaluate. Entry 2. Alternative to `direction2`. |
| 9 | `direction3` | `real` | 0.0 | Orientation in which the specified quantity acts or is measured. Entry 3. Alternative to `tableId3`. |
| 10 | `tableId3` | `integer` | — | Identifier of the tabulated function to evaluate. Entry 3. Alternative to `direction3`. |
| 11 | `controlNode` | `integer` | 0 | Identifier of the grid point through which this definition is controlled. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.
- `direction` — a component is a real or a table, not both.

**Example record**

~~~text
HeatFluxVectorLoad;1;1.361;5500.;;-1.;;0.;;0.;;;142
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `heatFlux = 1.361`, `sourceTemperature = 5500.`, `direction1 = -1.`.

## HeatIsoMat

The heat transfer material of a conduction element, and the fluid of a forced convection ([ForcedConvection](thermal.md#forcedconvection)).

**Record format and fields**

`HeatIsoMat;id;conductivity;specificHeat;density;convectionCoefficient;viscosity;heatGenerationFactor;referenceEnthalpy;phaseChangeTemperature;phaseChangeRange;latentHeat`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the thermal material namespace. |
| 2 | `conductivity` | `real` | — | Thermal conductivity. |
| 3 | `specificHeat` | `real` | 0.0 | Energy per unit mass required for one unit of temperature change. |
| 4 | `density` | `real` | 1.0 | Mass per unit volume for a volumetric material or fluid density. |
| 5 | `convectionCoefficient` | `real` | — | Coefficient in the relation for convection. |
| 6 | `viscosity` | `real` | — | Viscous response coefficient in the selected constitutive or flow law. |
| 7 | `heatGenerationFactor` | `real` | 1.0 | Multiplier for heat generation. |
| 8 | `referenceEnthalpy` | `real` | — | Enthalpy assigned to the reference thermodynamic state. |
| 9 | `phaseChangeTemperature` | `real` | — | Phase change temperature (temperature). |
| 10 | `phaseChangeRange` | `real` | — | Temperature range of the phase change. |
| 11 | `latentHeat` | `real` | — | Latent heat of fusion. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the material ID must be a positive integer.

**Example record**

~~~text
HeatIsoMat;1;0.2;9.E+8;2.7E-9;1.E-5
~~~

[Model containing this record](../../../validation/models/thermal/thermal_model.oos)

Reading the example gives `id = 1`, `conductivity = 0.2`, `specificHeat = 9.E+8`, `density = 2.7E-9`.

## HeatSurfaceDefaults

The default values of the [HeatSurfaceProperty](thermal.md#heatsurfaceproperty), [HeatSurfaceNodes](thermal.md#heatsurfacenodes) and [HeatSurfaceSide](thermal.md#heatsurfaceside) surface elements.

**Record format and fields**

`HeatSurfaceDefaults;kind;frontViewId;backViewId;frontRadiationPropId;backRadiationPropId;propId;orientationNode;directionFrameId;direction1;direction2;direction3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `kind` | `text` | — | Selects the kind for HeatSurfaceDefaults. |
| 2 | `frontViewId` | `integer` | 0 | Identifier selecting the front view record or set. |
| 3 | `backViewId` | `integer` | 0 | Identifier selecting the back view record or set. |
| 4 | `frontRadiationPropId` | `integer` | 0 | Identifier selecting the front radiation property record or set. |
| 5 | `backRadiationPropId` | `integer` | 0 | Identifier selecting the back radiation property record or set. |
| 6 | `propId` | `integer` | 0 | Identifier of the property from which the element obtains its section or constitutive data. |
| 7 | `orientationNode` | `integer` | 0 | Grid point defining the orientation direction in place of explicit vector components. |
| 8 | `directionFrameId` | `integer` | 0 | Identifier selecting the direction frame record or set. |
| 9 | `direction1` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 1. |
| 10 | `direction2` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 2. |
| 11 | `direction3` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 3. |

Accepted words: `AreaQuad4`, `AreaQuad8`, `AreaTria3`, `AreaTria6`, `Constant`, `Element`, `EllipticCylinder`, `ForcedConvectionTube`, `Line`, `Point`, `ReversedNormal`, `Table`, `Tube`.

**Example record**

~~~text
HeatSurfaceDefaults;AreaQuad4;;;1;1
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `kind = AreaQuad4`, `frontRadiationPropId = 1`, `backRadiationPropId = 1`.

## HeatSurfaceNodes

A boundary condition surface element defined by its grid points.

**Record format and fields**

`HeatSurfaceNodes;id;kind;frontViewId;backViewId;frontRadiationPropId;backRadiationPropId;node1;node2;node3;node4;node5;node6;node7;node8`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the surface element namespace. |
| 2 | `kind` | `text` | — | Selects the kind for HeatSurfaceNodes. |
| 3 | `frontViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 4 | `backViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 5 | `frontRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |
| 6 | `backRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |
| 7 | `node1` | `integer` | 0 | Grid point to which this entry applies. Entry 1. |
| 8 | `node2` | `integer` | 0 | Grid point to which this entry applies. Entry 2. |
| 9 | `node3` | `integer` | 0 | Grid point to which this entry applies. Entry 3. |
| 10 | `node4` | `integer` | 0 | Grid point to which this entry applies. Entry 4. |
| 11 | `node5` | `integer` | 0 | Grid point to which this entry applies. Entry 5. |
| 12 | `node6` | `integer` | 0 | Grid point to which this entry applies. Entry 6. |
| 13 | `node7` | `integer` | 0 | Grid point to which this entry applies. Entry 7. |
| 14 | `node8` | `integer` | 0 | Grid point to which this entry applies. Entry 8. |

Accepted words: `AreaQuad4`, `AreaQuad8`, `AreaTria3`, `AreaTria6`, `ReversedNormal`, `ReversedNormal1`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `node` — a grid point ID cannot be negative.
- `node` — a grid point is repeated in the surface.

**Example record**

~~~text
HeatSurfaceNodes;241;AreaQuad4;;;;;205;206;207;208
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 241`, `kind = AreaQuad4`, `node1 = 205`, `node2 = 206`.

## HeatSurfaceProp

The property of a [HeatSurfaceProperty](thermal.md#heatsurfaceproperty) surface element.

**Record format and fields**

`HeatSurfaceProp;id;area;diameter1;diameter2`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `area` | `real` | — | Surface or cross-sectional measure, in squared model length units. |
| 3 | `diameter1` | `real` | — | Diameter 1 (length). |
| 4 | `diameter2` | `real` | — | Diameter 2 (length). |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the property ID must be a positive integer.

**Example record**

~~~text
HeatSurfaceProp;21;;10.;10.
~~~

[Model containing this record](../../../validation/models/thermal_radiation/forced_convection_sol153.oos)

Reading the example gives `id = 21`, `diameter1 = 10.`, `diameter2 = 10.`.

## HeatSurfaceProperty

A boundary condition surface element defined by grid points and a [HeatSurfaceProp](thermal.md#heatsurfaceprop) property.

**Record format and fields**

`HeatSurfaceProperty;id;propId;kind;frontViewId;backViewId;node1;node2;orientationNode;frontRadiationPropId;backRadiationPropId;midsideNode;directionFrameId;direction1;direction2;direction3`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the surface element namespace. |
| 2 | `propId` | `integer` | Required | Identifier of the property from which the element obtains its section or constitutive data. |
| 3 | `kind` | `text` | — | Selects the kind for HeatSurfaceProperty. |
| 4 | `frontViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 5 | `backViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 6 | `node1` | `integer` | Required | Identifier addressing node data. |
| 7 | `node2` | `integer` | 0 | Identifier addressing node data. |
| 8 | `orientationNode` | `integer` | 0 | Grid point defining the orientation direction in place of explicit vector components. |
| 9 | `frontRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |
| 10 | `backRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |
| 11 | `midsideNode` | `integer` | 0 | Identifier addressing node data. |
| 12 | `directionFrameId` | `integer` | 0 | Identifier addressing coordinate data. |
| 13 | `direction1` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 1. |
| 14 | `direction2` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 2. |
| 15 | `direction3` | `real` | — | Orientation in which the specified quantity acts or is measured. Entry 3. |

Accepted words: `EllipticCylinder`, `ForcedConvectionTube`, `Line`, `Point`, `Tube`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `propId` — the surface property ID must be a positive integer.
- `orientationNode` — a grid point ID cannot be negative.

**Example record**

~~~text
HeatSurfaceProperty;151;7;Point;;;102;;;;;;;1.;0.;0.
~~~

[Model containing this record](../../../validation/models/thermal/thermal_model.oos)

Reading the example gives `id = 151`, `propId = 7`, `kind = Point`, `node1 = 102`.

## HeatSurfaceSide

A boundary condition surface element that is one side of a heat conduction element.

**Record format and fields**

`HeatSurfaceSide;id;conductionElemId;sideCode;frontViewId;backViewId;frontRadiationPropId;backRadiationPropId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the surface element namespace. |
| 2 | `conductionElemId` | `integer` | Required | Identifier addressing element data. |
| 3 | `sideCode` | `integer` | Required | Selects one side of the join, element or interface in the record’s local ordering. |
| 4 | `frontViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 5 | `backViewId` | `integer` | 0 | Identifier addressing view factor face factor data. |
| 6 | `frontRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |
| 7 | `backRadiationPropId` | `integer` | 0 | Identifier addressing radiation material data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the element ID must be a positive integer.
- `conductionElemId` — the conduction element ID must be a positive integer.

**Example record**

~~~text
HeatSurfaceSide;231;211;1;2;;2
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 231`, `conductionElemId = 211`, `sideCode = 1`, `frontViewId = 2`.

**Referenced records in this example**

- [ShellQuad4](elements.md#shellquad4) via `conductionElemId = 211`.

## HeatVolumeSourceLoad

Applies volumetric heat generation to a list of conduction elements.

**Record format and fields**

`HeatVolumeSourceLoad;id;heatGeneration;controlNode;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `heatGeneration` | `real` | Required | Heat produced by the specified source over its stated geometric measure. |
| 3 | `controlNode` | `integer` | 0 | Identifier of the grid point through which this definition is controlled. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the load set ID must be a positive integer.

**Example record**

~~~text
HeatVolumeSourceLoad;1;0.002;;1101;1201;1301
~~~

[Model containing this record](../../../validation/models/thermal/thermal_model.oos)

Reading the example gives `id = 1`, `heatGeneration = 0.002`.

## RadiationBands

Planck's second radiation constant and the wavelength breakpoints of the radiation exchange problems, for the [RadiationProp](thermal.md#radiationprop) entries that give an emissivity for each wave band.

**Record format and fields**

`RadiationBands;bandCount;planckSecondConstant;<wavelengths>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bandCount` | `integer` | Required | Number of band entries. |
| 2 | `planckSecondConstant` | `real` | Required | Second radiation constant used in the wavelength-dependent thermal radiation law. |

**Repeated group `wavelengths`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `bandWavelength` | `real` | — | Wavelength associated with the selected radiation band. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
RadiationBands;3;14388.;2.;10.
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `bandCount = 3`, `planckSecondConstant = 14388.`.

## RadiationCavity

The characteristics of one radiation enclosure (cavity).

**Record format and fields**

`RadiationCavity;id;ambientElemId;shadowing;scaleFactor;viewFactorOutput;viewFactorMethod;subdivisionAreaRatio;componentCount;<pairSets>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `ambientElemId` | `integer` | 0 | Identifier addressing surface element data. |
| 3 | `shadowing` | `text` | — | Selects visibility or shadow checks between radiating surfaces. |
| 4 | `scaleFactor` | `real` | 0.0 | Multiplier applied to the quantity specified by the entry. |
| 5 | `viewFactorOutput` | `integer` | — | Controls reporting of the radiative exchange factors between surfaces. |
| 6 | `viewFactorMethod` | `text` | — | Selects the view factor method for RadiationCavity. |
| 7 | `subdivisionAreaRatio` | `real` | 0.1 | Relative measure of subdivision area. |
| 8 | `componentCount` | `integer` | 32 | Number of component entries. |

**Repeated group `pairSets`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `pairSetId` | `integer` | — | Identifier addressing set data. |

Accepted words: `Contour`, `FiniteDifferenceMethod`, `No`, `Yes`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the cavity ID must be a positive integer.

**Example record**

~~~text
RadiationCavity;1;;Yes;;2
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `shadowing = Yes`, `viewFactorOutput = 2`.

## RadiationCavityList

The surface elements of a radiation enclosure.

**Record format and fields**

`RadiationCavityList;cavityId;matrixKind;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `cavityId` | `integer` | Required | Identifier selecting the cavity record or set. |
| 2 | `matrixKind` | `integer` | — | Selects the matrix kind for RadiationCavityList. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cavityId` — the cavity ID must be a positive integer.

**Example record**

~~~text
RadiationCavityList;2;1;231;Through;236
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `cavityId = 2`, `matrixKind = 1`.

## RadiationCavitySet

The radiation cavities that take part in the enclosure radiation analysis.

**Record format and fields**

`RadiationCavitySet;<cavities>`

This part of the record has no fixed fields.

**Repeated group `cavities`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `cavityId` | `integer` | — | Identifier addressing radiation cavity data. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cavityId` — the card needs at least one cavity.
- `cavityId` — a cavity ID must be a positive integer.

**Example record**

~~~text
RadiationCavitySet;1;2
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

## RadiationExchangeMatrix

One column of the radiation exchange matrix of a cavity.

**Record format and fields**

`RadiationExchangeMatrix;cavityId;columnIndex;<exchangeFactors>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `cavityId` | `integer` | Required | Identifier selecting the cavity record or set. |
| 2 | `columnIndex` | `integer` | Required | Column of the matrix to which the following terms belong. |

**Repeated group `exchangeFactors`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `exchangeFactor` | `real` | — | Multiplier for exchange. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cavityId` — the cavity ID must be a positive integer.
- `exchangeFactor` — a column of the matrix needs at least one coefficient.
- `exchangeFactor` — a radiation exchange coefficient cannot be negative.

**Example record**

~~~text
RadiationExchangeMatrix;2;3;0.;1998.2;2000.4;2000.4
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `cavityId = 2`, `columnIndex = 3`.

## RadiationProp

Supplies radiative properties for the sides of heat-transfer surfaces.

**Record format and fields**

`RadiationProp;id;absorptivity;<emissivities>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `absorptivity` | `real` | — | Fraction of incident radiation absorbed at the surface. |

**Repeated group `emissivities`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `emissivity` | `real` | — | Ratio of emitted radiation to that of a black body at the same temperature. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the radiation material ID must be a positive integer.
- `emissivity` — an emissivity cannot be negative.

**Example record**

~~~text
RadiationProp;3;0.3;0.2;0.85
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 3`, `absorptivity = 0.3`.

## RadiationPropTemperature

The tables that make the radiation properties of a [RadiationProp](thermal.md#radiationprop) depend on temperature.

**Record format and fields**

`RadiationPropTemperature;id;absorptivityTableId;<emissivityTables>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `absorptivityTableId` | `integer` | 0 | Identifier addressing material table data. |

**Repeated group `emissivityTables`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `emissivityTableId` | `integer` | — | Identifier addressing material table data. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
RadiationPropTemperature;1;21;21
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `absorptivityTableId = 21`.

**Referenced records in this example**

- [TableMaterial1](tables.md#tablematerial1) via `absorptivityTableId = 21`.

## RadiationToSpace

The radiation to space from surface element faces.

**Record format and fields**

`RadiationToSpace;ambientNode;ambientViewFactor;controlNode;<elements>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `ambientNode` | `integer` | Required | Identifier addressing scalar or grid point data. |
| 2 | `ambientViewFactor` | `real` | Required | Multiplier for ambient view. |
| 3 | `controlNode` | `integer` | 0 | Identifier of the grid point through which this definition is controlled. |

**Repeated group `elements`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `elemId` | `any` | — | Identifier of the element addressed by this record. |

Accepted words: `By`, `Through`.

**Example record**

~~~text
RadiationToSpace;9001;1.;;141;142;241
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `ambientNode = 9001`, `ambientViewFactor = 1.`.

## TemperatureBoundary

The temperature boundary conditions of a heat transfer analysis.

**Record format and fields**

`TemperatureBoundary;id;kind;<temperatureGroups>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `kind` | `text` | Static | Selects the kind for TemperatureBoundary. |

**Repeated group `temperatureGroups`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `temperatureEntry` | `any` | — | Reference to, or value of, the temperature data for this boundary condition. |

Accepted words: `By`, `Static`, `Through`, `Transient`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the temperature set ID must be a positive integer.
- `temperature` — the card needs at least one temperature and grid point.

**Example record**

~~~text
TemperatureBoundary;3;Static;50.;201;Through;204
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 3`, `kind = Static`.

## TrimComponentCoupling

How a (3D, finite element) trim component, a layer of porous or elastic material of a car interior, is coupled to the structure and to the acoustic cavities, and which of its degrees of freedom are constrained.

**Record format and fields**

`TrimComponentCoupling;id;gluedSetId;slidingSetId;openSetId;imperviousSetId;outOfCoreBlockCount;singlePrecisionFlag;airGapSetId;fixedTranslationXSetId;fixedTranslationYSetId;fixedTranslationZSetId;fixedRotationXSetId;fixedRotationYSetId;fixedRotationZSetId;fixedPressureSetId;regionId;structureCompressionRatio;cavityCompressionRatio`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `gluedSetId` | `integer` | 0 | Identifier selecting the glued set record or set. |
| 3 | `slidingSetId` | `integer` | 0 | Identifier selecting the sliding set record or set. |
| 4 | `openSetId` | `integer` | 0 | Identifier selecting the open set record or set. |
| 5 | `imperviousSetId` | `integer` | 0 | Identifier selecting the impervious set record or set. |
| 6 | `outOfCoreBlockCount` | `integer` | 1 | Number of out of core block entries. |
| 7 | `singlePrecisionFlag` | `integer` | 0 | Selects the single precision flag for TrimComponentCoupling. |
| 8 | `airGapSetId` | `integer` | 0 | Identifier selecting the air gap set record or set. |
| 9 | `fixedTranslationXSetId` | `integer` | 0 | Identifier selecting the fixed translation x set record or set. |
| 10 | `fixedTranslationYSetId` | `integer` | 0 | Identifier selecting the fixed translation y set record or set. |
| 11 | `fixedTranslationZSetId` | `integer` | 0 | Identifier selecting the fixed translation z set record or set. |
| 12 | `fixedRotationXSetId` | `integer` | 0 | Identifier selecting the fixed rotation x set record or set. |
| 13 | `fixedRotationYSetId` | `integer` | 0 | Identifier selecting the fixed rotation y set record or set. |
| 14 | `fixedRotationZSetId` | `integer` | 0 | Identifier selecting the fixed rotation z set record or set. |
| 15 | `fixedPressureSetId` | `integer` | 0 | Identifier selecting the fixed pressure set record or set. |
| 16 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 17 | `structureCompressionRatio` | `real` | — | Relative measure of structure compression. |
| 18 | `cavityCompressionRatio` | `real` | — | Relative measure of cavity compression. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TrimComponentCoupling;1;1;;2
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_3d_sol111.oos)

Reading the example gives `id = 1`, `gluedSetId = 1`, `openSetId = 2`.

## TrimComponentCoupling1D

How a 1D analytical trim component (a layered porous material, [TrimLayeredComponent](thermal.md#trimlayeredcomponent), that has no finite element mesh of its own) is coupled to the structure and to the cavities.

**Record format and fields**

`TrimComponentCoupling1D;id;gluedSetId;slidingSetId;openSetId;imperviousSetId;regionId;methodName`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `gluedSetId` | `integer` | 0 | Identifier selecting the glued set record or set. |
| 3 | `slidingSetId` | `integer` | 0 | Identifier selecting the sliding set record or set. |
| 4 | `openSetId` | `integer` | 0 | Identifier selecting the open set record or set. |
| 5 | `imperviousSetId` | `integer` | 0 | Identifier selecting the impervious set record or set. |
| 6 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |
| 7 | `methodName` | `text` | — | Text naming the method. |

Accepted words: `Constant`, `Element`, `OneDimensional`, `Table`.

**Example record**

~~~text
TrimComponentCoupling1D;2;1;;2;;0;OneDimensional
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_1d_sol111.oos)

Reading the example gives `id = 2`, `gluedSetId = 1`, `openSetId = 2`, `regionId = 0`.

## TrimCouplingTolerances

The tolerances with which the interface coupling matrices of a trim component are computed when the meshes at the interface do not match.

**Record format and fields**

`TrimCouplingTolerances;id;couplingKind;relativeTolerance;gapTolerance1;gapTolerance2;gapTolerance3;gapTolerance4;regionId`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |
| 2 | `couplingKind` | `text` | — | Selects the coupling kind for TrimCouplingTolerances. |
| 3 | `relativeTolerance` | `real` | — | Permitted numerical deviation for relative. |
| 4 | `gapTolerance1` | `real` | — | Permitted numerical deviation for gap. |
| 5 | `gapTolerance2` | `real` | same as gapTolerance1 | Permitted numerical deviation for gap. |
| 6 | `gapTolerance3` | `real` | same as gapTolerance2 | Permitted numerical deviation for gap. |
| 7 | `gapTolerance4` | `real` | same as gapTolerance3 | Permitted numerical deviation for gap. |
| 8 | `regionId` | `integer` | 0 | Identifier of the region on which the definition acts. |

Accepted words: `Constant`, `Element`, `Interface`, `SimplePerforation`, `SolidAirGap`, `SolidGlued`, `SolidOpen`, `SolidSlide`, `Table`, `TrimSurface`.

**Example record**

~~~text
TrimCouplingTolerances;2;Interface;0.1;1.
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_1d_sol111.oos)

Reading the example gives `id = 2`, `couplingKind = Interface`, `relativeTolerance = 0.1`, `gapTolerance1 = 1.`.

## TrimLayeredComponent

The layers of a 1D analytical trim component (a stack of porous or elastic materials with no mesh of its own), listed from the bottom one.

**Record format and fields**

`TrimLayeredComponent;id;<layers>`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Set identifier shared by entries in the same group. |

**Repeated group `layers`**. Repeat these fields in order for each entry.

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `globalPlyId` | `integer` | — | Identifier selecting the global ply record or set. |
| 2 | `plyMatId` | `integer` | — | Identifier selecting the ply material record or set. |
| 3 | `plyThickness` | `real` | — | Ply thickness (length). |
| 4 | `plyScaleFactor` | `real` | — | Multiplier for ply scale. |

Accepted words: `Constant`, `Element`, `Table`.

**Example record**

~~~text
TrimLayeredComponent;1;1;201;8.;1.;2;204;2.;0.
~~~

[Model containing this record](../../../validation/models/acoustics/pem_trim_1d_sol111.oos)

Reading the example gives `id = 1`.

## ViewFactorFace

The radiation cavity and the shadowing of a surface element face, for the view factor calculation.

**Record format and fields**

`ViewFactorFace;id;cavityId;shading;betaSubdivisions;gammaSubdivisions;surfaceOffset`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `id` | `integer` | Required | Identifier in the namespace of this card type. |
| 2 | `cavityId` | `integer` | 0 | Identifier addressing radiation cavity data. |
| 3 | `shading` | `text` | — | Controls treatment of surface obstruction in the radiation calculation. |
| 4 | `betaSubdivisions` | `integer` | 1 | Number of integration subdivisions in the beta direction. |
| 5 | `gammaSubdivisions` | `integer` | 1 | Number of integration subdivisions in the gamma direction. |
| 6 | `surfaceOffset` | `real` | 0.0 | Signed distance between the reference surface and the represented surface. |

Accepted words: `Both`, `CanBeShaded`, `CanShade`, `None`.

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `id` — the view factor ID must be a positive integer.

**Example record**

~~~text
ViewFactorFace;1;1;Both
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `id = 1`, `cavityId = 1`, `shading = Both`.

## ViewFactorIntegration

The parameters of the Gaussian integration method of view factor calculation for one radiation cavity.

**Record format and fields**

`ViewFactorIntegration;cavityId;blockingIntegrationOrder;shadowingIntegrationOrder;contourIntegrationLevel;errorTolerance;zeroTolerance;warpTolerance;radiationCheck`

| Position | Field | Type | Default | Meaning and conventions |
| ---: | --- | --- | --- | --- |
| 1 | `cavityId` | `integer` | Required | Identifier selecting the cavity record or set. |
| 2 | `blockingIntegrationOrder` | `integer` | 4 | Order of numerical integration used when checking for blocking surfaces. |
| 3 | `shadowingIntegrationOrder` | `integer` | 4 | Integration order used for surface visibility calculations. |
| 4 | `contourIntegrationLevel` | `integer` | 4 | Refinement level used for integration along the surface contour. |
| 5 | `errorTolerance` | `real` | 0.1 | Permitted numerical deviation for error. |
| 6 | `zeroTolerance` | `real` | 1.0e-10 | Permitted numerical deviation for zero. |
| 7 | `warpTolerance` | `real` | 0.01 | Permitted numerical deviation for warp. |
| 8 | `radiationCheck` | `integer` | 3 | Selects consistency checks on the radiative surface calculations. |

**Model diagnostics**

The following messages identify invalid input for the applicable field or form.

- `cavityId` — the cavity ID must be a positive integer.

**Example record**

~~~text
ViewFactorIntegration;1;3;3;6;0.05;1.E-10;0.01;3
~~~

[Model containing this record](../../../validation/models/thermal_radiation/radiation_enclosures_sol153.oos)

Reading the example gives `cavityId = 1`, `blockingIntegrationOrder = 3`, `shadowingIntegrationOrder = 3`, `contourIntegrationLevel = 6`.
