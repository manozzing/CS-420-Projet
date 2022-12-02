cmake_minimum_required (VERSION 3.5)
#set(CMAKE_C_COMPILER mpiicc)
#set(CMAKE_C_STANDARD 99)
#project(mp4-release-stencil VERSION 1.0.0 LANGUAGES C)

#add_compile_options(-Wall)

add_library(stencil_solution STATIC stencil.c stencil.h)

add_executable(stencil main.c stencil.c stencil.h)
target_link_libraries(stencil helpers)
target_compile_options(stencil PUBLIC -Ofast -xHost -qopt-prefetch -unroll-aggressive)
target_link_libraries(stencil ${MPI_C_LIBRARIES})

# add_executable(stencil_debug main.c stencil.c stencil.h)
# target_link_libraries(stencil_debug helpers)
# target_compile_options(stencil_debug PUBLIC -g)
# target_link_libraries(stencil_debug PUBLIC ${MPI_C_LIBRARIES})

# target_include_directories(stencil_debug PUBLIC ${MPI_C_INCLUDE_PATH})
if(MPI_COMPILE_FLAGS)
  set_target_properties(stencil PROPERTIES
  COMPILE_FLAGS "${MPI_CXX_COMPILE_FLAGS}")
endif()

