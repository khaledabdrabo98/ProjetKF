# This is a CMake makefile.  CMake is a tool that helps you build C++ programs.
# You can download CMake from http://www.cmake.org.  This CMakeLists.txt file
# you are reading builds dlib's example programs. 
#


cmake_minimum_required(VERSION 2.8.12)
# Every project needs a name.  We call this the "examples" project.
project(lifprojet_am4)

INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -I/usr/include/SDL2")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


set(GKIT_CORE_INCLUDE_DIR gKitCore)
set(GKIT_VIEW_INCLUDE_DIR gKitView)
set(VIDEOCAPTURE_INCLUDE_DIR videoCapture)
set(IMGUI_INCLUDE_DIR ../dependencies/imgui ../dependencies/imgui/examples)



file(GLOB GKIT_CORE_SRC gKitCore/*.cpp)
file(GLOB GKIT_VIEW_SRC gKitView/*.cpp)
file(GLOB IMGUI_SRC ../dependencies/imgui/*.cpp ../dependencies/imgui/examples/imgui_impl_opengl3.cpp ../dependencies/imgui/examples/imgui_impl_sdl.cpp)
file(GLOB VIDEOCAPTURE_SRC videoCapture/*.cpp)


# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# cmake needs is the dlib source code folder and it will take care of everything.


add_subdirectory(../dependencies/dlib-19.19/dlib dlib_build)

# If you have cmake 3.14 or newer you can even use FetchContent instead of
# add_subdirectory() to pull in dlib as a dependency.  So instead of using the
# above add_subdirectory() command, you could use the following three commands
# to make dlib available:
#  include(FetchContent)
#  FetchContent_Declare(dlib
#      GIT_REPOSITORY https://github.com/davisking/dlib.git
#      GIT_TAG        v19.18
#  )
#  FetchContent_MakeAvailable(dlib)


# The next thing we need to do is tell CMake about the code you want to
# compile.  We do this with the add_executable() statement which takes the name
# of the output executable and then a list of .cpp files to compile.  Here we
# are going to compile one of the dlib example programs which has only one .cpp
# file, assignment_learning_ex.cpp.  If your program consisted of multiple .cpp
# files you would simply list them here in the add_executable() statement.  


find_package(OpenCV QUIET)
   if (OpenCV_FOUND)
	   include_directories(${OpenCV_INCLUDE_DIRS} ${GKIT_CORE_INCLUDE_DIR} ${GKIT_VIEW_INCLUDE_DIR}  ${IMGUI_INCLUDE_DIR})
      	   add_executable(lifprojet_am4 ${GKIT_CORE_SRC} ${GKIT_VIEW_SRC} ${VIDEOCAPTURE_SRC} ${IMGUI_SRC} main.cpp)
            target_link_libraries(lifprojet_am4 dlib::dlib ${OpenCV_LIBS} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} 
                                                           ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )

   else()
      message("OpenCV not found, so we won't build lifprojet_am4.")
   endif()

# Finally, you need to tell CMake that this program, assignment_learning_ex,
# depends on dlib.  You do that with this statement: 


target_link_libraries(lifprojet_am4 dlib::dlib )

# To compile this program all you need to do is ask cmake.  You would type
# these commands from within the directory containing this CMakeLists.txt
# file:
#   mkdir build
#   cd build
#   cmake ..
#   cmake --build . --config Release
#
# The cmake .. command looks in the parent folder for a file named
# CMakeLists.txt, reads it, and sets up everything needed to build program.
# Also, note that CMake can generate Visual Studio or XCode project files.  So
# if instead you had written:
#   cd build
#   cmake .. -G Xcode
#
# You would be able to open the resulting Xcode project and compile and edit
# the example programs within the Xcode IDE.  CMake can generate a lot of
# different types of IDE projects.  Run the cmake -h command to see a list of
# arguments to -G to see what kinds of projects cmake can generate for you.  It
# probably includes your favorite IDE in the list.




