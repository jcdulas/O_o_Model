#include "oor/query/providers/quantities/ElementModelFacts.hpp"

#include "oor/analysis/frames/StoredFrames.hpp"
#include "oor/analysis/geometry/ElementGeometry.hpp"
#include "oor/model/cards/elements/shellQuad4/ShellQuad4Table.hpp"
#include "oor/model/cards/elements/shellQuad4Drilling/ShellQuad4DrillingTable.hpp"
#include "oor/model/cards/elements/shellQuad8/ShellQuad8Table.hpp"
#include "oor/model/cards/elements/shellTria3/ShellTria3Table.hpp"
#include "oor/model/cards/elements/shellTria3Drilling/ShellTria3DrillingTable.hpp"
#include "oor/model/cards/elements/shellTria6/ShellTria6Table.hpp"
#include "oor/model/cards/materials/isoMat/IsoMatTable.hpp"
#include "oor/model/cards/properties/compProp/CompPropTable.hpp"
#include "oor/model/cards/properties/compPropGlobal/CompPropGlobalTable.hpp"
#include "oor/model/cards/properties/rodProp/RodPropTable.hpp"
#include "oor/model/cards/properties/shellProp/ShellPropTable.hpp"
#include "oor/model/cards/properties/solidProp/SolidPropTable.hpp"

#include <cmath>

