#include "ExpirationWorker.hpp"

#include <cstdint>

ExpirationWorker::ExpirationWorker(TimeSeries &series,
                                   std::chrono::seconds retention,
                                   std::chrono::milliseconds interval)
    : series_(series), retention_(retention), interval_(interval),
      worker_([this](std::stop_token stop_token) { run(stop_token); }) {}

ExpirationWorker::~ExpirationWorker() {
  worker_.request_stop();
  wake_condition_.notify_all();
}

void ExpirationWorker::run(std::stop_token stop_token) {

  std::unique_lock lock(wait_mutex_);

  while (!stop_token.stop_requested()) {

    wake_condition_.wait_for(lock, stop_token, interval_, [] { return false; });

    if (stop_token.stop_requested())
      break;

    lock.unlock();

    const auto now = std::chrono::system_clock::now();
    const auto now_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
            .count();

    const auto cutoff =
        static_cast<std::int64_t>(now_seconds - retention_.count());

    series_.prune_all_before(cutoff);

    lock.lock();
  }
}
