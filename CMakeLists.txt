cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

project(l4bhop)

add_library(l4bhop MODULE src/main.cpp)
set(CMAKE_SHARED_MODULE_PREFIX "")

add_subdirectory(src/utils)
add_subdirectory(src/SDK)

find_package(minhook CONFIG REQUIRED)
target_link_libraries(l4bhop PRIVATE minhook::minhook)