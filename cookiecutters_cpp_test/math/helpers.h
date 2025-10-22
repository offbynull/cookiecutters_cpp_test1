#ifndef COOKIECUTTERS_CPP_TEST_MATH_HELPERS_H
#define COOKIECUTTERS_CPP_TEST_MATH_HELPERS_H

#include <vector>
#include <numeric>
#include <concepts>

namespace cookiecutters_cpp_test::math::helpers {
    /**
     * Math helpers.
     * 
     * @tparam T Integral type used for computations.
     */
    template <std::integral T>
    struct Helpers {
        /**
         * Sum of squares.
         * 
         * @param v Input numbers.
         * @return Sum of `v` squared.
         */
        static T sum_of_squares(const std::vector<T>& v) {
            return std::accumulate(v.begin(), v.end(), T{0},
                [](T acc, T x) { return acc + x * x; });
        }

        /**
         * Average.
         * 
         * @param v Input numbers.
         * @return Average of `v`.
         */
        static T average(const std::vector<T>& v) {
            if (v.empty()) return 0.0;
            auto sum = std::accumulate(v.begin(), v.end(), T{0});
            return static_cast<T>(sum) / static_cast<T>(v.size());
        }
    };
}

#endif //COOKIECUTTERS_CPP_TEST_MATH_HELPERS_H