// main.cpp
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

class Store {
public:
  void put(const std::string &key, const std::string &value) {
    data_[key] = value;
  }

  std::optional<std::string> get(const std::string &key) const {
    auto it = data_.find(key);

    if (it == data_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  void remove(const std::string &key) { data_.erase(key); }

private:
  std::unordered_map<std::string, std::string> data_;
};

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
