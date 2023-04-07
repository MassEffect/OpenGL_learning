cmake_minimum_required(VERSION 3.24)

project(lesson1)

add_executable(lesson1 	source/main.cpp						
			 )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.3.8)
target_link_libraries(lesson1 glfw)

add_subdirectory(external/glad)
target_link_libraries(lesson1 glad)

add_subdirectory(external/glm)
target_link_libraries(lesson1 glm)