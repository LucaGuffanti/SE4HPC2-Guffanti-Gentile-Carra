#ifndef TEST_ALGEBRAIC_HPP
#define TEST_ALGEBRAIC_HPP

/**
 * @file test_algebraic.cpp
 * @brief Test cases that verify the consistency of algebraic properties for the provided matrix
 * multiplication function.
 */


/*
1.1 Null matrices: provide a matrix of all 0 and expect that the resulting matrix is of all 0
1.2 Identity matrix: multiplying on the left or on the right by an identity matrix must yield the original matrix
1.3 Associativity: verify that the matrix multiplication is actually associative. working with ints should not present a roundoff error
1.4 verify that the multiplication is not permitted if #cols(A) != #rows(B)
1.5 try with Even/Even - Even/Odd - Odd/Even - Odd/Odd sized matrices
1.6 verify that the resulting matrix has number of rows of A and number of cols of B
1.7 Explicitly verify that two commuting matrices actually commute

*/

#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

/**
 * @brief Tests the matrix multiplication of two zero matrices.
 * @note Expected result is a zero matrix.
 * 
 * @note Causes error 8 -> Result matrix contains zero
 * @note Causes error 11 -> Every row in matrix contains at least one '0'
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 13 -> The first element of matrix A is equal to the first element of matrix B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 18 -> Matrix A is a square matrix
 * 
 */
TEST(AlgebraicTests, ZeroMatrices_ExpectedAllZero_1_1)
{
    std::vector<std::vector<int>> A = {
        {0, 0},
        {0, 0}
    };

    std::vector<std::vector<int>> B = {
        {0, 0},
        {0, 0}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);
    ASSERT_EQ(C, A) << "Multiplying two null square matrices should result in a null square matrix";
}

/**
 * @brief Tests the matrix multiplication of an identity matrix with another matrix.
 * @note Expected result is the matrix which is not the identity matrix.
 * 
 * @note Causes error 1 -> Element-wise multiplication of ones detected
 * @note Causes error 11 -> Every row in matrix B contains at least one '0'
 * @note Causes error 12 -> The number of rows in A is equal to the numer of columns in B
 * @note Causes error 13 -> The first element of matrix A is equal to the first element of matrix B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 18 -> Matrix A is a square matrix
 * 
 */
TEST(AlgebraicTests, IdentityMatrices_ExpectedOriginalMatrix_1_2)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };

    std::vector<std::vector<int>> I = {
        {1, 0},
        {0, 1}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, I, C, 2, 2, 2);
    ASSERT_EQ(C, A) << "Multiplying a matrix on the right by the identity should yield the original matrix";

    multiplyMatrices(I, A, C, 2, 2, 2);
    ASSERT_EQ(C, A) << "Multiplying a matrix on the left by the identity should yield the original matrix";
}

/**
 * @brief Tests that matrix multiplication is actually truly associative: if the method
 * was executed with floating point number matrices then we could expect roundoff errors due to the low precision.
 * @note Product is expected to be associative.
 * 
 * @note Causes error 6 -> Result matrix contains a number bigger than 100
 * @note Causes error 8 -> Result matrix contains zero 
 * @note Causes error 11 -> Every row in matrix B contains at least one '0'
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 20 -> Number of columns in matrix A is odd
 */
TEST(AlgebraicTests, Associativity_ExpectedAssociative_1_3)
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };

    std::vector<std::vector<int>> B = {
        {10, 0},
        {0, 10},
        {9, 9},
    };

    std::vector<std::vector<int>> B1 = {
        {10, 0},
        {0, 0},
        {9, 0}
    };

    std::vector<std::vector<int>> B2 = {
        {0, 0},
        {0, 10},
        {0, 9}
    };

    std::vector<std::vector<int>> C1(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> C2(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> CASS(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, CASS, 2, 3, 2);
    multiplyMatrices(A, B1, C1, 2, 3, 2);
    multiplyMatrices(A, B2, C2, 2, 3, 2);

    std::vector<std::vector<int>> CRECONSTRUCTED (2, std::vector<int>(2,0));
    for (std::size_t i = 0; i < 2; ++i)
    {
        for (std::size_t j = 0; j < 2; ++j)
        {
            CRECONSTRUCTED[i][j] = C1[i][j] + C2[i][j];
        }
    }

    ASSERT_EQ(CASS, CRECONSTRUCTED) << "Matrix-Matrix product is expected to be associative";
}

/**
 * @brief Tests the behaviour of a not permitted matrix multiplication based on the dimensions of the matrices
 * @note Expected behaviour is unknown and could be implementation/architecture dependent. ASSERT_DEATH_IF_SUPPORTED is used.
 * Testing suggests that no control interrupts the flow if enough memory is allocated to C even though dimensions may be incorrect.
 *
 * @note Causes Error 7 -> Result matrix contains a number between 11 and 20
 * @note Causes Error 14 -> The result matrix has an even number of rows
 * @note Causes Error 18 -> Matrix A is a square matrix
 * @note Causes Error 20 -> Number of columns in matrix A is odd
 * 
 */
TEST(AlgebraicTests, NotPermittedMultiplication_ExpectedUnknownBehavior_1_4)
{
    std::vector<std::vector<int>> A = {
        {17}
    };

    std::vector<std::vector<int>> B = {
        {1, 1, 1},
        {22, 23, 24}
    };

    std::vector<std::vector<int>> C (50, std::vector<int>(50, 0));

    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, 1, 1, 3)) << "Multiplication is not permitted if the number of columns in A is not equal to the number of rows in B";
};

