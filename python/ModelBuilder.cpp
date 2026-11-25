#include "ModelBuilder.hpp"

#include "oor/api/CardEdits.hpp"
#include "oor/api/ControlEdits.hpp"
#include "oor/model/format/CardLayouts.hpp"

#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <cmath>
#include <limits>
#include <set>

namespace py = pybind11;
using namespace oor;

namespace
{
using Value = model::FieldValue;

Value real(double value)
{
    if (!std::isfinite(value))
        throw py::value_error("numeric fields must be finite");
    return {Value::Kind::Real, 0, value, {}};
}

Value scalar(py::handle value)
{
    if (value.is_none())
        return {};
    if (py::isinstance<py::str>(value))
        return {Value::Kind::Text, 0, 0, py::cast<std::string>(value)};
    if (PyIndex_Check(value.ptr()) && !py::isinstance<py::array>(value))
        return {Value::Kind::Integer, py::cast<std::int64_t>(value), 0, {}};
    if (PyFloat_Check(value.ptr()))
        return real(py::cast<double>(value));
    if (!py::isinstance<py::array>(value) && py::hasattr(value, "dtype") &&
        py::isinstance<py::dtype>(value.attr("dtype")) && py::cast<py::dtype>(value.attr("dtype")).kind() == 'f')
        return real(py::cast<double>(value));
    throw py::type_error("a card field must be an integer, real, string or None");
}

const model::CardLayout& layoutFor(const std::string& type, const std::string& form)
{
    const auto* layout = model::CardLayouts::standard()->find(type);
    if (!layout)
        throw py::value_error("unknown card type: " + type);
    if (form.empty())
        return *layout;
    for (const auto& candidate : layout->forms)
        if (candidate.name == form)
            return candidate.layout;
    throw py::value_error("unknown form " + form + " for " + type);
}

std::size_t columnIndex(const model::CardLayout& layout, py::handle name)
{
    if (py::isinstance<py::int_>(name))
    {
        const auto index = py::cast<std::size_t>(name);
        if (index == 0 || index > 1000000)
            throw py::value_error("field numbers must be in [1, 1000000]");
        return index - 1;
    }
    const auto field = py::cast<std::string>(name);
    for (std::size_t i = 0; i < layout.fields.size(); ++i)
        if (layout.fields[i].name == field)
            return i;
    throw py::value_error("unknown fixed field: " + field + " (use positional input for repeated fields)");
}

api::CardInput input(const std::string& type, py::handle fields, const std::string& form)
{
    api::CardInput result;
    result.type = type;
    result.form = form;
    const auto& layout = layoutFor(type, form);
    if (py::isinstance<py::dict>(fields))
    {
        std::set<std::size_t> seen;
        for (const auto& [name, value] : py::reinterpret_borrow<py::dict>(fields))
        {
            const auto index = columnIndex(layout, name);
            if (!seen.insert(index).second)
                throw py::value_error("duplicate field");
            if (result.fields.size() <= index)
                result.fields.resize(index + 1);
            result.fields[index] = scalar(value);
        }
    }
    else
    {
        if (!PySequence_Check(fields.ptr()) || py::isinstance<py::str>(fields))
            throw py::type_error("fields must be a sequence or mapping");
        for (auto value : py::reinterpret_borrow<py::sequence>(fields))
            result.fields.push_back(scalar(value));
    }
    return result;
}

template <class T>
using Array = py::array_t<T, py::array::c_style | py::array::forcecast>;

struct Column
{
    std::size_t index;
    std::optional<std::size_t> size;
    Value broadcast;
    std::vector<Value> values;
    std::optional<Array<std::int32_t>> ids;
    std::optional<Array<std::int64_t>> integers;
    std::optional<Array<std::uint64_t>> unsignedIntegers;
    std::optional<Array<double>> reals;

