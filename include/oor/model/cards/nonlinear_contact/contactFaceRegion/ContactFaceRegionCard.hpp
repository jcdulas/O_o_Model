#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace oor::model
{

// One entry of the FACE form of a ContactFaceRegion: an element (or a TypedListSet3 of elements) and the face of it
// that is in contact.
struct ContactFaceRegionFace
{
    base::EntityId id = 0; // ESIDi: an element ID, or a TypedListSet3 ID with idtype SET
    std::string face; // FACEIDi: S1..S6, E1..E4, TOP, BTM, BOTH, ENDA or ENDB; blank for both sides of a shell or the
                      // whole beam
    std::string idType = "Elements"; // IDTYPEi: ELEM or SET

    [[nodiscard]] bool operator==(const ContactFaceRegionFace&) const = default;
};

// One entry of the GRID form: an element and the three corner grid points of the face of it that is in contact.
struct ContactFaceRegionGridFace
{
    base::EntityId elemId = 0; // EIDi
    std::array<base::EntityId, 3>
        grids{}; // Gi1 to Gi3: the corners of the face; all 0 for both sides of a shell or the whole beam

    [[nodiscard]] bool operator==(const ContactFaceRegionGridFace&) const = default;
};

// One ContactFaceRegion card: a contact region made of element faces (SOLs 101, 103 to 112, 200 and 400), named by
// ContactPair. Its FORM selects one of three layouts:
//
//   FACE (the default):  ContactFaceRegion  BID  BPID  DIM  (blank)  FORM  INCTHK  EDGCNT
//                        (continuation, two entries to a line)  ESID1  FACEID1  IDTYPE1  (blank)  ESID2  FACEID2
//                        IDTYPE2
//   GRID:                ContactFaceRegion  BID  BPID  DIM  (blank)  "GRID"  INCTHK  EDGCNT
//                        (continuation, two entries to a line)  EID1  G11  G12  G13  EID2  G21  G22  G23
//   RIGID:               ContactFaceRegion  BID  BPID  DIM  (blank)  "RIGID"
//                        (continuation)  BSID  BCRGID
struct ContactFaceRegionCard
{
    // BID: unique among ContactFaceRegion, ContactBody1 and ContactNodeRegion
    base::EntityId id = 0;
    base::EntityId bodyParamsId = 0;                  // the ContactBodyParams of the body parameters; 0 when blank
    std::string dimension = "ThreeDimensional";       // 2D or 3D
    std::string form = "Face";                        // FACE, GRID or RIGID
    std::string includeThickness = "Yes";             // YES or NO: include the thickness offset of the shells
    std::int32_t edgeContact = 1;                     // 1 beam and bar edges, 10 free and hard shell edges, 11 both
    std::vector<ContactFaceRegionFace> faces;         // FACE form
    std::vector<ContactFaceRegionGridFace> gridFaces; // GRID form
    // RIGID form: a ContactRigidSurfaceList, ContactPatchSurface, ContactBezierSurface, ContactNurbsCurve or
    // ContactNurbsSurface
    base::EntityId surfaceId = 0;
    base::EntityId rigidMotionId = 0;                 // RIGID form: the ContactRigidMotion of the motion; 0 when blank
};

} // namespace oor::model
