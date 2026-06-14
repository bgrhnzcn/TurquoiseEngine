set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(editor
	src/main.cpp
)

target_link_libraries(editor PUBLIC engine)
