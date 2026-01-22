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
- Lua

(I plan on eventually handling these dependicies through cmake)

## Building

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
| None          | Create and Mutate Mesh's |

### -- Cube --

**Description:** Creates A Cube Mesh.

**Arguments:** None.

**Returns:**

| Description                     | Type    |
| ------------------------------- | ------- |
| A reference to the created cube | Address |

**Example**

``` lua
function Start()
    local cube = nil
    cube = Cube()
end
```

<br>

### -- Translate --

**Description:** Moves a Mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| X Position                      | Number  |
| Y Position                      | Number  |
| Z Position                      | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    Translate(cube, 10, 0, 1)
end
```

<br>

### -- Rotate --

**Description:** Rotates a Mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| X Angle                         | Number  |
| Y Angle                         | Number  |
| Z Angle                         | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    Rotate(cube, 45, 20, 1)
end
```

<br>

### -- Scale --

**Description:** Scales a Mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| X Scale                         | Number  |
| Y Scale                         | Number  |
| Z Scale                         | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    Scale(cube, .5, 10, 1)
end
```

<br>

## Material

| Sub-API Name  | Description              |
| ------------- | ------------------------ |
| Material      | Mutate a Mesh's Material |

### -- Of --

**Description:** Gets the material of a mesh.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |

**Returns:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Material Reference              | Address |

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
end
```

<br>

### -- SetColor --

**Description:** Changes a material's color.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
    Material.SetColor(material, 255, 20, 120)
end
```

<br>

### -- SetTexture --

**Description:** Changes a material's texture.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| Texture Path                    | String  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
    Material.SetTexture(material, "Path")
end
```

<br>

### -- SetDiffuse --

**Description:** Changes the diffuse attribute of the material.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
    Material.SetDiffuse(material, 255, 20, 120)
end
```

<br>

### -- SetSpecular --

**Description:** Changes the specular attribute of the material.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| Red Color (0 - 255)             | Number  |
| Blue Color (0 - 255)            | Number  |
| Green Color (0 - 255)           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
    Material.SetSpecular(material, 255, 20, 120)
end
```

<br>

### -- SetShine --

**Description:** Changes the shininess attribute of the material.

**Arguments:** 

| Description                     | Type    |
| ------------------------------- | ------- |
| Mesh Reference                  | Address |
| Shine                           | Number  |

**Returns:** None.

**Example**

``` lua
local cube = nil
function Start()
    cube = Cube()

    local material = Material.Of(cube)
    Material.SetShine(material, 255, 20, 120)
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
