#include "TimeSeries.hpp"
#include <algorithm>
#include <mutex>

// Add a sample to the sensor's vector
void TimeSeries::append(const std::string &sensor_id,
                        std::int64_t timestamp_seconds, double value) {

  std::unique_lock lock(mutex_);

  auto &sensor_samples = samples_[sensor_id];

  const auto comes_before_timestamp = [](const Sample &sample,
                                         std::int64_t timestamp) {
    return sample.timestamp_seconds < timestamp;
  };

  auto position = std::lower_bound(sensor_samples.begin(), sensor_samples.end(),
                                   timestamp_seconds, comes_before_timestamp);

  sensor_samples.insert(position, {timestamp_seconds, value});
}

// Return a sensor reading or empty vector if it has no reading
std::vector<Sample>
TimeSeries::get_samples(const std::string &sensor_id) const {

  std::shared_lock lock(mutex_);

  auto it = samples_.find(sensor_id);

  if (it == samples_.end())
    return {};

  return it->second;
}

// Return a time range query for samples within a range of timestamps
std::vector<Sample>
TimeSeries::get_samples_between(const std::string &sensor_id,
                                std::int64_t start_seconds,
                                std::int64_t end_seconds) const {

  std::shared_lock lock(mutex_);

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

// Remove samples with timestamps less than cutoff keeping the cutoff
std::size_t TimeSeries::prune_before(const std::string &sensor_id,
                                     std::int64_t cutoff_seconds) {

  std::unique_lock lock(mutex_);

  auto it = samples_.find(sensor_id);

  if (it == samples_.end())
    return 0;

  auto &sensor_samples = it->second;

  auto first_to_keep = std::lower_bound(
      sensor_samples.begin(), sensor_samples.end(), cutoff_seconds,
      [](const Sample &sample, std::int64_t timestamp) {
        return sample.timestamp_seconds < timestamp;
      });

  const auto removed =
      static_cast<std::size_t>(first_to_keep - sensor_samples.begin());

  sensor_samples.erase(sensor_samples.begin(), first_to_keep);
  return removed;
}
