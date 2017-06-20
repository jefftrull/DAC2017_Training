cmake_minimum_required( VERSION 3.5 )

set( CMAKE_CXX_STANDARD 14 )

add_executable( member_fn member_function_qualifiers.cpp )
add_library( smart_ptrs smart_pointers.cpp )
add_executable( alg_examples alg_examples.cpp )
add_executable( generic generic_programming.cpp )

if( GBENCH_ROOT )
  # assuming you built gbench in a "build" directory but have not installed it:
  include_directories( ${GBENCH_ROOT}/include )
  add_executable( gbench_sort gbench_sort.cpp )
  target_link_libraries( gbench_sort ${GBENCH_ROOT}/build/src/libbenchmark.a pthread )
else()
  message( WARNING "GBENCH_ROOT not supplied; Google Benchmark-dependent code will not be built" )
endif()
