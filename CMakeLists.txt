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




# ####################################3
# cmake_minimum_required(VERSION 3.30)
# project(StoreProject LANGUAGES CXX)
#
# # require c++ 23
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
#
# # Include directories for headers
# include_directories(include)
#
# # Build the main executable
# add_executable(memory_store
#     src/Store.cpp
#     src/main.cpp
# )
#
# # Enable CTest framework
# enable_testing()
#
# # Build the test executable
# add_executable(store_tests
#     src/Store.cpp
#     tests/store_tests.cpp
# )
#
# # Register the test executable with CTest
# add_test(NAME StoreTests COMMAND store_tests)
