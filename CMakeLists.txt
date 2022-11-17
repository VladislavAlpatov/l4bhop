cmake_minimum_required(VERSION 3.20)
add_compile_options(-Ofast)
set(CMAKE_CXX_STANDARD 23)
project(l4bhop)
add_library(l4bhop MODULE src/main.cpp)
set(CMAKE_SHARED_MODULE_PREFIX "")

link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")
include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")

target_link_libraries(l4bhop PRIVATE d3d9.lib)


add_subdirectory(src/utils)
add_subdirectory(src/SDK)

find_package(minhook CONFIG REQUIRED)
target_link_libraries(l4bhop PRIVATE minhook::minhook)