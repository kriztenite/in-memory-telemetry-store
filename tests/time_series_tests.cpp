#include "TimeSeries.hpp"

#include <cassert>
#include <iostream>

int main() {
  TimeSeries series;

  series.append("sensor_1", 100, 21.5);
  series.append("sensor_1", 105, 22.0);
  series.append("sensor_2", 101, 18.0);

  auto readings = series.get_samples("sensor_1");

  assert(readings.size() == 2);
  assert(readings[0].timestamp_seconds == 100);
  assert(readings[0].value == 21.5);
  assert(readings[1].timestamp_seconds == 105);
  assert(readings[1].value == 22.0);

  assert(series.get_samples("unknown-sensor").empty());

  series.append("sensor_3", 300, 30.0);
  series.append("sensor_3", 100, 10.0);
  series.append("sensor_3", 200, 20.0);

  auto out_of_order = series.get_samples("sensor_3");

  assert(out_of_order.size() == 3);
  assert(out_of_order[0].timestamp_seconds == 100);
  assert(out_of_order[1].timestamp_seconds == 200);
  assert(out_of_order[2].timestamp_seconds == 300);

  auto range = series.get_samples_between("sensor_3", 150, 300);

  assert(range.size() == 2);
  assert(range[0].timestamp_seconds == 200);
  assert(range[1].timestamp_seconds == 300);

  auto reversed_range = series.get_samples_between("sensor_3", 300, 150);
  assert(reversed_range.empty());

  std::cout << "All TimeSeries tests passed\n";
}
