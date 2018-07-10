
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

file(GLOB golge_SRC "*.cpp" "*.c")
file(GLOB golge_CORE "core/*.cpp")
file(GLOB golge_ENGINE "engine/*.cpp")
file(GLOB golge_ENGINE_COMPONENTS "engine/components/*.cpp")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_SOURCE_DIR}/include/golge/config.h"
  )

# add_executable (Golge ${golge_SRC} ${golge_CORE} ${golge_ENGINE} ${golge_ENGINE_COMPONENTS})

add_library(Golge SHARED ${golge_SRC} ${golge_CORE} ${golge_ENGINE} ${golge_ENGINE_COMPONENTS})

set_target_properties(Golge PROPERTIES OUTPUT_NAME "Golge-${GOLGE_VERSION_STRING}")

set_target_properties(Golge PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin/)
set_target_properties(Golge PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set_target_properties(Golge PROPERTIES VERSION ${GOLGE_VERSION_STRING})
set_target_properties(Golge PROPERTIES SOVERSION ${GOLGE_VERSION_MAJOR})

target_link_libraries(Golge ${OPENGL_LIBRARIES} glfw3 Box2D sfml-audio)

