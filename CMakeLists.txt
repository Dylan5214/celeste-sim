cmake_minimum_required(VERSION 3.20)
project(CelesteSim)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DGL_SILENCE_DEPRECATION)

# GLM (header only, lives in external/)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE external)

# Find Homebrew-installed libs
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Collect sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(CelesteSim ${SOURCES})

target_include_directories(CelesteSim PRIVATE src external)

target_link_libraries(CelesteSim
    PRIVATE
    glfw
    GLEW::GLEW
    glm
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)