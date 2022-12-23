cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)

if( NOT CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Non release build, pdb file will be created")
    add_compile_options(-gcodeview)
    add_link_options(-fuse-ld=lld -Wl,--pdb=)
else()
    add_link_options(-static -s -pthread -dead_strip_dylibs)
    add_compile_options(-O3 -fdata-sections -ffunction-sections)

endif()


project(l4bhop)

add_library(l4bhop MODULE src/main.cpp)

set_target_properties(l4bhop PROPERTIES COMPILE_PDB_NAME "l4bgop")
set(CMAKE_SHARED_MODULE_PREFIX "")

add_subdirectory(src/utils)
add_subdirectory(src/SDK)

find_package(minhook CONFIG REQUIRED)
target_link_libraries(l4bhop PRIVATE minhook::minhook)
target_link_libraries(l4bhop PRIVATE d3dx9)