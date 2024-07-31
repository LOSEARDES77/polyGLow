cmake_minimum_required(VERSION 3.10)

project(polyGLow VERSION 1.0)

add_executable(polyGLow src/main.cpp ${GLAD_SOURCES})


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the glad source file
set(GLAD_SOURCES ${CMAKE_SOURCE_DIR}/src/glad.c)

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Specify the library directory
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(OpenGL_GL_PREFERENCE GLVND)

# Find and link GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(polyGLow glfw)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(polyGLow OpenGL::GL)

# Find and link GLEW
find_package(GLEW REQUIRED)
target_link_libraries(polyGLow GLEW::GLEW)


