#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
private:
    std::string m_FilePath;
    uint32_t m_RendererID;
    std::unordered_map<std::string, int32_t> m_UniformLocationCache;

    ShaderProgramSource ParseShader(const std::string& filePath);
    uint32_t CompileShader(uint32_t type, const std::string& source);
    int32_t  CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int32_t GetUniformLocation(const std::string& name);
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set uniforms
    void SetUniform1i(const std::string& name, int32_t value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix);
};