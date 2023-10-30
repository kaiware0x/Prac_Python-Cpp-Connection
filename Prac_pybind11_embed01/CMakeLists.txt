cmake_minimum_required(VERSION 3.5)

project(Prac_pybind11_embed01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pybind11::embed
)

my_link_python(${PROJECT_NAME})
