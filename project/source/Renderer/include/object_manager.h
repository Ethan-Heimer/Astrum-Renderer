#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "material.h"
#include "mesh.h"
#include "transform.h"
#include <memory>
#include <vector>
#include <object.h>

using namespace std;

namespace Renderer{
    class ObjectManager{
        public:
            Object& CreateObject(Mesh& mesh, Material& shader);
            void Clear();

        private:
            vector<unique_ptr<Object>> objects;
        
    };
}

#endif
