#pragma once

#include "oor/results/core/ResultTables.hpp"
#include "oor/results/writers/ResultWriteReport.hpp"
#include "oor/results/writers/XlsxWriteOptions.hpp"

#include <cstddef>
#include <filesystem>
#include <string>

namespace oor::results
{

// Writes result tables as an Excel workbook (.xlsx, Office Open XML), an output for people (the workbook is not read
// back: the HDF5 archive is the format to exchange results).
//
// - The sheet "Index" lists every table, with a link to its sheet.
// - Each table has a sheet: a few lines that say what it is, then one line per step and row, with the labels of the row
//   (step, ID, grid point, layer, ...) and one column per component (two for a complex value: real and imaginary
//   parts). The header line is frozen and has filters. A table longer than a sheet goes on in the next ones.
// - Each named result (a matrix, a grid point weight, ...) has a sheet with its arrays, and goes on in the next ones
//   when it is longer than a sheet. An array of two dimensions is a grid; one wider than a sheet is written one value
//   a line.
// - A sheet name is cut to the length the format allows between two characters, and bytes that are not UTF-8 in a
//   text (a title read from a file in another encoding) are written as U+FFFD: the workbook is always well-formed.
// Empty tables and tables with more columns than a sheet holds are reported in `skipped`, never dropped silently.
[[nodiscard]] std::string formatXlsx(const ResultTables& tables, const XlsxWriteOptions& options = {},
                                     ResultWriteReport* report = nullptr);

// The same, written to a file (through a temporary file next to it, so a failure never leaves half a file).
ResultWriteReport writeXlsx(const std::filesystem::path& path, const ResultTables& tables,
                            const XlsxWriteOptions& options = {});

} // namespace oor::results
