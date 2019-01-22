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

add_subdirectory(examples)

