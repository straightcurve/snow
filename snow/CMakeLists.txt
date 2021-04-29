# Project definition
cmake_minimum_required(VERSION 3.16)
project(snow)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(LIB_DIR "external")

file(GLOB SOURCES
        src/**/**/**/*.h
        src/**/**/**/*.cpp
        src/**/**/*.h
        src/**/**/*.cpp
        src/**/*.h
        src/**/*.cpp
        src/*.h
        src/*.cpp
        )

# Library definition and properties
add_library(snow STATIC ${SOURCES})
target_include_directories(snow PUBLIC src)
target_include_directories(snow PUBLIC ../imgui)
target_include_directories(snow PUBLIC external/glm/glm)
target_include_directories(snow PUBLIC external/stb)
target_link_libraries(snow imgui)

# PCH
target_precompile_headers(snow PRIVATE src/pch.h)

# spdlog
set(SPDLOG_DIR "${LIB_DIR}/spdlog")
target_include_directories(snow PUBLIC "${SPDLOG_DIR}/include")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(snow "glfw" "${GLFW_LIBRARIES}")
target_include_directories(snow PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(snow PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(snow PRIVATE "${GLAD_DIR}/include")
target_link_libraries(snow "glad" "${CMAKE_DL_LIBS}")
#target_compile_options(glad PRIVATE -fPIC)
