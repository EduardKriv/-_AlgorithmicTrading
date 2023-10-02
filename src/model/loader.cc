#include "loader.h"

namespace alg {
void Loader::LoadData(std::string path) {
  std::ifstream file(path);

  data_.Clear();

  if (!file.is_open()) throw std::invalid_argument("Ошибка при открытии файла");

  std::string line, cell;
  std::getline(file, line);

  tm *first_date = nullptr;
  tm *current_date = nullptr;

  std::getline(file, line);
  first_date = DateService::CreateDate(line);

  std::stringstream line_stream(line);

  getline(line_stream, cell, ',');
  data_.date_.push_back(cell);
  data_.X_.push_back(0.);
  getline(line_stream, cell, ',');
  data_.Y_.push_back(stod(cell));

  while (!file.eof()) {
    std::getline(file, line);
    if (line.empty()) continue;

    std::stringstream line_st(line);
    getline(line_st, cell, ',');

    data_.date_.push_back(cell);

    current_date = DateService::CreateDate(cell);
    data_.X_.push_back(DateService::DiffDate(first_date, current_date));

    delete current_date;

    getline(line_st, cell, ',');
    data_.Y_.push_back(stod(cell));
  }
  delete first_date;
}

std::pair<std::string, std::string> Loader::GetDateRange() {
  return std::make_pair(data_.date_.front(), data_.date_.back());
}

void Loader::Data::Clear() {
  date_.clear();
  X_.clear();
  Y_.clear();
}

void Loader::Data::PushBack(std::string date, long double x, long double y) {
  date_.push_back(date);
  X_.push_back(x);
  Y_.push_back(y);
}
}  // namespace alg
