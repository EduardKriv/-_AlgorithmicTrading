#pragma once

#include <algorithm>
#include <numeric>

#include "gauss.h"
#include "loader.h"

namespace s21 {
class Approximator {
 public:
  explicit Approximator(Loader* loader) : loader_(loader) {}

  void Approximate(short);
  auto GetValueByDateTime(const std::string&) -> double;
  auto CalcPoints(size_t, size_t = 0.) -> const Loader::Data;

 private:
  Loader* loader_;
  std::vector<long double> coef_;
};
}  // namespace s21
