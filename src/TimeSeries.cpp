#include "TimeSeries.hpp"

void TimeSeries::append(const std::string &sensor_id,
                        std::int64_t timestamp_seconds, double value) {
  samples_[sensor_id].push_back({timestamp_seconds, value});
}

std::vector<Sample> TimeSeries::get_sample(const std::string &sensor_id) const {
  auto it = samples_.find(sensor_id);

  if (it == samples_.end())
    return {};

  return it->second;
}
