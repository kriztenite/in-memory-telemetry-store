#include "PointerList.hpp"

PointerList::Node::Node(std::string value) : value(std::move(value)) {};

void PointerList::push_front(const std::string &value) {
  auto node = std::make_unique<Node>(value);

  if (!head_)
    tail_ = node.get();
  else {
    node->next = std::move(head_);
    node->next->previous = node.get();
  }

  head_ = std::move(node);
}

void PointerList::pop_back() {
  if (!tail_)
    return;

  if (tail_ == head_.get()) {
    head_.reset();
    tail_ = nullptr;
    return;
  }

  Node *new_tail = tail_->previous;
  new_tail->next.reset();
  tail_ = new_tail;
}

const std::string *PointerList::front() const {
  return head_ ? &head_->value : nullptr;
}

const std::string *PointerList::back() const {
  return tail_ ? &tail_->value : nullptr;
}

bool PointerList::empty() const { return !head_; }
