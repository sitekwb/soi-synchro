cmake_minimum_required(VERSION 3.12)
project(monitors)

include_directories(include)
include_directories(/usr/local/include)
set(CMAKE_CXX_STANDARD 11)

#set(SOURCES src/Buffer.cpp src/Consumer.cpp src/main.cpp src/Monitor.cpp src/Person.cpp src/Producer.cpp)
file(GLOB SOURCES "src/*.cpp")


add_executable(monitor main.cpp ${SOURCES})

add_executable(test test_main.cpp ${SOURCES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(test_debug test_main.cpp ${SOURCES})
add_executable(monitor_debug main.cpp ${SOURCES})


