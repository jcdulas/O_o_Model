#pragma once

#include "oor/base/ids/IdSpace.hpp"

#include <cstdint>
#include <string_view>

namespace oor::model
{

// The containers of the model: which group of the object model a card type belongs to.
enum class CardCategory : std::uint8_t
{
    Unknown, // cards kept as text
    Node,    // GRID: the grid points (model.nodes)
    // ScalarPoint, ExtraPoint, GeomPoint, AxisymFluidRingNode: the other points, which share the node ID space
    // (model.points)
    Point,
    Coordinate,
    Element,
    Property,
    Material,
    Load,
    Constraint,
    DynamicLoad,
    Method,
    Frequency,
    ComplexMethod,    // ComplexEigenMethod and ComplexEigenPoles: the complex eigenvalue extraction (CMETHOD)
    Delay,            // DynamicLoadDelay: the time delays of the dynamic loads
    PhaseLead,        // DynamicLoadPhase: the phase leads of the dynamic loads
    // TransientTimeSteps and NonlinearTimeSteps: the time steps of a transient analysis (TransientTimeSteps)
    TimeStep,
    // NonlinearStaticParams and ArcLengthParams: the parameters of a nonlinear static analysis (NonlinearStaticParams)
    NonlinearStatic,
    Random,           // RandomSpectralDensity and RandomTimeLags: the random analysis sets (RANDOM)
    TransferFunction, // TF: the transfer functions (TFL)
    InitialCondition, // TransientInitialCondition: the transient initial conditions (IC)
    Table,
    Set,
    Parameter,
    // DirectMatrixNodal, DirectMatrixAeroJ, DirectMatrixAeroJInterference, DirectMatrixAeroK, DirectMatrixAxisym and
    // DirectMatrix: the direct matrix input (model.matrices)
    Matrix,
    // MonitorIntegratedLoad1, MonitorElemLoad2, MonitorNodeForceSum3 and MonitorDisplacement: the monitor points
    // (model.monitor_points)
    MonitorPoint,
    ThermalMaterial,          // HeatIsoMat and HeatAnisoMat: the heat transfer materials (model.thermal_materials)
    // HeatSurfaceProp: the property of a HeatSurfaceProperty surface element (its own ID per HeatSurfaceProp)
    HeatBoundaryProperty,
    ConvectionProperty,       // FreeConvectionProp: the free convection property that a FreeConvection names
    ForcedConvectionProperty, // ForcedConvectionProp: the forced convection property that a ForcedConvection names
    RadiationMaterial,        // RadiationProp: the radiation properties a surface element names (RADMIDF, RADMIDB)
    ViewFactorFaceFactor,     // ViewFactorFace: the view factor definition a surface element names (IVIEWF, IVIEWB)
    // RadiationCavity, RadiationCavityList, RadiationExchangeMatrix, ViewFactorIntegration: the cards of one radiation
    // cavity (ICAVITY)
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
    DesignVariable,       // DesignVar: a design variable (the DVIDi of every relation and of DesignVarLink name one)
    // DesignEquation: an equation (the EQID of DesignPropRelation2, DesignMatRelation2, DesignElemRelation2 and
    // DesignResp2, and of the BushProp1D and GeneralFrame3 that take their data from an equation)
    DesignEquation,
    DesignResponse,       // DesignResp1, DesignResp2 and DesignResp3: a response; the three share one number space
    // DesignConstr and DesignConstrUnion: a set of design constraints (DESSUB and DESGLB name one)
    DesignConstraint,
    // DesignPropRelation1 and DesignPropRelation2: the relation of design variables to a property field
    PropertyRelation,
    // DesignMatRelation1 and DesignMatRelation2: the relation of design variables to a material field
    MaterialRelation,
    // DesignElemRelation1 and DesignElemRelation2: the relation of design variables to a connectivity field
    ConnectivityRelation,
    AeroElement,          // AeroLiftingPanel1 to AeroPistonPanel5: the aerodynamic macro elements (model.caeros)
    // AeroLiftingPanelProp1 to AeroPistonProp5: the properties of the macro elements (model.paeros)
    AeroProperty,
    // AeroBoxList: a list of aerodynamic boxes or grid points (a control surface, a spline, a component)
    AeroList,
    AeroFactor,         // AeroFactorList: a list of numbers (the divisions of a CAERO, the data of a PAERO, a schedule)
    // AeroFlutterFactors: the densities, Mach numbers, frequencies or velocities an AeroFlutter names
    AeroFlutterFactor,
    // AeroSurfaceSpline1 to AeroFiniteBeamSpline7 and AeroUserSpline: the interpolation of the structure to the
    // aerodynamics
    AeroSpline,
    // AeroControlSurface: a control surface (an AeroControlSchedule names it; an AeroTrim names its label)
    AeroControlSurface,
    // AeroRigidTrimVariable and AeroController: the rigid body motions and the general controllers of a trim
    AeroTrimVariable,
    AeroTrimSet,        // AeroTrim and AeroTrim2: a trim case (Case Control TRIM)
    AeroFlutterSet,     // FLUTTER: a flutter analysis (Case Control FMETHOD)
    AeroGustSet,        // AeroGust: a gust (Case Control AeroGust)
    DivergenceSet,      // AeroDivergence: a divergence analysis (Case Control AeroDivergence)
    ControlSchedule,    // AeroControlSchedule: the schedule of a control surface (Case Control AeroControlSchedule)
    // AeroControlVector: a vector of control parameters (Case Control AEUXREF, AeroDownwash, AeroForceVector,
    // AeroPressureVector)
    ControlVector,
    AeroNode,           // AeroNode: an aerodynamic grid point (AeroQuad4 and AeroTria3 name them)
    AeroScale,          // AeroNodeScale: the reference lengths an AeroNode names
    // AeroComponent and AeroComponentUnion: a component of an integrated load monitor point, keyed by its name
    AeroComponent,
    // AeroUnsteadyParams, AeroStaticParams and the other aeroelastic cards no other card names by number
    Aero,
    // SuperelementInteriorNodes, SuperelementBulkOptions, SuperelementConnection, SuperelementCopyPoints, ...: the
    // cards of the superelement family
    Superelement,
                  // (model.superelement_cards); those that define a superelement number (SuperelementInteriorNodes,
                  // SuperelementElemTransfer, SuperelementBulkOptions, SuperelementExteriorPoints,
                  // SuperelementCopyPoints) are IdSpace::Group
    // MassCaseCombination: a linear combination of mass cases (Case Control MassCaseCombination)
    MassCombination,
    // HybridDampingRotorOptions: parameter and hybrid damping (Case Control RSDAMP and SEDAMP)
    HybridDampingRotorOptionsSpecification,
    // HybridDamping: the hybrid modal damping a HybridDampingRotorOptions or a RotorHybridDamping names
    HybridDamping,
    // FluidMassElemList: a list of ShellQuad4 and ShellTria3 elements for virtual fluid mass (FluidVirtualMass)
    ElementList,
    // ModuleTranslation, ModuleRotation1, ModuleRotation2, ModuleMirror1, ModuleMirror2: a reposition of a module (a
    // ModuleMoveSequence names them by MVID)
    ModuleMove,
    // TableMultiVariable0, TableMultiVariable1, TableMultiVariable2 and TableScattered3D: tables of several variables
    MultiDimensionalTable,
    FatigueTable,          // TableFatigueHistory: the cyclic loading table of a fatigue load (FatigueLoad)
    ImperfectionCase,      // ImperfectionCase: a collection of imperfections (Case Control IMPERFECT)
    ImperfectionGeometry,  // ImperfectionGeometry: an imperfection that an ImperfectionCase names
    GeometricBoundary,     // GeomBoundaryCurve: a boundary curve that a LineInterface names
    AdaptivityCriterion,   // AdaptiveRefineCriterion: a mesh refinement criterion that an AdaptiveRefineControl names
    // AdaptiveRefineControl: the control of the local adaptive mesh refinement (Case Control HADAPT)
    AdaptivitySet,
    // RotorLineNodes, RotorModel3D, RotorAxisym and RotorSuperelement: a rotor (the ROTORID of the rotor dynamics
    // cards)
    Rotor,
    // DesignDiscreteValues: a list of discrete values (a DesignVar, DesignTopometryRegion, CampbellDiagram or
    // RotorRelativeSpin names one)
    DiscreteValueSet,
    // UserFileName: a file name that FatigueLoad, MicromechanicsCompositeMat, ResultFileModules and the load history
    // file table name
    UserDefinedName,
    FatigueProperty,       // FatigueProp: the fatigue properties a FatigueDefinition names
    FatigueLoad,           // FatigueLoad: a cyclic loading variation a FatigueEvent names
    // FatigueEvent and FatigueSequence: a loading event or a load sequence (they share one ID space)
    FatigueEvent,
    // EulerInitialRegions: the initial conditions of Euler regions (an EulerRegionProp names one)
    EulerInitialization,
    // InitialConditionRegion: a group of initial regions (an EulerInitialRegions names the group)
    EulerInitialRegions,
    // InitialConditionValues: the initial values of an Euler region (an InitialConditionRegion names one)
    InitialValueSet,
    // GasBagHeatTransfer: a set of heat loss definitions (an EulerLagrangeCoupling or a GasBag names one by HTRID)
    HeatLossSet,
    // GasBagConvection and GasBagRadiation: the convection or radiation model a GasBagHeatTransfer names
    HeatTransferModel,
    CosimulationGroup,     // CosimulationArea: the coupled area of a co-simulation (a CosimulationService names it)
    // CosimulationInputs: the input quantities of a co-simulation (a CosimulationService names them)
    CosimulationInput,
    // CosimulationOutputs: the output quantities of a co-simulation (a CosimulationService names them)
    CosimulationOutput,
    CosimulationService,   // CosimulationService: a co-simulation service (a CosimulationSelection names it)
    // WettedElemSide and WettedElemNodes: a wetted element of a fluid-structure service (one ID space)
    WettedElement,
    // WettedSurface: a wetted surface of a fluid-structure service (a WettedSurfaceLoad names it)
    WettedSurface,
    BrakeProperty,         // BrakeProp: the property of a brake system (a BrakeSystem names it)
    BrakeMotion,           // MOTION: the motion direction of a brake system (a BrakeSystem names it)
    // BrakeSqueal, BrakeSystem and ModuleBrakeSystem: a brake squeal analysis (Case Control BrakeSqueal)
    BrakeSqueal,
    // FrfComponent: a component of an FRF based assembly (the other FRF cards name it by ID or by name)
    FrfComponent,
    // NonlinearBushForceTables: the force tables of a rotor bushing (a NonlinearBushLoad3D names them)
    BushingForceSet,
    LoadStepControl,  // StepControlCriteria: the user criteria of load stepping (a NonlinearStepControl names it)
    // TemperatureTimeGroup: a group of grid points with one temperature history (a TimeTemperatureLoad names it)
    TemperatureGroup,
    MonteCarloSet,    // MonteCarloParams: the parameters of a Monte-Carlo simulation (Case Control MonteCarloParams)
    // DeactivatedElems: the elements that do not take part in an analysis (Case Control DeactivatedElems)
    DeactivatedElementSet,
    TransferPathSet,       // TransferPathSetup: the set-up of a transfer path analysis (Case Control TPASET)
    IterativeSolver,       // IterativeSolverOptions: the options of the iterative solver (Case Control SMETHOD)
    // MetadataGroup: a meta data group (the MetadataBooleanPairs, MetadataIntegerPairs, MetadataRealPairs and
    // MetadataTextPairs cards name it)
    MetadataGroup,
    Other
};

// What the model needs to know about a card type without looking at its fields.
struct CardTypeInfo
{
    std::string_view name;
    CardCategory category = CardCategory::Other;
    // The ID space the card's ID lives in (IdSpace::Group for a set ID shared by several cards, None for a card
    // without an ID).
    base::IdSpace idSpace = base::IdSpace::None;
    // True when a deck may define the same ID twice and the repeat is the same object, not an error (ScalarPoint and
    // ExtraPoint: the format reference allows repeated scalar point IDs). The reader keeps one row for the ID.
    bool repeatsAllowed = false;
};

} // namespace oor::model
