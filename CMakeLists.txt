
cmake_minimum_required (VERSION 3.8)

project ("GolgEngine")

set(GOLGE_VERSION_MAJOR 0)
set(GOLGE_VERSION_MINOR 1)
set(GOLGE_VERSION_PATCH 0)
set(GOLGE_VERSION_STRING ${GOLGE_VERSION_MAJOR}.${GOLGE_VERSION_MINOR}.${GOLGE_VERSION_PATCH})

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Include sub-projects.
add_subdirectory(src)

target_include_directories(Golge PUBLIC include)