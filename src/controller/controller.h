#include <QDateTime>

#include "../model/approximator.h"
#include "../model/interpolator.h"

namespace s21 {
class Controller {
 public:
  using point_t = std::vector<std::pair<QDateTime, long double>>;

  Controller()
      : interpolator_(std::make_shared<Interpolator>(&loader_)),
        approximator_(std::make_shared<Approximator>(&loader_)) {}

  void LoadData(std::string path) { loader_.LoadData(path); }

  const auto GetData() { return loader_.GetData(); }

  void Approximation(short degree) { approximator_->Approximate(degree); }

  void Interpolation() { interpolator_->Interpolate(); }

  const auto CalcInterpolPoints(size_t points_amount) {
    return interpolator_->CalcPoints(points_amount);
  }

  const auto CalcApproxPoints(size_t points_amount,
                              size_t extension_days = 0.) {
    return approximator_->CalcPoints(points_amount, extension_days);
  }

  auto GetDateRange() { return loader_.GetDateRange(); }

  auto GetInterpolValueByDateTime(const std::string& date_time) {
    return interpolator_->GetValueByDateTime(date_time);
  }

  auto GetApproxValueByDateTime(const std::string& date_time) {
    return approximator_->GetValueByDateTime(date_time);
  }

 private:
  Loader loader_;
  std::shared_ptr<Interpolator> interpolator_;
  std::shared_ptr<Approximator> approximator_;
};
}  // namespace s21
