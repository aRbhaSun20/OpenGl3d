#pragma once

#include <Precomz/precomz.h>

#include <glad/glad.h>  //glad for opengl libraries

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Logger file
#include "../Core/LogFile.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class ShaderInitialize
{
public:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_Uniform_locationCache;
    Logger::LogFile &p_File;

public:
    ShaderInitialize(const std::string &filepath,Logger::LogFile &LogFile);
    ~ShaderInitialize();

    void Bind() const;
    void Unbind() const;

    // set Uniforms
    void SetUniform1i(const std::string &name, int value);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform3f(const std::string &name, float v0, float v1, float v2);
    void SetUniform3fv(const std::string &name, const glm::vec3 &matrix);
    void SetUniformMat3f(const std::string &name, const glm::mat3 &matrix);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);
    unsigned int GetRendererId()
    {
        return m_RendererID;
    }

    private : ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    int GetUniformLocation(const std::string &name);
};
