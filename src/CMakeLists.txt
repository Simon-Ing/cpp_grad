

add_library(cpp_grad bind.cpp value.cpp)
target_link_libraries(cpp_grad pybind11::module)
