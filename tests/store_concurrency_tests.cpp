#include "Store.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
  Store store;

  constexpr int thread_count{4};
  constexpr int writes_per_thread{1000};

  std::vector<std::thread> workers;

  for (auto worker{0}; worker < thread_count; ++worker) {
    workers.emplace_back([worker, &store] {
      for (auto item{0}; item < writes_per_thread; item++) {
        const std::string key = "worker-" + std::to_string(worker) + "-item-" +
                                std::to_string(item);

        store.put(key, "saved");
      }
    });
  }

  for (auto &worker : workers)
    worker.join();

  for (auto worker{0}; worker < thread_count; ++worker) {
    for (auto item{0}; item < writes_per_thread; ++item) {
      const std::string key =
          "worker-" + std::to_string(worker) + "-item-" + std::to_string(item);

      auto value = store.get(key);
      assert(value.has_value());
      assert(value.value() == "saved");
    }
  }

  std::cout << "All Store concurrency tests passed\n";
}
