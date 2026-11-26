#pragma once

#include "oor/model/core/Model.hpp"

#include <vector>

namespace oor::analysis
{

// What the geometry says of one element, for the checks that look for degenerate elements. A value that does not apply
// to the element (the area of a solid) or cannot be computed (a missing node) is NaN.
struct ElementMeasure
{
    model::CardLocation location;
    double length = 0.0; // rods, tubes, bars and beams: between the end points
    double area = 0.0;   // shells
    double volume = 0.0; // solids (absolute)
    // A bar or beam whose orientation vector is zero or parallel to its axis, so that its element system is undefined.
    bool orientationUndefined = false;
};

// The size below which an element is collapsed, as a fraction of the size of the model. One linear tolerance for the
// three measures, so that the checks of the lengths, the areas and the volumes agree on what "no size" is: a length up
// to the tolerance, an area up to its square, a volume up to its cube. The tolerance is small on purpose: a volume
// limit at 1e-5 of the size of the model is 0.2 mm^3 in a model 60 m long, more than the volume of a sound tetrahedron
// with edges of a millimetre. What is found is an element whose measure is exactly zero (nodes at the same position,
// corners on a line or in a plane of the axes) or at the level of the round-off; a thin element that has a size is a
// matter of mesh quality, not of this tolerance.
inline constexpr double COLLAPSED_SIZE_RATIO = 1.0e-9;

// The measures of every rod, tube, bar, beam, shell and solid of a model, in the order of the registry and of the rows,
// and the size of the model (the diagonal of the bounding box of its grid points), which is what "zero" is relative
// to. Made once per validation, by the first check that needs it.
struct ElementMeasures
{
    std::vector<ElementMeasure> elements;
    double scale = 0.0;

    // The largest length, area and volume of a collapsed element (COLLAPSED_SIZE_RATIO of the size of the model, its
    // square and its cube). Zero for a model with no size: only an exact zero is then collapsed.
    [[nodiscard]] double collapsedLength() const noexcept { return COLLAPSED_SIZE_RATIO * scale; }
    [[nodiscard]] double collapsedArea() const noexcept { return collapsedLength() * collapsedLength(); }
    [[nodiscard]] double collapsedVolume() const noexcept { return collapsedArea() * collapsedLength(); }

    // An element that cannot be measured (a node that does not exist) is left out: the reference check reports it.
    [[nodiscard]] static ElementMeasures build(const model::Model& model);
};

} // namespace oor::analysis
