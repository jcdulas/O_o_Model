# Introduction

This reference describes the model records and their fields. Applications can build the same entities through the [in-memory API](../model-construction.md). The examples below show the OOS adapter’s text representation. Its executive, case and model sections select an analysis, define load cases and describe entities. O_o_Solver receives the resulting tables through its API.

## A rod in tension

Save the following file as `tie.oos`. The rod is 0.6 m long and has a cross-sectional area of 0.0004 m². A force of 120 N acts along its axis at node 2. Constraint set 8 fixes node 1 and leaves only the axial displacement free at node 2.

~~~text
[executive]
SolutionSequence;LinearStatics
[case]
TitleText;Tie rod in tension
DisplacementOutput;All
SubcaseStart;1
SinglePointConstrSelection;8
StaticLoadSelection;12
[model]
Node;1;;0.;0.;0.
Node;2;;0.6;0.;0.
Rod2;20;30;1;2
RodProp;30;40;0.0004
IsoMat;40;7.0e10;;0.33;2700.
SinglePointConstrList;8;123456;1
SinglePointConstrList;8;23456;2
PointForceLoad;12;2;;120.;1.;0.;0.
Parameter;WeightToMass;1.0
~~~

## Follow a reference

Start at `StaticLoadSelection;12`. The selected load has set ID 12 and acts on node 2. To find the stiffness data, follow element 20 to property 30, then to material 40. The property supplies the area and the material supplies Young’s modulus. [Bulk data](bulk-data.md) shows how to read the fields in that chain.

The [command-line examples](command-line.md) read this file and report two nodes and one rod. The [parameter query](parameters.md#inspect-an-explicit-value) finds the explicit mass conversion factor.
