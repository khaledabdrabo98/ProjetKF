# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build

# Include any dependencies generated for this target.
include CMakeFiles/rvm_regression_ex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rvm_regression_ex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rvm_regression_ex.dir/flags.make

CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o: CMakeFiles/rvm_regression_ex.dir/flags.make
CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o: ../rvm_regression_ex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o -c /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/rvm_regression_ex.cpp

CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/rvm_regression_ex.cpp > CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.i

CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/rvm_regression_ex.cpp -o CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.s

# Object files for target rvm_regression_ex
rvm_regression_ex_OBJECTS = \
"CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o"

# External object files for target rvm_regression_ex
rvm_regression_ex_EXTERNAL_OBJECTS =

rvm_regression_ex: CMakeFiles/rvm_regression_ex.dir/rvm_regression_ex.cpp.o
rvm_regression_ex: CMakeFiles/rvm_regression_ex.dir/build.make
rvm_regression_ex: dlib_build/libdlib.a
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libnsl.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libSM.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libICE.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libX11.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libXext.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libpng.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libz.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libjpeg.so
rvm_regression_ex: /usr/lib/x86_64-linux-gnu/libopenblas.so
rvm_regression_ex: CMakeFiles/rvm_regression_ex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rvm_regression_ex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rvm_regression_ex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rvm_regression_ex.dir/build: rvm_regression_ex

.PHONY : CMakeFiles/rvm_regression_ex.dir/build

CMakeFiles/rvm_regression_ex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rvm_regression_ex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rvm_regression_ex.dir/clean

CMakeFiles/rvm_regression_ex.dir/depend:
	cd /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles/rvm_regression_ex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rvm_regression_ex.dir/depend

