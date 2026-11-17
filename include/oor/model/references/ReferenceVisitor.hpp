#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>
#include <string_view>

namespace oor::model
{

// What a reference field points to. Most are ID spaces; the others are sets that several cards share.
enum class ReferenceTarget
{
    Node,        // a Node, or any other point of the node ID space (a scalar point is one)
    NodeInRange, // a node ID in a THRU range: renumbered like a node, but allowed not to exist (the solver skips the
                 // gaps)
    // a field that takes a grid point or a scalar point (SpringDofProperty G1, Beam2 SA): renumbered like a node; it
    // may name a scalar point that no ScalarPoint defines (the format reference lets a scalar element define its scalar
    // points by naming them), so it is allowed not to exist
    ScalarOrGridPoint,
    Element,
    // an element ID in a THRU range (ShellPressureLoad, PlateTemperatureLoad, LineElemTemperatureLoad): renumbered like
    // an element, but allowed not to exist (the solver skips the gaps)
    ElementInRange,
    // a HeatSurfaceSide, HeatSurfaceNodes or HeatSurfaceProperty: the heat transfer surface element (FreeConvection,
    // HeatFluxSurfaceLoad1, RadiationToSpace, ...)
    SurfaceElement,
    SurfaceElementInRange, // a surface element in a THRU list: renumbered like one, but allowed not to exist
    Property,
    // a property ID of a non-structural mass card (NonStructMass, NonStructMass1, NonStructMassLumped,
    // NonStructMassLumped1): renumbered like a property, but allowed not to exist (undefined property IDs are ignored)
    PropertyInRange,
    // an IsoMat, AnisoMat2D, ...; a field that names the material of a property may also name a HeatIsoMat or
    // HeatAnisoMat (below)
    Material,
    // a HeatIsoMat or HeatAnisoMat (the MID of a HeatIsoMatTemperature, HeatAnisoMatTemperature, FreeConvectionProp,
    // ForcedConvectionProp)
    ThermalMaterial,
    Coordinate,
    DynamicTable,
    MaterialTable,
    // a TableStress1 or TableStressTemperature (IsoMatStressDependent, CreepMat, HyperelasticPolynomialMat, ...)
    StressTable,
    HeatTable,                      // a TableHeat1 or TableHeatTwoVariables
    // a TableModalDamping1 (SDAMPING also takes a TABLEDi: it is looked for in the dynamic table space too)
    HybridDampingRotorOptionsTable,
    RandomTable,                    // a TableRandomSpectrum1 or TableGustSpectrum (RandomSpectralDensity)
    Method,
    LoadCombinationSet,  // a LOAD/FORCE/... set ID
    ConstraintSet,       // a SinglePointConstr/SinglePointConstrUnion/MultiPointConstr set ID
    // the set ID of a FreqResponseLoad1/TransientTableLoad1/DynamicLoadScale/... card (a DynamicLoadCombination term)
    DynamicLoadSet,
    ExcitationSet,       // the set a dynamic load excites with: a DynamicLoadScale set or a static load set (EXCITEID)
    // the EXCITEID that a StaticLoadSequence card defines: not reported (it is the definition), renumbered like
    // ExcitationSet, and found by an EXCITEID that names it
    ExcitationDefined,
    FrequencySet,        // the set ID of FreqList, FreqLinearSteps1 to FreqModeFractions5
    ComplexMethod,       // the ID of a ComplexEigenMethod (and of the ComplexEigenPoles cards that go with it): CMETHOD
    DelaySet,            // the set ID of a DynamicLoadDelay (the DELAY field of a dynamic load)
    PhaseSet,            // the set ID of a DynamicLoadPhase
    TimeStepSet,         // the ID of a TransientTimeSteps or NonlinearTimeSteps
    NonlinearSet,        // the ID of a NonlinearStaticParams (and of its ArcLengthParams)
    RandomSet,           // the set ID of RandomSpectralDensity and RandomTimeLags cards
    TransferFunctionSet, // the set ID of TF cards
    // the set ID of TransientInitialCondition cards (IC also names a set of temperatures: a NodeTemperatureLoad or
    // DefaultTemperatureLoad set)
    InitialConditionSet,
    Set,                 // an IdListSet1/TypedListSet3 ID
    HeatBoundaryProperty,     // the PID of a HeatSurfaceProp (HeatSurfaceProperty)
    ConvectionProperty,       // the PCONID of a FreeConvectionProp (FreeConvection)
    ForcedConvectionProperty, // the PCONID of a ForcedConvectionProp (ForcedConvection)
    RadiationMaterial,        // the RADMID of a RadiationProp (the RADMIDF and RADMIDB of the surface elements)
    ViewFactorFaceFactor,     // the IVIEW of a ViewFactorFace (the IVIEWF and IVIEWB of the surface elements)
    // the ICAVITY of a RadiationCavity, RadiationCavityList, RadiationExchangeMatrix or ViewFactorIntegration
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
    // what Case Control BCONTACT=n selects: a ContactTable1 or ContactTable, or directly a ContactPair
    ContactSelection,
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
    DesignVariable,       // the ID of a DesignVar (DVIDi, DDVID, IDVi)
    DesignEquation,       // the EQID of a DesignEquation
    // a DesignResp1, DesignResp2 or DesignResp3 (RID of a DesignConstr, NRk and NRRk of a DesignResp2, DESOBJ)
    DesignResponse,
    // the DCID of a DesignConstr or a DesignConstrUnion (DCi of a DesignConstrUnion, DESSUB, DESGLB)
    DesignConstraintSet,
    // the ID of a DesignPropRelation1 or a DesignPropRelation2 (DPIPi, DPI2Pi of a DesignResp2 or DesignResp3)
    PropertyRelation,
    MaterialRelation,     // the ID of a DesignMatRelation1 or a DesignMatRelation2 (DMIMi, DMI2Mi)
    ConnectivityRelation, // the ID of a DesignElemRelation1 or a DesignElemRelation2 (DCICi, DCI2Ci)
    // an AeroLiftingPanel1 to AeroPistonPanel5 (the CAERO of a SPLINE, a B of an AeroLiftingPanelProp1, a CAERO list of
    // an AeroComponent)
    AeroElement,
    // the CAERO of an AeroSurfaceSpline4: an AeroLiftingPanel1 to AeroPistonPanel5, or the component (CMPID) of the
    // AeroQuad4 and AeroTria3 of an aerodynamic mesh (format reference AeroSurfaceSpline4: "aerodynamic component");
    // renumbered like a CAERO where a CAERO has the ID
    AeroPanelOrComponent,
    AeroBox, // an aerodynamic box: an ID in the range a CAERO takes from its EID on (BOX1, ID1, BOXID of a SPLINE, the
             // items of an AeroBoxList). It may name nothing (an AeroBoxList of a Mach box or an aerodynamic mesh holds
             // other numbers) and is renumbered with the CAERO that owns it
    AeroProperty,       // an AeroLiftingPanelProp1 to AeroPistonProp5 (the PID of a CAERO)
    // an AeroBoxList (an AeroControlSurface, an AeroComponent, an AeroSurfaceSpline4 or an AeroBeamSpline5)
    AeroList,
    // an AeroFactorList (the divisions of a CAERO, the arrays of a PAERO, the data of an AeroControlSchedule)
    AeroFactor,
    AeroFlutterFactor,  // an AeroFlutterFactors (the DENS, MACH and RFREQ or VEL of an AeroFlutter)
    AeroControlSurface, // an AeroControlSurface (the AESID of an AeroControlSchedule)
    AeroTrimSet,        // an AeroTrim or AeroTrim2 (Case Control TRIM)
    AeroFlutterSet,     // a FLUTTER (Case Control FMETHOD)
    AeroGustSet,        // an AeroGust (Case Control AeroGust)
    DivergenceSet,      // an AeroDivergence (Case Control AeroDivergence)
    ControlSchedule,    // an AeroControlSchedule (Case Control AeroControlSchedule)
    // an AeroControlVector (Case Control AEUXREF, the UXID of an AeroDownwash, AeroForceVector or AeroPressureVector)
    ControlVector,
    AeroNode,           // an AeroNode (the points of an AeroQuad4 or an AeroTria3)
    AeroScale,          // an AeroNodeScale (the ASID of an AeroNode)
    // a superelement number: a part (BEGIN SUPER=n), a list superelement (SuperelementInteriorNodes,
    // SuperelementElemTransfer, SuperelementBulkOptions, SuperelementExteriorPoints, SuperelementCopyPoints, or the
    // SEID of a Node) or 0, the residual structure (the SEID of nearly every card of the family, and of the Case
    // Control SUPER, SEALL, SEDR, ...)
    Superelement,
    MassIncrement, // the number of a mass increment: BEGIN MASSID=n, or the MASSID of BEGIN SUPER=n MASSID=m (the IDi
                   // of a MassCaseCombination); 0 is the base mass case
    MassCombination, // a MassCaseCombination (Case Control MassCaseCombination)
    // an AeroSurfaceSpline1 to AeroFiniteBeamSpline7, AeroUserSpline, AeroSplineStripBlend, AeroSplineCurveBlend or
    // AeroRigidSpline (SID1 and SID2 of a SPBLND or AeroSplineRelaxation)
    AeroSpline,
    HybridDampingRotorOptionsSpecification, // a HybridDampingRotorOptions (Case Control RSDAMP and SEDAMP)
    // a HybridDamping (the HYBRID of a HybridDampingRotorOptions, the HYBDAMPi of a RotorHybridDamping)
    HybridDamping,
    ElementList,                            // a FluidMassElemList (ELIST1 and ELIST2 of a FluidVirtualMass)
    // a ModuleTranslation, ModuleRotation1, ModuleRotation2, ModuleMirror1 or ModuleMirror2 (the MVIDi of a
    // ModuleMoveSequence)
    ModuleMove,
    // a TABL3Di or TableScattered3D (the SOL 400 materials, a GeneralFrame3); a TABLEMi field falls back to it
    MultiDimensionalTable,
    // the FID of an ElastoPlasticMat: a TableStress1 or TableStressTemperature, or a TABL3Di (format reference
    // ElastoPlasticMat: "TableStress1 or TABL3D"); looked up and renumbered like StressTable where a stress table has
    // the ID
    StressOrMultiDimensionalTable,
    FatigueTable,                  // a TableFatigueHistory (the TID of a FatigueLoad)
    ImperfectionCase,              // an ImperfectionCase (Case Control IMPERFECT)
    ImperfectionGeometry,          // an ImperfectionGeometry (the IMPFIDi of an ImperfectionCase)
    GeometricBoundary,             // a GeomBoundaryCurve (the BIDs of the LIST of a LineInterface)
    AdaptivityCriterion,           // an AdaptiveRefineCriterion (the CRITID of an AdaptiveRefineControl)
    AdaptivitySet,                 // an AdaptiveRefineControl (Case Control HADAPT)
    // a RotorLineNodes, RotorModel3D, RotorAxisym or RotorSuperelement (the ROTORID of a RotorRelativeSpin,
    // RotorTransientSpin, ReferenceRotor, SuperelementReferenceRotor, RotorInitialBend and RotorHybridDamping)
    Rotor,
    // a DesignDiscreteValues (the DesignDiscreteValues of a DesignVar, the DSVID of a DesignTopometryRegion, the
    // DDVALID of a CampbellDiagram)
    DiscreteValueSet,
    // a UserFileName (the UID of the load history file table, the UDID of a ResultFileModules, a FatigueLoad file)
    UserDefinedName,
    FatigueProperty,     // a FatigueProp (the PFTGID of a FatigueDefinition)
    FatigueLoad,         // a FatigueLoad (the FLOADi of a FatigueEvent)
    FatigueEvent,        // a FatigueEvent or a FatigueSequence (the FIDi of a FatigueSequence)
    EulerInitialization, // an EulerInitialRegions (the SID of an EulerRegionProp)
    // the group of InitialConditionRegion cards that share a TSID (the TSID of an EulerInitialRegions)
    EulerInitialRegions,
    InitialValueSet,     // an InitialConditionValues (the second TSID of an InitialConditionRegion)
    // the GasBagHeatTransfer cards that share an HTRID (the HTRID of an EulerLagrangeCoupling and of a GasBag)
    HeatLossSet,
    HeatTransferModel,   // a GasBagConvection or a GasBagRadiation (the HTRTYPID of a GasBagHeatTransfer)
    CosimulationGroup,   // a CosimulationArea (the GRPID1 and GRPID2 of a CosimulationService)
    CosimulationInput,   // a CosimulationInputs (the PHYINP of a CosimulationService)
    CosimulationOutput,  // a CosimulationOutputs (the PHYOUT of a CosimulationService)
    CosimulationService, // a CosimulationService (the CSRVIDi of a CosimulationSelection)
    WettedElement,       // a WettedElemSide or a WettedElemNodes (the WEIDi of a WettedSurface)
    WettedSurface,       // a WettedSurface (the WSID of a WettedSurfaceLoad)
    BrakeProperty,       // a BrakeProp (the BProp_ID of a BrakeSystem)
    BrakeMotion,         // a MOTION (the motion IDs of a BrakeSystem)
    BrakeSqueal,         // a BrakeSqueal, a BrakeSystem or a ModuleBrakeSystem (Case Control BrakeSqueal)
    // a FrfComponent (the COMPID of a FrfConnection, FrfFlexibleConnection, FrfReleasedDofs, FrfSinglePointConstr,
    // FrfAssemblyLoadDelay, FrfAssemblyLoadScale and FrfAssemblyLoadPhase)
    FrfComponent,
    BushingForceSet,  // a NonlinearBushForceTables (the LID of a NonlinearBushLoad3D)
    LoadStepControl,  // a StepControlCriteria (the table of a NonlinearStepControl)
    TemperatureGroup, // a TemperatureTimeGroup (the GROUP_ID of a TimeTemperatureLoad)
    MonteCarloSet,    // a MonteCarloParams (Case Control MonteCarloParams)
    DeactivatedElementSet, // a DeactivatedElems (Case Control DeactivatedElems)
    TransferPathSet,       // a TransferPathSetup (Case Control TPASET)
    IterativeSolver,       // an IterativeSolverOptions (Case Control SMETHOD)
    // a MetadataGroup (the ABSTID of a MetadataBooleanPairs, MetadataIntegerPairs, MetadataRealPairs and
    // MetadataTextPairs)
    MetadataGroup,
    Other
};

// Visits the ID fields of a card that point to other cards. Renumbering, validation and reference resolution are
// visitors: each card type lists its references once (CardTable::visitReferences), so that those operations work on
// every card type.
//
// visit() receives the field name, what it points to and the current ID (0 where the field is blank); it returns the
// ID the field should hold afterwards. A visitor that only looks returns `id` unchanged.
class ReferenceVisitor
{
public:
    virtual ~ReferenceVisitor() = default;
    virtual base::EntityId visit(std::string_view field, ReferenceTarget target, base::EntityId id) = 0;

