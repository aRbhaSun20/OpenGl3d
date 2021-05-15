#pragma once

#include <glad/glad.h> //glad for opengl libraries

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/LogFile.h"

struct Vertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    VertexBuffer() =default;

    void AddBuffer(const void *data, unsigned int size);
    void AddBufferv(std::vector<float> data);
    void AddBufferVertex(std::vector<Vertex> data);

    void Bind() const;
    void UnBind() const;
    ~VertexBuffer();
};