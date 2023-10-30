
#include <boost/python.hpp>

namespace py = boost::python;

int main()
{
    Py_Initialize();    // 最初に呼んでおく必要あり

    try {
        // Pythonで「print('Hello World!')」を実行
        py::object global = py::import("__main__").attr("__dict__");
        py::exec("print('Hello World!')", global);
    }
    catch (const py::error_already_set &) {
        // Pythonコードの実行中にエラーが発生した場合はエラー内容を表示
        PyErr_Print();
    }

    return 0;
}
