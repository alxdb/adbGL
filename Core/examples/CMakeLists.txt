set(EXAMPLES_SRC BasicTriangle.cpp BasicCube.cpp)

foreach(EXAMPLE ${EXAMPLES_SRC})
  get_filename_component(EXAMPLE_EXE ${EXAMPLE} NAME_WE)
  add_executable(${EXAMPLE_EXE} ${EXAMPLE})
  target_link_libraries(${EXAMPLE_EXE} adbGL)
  target_include_directories(${EXAMPLE_EXE} PRIVATE ${ADBGL_INC})
endforeach(EXAMPLE)

set(SHADERS base diffuse)

foreach(SHADER ${SHADERS})
  configure_file(shaders/${SHADER}.vs.glsl shaders/${SHADER}.vs.glsl COPYONLY)
  configure_file(shaders/${SHADER}.fs.glsl shaders/${SHADER}.fs.glsl COPYONLY)
endforeach(SHADER)

set(RESOURCES UV_Grid.jpg)

foreach(RESOURCE ${RESOURCES})
  configure_file(resources/${RESOURCE} resources/${RESOURCE} COPYONLY)
endforeach(RESOURCE)

