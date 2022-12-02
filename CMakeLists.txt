cmake_minimum_required (VERSION 3.5)
set(CMAKE_C_COMPILER mpiicc)
set(CMAKE_C_STANDARD 99)
project(mp3-release VERSION 1.0.0 LANGUAGES C)

add_compile_options(-Wall)
# add_compile_options(-DVERBOSE_LEVEL=1)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_library(utils STATIC tools/utils.c tools/utils.h)
add_library(helpers STATIC tools/helpers.c tools/helpers.h)
target_link_libraries(helpers utils)


target_link_libraries(helpers  ${MPI_C_LIBRARIES})
if(MPI_COMPILE_FLAGS)
  set_target_properties(helpers PROPERTIES
  COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
endif()

include_directories(tools)

add_subdirectory(stencil)
