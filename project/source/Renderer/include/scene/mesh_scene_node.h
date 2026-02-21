#pragma once

#include "scene/scene_node.h"
#include "mesh.h"
#include "transform.h"
#include "material.h"

namespace Renderer{
    namespace Scene{
        class MeshSceneNode : public SceneNode{
            public:
                MeshSceneNode(SceneNode* parent, Mesh* mesh, Material* material);
                ~MeshSceneNode() override;

                void OnRendered(ICommandQueue* renderer) override;

                void UseUniqueMaterial();

                Mesh& GetMesh();
                Material& GetMaterial();

            protected: 
                Material* material;
                Mesh* mesh;

                bool uniqueMaterial{false};
                bool uniqueMesh{false};

                void CloneMaterial();
                void CloneMesh();
        };
    }
}

