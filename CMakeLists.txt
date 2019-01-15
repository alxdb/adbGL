cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.11)
project(adbGL)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(SOIL REQUIRED)

add_subdirectory(Core)

add_library(adbGL SHARED $<TARGET_OBJECTS:Core>)
target_link_libraries(adbGL glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES})

include_directories(Core)

add_executable(playground tests/Playground.cpp)
target_link_libraries(playground adbGL)
add_executable(triangle tests/BasicTriangle.cpp)
target_link_libraries(triangle adbGL)
add_executable(cube tests/BasicCube.cpp)
target_link_libraries(cube adbGL)

configure_file(shaders/base.vs.glsl shaders/base.vs.glsl COPYONLY)
configure_file(shaders/base.fs.glsl shaders/base.fs.glsl COPYONLY)
