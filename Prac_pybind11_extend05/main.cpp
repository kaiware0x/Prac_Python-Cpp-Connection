#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
    enum Kind { Dog = 0, Cat };

    struct Attributes {
        float age = 0;
    };

    Pet(const std::string &name, Kind type) : name(name), type(type) {}

    std::string name;
    Kind        type;
    Attributes  attr;
};

PYBIND11_MODULE(extend5, m)
{
    py::class_<Pet> pet_class(m, "Pet");

    pet_class.def(py::init<const std::string &, Pet::Kind>())
        .def_readwrite("name", &Pet::name)
        .def_readwrite("type", &Pet::type)
        .def_readwrite("attr", &Pet::attr);

    auto pet_kind_enum = py::enum_<Pet::Kind>(pet_class, "Kind");
    pet_kind_enum.value("Dog", Pet::Kind::Dog);
    pet_kind_enum.value("Cat", Pet::Kind::Cat);
    pet_kind_enum.export_values();    /// 親スコープへExport

    auto pet_attr = py::class_<Pet::Attributes>(pet_class, "Attributes");
    pet_attr.def(py::init<>());
    pet_attr.def_readwrite("age", &Pet::Attributes::age);
}
