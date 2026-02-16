#pragma once

#include "texture_interface.h"
#include "shader.h"

#include <string>

using namespace std;

namespace Renderer{
    class CubeMap : public ITexture{
        public:
            CubeMap(const string& basePath, const string& fileType);
            ~CubeMap();

            void Delete() override;
            void Use(Shader* shader) override;

            unsigned int GetTextureID() const override;        
    };
}
