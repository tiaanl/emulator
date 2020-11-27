cmake_minimum_required(VERSION 3.16)

project(emulator)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

include(cmake/utils.cmake)

add_subdirectory(libs)
add_subdirectory(bins)
