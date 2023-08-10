project(Nullspace)

cmake_minimum_required(VERSION 3.0.0)

find_package(pybind11)

add_subdirectory(src)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE cpp_grad)
