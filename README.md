# FurSystem
## NCCA Innovations assignment

## Build Instructions
run `qmake` or `qmake-qt5`
run `make -j 8`

## Usage Instructions
run `./FurSystem`

### Controls
Right Click in the Node Graph to create nodes.
Left Click in the viewport to rotate the camera.
Arrow keys move the point at which the camera orbits around.
'C' key resets the camera.
'L' key or the 'Load' button loads a preset node graph.
'S' key or the 'Save' button saves the current node graph.
'R' key recompiles all shaders (used for testing purposes).

Note: Upon loading presets, you will need to change the path specified in the OBJ loader node so that it points to any of the meshes in the `meshes/` directory, or to the OBJ files provided.
