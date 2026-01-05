#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <memory>
#include <vector>

#include "shader.h"
#include "texture.h"

using namespace std;

namespace Renderer{
    class AssetManager{
        public:
            Shader& CreateShader(string vertexPath, string shaderPath);
            Texture& CreateTexture(string texturePath);

        private:
            vector<unique_ptr<Shader>> shaders;
            vector<unique_ptr<Texture>> textures;

    };
}

#endif
