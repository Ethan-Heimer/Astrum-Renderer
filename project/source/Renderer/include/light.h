#ifndef LIGHT_H
#define LIGHT_H

#include "glm/ext/vector_float3.hpp"
#include "transform.h"
namespace Renderer{
    class Light{
        public:
            glm::vec3 Ambient{1, 1, 1};
            glm::vec3 Diffuse{1, 1, 1};
            glm::vec3 Specular{1, 1, 1};
        private:
    };

    class DirectionalLight : public Light{
        public: 
            glm::vec3 Direction{1, 0, 0};
        private:
    };

    class PointLight : public Light{
        public:
            glm::vec3 Position{0, 0, 0};

            float KConstant = 1;
            float KLinear = 0.09;
            float KQuadratic = 0.032;
        private:
    };

    class SpotLight : public Light{
        public:
            glm::vec3 position;
            glm::vec3 direction;
            float cutOff;
        private:
    };
}

#endif
