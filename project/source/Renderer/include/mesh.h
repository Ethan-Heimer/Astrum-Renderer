#ifndef MESH_H
#define MESH_H

namespace Renderer{
    class Mesh{
        public:
            Mesh(float* verticies, unsigned int vert_size, 
                unsigned int* indiceies, unsigned int indicies_size, 
                float* uv_coords, unsigned int uv_size);
    
            ~Mesh();

            void Delete();
    
            unsigned int GetVertexArrayObject() const;
            // copy and move eventualy
    
        private:
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;
    };
}

#endif
