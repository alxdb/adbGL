set(EXAMPLES_SRC BasicCube.cpp BasicTriangle.cpp)

foreach(EXAMPLE ${EXAMPLES_SRC})
	get_filename_component(EXAMPLE_EXE ${EXAMPLE} NAME_WE)
	add_executable(${EXAMPLE_EXE} ${EXAMPLE})
	target_link_libraries(${EXAMPLE_EXE} adbGL)
	target_include_directories(${EXAMPLE_EXE} PRIVATE ../)
endforeach(EXAMPLE)

configure_file(shaders/base.vs.glsl shaders/base.vs.glsl COPYONLY)
configure_file(shaders/base.fs.glsl shaders/base.fs.glsl COPYONLY)
configure_file(resources/UV_Grid.jpg resources/UV_Grid.jpg COPYONLY)

