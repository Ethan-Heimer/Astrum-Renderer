#ifndef OBJECT_H
#define OBJECT_H

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include <memory>
using namespace std;

namespace Renderer{
    class Object{
        public:
            Object(Mesh& mesh, Shader& shader);

            Object(const Object& object);
            Object(Object&& object);

            void SetShader(Shader& shader);

            Mesh& GetMesh();
            Transform& GetTransform();

            Shader& GetShader();

        private:
           shared_ptr<Mesh> mesh;
           shared_ptr<Transform> transform; 

           Shader& shader;
    };
}

#endif
