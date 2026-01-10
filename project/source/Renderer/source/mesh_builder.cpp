#include "mesh_builder.h"
#include "mesh.h"
#include <algorithm>
#include <memory>

void Renderer::Primatives::Cube(std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies){
    float verts[] = {
        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f, 
        -0.5f, 0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,  
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f,
        
        -0.5f, 0.5f, 0.5f,  
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,  
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f, 
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, 0.5f, -0.5f,  
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, -0.5f,
    };
    
    
    float uvs[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

    };

    float normals[] = {
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,

        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,

        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,

        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    indicies = {
        0, 1, 2,
        3, 4, 5,
    
        6, 7, 8,
        9, 10, 11, 
    
        12, 13, 14,
        15, 16, 17,
    
        18, 19, 20,
        21, 22, 23,
    
        24, 25, 26,
        27, 28, 29, 
    
        30, 31, 32,
        33, 34, 35
    };

    unsigned int vert_size = sizeof(verts);
    unsigned int uv_size = sizeof(uvs);
    unsigned int normal_size = sizeof(normals);
    unsigned int indicies_size = sizeof(indicies);

    //create verticies
    MeshBuilder::CreateVerticies(verticies, verts, vert_size, 
            uvs, uv_size, normals, normal_size);
};


void Renderer::MeshBuilder::CreateVerticies(std::vector<Vertex>& verticies,
                float* verts, unsigned int vert_size,
                float* uvs, unsigned int uv_size,
                float* normals, unsigned int normal_size){

    size_t vertex_size = vert_size/sizeof(float)/3;
    verticies.resize(vertex_size);

    // -- Fill Vertex Data
    for(int i = 0; i < vertex_size; i++){
        float x = verts[i * 3];
        float y = verts[i * 3 + 1];
        float z = verts[i * 3 + 2];

        verticies[i].Position = glm::vec3(x, y, z);

        float nx = normals[i * 3];
        float ny = normals[i * 3 + 1];
        float nz = normals[i * 3 + 2];

        verticies[i].Normal = glm::vec3(nx, ny, nz);

        float u = uvs[i * 2];
        float v = uvs[i * 2 + 1];

        verticies[i].Uv = glm::vec2(u, v);
    }
}
