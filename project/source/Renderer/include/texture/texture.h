#pragma once

#include "texture/texture_interface.h"

#include "shader.h"
#include <string>

namespace Renderer{
    class Texture : public ITexture{
        public:
            Texture(unsigned int width, unsigned int height);
            Texture(std::string imagePath);

            ~Texture();

            void Use(Shader* shader) override;
            void Delete() override;

            unsigned int GetTextureID() const override;
    };
}
