cmake_minimum_required(VERSION 3.14)
project(MMI)

set(CMAKE_CXX_STANDARD 14)

add_executable(MMI src/main.cpp
        include/zespolona.h
        src/simple_function.cpp
        include/simple_function.h
        src/polygon_function.cpp
        include/polygon_function.h
        src/matrix_function.cpp
        include/matrix_function.h
        include/DFT.h
        src/DFT.cpp
        #[[libs/gnuplot_i.hpp]])

find_package(PythonLibs 2.7)
target_include_directories(MMI PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(MMI ${PYTHON_LIBRARIES})
