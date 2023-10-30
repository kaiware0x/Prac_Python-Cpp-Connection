cmake_minimum_required(VERSION 3.5)

project(Prac_CallPythonFromCpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python COMPONENTS Development)
if (NOT Python_FOUND)
  message(FATAL_ERROR "Python not found")
endif()
message("Python_FOUND:${Python_FOUND}")
message("Python_VERSION:${Python_VERSION}")
message("Python_Development_FOUND:${Python_Development_FOUND}")
message("Python_LIBRARIES:${Python_LIBRARIES}")
message("Python_INCLUDE_DIRS:${Python_INCLUDE_DIRS}")

# @brief: macro呼び出し元のCMakeLists.txt直下のソールファイルパスを取得する.
macro(get_source_files)
    # 直下のソースファイル群を取得する
    file(GLOB_RECURSE SOURCES     RELATIVE ${PROJECT_SOURCE_DIR} *.cpp)
    file(GLOB_RECURSE SOURCES_CXX RELATIVE ${PROJECT_SOURCE_DIR} *.cxx)
    file(GLOB_RECURSE SOURCES_CU  RELATIVE ${PROJECT_SOURCE_DIR} *.cu)
    file(GLOB_RECURSE HEADERS     RELATIVE ${PROJECT_SOURCE_DIR} *.h)
    file(GLOB_RECURSE HEADERS_HPP RELATIVE ${PROJECT_SOURCE_DIR} *.hpp)
    file(GLOB_RECURSE HEADERS_HXX RELATIVE ${PROJECT_SOURCE_DIR} *.hxx)
    file(GLOB_RECURSE HEADERS_CUH RELATIVE ${PROJECT_SOURCE_DIR} *.cuh)
    file(GLOB_RECURSE FORMS       RELATIVE ${PROJECT_SOURCE_DIR} *.ui)
    file(GLOB_RECURSE RESOURCES   RELATIVE ${PROJECT_SOURCE_DIR} *.qrc)

    # .cxxと.hxxをSOURCESとHEADERSに統合
    list(APPEND SOURCES ${SOURCES_CXX})
    list(APPEND SOURCES ${SOURCES_CU})
    list(APPEND HEADERS ${HEADERS_HPP})
    list(APPEND HEADERS ${HEADERS_HXX})
    list(APPEND HEADERS ${HEADERS_CUH})

    # 変数を破棄
    unset(SOURCES_CXX)
    unset(SOURCES_CU)
    unset(HEADERS_HPP)
    unset(HEADERS_HXX)
    unset(HEADERS_CUH)

    # deprecatedフォルダ以下のソースは除外する
    list(FILTER SOURCES   EXCLUDE REGEX "^deprecated/.*")
    list(FILTER HEADERS   EXCLUDE REGEX "^deprecated/.*")
    list(FILTER FORMS     EXCLUDE REGEX "^deprecated/.*")
    list(FILTER RESOURCES EXCLUDE REGEX "^deprecated/.*")
endmacro()

get_source_files()

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    README.md
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Python_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Python_INCLUDE_DIRS}
)
