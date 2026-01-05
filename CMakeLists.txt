# g++ -I ./include -o test main.cpp glad.cpp 
# -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl

cmake_minimum_required(VERSION 3.10)

set(NAME Renderer)
project(${NAME} VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard (e.g., C++17, C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Grab All  Source Files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/project/source/*.cpp")

# Add source files for the executable
add_executable(${NAME}
    project/libs/glad.cpp
    ${SOURCE_FILES}
)

message("Ensuring Json Parser is installed")

include(FetchContent)
FetchContent_Declare(
    Json
    GIT_REPOSITORY "https://github.com/nlohmann/json"
    GIT_TAG "origin/master"
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/project/libs/external/json"
)
FetchContent_MakeAvailable(Json)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Renderer/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Utils/include
)

target_include_directories(${NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/project/source/Core/include
)

target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/external/json/include)
target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/project/libs/include)

# Lua and GLFW are libs that need to be installed. 

target_link_libraries(${NAME} glfw)
target_link_libraries(${NAME} GLU)
target_link_libraries(${NAME} GL)
target_link_libraries(${NAME} Xrandr)
target_link_libraries(${NAME} Xxf86vm)
target_link_libraries(${NAME} Xi)
target_link_libraries(${NAME} Xinerama)
target_link_libraries(${NAME} X11)
target_link_libraries(${NAME} rt)
target_link_libraries(${NAME} dl)
target_link_libraries(${NAME} lua)


file(COPY "${CMAKE_SOURCE_DIR}/project/source/assets/"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
)

file(COPY "${CMAKE_SOURCE_DIR}/project/source/shaders/"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders"
)

