#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace Renderer{
    class Texture{
        public:
            Texture(std::string imagePath);

            ~Texture();

            void Delete();

            unsigned int GetTextureID() const;

        private:
            unsigned int textureID;
    };
}

#endif
