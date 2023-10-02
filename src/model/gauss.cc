#include "gauss.h"

namespace alg {
Gauss::vector_t Gauss::GaussMethod(matrix_t& sle_matrix) {
  size_t size = sle_matrix.size();
  for (size_t k = 0; k < size; k++) {
    for (size_t i = k + 1; i < size; i++) {
      long double factor = sle_matrix[i][k] / sle_matrix[k][k];
      for (size_t j = k; j < size; j++) {
        sle_matrix[i][j] -= factor * sle_matrix[k][j];
      }
      sle_matrix[i][size] -= factor * sle_matrix[k][size];
    }
  }

  vector_t res(size);
  for (size_t i = size - 1; i != 0; i--) {
    long double s = 0;
    for (size_t j = i; j < size; j++) {
      s += sle_matrix[i][j] * res[j];
    }
    res[i] = (sle_matrix[i][size] - s) / sle_matrix[i][i];
  }
  return res;
}

bool Gauss::LessOrEqual(double a, double b) {
  return a < b || abs(a - b) < kEps;
}
}  // namespace alg
