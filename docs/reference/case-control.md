# 3. Case control

Use `[case]` to choose what belongs to each load case and which results to request. Commands above the first subcase apply globally. `SubcaseStart` opens a numbered subcase. Its records extend to the next section or subcase header. [Commands A–Z](case-commands.md)

## Selecting loads and constraints

**Purpose.** `StaticLoadSelection` selects a load set already defined in `[model]`.

**Format.** `StaticLoadSelection;set-id`. The field is an integer identifying the load set. For the worked model, the referenced record is a [point force](../model-format-cards.md#pointforceload).

**Example.** These lines define two alternatives for the same structure. Set 12 is the axial force in the [rod model](introduction.md). To use the second subcase, add `PointForceLoad;13;2;;240.;1.;0.;0.` to its model section.

~~~text
[case]
SinglePointConstrSelection;8
DisplacementOutput;All
SubcaseStart;1
StaticLoadSelection;12
SubcaseStart;2
StaticLoadSelection;13
~~~

**Remarks.** Each subcase uses constraint set 8 and requests displacements. Only the selected force changes. A load ID refers to the set of records carrying that ID, so several forces can contribute to one selection.

## Requesting selected output

`DisplacementOutput;All` requests all nodes. To select nodes by ID, define a set and use its integer ID as the output value. In the rod model the following requests a displacement at node 2.

~~~text
SetDefinition;27;2
DisplacementOutput;27
~~~

Look up [DisplacementOutput](case-commands.md#displacementoutput), [SetDefinition](case-commands.md#setdefinition) and [SubcaseParameter](case-commands.md#subcaseparameter) for their individual record shapes.

~~~{toctree}
:hidden:
:maxdepth: 1

case-commands
~~~
