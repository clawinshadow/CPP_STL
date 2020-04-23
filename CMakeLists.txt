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
    standard_template_library/algorithms.cpp
    standard_template_library/func_arguments.cc
    containers/demos.cpp
    containers/arrays.cpp
    containers/vectors.cpp
    containers/deques.cpp
    containers/lists.cpp
    containers/forward_lists.cpp
    containers/common.cc
    containers/sets.cc
    containers/maps.cpp
    containers/others.cpp
    container_members/demos.cpp
    iterators/demos.cpp
    iterators/categories.cpp
    iterators/auxiliary.cpp
    iterators/adapters.cpp
    function_objects/demos.cpp
    function_objects/basics.cpp
    function_objects/binders.cpp
    function_objects/lambdas.cpp
    algorithms/demos.cpp
    algorithms/for_each.cpp
    algorithms/non_modifying.cpp
    algorithms/modifying.cpp
    algorithms/removing.cpp
    algorithms/mutating.cpp
    algorithms/sorting.cpp
    algorithms/sorted_range.cpp
    algorithms/numerics.cpp
    special_containers/demos.cpp
    special_containers/stacks.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
