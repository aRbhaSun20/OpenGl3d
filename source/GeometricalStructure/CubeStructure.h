#pragma once

#include <Precomz/precomz.h>

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
    Logger::LogFile &p_File;

public:
    CubeStructures(Logger::LogFile &LogFile);
    void DrawGeometry(const ShaderInitialize &);
    void Clear(float *color);
    ~CubeStructures(){
        CORE_WARN("Cube Structure Closing");
    };
public:
    VertexBuffer getVertexBuff() { return cube_Vb; };
    IndexBuffer getIndexBuff() { return cube_Ib; };
    VertexArray getVertexArray() { return cube_Va; };
};
