#pragma once

#include "../VertexBuffers/VertexBuffer.h"
#include "../VertexBufferLayouts/VertexBufferLayout.h"

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_RenderedID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &, const VertexBufferLayout &);
    void LinkAttrib(const VertexBuffer &, unsigned int layout, unsigned int numComponents, unsigned int type, ptrdiff_t stride, void *offset);

    void Bind() const;
    void Unbind() const;
};
