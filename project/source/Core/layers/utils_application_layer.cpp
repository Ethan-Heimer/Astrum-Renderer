#include "layers/utils_application_layer.h"
#include "application.h"
#include "console/console.h"
#include "file_watcher.h"
#include "input.h"
#include "GLFW/glfw3.h"
#include <iostream>

Core::UtilsApplicationLayer::UtilsApplicationLayer(Application* application)
    : Core::ApplicationLayer(application), inputManager(application->GetWindow()),
      fileWatcher(){ 

    application->RegisterResource<Utils::Input>(&inputManager);
    application->RegisterResource<Utils::FileWatcher>(&fileWatcher);

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
