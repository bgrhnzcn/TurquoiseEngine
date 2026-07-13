set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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

# Fetch Assimp
FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG v6.0.5
)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "")
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(assimp)


add_library(imgui STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_demo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_tables.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(imgui PUBLIC glfw)

target_include_directories(
	imgui
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
)

# Create a GLAD library from single header one.
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/src/glad_impl.c)
target_include_directories(
	glad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/inc/
)

# Find System OpenGL
find_package(OpenGL REQUIRED)

# 4. Manually Define Source Files (.cpp only)
set(SOURCES
	# Core
	src/core/engine.cpp
	src/core/window.cpp
	# Core/Input
	src/core/input/input.cpp
	src/core/input/key_code.cpp
	# Core/Math
	src/core/math/mat4.cpp
	# Core/Util
	src/core/util/time.cpp
	src/core/util/logger.cpp
	# Core/Asset
	src/core/asset/mesh.cpp
	src/core/asset/mesh_data.cpp
	src/core/asset/model.cpp
	src/core/asset/model_loader.cpp
	# Core/Resources

	# Core/Render
	src/core/render/program.cpp
	src/core/render/shader.cpp
	src/core/render/camera.cpp
)

# 5. Define the Executable Target using ${PROJECT_NAME}
add_library(engine ${SOURCES})

# 6. Include Headers Directory
target_include_directories(
	engine
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# 7. Set Required Compiler Flags (Conditional -Werror)
if (MSVC)
	target_compile_options(engine PRIVATE
		/W4
		$<$<CONFIG:Release>:/WX>
		/std:c++latest
	)
else()
	target_compile_options(engine PRIVATE
		-Wall
		-Wextra
		$<$<CONFIG:Release>:-Werror>
	)
endif()

target_compile_definitions(engine PRIVATE GLFW_INCLUDE_NONE)

# 8. Link Dependencies using ${PROJECT_NAME}
target_link_libraries(engine PUBLIC
	glfw
	assimp
	imgui
	glad
	OpenGL::GL
)
