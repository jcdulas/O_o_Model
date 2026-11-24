#include "oor/api/Deck.hpp"

#include "oor/base/errors/Errors.hpp"
#include "oor/model/core/CardRegistry.hpp"
#include "oor/model/references/ReferenceChecker.hpp"

#include <map>

namespace oor::api
{

std::vector<std::string> Deck::documentNames() const
{
    std::vector<std::string> names;
    for (const auto& [name, text] : m_model->documents())
    {
        (void)text;
        names.push_back(name);
    }
    return names;
}

std::optional<std::string> Deck::document(const std::string& name) const
{
    const auto found = m_model->documents().find(name);
    return found == m_model->documents().end() ? std::nullopt : std::optional(found->second);
}

void Deck::setDocument(std::string name, std::string text) const
{
    m_model->setDocument(std::move(name), std::move(text));
}

bool Deck::removeDocument(const std::string& name) const
{
    return m_model->removeDocument(name);
}

std::shared_ptr<Deck> Deck::createModel()
{
    return std::shared_ptr<Deck>(new Deck(std::make_shared<model::Model>()));
}

std::shared_ptr<Deck> Deck::fromModel(std::shared_ptr<model::Model> model)
{
    if (!model)
        throw base::UsageError("a deck needs a model");
    return std::shared_ptr<Deck>(new Deck(std::move(model)));
}

std::shared_ptr<Deck> Deck::copy() const
{
    auto owner = std::make_shared<model::Model>(m_model->root().copy());
    if (!m_model->isPart())
        return std::shared_ptr<Deck>(new Deck(std::move(owner)));
    const auto& info = *m_model->partInfo();
    auto* part = owner->findPart(info.kind, info.id, info.massId);
    return std::shared_ptr<Deck>(new Deck(std::shared_ptr<model::Model>(owner, part)));
}

std::shared_ptr<Deck> Deck::addPart(const model::PartInfo& info) const
{
    if (m_model->isPart())
        throw base::UsageError("parts belong to the root model");
    const bool unnumbered = info.kind == "ActivePart" || info.kind == "PassivePart";
    if (info.kind.empty() || info.kind.find_first_of(";\r\n[]") != std::string::npos ||
        (unnumbered ? info.id != 0 : info.id <= 0) || info.massId < 0)
        throw base::UsageError("a part needs a kind, a positive ID and a nonnegative mass ID");
    if (m_model->findPart(info.kind, info.id, info.massId))
        throw base::UsageError("the part already exists");
    model::Model& added = m_model->addPart(info);
    return std::shared_ptr<Deck>(new Deck(std::shared_ptr<model::Model>(m_model, &added)));
}

std::shared_ptr<Deck> Deck::part(const std::string& kind, std::int64_t id, std::int64_t massId) const
{
    model::Model* found = m_model->findPart(kind, id, massId);
    return found ? std::shared_ptr<Deck>(new Deck(std::shared_ptr<model::Model>(m_model, found))) : nullptr;
}

std::vector<model::PartInfo> Deck::parts() const
{
    std::vector<model::PartInfo> result;
    for (const auto& item : m_model->root().parts())
        result.push_back(*item->partInfo());
    return result;
}

void Deck::applyDefaults() const
{
    m_model->applyDefaults();
}

std::vector<DiagnosticText> Deck::checkReferences() const
{
    base::DiagnosticSink sink;
    // Reference visitors may write unchanged IDs; scan a copy to isolate their column writes.
    model::Model copy = m_model->root().copy();
    if (m_model->isPart())
    {
        const auto& info = *m_model->partInfo();
        model::ReferenceChecker::check(*copy.findPart(info.kind, info.id, info.massId), sink);
    }
    else
    {
        model::ReferenceChecker::check(copy, sink);
        for (const auto& part : copy.parts())
            model::ReferenceChecker::check(*part, sink);
    }
    std::vector<DiagnosticText> result;
    for (const auto& item : sink.diagnostics())
        result.push_back(diagnosticText(item));
    return result;
}

DiagnosticText diagnosticText(const base::Diagnostic& diagnostic)
{
    DiagnosticText text;
    switch (diagnostic.severity)
    {
    case base::Severity::Info:
        text.severity = "info";
        break;
    case base::Severity::Warning:
        text.severity = "warning";
        break;
    case base::Severity::Error:
        text.severity = "error";
        break;
    }
    text.code = diagnostic.code;
    text.message = diagnostic.message;
    text.location = diagnostic.location.toString();
    return text;
}

std::vector<std::pair<std::string, std::size_t>> Deck::cardCounts() const
{
    std::map<std::string, std::size_t> counts;
    const model::CardRegistry& registry = model::CardRegistry::instance();
    for (std::uint16_t type = 0; type < registry.size(); ++type)
    {
        const model::CardTable* table = m_model->findTable(type);
        if (table == nullptr || table->rows().aliveCount() == 0)
            continue;
        const std::string name = type == model::CardRegistry::UNKNOWN_TYPE
                                     ? std::string("(unknown cards)")
                                     : std::string(registry.entry(type).info.name);
        counts[name] += table->rows().aliveCount();
    }
    return {counts.begin(), counts.end()};
}

std::size_t Deck::cardCount() const
{
    return m_model->cardCount();
}

std::vector<DiagnosticText> Deck::diagnostics() const
{
    std::vector<DiagnosticText> texts;
    for (const base::Diagnostic& diagnostic : m_model->diagnostics().diagnostics())
        texts.push_back(diagnosticText(diagnostic));
    return texts;
}

} // namespace oor::api
