cmake_minimum_required( VERSION 3.5 )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Og -fno-omit-frame-pointer" )

if( CMAKE_BUILD_TYPE STREQUAL "" )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Release, Debug, RelWithDebInfo, MinSizeRel)" FORCE )
endif()

add_executable( member_fn member_function_qualifiers.cpp )
add_library( smart_ptrs smart_pointers.cpp )
add_executable( alg_examples alg_examples.cpp )
add_executable( generic generic_programming.cpp )
add_library( visitor visitor.cpp )
add_executable( ub ub.cpp )
target_compile_options( ub PUBLIC -fsanitize=undefined )
target_link_libraries( ub -fsanitize=undefined )

if( GBENCH_ROOT )
  # assuming you built gbench in a "build" directory but have not installed it:
  include_directories( ${GBENCH_ROOT}/include )
  add_executable( gbench_sort gbench_sort.cpp )
  target_link_libraries( gbench_sort ${GBENCH_ROOT}/build/src/libbenchmark.a pthread )
else()
  message( WARNING "GBENCH_ROOT not supplied; Google Benchmark-dependent code will not be built" )
endif()
