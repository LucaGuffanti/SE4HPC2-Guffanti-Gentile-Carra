#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "test_algebraic.hpp"
#include "test_combinatorial.hpp"
#include "test_monkey.hpp"
#include "test_structural.hpp"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "Running 'em all!" << std::endl;
    return RUN_ALL_TESTS();
}
