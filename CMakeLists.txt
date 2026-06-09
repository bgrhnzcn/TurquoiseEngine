cmake_minimum_required(VERSION 3.25)

project(game LANGUAGES C CXX)

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

# 3. Automatically Fetch Dependencies (GLFW & GLAD2)
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
				glfw
				GIT_REPOSITORY https://github.com/glfw/glfw.git
				GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(glfw)

# Create a GLAD library from single header one.
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/src/glad_impl.c)
target_include_directories(
	glad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/inc/
)

# Find System OpenGL
find_package(OpenGL REQUIRED)

file(CREATE_LINK
	${CMAKE_CURRENT_SOURCE_DIR}/assets
	${CMAKE_BINARY_DIR}/assets
	SYMBOLIC
	COPY_ON_ERROR
)

# 4. Manually Define Source Files (.cpp only)
set(SOURCES
	src/engine.cpp
	src/input.cpp
	src/key_code.cpp
	src/main.cpp
	src/mat4.cpp
	src/mesh.cpp
	src/model.cpp
	src/program.cpp
	src/shader.cpp
	src/test_engine.cpp
	src/time.cpp
	src/window.cpp
)

# 5. Define the Executable Target using ${PROJECT_NAME}
add_executable(${PROJECT_NAME} ${SOURCES})

# 6. Include Headers Directory
target_include_directories(
	${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# 7. Set Required Compiler Flags (Conditional -Werror)
target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	$<$<CONFIG:Release>:-Werror>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# 8. Link Dependencies using ${PROJECT_NAME}
target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	glad
	OpenGL::GL
)
