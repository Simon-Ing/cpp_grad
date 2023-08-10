#include <pybind11/pybind11.h>
#include "value.h"

namespace py = pybind11;

PYBIND11_MODULE(cpp_grad, m)
{
  py::class_<Value>(m, "Value")
    .def(py::init<double>())
    .def("__add__", [](Value &a, Value &b) { return a + b; })
    .def("__repr__", &Value::get)
    .def("backward", &Value::backward)
    ;
}
