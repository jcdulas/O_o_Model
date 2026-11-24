#include "oor/api/CardEdits.hpp"
#ifdef OOR_CHECK_oos
#include "oor/formats/oos.hpp"
namespace adapter = oor::formats::oos;
#else
#include "oor/formats/ooh5.hpp"
namespace adapter = oor::formats::ooh5;
#endif

#include <cstdio>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;
    using namespace oor;
    const auto original = api::Deck::createModel();
    api::CardInput node;
    node.type = "Node";
    node.fields = {{model::FieldValue::Kind::Integer, 17, 0, {}}, {},
                   {model::FieldValue::Kind::Real, 0, 1.25, {}}};
    (void)api::insertCard(*original, node);
    original->setDocument("metadata", "stored in archive");
#ifdef OOR_CHECK_oos
    if (adapter::write(*original, argv[1]).size() != 1) return 2;
#else
    if (!adapter::write(*original, argv[1]).finished) return 2;
#endif
    const auto copy = adapter::read(argv[1], {.strict = true});
    std::remove(argv[1]);
    if (copy->cardCounts() != original->cardCounts() || !copy->checkReferences().empty()) return 3;
#ifdef OOR_CHECK_ooh5
    if (copy->document("metadata") != original->document("metadata")) return 4;
#endif
    const auto card = api::findCard(*copy, "Node", 17);
    return card && card->fields.at(2) == "1.25" ? 0 : 5;
}
