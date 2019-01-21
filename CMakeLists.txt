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

set(EXAMPLES Playground BasicTriangle BasicCube)

foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} examples/${EXAMPLE}.cpp)
	target_link_libraries(${EXAMPLE} adbGL)
	target_include_directories(${EXAMPLE} PRIVATE Core)
endforeach(EXAMPLE)

configure_file(shaders/base.vs.glsl shaders/base.vs.glsl COPYONLY)
configure_file(shaders/base.fs.glsl shaders/base.fs.glsl COPYONLY)
