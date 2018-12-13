cmake_minimum_required(VERSION 3.12)
project(monitors)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "src/*")
set(CMAKE_CXX_FLAGS "-I/usr/local/include")

add_executable(monitor ${SOURCES})