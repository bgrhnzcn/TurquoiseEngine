set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(editor
	src/main.cpp
)

target_link_libraries(editor PUBLIC engine)

if (MSVC)
	target_compile_options(editor PRIVATE
		/W4
		$<$<CONFIG:Release>:/WX>
		/std:c++latest
	)
else()
	target_compile_options(editor PRIVATE
		-Wall
		-Wextra
		$<$<CONFIG:Release>:-Werror>
	)
endif()
