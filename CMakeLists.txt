cmake_minimum_required(VERSION 3.17)

project(emulator)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

include(cmake/utils.cmake)

add_subdirectory(libs)
add_subdirectory(bins)
