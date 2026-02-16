#include "texture.h"

#include <iostream>

#include "glad/glad.h"
#include "Image/stb_image.h"

using namespace Renderer;
using namespace std;

Texture::Texture(unsigned int width, unsigned int height){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(string imagePath){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //set texture wrapping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, channelNumber;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channelNumber, 4);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl; 
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

Renderer::Texture::~Texture(){
    Delete();
}

void Renderer::Texture::Delete(){
    glDeleteTextures(1, &textureID);
}

void Renderer::Texture::Use(Renderer::Shader* shader){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID); 
    shader->SetBool("useTexture", true);
}

unsigned int Renderer::Texture::GetTextureID() const{
    return textureID;
}
