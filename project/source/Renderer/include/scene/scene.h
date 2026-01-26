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

                virtual void OnRendered(ICommandQueue* commandQueue) = 0; 

            protected:
                vector<SceneNode*> children;
                SceneNode* parent;
        };

        class RootSceneNode : public SceneNode{
            public:
                RootSceneNode(SceneNode* parent);

                void OnRendered(ICommandQueue* commandQueue) override;
                void SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b);

            private:
                glm::vec3 skyColor;  

        };

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
