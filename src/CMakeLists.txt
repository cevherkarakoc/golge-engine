# CMakeList.txt : CMake project for Perde, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS -m32)
set(CMAKE_CXX_STANDARD 17)

file(GLOB golge_SRC "*.cpp" "*.c")
file(GLOB golge_CORE "core/*.cpp")
file(GLOB golge_GAME "game/*.cpp")
file(GLOB golge_GAME_COMPONENTS "game/components/*.cpp")

add_executable (Golge ${golge_SRC} ${golge_CORE} ${golge_GAME} ${golge_GAME_COMPONENTS})

set_target_properties(Golge PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

target_link_libraries(Golge ${OPENGL_LIBRARIES} glfw3 Box2D sfml-audio)

