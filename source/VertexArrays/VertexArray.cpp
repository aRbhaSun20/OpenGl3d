#include "VertexArray.h"

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RenderedID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    // Bind();
    // vb.Bind();
    glGenVertexArrays(1, &m_RenderedID);
    glBindVertexArray(m_RenderedID);
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        // links the buffer to vao
        glVertexAttribPointer(i, element.count, element.type,
                              element.normalized, layout.GetStride(), (void *)(uint64_t)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

// Links a VBO Attribute such as a position or color to the VAO
void VertexArray::LinkAttrib(const VertexBuffer &vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    vertexBuffer.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vertexBuffer.UnBind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RenderedID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}