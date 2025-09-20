#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int ID;
    void CheckCompileErrors(unsigned int shader, std::string type);

public:
    Shader(const char* vertexSource, const char* fragmentSource);

    void Use();

    // Utility functions for setting uniforms
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat2(const std::string& name, const glm::mat2& mat);
    void SetMat3(const std::string& name, const glm::mat3& mat);
    void SetMat4(const std::string& name, const glm::mat4& mat);

    unsigned int GetID() const;

    ~Shader();
};

#endif // SHADER_H

