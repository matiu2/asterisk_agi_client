CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(AGI)

ADD_DEFINITIONS(-std=c++11 -Wall -Wextra)

add_subdirectory(agi_proxy)

ADD_EXECUTABLE(agi agi_proxy main.cpp)
