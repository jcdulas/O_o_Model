#include "oor/api/CardEdits.hpp"
#include "oor/api/CardTables.hpp"
#include "oor/api/ControlEdits.hpp"

int main()
{
    using namespace oor;
    const auto deck = api::Deck::createModel();
    api::setSolution(*deck, "LinearStatics");
    api::CardInput node;
    node.type = "Node";
    node.fields.push_back({model::FieldValue::Kind::Integer, 17, 0, {}});
    const auto added = api::insertCard(*deck, node);
    deck->applyDefaults();
    const auto table = api::cardTable(*deck, "Node", {"id"});
    return added.id == 17 && deck->checkReferences().empty() && table->rowCount() == 1 ? 0 : 1;
}
