#include "texture/cubemap.h"

#include "glad/glad.h"
#include "Image/stb_image.h"

#include <iostream>

using namespace Renderer;

CubeMap::CubeMap(const string& basePath, const string& fileType) : ITexture(){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    int width, height, channels;
    unsigned char* data;

    const int cube_faces = 6;
    const string texture_names[] = {
        "right",
        "left",
        "top",
        "bottom",
        "back",
        "front"
    };

    for(int i = 0; i < cube_faces; i++){
        string textureName = basePath + texture_names[i] + "." + fileType;
        data = stbi_load(textureName.c_str(), &width, &height, &channels, 4);

        if(!data){
            cout << "Texture: " << textureName << "Expected, but not found for cube map" << endl;
            continue;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeMap::~CubeMap(){
    Delete();
}

void CubeMap::Delete(){
    glDeleteTextures(1, &textureID);
}

void CubeMap::Use(Shader* shader){ 
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    shader->SetBool("useCubemap", true);
}

unsigned int CubeMap::GetTextureID() const{
    return textureID;
}
