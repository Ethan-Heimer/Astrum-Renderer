#include "object_manager.h"
#include <memory>

Renderer::Object& Renderer::ObjectManager::CreateObject(Mesh& mesh, Material& material){
   unique_ptr<Object> newObject = make_unique<Object>(mesh, material);

   Object& ref = *newObject.get();

   objects.push_back(std::move(newObject));

   return ref; 
}

void Renderer::ObjectManager::Clear(){
    objects.clear();
}

