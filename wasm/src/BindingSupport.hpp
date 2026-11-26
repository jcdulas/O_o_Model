#pragma once
#include "oor/api/CardEdits.hpp"
#include "oor/base/errors/Errors.hpp"

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <cmath>
#include <cstdint>
#include <exception>
#include <limits>
#include <string>
#include <vector>

namespace oor::wasm
{
using emscripten::val;
// Runs `work`; a C++ exception is thrown again as a JavaScript Error.
template <typename Work>
auto guarded(Work work) -> decltype(work())
{
    try
    {
        return work();
    }
    catch (const std::exception& error)
    {
        val::global("Error").new_(std::string(error.what())).throw_();
    }
    catch (...)
    {
        val::global("Error").new_(std::string("unknown C++ error")).throw_();
    }
    __builtin_unreachable();
}

// A whole number given by JavaScript, checked before it is narrowed: a number of JavaScript is a double, and the
// conversion of the interface to an integer drops a fraction without a word (the card 1.9 would be the card 1, the
// table -1 the table 0). Throws UsageError saying what `what` must be; call it inside guarded().
inline double wholeNumber(double value, double lowest, double highest, const char* what)
{
    if (!std::isfinite(value) || std::floor(value) != value || value < lowest || value > highest)
        throw base::UsageError(std::string(what) + " must be a whole number from " +
                               std::to_string(static_cast<std::int64_t>(lowest)) + " to " +
                               std::to_string(static_cast<std::int64_t>(highest)));
    return value;
}

// The largest whole number a number of JavaScript holds exactly (2^53 - 1).
inline constexpr double MAX_SAFE_INTEGER = 9007199254740991.0;

// The ID of a card (any 32-bit integer: an ID no card has is simply not found).
inline base::EntityId entityIdOf(double value)
{
    return static_cast<base::EntityId>(wholeNumber(value, std::numeric_limits<base::EntityId>::min(),
                                                   std::numeric_limits<base::EntityId>::max(), "a card ID"));
}

// The key of a card, of a Case Control section or of one of its entries.
inline std::uint32_t keyOf(double value)
{
    return static_cast<std::uint32_t>(
        wholeNumber(value, 0.0, std::numeric_limits<std::uint32_t>::max(), "a card or case key"));
}

// The number of a field of a card, from 1.
inline int fieldNumberOf(double value)
{
    return static_cast<int>(wholeNumber(value, 1.0, std::numeric_limits<int>::max(), "a field number"));
}

// The position of a table or of a named result in its list, from 0.
inline std::size_t listIndexOf(double value, const char* what)
{
    return static_cast<std::size_t>(wholeNumber(value, 0.0, MAX_SAFE_INTEGER, what));
}

// A member of a JavaScript options object, or `fallback` when the object or the member is missing.
template <typename T>
T option(const val& options, const char* name, T fallback)
{
    if (options.isUndefined() || options.isNull())
        return fallback;
    const val member = options[name];
    if (member.isUndefined() || member.isNull())
        return fallback;
    return member.as<T>();
}

// Copies of C++ vectors as JavaScript typed arrays and arrays.
template <typename T>
val typedArray(const char* type, const T* data, std::size_t count)
{
    return val::global(type).new_(emscripten::typed_memory_view(count, data));
}
inline val int32Array(const std::vector<std::int32_t>& values)
{
    return typedArray("Int32Array", values.data(), values.size());
}
inline val float64Array(const std::vector<double>& values)
{
    return typedArray("Float64Array", values.data(), values.size());
}
inline val textArray(const std::vector<std::string>& texts)
{
    val array = val::array();
    for (const std::string& text : texts)
        array.call<void>("push", text);
    return array;
}

template <typename T>
std::vector<T> vectorOf(const val& array)
{
    if (array.isUndefined() || array.isNull())
        return {};
    return emscripten::vecFromJSArray<T>(array);
}

inline val diagnosticsArray(const std::vector<api::DiagnosticText>& diagnostics)
{
    val array = val::array();
    for (const api::DiagnosticText& diagnostic : diagnostics)
    {
        val item = val::object();
        item.set("severity", diagnostic.severity);
        item.set("code", diagnostic.code);
        item.set("message", diagnostic.message);
        item.set("location", diagnostic.location);
        array.call<void>("push", item);
    }
    return array;
}

inline val fieldValue(const api::FieldValue& value)
{
    switch (value.kind)
    {
    case api::FieldValue::Kind::Number:
        return val(value.number);
    case api::FieldValue::Kind::Numbers:
        return float64Array(value.numbers);
    case api::FieldValue::Kind::Text:
        return val(value.text);
    case api::FieldValue::Kind::Texts:
        return textArray(value.texts);
    case api::FieldValue::Kind::Missing:
        break;
    }
    return val::null();
}

inline val cardObject(const api::CardView& card)
{
    val object = val::object();
    object.set("type", card.type);
    object.set("id", card.id);
    object.set("key", card.key);
    val values = val::object();
    for (const auto& [name, value] : card.values)
        values.set(name, fieldValue(value));
    object.set("values", values);
    object.set("fields", textArray(card.fields));
    object.set("text", card.text);
    object.set("comment", card.comment);
    return object;
}
} // namespace oor::wasm
