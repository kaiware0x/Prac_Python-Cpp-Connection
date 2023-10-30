cmake_minimum_required(VERSION 3.5)

# vcpkgでインストールしたBoostをfind_packageで見つけるために必要
add_definitions(
    -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake
)

project(Prac_BoostPyhon LANGUAGES CXX)

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


find_package(Boost REQUIRED)
#find_package(Boost 1.83.0 REQUIRED COMPONENTS python)
#find_package(Boost 1.83.0 REQUIRED COMPONENTS system python)
message("Boost_FOUND:${Boost_FOUND}")
message("Boost_VERSION:${Boost_VERSION}")
message("Boost_LIBRARY_DIRS:${Boost_LIBRARY_DIRS}")
message("Boost_LIBRARIES:${Boost_LIBRARIES}")
message("Boost_INCLUDE_DIRS:${Boost_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME}
    main.cpp
    README.md
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIRS}
#    ${Python_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:${Boost_LIBRARY_DIRS}/../debug/lib>
    $<$<CONFIG:Release>:${Boost_LIBRARY_DIRS}>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Boost_LIBRARIES}
    $<$<CONFIG:Debug>:boost_python311-vc140-mt-gd.lib>
    $<$<CONFIG:Release>:boost_python311-vc140-mt.lib>

#    ${Python_LIBRARIES}
#    $<$<CONFIG:Debug>:python311_d.lib>
#    $<$<CONFIG:Release>:python311.lib>
)
