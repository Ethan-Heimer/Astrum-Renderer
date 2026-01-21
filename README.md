# Astrum Renderer 
![A Wave Rendered with Astrum](wave.png)

## Introduction
Astrum is a basic 3D renderer scriptable with lua. It takes in an input script
That defines the behavior of the renderer.

## Install

### Dependendicies

- OpenGL
- GLFW
- Lua

(I plan on eventually handling these dependicies throught cmake)

### Building

```
git clone https://github.com/Ethan-Heimer/Astrum-Renderer
cd Astrum-Renderer
mkdir build && cd build
cmake ..
make
```

alternativly:

```
git clone https://github.com/Ethan-Heimer/Astrum-Renderer
cd Astrum-Renderer
mkdir build
./build.sh
```
The binary can be found in `./build/bin/`
