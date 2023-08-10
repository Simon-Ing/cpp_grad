
from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

setup(name="cpp_grad", version="0.0.1", ext_modules=[Pybind11Extension("cpp_grad", ["src/bind.cpp", "src/value.cpp"])])
