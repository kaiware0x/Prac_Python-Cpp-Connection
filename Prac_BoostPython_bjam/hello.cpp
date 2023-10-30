#include <boost/python.hpp>
#include <iostream>

char const *greet()
{
    return "hello, world";
}

class MyClass {
public:
    MyClass(int value) : value_(value) {}
    void add(int x) {
        value_ += x;
    }
    int get_value() const {
        return value_;
    }
private:
    int value_;
};


BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def("greet", greet);
    class_<MyClass>("MyClass", init<int>())
        .def("add", &MyClass::add)
        .def("get_value", &MyClass::get_value)
    ;
}