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
include CMakeFiles/kkmeans_ex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kkmeans_ex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kkmeans_ex.dir/flags.make

CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o: CMakeFiles/kkmeans_ex.dir/flags.make
CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o: ../kkmeans_ex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o -c /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/kkmeans_ex.cpp

CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/kkmeans_ex.cpp > CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.i

CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/kkmeans_ex.cpp -o CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.s

# Object files for target kkmeans_ex
kkmeans_ex_OBJECTS = \
"CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o"

# External object files for target kkmeans_ex
kkmeans_ex_EXTERNAL_OBJECTS =

kkmeans_ex: CMakeFiles/kkmeans_ex.dir/kkmeans_ex.cpp.o
kkmeans_ex: CMakeFiles/kkmeans_ex.dir/build.make
kkmeans_ex: dlib_build/libdlib.a
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libnsl.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libSM.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libICE.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libX11.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libXext.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libpng.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libz.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libjpeg.so
kkmeans_ex: /usr/lib/x86_64-linux-gnu/libopenblas.so
kkmeans_ex: CMakeFiles/kkmeans_ex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kkmeans_ex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kkmeans_ex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kkmeans_ex.dir/build: kkmeans_ex

.PHONY : CMakeFiles/kkmeans_ex.dir/build

CMakeFiles/kkmeans_ex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kkmeans_ex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kkmeans_ex.dir/clean

CMakeFiles/kkmeans_ex.dir/depend:
	cd /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles/kkmeans_ex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kkmeans_ex.dir/depend

