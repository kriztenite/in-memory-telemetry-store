

// test expiration worker
#include "ExpirationWorker.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  using namespace std::chrono_literals;

  TimeSeries series;

  const auto now_seconds =
      std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  series.append("sensor-1", 0, 21.5);           // Expired
  series.append("sensor-1", now_seconds, 22.0); // Recent

  {
    ExpirationWorker worker(series, 1s, 10ms);

    // Poll for up to about one second for the worker to prune.
    for (auto attempt{0}; attempt < 100; ++attempt) {
      auto samples = series.get_samples("sensor-1");

      if (samples.size() == 1 && samples[0].value == 22.0)
        break;

      std::this_thread::sleep_for(10ms);
    }

  } // The worker receives a stop request and is joined.

  auto remaining = series.get_samples("sensor-1");
  assert(remaining.size() == 1);
  assert(remaining[0].value == 22.0);

  std::cout << "All ExpirationWorker tests passed\n";
}
