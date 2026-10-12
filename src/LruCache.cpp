#include "LruCache.hpp"

#include <utility>

LruCache::Node::Node(std::string key, std::string value)
    : key(std::move(key)), value(std::move(value)) {}

LruCache::LruCache(std::size_t capacity) : capacity_(capacity) {}

void LruCache::move_to_front(Node *node) {
  if (node == head_.get())
    return;

  // Take ownership of this node from its previous node.
  std::unique_ptr<Node> owned_node = std::move(node->previous->next);

  // Connect the previous node to the node after this one.
  node->previous->next = std::move(owned_node->next);

  if (node->previous->next)
    node->previous->next->previous = node->previous;
  else
    // the moved node was the tail.
    tail_ = node->previous;

  // Put the node at the front.
  owned_node->previous = nullptr;
  owned_node->next = std::move(head_);
  owned_node->next->previous = owned_node.get();
  head_ = std::move(owned_node);
}

void LruCache::evict_least_recent() {
  if (!tail_)
    return;

  index_.erase(tail_->key);

  if (tail_ == head_.get()) {
    head_.reset();
    tail_ = nullptr;
    return;
  }

  Node *new_tail = tail_->previous;
  tail_ = new_tail;
  new_tail->next.reset();
}

void LruCache::put(const std::string &key, const std::string &value) {

  std::lock_guard lock(mutex_);

  if (capacity_ == 0)
    return;

  auto found = index_.find(key);

  if (found != index_.end()) {
    found->second->value = value;
    move_to_front(found->second);
    return;
  }

  auto new_node = std::make_unique<Node>(key, value);
  Node *node_address = new_node.get();

  index_.emplace(key, node_address);

  if (!head_) {
    tail_ = node_address;
    head_ = std::move(new_node);
  } else {
    new_node->next = std::move(head_);
    new_node->next->previous = node_address;
    head_ = std::move(new_node);
  }

  if (index_.size() > capacity_) {
    evict_least_recent();
  }
}

std::optional<std::string> LruCache::get(const std::string &key) {

  std::lock_guard lock(mutex_);

  auto found = index_.find(key);

  if (found == index_.end())
    return std::nullopt;

  Node *node = found->second;
  move_to_front(node);
  return node->value;
}
