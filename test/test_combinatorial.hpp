#ifndef TEST_COMBINATORIAL_HPP
#define TEST_COMBINATORIAL_HPP

/**
 * @file test_combinatorial.cpp
 * @brief Test that iteratively computes simple products to enumerate all possible cases
 */

#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

/**
 * @brief Through extensive testing it was found that there seems to exist a correlation
 * between the values present in the matrix and the presence of errors. A possible way to verify this
 * is through the use of a COMBINATORIAL TESTs, that enumerates all possible cases of legal inputs. 
 * (identified as being from -100 to 100 from the previous tests) This test computes matrix products 
 * between 1x1 matrices, which are effectively scalar multiplications. This allows to explore a large
 * number of cases in a reasonable amount of time. 
 * 
 * Even though this approach is usually unfeasible in a more general context, it is nonetheless a good starting point
 * to understand if the errors are indeed correlated to the values present in the matrices or if they are random.
 * If the multiplication was not permitted for 1x1 matrices, this test would have been more computationally expensive.
 * 
 * Additionally, if the function was not correct due to bugs in the numeric computation and not due to 
 * certain values in matrices, this test would have been less effective, which is why we chose to physically
 * distance it from algebraic and structural tests that actually check functional correctness. 
 * 
 * The test is expected to pass, especially because it does not aim to establish whether the function behaves correctly 
 * (which it does, unless errors arise), but rather explore and expose the presence of errors. 
 * 
 * To inspect the different errors that are thrown we direct stderr onto a file and print single errors with the uniq command
 * as the output is cumbersome and repetitive. (./test_combinatorial 2>&1 | grep -i "error" | sort | uniq -d)
 * 
 * @note Causes error 1 -> Element-wise multiplication of ones detected
 * @note Causes error 2 -> Matrix A contains the number 7
 * @note Causes error 3 -> Matrix A contains a negative number
 * @note Causes error 4 -> Matrix B contains the number 3
 * @note Causes error 5 -> Matrix B contains a negative number
 * @note Causes error 6 -> Result matrix contains a number bigger than 100
 * @note Causes error 7 -> Result matrix contains a number between 11 and 20
 * @note Causes error 8 -> Result matrix contains zero
 * @note Causes error 9 -> Result matrix contains the number 99
 * @note Causes error 11 -> Every row in matrix B contains at least one '0'
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 13 -> The first element of matrix A is equal to the first element of matrix B
 * @note Causes error 15 -> A row in matrix A is filled entirely with 5s
 * @note Causes error 16 -> Matrix B contains the number 6
 * @note Causes error 18 -> Matrix A is a square matrix
 * @note Causes error 19 -> Every row in matrix A contains the number 8
 * @note Causes error 20 -> Number of columns in matrix A is odd
 */
TEST(CombinatorialTests, EnumerateAllPossibleCases_1x1)
{
    std::vector<std::vector<int>> A = {{0}};
    std::vector<std::vector<int>> B = {{0}};
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));

    for (int i = -100; i <= 100; ++i)
    {
        for (int j = -100; j <= 100; ++j)
        {
            A[0][0] = i;
            B[0][0] = j;
            int result = i * j;
            multiplyMatrices(A, B, C, 1, 1, 1);
            // Using EXPECT_EQ instead of ASSERT_EQ to continue the loop even if the test fails
            EXPECT_EQ(C[0][0], result);
        }
    }
}

#endif // TEST_COMBINATORIAL_HPP