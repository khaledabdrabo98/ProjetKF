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
include CMakeFiles/server_iostream_ex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server_iostream_ex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_iostream_ex.dir/flags.make

CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o: CMakeFiles/server_iostream_ex.dir/flags.make
CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o: ../server_iostream_ex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o -c /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/server_iostream_ex.cpp

CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/server_iostream_ex.cpp > CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.i

CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/server_iostream_ex.cpp -o CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.s

# Object files for target server_iostream_ex
server_iostream_ex_OBJECTS = \
"CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o"

# External object files for target server_iostream_ex
server_iostream_ex_EXTERNAL_OBJECTS =

server_iostream_ex: CMakeFiles/server_iostream_ex.dir/server_iostream_ex.cpp.o
server_iostream_ex: CMakeFiles/server_iostream_ex.dir/build.make
server_iostream_ex: dlib_build/libdlib.a
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libnsl.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libSM.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libICE.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libX11.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libXext.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libpng.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libz.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libjpeg.so
server_iostream_ex: /usr/lib/x86_64-linux-gnu/libopenblas.so
server_iostream_ex: CMakeFiles/server_iostream_ex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server_iostream_ex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_iostream_ex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_iostream_ex.dir/build: server_iostream_ex

.PHONY : CMakeFiles/server_iostream_ex.dir/build

CMakeFiles/server_iostream_ex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_iostream_ex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_iostream_ex.dir/clean

CMakeFiles/server_iostream_ex.dir/depend:
	cd /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build /home/feras/Documents/fac/lifprojet/test/projetkf/dlib-19.19/examples/build/CMakeFiles/server_iostream_ex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_iostream_ex.dir/depend

