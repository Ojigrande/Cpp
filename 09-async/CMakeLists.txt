cmake_minimum_required(VERSION 3.1)

project(09-testasync)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})