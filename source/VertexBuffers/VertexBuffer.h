#pragma once
#include "../precomz.h"

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
    std::string identity = "VertexBuffers";
    Logger::LogFile log;

public:
    VertexBuffer() { log.Init(identity); };

    void AddBuffer(const void *data, unsigned int size);
    void AddBufferv(std::vector<float> data);
    void AddBufferVertex(std::vector<Vertex> data);

    void Bind() const;
    void UnBind() const;
    ~VertexBuffer();
};