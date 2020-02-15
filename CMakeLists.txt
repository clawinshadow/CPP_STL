cmake_minimum_required(VERSION 3.0.0)

#set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD 11)

project(stl_demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(stl_demo main.cpp 
    cpp_11/new_features.cpp
    cpp_11/move_semantics.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
