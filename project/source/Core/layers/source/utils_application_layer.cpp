#include "utils_application_layer.h"
#include "application.h"
#include "console.h"
#include "file_watcher.h"
#include "input.h"
#include "GLFW/glfw3.h"

using namespace Core;
using namespace Utils;

UtilsApplicationLayer::UtilsApplicationLayer(Application* application)
    : ApplicationLayer(application), inputManager(application->GetWindow()),
      fileWatcher(){ 

    application->RegisterResource<Input>(&inputManager);
    application->RegisterResource<FileWatcher>(&fileWatcher);

    application->SubscribeToInitialize([this](){
            this->inputManager.Initalize();

            Console::Log(Message, "Engine", Green, "Engine Initilaized!");
        });
    application->SubscribeToUpdate([this](){
            this->inputManager.PollInputState();
            this->fileWatcher.CheckFiles();
            
            if(this->inputManager.IsKeyDown(GLFW_KEY_LEFT_CONTROL) &&
               this->inputManager.IsKeyDown(GLFW_KEY_ESCAPE)){
                this->application->Exit();
            }
    });
}
