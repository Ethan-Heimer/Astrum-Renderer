# Astrum Renderer 
![A Wave Rendered with Astrum](wave.png)

# Introduction
Astrum is a basic 3D renderer scriptable with lua. It takes in an input script
That defines the behavior of the renderer.

One of the biggest goals with Astrum is to provide a very basic and intuitive 3D
rendering interface that anyone with any skill level can use. Because of this, Lua
scripts are used to provide a high level interface to Astrum's rendering capabilities.

# Install

## Dependendicies

- OpenGL
- GLFW
- GLM
- Lua
- Assimp

(The Initial Build Might Take Some Time!)

## Building

```
git clone --recurse-submodules https://github.com/Ethan-Heimer/Astrum-Renderer
cd Astrum-Renderer
mkdir build && cd build
cmake ..
make
```

alternativly:

```
git clone --recurse-submodules https://github.com/Ethan-Heimer/Astrum-Renderer
cd Astrum-Renderer
mkdir build
./build.sh
```
The binary can be found in `./build/bin/`

# Use

Starting the renderer is very simple:

```
./Astrum -s {script-name}.lua
```

Astrum will execute the script inputted.

# API

There's a lot that renderer's can do, therefore, Astrum's API is split into multiple 
**Sub-API's**.

## Getting Started

When a script is ran with Astrum, it will first seek out 2 special user-defined
functons: `Start` and `Update`. 
### -- Start --
``` lua
function Start()

end
```

**`Start` Runs once when the script is loaded.**

`Start` is called only once when a script is **Loaded** or **Reloaded (Saved)**.
`Start` is intened to be used to initialize Astrum's initial state, i.e. define
global variable's values and create objects that will be persistant through Astrum's 
lifespan.


### -- Update --
``` lua 
function Update()

end
```

**`Update` Runs Continuously.**

`Update` is called throughout the life span of Astrum. `Update`'s
pourpose is to **Change** the state of the script, gloabl variables, and Astrum
objects. 

These are **Anchors**, and Astrum's way of interacting with the provided lua
script. All code that uses any of Asrtum's api should be placed in these functions.

## Mesh

| Sub-API Name  | Description              |
| ------------- | ------------------------ |
| None          | Create and Mutate Meshs  |

### -- Cube --

**Description:** Creates A Cube Mesh.

**Arguments:** None.

**Returns:**

| Description                                   | Type     |
| --------------------------------------------- | -------- |
| A Table of Child Functions to Mutate The Mesh | Table    |

**Children Functions**

| Signurature        |
-------------------- |
| Translate(x, y, z) |
| Scale(x, y, z)     |
| Rotate(x, y, z)    |
| Color(r, g, b)     |
| Diffuse(r, g, b)   |
| Specular(r, g, b)  |
| Shine(value)       |
| Texture(path)      |

**Example**

``` lua
function Start()
    local cube = Cube();
end
```

<br>

### -- Model --

**Description:** Imports a 3d Model.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| The Path of the 3D Model        | String  |

**Returns:**

| Description                                    | Type     |
| ---------------------------------------------- | -------- |
| A Table of Child Functions to Mutate The Model | Table    |

**Children Functions**

| Signurature        |
-------------------- |
| Translate(x, y, z) |
| Scale(x, y, z)     |
| Rotate(x, y, z)    |

**Example**

``` lua
function Start()
    local model = Model("./assets/model.obj")a
end
```

<br>

### -- .Translate --

**Description:** Moves a Mesh Or Model.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| X Position                      | Number  |
| Y Position                      | Number  |
| Z Position                      | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}

function Start()
    cube = Cube()
    cube.Translate(10, 0, 1)
end
```

<br>

### -- .Rotate --

**Description:** Rotates a Mesh Or Model.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| X Angle                         | Number  |
| Y Angle                         | Number  |
| Z Angle                         | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}

function Start()
    cube = Cube()
    cube.Rotate(45, 20, 1)
end
```

<br>

### -- .Scale --

**Description:** Scales a Mesh Or Model.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| X Scale                         | Number  |
| Y Scale                         | Number  |
| Z Scale                         | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}

function Start()
    cube = Cube()
    cube.Scale(.5, 10, 1)
end
```

<br>

### -- .Color --

**Description:** Changes the color of a mesh;

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}

function Start()
    cube = Cube()
    cube.Color(255, 20, 120);
end
```

