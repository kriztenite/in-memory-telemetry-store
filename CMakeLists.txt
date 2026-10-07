cmake_minimum_required(VERSION 3.30)

project(memory_store LANGUAGES CXX)

# Set the C++ Standard to c++23 and require it
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the executable output name and source files
add_executable(memory_store
    src/main.cpp
    src/Store.cpp
)

target_include_directories(memory_store PRIVATE include)

# Pass the GCC-specific -fmodules flag if using GCC
target_compile_options(memory_store PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

