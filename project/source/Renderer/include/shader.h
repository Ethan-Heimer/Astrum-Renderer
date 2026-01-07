#ifndef SHADER_H
#define SHADER_H

#include <string>
namespace Renderer{
    class Shader{
        public:
            Shader(std::string vertexPath, std::string fragmentPath);
            ~Shader();

            void Delete();

            unsigned int GetId() const;

            void SetBool(const std::string& name, bool value);
            void SetInt(const std::string& name, int value);
            void SetUnsignedInt(const std::string& name, unsigned int value);
            void SetFloat(const std::string& name, float value);

            void SetVector2(const std::string& name, float x, float y);
            void SetVector3(const std::string& name, float x, float y, float z);
            void SetVector4(const std::string& name, float x, float y, float z, float w);

            void SetMatrix4x4(const std::string& name, const float* matrix);

        private:
            unsigned int shaderProgramID;

    };
}

#endif
