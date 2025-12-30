#include "camera.h"
#include "glm/packing.hpp"
#include <locale>
#include <numeric>
#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "input.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "renderer.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

#include <iostream>
#include <string>

#include "Image/stb_image.h"

float vertices[] = {
    0.5f, 0.5f, -0.5f,  
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,

    0.5f, 0.5f, 0.5f, 
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
};

unsigned int indices[] = { // note that we start from 0!
    0, 1, 2,
    0, 3, 2,

    4, 5, 6,
    4, 7, 6, 

    0, 1, 4,
    4, 5, 1,

    0, 3, 4,
    4, 7, 3,

    2, 3, 6,
    6, 7, 3, 

    6, 5, 2,
    5, 2, 1
};

float uv[] = {
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
};

int main(){
    // 1. Init Window and OpenGL Context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", monitor, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, mode->width, mode->height);

    //setings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Utils::Input::Initalize(window);

    Renderer::BasicRenderer renderer{window};

    Renderer::Shader shader{"./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl"};
    Renderer::Texture texture{"./assets/dog.jpg"};

    Renderer::Mesh mesh{vertices, sizeof(vertices), indices, sizeof(indices), 
            uv, sizeof(uv)};

    Renderer::Mesh meshCopy{mesh};

    Renderer::Transform transform{};
    Renderer::Transform transformCopy{transform};

    Renderer::Camera camera{};

    camera.SetRotation(0, 0);

    while(!glfwWindowShouldClose(window))
    {
        Utils::Input::PollInputState();

        if(Utils::Input::IsKeyDown(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true);

        //camera input
        const float cameraSpeed = 0.01f; // adjust accordingly

        if (Utils::Input::IsKeyDown(GLFW_KEY_W))
            camera.Move(cameraSpeed, 0, 0);
        if (Utils::Input::IsKeyDown(GLFW_KEY_S))
            camera.Move(-cameraSpeed, 0, 0);
        if (Utils::Input::IsKeyDown(GLFW_KEY_A))
            camera.Move(0, -cameraSpeed, 0);
        if (Utils::Input::IsKeyDown(GLFW_KEY_D))
            camera.Move(0, cameraSpeed, 0);

        double xMouseDelta = 0, yMouseDelta = 0;
        Utils::Input::GetMousePosDelta(&xMouseDelta, &yMouseDelta);

        float sensitivity = 0.1f;

        float yaw = 0;
        float pitch = 0;

        camera.GetRotation(&pitch, &yaw);

        yaw += -xMouseDelta * sensitivity;
        pitch += yMouseDelta * sensitivity;

        camera.SetRotation(pitch, yaw);

        auto rotation = transform.GetRotation();
        transform.SetRotation(rotation.x+.005, rotation.y+.001, rotation.z);

        float radius = 10;

        auto position = transformCopy.GetPosition();
        transformCopy.SetPosition(glm::cos(glfwGetTime()) * radius, 
                glm::sin(glfwGetTime()), glm::sin(glfwGetTime()) * radius);

        renderer.QueueObject(&mesh, &transform, &shader, &texture);
        renderer.QueueObject(&meshCopy, &transformCopy, &shader, &texture);

        renderer.Draw(&camera);

        glfwPollEvents();
    }

    glfwTerminate();
}
