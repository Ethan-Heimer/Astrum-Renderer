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

            private:
                glm::vec3 skyColor;  

        };
    }
}

#endif
