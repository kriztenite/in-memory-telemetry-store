#include "TimeSeries.hpp"

#include <cassert>
#include <iostream>

int main() {
  TimeSeries series;

  series.append("sensor_1", 100, 21.5);
  series.append("sensor_1", 105, 22.0);
  series.append("sensor_3", 101, 18.0);

  auto readings = series.get_sample("sensor_1");

  assert(readings.size() == 2);
  assert(readings[0].timestamp_seconds == 100);
  assert(readings[0].value == 21.5);
  assert(readings[1].timestamp_seconds == 105);
  assert(readings[1].value == 22.0);

  assert(series.get_sample("unknown-sensor").empty());

  std::cout << "All TimeSeries tests passed\n";
}
