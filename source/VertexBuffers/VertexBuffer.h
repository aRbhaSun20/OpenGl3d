#pragma once
#include <glad/glad.h>
#include <vector>

#include <glm/glm.hpp>

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    // VertexBuffer(std::vector<Vertex> &vertices);

    VertexBuffer() = default;

    void AddBuffer(const void *data, unsigned int size);
    void AddBufferv(std::vector<float> data);

    void Bind() const;
    void UnBind() const;
    ~VertexBuffer();
};