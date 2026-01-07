#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

#include "shader.h"
#include "texture.h"

namespace Renderer{
    class Material{
        public:
            Material(Shader* shader);
            Material(const Material& src);
            Material(Material&& src);

            void SetShader(Shader* shader);
            void SetTexture(Texture* texture);
            void SetColor(float r, float g, float b, float a);

            Shader* GetShader() const;
            Texture* GetTexture() const;
            glm::vec4 GetColor() const;

            bool HasTexture() const;

        private:
            Shader* shader;

            Texture* texture;
            glm::vec4 color;
    };
}

#endif
