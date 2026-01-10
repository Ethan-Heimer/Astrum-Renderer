#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

#include "shader.h"
#include "texture.h"

namespace Renderer{
    class Material{
        public:
            glm::vec3 Ambient{1, 1, 1};
            glm::vec3 Diffuse{1, 1, 1};
            glm::vec3 Specular{1, 1, 1};
            float Shininess = 32;

            Material(Shader* shader);
            Material(const Material& src);
            Material(Material&& src);

            void SetShader(Shader* shader);
            void SetTexture(Texture* texture);

            Shader* GetShader() const;
            Texture* GetTexture() const;

            bool HasTexture() const;

        private:

            Shader* shader;
            Texture* texture;
    };
}

#endif
