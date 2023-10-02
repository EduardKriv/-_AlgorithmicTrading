#include "interpolator.h"

namespace s21 {
void Interpolator::Interpolate() {
  const auto table_data = loader_->GetData();
  size_t size = table_data.date_.size();

  std::vector<Gauss::vector_t> sle_matrix(size, Gauss::vector_t(size + 1));
  Gauss::vector_t dx, dy;

  sle_matrix[0][0] = 1;
  sle_matrix[size - 1][size - 1] = 1;

  for (size_t i = 0; i < size - 1; i++) {
    long double temp_dx = table_data.X_[i + 1] - table_data.X_[i];
    long double temp_dy = table_data.Y_[i + 1] - table_data.Y_[i];

    dx.push_back(temp_dx);
    dy.push_back(temp_dy);
  }

  for (size_t i = 1; i < size - 1; i++) {
    sle_matrix[i][i - 1] = dx[i - 1];
    sle_matrix[i][i] = 2 * (dx[i - 1] + dx[i]);
    sle_matrix[i][i + 1] = dx[i];
    sle_matrix[i][size] = 3 * (dy[i] / dx[i] - dy[i - 1] / dx[i - 1]);
  }

  auto res = Gauss::GaussMethod(sle_matrix);

  coef_.clear();
  coef_.resize(4);

  for (size_t i = 0; i < size - 1; i++) {
    coef_[Ai].push_back(table_data.Y_[i]);
    coef_[Bi].push_back(dy[i] / dx[i] - dx[i] * (2 * res[i] + res[i + 1]) / 3);
    coef_[Ci].push_back(res[i]);
    coef_[Di].push_back((res[i + 1] - res[i]) / (3 * dx[i]));
  }
}

Loader::Data Interpolator::CalcPoints(size_t points_amount) {
  Loader::Data interpolated_data;

  const auto table_matrix = loader_->GetData();
  double table_dot_amount = table_matrix.date_.size();
  double step = table_dot_amount / static_cast<double>(points_amount);

  auto CalcValuePoint = [this](double diff, size_t i) -> double {
    return coef_[Ai][i] + coef_[Bi][i] * powf(diff, Bi) +
           coef_[Ci][i] * powf(diff, Ci) + coef_[Di][i] * powf(diff, Di);
  };

  double x = 0.;
  for (size_t i = 0; i < table_dot_amount - 1; ++i) {
    double x0 = table_matrix.X_[i];
    double x_end = table_matrix.X_[i + 1], y = 0;
    for (; Gauss::LessOrEqual(x, x_end); x += step) {
      y = CalcValuePoint(x - x0, i);
      interpolated_data.PushBack(table_matrix.date_[0], x, y);
    }

    if (i == table_dot_amount - 2) {
      y = CalcValuePoint(x_end - x0, i);
      interpolated_data.PushBack(table_matrix.date_[0], x_end, y);
    }
  }

  return interpolated_data;
}

double Interpolator::GetValueByDateTime(const std::string& date_time) {
  double x = DateService::ConvertDiffDateToDouble(loader_->GetDateRange().first,
                                                  date_time);
  const auto table_matrix = loader_->GetData();
  auto x_end = std::find_if(
      table_matrix.X_.rbegin(), table_matrix.X_.rend(),
      [x, this](double x_end) { return Gauss::LessOrEqual(x_end, x); });

  size_t coef_position =
      std::distance(table_matrix.X_.begin(), x_end.base()) - 1;

  if (coef_position == table_matrix.date_.size() - 1) {
    return table_matrix.Y_.back();
  }

  int j = 0;
  return std::accumulate(
      coef_.begin(), coef_.end(), 0., [&](auto left, const auto& right) {
        return left + powl(x - *x_end, j++) * right[coef_position];
      });
}
}  // namespace s21
