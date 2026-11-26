# `query`

Query plans, operators, query tables, Arrow export, apply, named queries.

- Headers: `include/oor/query/`. Sources: this folder. Tests: `tests/cpp/query/`.
- May use: `analysis`, `results`, `model`, `deck`, `io`, `base` (checked by `tools/check_layering.py`).
- Start reading at `plan/Query.hpp` (the builder and the executor), then `plan/QuerySource.hpp` (what a source and a join
  target give) and `table/QueryTable.hpp` (the result).
- `table/`: `QueryColumn`, `QueryTable`, `ArrowExport` (the Arrow C Data Interface, no copy), `CsvExport`.
- `operators/`: `Expression` and `ExpressionEvaluator`, `SortOperator`, `GroupOperator`, `ColumnOps`, `ExecutionContext`.
- `plan/`: `Query`, `QueryPlan`, `QueryFrame` (private), `TableSource`.
- `providers/`: the columns of the cards of a model: `StoredColumnCatalogue`, `CardColumns`, `ComputedColumns`,
  `ModelSource`.
- `apply/`: `CellValue`, `ColumnEdits`, `ChangeTracker`, `EditableTable`, `QueryApply` (edits of a result and `apply`).
- `named/`: the named queries: `NamedQuery`/`QueryBase`, `QueryInfo` (the catalogue entry), `QueryValue` (typed
  arguments), `NamedQueryRegistry` (finds, checks and runs a query, applies `columns`/`sort`/`limit`), `TableBuilder`, `common/` (helpers shared
  by the queries), and one folder per family under `topology/` (`t1_inventory` ... `t13_comparison`), one `.cpp` for each query. The components, the
  boundaries and the revision stamps they use are in `src/analysis/components/`.

## Conventions

- A blank P2 of a `BeamDistributedLoad` is P1, a uniform load, also when X2 is given (`lineLoadsTable`).
- A range of a `SinglePointConstrList` names every point in it, grid points and scalar points, which share the node
  ID space. A scalar point is taken only when the components of the card are blank or 0, the one degree of freedom it
  has.
- A non-structural mass row carries the property card it names (`propertyType` of `nonStructMassTable`), so that the
  solver reaches the elements of that property card alone.
- A shell strain table written as membrane strains and curvatures gives the strains of the fibres Z1 and Z2: the
  membrane strain less the fibre distance times the curvature, with the fibre distances of the model
  (`providers/quantities/ElementModelFacts.hpp`). Without the model it gives the membrane strain alone, at fibre
  distance 0. A curvature is never listed as a strain.
- The values of a `Bar2` at the four recovery points of an end are its bending stresses alone. The combined
  extremes of the end (`o1`, `o2`) add the axial stress, which is the same at every point; they are read from the
  table when it stores them, else made from the recovery points.
- The failure index of a ply is the number the solver writes (`providers/quantities/CompositeQuantities.hpp`). For
  Hill, the allowable of each term follows the sign of what it multiplies: X by the sign of the stress along the
  fibres, Y by that of the transverse stress, and the X of the interaction term by the sign of their product. For
  Tsai-Wu, F12 is the value of the card (0 when blank) and its term is 2 F12 s1 s2. A blank compression allowable is
  the tension one. The strength ratio is the factor on the loads that brings the index to 1: the index itself for the
  linear theories, the root of the quadratic for Hill, Hoffman and Tsai-Wu.
- A left join keeps a row that holds no ID (a blank reference, an empty list) once, its joined columns null.
- A query on a table (`columns`, `sort`, `limit`, an envelope, an edited table) gives a table of the same data
  contract version, so that its package still says which contract its columns follow.
