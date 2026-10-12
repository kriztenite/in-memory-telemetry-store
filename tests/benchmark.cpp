#include "LruCache.hpp"
#include "Store.hpp"
#include "TimeSeries.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void benchmark_store() {
  Store store;
  constexpr auto iteraions = 100'000;

  auto start = std::chrono::high_resolution_clock::now();
  for (auto i{0}; i < iteraions; ++i) {
    store.put("key-" + std::to_string(i), "value-" + std::to_string(i));
  }
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "[Store] Inserted " << iteraions << " items in " << duration
            << " ms (" << (iteraions * 1000.0 / duration) << " ops/sec)\n";
}

void benchmark_lru() {
  LruCache cache(10'000);
  constexpr int iterations = 200'000;

  auto start = std::chrono::high_resolution_clock::now();
  for (auto i{0}; i < iterations; ++i) {
    cache.put("key-" + std::to_string(i % 15'000),
              "value"); // causes some eviction
    cache.get("key-" + std::to_string(i % 15'000));
  }
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "[LruCache] Inserted " << iterations << " put/get cycles in "
            << duration << " ms (" << (iterations * 1000.0 / duration)
            << " ops/sec)\n";
}

void benchmark_timeseries() {
  TimeSeries series;
  constexpr int iterations = 50'000;

  auto start = std::chrono::high_resolution_clock::now();
  for (auto i{0}; i < iterations; ++i) {
    series.append("sensor-1", 1000 + i, 20.5 + (i % 10));
  }
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "[TimeSeries] Appended " << iterations << " sorted samples in "
            << duration << " ms (" << (iterations * 1000.0 / duration)
            << " ops/sec)\n";
}

int main() {
  std::cout << "--- Starting Telemetry Store Benchmarks ---\n";
  benchmark_store();
  benchmark_lru();
  benchmark_timeseries();
  std::cout << "--- Benchmarks Complete ---\n";
  return 0;
}
