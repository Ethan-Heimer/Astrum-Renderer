#ifndef MESH_SCENE_NODE_H
#define MESH_SCENE_NODE_H

#include "scene/scene.h"
#include <memory>

namespace Renderer{
    namespace Scene{
        class MeshSceneNode : public SceneNode{
            public:
                MeshSceneNode(SceneNode* parent, Mesh* mesh, Material* material);
                ~MeshSceneNode() override;

                void OnRendered(ICommandQueue* renderer) override;

                void UseUniqueMaterial();

                Mesh& GetMesh();
                Transform& GetTransform();
                Material& GetMaterial();

            protected:
                Transform transform{};
                
                Material* material;
                Mesh* mesh;

                bool uniqueMaterial{false};
                bool uniqueMesh{false};

                void CloneMaterial();
                void CloneMesh();
        };
    }
}

#endif
