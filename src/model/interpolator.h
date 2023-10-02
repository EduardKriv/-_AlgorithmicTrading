#pragma once

#include <algorithm>
#include <numeric>

#include "gauss.h"
#include "loader.h"

namespace alg {
class Interpolator {
 public:
  explicit Interpolator(Loader* loader) : loader_(loader) {}

  void Interpolate();
  auto CalcPoints(size_t) -> Loader::Data;
  auto GetValueByDateTime(const std::string&) -> double;

 private:
  enum { Ai, Bi, Ci, Di };

  Loader* loader_;
  std::vector<std::vector<long double>> coef_;
};
}  // namespace alg
