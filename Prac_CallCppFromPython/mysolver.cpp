#define PY_SSIZE_T_CLEAN

#include <Python.h>

static int calc(int a, int x, int b)
{
    return a * x + b;
}

/**
 * @brief C関数calc()をラップする.
 * @param self
 * @param args
 * @return
 */
static PyObject* mysolver_calc(PyObject* self, PyObject* args)
{
    int a, x, b;

    /// iii = int3つに展開
    if (!PyArg_ParseTuple(args, "iii", &a, &x, &b)) {
        return nullptr;
    }
    int ret = calc(a, x, b);
    return PyLong_FromLong(ret);
}

// clang-format off
/**
 * @brief メソッドの登録
 */
static PyMethodDef mysolver_methods[] = {
    {
        "calc",         /// Pythonで参照する関数名
        mysolver_calc,  /// C関数
        METH_VARARGS,   /// 呼び出し規約
        "Solve ax+b"    /// 関数のdocstring
    },
    {nullptr, nullptr, 0, nullptr},
};
// clang-format on

/**
 * @brief モジュールの登録
 */
static PyModuleDef mysolver_module = {
    PyModuleDef_HEAD_INIT,    /// 初期化子
    "mysolver",               /// モジュール名
    "Sample module.",         /// モジュールのDocstring
    -1,                       /// モジュールのメモリ領域?
    mysolver_methods          /// モジュールの関数のテーブルへのポインタ
};

/**
 * モジュールの初期化
 * importされたときに呼ばれる
 * PyInit_XXXのXXXはモジュール名と一致させる
 */
PyMODINIT_FUNC PyInit_mysolver()
{
    return PyModule_Create(&mysolver_module);
}
