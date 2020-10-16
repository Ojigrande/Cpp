cmake_minimum_required(VERSION 3.1)

project(02-table)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} "table.cpp")
target_link_libraries (${PROJECT_NAME})
