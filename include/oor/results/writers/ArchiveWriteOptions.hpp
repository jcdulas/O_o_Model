#pragma once

#include <memory>
#include <string>

namespace oor::model
{
class Model;
}

namespace oor::results
{
// How an archive is written.
struct ArchiveWriteOptions
{
    // The deflate level of the values and labels, 0 (no compression, contiguous datasets) to 9. 4 is a good balance:
    // most of the gain of 9 at a fraction of its time.
    int compressionLevel = 4;
    // The shuffle filter before deflate: it groups the bytes of the numbers by rank, which compresses floating-point
    // values much better.
    bool shuffle = true;
    // Raise (UsageError) instead of reporting when a table cannot be written.
    bool strict = false;
    // Written in the root attributes; the producer is "oor_reader <version>" when empty.
    std::string producer;
    std::string title;
    std::string subtitle;
    std::string label;
    // Optional model, serialized as native typed columns. An unrepresentable control entry raises UsageError.
    std::shared_ptr<const model::Model> model;
};
} // namespace oor::results
