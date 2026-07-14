cmake_minimum_required(VERSION 3.25)

project(turquoise LANGUAGES C CXX)

if (MSVC)
	set(CMAKE_CXX_STANDARD 23)
else()
	set(CMAKE_CXX_STANDARD 26)
endif()

if (POLICY CMP0205)
	cmake_policy(SET CMP0205 NEW)
endif()

# 1. Set C++26 Standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Default to Debug mode if no build type is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
	set(CMAKE_BUILD_TYPE "RelWithDebInfo"
		CACHE STRING "Choose the type of build." FORCE
	)
	# Set the possible values for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE
		PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
endif()

add_subdirectory(engine)
add_subdirectory(editor)

target_compile_definitions(engine PRIVATE
	$<$<CONFIG:Debug>:DEBUG_TAG>
)
target_compile_definitions(editor PRIVATE
	PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
	$<$<CONFIG:Debug>:DEBUG_TAG>
)

