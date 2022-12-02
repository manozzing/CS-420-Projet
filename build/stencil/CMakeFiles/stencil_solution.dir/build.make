# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/manhop2/cs420/mp3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manhop2/cs420/mp3/build

# Include any dependencies generated for this target.
include stencil/CMakeFiles/stencil_solution.dir/depend.make

# Include the progress variables for this target.
include stencil/CMakeFiles/stencil_solution.dir/progress.make

# Include the compile flags for this target's objects.
include stencil/CMakeFiles/stencil_solution.dir/flags.make

stencil/CMakeFiles/stencil_solution.dir/stencil.c.o: stencil/CMakeFiles/stencil_solution.dir/flags.make
stencil/CMakeFiles/stencil_solution.dir/stencil.c.o: ../stencil/stencil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manhop2/cs420/mp3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object stencil/CMakeFiles/stencil_solution.dir/stencil.c.o"
	cd /home/manhop2/cs420/mp3/build/stencil && /usr/local/intel/parallel_studio_xe_2018/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/stencil_solution.dir/stencil.c.o -c /home/manhop2/cs420/mp3/stencil/stencil.c

stencil/CMakeFiles/stencil_solution.dir/stencil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/stencil_solution.dir/stencil.c.i"
	cd /home/manhop2/cs420/mp3/build/stencil && /usr/local/intel/parallel_studio_xe_2018/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manhop2/cs420/mp3/stencil/stencil.c > CMakeFiles/stencil_solution.dir/stencil.c.i

stencil/CMakeFiles/stencil_solution.dir/stencil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/stencil_solution.dir/stencil.c.s"
	cd /home/manhop2/cs420/mp3/build/stencil && /usr/local/intel/parallel_studio_xe_2018/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manhop2/cs420/mp3/stencil/stencil.c -o CMakeFiles/stencil_solution.dir/stencil.c.s

# Object files for target stencil_solution
stencil_solution_OBJECTS = \
"CMakeFiles/stencil_solution.dir/stencil.c.o"

# External object files for target stencil_solution
stencil_solution_EXTERNAL_OBJECTS =

stencil/libstencil_solution.a: stencil/CMakeFiles/stencil_solution.dir/stencil.c.o
stencil/libstencil_solution.a: stencil/CMakeFiles/stencil_solution.dir/build.make
stencil/libstencil_solution.a: stencil/CMakeFiles/stencil_solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/manhop2/cs420/mp3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libstencil_solution.a"
	cd /home/manhop2/cs420/mp3/build/stencil && $(CMAKE_COMMAND) -P CMakeFiles/stencil_solution.dir/cmake_clean_target.cmake
	cd /home/manhop2/cs420/mp3/build/stencil && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stencil_solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stencil/CMakeFiles/stencil_solution.dir/build: stencil/libstencil_solution.a

.PHONY : stencil/CMakeFiles/stencil_solution.dir/build

stencil/CMakeFiles/stencil_solution.dir/clean:
	cd /home/manhop2/cs420/mp3/build/stencil && $(CMAKE_COMMAND) -P CMakeFiles/stencil_solution.dir/cmake_clean.cmake
.PHONY : stencil/CMakeFiles/stencil_solution.dir/clean

stencil/CMakeFiles/stencil_solution.dir/depend:
	cd /home/manhop2/cs420/mp3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manhop2/cs420/mp3 /home/manhop2/cs420/mp3/stencil /home/manhop2/cs420/mp3/build /home/manhop2/cs420/mp3/build/stencil /home/manhop2/cs420/mp3/build/stencil/CMakeFiles/stencil_solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stencil/CMakeFiles/stencil_solution.dir/depend

