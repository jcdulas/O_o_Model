#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/core/Model.hpp"

#include <functional>
#include <optional>

namespace oor::model
{

// What a renumbering renumbers: one ID space, or the set IDs of one category of cards.
enum class RenumberSpace
{
    Node,
    Element,
    SurfaceElement, // HeatSurfaceSide, HeatSurfaceNodes, HeatSurfaceProperty
    Property,
    Material,
    ThermalMaterial, // HeatIsoMat and HeatAnisoMat
    Coordinate,
    Method,
    DynamicTable,
    MaterialTable,
    StressTable,
    HeatTable,
    HybridDampingRotorOptionsTable, // TableModalDamping1
    RandomTable,                    // TableRandomSpectrum1 and TableGustSpectrum
    // the set IDs of LoadCombination, PointForceLoad, FacePressureLoad, ... (category Load)
    LoadCombinationSet,
    // the set IDs of SinglePointConstr, SinglePointConstrList, MultiPointConstr, SinglePointConstrUnion (category
    // Constraint)
    ConstraintSet,
    // the set IDs of TransientTableLoad1, FreqResponseLoad1, DynamicLoadCombination, DynamicLoadScale, ... (category
    // DynamicLoad)
    DynamicLoadSet,
    Set,                            // the IDs of IdListSet1 and TypedListSet3 (category Set)
    // the set IDs of FreqList, FreqLinearSteps1 to FreqModeFractions5 (category Frequency)
    FrequencySet,
    // the IDs of ComplexEigenMethod and ComplexEigenPoles (the real methods are the Method space)
    ComplexMethod,
    Delay,                          // the set IDs of DynamicLoadDelay
    Phase,                          // the set IDs of DynamicLoadPhase
    // the IDs of TransientTimeSteps and NonlinearTimeSteps (they number the same selection: one ID gives both a new
    // one)
    TimeStep,
    Nonlinear,            // the IDs of NonlinearStaticParams and ArcLengthParams
    Random,               // the set IDs of RandomSpectralDensity and RandomTimeLags
    TransferFunction,     // the set IDs of TF
    InitialCondition,     // the set IDs of TransientInitialCondition
    HeatBoundaryProperty, // the IDs of HeatSurfaceProp
    ConvectionProperty,   // the IDs of FreeConvectionProp
    ForcedConvectionProperty, // the IDs of ForcedConvectionProp
    RadiationMaterial,        // the IDs of RadiationProp
    ViewFactorFaceFactor,     // the IDs of ViewFactorFace
    // the cavity IDs of RadiationCavity, RadiationCavityList, RadiationExchangeMatrix and ViewFactorIntegration
    RadiationCavity,
    // ContactBody, ContactBody1, ContactFaceRegion, ContactNodeRegion: a body of a contact pair
    ContactBody,
    // ContactElemSurface, ContactPropertyRegion, ContactBoxRegion, ... and the rigid surfaces ContactPatchSurface,
    // ContactBezierSurface, ...: what a body is made of
    ContactSurface,
    ContactRigid,   // ContactRigidMotion: the motion of a rigid contact body
    ContactBodyParameters,      // ContactBodyParams: the parameters of a contact body
    ContactGeometricParameters, // ContactPairGeomParams: the geometric parameters of a contact pair
    ContactPhysicalParameters,  // ContactPairPhysicalParams: the physical parameters of a contact pair
    ContactPair,                // ContactPair and ModuleContactPair: a contact pair
    // ContactTable1, ContactTable, ContactSetUnion, ContactSet and ModuleContactTable: a contact table
    ContactTable,
    TrimmingCurve,              // ContactTrimCurve: the trimming curve of a NURBS surface
    SlidelineSegments,          // SlidelineSegments: the line segments of a slideline contact region
    SlidelineContact,           // ContactSlideline: a slideline contact region
    SlidelineFriction,          // SlidelineFriction: the friction of a slideline contact region
    NonlinearStep,              // NonlinearStepControl: the load or time stepping of a nonlinear analysis
    NonlinearHarmonic,          // NonlinearHarmonicParams: the parameters of a nonlinear harmonic response
    // NonlinearHarmonicFreqList, NonlinearHarmonicFreqSteps and NonlinearHarmonicFreqContinuation: the forcing
    // frequencies of a nonlinear harmonic response
    NonlinearFrequency,
    // DeflagrationStateEquation, GammaLawStateEquation, IgnitionGrowthStateEquation, ...: the equation of state an
    // EulerMat names
    EquationOfState,
    // ElasticShearModel, PolynomialShearModel, UserShearModel: the shear model an EulerMat names
    ShearModel,
    // HydrodynamicYield, JohnsonCookYield, VonMisesYield, ...: the yield model an EulerMat names
    YieldModel,
    // JohnsonCookFailure, MaxPlasticStrainFailure, UserFailureModel: the failure model an EulerMat names
    FailureModel,
    SpallModel,                 // ConstantSpallation: the spall model an EulerMat names
    // EulerMeshGenerator: an Euler mesh (an EulerLagrangeCoupling, EulerBarrier or flow boundary names it)
    EulerMesh,
    MeshBias,                   // EulerMeshBias: the mesh size variation an EulerMeshGenerator names
    EulerBodyForce,             // EulerBodyForce and EulerBodyForceSet: a body force on Euler elements
    EulerRegionSet,             // EulerForceRegion: the set of Euler regions an EulerBodyForceSet names
    // InitialSurfaceVolume, CylinderShape, SphereShape: a geometric shape that defines an Euler region
    EulerRegionShape,
    Coupling,                   // EulerLagrangeCoupling: an Euler-Lagrange coupling surface
    CouplingOptions,            // CouplingOptions: the set of coupling options an EulerLagrangeCoupling names (OPTID)
    CohesiveFriction,           // CohesiveFriction: a cohesive friction model
    // CouplingCohesiveFriction: the set of cohesive frictions an EulerLagrangeCoupling names (COHFRID)
    CohesiveFrictionSet,
    CouplingFailure,            // CouplingFailedSegmentFlow: the surroundings of a failed coupling surface segment
    HydrostaticPreset,          // EulerHydrostaticPreset: a hydrostatic preset of the Euler densities
    GasBag,                     // GasBag: a gas bag with a uniform pressure
    // GasBagLeakage: the set of porosity definitions a GasBag or EulerLagrangeCoupling names (PORID)
    Leakage,
    // SurfacePermeability, GasBagPermeableLink, CouplingHoleToCoupling, CouplingHoleToGasBag, PorousFlowBoundary,
    // PorousTimeFlowBoundary, GasBagVentHole, PorousHydrostaticBoundary, PorousUserBoundary: the porosity model a
    // GasBagLeakage names
    Porosity,
    InflatorSet, // InflatorInlet: the set of inflators a GasBag or EulerLagrangeCoupling names (INFID)
    // ColdGasInflator, HybridInflator, TankTestInflator, StandardInflator: the inflator model an InflatorInlet names
    Inflator,
    InflatorGas, // InflatorGas: a gas of an inflator or of an initial gas composition
    GasFractions,         // HybridInflatorFractions: the gas fractions of a hybrid inflator as a function of time
    InitialGas,           // InitialGasComposition: the initial gas composition of a gas bag or a coupling surface
    DesignVariable,       // the IDs of DesignVar
    DesignEquation,       // the IDs of DesignEquation
    DesignResponse,       // the IDs of DesignResp1, DesignResp2 and DesignResp3 (one number space)
    DesignConstraintSet,  // the DCIDs of DesignConstr and DesignConstrUnion
    PropertyRelation,     // the IDs of DesignPropRelation1 and DesignPropRelation2
    MaterialRelation,     // the IDs of DesignMatRelation1 and DesignMatRelation2
    ConnectivityRelation, // the IDs of DesignElemRelation1 and DesignElemRelation2
    // the EIDs of AeroLiftingPanel1 to AeroPistonPanel5; the boxes (AeroBox references) follow their CAERO, so use a
    // mapping that keeps the ranges apart (an offset)
    AeroElement,
    AeroProperty,         // the IDs of AeroLiftingPanelProp1 to AeroPistonProp5
    AeroList,             // the IDs of AeroBoxList
    AeroFactor,           // the IDs of AeroFactorList
    AeroFlutterFactor,    // the IDs of AeroFlutterFactors
    AeroControlSurface,   // the IDs of AeroControlSurface
    AeroTrimSet,          // the IDs of AeroTrim and AeroTrim2 (one selection: both get the same new ID)
    AeroFlutterSet,       // the IDs of FLUTTER
    AeroGustSet,          // the IDs of AeroGust
    DivergenceSet,        // the IDs of AeroDivergence
    ControlSchedule,      // the IDs of AeroControlSchedule
    ControlVector,        // the IDs of AeroControlVector
    AeroNode,             // the IDs of AeroNode
    AeroScale,            // the IDs of AeroNodeScale
    // the superelement numbers: the SEID of SuperelementInteriorNodes, SuperelementElemTransfer,
    // SuperelementBulkOptions, SuperelementExteriorPoints, SuperelementCopyPoints, every reference to one, the SEID of
    // Node and NodeDefaults, the Case Control selections and the BEGIN SUPER=n lines of the parts (one number space for
    // the whole deck: the residual structure and its parts)
    Superelement,
    MassCombination, // the IDs of MassCaseCombination
    // the IDs of AeroSurfaceSpline1 to AeroFiniteBeamSpline7, AeroUserSpline, AeroSplineStripBlend,
    // AeroSplineCurveBlend and AeroRigidSpline (the cards of one category, IDs unique per card type: two types with one
    // ID are one selection and get one new ID)
    AeroSpline,
    HybridDampingRotorOptionsSpecification, // the IDs of HybridDampingRotorOptions
    HybridDamping,                          // the IDs of HybridDamping
    ElementList,                            // the IDs of FluidMassElemList
    // the MVIDs of ModuleTranslation, ModuleRotation1, ModuleRotation2, ModuleMirror1 and ModuleMirror2
    ModuleMove,
    // the IDs of TableMultiVariable0, TableMultiVariable1, TableMultiVariable2 and TableScattered3D
    MultiDimensionalTable,
    FatigueTable,                           // the IDs of TableFatigueHistory
    ImperfectionCase,                       // the IDs of ImperfectionCase
    ImperfectionGeometry,                   // the IDs of ImperfectionGeometry
    GeometricBoundary,                      // the IDs of GeomBoundaryCurve
    AdaptivityCriterion,                    // the IDs of AdaptiveRefineCriterion
    AdaptivitySet,                          // the IDs of AdaptiveRefineControl
    // the ROTORIDs of RotorLineNodes, RotorModel3D, RotorAxisym and RotorSuperelement
    Rotor,
    DiscreteValueSet,                       // the IDs of DesignDiscreteValues
    UserDefinedName,                        // the UDIDs of UserFileName
    FatigueProperty,                        // the IDs of FatigueProp
    FatigueLoad,                            // the IDs of FatigueLoad
    FatigueEvent,                           // the IDs of FatigueEvent and FatigueSequence
    EulerInitialization,                    // the IDs of EulerInitialRegions
    EulerInitialRegions,                    // the TSIDs of InitialConditionRegion
    InitialValueSet,                        // the IDs of InitialConditionValues
    HeatLossSet,                            // the HTRIDs of GasBagHeatTransfer
    HeatTransferModel,                      // the IDs of GasBagConvection and GasBagRadiation
    CosimulationGroup,                      // the IDs of CosimulationArea
    CosimulationInput,                      // the IDs of CosimulationInputs
    CosimulationOutput,                     // the IDs of CosimulationOutputs
    CosimulationService,                    // the IDs of CosimulationService
    WettedElement,                          // the WEIDs of WettedElemSide and WettedElemNodes
    WettedSurface,                          // the WSIDs of WettedSurface
    BrakeProperty,                          // the IDs of BrakeProp
    BrakeMotion,                            // the IDs of MOTION
    BrakeSqueal,                            // the IDs of BrakeSqueal and BrakeSystem
    FrfComponent,                           // the COMPIDs of FrfComponent
    BushingForceSet,                        // the LIDs of NonlinearBushForceTables
    LoadStepControl,                        // the IDs of StepControlCriteria
    TemperatureGroup,                       // the IDs of TemperatureTimeGroup
    MonteCarloSet,                          // the SIDs of MonteCarloParams
    DeactivatedElementSet,                  // the IDs of DeactivatedElems
    TransferPathSet,                        // the SETIDs of TransferPathSetup
    IterativeSolver,                        // the SIDs of IterativeSolverOptions
    MetadataGroup                           // the ABSTIDs of MetadataGroup
};

// The new ID of an old one; nothing leaves it unchanged.
using IdMapping = std::function<std::optional<base::EntityId>(base::EntityId)>;
// Makes the mapping for one model (the residual structure or a part): the mapping of a renumbering "from 1000, in file
// order" depends on the model it is applied to.
using MappingFactory = std::function<IdMapping(const Model&)>;

// Renumbering of one ID space, with every reference to it rewritten.
struct Renumbering
{
    // Gives every ID of the space a new one and rewrites the references to them, in the model and (with
    // `includeParts`) in each of its parts, which have ID spaces of their own, each with the mapping of its own IDs.
    // Atomic: when a new ID is not valid, or two IDs would become the same (or one becomes an ID that stays), nothing
    // is changed and DuplicateIdError or UsageError is thrown. Returns the number of cards whose ID changed. A THRU
    // range keeps its end points renumbered (it stays correct for an offset or any increasing mapping).
    //
    // A part is renumbered on its own too (`apply` on the part): what the residual structure names in it (the grid
    // points of a SuperelementConnection, SuperelementBoundarySearch or SuperelementExcludedNodes, the design variables
    // of a SuperelementDesignLink: ReferenceVisitor::visitInSuperelement) follows, and nothing else changes. The
    // residual structure alone leaves the parts as they are, and so does a part leave the others. The superelement
    // numbers are the exception: they belong to the whole deck, so that space is renumbered on the residual structure
    // (never on a part) and takes the parts, whatever `includeParts` says.
    static std::size_t apply(Model& model, RenumberSpace space, const MappingFactory& factory,
                             bool includeParts = false);

    // The mapping that adds `offset` to every ID.
    [[nodiscard]] static MappingFactory offset(base::EntityId offset);
    // The mapping that gives the IDs of the space, in file order, `start`, `start + step`, ...
    [[nodiscard]] static MappingFactory consecutive(RenumberSpace space, base::EntityId start, base::EntityId step);
    // A mapping given as a function (for a dictionary or a callable).
    [[nodiscard]] static MappingFactory fromFunction(IdMapping mapping);
};

} // namespace oor::model
