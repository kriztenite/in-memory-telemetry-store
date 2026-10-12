cmake_minimum_required(VERSION 3.30)

project(memory_store LANGUAGES CXX)


# Set the C++ Standard to c++23 and require it
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target: store_lib (static library)
add_library(store_lib src/Store.cpp)
#propagage header directories to consumers automatically via PUBLIC
target_include_directories(store_lib PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

#Target memory_store
# Define the executable output name and source files
add_executable(memory_store src/main.cpp)
target_link_libraries(memory_store PRIVATE store_lib)


# Target store test 
enable_testing()
add_executable(store_tests tests/store_tests.cpp)

target_link_libraries(store_tests PRIVATE store_lib)

add_test(NAME StoreTests COMMAND store_tests)

# Target Timeseries
add_executable(time_series_tests tests/time_series_tests.cpp
    src/TimeSeries.cpp)
target_include_directories(time_series_tests PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_test(NAME TimeSeriesTests COMMAND time_series_tests)

# Target LruCache
add_executable(lru_cache_tests tests/lru_cache_tests.cpp src/LruCache.cpp)
target_include_directories(lru_cache_tests PRIVATE include)
add_test(NAME LruCacheTests COMMAND lru_cache_tests)

#Target PointerList
add_executable(pointer_list_tests tests/pointer_list_tests.cpp src/PointerList.cpp)
target_include_directories(pointer_list_tests PRIVATE include)
add_test(NAME PointerListTests COMMAND pointer_list_tests)

#Target concurrency test
find_package(Threads REQUIRED)
add_executable(store_concurrency_tests tests/store_concurrency_tests.cpp src/Store.cpp)
target_include_directories(store_concurrency_tests PRIVATE include)
target_link_libraries(store_concurrency_tests PRIVATE Threads::Threads)
add_test(NAME StoreConcurrencyTests COMMAND store_concurrency_tests)

# Target lru concurrency test
add_executable(lru_cache_concurrency_tests tests/lru_cache_concurrency_tests.cpp src/LruCache.cpp)
target_include_directories(lru_cache_concurrency_tests PRIVATE include)
target_link_libraries(lru_cache_concurrency_tests PRIVATE Threads::Threads)
add_test(NAME LruCacheConcurrencyTest COMMAND lru_cache_concurrency_tests)

# Target ExpirationWorker 
add_executable(expiration-worker-tests 
    tests/expiration_worker_tests.cpp src/ExpirationWorker.cpp src/TimeSeries.cpp)
target_include_directories(expiration-worker-tests PRIVATE include)
target_link_libraries(expiration-worker-tests PRIVATE Threads::Threads)
add_test(NAME ExpirationWorkerTests COMMAND expiration-worker-tests)

