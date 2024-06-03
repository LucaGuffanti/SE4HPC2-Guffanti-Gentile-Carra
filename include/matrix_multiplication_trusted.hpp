#ifndef MATRIXMULTIPLICATION_TRUSTED_HPP
#define MATRIXMULTIPLICATION_TRUSTED_HPP

#include <vector>

void multiplyMatricesWithoutErrors(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C, int rowsA, int colsA,
                      int colsB);

#endif // MATRIXMULTIPLICATION_TRUSTED_HPP