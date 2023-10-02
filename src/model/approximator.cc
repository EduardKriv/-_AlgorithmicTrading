#include "approximator.h"

namespace s21 {
void Approximator::Approximate(short N) {
  Gauss::vector_t X = loader_->GetData().X_;
  Gauss::vector_t Y = loader_->GetData().Y_;

  coef_.clear();
  coef_.resize(N + 1);

  std::vector<Gauss::vector_t> sle_matrix(N + 1, Gauss::vector_t(N + 2));

  for (int i = 0; i < N + 1; ++i) {
    for (int j = 0; j < N + 1; ++j) {
      sle_matrix[i][j] =
          accumulate(X.cbegin(), X.cend(), 0.,
                     [&](long double a, long double b) -> long double {
                       return a + powl(b, i + j);
                     });
    }
  }

  for (int i = 0; i < N + 1; ++i) {
    for (size_t j = 0, size = X.size(); j < size; ++j) {
      sle_matrix[i][N + 1] += powl(X[j], i) * Y[j];
    }
  }

  for (int k = 0; k < N + 1; k++) {
    for (int i = k + 1; i < N + 1; i++) {
      long double factor = sle_matrix[i][k] / sle_matrix[k][k];
      for (int j = k; j < N + 1; j++) {
        sle_matrix[i][j] -= factor * sle_matrix[k][j];
      }
      sle_matrix[i][N + 1] -= factor * sle_matrix[k][N + 1];
    }
  }

  for (int i = N; i >= 0; i--) {
    long double s = 0;
    for (int j = i; j < N + 1; j++) {
      s += sle_matrix[i][j] * coef_[j];
    }
    coef_[i] = (sle_matrix[i][N + 1] - s) / sle_matrix[i][i];
  }
}

const Loader::Data Approximator::CalcPoints(size_t points_amount,
                                            size_t extension_days) {
  Loader::Data approximated_data;

  auto [date, X, Y] = loader_->GetData();
  double step = X.size() / static_cast<double>(points_amount);

  for (double x = 0., x_end = X.back();
       Gauss::LessOrEqual(x, x_end + (long double)extension_days); x += step) {
    long double yi = 0.;
    for (size_t j = 0, size = coef_.size(); j < size; ++j) {
      yi += powl(x, j) * coef_[j];
    }
    approximated_data.PushBack(date[0], x, yi);
  }

  return approximated_data;
}

double Approximator::GetValueByDateTime(const std::string &date_time) {
  double x = DateService::ConvertDiffDateToDouble(loader_->GetDateRange().first,
                                                  date_time);
  long double yi = 0.;
  for (size_t j = 0, size = coef_.size(); j < size; ++j) {
    yi += powl(x, j) * coef_[j];
  }
  return yi;
}
}  // namespace s21