<br>

### -- .Texture --

**Description:** Changes a mesh's texture.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Texture Path                    | String  |

**Returns:** None.

**Example**

``` lua
local cube = {}
function Start()
    cube = Cube()
    cube.Texture("Path")
end
```

<br>

### -- .Diffuse --

**Description:** Changes the diffuse attribute of a mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}
function Start()
    cube = Cube()
    cube.Diffuse(255, 20, 120)
end
```

<br>

### -- .Specular --

**Description:** Changes the specular attribute of a mesh;

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}
function Start()
    cube = Cube()
    cube.Specular(255, 20, 120)
end
```

<br>

### -- .Shine --

**Description:** Changes the shininess attribute of the mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Shine                           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = {}
function Start()
    cube = Cube()
    cube.Shine(32)
end
```

<br>

## Light

| Sub-API Name  | Description                   |
| ------------- | ----------------------------- |
| Light         | Creates lights in the scene.  |

### -- Point --

**Description:** Creates a Point Light

**Arguments:** None.

**Returns:** 

| Description                                   | Type     |
| --------------------------------------------- | -------- |
| A Table of Child Functions to Mutate The Mesh | Table    |

**Children Functions**

| Signurature        |
| ------------------ |
| Position(x, y, z)  |
| Color(r, g, b)     |

**Example**

``` lua
function Start()
    local light = Light.Point();
end
```

<br>

### -- .Color --

**Description:** Changes a point light's color.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Red (r)                         | Number [0-255]    |
| Green (g)                       | Number [0-255]    |
| Blue (b)                        | Number [0-255]    |

**Returns:** None.

**Example**

``` lua
function Start()
    local light = Light.Point();
    light.Color(255, 0, 0)
end
```

<br>

### -- .Position --

**Description:** Changes a point light's position.

**Arguments:** 

| Description             | Type              |
| ------------------------| ----------------- |
| x                       | Number            |
| y                       | Number            |
| z                       | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    local light = Light.Point();
    light.Position(10, 0, 1);
end
```

<br>

## Scene

| Sub-API Name  | Description                   |
| ------------- | ----------------------------- |
| Scene         | Edit Scene Attributes.        |

### -- SetBackgroundColor --

**Description:** Set The Background Color of The Scene.

<code style="color : green">Test</code>

**Arguments:**

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Red (r)                         | Number [0-255]    |
| Green (g)                       | Number [0-255]    |
| Blue (b)                        | Number [0-255]    |
| Alpha (a)                       | Number [0-1]      |

**Returns:** None.

**Example**

``` lua
function Start()
    Scene.SetBackgroundColor(50, 50, 50, 1);
end
```

<br>

### -- SetLightDirection --

**Description:** Changes the Scene's Directional Light's Direction.

**Arguments:** 

| Description             | Type              |
| ------------------------| ----------------- |
| x                       | Number            |
| y                       | Number            |
| z                       | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    Scene.SetLightDirection(.9, .1, 0);
end
```

<br>

### -- SetLightColor --

**Description:** Changes the Scene's Directional Light's Color.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Red (r)                         | Number [0-255]    |
| Green (g)                       | Number [0-255]    |
| Blue (b)                        | Number [0-255]    |

**Returns:** None.

**Example**

``` lua
function Start()
    Scene.SetLightColor(200, 100, 50);
end
```

### -- SetLightSpecularColor --

**Description:** Changes the Scene's Directional Light's Specular Color.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Red (r)                         | Number [0-255]    |
| Green (g)                       | Number [0-255]    |
| Blue (b)                        | Number [0-255]    |

**Returns:** None.

**Example**

``` lua
function Start()
    Scene.SetLightSpecularColor(200, 100, 50);
end
```

<br>

### -- SetLightDiffuseColor --

**Description:** Changes the Scene's Directional Light's Diffuse Color.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Red (r)                         | Number [0-255]    |
| Green (g)                       | Number [0-255]    |
| Blue (b)                        | Number [0-255]    |

**Returns:** None.

**Example**

``` lua
function Start()
    Scene.SetLightDiffuseColor(200, 100, 50);
