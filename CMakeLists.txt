cmake_minimum_required(VERSION 3.10)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include_directories(/opt/homebrew/include ${CMAKE_SOURCE_DIR}/headers)
link_directories(/opt/homebrew/lib)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(MyOpenGLProject ${SOURCES})

target_link_libraries(
    MyOpenGLProject
    OpenGL::GL
    glfw
    GLEW
)
