#pragma once

#include "shader.h"

namespace Renderer{
    class ITexture{
        public:
            ITexture(){}
            ~ITexture(){}

            virtual void Use(Shader* shader) = 0;
            virtual void Delete() = 0;

            virtual unsigned int GetTextureID() const = 0;

        protected:
            unsigned int textureID;
    };
}
