#include "IndexBuffer.h"

void IndexBuffer ::AddBuffer(const unsigned int *data, unsigned int count)
{
    m_Count = count;
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer ::AddBufferv(std::vector<unsigned int> data)
{
    m_Count = data.size();
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
};

void IndexBuffer ::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void IndexBuffer ::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer ::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererId);
}