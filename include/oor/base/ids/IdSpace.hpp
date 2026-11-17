#pragma once

#include <string_view>

namespace oor::base
{

// The ID spaces of a model. All element types share one EID space, likewise properties,
// materials, coordinate systems and methods; dynamic tables, material tables, stress tables, heat tables, damping
// tables and random tables have separate spaces. Categories
// of the long tail have no cross-type space: an ID is unique per card type there (IdSpace::PerCardType).
enum class IdSpace
{
    Node,
    Element,
    Property,
    Material,
    Coordinate,
    Method,
    DynamicTable,
    MaterialTable,
    // TableStress1 and TableStressTemperature: the tables of stress dependent properties (IsoMatStressDependent,
    // CreepMat, HyperelasticPolynomialMat, ...)
    StressTable,
    HeatTable,   // TableHeat1 and TableHeatTwoVariables: the tables of convection coefficients
    HybridDampingRotorOptionsTable, // TableModalDamping1: the modal damping tables (Case Control SDAMPING)
    // TableRandomSpectrum1 and TableGustSpectrum: the power spectral density tables (RandomSpectralDensity)
    RandomTable,
    // HeatIsoMat and HeatAnisoMat: the heat transfer materials. Apart from the structural MID space: the format
    // reference lets a HeatIsoMat or HeatAnisoMat have the ID of an IsoMat, AnisoMat2D or AxisymOrthoMat (a coupled
    // model has both), and they must be unique with respect to each other
    ThermalMaterial,
    // HeatSurfaceSide, HeatSurfaceNodes and HeatSurfaceProperty: the heat transfer surface elements. Apart from the
    // conduction elements: a SolidHexa 1 may have the HeatSurfaceSide 1 to 6 on its sides
    SurfaceElement,
    // AeroLiftingPanel1 to AeroPistonPanel5: the aerodynamic macro elements. Apart from the structural elements (the
    // format
    AeroElement,
                 // reference lets the boxes of an AeroLiftingPanel1 overlap the IDs of the structure) and unique with
                 // respect to each other; the boxes of a CAERO take the IDs from its EID on (the AeroBox reference
                 // target)
    // AeroLiftingPanelProp1 to AeroPistonProp5: the properties a CAERO names, one number space for the five cards
    AeroProperty,
    PerCardType,
    // the ID is a set ID shared by several cards (PointForceLoad, SinglePointConstrList, ...): not unique, cards are
    // grouped by it
    Group,
    None   // the card has no ID
};

[[nodiscard]] std::string_view idSpaceName(IdSpace space) noexcept;

} // namespace oor::base
