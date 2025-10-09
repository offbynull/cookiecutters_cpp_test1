#ifndef COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H
#define COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H

#include <Python.h>
#include "cookiecutters_cpp_test/math/helpers.h"

namespace cookiecutters_cpp_test::math::helpers::helpers_python_extension {
    using cookiecutters_cpp_test::math::helpers::Helpers;

    static std::vector<long long> to_vec_ll(PyObject* obj) {
        PyObject* fast = PySequence_Fast(obj, "expected iterable");
        if (!fast) {
            return {};
        }
        std::vector<long long> out {};
        out.reserve(PySequence_Fast_GET_SIZE(fast));
        PyObject** items = PySequence_Fast_ITEMS(fast);
        Py_ssize_t n = PySequence_Fast_GET_SIZE(fast);
        for (Py_ssize_t i = 0; i < n; ++i) {
            long long v = PyLong_AsLongLong(items[i]);
            if (PyErr_Occurred()) {
                Py_DECREF(fast);
                return {};
            }
            out.push_back(v);
        }
        Py_DECREF(fast);
        return out;
    }

    extern "C" {
        static PyObject* py_sum_of_squares(PyObject*, PyObject* args) {
            PyObject* seq;
            if (!PyArg_ParseTuple(args, "O", &seq)) {
                return nullptr;
            }
            auto v = to_vec_ll(seq);
            if (PyErr_Occurred()) {
                return nullptr;
            }
            long long r = Helpers<long long>::sum_of_squares(v);
            return PyLong_FromLongLong(r);
        }

        static PyObject* py_average(PyObject*, PyObject* args) {
            PyObject* seq;
            if (!PyArg_ParseTuple(args, "O", &seq)) {
                return nullptr;
            }
            auto v = to_vec_ll(seq);
            if (PyErr_Occurred()) {
                return nullptr;
            }
            double r = Helpers<long long>::average(v);
            return PyFloat_FromDouble(r);
        }

        static PyMethodDef Methods[] = {
            {"sum_of_squares", py_sum_of_squares, METH_VARARGS, "Sum of squares of ints"},
            {"average",        py_average,        METH_VARARGS, "Average of ints"},
            {nullptr, nullptr, 0, nullptr}
        };

        static struct PyModuleDef Module = {
            // IMPORTANT: Once compiled, this python extension MUST be at the package referenced below (e.g., if the string below is "a.b.c.d", the extension must live under to /a/b/c)
            PyModuleDef_HEAD_INIT, "cookiecutters_cpp_test.math.helpers_python_extension", nullptr, -1, Methods
        };


        PyMODINIT_FUNC PyInit_helpers_python_extension(void) {
            return PyModule_Create(&Module);
        }
    }
}

#endif // COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H