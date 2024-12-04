#!/usr/bin/env python

from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "condorcet",
        ["condorcet.cpp"],
    ),
]

setup(
    name="condorcet",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
