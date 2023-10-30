
///---------------------------------------------------------
/// pybind11
/// Advanced Topics - Classes
/// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
///---------------------------------------------------------

#include <pybind11/eval.h>
#include <pybind11/pybind11.h>
#include <iostream>
namespace py = pybind11;

class MyClass {
public:
    MyClass() {}

    bool myMethod(int32_t& value)
    {
        /// GILを取得
        py::gil_scoped_acquire gil;

        /// Python側でOverrideされた関数を検索
        py::function override_func = py::get_override(this, "myMethod");

        /// 関数が見つかった.
        if (override_func) {
            auto obj = override_func(value);        /// Python関数呼び出し
            if (py::isinstance<py::int_>(obj)) {    /// 戻り値がintかどうかチェック
                value = obj.cast<int32_t>();        /// intへキャストして引数に格納
                return true;                        /// Return true; value は更新された.
            }
            else {
                return false;    /// Python returned None, return false.
            }
        }

        /// 関数が見つからなかった.
        return false;
    }
};

///---------------------------------------------------------
/// カスタムコンストラクタ
///---------------------------------------------------------
class Example {
private:
    /// Privateコンストラクタ
    Example(int val) { std::cout << val << std::endl; };

public:
    /// ファクトリメソッド - 値返し
    static Example create(int a) { return Example(a); }

    /// Publicコンストラクタ
    Example(double val) { std::cout << val << std::endl; };
    Example(int val1, int val2) { std::cout << val1 << " " << val2 << std::endl; };
    Example(std::string val) { std::cout << val << std::endl; };

    Example() { std::cout << "Empty ctr" << std::endl; }
    virtual ~Example() = default;
};

class PyExample : public Example {
public:
    using Example::Example;
    PyExample(Example&& base) : Example(std::move(base)) {}
};

struct Aggregate {
    int         a;
    std::string b;
};

class MyPrivateClass {
public:
    MyPrivateClass() {}

private:
    ~MyPrivateClass() {}
};

class MyDangerClass {
public:
    MyDangerClass() = default;
    ~MyDangerClass()
    {
        try {
            py::print("Even printing is dangerous in a destructor");
            py::exec("raise ValueError('This is an unraisable exception')");
        }
        catch (py::error_already_set& e) {
            // error_context should be information about where/why the occurred,
            // e.g. use __func__ to get the name of the current function
            e.discard_as_unraisable(__func__);
        }
    }
};

///---------------------------------------------------------
/// モジュール定義
///---------------------------------------------------------

PYBIND11_MODULE(extend08, m)
{
    ///---------------------------------------------------------
    ///
    ///---------------------------------------------------------

    py::class_<Example>(m, "Example")
        /// Bind the factory function as a constructor:
        .def(py::init(&Example::create))
        /// Bind a lambda function returning a pointer wrapped in a holder:
        .def(py::init([](std::string arg) { return std::unique_ptr<Example>(new Example(arg)); }))
        /// Return a raw pointer:
        .def(py::init([](int a, int b) { return new Example(a, b); }))
        /// You can mix the above with regular C++ constructor bindings as well:
        .def(py::init<double>())
        .def(py::init());

    ///---------------------------------------------------------
    ///
    ///---------------------------------------------------------

    //    py::class_<Example, PyExample>(m, "Example")
    //        /// Returns an Example pointer.  If a PyExample is needed, the Example
    //        /// instance will be moved via the extra constructor in PyExample, above.
    //        .def(py::init([]() { return new Example(); }))
    //        // Two callbacks:
    //        .def(py::init([]() { return new Example(); } /* no alias needed */,
    //                      []() { return new PyExample(); } /* alias needed */))
    //        // *Always* returns an alias instance (like py::init_alias<>())
    //        .def(py::init([]() { return new PyExample(); }));

    ///---------------------------------------------------------
    ///
    ///---------------------------------------------------------

    /// 暗黙のコンストラクタが生成されている.
    py::class_<Aggregate>(m, "Aggregate").def(py::init<int, const std::string&>());

    /// privateまたはprotectedのデストラクタを持つクラスのバインディングを生成する.
    /// Python側でのデストラクタ呼び出しを避けるため py::nodelete を指定する.
    /// この場合、メモリリークを避けるために、C++側でインスタンスが解放されることが重要.
    py::class_<MyPrivateClass, std::unique_ptr<MyPrivateClass, py::nodelete>>(m, "MyPrivateClass").def(py::init<>());

    /// Pythonの関数はすべて例外を投げる可能性があるものとして扱うべき.
    py::class_<MyDangerClass>(m, "MyDangerClass").def(py::init());
}
