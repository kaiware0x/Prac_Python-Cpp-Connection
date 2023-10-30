
///---------------------------------------------------------
/// pybind11
/// Advanced Topics - Classes
/// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
///---------------------------------------------------------

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <iostream>
namespace py = pybind11;

class Vector2 {
public:
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2  operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); }
    Vector2  operator-() const { return Vector2(-x, -y); }
    Vector2  operator*(float value) const { return Vector2(x * value, y * value); }
    Vector2 &operator+=(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2 &operator*=(float v)
    {
        x *= v;
        y *= v;
        return *this;
    }

    friend Vector2 operator*(float f, const Vector2 &v) { return Vector2(f * v.x, f * v.y); }

    std::string toString() const { return "[" + std::to_string(x) + ", " + std::to_string(y) + "]"; }

private:
    float x, y;
};

class Pickleable {
public:
    Pickleable(const std::string &value) : m_value(value) {}
    const std::string &value() const { return m_value; }

    void setExtra(int extra) { m_extra = extra; }
    int  extra() const { return m_extra; }

private:
    std::string m_value;
    int         m_extra = 0;
};

class Copyable {
public:
    Copyable() {}
    Copyable(const Copyable &other) { std::cout << "Copy!" << std::endl; }
};

///---------------------------------------------------------
/// モジュール定義
///---------------------------------------------------------

PYBIND11_MODULE(extend09, m)
{
    py::class_<Vector2>(m, "Vector2")
        .def(py::init<float, float>())
        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self *= float())
        .def(float() * py::self)
        .def(py::self * float())
        .def(-py::self)
        .def("__repr__", &Vector2::toString);

    /**
        .def(py::self * float())
            は、以下の処理の略記
        .def("__mul__", [](const Vector2 &a, float b) {
            return a * b;
        }, py::is_operator())
     */
    /// py::is_operatorフラグマーカーは、型エラーを投げるのではなく、
    /// 互換性のない引数で呼び出された時に
    /// NotImplemented
    /// を返す演算子であることを pybind11 に通知するために必要です。

    py::class_<Pickleable>(m, "Pickleable")
        .def(py::init<std::string>())
        .def("value", &Pickleable::value)
        .def("extra", &Pickleable::extra)
        .def("setExtra", &Pickleable::setExtra)
        .def(py::pickle(
            [](const Pickleable &p) {    // __getstate__
                /* Return a tuple that fully encodes the state of the object */
                return py::make_tuple(p.value(), p.extra());
            },
            [](py::tuple t) {    // __setstate__
                if (t.size() != 2) throw std::runtime_error("Invalid state!");

                /* Create a new C++ instance */
                Pickleable p(t[0].cast<std::string>());

                /* Assign any additional state */
                p.setExtra(t[1].cast<int>());

                return p;
            }));

    /// pickleをサポートするクラスは、自動的に(deep)copyにも対応します。
    /// しかし、カスタムの__copy__および__deepcopy__メソッドを追加することで、
    /// パフォーマンスを向上させることができます。
    using namespace py::literals;
    py::class_<Copyable>(m, "Copyable")
        .def(py::init())
        .def("__copy__", [](const Copyable &self) { return Copyable(self); })
        .def(
            "__deepcopy__", [](const Copyable &self, py::dict) { return Copyable(self); }, "memo"_a);
}
