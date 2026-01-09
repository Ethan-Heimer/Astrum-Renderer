#include "mesh.h"

#include "glad/glad.h"
#include "glm/exponential.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float3.hpp"

#include <complex>
#include <vector>
#include <iostream>

Renderer::Mesh::Mesh(float* verticies, unsigned int vert_size,
                    float* uv_coords, unsigned int uv_size,
                    float* normals, unsigned int normal_size,
                    unsigned int* indicies, unsigned int indicies_size)
    : indicies(indicies, indicies + (indicies_size/sizeof(int))){

    size_t vertex_size = vert_size/sizeof(float)/3;
    this->verticies.resize(vertex_size);

    // -- Fill Vertex Data
    for(int i = 0; i < vertex_size; i++){
        float x = verticies[i * 3];
        float y = verticies[i * 3 + 1];
        float z = verticies[i * 3 + 2];

        this->verticies[i].Position = glm::vec3(x, y, z);

        float nx = normals[i * 3];
        float ny = normals[i * 3 + 1];
        float nz = normals[i * 3 + 2];

        this->verticies[i].Normal = glm::vec3(nx, ny, nz);

        float u = uv_coords[i * 2];
        float v = uv_coords[i * 2 + 1];

        this->verticies[i].Uv = glm::vec2(u, v);
    }

    CreateBuffers();
}

Renderer::Mesh::Mesh(float* verticies, unsigned int vert_size,
                    float* uv_coords, unsigned int uv_size,
                    unsigned int* indicies, unsigned int indicies_size)
    : indicies(indicies, indicies + (indicies_size/sizeof(int))){

    size_t vertex_size = vert_size/sizeof(float)/3;
    this->verticies.resize(vertex_size);

    // -- Fill Vertex Data
    for(int i = 0; i < vertex_size; i++){
        float x = verticies[i * 3];
        float y = verticies[i * 3 + 1];
        float z = verticies[i * 3 + 2];

        this->verticies[i].Position = glm::vec3(x, y, z);

        float u = uv_coords[i * 2];
        float v = uv_coords[i * 2 + 1];

        this->verticies[i].Uv = glm::vec2(u, v);
    }

    CalculateVertexNormals();

    CreateBuffers();
}

Renderer::Mesh::~Mesh(){
    Delete();
}

Renderer::Mesh::Mesh(const Mesh& src) 
    : verticies(src.verticies), indicies(src.indicies){

    CreateBuffers();
}

Renderer::Mesh::Mesh(Mesh&& src) 
    : verticies(std::move(src.verticies)), indicies(std::move(src.indicies)){ 

    src.Delete();

    CreateBuffers();
}

unsigned int Renderer::Mesh::GetVertexCount() const{
    return verticies.size();
}

unsigned int Renderer::Mesh::GetIndiciesCount() const{
    return indicies.size();
}

void Renderer::Mesh::Delete(){
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

    size_t vertexCount = verticies.size();

    std::vector<float> data{};
    for(int i = 0; i < vertexCount; i++){
        data.push_back(verticies[i].Position.x);
        data.push_back(verticies[i].Position.y);
        data.push_back(verticies[i].Position.z);

        data.push_back(verticies[i].Uv.x);
        data.push_back(verticies[i].Uv.y);

        data.push_back(verticies[i].Normal.x);
        data.push_back(verticies[i].Normal.y);
        data.push_back(verticies[i].Normal.z);
    }
    

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);

    const size_t vertexOffset = 0;
    const size_t UVOffset = 3 * sizeof(float);
    const size_t normalOffset = 5 * sizeof(float);

    size_t stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)vertexOffset);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)UVOffset);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffset);
    glEnableVertexAttribArray(2);
}

void Renderer::Mesh::CalculateVertexNormals(){
    // -- 1 Iterate Throught Each Face (A face is every three indicie value)
    for(int i = 0; i < indicies.size(); i+=3){
        // -- 2 Calculate Face Normal
        unsigned int index_1 = indicies[i];
        unsigned int index_2 = indicies[i+1];
        unsigned int index_3 = indicies[i+2];

        Vertex& vertex_1 = verticies[index_1];
        Vertex& vertex_2 = verticies[index_2];
        Vertex& vertex_3 = verticies[index_3];


        glm::vec3 edge_1 = vertex_2.Position - vertex_1.Position;
        glm::vec3 edge_2 = vertex_3.Position - vertex_1.Position;

        glm::vec3 faceNormal = glm::cross(edge_1, edge_2);

        // -- 3 sum face normals 
        std::cout << "Face Normal" << faceNormal.x << faceNormal.y << faceNormal.z << std::endl;

        vertex_1.Normal += faceNormal;
        vertex_2.Normal += faceNormal;
        vertex_3.Normal += faceNormal;

        std::cout << vertex_1.Normal.x << vertex_1.Normal.y << vertex_1.Normal.z << std::endl;

        std::cout << std::endl;
    }
    
    for(auto& vertex : verticies){
        vertex.Normal = glm::normalize(vertex.Normal);
        std::cout << vertex.Normal.x << vertex.Normal.y << vertex.Normal.z << std::endl;
    }

    std::cout << std::endl;


}
