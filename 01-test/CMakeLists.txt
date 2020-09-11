cmake_minimum_required(VERSION 3.3)

project(01-VoxImplant)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(${PROJECT_NAME} "main.cpp" "rook.cpp" "board.cpp" "barrier.cpp" "point.cpp")
