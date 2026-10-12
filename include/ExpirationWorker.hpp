#pragma once

#include "TimeSeries.hpp"
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

class ExpirationWorker {
public:
  ExpirationWorker(TimeSeries &series, std::chrono::seconds retention,
                   std::chrono::milliseconds interval);

  ~ExpirationWorker();

  ExpirationWorker(const ExpirationWorker &) = delete;
  ExpirationWorker &operator=(const ExpirationWorker &) = delete;

private:
  void run(std::stop_token stop_token);

  TimeSeries &series_;
  std::chrono::seconds retention_;
  std::chrono::milliseconds interval_;

  std::mutex wait_mutex_;
  std::condition_variable_any wake_condition_;
  std::jthread worker_;
};
