#include "framebuffer.h"
#include "glad/glad.h"
#include "texture.h"
#include <iostream>

using namespace Renderer;
using namespace std;

FrameBuffer::FrameBuffer(unsigned int windowWidth, unsigned int windowHeight) :
    texture(windowWidth, windowHeight){
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    //bind texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetTextureID(), 0);

    //bind rbo
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
       cout << "Frame Buffer is not complete"  << endl;
    }


    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer(){
    Delete(); 
}

void FrameBuffer::Use(){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::Disable(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Delete(){
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
}

Texture* FrameBuffer::GetColorBuffer(){
    return &texture;
}
