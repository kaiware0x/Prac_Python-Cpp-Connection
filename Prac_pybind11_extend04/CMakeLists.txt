cmake_minimum_required(VERSION 3.5)

project(Prac_pybind11_extend04 LANGUAGES CXX)

find_package(pybind11 CONFIG REQUIRED)

# pybind11 method:
pybind11_add_module(extend04 main.cpp)

## Python method:
#Python_add_library(MyModule2 src2.cpp)
#target_link_libraries(MyModule2 pybind11::headers)
#set_target_properties(MyModule2 PROPERTIES
#    INTERPROCEDURAL_OPTIMIZATION ON
#    CXX_VISIBILITY_PRESET ON
#    VISIBILITY_INLINES_HIDDEN ON
#)

linkPython(extend04)
