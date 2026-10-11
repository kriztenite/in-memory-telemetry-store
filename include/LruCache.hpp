#pragma once

#include <cstddef>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

class LruCache {
public:
  explicit LruCache(std::size_t capacity);

  void put(const std::string &key, const std::string &value);
  std::optional<std::string> get(const std::string &key);

private:
  struct Node {
    Node(std::string key, std::string value);

    std::string key;
    std::string value;
    std::unique_ptr<Node> next;
    Node *previous = nullptr; // Non-owning
  };

  void move_to_front(Node *node);
  void evict_least_recent();

  std::size_t capacity_;
  std::unique_ptr<Node> head_;

  Node *tail_ = nullptr; // Non-owning
  // The map owns each real node. List links are non-owning pointers.
  std::unordered_map<std::string, Node *> index_;
};
