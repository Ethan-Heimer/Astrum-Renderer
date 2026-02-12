#include "screen.h"
#include <vector>

#include "glad/glad.h"

using namespace Renderer;
using namespace std;

Screen::Screen(){
    vector<float> screenQuad = {
        //positions  text coords 
        -1.0,  1.0,  0.0f, 1.0f,
        -1.0, -1.0,  0.0f, 0.0f,
        1.0,  -1.0,  1.0f, 0.0f,
         
        -1.0,  1.0,  0.0f, 1.0f,
         1.0, -1.0,  1.0f, 0.0f,
         1.0,  1.0,  1.0f, 1.0f,
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, screenQuad.size() * sizeof(float), screenQuad.data(), GL_STATIC_DRAW);

    const size_t vertexOffset = 0;
    const size_t uvOffset = 2 * sizeof(float);

    const size_t stride = 4 * sizeof(float);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)vertexOffset);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)uvOffset);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Screen::~Screen(){
    Delete();
}

void Screen::Delete(){
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Screen::Use(){
    glBindVertexArray(vao);
}

void Screen::Disable(){
    glBindVertexArray(vao);
}
