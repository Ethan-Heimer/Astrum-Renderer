#ifndef ROOT_SCENE_NODE_H
#define ROOT_SCENE_NODE_H

#include "scene/scene_node.h"
#include "glm/glm.hpp"

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
                glm::vec3 skyColor{0, 0, 0};  

                glm::vec3 dirLightDirection{1, 0, 1};  
                glm::vec3 dirLightAmbient{255, 255, 255};  
                glm::vec3 dirLightSpecular{255, 255, 255};  
                glm::vec3 dirLightDiffuse{255, 255, 255};  
        };
    }
}

#endif
