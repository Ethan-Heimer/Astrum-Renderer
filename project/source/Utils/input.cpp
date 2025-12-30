#include "input.h"

#include <GLFW/glfw3.h>

double Utils::Input::xCurrentPos = 0;
double Utils::Input::yCurrentPos = 0;

double Utils::Input::xLastPos = 0;
double Utils::Input::yLastPos = 0;

double Utils::Input::xMouseDelta = 0;
double Utils::Input::yMouseDelta = 0;

double Utils::Input::xScrollDelta = 0;
double Utils::Input::yScrollDelta = 0;

bool Utils::Input::mouseDeltaCalculated = true;
bool Utils::Input::initalized = false;

/*
 * Disabling the cursor invokes a cursor pos callback, therefor the first 
 * Invokation of the callback gets ignored.
 *
 * this cam probably be removed when app core is implemented
 */
bool Utils::Input::ignoreFirstCallback = true;

GLFWwindow* Utils::Input::Window = nullptr;

void Utils::Input::Initalize(GLFWwindow* window){
    Window = window;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    int width, height;
    glfwGetWindowSize(window, &width, &height);


    xCurrentPos = width/2.0f;
    yCurrentPos = height/2.0f;

    xLastPos = width/2.0f;
    yLastPos = height/2.0f;

    initalized = true;
}

void Utils::Input::PollInputState(){
    if(!initalized)
        return;

    if(!mouseDeltaCalculated){
        xMouseDelta = xLastPos - xCurrentPos;
        yMouseDelta = yLastPos - yCurrentPos;

        mouseDeltaCalculated = true;
    } else {
        xMouseDelta = 0;
        yMouseDelta = 0;
    }
}

bool Utils::Input::IsKeyDown(unsigned int keyCode){
   return glfwGetKey(Window, keyCode) == GLFW_PRESS;
}

void Utils::Input::GetMousePos(double *posX, double *posY){
    *posX = xCurrentPos;
    *posY = yCurrentPos;
}

void Utils::Input::GetMouseScrollDelta(double* scrollDelta){
    *scrollDelta = yScrollDelta;
}

void Utils::Input::GetMousePosDelta(double *posDeltaX, double *posDeltaY){
    *posDeltaX = xMouseDelta;
    *posDeltaY = yMouseDelta;
}

void Utils::Input::mouseCallback(GLFWwindow* window, double xpos, double ypos){
    if(!initalized)
        return;

    if(ignoreFirstCallback){
        ignoreFirstCallback = false;
        return;
    }

    xLastPos = xCurrentPos;
    yLastPos = yCurrentPos;

    xCurrentPos = xpos;
    yCurrentPos = ypos;

    mouseDeltaCalculated = false;
}

void Utils::Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    if(!initalized)
        return;

    if(ignoreFirstCallback){
        ignoreFirstCallback = false;
        return;
    }

    xScrollDelta = xoffset;
    yScrollDelta = yoffset;
}
