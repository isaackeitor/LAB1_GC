cmake_minimum_required(VERSION 3.26.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SR VERSION 1.0)

add_executable(${PROJECT_NAME}
    src/main.cpp 
    src/framebuffer.cpp
    src/bitmap.cpp
    src/drawpolygon.cpp
    src/renderBuffer.cpp
)
