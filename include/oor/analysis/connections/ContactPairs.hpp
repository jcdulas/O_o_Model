#pragma once

#include "oor/analysis/connections/ContactBodies.hpp"
#include "oor/base/ids/EntityId.hpp"
#include "oor/model/core/Model.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace oor::analysis
{

// The kind of contact of a pair (every kind counts).
enum class ContactKind : std::uint8_t
{
    Glued,     // IGLUE not 0 and JGLUE 0: the grid points do not separate
    Breakable, // IGLUE not 0 and JGLUE 1 (separation on the residual force) or 2 (breaking glue)
    Touching   // IGLUE 0 (or blank): general contact
};

[[nodiscard]] std::string_view contactKindName(ContactKind kind) noexcept;

// One parameter of a pair as the solver resolves it, with the card that sets it: "ContactTable 5" or
// "ContactPairGeomParams 1" (the pair's own fields or parameter card), "ContactParams" (the defaults of the model),
// "default" (the format reference default).
struct ResolvedContactParameter
{
    std::optional<double> value; // nothing: not given (ERROR: the automatic value; DQNEAR: no near contact)
    std::string source = "default";
};

// The parameters of a pair that decide the glue and the search (format reference ContactTable, ContactPairGeomParams,
// ContactPairPhysicalParams, ContactParams).
struct ContactPairParameters
{
    ResolvedContactParameter glueOption;      // default 0: no glue
    ResolvedContactParameter glueSeparation;  // default 0
    ResolvedContactParameter coordinateCheck; // default 0
    ResolvedContactParameter searchOption;    // default 0: the double-order search
    ResolvedContactParameter errorTolerance;  // the pair's, else ContactParams's, else nothing (automatic)
    // the pair's; else 0.0 for a glued pair, ContactParams's or 0.9 for another
    ResolvedContactParameter toleranceBias;
    // the pair's (ContactTable, ContactPairGeomParams or ContactPairPhysicalParams), else nothing
    ResolvedContactParameter nearDistance;
    // COPTS and COPTM: how the secondary and the primary surfaces may contact: the
    // packed code A + 10 B + 1000 C, whose digit B says which skins of a shell take part and
    // whether the thickness counts. 0 when the pair gives none (the default, 1011 for a ContactPairGeomParams).
    std::int32_t secondaryContactOption = 0;
    std::int32_t primaryContactOption = 0;
};

// One pair of contact bodies: the secondary body, whose grid points touch, and the primary body, whose surface is
// touched (format reference ContactTable and ContactPair: SECNDRY or SLAVE is the touching body, PRIMARY or MASTER the
// touched one).
struct ContactPair
{
    // The card that pairs the bodies (a ContactTable, a ContactPair, a ContactSet or a ContactSlideline) and its ID; no
    // card for the pairs of a Bulk Data that has bodies and no table.
    std::optional<model::CardLocation> table;
    std::string tableName; // the card type: "ContactTable", ...; empty with no card
    base::EntityId tableId = 0;
    const ContactBody* secondary = nullptr;
    const ContactBody* primary = nullptr;
    ContactKind kind = ContactKind::Touching;
    // The distance the pair gives (the ERROR or DQNEAR of the pair, the MAXD of a ContactSet pair); 0 when it gives
    // none.
    double tolerance = 0.0;
    // format reference ContactTable and ContactPairGeomParams, ISEARCH: 0 (the default) searches from the secondary to
    // the primary body and then the other way; 1 only from the secondary body.
    bool searchesBothWays = true;
    ContactPairParameters parameters;
    // The contact cards that make the pair: the table, its parameter cards (ContactPairGeomParams,
    // ContactPairPhysicalParams), the two bodies and what they are made of. Editing one of them changes the revision
    // stamp of the component the pair merges.
    std::vector<model::CardLocation> cards;

    // "ContactTable 5"; empty with no card.
    [[nodiscard]] std::string tableLabel() const;
};

// The contact pairs of a model: those of every contact table of the Bulk Data, whatever the Case Control selects (the
// owner's rule of 2026-10-06: the components are the same for every load case and a Bulk Data is processed without its
// Case Control). The tables are:
//   ContactTable  its short form (IDSCND, IDPRIM) and every SECNDRY with each of its PRIMARY bodies;
//   ContactPair  the same, with the parameters of its ContactPairGeomParams (geometric) and ContactPairPhysicalParams
//                (physical) cards; a ContactTable1 is a list of ContactPair, which are all read anyway;
//   ContactSet  each SIDi / TIDi pair of regions (a ContactElemSurface, else a SlidelineSegments); a ContactSetUnion is
//               a union of ContactSet, all read anyway; ContactSlideline its secondary and primary SlidelineSegments
//               lines (slideline contact).
// A Bulk Data with deformable bodies and no table pairs every two of them, as the solver does when no table is given:
// the lower BID is the secondary body. A pair with a rigid body, a body that does
// not exist or a body with nothing to search (no shell, no solid, no grid point) is left out, and so is a pair of a
// body with itself.
class ContactPairs
{
public:
    [[nodiscard]] static ContactPairs read(const model::Model& model, const ContactBodies& bodies);

    // By table name, table ID, secondary body and primary body (the pairs without table first).
    [[nodiscard]] const std::vector<ContactPair>& pairs() const noexcept { return m_pairs; }
    // True when the pairs come from tables; false when they pair every two bodies.
    [[nodiscard]] bool fromTables() const noexcept { return m_fromTables; }
    // The ContactParams parameters the the solver rule reads: ERRBAS (1: the automatic ERROR of each pair from its own
    // bodies; 0, the default: one value for every pair) and THKOFF (1: the thickness left out of the search order of
    // ISEARCH 2).
    [[nodiscard]] bool errorPerPair() const noexcept { return m_errorPerPair; }
    [[nodiscard]] bool thicknessOffInOrder() const noexcept { return m_thicknessOffInOrder; }

private:
    std::vector<ContactPair> m_pairs;
    bool m_fromTables = false;
    bool m_errorPerPair = false;
    bool m_thicknessOffInOrder = false;
};

} // namespace oor::analysis
