#include "postprocessing_lua_api_layer.h"

#include "application.h"
#include "scene/post_processing_scene_node.h"
#include "scene/scene.h"

using namespace Core;
using namespace Lua;
using namespace glm;

void PostProcessingAPI::OnInit(){
    Function("ColorOffset", [this](unsigned char r, unsigned char g, unsigned char b, unsigned char a){
        SetColorOffset(r, g, b, a);
    });

    Function("ChannelMultiplyer", [this](float r, float g, float b, float a){
        SetChannelMultiplyer(r, g, b, a);
    });

    Function("Kernal", [this](float x11, float x12, float x13, float x21, float x22, float x23, float x31, float x32, float x33){
        mat3 kernal{x11, x12, x13, x21, x22, x23, x31, x32, x33};
        Kernal(kernal);
    });

    Function("EdgeDetection", [this](){
        mat3 kernal{0, -1, 0, 
                   -1, 4, -1,
                    0, -1, 0};

        Kernal(kernal);
    });

    Function("Sharpen", [this](){
        mat3 kernal{0, -1, 0, 
                   -1,  5, -1,
                    0, -1, 0};

        Kernal(kernal);
    });

    Function("BoxBlur", [this](){
        mat3 kernal{1, 1, 1, 
                    1, 1, 1,
                    1, 1, 1};

        kernal = kernal * 1.0f/9.0f;

        Kernal(kernal);
    });

    Function("GaussianBlur", [this](){
        mat3 kernal{1, 2, 1, 
                    2, 4, 2,
                    1, 2, 1};

        kernal = kernal * 1.0f/16.0f;

        Kernal(kernal);
    });
}

void PostProcessingAPI::SetColorOffset(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    AppResource(Scene::Scene, scene);
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetColorOffset(r, g, b, a);
}

void PostProcessingAPI::SetChannelMultiplyer(float r, float g, float b, float a){
    AppResource(Scene::Scene, scene);
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetChannelMultiplyer(r, g, b, a);
}

void PostProcessingAPI::Kernal(glm::mat3 kernal){
    AppResource(Scene::Scene, scene);
    scene->AddChildAtRoot<Scene::PostProcessingNode>(kernal);
}
