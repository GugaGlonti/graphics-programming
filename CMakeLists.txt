cmake_minimum_required(VERSION 3.10)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libraries from Homebrew
find_package(OpenGL REQUIRED)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(MyOpenGLProject main.cpp)

target_link_libraries(
    MyOpenGLProject
    OpenGL::GL
    glfw
    GLEW
)
