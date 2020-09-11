cmake_minimum_required(VERSION 3.1)

project(games)

# Setting output directories
# Runtime output directory
# -----------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin.debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin.release")
# -----------------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin.debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin.release")

# Add project collections to build tree.
# -----------------------------------------------------------------------
add_subdirectory(01-max_element_by_priedikat)
