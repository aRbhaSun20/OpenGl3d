#pragma once

#include "./VertexArrays/VertexArray.h"
#include "./IndexBuffers/IndexBuffer.h"
#include "./Shaders/ShaderInitialize.h"

// #include <memory>

class IndexBuffer;
class VertexArray;
class ShaderInitialize;

class Renderer
{
public:
    Renderer() = default;

    void Clear(float *color);
    void Draw(const VertexArray &, const IndexBuffer &, const ShaderInitialize &) const;
};
