
#include <pybind11/embed.h>    // everything needed for embedding
#include <filesystem>
#include <fstream>
#include <iostream>

namespace py = pybind11;
using namespace py::literals;

PYBIND11_EMBEDDED_MODULE(fast_calc, m)
{
    // `m` is a `py::module_` which is used to bind functions and classes
    m.def("add", [](int i, int j) { return i + j; });
}

PYBIND11_EMBEDDED_MODULE(cpp_module, m)
{
    m.attr("a") = 1;
}

int main()
{
    {
        if (!std::filesystem::exists("py_module.py")) {
            std::ofstream py_module("py_module.py");
            py_module << "import cpp_module\n";
            py_module << "a = cpp_module.a\n";
            py_module << "b = a + 1\n";
            py_module.close();
        }
    }

    py::scoped_interpreter guard{};    // start the interpreter and keep it alive

    py::print("Hello, World!");    // use the Python API

    py::exec(R"(
        kwargs = dict(name="World", number=1)
        message = "Hello, {name}! The answer is {number}".format(**kwargs)
        print(message)
    )");

    {
        auto kwargs  = py::dict("name"_a = "World", "number"_a = 2);
        auto message = "Hello, {name}! The answer is {number}"_s.format(**kwargs);
        py::print(message);
    }

    {
        auto locals = py::dict("name"_a = "World", "number"_a = 3);
        py::exec(R"(
            message = "Hello, {name}! The answer is {number}".format(**locals())
        )",
                 py::globals(), locals);

        auto message = locals["message"].cast<std::string>();
        std::cout << message << std::endl;
    }

    {
        py::module_ sys = py::module_::import("sys");
        py::print(sys.attr("path"));
    }

    {
        auto fast_calc = py::module_::import("fast_calc");
        auto result    = fast_calc.attr("add")(1, 2).cast<int>();
        assert(result == 3);
        std::cout << "fast_calc result: " << result << std::endl;
    }

    {
        try {
            auto py_module = py::module_::import("py_module");

            auto locals = py::dict("fmt"_a = "{} + {} = {}", **py_module.attr("__dict__"));
            assert(locals["a"].cast<int>() == 1);
            assert(locals["b"].cast<int>() == 2);

            py::exec(R"(
            c = a + b
            message = fmt.format(a, b, c)
        )",
                     py::globals(), locals);

            py::exec(R"(
                        print(c)
                        print(message)
                    )",
                     py::globals(), locals);

            assert(locals["c"].cast<int>() == 3);
            assert(locals["message"].cast<std::string>() == "1 + 2 = 3");

            std::cout << "py_module c: " << locals["c"].cast<int>() << std::endl;
            std::cout << "py_module message: " << locals["message"].cast<std::string>() << std::endl;
        }
        catch (py::error_already_set e) {
            std::cout << e.what() << std::endl;
        }
    }

    {
        py::print(1, 2.0, "three");                   // 1 2.0 three
        py::print(1, 2.0, "three", "sep"_a = "-");    // 1-2.0-three

        auto args = py::make_tuple("unpacked", true);
        py::print("->", *args, "end"_a = "<-");    // -> unpacked True <-
    }
}
