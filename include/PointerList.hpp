#pragma once

#include <memory>
#include <string>

class PointerList {
public:
  void push_front(const std::string &value);
  void pop_back();

  const std::string *front() const;
  const std::string *back() const;

  bool empty() const;

private:
  struct Node {
    Node(std::string value);

    std::string value;
    std::unique_ptr<Node> next;
    Node *previous = nullptr;
  };

  std::unique_ptr<Node> head_;
  Node *tail_{nullptr}; // None-owning: head_owns the chain of nodes.
};
