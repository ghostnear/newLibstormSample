# Project for the library.
project(Storm)

# Get source files.
file(
	GLOB_RECURSE
	SOURCE_FILES
		"source/*.cpp"
)

# Add the library.
add_library(
	${PROJECT_NAME}
	${SOURCE_FILES}
)

# Add the include directory.
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
		"include/"
	PRIVATE
		"include/Storm"
)

# Set cpp standard.
set_property(
	TARGET ${PROJECT_NAME}
	PROPERTY
	CXX_STANDARD 20
)


# Platform specific defines and links.
add_compile_definitions("BUILD_TYPE_${BUILD_PLATFORM}")

if(${BUILD_PLATFORM} MATCHES "WINDOWS")
	target_link_libraries(
		${PROJECT_NAME}
		PUBLIC
			ws2_32.lib
	)
endif()

# Cross-platform libraries.
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		GLEW::GLEW
		OpenGL::GL glm::glm
		Freetype::Freetype
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)