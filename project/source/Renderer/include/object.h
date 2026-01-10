#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include <memory>
using namespace std;

namespace Renderer{
    class Object{
        public:
            Object(Mesh& mesh, Material& material);
            ~Object();

            Object(const Object& object);
            Object(Object&& object);

            void SetMaterial(Material& material);

            Mesh& GetMesh();
            Transform& GetTransform();

            Material& GetMaterial();

        private:
           unique_ptr<Transform> transform; 
           unique_ptr<Material> material;
           unique_ptr<Mesh> mesh;
    };
}

#endif
