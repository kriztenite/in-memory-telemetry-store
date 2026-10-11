
#include "LruCache.hpp"

#include <cassert>
#include <iostream>

int main() {
  LruCache cache(2);

  cache.put("A", "apple");
  cache.put("B", "banana");

  // Access A, making B the least recently used.
  assert(cache.get("A").has_value());
  assert(cache.get("A").value() == "apple");

  // Adding C should evict B.
  cache.put("C", "cherry");

  assert(cache.get("B") == std::nullopt);
  assert(cache.get("A").has_value());
  assert(cache.get("A").value() == "apple");
  assert(cache.get("C").has_value());
  assert(cache.get("C").value() == "cherry");

  // Updating a key changes its value without adding another entry.
  cache.put("A", "apricot");
  assert(cache.get("A").has_value());
  assert(cache.get("A").value() == "apricot");

  // A zero-capacity cache stores nothing.
  LruCache empty_cache(0);
  empty_cache.put("X", "x-ray");
  assert(empty_cache.get("X") == std::nullopt);

  std::cout << "All LruCache tests passed\n";
}
