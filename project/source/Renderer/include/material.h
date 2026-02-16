#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

#include "shader.h"
#include "texture.h"
#include "cubemap.h"

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

            void Use() const;

            void SetShader(Shader* shader);

            void SetTexture(Texture* texture);
            void SetCubemap(CubeMap* cubemap);

            Shader* GetShader() const;

            Texture* GetTexture() const;
            CubeMap* GetCubeMap() const;

            bool HasTexture() const;
            bool HasCubeMap() const;

        private:
            Shader* shader;

            Texture* texture;
            CubeMap* cubemap;
    };
}

#endif
