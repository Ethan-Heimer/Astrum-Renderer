#ifndef MESH_H
#define MESH_H

#include <vector>
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"

namespace Renderer{
    class Vertex{
        public:
            glm::vec3 Position{0.0f, 0.0f, 0.0f};
            glm::vec3 Normal{0.0f, 0.0f, 0.0f};
            glm::vec2 Uv{0.0f, 0.0f};
    };

    class Mesh{
        public:
            Mesh(std::vector<Vertex>& verticiesm, std::vector<unsigned int>& indicies);
    
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

            std::vector<Vertex> verticies;
            std::vector<unsigned int> indicies;

            void CreateBuffers();
            void CalculateVertexNormals();
    };
}

#endif
