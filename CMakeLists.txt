cmake_minimum_required(VERSION 3.16)

project(snow_main)

add_subdirectory(imgui)
add_subdirectory(snow)
add_subdirectory(sandbox)

file(COPY snow/assets DESTINATION "${CMAKE_BINARY_DIR}/sandbox")
