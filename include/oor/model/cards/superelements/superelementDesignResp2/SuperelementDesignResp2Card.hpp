#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/superelements/SuperelementGroups.hpp"

#include <array>
#include <string>
#include <vector>

namespace oor::model
{

// The groups of a SuperelementDesignResp2 and a SuperelementDesignResp3 are those of a DesignResp2 and a DesignResp3
// (the SuperelementDesignResp3 adds USRDATA), each item led by the part superelement that holds what it names, in the
// order of the format reference. DesignConstants names constants of a DesignConstants or DesignFieldConstants and names
// no card. The DesignResp2 flag is not supported.
inline constexpr std::array<SuperelementGroupKeyword, 10> SUPERELEMENT_DESIGN_RESP2_GROUPS{{
    {"DesignVar", SuperelementGroupContent::Pairs, ReferenceTarget::DesignVariable, "designVarIds"},
    {"DesignConstants", SuperelementGroupContent::Labels, ReferenceTarget::Other, "constantLabels"},
    {"DesignResp1", SuperelementGroupContent::Pairs, ReferenceTarget::DesignResponse, "responseIds"},
    {"DesignNodes", SuperelementGroupContent::Nodes, ReferenceTarget::Node, "nodeIds"},
    {"DesignPropRelation1", SuperelementGroupContent::Pairs, ReferenceTarget::PropertyRelation, "propRelationIds"},
    {"DesignElemRelation1", SuperelementGroupContent::Pairs, ReferenceTarget::ConnectivityRelation, "elemRelationIds"},
    {"DesignMatRelation1", SuperelementGroupContent::Pairs, ReferenceTarget::MaterialRelation, "matRelationIds"},
    {"DesignPropRelation2", SuperelementGroupContent::Pairs, ReferenceTarget::PropertyRelation, "propRelation2Ids"},
    {"DesignElemRelation2", SuperelementGroupContent::Pairs, ReferenceTarget::ConnectivityRelation, "elemRelation2Ids"},
    {"DesignMatRelation2", SuperelementGroupContent::Pairs, ReferenceTarget::MaterialRelation, "matRelation2Ids"},
}};

// One SuperelementDesignResp2 card: a response computed from design variables, constants and responses of several part
// superelements, by a DesignEquation equation or by a function, as a DesignResp2 does for one model.
//
// Card layout: SuperelementDesignResp2  ID  LABEL  EQID/FUNC  REGION  METHOD  C1  C2  C3  fields 1 to 8
//                                      DesignVar  DVSEID1  DVID1  DVSEID2  DVID2  DVSEID3  DVID3  the lines after, from
//                                                 field 9:
//                                      DesignConstants  LBSEID1  LABL1  ...  DesignResp1  R1SEID1  NR1 ...  a keyword
//                                                       and three (SEID, ID)
//                                      pairs DNODE  NDSEID1  G1  CMP1  NDSEID2  G2  CMP2  (two triples)  to a line,
//                                                   DNODE two triples
//                                      DesignPropRelation1 ... DesignElemRelation1 ... DesignMatRelation1 ...
//                                      DesignPropRelation2 ... DesignElemRelation2 ... DesignMatRelation2 ...
// Apart from the part superelement that leads each item, the card follows the rules of the DesignResp2, so the
// fields of the first line are those of DesignResp2Card: EQID is the number of a DesignEquation of the main Bulk Data,
// or FUNC the name of a function, and METHOD and C1 to C3 belong to BETA and MATCH. The defaults of the constants are
// those of this format for C1 (100.0) and C2 (0.005), and the 10.0 of the DesignResp2 for C3. An item may name
// superelement 0, the residual structure. The DNODE of a common deck reads `10 14 0 1`, which is not a whole number of
// triples: the card reads triples (the superelement, the grid point and the translation 1 to 3). The card belongs in
// the main Bulk Data and is ignored after a BEGIN SUPER=n with n above 0. Its ID is a response number, one of the
// numbers of DesignResp1, DesignResp2 and DesignResp3 (category DesignResponse, one ID space per card type).
struct SuperelementDesignResp2Card
{
    static constexpr double DEFAULT_CONSTANT1 = 100.0;
    static constexpr double DEFAULT_CONSTANT2 = 0.005;
    static constexpr double DEFAULT_CONSTANT3 = 10.0;

    base::EntityId id = 0;
    std::string entryLabel;
    base::EntityId equationId = 0; // the DesignEquation, or 0 when a function is named
    std::string function;          // upper case; empty when an equation is named
    base::EntityId regionId = 0;   // 0: blank
    std::string methodName;        // upper case, empty when blank
    double constant1 = DEFAULT_CONSTANT1;
    double constant2 = DEFAULT_CONSTANT2;
    double constant3 = DEFAULT_CONSTANT3;
    std::vector<SuperelementGroup> groups; // in the order written

    [[nodiscard]] bool operator==(const SuperelementDesignResp2Card&) const noexcept = default;
};

} // namespace oor::model
