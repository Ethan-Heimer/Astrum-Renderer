#pragma once

#include "scene/scene_node.h"
#include "glm/glm.hpp"

using namespace glm;

namespace Renderer{
    namespace Scene{
        class RootSceneNode : public SceneNode{
            public:
                RootSceneNode(SceneNode* parent);

                void OnRendered(ICommandQueue* commandQueue) override;

                void SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b);
                void SetDirectionalLightDirection(float x, float y, float z);
                void SetDirectionalAmbientColor(const unsigned char r, const unsigned char g, const unsigned char b);
                void SetDirectionalSpecularColor(const unsigned char r, const unsigned char g, const unsigned char b);
                void SetDirectionalDiffuseColor(const unsigned char r, const unsigned char g, const unsigned char b);

            private:
                vec3 skyColor{0, 0, 0};  

                vec3 dirLightDirection{1, 0, 1};  
                vec3 dirLightAmbient{255, 255, 255};  
                vec3 dirLightSpecular{255, 255, 255};  
                vec3 dirLightDiffuse{255, 255, 255};  
        };
    }
}
