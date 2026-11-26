#pragma once

#include <cstddef>
#include <string>

namespace oor::results
{
// How an Excel workbook of results is written.
struct XlsxWriteOptions
{
    // The texts at the top of the index sheet.
    std::string title;
    std::string subtitle;
    std::string label;
    // The deflate level of the ZIP container, 0 (stored) to 9.
    int compressionLevel = 6;
    // The rows of a sheet, header included, before the table or the named result goes on in another sheet: Excel's
    // limit by default. A smaller number (at least 20) splits sooner; a larger one is refused.
    std::size_t maxRowsPerSheet = 1'048'576;
};
} // namespace oor::results
