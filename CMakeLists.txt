cmake_minimum_required(VERSION 3.10)
project(adbGL)
set(CMAKE_CXX_STANDARD 11)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

add_subdirectory(Core)

add_library(adbGL SHARED $<TARGET_OBJECTS:Core>)
target_link_libraries(adbGL glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

include_directories(Core)

add_executable(playground tests/Playground.cpp)
target_link_libraries(playground adbGL)
add_executable(triangle tests/BasicTriangle.cpp)
target_link_libraries(triangle adbGL)
