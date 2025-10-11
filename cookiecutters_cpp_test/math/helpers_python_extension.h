#ifndef COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H
#define COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cookiecutters_cpp_test/math/helpers.h"

namespace cookiecutters_cpp_test::math::helpers::helpers_python_extension {
    using cookiecutters_cpp_test::math::helpers::Helpers;

    class HelpersPythonExtension {
    public:
        static long long sum_of_squares_cpp(const std::vector<long long>& v) {
            return Helpers<long long>::sum_of_squares(v);
        }

        static double average_cpp(const std::vector<long long>& v) {
            return Helpers<long long>::average(v);
        }
    };

    PYBIND11_MODULE(helpers_python_extension, m) {
        m.doc() = "Math helpers.";
        m.def("sum_of_squares", &HelpersPythonExtension::sum_of_squares_cpp, "Sum of squares of ints");
        m.def("average", &HelpersPythonExtension::average_cpp, "Average of ints");
    }
}

#endif //COOKIECUTTERS_CPP_TEST_MATH_HELPERS_PYTHON_EXTENSION_H