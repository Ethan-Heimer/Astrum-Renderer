#include "mesh_builder.h"
#include "mesh.h"
#include <algorithm>
#include <memory>

std::unique_ptr<Renderer::Mesh> Renderer::MeshBuilder::Cube(){    
    float vertices[] = {
        0.5f, 0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
    
        0.5f, 0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2,
    
        4, 5, 6,
        4, 7, 6, 
    
        0, 1, 4,
        4, 5, 1,
    
        0, 3, 4,
        4, 7, 3,
    
        2, 3, 6,
        6, 7, 3, 
    
        6, 5, 2,
        5, 2, 1
    };
    
    float uv[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    unsigned int vert_size = sizeof(vertices);
    unsigned int indicies_size = sizeof(indices);
    unsigned int uv_size = sizeof(indices);

    return std::make_unique<Renderer::Mesh>(vertices, vert_size, indices, indicies_size, uv, uv_size);
};
