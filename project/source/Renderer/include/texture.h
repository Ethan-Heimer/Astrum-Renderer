#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace Renderer{
    class Texture{
        public:
            Texture(unsigned int width, unsigned int height);
            Texture(std::string imagePath);

            ~Texture();

            void Delete();

            unsigned int GetTextureID() const;

        private:
            unsigned int textureID;
    };
}

#endif
