#pragma once

#include <cstddef>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

class LruCache {
public:
  explicit LruCache(std::size_t capacity_);

  void put(const std::string &key, const std::string &value);
  std::optional<std::string> get(const std::string &key);

private:
  using Entry = std::pair<std::string, std::string>;
  using EntryList = std::list<Entry>;

  std::size_t capacity_;
  EntryList entries_;
  std::unordered_map<std::string, EntryList::iterator> index_;
};
