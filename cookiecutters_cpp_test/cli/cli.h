#ifndef COOKIECUTTERS_CPP_TEST_CLI_CLI_H
#define COOKIECUTTERS_CPP_TEST_CLI_CLI_H

#include "cookiecutters_cpp_test/math/helpers.h"

namespace cookiecutters_cpp_test::cli::cli {
    using cookiecutters_cpp_test::math::helpers::Helpers;

    struct CommandLineInterface {
        int main(int argc, char* argv[]) {
            return Helpers<int>::average({1, 2, 3});
        }
    };
}

#endif //COOKIECUTTERS_CPP_TEST_CLI_CLI_H