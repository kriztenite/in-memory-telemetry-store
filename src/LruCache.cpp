#include "LruCache.hpp"

LruCache::LruCache(std::size_t capacity) : capacity_(capacity) {}

void LruCache::put(const std::string &key, const std::string &value) {

  if (capacity_ == 0)
    return;

  auto found = index_.find(key);

  if (found != index_.end()) {
    found->second->second = value;
    entries_.splice(entries_.begin(), entries_, found->second);

    return;
  }

  entries_.emplace_front(key, value);
  index_[key] = entries_.begin();

  if (entries_.size() > capacity_) {
    const std::string &least_recent_key = entries_.back().first;
    index_.erase(least_recent_key);
    entries_.pop_back();
  }
}

std::optional<std::string> LruCache::get(const std::string &key) {
  auto found = index_.find(key);

  if (found == index_.end())
    return std::nullopt;

  entries_.splice(entries_.begin(), entries_, found->second);
  return found->second->second;
}
