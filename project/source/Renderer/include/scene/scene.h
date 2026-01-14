#ifndef SCENE_H
#define SCENE_H

#include <type_traits>
#include <vector>
#include <memory>

#include "glm/glm.hpp"
#include "renderer/renderer.h"

using namespace std;

namespace Renderer{
    namespace Scene{
        class Scene;

        class SceneNode{
            public:
                friend class Scene;

                SceneNode(SceneNode* parent);
                virtual ~SceneNode();

                template<class T, class... U>
                T* AddChild(U... args){
                    static_assert(is_base_of<SceneNode, T>::value, 
                            "Attempted to create child that is not if base SceneNode");

                    T* child = new T(this, args...);

                    children.push_back(child);

                    return child;
                }

                virtual void OnRendered(IRenderQueue* renderer) = 0; 

            protected:
                vector<SceneNode*> children;
                SceneNode* parent;
        };

        class RootSceneNode : public SceneNode{
            public:
                RootSceneNode(SceneNode* parent);

                void OnRendered(IRenderQueue* renderer) override;
            private:
                glm::vec3 skyColor;  

        };

        class Scene{
            public:
                Scene();
                ~Scene();

                void Render(IRenderQueue* renderer);
                void Clear();

                template<class T, class... U>
                T* AddChildAtRoot(U... args){
                    T* child = root->AddChild<T>(args...);
                    return child;
                };

            private:
                RootSceneNode* root;
                
                void RenderNode(IRenderQueue* renderer, SceneNode& node);
                void ClearNode(SceneNode& node);
        };
    }
}

#endif
