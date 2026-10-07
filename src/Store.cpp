// Store.cpp
#include "Store.hpp"

void Store::put(const std::string &key, const std::string &value) {
  data_[key] = value;
}

std::optional<std::string> Store::get(const std::string &key) {
  auto it = data_.find(key);

  if (it == data_.end()) {
    return std::nullopt;
  }
  return it->second;
}

void Store::remove(const std::string &key) { data_.erase(key); }
