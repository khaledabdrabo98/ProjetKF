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
include CMakeFiles/dir_nav_ex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dir_nav_ex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dir_nav_ex.dir/flags.make

CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o: CMakeFiles/dir_nav_ex.dir/flags.make
CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o: ../dir_nav_ex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o -c /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/dir_nav_ex.cpp

CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/dir_nav_ex.cpp > CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.i

CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/dir_nav_ex.cpp -o CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.s

# Object files for target dir_nav_ex
dir_nav_ex_OBJECTS = \
"CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o"

# External object files for target dir_nav_ex
dir_nav_ex_EXTERNAL_OBJECTS =

dir_nav_ex: CMakeFiles/dir_nav_ex.dir/dir_nav_ex.cpp.o
dir_nav_ex: CMakeFiles/dir_nav_ex.dir/build.make
dir_nav_ex: dlib_build/libdlib.a
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libnsl.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libSM.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libICE.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libX11.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libXext.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libpng.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libz.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libjpeg.so
dir_nav_ex: /usr/lib/x86_64-linux-gnu/libopenblas.so
dir_nav_ex: CMakeFiles/dir_nav_ex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dir_nav_ex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dir_nav_ex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dir_nav_ex.dir/build: dir_nav_ex

.PHONY : CMakeFiles/dir_nav_ex.dir/build

CMakeFiles/dir_nav_ex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dir_nav_ex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dir_nav_ex.dir/clean

CMakeFiles/dir_nav_ex.dir/depend:
	cd /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles/dir_nav_ex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dir_nav_ex.dir/depend

