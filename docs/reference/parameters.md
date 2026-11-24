# 5. Parameters

A parameter carries a named value such as a mass conversion factor, a numerical tolerance or an output setting. Use the [alphabetical index](parameter-index.md) to check the exact spelling, type, fixed default and enumerated values. A catalogue default describes the input convention. Whether a setting affects a calculation depends on the analysis and its implementation.

## Parameter entry and scope

**Purpose.** `WeightToMass` records the conversion factor between weight and mass.

**Format.** In `[model]`, write `Parameter;WeightToMass;value`. The field is real and its catalogue default is `1`. In `[case]`, use `SubcaseParameter;name;value` to record a case-control parameter. A record after a subcase header belongs to that subcase.

**Example.** The [rod model](introduction.md) explicitly supplies `Parameter;WeightToMass;1.0`. Its stored value is numerically equal to the default. [WeightToMass entry](parameter-index.md#weighttomass)

**Remarks.** `paramsTable` distinguishes explicit records from supplied catalogue defaults with `isDefault`. The `subcase` column distinguishes a model parameter (null), global case control (0), and numbered subcases.

## Inspect an explicit value

After reading `tie.oos` as in [Command line](command-line.md), run either snippet while the deck is live. Both report one row for the explicit `WeightToMass` record. With `withDefaults` enabled, the query also returns fixed defaults for requested names absent from the model.

**JavaScript / WebAssembly**

~~~javascript
const table = reader.runQuery("paramsTable", {
  deck, args: { names: ["WeightToMass"], withDefaults: false }
});
try {
  console.log(table.rowCount()); // 1
} finally {
  table.delete();
}
~~~

**Python / native C++**

~~~python
table = deck.query("paramsTable", names=["WeightToMass"], withDefaults=False)
print(len(table))  # 1
~~~

## Parameters by task

| Parameter family | Where to start | Related model data |
| --- | --- | --- |
| Model input and translation | [InputUnit](parameter-index.md#inputunit), [InputProcessorDebug](parameter-index.md#inputprocessordebug) | [Text values and field conventions](../model-format.md#values) |
| Geometry processing | [GeometryDeclarations](parameter-index.md#geometrydeclarations), [ShellNormalAngle](parameter-index.md#shellnormalangle) | [Node](../model-format-cards.md#node), [SurfaceEdge](../model-format-cards.md#surfaceedge) |
| Solution control | [AutoSingularityConstr](parameter-index.md#autosingularityconstr), [WeightToMass](parameter-index.md#weighttomass) | [Constraints and loads](case-control.md#selecting-loads-and-constraints) |
| Eigenvalue extraction | [EigenFilter](parameter-index.md#eigenfilter), [EigenShift1](parameter-index.md#eigenshift1) | [LanczosEigenMethod](../model-format-cards.md#lanczoseigenmethod) |
| Transient response | [StartTime](parameter-index.md#starttime), [TransientStatic](parameter-index.md#transientstatic) | [TransientTimeSteps](../model-format-cards.md#transienttimesteps) |
| Frequency response | [FreqDuplicateTolerance](parameter-index.md#freqduplicatetolerance), [HighFreqLimit](parameter-index.md#highfreqlimit) | [DisplacementOutput](case-commands.md#displacementoutput) |
| Nonlinear solution | [NonlinearMaxLoad](parameter-index.md#nonlinearmaxload), [NonlinearMinLoad](parameter-index.md#nonlinearminload) | [NonlinearStaticParams](../model-format-cards.md#nonlinearstaticparams) |
| Results processing | [ConstraintPrint](parameter-index.md#constraintprint), [OutputGeometry](parameter-index.md#outputgeometry) | [ResultFileParams](../model-format-cards.md#resultfileparams) |
| Topology and design optimization | [TopologyConvergence](parameter-index.md#topologyconvergence), [DesignOptimOutput](parameter-index.md#designoptimoutput) | [DesignTopologyRegion](../model-format-cards.md#designtopologyregion), [DesignOptimParams](../model-format-cards.md#designoptimparams) |

## Archive and analysis lookup

| Question | Reference |
| --- | --- |
| Where are geometry, connectivity and model controls stored? | [Native model datasets](../archive-format.md#native-model) |
| Where are result components and steps stored? | [Result tables](../archive-format.md#result-tables) |
| Which archive versions can the Model open? | [Archive compatibility](../archive-format.md#versions) |
| Which solution does a setting belong to? | Read the [solution sequence](initialization.md#executive-records) and [case selections](case-control.md). The Model catalogue defines record types and defaults. Solver support is specific to the selected analysis. |

~~~{toctree}
:hidden:
:maxdepth: 1

parameter-index
~~~
