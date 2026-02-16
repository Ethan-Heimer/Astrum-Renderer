#pragma once

#include <string>
#include "shader.h"

using namespace std;

namespace Renderer{
    class CubeMap{
        public:
            CubeMap(const string& basePath, const string& fileType);
            ~CubeMap();

            void Delete();
            void Use(Shader* shader);
            
        private:
            unsigned int texture;
    };
}
