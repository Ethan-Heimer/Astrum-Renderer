#include "asset_manager.h"
#include "model.h"
#include "renderer/render_commands.h"
#include "scene/model_scene_node.h"

#include "renderer/renderer.h"

using namespace Renderer;
using namespace Scene;

ModelSceneNode::ModelSceneNode(SceneNode* parent, Model* model) : SceneNode(parent){
    this->model = model;
}

void ModelSceneNode::OnRendered(ICommandQueue* commandQueue){
    commandQueue->Queue(Renderer::Command::Standard, [this](IRenderer* renderer){ 
        int count = model->GetMeshCount();

        for(int i = 0; i < count; i++){
            Mesh* mesh = model->GetMesh(i);
            Material* material = model->GetMaterial(i);

            renderer->DrawMesh(mesh, &transform, material);
        }
    });
}

