
///---------------------------------------------------------
/// pybind11
/// Advanced Topics - Classes
/// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
///---------------------------------------------------------

#include <pybind11/pybind11.h>
#include <iostream>
namespace py = pybind11;

///---------------------------------------------------------
/// 通常のC++クラス、関数
///---------------------------------------------------------

class Animal {
public:
    virtual ~Animal() {}
    virtual std::string go(int n_times) = 0;
    virtual std::string name() { return "unknown"; }
};

class Dog : public Animal {
public:
    std::string go(int n_times) override
    {
        std::string result;
        for (int i = 0; i < n_times; ++i)
            result += bark() + " ";
        return result;
    }

    virtual std::string bark() { return "woof!"; }
};

class Husky : public Dog {
public:
    std::string bark() override { return "gaow!"; }
};

std::string call_go(Animal *animal)
{
    return animal->go(3);
}

///---------------------------------------------------------
/// 仮想関数コールをPythonへ転送するためのトランポリンクラス
///---------------------------------------------------------

template <class AnimalBase = Animal>
class PyAnimal : public AnimalBase {
public:
    using AnimalBase::AnimalBase;    // Inherit constructors
    std::string go(int n_times) override
    {
        PYBIND11_OVERRIDE_PURE(std::string,    /// 戻り値型
                               AnimalBase,     /// 親クラス
                               go,             /// 継承する関数
                               n_times         /// 引数
        );
        /// -> std::string AnimalBase::go(n_times);
    }
    std::string name() override
    {
        PYBIND11_OVERRIDE(std::string, AnimalBase, name, );
        /// -> std::string AnimalBase::name();
    }
};
template <class DogBase = Dog>
class PyDog : public PyAnimal<DogBase> {
public:
    using PyAnimal<DogBase>::PyAnimal;    // Inherit constructors
    // Override PyAnimal's pure virtual go() with a non-pure one:
    std::string go(int n_times) override
    {
        PYBIND11_OVERRIDE(std::string, DogBase, go, n_times);
        /// -> std::string DogBase::go(n_times);
    }
    std::string bark() override { PYBIND11_OVERRIDE(std::string, DogBase, bark, ); }
};

///---------------------------------------------------------
/// モジュール定義
///---------------------------------------------------------

PYBIND11_MODULE(extend07, m)
{
    /// Animal基底クラスの登録
    /// Animal基底クラスは抽象クラスなのでコンストラクトできない.
    /// そこでAnimalを継承したPyAnimalを定義し、PyAnimalをPythonから見た基底クラスとする.

    /// テンプレート型引数にヘルパークラスを指定する (順番は関係ない)
    auto py_animal_class = py::class_<Animal, PyAnimal<> /* <--- trampoline*/>(m, "Animal");
    py_animal_class.def(py::init<>());
    py_animal_class.def("go", &Animal::go);

    py::class_<Dog, Animal, PyDog<>>(m, "Dog").def(py::init<>());
    py::class_<Husky, Animal, PyDog<Husky>>(m, "Husky").def(py::init<>());

    m.def("call_go", &call_go);
}
