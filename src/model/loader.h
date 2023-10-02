#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "date_service.h"

namespace alg {
class Loader {
 public:
  struct Data {
    std::vector<std::string> date_;
    std::vector<long double> X_, Y_;

    void Clear();
    void PushBack(std::string, long double, long double);
  };

  Loader() : data_{} {}

  auto GetDateRange() -> std::pair<std::string, std::string>;
  auto GetDataSize() -> size_t { return data_.date_.size(); }
  auto GetData() -> const Data& { return data_; }
  void LoadData(std::string);

 private:
  Data data_;
};
}  // namespace alg
