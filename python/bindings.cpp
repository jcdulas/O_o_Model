#include "oor/api/CardTables.hpp"
#include "oor/api/CardEdits.hpp"
#include "oor/api/Design.hpp"
#include "oor/api/Queries.hpp"
#include "oor/query/table/ArrowExport.hpp"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace oor;

namespace
{
struct Table
{
    std::shared_ptr<const query::QueryTable> data;
};

struct QueryWorkers
{
    std::unique_ptr<base::ThreadPool> pool;
    bool closed = false;

    base::ThreadPool* get()
    {
        if (!closed && !pool) pool = std::make_unique<base::ThreadPool>(base::ThreadPool::defaultWorkerCount() - 1);
        return pool.get();
    }
};

// The capsule owns the outer structure. Its release callback owns the Arrow buffers until consumed.
template <class T>
py::capsule capsule(const char* name)
{
    auto storage = std::make_unique<T>();
    py::capsule result(storage.get(), name,
                       [](void* raw)
                       {
                           std::unique_ptr<T> value(static_cast<T*>(raw));
                           if (value->release)
                               value->release(value.get());
                       });
    storage.release();
    return result;
}

py::tuple exportTable(const Table& table, const py::object& requested)
{
    if (!requested.is_none())
        throw py::value_error("Requested schema conversion is unavailable");
    auto schema = capsule<ArrowSchema>("arrow_schema");
    auto array = capsule<ArrowArray>("arrow_array");
    query::ArrowExport::exportSchema(*table.data, schema.get_pointer<ArrowSchema>());
    query::ArrowExport::exportArray(*table.data, array.get_pointer<ArrowArray>());
    return py::make_tuple(schema, array);
}
} // namespace

PYBIND11_MODULE(_native, m)
{
    auto workers = std::make_shared<QueryWorkers>();
    py::module_::import("atexit").attr("register")(py::cpp_function([workers] {
        workers->closed = true;
        workers->pool.reset();
    }));
    py::class_<Table>(m, "Table")
        .def("__arrow_c_array__", &exportTable, py::arg("requested_schema") = py::none())
        .def_property_readonly("columns", [](const Table& t) { return t.data->columnNames(); })
        .def("__len__", [](const Table& t) { return t.data->rowCount(); });
    py::class_<api::DiagnosticText>(m, "Diagnostic")
        .def_readonly("severity", &api::DiagnosticText::severity)
        .def_readonly("message", &api::DiagnosticText::message)
        .def_readonly("code", &api::DiagnosticText::code)
        .def_readonly("location", &api::DiagnosticText::location);
    py::class_<api::Deck, std::shared_ptr<api::Deck>>(m, "Deck")
        .def("copy", &api::Deck::copy)
        .def("set_card_value", [](const api::Deck& d, const std::string& card, std::int32_t id,
                                  const std::string& field, py::object value) {
            api::setCardValue(d, card, id, field, py::str(value).cast<std::string>());
        }, py::arg("card"), py::arg("id"), py::arg("field"), py::arg("value"))
        .def_property_readonly("card_counts",
                               [](const api::Deck& d)
                               {
                                   py::dict result;
                                   for (const auto& [name, count] : d.cardCounts())
                                       result[py::str(name)] = count;
                                   return result;
                               })
        .def_property_readonly("diagnostics", &api::Deck::diagnostics)
        .def_property_readonly("versions",
                               [](const api::Deck& d)
                               {
                                   const auto v = api::modelVersions(d);
                                   return py::make_tuple(v.structure, v.content, v.control);
                               })
        .def("card_types", &api::cardTypesOf)
        .def(
            "card_table",
            [](const api::Deck& d, const std::string& name, const std::vector<std::string>& cols)
            { return Table{api::cardTable(d, name, cols)}; },
            py::arg("name"), py::arg("columns") = std::vector<std::string>{})
        .def("query",
             [workers](const std::shared_ptr<api::Deck>& d, const std::string& name, const py::kwargs& args)
             {
                 auto json = py::module_::import("json").attr("dumps")(args).cast<std::string>();
                 return Table{api::runQueryWithPool(name, d, nullptr, api::argumentsFromJson(name, json), workers->get())};
             })
        .def_property_readonly("offset_definition",
                               [](const api::Deck& d)
                               {
                                   const auto table = api::cardTable(d, "ModelParams", {"name", "text"});
                                   std::string result = "ElemOffsetsOnly";
                                   for (std::int64_t i = 0; i < table->rowCount(); ++i)
                                       if (table->column("name").textAt(i) == "OffsetDefinition")
                                           result = table->column("text").textAt(i);
                                   return result;
                               })
        .def("displacement_rotations",
             [](const api::Deck& d)
             {
                 auto values = std::make_unique<std::vector<double>>(api::displacementRotations(d));
                 auto* data = values.get();
                 py::capsule owner(data, [](void* p) { delete static_cast<std::vector<double>*>(p); });
                 values.release();
                 return py::array_t<double>(
                     {static_cast<py::ssize_t>(data->size() / 9), py::ssize_t(3), py::ssize_t(3)}, data->data(), owner);
             })
        .def("validate_design",
             [](const api::Deck& d)
             {
                 const auto model = api::designModel(d);
                 if (!model.problems().empty())
                     throw py::value_error(model.problems().front());
                 if (!model.notApplied().empty())
                 {
                     const auto& first = model.notApplied().front();
                     throw py::value_error(first.card + " " + std::to_string(first.id) + ": " + first.reason);
                 }
             })
        .def("with_design_point",
             [](const api::Deck& d, const std::vector<std::int32_t>& ids, const std::vector<double>& values)
             {
                 auto copy = d.copy();
                 (void)api::applyDesignPoint(*copy, ids, values);
                 return copy;
             })
        .def("write_archive", [](const api::Deck& d, const std::string& path) { d.writeArchive(path); })
        .def("write_model", [](const api::Deck& d, const std::string& path) { return d.writeModel(path); });
    m.def(
        "read_model", [](const std::string& path, bool strict) { return api::Deck::readModel(path, {strict}); },
        py::arg("path"), py::arg("strict") = true, py::call_guard<py::gil_scoped_release>());
    m.def("card_columns",
          [](const std::string& name)
          {
              const auto c = api::cardTableColumns(name);
              return py::make_tuple(c.stored, c.computed);
          });
}
