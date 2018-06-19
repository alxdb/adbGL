cmake_minimum_required(VERSION 3.10)
project(adbGL)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(core)

add_library(adbGL SHARED $<TARGET_OBJECTS:core>)
target_link_libraries(adbGL glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

include_directories(core)
add_executable(window tests/WindowTest.cpp)
target_link_libraries(window adbGL)
