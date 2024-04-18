cmake_minimum_required(VERSION 3.28)
project(RealEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/depends)
include_directories(${PROJECT_SOURCE_DIR}/depends/glad)
include_directories(${PROJECT_SOURCE_DIR}/depends/GLFW)
include_directories(${PROJECT_SOURCE_DIR}/depends/glext)
include_directories(${PROJECT_SOURCE_DIR}/depends/glm)
include_directories(${PROJECT_SOURCE_DIR}/depends/stb)
include_directories(${PROJECT_SOURCE_DIR}/depends/rapidxml)
include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/source/renderer)
include_directories(${PROJECT_SOURCE_DIR}/source/utils)

link_directories(${PROJECT_SOURCE_DIR}/libs)

set(glad_c ${PROJECT_SOURCE_DIR}/depends/glad/glad.c)

file(GLOB_RECURSE engine_cpp source/*.cpp)
file(GLOB_RECURSE engine_h source/*.h)

add_executable(RealEngine ${engine_h} ${engine_cpp} ${glad_c})

target_link_libraries(RealEngine ${PROJECT_SOURCE_DIR}/libs/glfw3.dll)
