#ifndef SHADER_H
#define SHADER_H

#include <string>
namespace Renderer{
    class Shader{
        public:
            Shader(std::string vertexPath, std::string fragmentPath);
            ~Shader();

            void Delete();

            unsigned int GetShaderId() const;

        private:
            unsigned int shaderProgramID;

    };
}

#endif
