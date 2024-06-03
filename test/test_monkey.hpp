#ifndef TEST_MONKEY_HPP
#define TEST_MONKEY_HPP

#include <vector>
#include <random>
#include <iostream>
#include <gtest/gtest.h>
#include "matrix_multiplication.h"
#include "matrix_multiplication_trusted.hpp"


/**
 * @brief Fuzz test for matrix multiplication. It generates random matrices of elements uniformly distributed in the
 * range [1, 10] and checks if the product of the matrices is correct.
 * @note The test chooses two random matrices A and B and computes their product. It then compares the result with the 
 * value obtained by using a trusted method for calculating the matrix product: "multiplyMatricesWithoutErrors".
 * The test is repeated 100 times and every time the dimensions are choosen randomly between 1 and 10. 
 * 
 * If the test fails, it prints the seed used to generate the random matrices in order for the test to be REPRODUCIBLE. 
 * 
 * 
 * To extract the errors, the seed and the iteration number that failed, run the following command:
 * ./test_monkey 2>&1 | egrep -i "error*|*seed: [0-9]*" | sort | uniq
 *
 * @note The following errors are found with seed 3922693891:
 * @note Error 1  : Element-wise multiplication of ones detected!
 * @note Error 2  : Matrix A contains the number 7!
 * @note Error 4  : Matrix B contains the number 3!
 * @note Error 6  : Result matrix contains a number bigger than 100!
 * @note Error 7  : Result matrix contains a number between 11 and 20!
 * @note Error 9  : Result matrix contains the number 99!
 * @note Error 10 : A row in matrix A contains more than one '1'!
 * @note Error 12 : The number of rows in A is equal to the number of columns in B!
 * @note Error 13 : The first element of matrix A is equal to the first element of matrix B!
 * @note Error 14 : The result matrix C has an even number of rows!
 * @note Error 15 : A row in matrix A is filled entirely with 5s!
 * @note Error 16 : Matrix B contains the number 6!
 * @note Error 17 : Result matrix C contains the number 17!
 * @note Error 18 : Matrix A is a square matrix!
 * @note Error 19 : Every row in matrix A contains the number 8!
 * @note Error 20 : Number of columns in matrix A is odd!
 */
TEST(MonkeyTests, RandomMatrices) {
    std::random_device rd;
    auto seed = rd();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < 100; ++i) {
        // pick random dimensions for the matrices
        int rowA = dis(gen);
        int colA = dis(gen);
        int colB = dis(gen);

        std::vector<std::vector<int>> A(rowA, std::vector<int>(colA));
        std::vector<std::vector<int>> B(colA, std::vector<int>(colB));
        std::vector<std::vector<int>> C(rowA, std::vector<int>(colB));
        std::vector<std::vector<int>> expected(rowA, std::vector<int>(colB));

        // Fill A and B with random numbers
        for (auto& row : A)
            for (auto& elem : row)
                elem = dis(gen);

        for (auto& row : B)
            for (auto& elem : row)
                elem = dis(gen);

        multiplyMatrices(A, B, C, rowA, colA, colB);
        multiplyMatricesWithoutErrors(A, B, expected, rowA, colA, colB);

        // Check the result
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! Seed: " << seed << ", iteration:" << i;
        
    }
}


#endif // TEST_MONKEY_HPP