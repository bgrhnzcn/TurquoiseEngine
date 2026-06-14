cmake_minimum_required(VERSION 3.25)

project(turquoise LANGUAGES C CXX)

cmake_policy(SET CMP0205 NEW)

# 1. Set C++26 Standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 2. Default to Debug mode if no build type is specified
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

add_subdirectory(engine)
add_subdirectory(editor)
