cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

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

add_executable(sandbox ${SOURCES})
target_link_libraries(sandbox PUBLIC snow)
add_compile_definitions(SNOW_ENABLE_ASSERTS=TRUE)
