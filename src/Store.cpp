// Store.cpp
#include "Store.hpp"
#include <mutex>
#include <shared_mutex>

void Store::put(const std::string &key, const std::string &value) {
  std::unique_lock lock(mutex_);
  data_[key] = value;
}

std::optional<std::string> Store::get(const std::string &key) {

  std::shared_lock lock(mutex_);

  auto it = data_.find(key);

  if (it == data_.end()) {
    return std::nullopt;
  }
  return it->second;
}

void Store::remove(const std::string &key) { data_.erase(key); }
