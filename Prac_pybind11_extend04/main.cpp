#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
    Pet(const std::string &name, int age) : name(name), age(age) {}

    void set(int age_) { age = age_; }
    void set(const std::string &name_) { name = name_; }

    std::string name;
    int         age;
};

struct Widget {
    int foo(int x, float y) { return 1; }
    int foo(int x, float y) const { return 2; }
};

PYBIND11_MODULE(extend4, m)
{
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &, int>())
        .def("set", py::overload_cast<int>(&Pet::set), "Set the pet's age")
        .def("set", py::overload_cast<const std::string &>(&Pet::set), "Set the pet's name");

    py::class_<Widget>(m, "Widget")
        .def(py::init<>())
        .def("foo_mutable", py::overload_cast<int, float>(&Widget::foo))
        .def("foo_const", py::overload_cast<int, float>(&Widget::foo, py::const_));
}
