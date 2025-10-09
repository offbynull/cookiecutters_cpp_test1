#include "gtest/gtest.h"
#include "cookiecutters_cpp_test/math/helpers.h"

namespace {
    using cookiecutters_cpp_test::math::helpers::Helpers;
    
    TEST(CMHelpersTest, MustGetSumOfSquares) {
        EXPECT_EQ(
            14,
            (Helpers<int>::sum_of_squares({1, 2, 3}))
        );
    }

    TEST(CMHelpersTest, MustGetAverage) {
        EXPECT_EQ(
            2,
            (Helpers<int>::average({1, 2, 3}))
        );
    }
}