# This Python file uses the following encoding: utf-8

from setuptools import setup, Extension

setup(
    name = "mysolver",
    ext_modules=[
        Extension("mysolver", ["mysolver.cpp"]),
    ]
)

