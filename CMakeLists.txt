cmake_minimum_required(VERSION 3.12)
project(t3 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-lpthread")

include_directories(.)


add_executable(t3
        sem.h queue.h main.c)