namespace oor::query
{

namespace
{

// The IsoMat with this ID, or nothing (another kind of material, a missing one).
std::optional<model::IsoMatCard> isotropicMaterial(const model::Model& model, base::EntityId mid, std::string& why)
{
    const auto location = model.locate(base::IdSpace::Material, mid);
    if (!location)
    {
        why = "the material " + std::to_string(mid) + " does not exist";
        return std::nullopt;
    }
    if (location->table != model::typeIndexOf<model::IsoMatTable>())
    {
        why =
            "the material " + std::to_string(mid) +
            " is not an IsoMat (only a linear isotropic material gives a stress from a strain, or a strain from a "
            "stress)";
        return std::nullopt;
    }
    const model::IsoMatCard card =
        static_cast<const model::IsoMatTable&>(*model.findTable(location->table)).card(location->row);
    if (!(card.youngsModulus > 0.0))
    {
        why = "the IsoMat " + std::to_string(mid) + " has no Young's modulus";
        return std::nullopt;
    }
    return card;
}

// The corners of a shell element card: their grid points and the thicknesses the card gives them (negative: blank),
// with TFLAG (1: the thicknesses are fractions of the thickness of the property).
struct ShellCorners
{
    std::size_t count = 0;
    std::array<std::int32_t, 4> nodes{};
    std::array<double, 4> thickness{};
    std::int32_t thicknessFlag = 0;
};

// The corners of the card at `element` when it is a card of the table TableT (the corners come first in its nodes).
template <typename TableT>
bool readCorners(const model::Model& model, const model::CardLocation& element, ShellCorners& corners)
{
    if (element.table != model::typeIndexOf<TableT>())
        return false;
    const auto card = static_cast<const TableT&>(*model.findTable(element.table)).card(element.row);
    corners.count = card.cornerThickness.size();
    for (std::size_t corner = 0; corner < corners.count; ++corner)
    {
        corners.nodes[corner] = card.nodes[corner];
        corners.thickness[corner] = card.cornerThickness[corner];
    }
    corners.thicknessFlag = card.thicknessFlag;
    return true;
}

std::optional<ShellCorners> shellCornersOf(const model::Model& model, const model::CardLocation& element)
{
    ShellCorners corners;
    if (readCorners<model::ShellQuad4Table>(model, element, corners) ||
        readCorners<model::ShellTria3Table>(model, element, corners) ||
        readCorners<model::ShellQuad8Table>(model, element, corners) ||
        readCorners<model::ShellTria6Table>(model, element, corners) ||
        readCorners<model::ShellQuad4DrillingTable>(model, element, corners) ||
        readCorners<model::ShellTria3DrillingTable>(model, element, corners))
        return corners;
    return std::nullopt;
}

} // namespace

ElementModelFacts::ElementModelFacts(const ResultQueryContext& context, std::size_t set)
    : m_context(context), m_set(set), m_model(context.modelOf(set))
{
}

const ShellFacts& ElementModelFacts::shell(std::int32_t resultEid)
{
    const auto found = m_shells.find(resultEid);
    if (found != m_shells.end())
        return found->second;
    ShellFacts facts;
    const auto card = m_context.elementCard(m_set, resultEid);
    do
    {
        if (m_model == nullptr)
        {
            facts.why = "no model is attached to the results";
            break;
        }
        if (!card.linked || card.pid == 0)
        {
            facts.why = "the element is not linked to a card of the model that has a property";
            break;
        }
        const auto property = m_model->locate(base::IdSpace::Property, card.pid);
        if (!property || property->table != model::typeIndexOf<model::ShellPropTable>())
        {
            facts.why = "the property " + std::to_string(card.pid) + " is not a ShellProp";
            break;
        }
        const model::ShellPropCard shell =
            static_cast<const model::ShellPropTable&>(*m_model->findTable(property->table)).card(property->row);
        if (shell.membraneMatId <= 0 || (shell.bendingMatId != 0 && shell.bendingMatId != shell.membraneMatId) ||
            shell.couplingMatId != 0 || std::fabs(shell.bendingStiffnessRatio - 1.0) > 1e-12)
        {
            facts.why =
                "the ShellProp " + std::to_string(card.pid) +
                " does not have one material for membrane and bending with the plain bending stiffness (MID1 = MID2, "
                "12I/T**3 = 1, no MID4)";
            break;
        }
        std::string why;
        const auto material = isotropicMaterial(*m_model, shell.membraneMatId, why);
        if (!material)
        {
            facts.why = why;
            break;
        }
        const auto element = m_model->locate(base::IdSpace::Element, card.modelId);
        double thickness = shell.thickness;
        if (element)
        {
            const double geometric =
                analysis::ElementGeometry::of(*m_model, *element, analysis::bit(analysis::Quantity::Thickness))
                    .thickness;
            if (std::isfinite(geometric) && geometric > 0.0)
                thickness = geometric;
        }
        if (!(thickness > 0.0))
        {
            facts.why = "the shell has no thickness";
            break;
        }
        facts.ok = true;
        facts.thickness = thickness;
        // a blank fibre distance is half the thickness of the element; one given is
        // as given
        facts.z1 = shell.fiberDistance1.value_or(-0.5 * thickness);
        facts.z2 = shell.fiberDistance2.value_or(0.5 * thickness);
        facts.e = material->youngsModulus;
        facts.nu = material->poissonRatio;
        facts.g = material->shearModulus > 0.0 ? material->shearModulus
                                               : material->youngsModulus / (2.0 * (1.0 + material->poissonRatio));
        facts.pid = card.pid;
    } while (false);
    return m_shells.emplace(resultEid, std::move(facts)).first->second;
}

const ElementModelFacts::ShellPlaces& ElementModelFacts::shellPlaces(std::int32_t resultEid)
{
    const auto found = m_places.find(resultEid);
    if (found != m_places.end())
        return found->second;
    ShellPlaces places;
    const auto card = m_context.elementCard(m_set, resultEid);
    do
    {
        if (m_model == nullptr || !card.linked || card.pid == 0)
            break;
        const auto element = m_model->locate(base::IdSpace::Element, card.modelId);
        const auto property = m_model->locate(base::IdSpace::Property, card.pid);
        if (!element || !property)
            break;
        const std::optional<ShellCorners> corners = shellCornersOf(*m_model, *element);
        if (!corners)
            break;
        const model::CardTable& table = *m_model->findTable(property->table);
        double thickness = 0.0;
        bool laminate = false;
        if (property->table == model::typeIndexOf<model::ShellPropTable>())
        {
            const model::ShellPropCard shell = static_cast<const model::ShellPropTable&>(table).card(property->row);
            thickness = shell.thickness;
            places.z1 = shell.fiberDistance1;
            places.z2 = shell.fiberDistance2;
        }
        else if (property->table == model::typeIndexOf<model::CompPropTable>())
        {
            thickness = static_cast<const model::CompPropTable&>(table).card(property->row).totalThickness();
            laminate = true;
        }
        else if (property->table == model::typeIndexOf<model::CompPropGlobalTable>())
        {
            thickness = static_cast<const model::CompPropGlobalTable&>(table).card(property->row).totalThickness();
            laminate = true;
        }
        else
            break;
        places.cornerCount = corners->count;
        places.ok = true;
        for (std::size_t corner = 0; corner < corners->count; ++corner)
        {
            // a blank corner thickness, and every corner of a laminate, has the thickness of the property; TFLAG 1
            // gives the corner thicknesses as fractions of it
            const double given = corners->thickness[corner];
            const double here =
                laminate || given < 0.0 ? thickness : (corners->thicknessFlag == 1 ? given * thickness : given);
            places.cornerNodes[corner] = corners->nodes[corner];
            places.cornerThickness[corner] = here;
            places.ok = places.ok && here > 0.0;
        }
    } while (false);
    return m_places.emplace(resultEid, places).first->second;
}

ShellFibres ElementModelFacts::shellFibres(std::int32_t resultEid, std::int32_t nodeId)
{
    const ShellPlaces& places = shellPlaces(resultEid);
    ShellFibres fibres;
    if (!places.ok || places.cornerCount == 0)
        return fibres;
    // the thickness at the place: of the corner, or at the centre the mean of the corners
    double thickness = 0.0;
    if (nodeId == 0)
    {
        for (std::size_t corner = 0; corner < places.cornerCount; ++corner)
            thickness += places.cornerThickness[corner] / static_cast<double>(places.cornerCount);
    }
    else
    {
        std::size_t corner = 0;
        while (corner < places.cornerCount && places.cornerNodes[corner] != nodeId)
            ++corner;
        if (corner == places.cornerCount)
            return fibres;
        thickness = places.cornerThickness[corner];
    }
    fibres.ok = true;
    fibres.z1 = places.z1.value_or(-0.5 * thickness);
    fibres.z2 = places.z2.value_or(0.5 * thickness);
    return fibres;
}

const RodFacts& ElementModelFacts::rod(std::int32_t resultEid)
{
    const auto found = m_rods.find(resultEid);
    if (found != m_rods.end())
        return found->second;
    RodFacts facts;
    const auto card = m_context.elementCard(m_set, resultEid);
    do
    {
        if (m_model == nullptr)
        {
            facts.why = "no model is attached to the results";
            break;
        }
        if (!card.linked || card.pid == 0)
        {
            facts.why = "the element is not linked to a card of the model that has a property";
            break;
        }
        const auto property = m_model->locate(base::IdSpace::Property, card.pid);
        if (!property || property->table != model::typeIndexOf<model::RodPropTable>())
        {
            facts.why = "the property " + std::to_string(card.pid) + " is not a RodProp";
            break;
        }
        const model::RodPropCard rod =
            static_cast<const model::RodPropTable&>(*m_model->findTable(property->table)).card(property->row);
        std::string why;
        const auto material = isotropicMaterial(*m_model, rod.matId, why);
        if (!material)
        {
            facts.why = why;
            break;
        }
        if (!(rod.area > 0.0))
        {
            facts.why = "the RodProp " + std::to_string(card.pid) + " has no area";
            break;
        }
        facts.ok = true;
        facts.area = rod.area;
        facts.torsion = rod.torsion;
        facts.coefficient = rod.stressCoefficient;
        facts.e = material->youngsModulus;
        facts.g = material->shearModulus > 0.0 ? material->shearModulus
                                               : material->youngsModulus / (2.0 * (1.0 + material->poissonRatio));
        facts.pid = card.pid;
    } while (false);
    return m_rods.emplace(resultEid, std::move(facts)).first->second;
}

const SolidFacts& ElementModelFacts::solid(std::int32_t resultEid)
{
    const auto found = m_solids.find(resultEid);
    if (found != m_solids.end())
        return found->second;
    SolidFacts facts;
    const auto card = m_context.elementCard(m_set, resultEid);
    do
    {
        if (m_model == nullptr)
        {
            facts.why = "no model is attached to the results";
            break;
        }
        if (!card.linked || card.pid == 0)
        {
            facts.why = "the element is not linked to a card of the model that has a property";
            break;
        }
        const auto property = m_model->locate(base::IdSpace::Property, card.pid);
        if (!property || property->table != model::typeIndexOf<model::SolidPropTable>())
        {
            facts.why = "the property " + std::to_string(card.pid) + " is not a SolidProp";
            break;
        }
        const model::SolidPropCard solid =
            static_cast<const model::SolidPropTable&>(*m_model->findTable(property->table)).card(property->row);
        std::string why;
        const auto material = isotropicMaterial(*m_model, solid.matId, why);
        if (!material)
        {
            facts.why = why;
            break;
        }
        facts.ok = true;
        facts.e = material->youngsModulus;
        facts.nu = material->poissonRatio;
        facts.g = material->shearModulus > 0.0 ? material->shearModulus
                                               : material->youngsModulus / (2.0 * (1.0 + material->poissonRatio));
        facts.pid = card.pid;
    } while (false);
    return m_solids.emplace(resultEid, std::move(facts)).first->second;
}

} // namespace oor::query
