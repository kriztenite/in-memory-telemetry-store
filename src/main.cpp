// main.cpp
#include "Store.hpp"
#include <iostream>

int main() {
  Store store;

  store.put("sensor-1", "23.5");

  auto value = store.get("sensor-1");
  if (value.has_value()) {
    std::cout << "sensor-1 = " << value.value() << '\n';
  }

  auto missing = store.get("sensor-2");
  if (!missing.has_value()) {
    std::cout << "sensor-2 was not found\n";
  }

  store.remove("sensor-1");

  if (!store.get("sensor-1").has_value()) {
    std::cout << "sensor-1 was removed\n";
  }
}
