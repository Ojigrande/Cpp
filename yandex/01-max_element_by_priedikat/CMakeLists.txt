cmake_minimum_required(VERSION 3.1)

project(01-max_element_by_priedikat)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} "test_runner.h" "max_element_if.cpp")
target_link_libraries (${PROJECT_NAME})
