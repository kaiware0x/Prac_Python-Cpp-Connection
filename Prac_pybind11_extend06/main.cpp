
///---------------------------------------------------------
/// pybind11
/// Advanced Topics - Functions
/// https://pybind11.readthedocs.io/en/stable/advanced/functions.html
///---------------------------------------------------------

#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

struct Data {
    int value = 0;
};

struct SomeType {
    SomeType(int x_) : x(x_) {}
    int x;
};

class MyClass {
public:
    MyClass() {}

    static Data* getData() { return s_data; }

    int myFunction(SomeType st) { return st.x; }

private:
    static inline Data* s_data = new Data;
};

class Dog {};
class Cat {};

void print_dict(const py::dict& dict)
{
    /* Easily interact with Python types */
    for (auto item : dict)
        std::cout << "key=" << std::string(py::str(item.first)) << ", "
                  << "value=" << std::string(py::str(item.second)) << std::endl;
}

void generic(py::args args, const py::kwargs& kwargs)
{
    /// .. do something with args
    if (kwargs) {
        /// .. do something with kwargs
    }
}

template <typename T>
void set(T t)
{
    std::cout << "set: " << t << std::endl;
}

PYBIND11_MODULE(extend6, m)
{
    ///---------------------------------------------------------
    /// https://pybind11.readthedocs.io/en/stable/advanced/functions.html#return-value-policies
    ///---------------------------------------------------------

    /// --- Bad ---
    /// staticインスタンスの所有権がPythonにmoveされ、
    /// 参照カウントがゼロになるとPython側でDeleteが呼ばれてしまう!
    //    m.def("getData", &MyClass::getData);

    /// --- Good ---
    /// 参照のみを渡し、Pythonへ所有権を渡さない.
    m.def("getData", &MyClass::getData, py::return_value_policy::reference);

    ///---------------------------------------------------------
    ///
    ///---------------------------------------------------------

    m.def("print_dict", &print_dict);
    m.def("generic", &generic);

    auto some_type = py::class_<SomeType>(m, "SomeType");
    some_type.def(py::init<int>());

    auto myclass = py::class_<MyClass>(m, "MyClass");
    myclass.def(py::init());
    //    myclass.def("myFunction", &MyClass::myFunction, py::arg("arg") = SomeType(123));
    /// py::arg_vによって__repr__に任意のテキストを設定できる.
    myclass.def("myFunction", &MyClass::myFunction, py::arg_v("arg", SomeType(123), "SomeType(int)"));

    ///  py::kw_only()以降の引数は必ずキーワード引数で呼ぶ必要がある.
    m.def(
        "f", [](int a, int b) { return a * b; }, py::arg("a"), py::kw_only(), py::arg("b"));

    /// noconvert()によって暗黙の型変換を禁止できる.
    m.def(
        "floats_only", [](double f) { return 0.5 * f; }, py::arg("f").noconvert());
    m.def(
        "floats_preferred", [](double f) { return 0.5 * f; }, py::arg("f"));

    ///---------------------------------------------------------
    /// None引数の処理
    /// https://pybind11.readthedocs.io/en/stable/advanced/functions.html#allow-prohibiting-none-arguments
    ///---------------------------------------------------------
    py::class_<Dog>(m, "Dog").def(py::init<>());
    py::class_<Cat>(m, "Cat").def(py::init<>());
    m.def(
        "bark",
        [](Dog* dog) -> std::string {
            if (dog)
                return "woof!"; /* Called with a Dog instance */
            else
                return "(no dog)"; /* Called with None, dog == nullptr */
        },
        py::arg("dog").none(true));    /// None引数を許可する(default)
    m.def(
        "meow",
        [](Cat* cat) -> std::string {
            // Can't be called with None argument
            return "meow";
        },
        py::arg("cat").none(false));    /// None引数を許可しない

    ///---------------------------------------------------------
    /// テンプレート
    /// https://pybind11.readthedocs.io/en/stable/advanced/functions.html#binding-functions-with-template-parameters
    ///---------------------------------------------------------
    /// それぞれインスタンス化する必要がある.
    /// 同じ名前でバインドすればオーバーロードと同じ扱いになる.
    m.def("set", &set<int>);
    m.def("set", &set<std::string>);

    /// 別名を付けたほうが安全なときもある.
    m.def("setInt", &set<int>);
    m.def("setString", &set<std::string>);
}
