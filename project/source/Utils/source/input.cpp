#include "input.h"

#include <GLFW/glfw3.h>
#include <iostream>

/*
 * Disabling the cursor invokes a cursor pos callback, therefor the first 
 * Invokation of the callback gets ignored.
 *
 * this cam probably be removed when app core is implemented
 */

Utils::Input::Input(GLFWwindow* window)
    : window(window), isInputFocused(0){}


void Utils::Input::Initalize(){
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y){
        Input* input = (Input*)glfwGetWindowUserPointer(window);
        input->scrollCallback(window, x, y);
    });

    xCurrentPos = width/2.0f;
    yCurrentPos = height/2.0f;

    xLastPos = width/2.0f;
    yLastPos = height/2.0f;
}

void Utils::Input::PollInputState(){
    xLastPos = xCurrentPos;
    yLastPos = yCurrentPos;

    glfwGetCursorPos(window, &xCurrentPos, &yCurrentPos);

    xMouseDelta = xLastPos - xCurrentPos;
    yMouseDelta = yLastPos - yCurrentPos;

    isInputFocused = glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

bool Utils::Input::IsKeyDown(unsigned int keyCode){
   return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

void Utils::Input::GetMousePos(double *posX, double *posY){
    *posX = xCurrentPos;
    *posY = yCurrentPos;
}

void Utils::Input::GetMouseScrollDelta(double* scrollDelta){
    *scrollDelta = yScrollDelta;
}

void Utils::Input::GetMousePosDelta(double *posDeltaX, double *posDeltaY){
    if(!isInputFocused){
        *posDeltaX = 0;
        *posDeltaY = 0;
    } else {
        *posDeltaX = xMouseDelta;
        *posDeltaY = yMouseDelta;
    }
}

void Utils::Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    xScrollDelta = xoffset;
    yScrollDelta = yoffset;
}
