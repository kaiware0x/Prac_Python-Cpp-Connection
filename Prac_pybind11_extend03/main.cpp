#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
    Pet(const std::string &name) : name(name) {}
    std::string name;
};

struct Dog : Pet {
    Dog(const std::string &name) : Pet(name) {}
    std::string bark() const { return "woof!"; }
};

struct PolymorphicPet {
    virtual ~PolymorphicPet() = default;
};

struct PolymorphicDog : PolymorphicPet {
    std::string bark() const { return "woof!"; }
};

PYBIND11_MODULE(extend3, m)
{
    auto pet_class = py::class_<Pet>(m, "Pet");
    pet_class.def(py::init<const std::string &>());
    pet_class.def_readwrite("name", &Pet::name);

    /// Method 1: template parameter:
    //    auto dog_class = py::class_<Dog, Pet /* <- specify C++ parent type */>(m, "Dog");
    /// Method 2: pass parent class_ object:
    auto dog_class = py::class_<Dog>(m, "Dog", pet_class);
    dog_class.def(py::init<const std::string &>());
    dog_class.def("bark", &Dog::bark);

    /// Return a base pointer to a derived instance
    m.def("pet_store", []() { return std::unique_ptr<Pet>(new Dog("Molly")); });

    ///---------------------------------------------------------
    ///
    ///---------------------------------------------------------

    /// Same binding code
    py::class_<PolymorphicPet>(m, "PolymorphicPet");
    py::class_<PolymorphicDog, PolymorphicPet>(m, "PolymorphicDog")
        .def(py::init<>())
        .def("bark", &PolymorphicDog::bark);

    /// Again, return a base pointer to a derived instance
    m.def("pet_store2", []() { return std::unique_ptr<PolymorphicPet>(new PolymorphicDog); });
}
