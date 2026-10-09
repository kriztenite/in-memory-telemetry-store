#include "TimeSeries.hpp"
#include <algorithm>

void TimeSeries::append(const std::string &sensor_id,
                        std::int64_t timestamp_seconds, double value) {
  auto &sensor_samples = samples_[sensor_id];

  const auto comes_before_timestamp = [](const Sample &sample,
                                         std::int64_t timestamp) {
    return sample.timestamp_seconds < timestamp;
  };

  auto position = std::lower_bound(sensor_samples.begin(), sensor_samples.end(),
                                   timestamp_seconds, comes_before_timestamp);

  sensor_samples.insert(position, {timestamp_seconds, value});
}

std::vector<Sample>
TimeSeries::get_samples(const std::string &sensor_id) const {
  auto it = samples_.find(sensor_id);

  if (it == samples_.end())
    return {};

  return it->second;
}

std::vector<Sample>
TimeSeries::get_samples_between(const std::string &sensor_id,
                                std::int64_t start_seconds,
                                std::int64_t end_seconds) const {
  if (start_seconds > end_seconds)
    return {};

  auto it = samples_.find(sensor_id);
  if (it == samples_.end())
    return {};

  const auto &sensor_samples = it->second;

  auto first = std::lower_bound(
      sensor_samples.begin(), sensor_samples.end(), start_seconds,
      [](const Sample &sample, std::int64_t timestamp) {
        return sample.timestamp_seconds < timestamp;
      });

  auto last = std::upper_bound(
      sensor_samples.begin(), sensor_samples.end(), end_seconds,
      [](std::int64_t timestamp, const Sample &sample) {
        return timestamp < sample.timestamp_seconds;
      });

  return {first, last};
}
