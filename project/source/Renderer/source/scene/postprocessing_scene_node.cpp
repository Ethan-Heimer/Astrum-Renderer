#include "renderer/render_commands.h"
#include "scene/post_processing_scene_node.h"

#include "renderer/renderer.h"
#include <iostream>

using namespace Scene;

PostProcessingNode::PostProcessingNode(SceneNode* parent, mat3 kernal) 
    : kernal(kernal), SceneNode(parent){};

void PostProcessingNode::OnRendered(ICommandQueue* queue){
    queue->Queue(PostProcessingKernal, [this](IRenderer* renderer){
            renderer->AddPostProcessingKernal(kernal);
    });
}
