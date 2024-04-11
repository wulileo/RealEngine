cmake_minimum_required(VERSION 3.28)
project(RealEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(RealEngine main.cpp src/glad.c
        VertexData.h
        ShaderSource.h
        Texture2D.cpp
        Texture2D.h)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)
target_link_libraries(RealEngine ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)