end
```

<br>

## Input

| Sub-API Name  | Description                  |
| ------------- | ---------------------------- |
| Input         | Get Keyboard and Mouse Input |

### Globals

**Key Codes**

| Name          | Value |
| ------------- | ----: |
| Space_Key     | 32    |
| 0_Key         | 48    |
| 1_Key         | 49    |
| 2_Key         | 50    |
| 3_Key         | 51    |
| 4_Key         | 52    |
| 5_Key         | 53    |
| 6_Key         | 54    |
| 7_Key         | 55    |
| 8_Key         | 56    |
| 9_Key         | 57    |
| A_Key         | 65    |
| B_Key         | 66    |
| C_Key         | 67    |
| D_Key         | 68    |
| E_Key         | 69    |
| F_Key         | 70    |
| G_Key         | 71    |
| H_Key         | 72    |
| I_Key         | 73    |
| J_Key         | 74    |
| K_Key         | 75    |
| L_Key         | 76    |
| M_Key         | 77    |
| N_Key         | 78    |
| O_Key         | 79    |
| P_Key         | 80    |
| Q_Key         | 81    |
| R_Key         | 82    |
| S_Key         | 83    |
| T_Key         | 84    |
| U_Key         | 85    |
| V_Key         | 86    |
| W_Key         | 87    |
| X_Key         | 88    |
| Y_Key         | 89    |
| Z_Key         | 90    |
| Shift_Key     | 340   |

**Cursor Values**

| Name           | Description                                    |
| -------------- | ---------------------------------------------- |
| CursorX        | The Cursor's X Position                        |
| CursorY        | The Cursor's Y Position                        |
| CursorDeltaX   | The Change in the Cursor's X Position          |
| CursorDeltaY   | The Change in the Cursor's Y Position          |

### -- IsKeyPressed --

**Description:** Checks if a keycode is pressed.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Key Code                        | Number (Key Code) |

**Returns:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| If The Key is Pressed           | Bool    |

**Example**

``` lua
function Update()
    if(Input.IsKeyPressed(Input.A_Key)) then
        Print("Key is Pressed")
    end
end
```

<br>

## Camera

| Sub-API Name  | Description                   |
| ------------- | ----------------------------- |
| Camera        | Mutates the Camera's Potition |

### -- Position --

**Description:** Sets the camera's position.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| forward position                | Number            |
| straif position                 | Number            |
| up position                     | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    Camera.Position(10, 0, 0)
end
```

<br>

### -- Move --

**Description:** Increments the camera's position.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| forward position                | Number            |
| straif position                 | Number            |
| up position                     | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    Camera.Move(10, 0, 0)
end
```

<br>

### -- Rotate --

**Description:** Rotates the camera.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| pitch                           | Number            |
| yaw                             | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    Camera.Rotate(45, 10)
end
```

<br>

### -- Zoom --

**Description:** Changed the camera's FOV.

**Arguments:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| zoom                            | Number            |

**Returns:** None.

**Example**

``` lua
function Start()
    Camera.Zoom(90)
end
```

<br>

### -- GetRotation --

**Description:** Returns the current rotation of the camera.

**Arguments:** None.

**Returns:** 

| Description                     | Type              |
| ------------------------------- | ----------------- |
| Pitch Rotation                  | Number            |
| Yaw Rotation                    | Number            |


**Example**

``` lua
function Start()
    local pitch, yaw = Camera.GetRotation()
end
```

<br>

## Debug

| Sub-API Name  | Description                           |
| ------------- | ------------------------------------- |
| Debug         | Provides Basic Debugging Information. |

### -- GetFPS --

**Description:** Returns the FPS of the Program.

**Arguments:** None.

**Returns:**

| Description                     | Type              |
| ------------------------------- | ----------------- |
| FPS                             | Number            |

**Example**

``` lua
function Update()
    local fps = Debug.GetFPS();
    print(fps);
end
```

<br>

### -- StartTimer --

**Description:** Starts a timer for debugging how long something takes to execute.

**Arguments:** None.

**Returns:** None.

**Example**

``` lua
function Start()
    Debug.StartTimer();
end
```

<br>

### -- EndTimer --

**Description:** Ends a debugging Timer and Returns the Result in Milliseconds.

**Arguments:** None.

**Returns:** 

| Description                                             | Type              |
| ------------------------------------------------------- | ----------------- |
| Returns Time since a StartTimer() call in Milliseconds. | Number            |

**Example**

``` lua
function Start()
    Debug.StartTimer();

    for i=0, 30 do
        Cube();
    end

    local result = Debug.EndTimer();
    print(result);
end
```

<br>

