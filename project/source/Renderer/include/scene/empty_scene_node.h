#pragma once

#include "renderer/render_commands.h"
#include "scene/scene_node.h"

namespace Renderer{
    namespace Scene{
        class EmptyNode : public SceneNode{
            using SceneNode::SceneNode;

            void OnRendered(ICommandQueue* commandQueue){};
        };
    }
}
