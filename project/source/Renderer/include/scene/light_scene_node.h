#ifndef LIGHT_SCENE_NODE_H
#define LIGHT_SCENE_NODE_H

#include "light.h"
#include "renderer/render_commands.h"
#include "scene_node.h"

namespace Renderer{
    namespace Scene{
        class LightSceneNode : public SceneNode{
            public:
                LightSceneNode(SceneNode* parent);

                void OnRendered(ICommandQueue* renderer) override;

                void SetAmbient(unsigned char r, unsigned char g, unsigned char b);
                void SetPosition(float x, float y, float z);

            private:
                PointLight light;
        };
    }
}

#endif
