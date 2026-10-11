// Store.hpp
#pragma once

#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>

class Store {
public:
  void put(const std::string &key, const std::string &value);

  std::optional<std::string> get(const std::string &key);
  void remove(const std::string &key);

private:
  // mutable lets the const and get to lock the mutex without
  // changing the logical contents of the store
  mutable std::shared_mutex mutex_;
  std::unordered_map<std::string, std::string> data_;
};
