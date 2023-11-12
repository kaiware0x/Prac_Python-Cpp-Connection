#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
    Pet(const std::string &name) : name(name) {}
    void               setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    const std::string &getROName() const { return name_ro; }

    static std::string getClassName() { return "Pet"; }

    std::string name_pub = "Public name";

private:
    std::string name;
    std::string name_ro = "Read only name";
};

PYBIND11_MODULE(extend02, m)
{
    /// クラスのExport。dynamic_attrで動的プロパティ設定を有効にできる.
    auto pet_class = py::class_<Pet>(m, "Pet", py::dynamic_attr());
    /**
        >>> p = example.Pet()
        >>> p.name = "Charly"  # OK, overwrite value in C++
        >>> p.age = 2  # OK, dynamically add a new attribute
        >>> p.__dict__  # just like a native Python class
        {'age': 2}
     */

    /// コンストラクタのExport
    pet_class.def(py::init<const std::string &>());

    /// メンバ関数のExport
    pet_class.def("setName", &Pet::setName);

    /// メンバ関数のExport
    pet_class.def("getName", &Pet::getName);

    /// クラス関数のExport
    pet_class.def_static("getClassName", &Pet::getClassName);

    /// ラムダ式のBind
    pet_class.def("__repr__", [](const Pet &a) { return "<example.Pet named '" + a.getName() + "'>"; });

    /// publicメンバ変数のExport
    pet_class.def_readwrite("name_pub", &Pet::name_pub);

    /// privateメンバ変数のGetterとSetterの定義
    pet_class.def_property("name", &Pet::getName, &Pet::setName);

    /// Read onlyプロパティのExport。どちらも同じ効果がある. _static()も用意されている.
    //    pet_class.def_property("name_ro", &Pet::getName, nullptr);
    pet_class.def_property_readonly("name_ro", &Pet::getROName);
}
