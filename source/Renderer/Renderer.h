#pragma once

#include "../VertexArrays/VertexArray.h"
#include "../IndexBuffers/IndexBuffer.h"
#include "../Shaders/ShaderInitialize.h"

// Logger file
#include "../Core/LogFile.h"

class IndexBuffer;
class VertexArray;
class ShaderInitialize;

class Renderer
{
private:


public:
    Renderer() {  };

    void Clear(float *color);
    void Draw(const VertexArray &, const IndexBuffer &, const ShaderInitialize &) const;
    void UnBind(const VertexArray &, const IndexBuffer &, const ShaderInitialize &) const;
};
