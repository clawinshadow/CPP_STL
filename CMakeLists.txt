cmake_minimum_required(VERSION 3.0.0)

#set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD 11)

project(stl_demo VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(helper)

add_executable(stl_demo main.cpp helper/helper.h
    cpp_11/new_features.cpp
    cpp_11/move_semantics.cpp
    cpp_11/exceptions.cpp
    cpp_11/lambdas.cpp
    utility/pairs_and_tuples.cc
    utility/utility_demos.cc
    utility/smart_pointers.cc
    utility/type_trait.cpp
    utility/auxiliary_functions.cc
    standard_template_library/stl_basics.cc
    standard_template_library/containers.cc
    standard_template_library/iterators.cpp
    standard_template_library/algorithms.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
