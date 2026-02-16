#pragma once

#include "texture/texture.h"

namespace Renderer{
    class FrameBuffer{
        public:
            FrameBuffer(unsigned int windowWidth, unsigned int windowHeight);
            ~FrameBuffer();

            void Delete();

            void Use();
            void Disable();

            Texture* GetColorBuffer();

        private:
            unsigned int fbo;
            unsigned int rbo;
            
            Texture texture;

    };
}
