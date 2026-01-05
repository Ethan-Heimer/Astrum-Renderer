#include "mesh.h"

#include "glad/glad.h"

#include <vector>
#include <iostream>

Renderer::Mesh::Mesh(float* verticies, unsigned int vert_size,
                    unsigned int* indicies, unsigned int indicies_size,
                    float* uv_coords, unsigned int uv_size)
    : verticies(verticies, verticies + (vert_size/sizeof(float))),
      indicies(indicies, indicies + (indicies_size/sizeof(int))),
      uvs(uv_coords, uv_coords + (uv_size/sizeof(float))){

    CreateBuffers();
}

Renderer::Mesh::~Mesh(){
    Delete();
}

Renderer::Mesh::Mesh(const Mesh& src) 
    : verticies(src.verticies), indicies(src.indicies), uvs(src.uvs){

    CreateBuffers();
}

Renderer::Mesh::Mesh(Mesh&& src) 
    : verticies(std::move(src.verticies)), indicies(std::move(src.indicies)), 
      uvs(std::move(src.uvs)){ 

    src.Delete();

    CreateBuffers();
}

unsigned int Renderer::Mesh::GetVertexCount() const{
    return verticies.size();
}

unsigned int Renderer::Mesh::GetIndiciesCount() const{
    return indicies.size();
}

unsigned int Renderer::Mesh::GetUVCount() const{
    return uvs.size();
}

void Renderer::Mesh::Delete(){
    std::cout << "Mesh Delete Called" << std::endl;

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAO);
}

unsigned int Renderer::Mesh::GetVertexArrayObject() const {
    return VAO;
}

void Renderer::Mesh::CreateBuffers(){
    //--Vertex Array Buffer 
    glGenVertexArrays(1, &VAO); 

    //--Vertex Buffer Object
    glGenBuffers(1, &VBO);

    //--Element Buffer Object
    glGenBuffers(1, &EBO);

    //--Merge Vert data and UV data
    const int verticiesDepth = 3;
    const int UVDepth = 2;
 
    bool useUVs = (uvs.size() > 0);

    int vertexCount = verticies.size() / verticiesDepth;

    std::vector<float> data{};

    for(int i = 0; i < vertexCount; i++){
        for(int j = 0; j < verticiesDepth; j++)
            data.push_back(verticies[(i * verticiesDepth) + j]);

        if(!useUVs)
            continue;

        for(int j = 0; j < UVDepth; j++)
            data.push_back(uvs[(i * UVDepth) + j]);
    }
    

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);

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
