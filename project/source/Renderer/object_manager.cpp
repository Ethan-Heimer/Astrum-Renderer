#include "object_manager.h"
#include <memory>

Renderer::Object& Renderer::ObjectManager::CreateObject(Mesh& mesh, Shader& shader){
   unique_ptr<Object> newObject = make_unique<Object>(mesh, shader);

   Object& ref = *newObject.get();

   objects.push_back(std::move(newObject));

   return ref; 
}
