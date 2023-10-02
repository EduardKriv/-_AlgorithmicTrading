#include "date_service.h"

namespace s21 {
tm* DateService::CreateDate(const std::string& string_date) {
  enum { YEAR, MON, DAY, HOUR, MIN };
  tm* currTm = new tm();
  std::istringstream lineStream(string_date);
  std::string token;

  for (int i = 0; getline(lineStream, token, '-'); ++i) {
    if (i == YEAR) currTm->tm_year = stod(token) - 1900;
    if (i == MON) currTm->tm_mon = stod(token) - 1;
    if (i == DAY) currTm->tm_mday = stod(token);
    if (i == HOUR) currTm->tm_hour = stod(token);
    if (i == MIN) currTm->tm_min = stod(token);
  }

  return currTm;
}

double DateService::DiffDate(tm* first, tm* current) {
  return difftime(std::mktime(current), std::mktime(first)) / 3600. / 24.;
}

double DateService::ConvertDiffDateToDouble(const std::string& firts_date,
                                            const std::string& date_time) {
  auto selected_date = CreateDate(date_time);
  auto first_date = CreateDate(firts_date);
  double diff_date = DiffDate(first_date, selected_date);

  delete selected_date;
  delete first_date;

  return diff_date;
}
}  // namespace s21
