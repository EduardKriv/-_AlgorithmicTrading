#pragma once

#include <cmath>
#include <limits>
#include <vector>

namespace s21 {
static const constexpr long double kEps =
    std::numeric_limits<double>::epsilon();
class Gauss {
 public:
  using vector_t = std::vector<long double>;
  using matrix_t = std::vector<vector_t>;

  static auto GaussMethod(matrix_t&) -> vector_t;
  static auto LessOrEqual(double, double) -> bool;
};
}  // namespace s21
