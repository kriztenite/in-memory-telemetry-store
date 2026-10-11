#include "PointerList.hpp"

#include <cassert>
#include <iostream>

int main() {
  PointerList list;

  assert(list.empty());
  assert(list.front() == nullptr);
  assert(list.back() == nullptr);

  list.push_front("first");
  list.push_front("second");

  assert(*list.front() == "second");
  assert(*list.back() == "first");

  list.pop_back();
  assert(*list.back() == "second");

  list.pop_back();
  assert(list.empty());

  std::cout << "All PointerList tests passed\n";
}
