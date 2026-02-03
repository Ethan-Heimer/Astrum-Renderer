#pragma once

#include "model.h"
#include "renderer/render_commands.h"
#include "scene_node.h"
#include "transform.h"

namespace Renderer{
    namespace Scene{
        class ModelSceneNode : public SceneNode{
            public:
                ModelSceneNode(SceneNode* parent, Model* model);

                void OnRendered(ICommandQueue* commandQueue) override;
            private:
                Model* model;
                Transform transform{};
        };
    }
}
