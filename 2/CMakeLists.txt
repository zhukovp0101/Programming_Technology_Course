cmake_minimum_required(VERSION 2.8)
project(TP_2)

add_subdirectory(B)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(SOURCES_LIST C/main.cpp)

execute_process(COMMAND python3 
A/preparing.py )

add_executable(TP_2 ${SOURCES_LIST})