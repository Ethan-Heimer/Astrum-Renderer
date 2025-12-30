#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
namespace Utils{
    class Input{
        public:
            static void Initalize(GLFWwindow* window);
            static void PollInputState();

            static bool IsKeyDown(unsigned int KeyCode);

            static void GetMousePos(double* posX, double* posY);
            static void GetMouseScrollDelta(double* scrollDelta);
            static void GetMousePosDelta(double* posDeltaX, double* posDeltaY);

        private:
            static GLFWwindow* Window;

            static double xCurrentPos, yCurrentPos, xLastPos, yLastPos;
            static double xMouseDelta, yMouseDelta;
            static double xScrollDelta, yScrollDelta;

            static bool mouseDeltaCalculated, initalized;
            static bool ignoreFirstCallback;

            static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
            static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}

#endif
