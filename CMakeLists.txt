cmake_minimum_required(VERSION 3.20)

project(aoc2021)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 20)
set(CMAKE_C_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
	message(INFO "Defaulting to build type RelWithDeb")
	set(CMAKE_BUILD_TYPE RelWithDeb CACHE FORCE)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

# utility
add_library(utility INTERFACE)
target_include_directories(utility INTERFACE includes)

add_subdirectory("Day01")
add_subdirectory("Day02")
add_subdirectory("Day03")
add_subdirectory("Day04")
add_subdirectory("Day05")

