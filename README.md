# adbGL

## Summary
A simple openGL library, for sane people.

## Requirements
- GLFW
- GLEW
- GLM

## Optimization notes
At the moment, most bindings done inside functions are unbound at the end of the
function. It could alternatively be assumed that the correct bindings will be
made when they need to be made, and that the global gl state should not affect
the state of the objects. Not sure how much performance will be gained by
removing the unbinds.

This actually causes problems regardless...
