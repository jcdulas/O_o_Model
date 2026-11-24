#pragma once


#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace oor::deck
{

// Source metadata is kept once per inclusion.
struct SourceFile
{
    std::filesystem::path path;
    std::string includeTextAsWritten;
    std::int32_t parent = -1;
    std::uint32_t includeLine = 0;
};

struct ReadOptions
{
    std::filesystem::path workingDirectory;
    std::size_t maxIncludeDepth = 32;
};

inline constexpr std::string_view INCLUDE_RECORD = "Include";

enum class ModelItemKind : std::uint8_t
{
    Section,      // a section line: [executive], [case], [model], [model;SuperelementPart;5]
    Record,       // a record: a card, a command, a statement
    IncludeBegin, // an Include record: the items of the included file follow
    IncludeEnd,   // the end of the included file
    Comments      // comment lines that no record follows in their file (before a section line, at the end of a file)
};

// One item of a model file, in file order.
struct ModelItem
{
    ModelItemKind kind = ModelItemKind::Record;
    // Record: the values, the name first. Section: the values between the brackets ("model", "SuperelementPart",
    // "5"). IncludeBegin: the path as written.
    std::vector<std::string> values;
    // The comment lines before the item (Comments: the lines themselves), joined with '\n', without the '#'.
    std::string comments;
    std::uint32_t fileIndex = 0;         // index in ModelText::files
    std::uint32_t line = 0;              // 1-based
    std::uint32_t includedFileIndex = 0; // IncludeBegin: the file that is opened
};

// A model file and the files it includes, cut into items.
struct ModelText
{
    std::vector<SourceFile> files; // the main file first; an included file once per inclusion (no mapping kept)
    std::vector<ModelItem> items;
};

} // namespace oor::deck
