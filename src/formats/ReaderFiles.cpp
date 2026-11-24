#include "oor/api/Results.hpp"
#include "oor/base/errors/Errors.hpp"
#ifdef OOR_WITH_OOH5
#include "oor/formats/ooh5.hpp"
#endif
#ifdef OOR_WITH_OOS
#include "oor/formats/oos.hpp"
#endif
#ifdef OOR_WITH_XLSX
#include "oor/results/xlsx/XlsxWriter.hpp"
#endif

namespace oor::api
{
namespace
{
[[maybe_unused, noreturn]] void unavailable(const char* format)
{
    throw base::UsageError(std::string("this Reader build does not include the ") + format + " file adapter");
}
} // namespace

std::shared_ptr<Deck> Deck::readModel(const std::string& path, const DeckReadSettings& settings)
{
#ifdef OOR_WITH_OOH5
    if (formats::ooh5::recognizes(path))
        return formats::ooh5::read(path, settings);
#endif
#ifdef OOR_WITH_OOS
    return formats::oos::read(path, settings);
#elif defined(OOR_WITH_OOH5)
    throw base::UsageError("input is not an O_o archive and this Reader build has no oos adapter");
#else
    (void)path;
    (void)settings;
    throw base::UsageError("this Reader build contains no model file adapters");
#endif
}

std::vector<std::string> Deck::writeModel(const std::string& path, const DeckWriteSettings& settings) const
{
#ifdef OOR_WITH_OOS
    return formats::oos::write(*this, path, settings);
#else
    (void)path;
    (void)settings;
    unavailable("oos");
#endif
}

std::string Deck::toModelText(const DeckWriteSettings& settings) const
{
#ifdef OOR_WITH_OOS
    return formats::oos::text(*this, settings);
#else
    (void)settings;
    unavailable("oos");
#endif
}

results::ResultWriteReport Deck::writeArchive(const std::string& path,
                                              const results::ArchiveWriteOptions& options) const
{
#ifdef OOR_WITH_OOH5
    return formats::ooh5::write(*this, path, options);
#else
    (void)path;
    (void)options;
    unavailable("ooh5");
#endif
}

#ifndef OOR_WITH_OOH5
std::shared_ptr<Results> Results::open(const std::string&)
{
    unavailable("ooh5");
}

results::ResultWriteReport Results::writeArchive(const std::string&, const results::ArchiveWriteOptions&) const
{
    unavailable("ooh5");
}
#endif

results::ResultWriteReport Results::writeXlsx(const std::string& path, const results::XlsxWriteOptions& options) const
{
#ifdef OOR_WITH_XLSX
    return results::writeXlsx(path, *m_tables, options);
#else
    (void)path;
    (void)options;
    unavailable("xlsx");
#endif
}
} // namespace oor::api
