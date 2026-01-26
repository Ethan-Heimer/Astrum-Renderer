#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>
#include <type_traits>

#include "renderer/render_commands.h"

using namespace std;
using namespace Renderer;
using namespace Command;

namespace Renderer{
    namespace Scene{
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
    }
}

#endif
