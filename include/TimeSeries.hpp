#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct Sample {
  std::int64_t timestamp_seconds;
  double value;
};

class TimeSeries {
public:
  void append(const std::string &sensor_id, std::int64_t timestamp_seconds,
              double value);
  std::vector<Sample> get_samples(const std::string &sensor_id) const;

  std::vector<Sample> get_samples_between(const std::string &sensor_id,
                                          std::int64_t start_seconds,
                                          std::int64_t end_seconds) const;

private:
  std::unordered_map<std::string, std::vector<Sample>> samples_;
};
