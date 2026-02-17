#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

namespace Utils{
    class Input{
        public:
            void Initalize(GLFWwindow* window);
            void PollInputState();

            bool IsKeyDown(unsigned int KeyCode);

            void GetMousePos(double* posX, double* posY);
            
            void GetMouseScrollDelta(double* scrollDelta);
            void GetMousePosDelta(double* posDeltaX, double* posDeltaY);

        private:
            GLFWwindow* window;

            double xCurrentPos, yCurrentPos, xLastPos, yLastPos;
            double xMouseDelta, yMouseDelta;
            double xScrollDelta, yScrollDelta;

            int isInputFocused = 0;

            void mouseCallback(GLFWwindow* window, double xpos, double ypos);
            void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}

#endif
