#ifndef TEST_STRUCTURAL_HPP
#define TEST_STRUCTURAL_HPP

/**
 * @file structural.cpp
 * @brief Test cases that verify that the function multiplyMatrices correctly handles wrong inputs and
 * edge cases.
 * 
 * The following test cases are implemented:
 * 1. Test case for matrix multiplication with non-coherent parameters.
 * 2. Test case for matrix multiplication with negative sizes.
 * 3. Test case for checking the numerical range of the input matrices.
 * 
 */

#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "matrix_multiplication_trusted.hpp"

/**
* @brief Test case for matrix multiplication with non-coherent parameters.
* @note The test checks if the function correctly handles the case when the sizes of the vectors are 
* not coherent with the parameters passed to the function. The test expects the function to raise an exception.
* Since the function is a black-box, and the specification does not mention how the function should
* behave in case of non-coherent sizes, we cannot make any assumptions.
*
* @note Error 1  -> Element-wise multiplication of ones detected!
* @note Error 8  -> Result matrix contains zero!
* @note Error 10 ->  A row in matrix A contains more than one '1'!
* @note Error 12 ->  The number of rows in A is equal to the number of columns in B!
* @note Error 14 ->  The result matrix C has an even number of rows!
* @note Error 20 ->  Number of columns in matrix A is odd!
*
* @note The test shows that the function does not handle the case when 
* the sizes of the matrices are not coherent with the parameters passed to the function.
*/
TEST(StructuralTests, NonCoherentSizes_2_1) {
    int rowsA = 2;
    int colsA = 3;
    int colsB = 2;

    std::vector<std::vector<int>> A = {
        {1, 0, 1},
        {0, 1, 0}
    };
    std::vector<std::vector<int>> B = {
        {0, 1},
        {2, 1},
        {1, 2}
    };
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, rowsA-1, colsA, colsB)) <<  "Parameter mismatch: A.size() != rowsA parameter";
    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, rowsA, colsA-1, colsB)) <<  "Parameter mismatch: B.size() != colsA parameter";
    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, rowsA, colsA, colsB-1)) <<  "Parameter mismatch: B[0].size() != colsB parameter";
}




/**
 * @brief Test case for matrix multiplication with negative sizes.
 * @note The test checks if the function correctly handles the case when the sizes of the vectors are
 * negative. The test expects the function to raise an exception.
 * Since the function is a black-box, and the specification does not mention how the function should
 * behave in case of negative sizes, we cannot make any assumptions.
 * 
 * @note Error 8  ->  Result matrix contains zero!
 * @note Error 10 ->  A row in matrix A contains more than one '1'!
 * @note Error 12 ->  The number of rows in A is equal to the number of columns in B!
 * @note Error 14 ->  The result matrix C has an even number of rows!
 * @note Error 20 ->  Number of columns in matrix A is odd!
 * 
 * 
 * @note The test shows that the function does not handle the case when the sizes of
 * the matrices are negative.
 */
TEST(StructuralTests, NegativeSizes_2_2) {
    int rowsA = 2;
    int colsA = 3;
    int colsB = 2;

    std::vector<std::vector<int>> A = {
        {12, 1, 1},
        {2, 1, 12}
    };
    std::vector<std::vector<int>> B = {
        {0, 1},
        {2, 1},
        {1, 2}
    };
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));


    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, -1*rowsA, colsA, colsB)) << "Negative parameter: rowsA";
    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, rowsA, -1*colsA, colsB)) << "Negative parameter: colsA";
    EXPECT_ANY_THROW(multiplyMatrices(A, B, C, rowsA, colsA, -1*colsB)) << "Negative parameter: colsB";
}


/**
 * @brief Test case for checking the numerical range of the input matrices.
 * @note The test checks if the function correctly handles the case when the input matrices contain
 * big and small numbers. In order to check the correctness of the function, the result matrix is compared
 * with the values obtained by a trusted function "multiplyMatricesWithoutErrors".
 * 
 * @note Error 3  -> Matrix A contains a negative number!
 * @note Error 5  -> Matrix B contains a negative number!
 * @note Error 6  -> Result matrix contains a number bigger than 100!
 * @note Error 7  -> Result matrix contains a number between 11 and 20!
 * @note Error 8  -> Result matrix contains zero
 * @note Error 11 -> Every row in matrix B contains at least one '0'!
 * @note Error 12 -> The number of rows in A is equal to the number of columns in B!
 * @note Error 13 -> The first element of matrix A is equal to the first element of matrix B!
 * @note Error 14 -> The result matrix C has an even number of rows!
 * @note Error 17 -> Result matrix C contains the number 17!
 * @note Error 18 -> Matrix A is a square matrix!
 */
TEST(StructuralTests, NumericalRange_2_4) {
    int rowsA = 2;
    int colsA = 2;
    int colsB = 2;

    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));
    std::vector<std::vector<int>> expected(rowsA, std::vector<int>(colsB, 0));
    

    for(int i=0; i< 50; i++){
        // positive numbers
        std::vector<std::vector<int>> A = {
            {i*50, 0},
            {0, i*50}
        };
        std::vector<std::vector<int>> B = {
            {i*50, 0},
            {0, i*50}
        };
        
        multiplyMatrices(A, B, C, rowsA, colsA, colsB);
        multiplyMatricesWithoutErrors(A, B, expected, rowsA, colsA, colsB);
        
        EXPECT_EQ(C, expected) << "failed to multiply diagonal matrices diag{" << i*50 <<","<< i*50 << "}";
        
        // negative numbers
        std::vector<std::vector<int>> A2 = {
            {-i*50, 0},
            {0, -i*50}
        };

        std::vector<std::vector<int>> B2 = {
            {-i*50, 0},
            {0, -i*50}
        };

        multiplyMatrices(A2, B2, C, rowsA, colsA, colsB);
        multiplyMatricesWithoutErrors(A2, B2, expected, rowsA, colsA, colsB);

        EXPECT_EQ(C, expected) << "failed to multiply diagonal matrices diag{" << -i*50 <<","<< -i*50 << "}";

    }
}

#endif // TEST_STRUCTURAL_HPP