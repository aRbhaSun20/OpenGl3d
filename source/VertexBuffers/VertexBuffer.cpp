#include "VertexBuffer.h"

void VertexBuffer ::AddBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer ::AddBufferv(std::vector<float> data)
{
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
};

void VertexBuffer ::AddBufferVertex(std::vector<Vertex> data)
{
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0], GL_STATIC_DRAW);
};

void VertexBuffer ::AddBufferPosition(std::vector<Positions> data)
{
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Positions), &data[0], GL_STATIC_DRAW);
};

void VertexBuffer ::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void VertexBuffer ::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer ::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererId);
}