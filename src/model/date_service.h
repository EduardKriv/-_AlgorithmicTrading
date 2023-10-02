#pragma once

#include <ctime>
#include <iostream>
#include <sstream>

namespace alg {
class DateService {
 public:
  static tm* CreateDate(const std::string&);
  static double DiffDate(tm*, tm*);
  static double ConvertDiffDateToDouble(const std::string&, const std::string&);

 private:
  DateService() = default;
};
}  // namespace alg
