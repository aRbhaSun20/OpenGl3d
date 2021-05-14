#pragma once

#include "../precomz.h"

// Logger file
#include "../Core/LogFile.h"

class IndexBuffer
{
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    IndexBuffer() = default;

    void AddBufferv(std::vector<unsigned int> data);
    void AddBuffer(const unsigned int *data, unsigned int count);
    void Bind() const;
    void UnBind() const;
    inline unsigned int GetCount() const { return m_Count; }

    ~IndexBuffer();
};