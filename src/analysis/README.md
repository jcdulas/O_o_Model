# `analysis`

Geometry, frames, sections, laminates, mass, quality, adjacency, components, connections, validation.

- Headers: `include/oor/analysis/`. Sources: this folder. Tests: `tests/cpp/analysis/`.
- May use: `results`, `model`, `deck`, `io`, `base` (checked by `tools/check_layering.py`).
- Start reading at `geometry/ElementGeometry.hpp` (geometry) and `mass/MassCalculator.hpp` (mass, sections and laminates).
- Mesh quality and adjacency (`quality/`, `adjacency/`): start at `quality/MeshQuality.hpp` and `adjacency/MeshAdjacency.hpp`.
- Validation (`validation/`): start at `validation/engine/CheckRegistry.hpp` and `validation/engine/ValidationEngine.hpp`; one class and one file per check in the folder of its family.
- Components and connections (`components/`, `connections/`): start at `components/ComponentModel.hpp` (components, boundaries, stamps), `components/GroupSet.hpp` (groups and zones) and `connections/FastenerPiercings.hpp` (where Fastener and Weld pierce the shells, private helpers in `connections/fasteners/`), then `connections/Spiders.hpp` and `connections/ConnectionClusters.hpp`, and `connections/ContactSearch.hpp` (contact between bodies: `ContactBodies`, `ContactPairs`, `ContactSurfaces`, private helpers in `connections/contact/`).

## Conventions

Mesh quality (`quality/QualityMetrics.hpp`, `quality/GeometryCheckThresholds.hpp`):

- The skew of a quadrilateral is 90 degrees less the angle between the lines that join the middles of its opposite
  sides. `QuadSkewLimit` is the smallest angle allowed between those lines (30 by default): an element fails when its
  skew is above 90 less the limit.
- A triangle is tested on its smallest and largest vertex angles (`TriangleMinAngle`, `TriangleMaxAngle`).
- The limits are named by the keywords of the `GeometryCheck` statement, whatever the case of their letters. The
  defaults are changed by the statements of the deck, the last one that names a keyword counting. A metric that does
  not apply to an element fails nothing.

Collapsed elements (`validation/engine/ElementMeasures.hpp`):

- One linear tolerance, 1e-9 of the size of the model (the diagonal of the bounding box of its grid points), says
  what has no size: a length up to the tolerance, an area up to its square, a volume up to its cube. A thin element
  that has a size is a matter of mesh quality, not of this tolerance.
- A solid collapsed to no volume holds no point (`geometry/PointLocator.hpp`). A face on which a collapsed solid names
  a grid point twice is listed with that grid point once (`adjacency/MeshAdjacency.hpp`).

Mass (`mass/MassCalculator.hpp`, `mass/SectionFormulas.hpp`):

- The structural mass of a beam is on its neutral axis, which the property gives from the line of the shear centres,
  as in the mass matrix of the solver. The non-structural mass is at its own centre of gravity.
- An element is a point mass: the rotary inertia of the section of a line element is not counted.
- The volume of an axisymmetric element is 2 pi times the integral of the radius over its cross-section, by the
  2 x 2 Gauss rule for a quadrilateral.

Isotropic materials (`validation/compatibility/`):

- A value the card gives is an error when it cannot be a material: a Young's modulus that is zero or negative
  (`compat.iso-mat-modulus`), a Poisson's ratio above 0.5, or -1 or less (`compat.iso-mat-poisson`; 0.5 itself is
  accepted), a shear modulus that is negative, or zero where a property needs it (`compat.iso-mat-shear-modulus`).
- A value derived from blank fields is a warning, since the card wrote no such value: a Poisson's ratio above 0.5
  from E and G (`compat.iso-mat-poisson-derived`), and a material given with E alone that a bar, a beam or a shell
  uses, which then has no shear modulus (`compat.iso-mat-shear-modulus-blank`).

Constraints and subcases (`validation/engine/ValidationSupport.hpp`, `components/SubcaseCombination.hpp`):

- The constraint sets judged together are those one subcase selects: the sets of two subcases are never active
  together. Without a Case Control, every multipoint constraint set is taken with every single point constraint set.
- The coefficients of a subcase combination apply to the plain subcases before it, the last ones first; another
  combination between them is not counted.