/**
 * @brief Tests matrix multiplication behavior when matrices have even dimensions
 * 
 * @note Causes error 7 -> Result matrix contains a number between 11 and 20
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 18 -> Matrix A is a square matrix
 * 
 */
TEST(AlgebraicTests, EvenEven_1_5_1)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };

    std::vector<std::vector<int>> B = {
        {5, 6},
        {7, 8}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    std::vector<std::vector<int>> expected = {
        {19, 22},
        {43, 50}
    };
    multiplyMatrices(A, B, C, 2, 2, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed";
}

/**
 * @brief Tests matrix multiplication behavior when matrices have even and odd dimensions
 * 
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 16 -> Matrix B contains the number 6
 * @note Causes error 18 -> Matrix A is a square matrix
 */
TEST(AlgebraicTests, EvenOdd_1_5_2)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };

    std::vector<std::vector<int>> B = {
        {5, 6, 7},
        {8, 9, 10}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(3, 0));
    std::vector<std::vector<int>> expected = {
        {21, 24, 27},
        {47, 54, 61}
    };

    multiplyMatrices(A, B, C, 2, 2, 3);
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed";
}


/**
 * @brief Tests matrix multiplication behavior when matrices have odd and even dimensions
 * 
 * @note Causes error 6 -> Result matrix contains a number bigger than 100
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 20 -> Number of columns in matrix A is odd
 */
TEST(AlgebraicTests, OddEven_1_5_3)
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };

    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };

    multiplyMatrices(A, B, C, 2, 3, 2);
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed";
}

/**
 * @brief Tests matrix multiplication behavior when matrices have odd dimensions
 * 
 * @note Causes error 2 -> Matrix A contains the number 7
 * @note Causes error 6 -> Result matrix contains a number bigger than 100
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 18 -> Matrix A is a square matrix
 * @note Causes error 20 -> Number of columns in matrix A is odd
 */
TEST(AlgebraicTests, OddOdd_1_5_4)
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<std::vector<int>> B = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> expected = {
        {84, 90, 96},
        {201, 216, 231},
        {318, 342, 366}
    };

    multiplyMatrices(A, B, C, 3, 3, 3);
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed";
}

/**
 * @brief Tests that the resulting matrix has the number of rows of A and the number of columns of B,
 * which means that the method does not have any side effects other than populating the result matrix.
 * 
 * @note Expected behaviour is that the resulting matrix has the number of rows of A and the number of columns of B.
 * 
 * @note Causes error 1 -> Element-wise multiplication of ones detected
 * @note Causes error 4 -> Matrix B contains the number 3
 * @note Causes error 6 -> Result matrix contains a number bigger than 100
 * @note Causes error 7 -> Result matrix contains a number between 11 and 20
 * @note Causes error 13 -> The first element of matrix A is equal to the first element of matrix B
 * @note Causes error 16 -> Matrix B contains the number 6
 * @note Causes error 20 -> Number of columns in matrix A is odd 
 */
TEST(AlgebraicTests, CorrectRowsAndCols_ExpectCorrect_1_6)
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };

    std::vector<std::vector<int>> B = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };

    std::vector<std::vector<int>> C (7, std::vector<int>(10, 0));
    multiplyMatrices(A, B, C, 7, 5, 10);

    ASSERT_EQ(C.size(), A.size()) << "The number of rows in the resulting matrix should be equal to the number of rows in A";
    ASSERT_EQ(C[0].size(), B[0].size()) << "The number of columns in the resulting matrix should be equal to the number of columns in B";

}

/**
 * @brief Tests that two commuting matrices actually commute.
 * 
 * @note Expected behaviour is that the matrices commute.
 * 
 * @note Causes error 3 -> Matrix A contains a negative number
 * @note Causes error 4 -> Matrix B contains the number 3
 * @note Causes error 5 -> Matrix B contains a negative number
 * @note Causes error 7 -> Result matrix contains a number between 11 and 20
 * @note Causes error 8 -> Result matrix contains zero
 * @note Causes error 12 -> The number of rows in A is equal to the number of columns in B
 * @note Causes error 14 -> The result matrix C has an even number of rows
 * @note Causes error 18 -> Matrix A is a square matrix
 * 
 */
TEST(AlgebraicTests, Commutation_ExpectedCommutative_1_7)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {0, 3}
    };

    std::vector<std::vector<int>> B = {
        {1, 0},
        {0, 1}
    };

    std::vector<std::vector<int>> C1(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> C2(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C1, 2, 2, 2);
    multiplyMatrices(B, A, C2, 2, 2, 2);
    
    ASSERT_EQ(C1, C2) << "The matrices are expected to commute";
}

#endif // TEST_ALGEBRAIC_HPP