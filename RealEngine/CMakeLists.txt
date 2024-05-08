cmake_minimum_required(VERSION 3.28)
project(RealEngine)

set(CMAKE_CXX_STANDARD 17)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pragmas")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pragmas")
endif ()

file(GLOB LIB_FILES ${PROJECT_SOURCE_DIR}/libs/*)
file(COPY ${LIB_FILES} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${PROJECT_BINARY_DIR})

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -mwindows")

include_directories(${PROJECT_SOURCE_DIR}/depends)
include_directories(${PROJECT_SOURCE_DIR}/depends/glad)
include_directories(${PROJECT_SOURCE_DIR}/depends/GLFW)
include_directories(${PROJECT_SOURCE_DIR}/depends/glext)
include_directories(${PROJECT_SOURCE_DIR}/depends/glm)
include_directories(${PROJECT_SOURCE_DIR}/depends/stb)
include_directories(${PROJECT_SOURCE_DIR}/depends/rapidxml)
include_directories(${PROJECT_SOURCE_DIR}/depends/freetype)
include_directories(${PROJECT_SOURCE_DIR}/depends/renderdoc)

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/source/renderer)
include_directories(${PROJECT_SOURCE_DIR}/source/utils)

link_directories(${PROJECT_SOURCE_DIR}/libs)

set(glad_c ${PROJECT_SOURCE_DIR}/depends/glad/glad.c)
file(GLOB_RECURSE rttr_cpp depends/rttr/*.cpp)

file(GLOB_RECURSE engine_cpp source/*.cpp)
file(GLOB_RECURSE project_cpp project/*.cpp)

add_executable(RealEngine ${engine_cpp} ${glad_c} ${rttr_cpp} ${project_cpp})

target_link_libraries(RealEngine ${PROJECT_SOURCE_DIR}/libs/glfw3.dll ${PROJECT_SOURCE_DIR}/libs/libfreetyped.a)
