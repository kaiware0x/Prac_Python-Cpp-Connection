
### pybind11の環境構築
# vcpkgでinstallし、
# definition「CMAKE_TOOLCHAIN_FILE」に
# {vcpkg-install-dir}/scripts/buildsystems/vcpkg.cmake を指定する。

cmake_minimum_required(VERSION 3.5)

project(Prac_Python-Cpp-Connection LANGUAGES CXX)

include(Utility.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Prac_pybind11_extend01/)
add_subdirectory(Prac_pybind11_extend02/)
add_subdirectory(Prac_pybind11_extend03/)
add_subdirectory(Prac_pybind11_extend04/)
add_subdirectory(Prac_pybind11_extend05/)
add_subdirectory(Prac_pybind11_extend06/) # Classes
add_subdirectory(Prac_pybind11_extend07/) # Classes
add_subdirectory(Prac_pybind11_extend08/) # Classes
add_subdirectory(Prac_pybind11_extend09/) # Classes

add_subdirectory(Prac_pybind11_embed01/)
