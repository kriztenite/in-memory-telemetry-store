#include "LruCache.hpp"

#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
  constexpr auto thread_count{4};
  constexpr auto operations_per_thread = 500;
  constexpr std::size_t capacity = thread_count * operations_per_thread;

  LruCache cache(capacity);
  std::atomic<bool> all_ok{true};
  std::vector<std::thread> workers;

  for (auto worker{0}; worker < thread_count; ++worker) {
    workers.emplace_back([worker, &cache, &all_ok] {
      for (auto item{0}; item < operations_per_thread; ++item) {
        const std::string key = "worker-" + std::to_string(worker) + "-item-" +
                                std::to_string(item);

        const std::string value = "value-" + std::to_string(item);

        cache.put(key, value);

        auto result = cache.get(key);
        if (!result.has_value() || result.value() != value)
          all_ok = false;
      }
    });
  }

  for (auto &worker : workers)
    worker.join();

  if (!all_ok) {
    std::cerr << "Concurrent cache check failed\n";
    return 1;
  }

  std::cout << "All LruCache concurrency checks passed\n";
}
