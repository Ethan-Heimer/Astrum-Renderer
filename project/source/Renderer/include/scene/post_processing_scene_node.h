#pragma once

#include "renderer/render_commands.h"
#include "scene_node.h"

namespace Renderer{
    namespace Scene{
        class PostProcessingNode : public SceneNode{
            public:
                PostProcessingNode(SceneNode* parent, mat3 kernal);

                void OnRendered(ICommandQueue* renderer) override;

            private:
                mat3 kernal;
        };
    }
}
