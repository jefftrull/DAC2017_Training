cmake_minimum_required( VERSION 3.5 )

set( CMAKE_CXX_STANDARD 14 )

add_executable( member_fn member_function_qualifiers.cpp )
add_library( smart_ptrs smart_pointers.cpp )
add_executable( alg_examples alg_examples.cpp )
