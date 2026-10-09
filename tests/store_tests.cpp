#include "Store.hpp"

#include <cassert>
#include <iostream>

int main() {
  Store store;

  // A new key should not be found.
  assert(!store.get("missing").has_value());

  // A stored value should be retrievable.
  store.put("sensor-1", "23.5");
  auto value = store.get("sensor-1");
  assert(value.has_value());

  assert(value.value() == "23.5");

  // Storing the same key again should replace its value.
  store.put("sensor-1", "24.0");
  assert(store.get("sensor-1").value() == "24.0");

  // Removing a key should make it unavailable.
  store.remove("sensor-1");
  assert(!store.get("sensor-1").has_value());

  std::cout << "All Store tests passed\n";
}
