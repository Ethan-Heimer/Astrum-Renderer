#ifndef MESH_H
#define MESH_H

#include <vector>
namespace Renderer{
    class Mesh{
        public:
            Mesh(float* verticies, unsigned int vert_size, 
                unsigned int* indiceies, unsigned int indicies_size, 
                float* uv_coords, unsigned int uv_size);
    
            ~Mesh();

            Mesh(const Mesh& src);
            Mesh(Mesh&& src);

            void Delete();
    
            unsigned int GetVertexArrayObject() const;

            unsigned int GetIndiciesCount() const;
            unsigned int GetVertexCount() const;
            unsigned int GetUVCount() const;
    
        private:
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;

            std::vector<float> verticies;
            std::vector<unsigned int> indicies;
            std::vector<float> uvs;

            void CreateBuffers();
    };
}

#endif
