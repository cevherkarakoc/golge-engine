# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GolgEngine")
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Include sub-projects.
add_subdirectory(src)

target_include_directories(Golge PUBLIC include)