
#include "LruCache.hpp"

#include <cassert>
#include <iostream>

int main() {
  {
    LruCache cache(2);

    cache.put("A", "apple");
    cache.put("B", "banana");

    // Access A, making B the least recently used.
    assert(cache.get("A").has_value());
    assert(cache.get("A").value() == "apple");

    // Adding C should evict B.
    cache.put("C", "cherry");

    assert(!cache.get("B").has_value());
    assert(cache.get("A").has_value());
    assert(cache.get("A").value() == "apple");
    assert(cache.get("C").has_value());
    assert(cache.get("C").value() == "cherry");
  }

  {
    LruCache cache(2);

    cache.put("A", "apple");
    cache.put("B", "banana");

    // Updating A make it most recently used.
    cache.put("A", "apricot");
    cache.put("C", "cherry");

    assert(!cache.get("B").has_value());
    assert(cache.get("A").has_value());
    assert(cache.get("A").value() == "apricot");
  }

  {
    LruCache cache(2);

    cache.put("A", "apple");
    cache.put("B", "banana");

    // Access B, so A becomes least recently used.
    assert(cache.get("B").value() == "banana");

    cache.put("C", "cherry");

    assert(!cache.get("A").has_value());
    assert(cache.get("B").value() == "banana");
  }

  {
    LruCache cache(1);

    cache.put("A", "apple");
    cache.put("B", "banana");

    assert(!cache.get("A").has_value());
    assert(cache.get("B").value() == "banana");
  }

  {

    // A zero-capacity cache stores nothing.
    LruCache empty_cache(0);
    empty_cache.put("A", "apple");
    assert(empty_cache.get("A") == std::nullopt);
  }

  std::cout << "All LruCache tests passed\n";
}
