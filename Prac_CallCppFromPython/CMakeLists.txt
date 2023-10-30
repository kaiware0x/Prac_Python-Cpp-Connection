cmake_minimum_required(VERSION 3.5)

project(Prac_CallCppFromPython VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_PYTHON_ROOT C:/Users/funne/AppData/Local/Programs/Python/Python311)

add_executable(${PROJECT_NAME}
    mysolver.cpp
    setup.py
    README.md
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${MY_PYTHON_ROOT}/libs
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:python311_d.lib>
    $<$<CONFIG:Release>:python311.lib>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${MY_PYTHON_ROOT}/include
)