    // A reference to an ID that lives in the model of another superelement: the grid points of SuperelementConnection,
    // SuperelementBoundarySearch and SuperelementExcludedNodes name those of superelement SEIDA, and the design
    // variables of SuperelementDesignLink those of the part they name. The ID is looked up (and, in a renumbering,
    // rewritten) in `Model::superelementModel(superelement)`: the part BEGIN SUPER=superelement when the deck has one,
    // else the residual structure. A visitor that does not follow references across the parts keeps the default, which
    // leaves the ID as it is.
    virtual base::EntityId visitInSuperelement([[maybe_unused]] std::string_view field,
                                               [[maybe_unused]] ReferenceTarget target, base::EntityId id,
                                               [[maybe_unused]] base::EntityId superelement)
    {
        return id;
    }

    // A reference to an ID that lives in a part of the deck named by its BEGIN kind and number: the IdListSet1 and
    // TypedListSet3 of a TrimComponentCoupling or TrimComponentCoupling1D are in the part BEGIN BULK TRMC=TID, the grid
    // points an MD card places in module n are in BEGIN MODULE=n (or in the primary module that module n copies). The
    // ID is looked up (and, in a renumbering, rewritten) in the models PartScopes::modelsOfPart gives. A visitor that
    // does not follow references across the parts keeps the default, which leaves the ID as it is.
    virtual base::EntityId visitInPart([[maybe_unused]] std::string_view field, [[maybe_unused]] ReferenceTarget target,
                                       base::EntityId id, [[maybe_unused]] std::string_view partKind,
                                       [[maybe_unused]] std::int64_t partId)
    {
        return id;
    }
};

} // namespace oor::model
