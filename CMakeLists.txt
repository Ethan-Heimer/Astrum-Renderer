# g++ -I ./include -o test main.cpp glad.cpp 
# -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl

cmake_minimum_required(VERSION 3.10)

set(NAME Astrum)
project(${NAME} VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard (e.g., C++17, C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set GLFW Build features off
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

# Set LuaJit Dir
set(LUAJIT_DIR "/usr/include/luajit-2.1")
set(LUAJIT_LIB "luajit-5.1")

if(NOT IS_DIRECTORY ${LUAJIT_DIR})
    message("LUA Jit Directiory not found! Please install LuaJIT or place luajit-2.1
    into /usr/include/. Expecting ${LUAJIT_DIR}")
endif()

# Set Use Modern OpenGL
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

#find packages
find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

# Grab All Source Files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/project/source/*.cpp")

# Add source files for the executable
add_executable(${NAME}
    project/libs/glad.cpp
    ${SOURCE_FILES}
)

add_subdirectory(./project/libs/glfw)
add_subdirectory(./project/libs/sol)
add_subdirectory(./project/libs/assimp)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Renderer/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Utils/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/AssetManager/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/include
)

# Core Includes

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/application/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/assetmanager/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/console/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/layers/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/lua/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/exeptions/include
)

target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/sol/include)
target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/include)
target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/glfw/include)
target_include_directories(${NAME} PRIVATE ${LUAJIT_DIR})
target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/assimp/include)

# Found Libs Targets Packages
target_link_libraries(${NAME} PRIVATE OpenGL::OpenGL)
target_link_libraries(${NAME} PRIVATE glfw)
target_link_libraries(${NAME} PRIVATE ${LUAJIT_LIB})
target_link_libraries(${NAME} PRIVATE assimp::assimp)

target_compile_definitions(${NAME} PRIVATE SOL_LUAJIT=1)

file(COPY "${CMAKE_SOURCE_DIR}/project/source/assets/"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
)

file(COPY "${CMAKE_SOURCE_DIR}/project/source/shaders/"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders"
)

