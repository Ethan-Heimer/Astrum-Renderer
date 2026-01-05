#include "layers/utils_application_layer.h"
#include "application.h"
#include "input.h"
#include <GLFW/glfw3.h>

Core::UtilsApplicationLayer::UtilsApplicationLayer(Application* application)
    : Core::ApplicationLayer(application), inputManager(application->GetWindow()){ 

    application->RegisterResource<Utils::Input>(&inputManager);

    application->SubscribeToInitialize([this](){this->inputManager.Initalize();});
    application->SubscribeToUpdate([this](){
            this->inputManager.PollInputState();
            
            if(this->inputManager.IsKeyDown(GLFW_KEY_LEFT_CONTROL) &&
               this->inputManager.IsKeyDown(GLFW_KEY_ESCAPE)){
                this->application->Exit();
            }
    });
}
