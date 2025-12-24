#include "mesh.h"

#include "glad/glad.h"

#include <vector>
#include <iostream>

Renderer::Mesh::Mesh(float* verticies, unsigned int vert_size,
                    unsigned int* indicies, unsigned int indicies_size,
                    float* uv_coords, unsigned int uv_size){
    //--Vertex Array Buffer 
    glGenVertexArrays(1, &VAO); 

    //--Vertex Buffer Object
    glGenBuffers(1, &VBO);

    //--Element Buffer Object
    glGenBuffers(1, &EBO);

    //--Merge Vert data and UV data
    const int verticiesDepth = 3;
    const int UVDepth = 2;

    int vertexCount = (vert_size/sizeof(float))/verticiesDepth;
    
    bool useUVs = (uv_size > 0);

    std::vector<float> data{};
    for(int i = 0; i < vertexCount; i++){
        for(int j = 0; j < verticiesDepth; j++)
            data.push_back(verticies[(i * verticiesDepth) + j]);

        if(!useUVs)
            continue;

        for(int j = 0; j < UVDepth; j++)
            data.push_back(uv_coords[(i * UVDepth) + j]);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_size, indicies, GL_STATIC_DRAW);

    const size_t vertexOffset = 0;
    const size_t UVOffset = 3 * sizeof(float);

    size_t stride = 3 * sizeof(float);
    if(useUVs)
        stride += 2 * sizeof(float); //adds UV size to stride

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)vertexOffset);
    glEnableVertexAttribArray(0);

    if(useUVs){    
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)UVOffset);
        glEnableVertexAttribArray(1);
    }
}

Renderer::Mesh::~Mesh(){
    Delete();
}

void Renderer::Mesh::Delete(){
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAO);
}

unsigned int Renderer::Mesh::GetVertexArrayObject() const {
    return VAO;
}

