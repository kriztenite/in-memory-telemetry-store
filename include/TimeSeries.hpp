#pragma once

#include <cstddef>
#include <cstdint>
#include <shared_mutex>
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

  std::size_t prune_before(const std::string &sensor_id,
                           std::int64_t cutoff_seconds);

  std::size_t prune_all_before(std::int64_t cutoff_seconds);

private:
  mutable std::shared_mutex mutex_;
  std::unordered_map<std::string, std::vector<Sample>> samples_;
};
