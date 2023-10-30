
function(my_link_python target)
    find_package(Python COMPONENTS Interpreter Development)

    message(STATUS "Python_FOUND: ${Python_FOUND}")
    message(STATUS "Python_LIBRARY_DIRS: ${Python_LIBRARY_DIRS}")
    message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")
    message(STATUS "Python_INCLUDE_DIR: ${Python_INCLUDE_DIR}")

    target_link_libraries(${target} PRIVATE
        ${Python_LIBRARIES}
    )
    target_include_directories(${target} PRIVATE
        ${Python_INCLUDE_DIR}
    )
endfunction()