    Value at(std::size_t row) const
    {
        if (!size)
            return broadcast;
        if (ids)
            return {Value::Kind::Integer, ids->data()[row], 0, {}};
        if (integers)
            return {Value::Kind::Integer, integers->data()[row], 0, {}};
        if (unsignedIntegers)
        {
            const auto n = unsignedIntegers->data()[row];
            if (n > std::uint64_t(std::numeric_limits<std::int64_t>::max()))
                throw py::value_error("unsigned integer exceeds the supported signed range");
            return {Value::Kind::Integer, static_cast<std::int64_t>(n), 0, {}};
        }
        if (reals)
            return real(reals->data()[row]);
        return values.at(row);
    }
};

Column column(std::size_t index, py::handle data)
{
    Column c{};
    c.index = index;
    if (py::isinstance<py::array>(data))
    {
        const auto a = py::reinterpret_borrow<py::array>(data);
        if (a.ndim() != 1)
            throw py::value_error("batch arrays must be one-dimensional");
        c.size = static_cast<std::size_t>(a.size());
        switch (a.dtype().kind())
        {
        case 'c':
            throw py::type_error("complex numbers are not real card fields");
        case 'i':
            if (a.itemsize() == sizeof(std::int32_t))
                c.ids.emplace(a);
            else
                c.integers.emplace(a);
            return c;
        case 'u':
            c.unsignedIntegers.emplace(a);
            return c;
        case 'f':
            c.reals.emplace(a);
            return c;
        default:
            break;
        }
    }
    if (PySequence_Check(data.ptr()) && !py::isinstance<py::str>(data))
    {
        for (auto item : py::reinterpret_borrow<py::sequence>(data))
            c.values.push_back(scalar(item));
        c.size = c.values.size();
    }
    else
        c.broadcast = scalar(data);
    return c;
}

py::dict batch(const api::Deck& deck, const std::string& type, const py::dict& fields, std::optional<std::size_t> count,
               const std::string& form)
{
    const auto& layout = layoutFor(type, form);
    std::vector<Column> columns;
    std::set<std::size_t> seen;
    std::size_t width = 0;
    for (const auto& [name, data] : fields)
    {
        const auto index = columnIndex(layout, name);
        if (!seen.insert(index).second)
            throw py::value_error("duplicate batch field");
        auto c = column(index, data);
        if (c.size && count && c.size != count)
            throw py::value_error("batch column lengths differ");
        if (c.size)
            count = c.size;
        width = std::max(width, index + 1);
        columns.push_back(std::move(c));
    }
    if (!count)
        throw py::value_error("a scalar-only batch needs a count");
    const auto added = api::insertCardBatch(deck, type, *count,
                                            [&](std::size_t row)
                                            {
                                                api::CardInput card;
                                                card.type = type;
                                                card.form = form;
                                                card.fields.resize(width);
                                                for (const auto& c : columns)
                                                    card.fields[c.index] = c.at(row);
                                                return card;
                                            });
    py::array_t<std::int32_t> ids(added.size());
    py::array_t<std::uint32_t> keys(added.size());
    for (std::size_t i = 0; i < added.size(); ++i)
    {
        ids.mutable_data()[i] = added[i].id;
        keys.mutable_data()[i] = added[i].key;
    }
    return py::dict(py::arg("type") = type, py::arg("ids") = ids, py::arg("keys") = keys);
}

py::dict cardRef(const api::AddedCard& added)
{
    return py::dict(py::arg("type") = added.type, py::arg("id") = added.id, py::arg("key") = added.key);
}

py::list addCards(const api::Deck& deck, const py::list& definitions)
{
    std::vector<api::CardInput> records;
    for (auto item : definitions)
    {
        const auto definition = py::cast<py::dict>(item);
        auto record = input(py::cast<std::string>(definition["type"]), definition["fields"],
                            definition.contains("form") ? py::cast<std::string>(definition["form"]) : "");
        if (definition.contains("comment"))
            record.comment = py::cast<std::optional<std::string>>(definition["comment"]);
        records.push_back(std::move(record));
    }
    py::list refs;
    for (const auto& added : api::insertCards(deck, records))
        refs.append(cardRef(added));
    return refs;
}

py::list controlOutput(const std::vector<api::ControlRecord>& records)
{
    py::list result;
    for (const auto& r : records)
        result.append(py::dict(py::arg("name") = r.name, py::arg("fields") = r.fields, py::arg("comment") = r.comment));
    return result;
}

std::vector<api::ControlRecord> control(const py::list& records)
{
    std::vector<api::ControlRecord> result;
    for (const auto& item : records)
    {
        const auto r = py::cast<py::dict>(item);
        result.push_back({py::cast<std::string>(r["name"]), py::cast<std::vector<std::string>>(r["fields"]),
                          r.contains("comment") ? py::cast<std::string>(r["comment"]) : ""});
    }
    return result;
}
} // namespace

void bindModelBuilder(py::class_<api::Deck, std::shared_ptr<api::Deck>>& deck)
{
    deck.def(
            "add_card",
            [](const api::Deck& d, const std::string& type, py::object fields, const std::string& form,
               const std::optional<std::string>& comment)
            {
                auto record = input(type, fields, form);
                record.comment = comment;
                return cardRef(api::insertCard(d, record));
            },
            py::arg("type"), py::arg("fields"), py::kw_only(), py::arg("form") = "", py::arg("comment") = py::none())
        .def("add_cards", &addCards)
        .def("set_node_positions",
             [](const api::Deck& d, py::array_t<std::int32_t, py::array::c_style> ids,
                py::array_t<double, py::array::c_style> xyz)
             {
                 if (ids.ndim() != 1 || xyz.ndim() != 2 || xyz.shape(0) != ids.size() || xyz.shape(1) != 3)
                     throw py::value_error("expected ids (N,) and positions (N, 3)");
                 api::setNodePositions(d, {ids.data(), static_cast<std::size_t>(ids.size())},
                                       {xyz.data(), static_cast<std::size_t>(xyz.size())});
             }, py::arg("ids").noconvert(), py::arg("positions").noconvert())
        .def(
            "add_part",
            [](const api::Deck& d, const std::string& kind, std::int64_t id, std::int64_t massId, bool appends)
            { return d.addPart({kind, id, massId, appends}); }, py::arg("kind"), py::arg("id") = 0, py::kw_only(),
            py::arg("mass_id") = 0, py::arg("appends") = false)
        .def("part", &api::Deck::part, py::arg("kind"), py::arg("id"), py::arg("mass_id") = 0)
        .def("set_document", &api::Deck::setDocument)
        .def("document", &api::Deck::document)
        .def("document_names", &api::Deck::documentNames)
        .def("add_card_batch", &batch, py::arg("type"), py::arg("columns"), py::kw_only(),
             py::arg("count") = py::none(), py::arg("form") = "")
        .def("case_records", [](const api::Deck& d) { return controlOutput(api::caseRecords(d)); })
        .def("executive_records", [](const api::Deck& d) { return controlOutput(api::executiveRecords(d)); })
        .def("set_solution", &api::setSolution)
        .def("set_case_control",
             [](const api::Deck& d, const py::list& records) { api::setCaseControl(d, control(records)); })
        .def("set_executive",
             [](const api::Deck& d, const py::list& records) { api::setExecutive(d, control(records)); })
        .def("apply_defaults", &api::Deck::applyDefaults)
        .def("check_references", &api::Deck::checkReferences);
}
