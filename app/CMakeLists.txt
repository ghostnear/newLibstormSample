# Get source files.
file(
	GLOB_RECURSE
	SOURCE_FILES
		"source/*.cpp"
)

# Add executable to the project.
add_executable(
	${PROJECT_NAME}
	${SOURCE_FILES}
)

# Add libraries.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Storm
)

# Add include directories.
target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		"include"
)

# Link libraries.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Storm
)

# Set C++ standard.
set_property(
	TARGET ${PROJECT_NAME}
	PROPERTY
	CXX_STANDARD 20
)

# Platform specific defines.
add_compile_definitions("BUILD_TYPE_${BUILD_PLATFORM}")

# Hide the terminal.
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
	if(${BUILD_PLATFORM} MATCHES "WINDOWS")
		target_link_options(
			${PROJECT_NAME}
			PUBLIC
				/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup
		)
	else()
		target_link_options(
			${PROJECT_NAME}
			PUBLIC
				-mwindows
		)
	endif()
endif()

# TODO: Add tests and install targets if needed.
