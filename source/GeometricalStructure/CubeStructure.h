#pragma once

#include "../precomz.h"

#include "../VertexBuffers/VertexBuffer.h"
#include "../IndexBuffers/IndexBuffer.h"
#include "../VertexArrays/VertexArray.h"
#include "../VertexBufferLayouts/VertexBufferLayout.h"
#include "../Renderer/Renderer.h"
#include "../Shaders/ShaderInitialize.h"

// Logger file
#include "../Core/LogFile.h"

class VertexBuffer;
class IndexBuffer;
class VertexArray;
class VertexBufferLayout;
class Renderer;
class ShaderInitialize;

class CubeStructures
{
private:
    VertexBuffer cube_Vb;
    IndexBuffer cube_Ib;
    VertexArray cube_Va;
    VertexBufferLayout cube_Layout;
    std::unique_ptr<Renderer> cube_render;

public:
    CubeStructures();
    void DrawGeometry(const ShaderInitialize &);
    void Clear(float *color);

public:
    VertexBuffer getVertexBuff() { return cube_Vb; };
    IndexBuffer getIndexBuff() { return cube_Ib; };
    VertexArray getVertexArray() { return cube_Va; };
};
