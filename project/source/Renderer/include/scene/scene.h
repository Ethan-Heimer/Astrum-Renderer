#ifndef SCENE_H
#define SCENE_H

#include "scene/root_scene_node.h"

using namespace std;

namespace Renderer{
    namespace Scene{
        class Scene{
            public:
                Scene();
                ~Scene();

                void Render(ICommandQueue* renderer);
                void Clear();

                RootSceneNode* GetRootNode();
                template<class T, class... U>
                T* AddChildAtRoot(U... args){
                    T* child = root->AddChild<T>(args...);
                    return child;
                };

            private:
                RootSceneNode* root;
                
                void RenderNode(ICommandQueue* renderer, SceneNode& node);
                void ClearNode(SceneNode& node);
        };
    }
}

#endif
