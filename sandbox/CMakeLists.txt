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

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

add_executable(sandbox ${SOURCES})
target_link_libraries(sandbox PUBLIC snow ${X11_LIBRARIES} -lXcomposite -lXrender)
add_compile_definitions(SNOW_ENABLE_ASSERTS=TRUE)
