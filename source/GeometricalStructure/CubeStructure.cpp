#include "CubeStructure.h"
#include <iostream>
// #include "Core/Log.h"
#include <glm/glm.hpp>
#include <vector>

CubeStructures::CubeStructures(Logger::LogFile &LogFile)
    : p_File(LogFile)
{
    std::vector<Positions> vertexs;

    {
        Positions vert;

        // front
        // 1
        vert.vertices = {-1.0f, -1.0f, 1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {0.0f, 0.0f, 1.0f};
        vertexs.push_back(vert);
        // 2
        vert.vertices = {1.0f, -1.0f, 1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {0.0f, 0.0f, 1.0f};
        vertexs.push_back(vert);
        // 3
        vert.vertices = {1.0f, 1.0f, 1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {0.0f, 0.0f, 1.0f};
        vertexs.push_back(vert);
        // 4
        vert.vertices = {-1.0f, 1.0f, 1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {0.0f, 0.0f, 1.0f};
        vertexs.push_back(vert);

        // top
        // 5
        vert.vertices = {-1.0f, 1.0f, 1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {0.0f, 1.0f, 0.0f};
        vertexs.push_back(vert);
        // 6
        vert.vertices = {1.0f, 1.0f, 1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {0.0f, 1.0f, 0.0f};
        vertexs.push_back(vert);
        // 7
        vert.vertices = {1.0f, 1.0f, -1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {0.0f, 1.0f, 0.0f};
        vertexs.push_back(vert);
        // 8
        vert.vertices = {-1.0f, 1.0f, -1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {0.0f, 1.0f, 0.0f};
        vertexs.push_back(vert);

        // back
        // 9
        vert.vertices = {1.0f, -1.0f, -1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {0.0f, 0.0f, -1.0f};
        vertexs.push_back(vert);
        // 10
        vert.vertices = {-1.0f, -1.0f, -1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {0.0f, 0.0f, -1.0f};
        vertexs.push_back(vert);
        // 11
        vert.vertices = {-1.0f, 1.0f, -1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {0.0f, 0.0f, -1.0f};
        vertexs.push_back(vert);
        // 12
        vert.vertices = {1.0f, 1.0f, -1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {0.0f, 0.0f, -1.0f};
        vertexs.push_back(vert);

        // bottom
        // 13
        vert.vertices = {-1.0f, -1.0f, -1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {0.0f, -1.0f, 0.0f};
        vertexs.push_back(vert);
        // 14
        vert.vertices = {1.0f, -1.0f, -1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {0.0f, -1.0f, 0.0f};
        vertexs.push_back(vert);
        // 15
        vert.vertices = {1.0f, -1.0f, 1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {0.0f, -1.0f, 0.0f};
        vertexs.push_back(vert);
        // 16
        vert.vertices = {1.0f, -1.0f, 1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {0.0f, -1.0f, 0.0f};
        vertexs.push_back(vert);

        // left
        // 17
        vert.vertices = {-1.0f, -1.0f, -1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 18
        vert.vertices = {-1.0f, -1.0f, 1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 19
        vert.vertices = {-1.0f, 1.0f, 1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 20
        vert.vertices = {-1.0f, 1.0f, -1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);

        // right
        // 21
        vert.vertices = {1.0f, -1.0f, 1.0f};
        vert.textures = {0.0f, 0.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 22
        vert.vertices = {1.0f, -1.0f, -1.0f};
        vert.textures = {1.0f, 0.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 23
        vert.vertices = {1.0f, 1.0f, -1.0f};
        vert.textures = {1.0f, 1.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
        // 24
        vert.vertices = {1.0f, 1.0f, 1.0f};
        vert.textures = {0.0f, 1.0f};
        vert.normals = {-1.0f, 0.0f, 0.0f};
        vertexs.push_back(vert);
    }

    cube_Vb.AddBufferPosition(vertexs);

    cube_Layout.Push<float>(3);
    cube_Layout.Push<float>(2);
    cube_Layout.Push<float>(3);

    cube_Va.AddBuffer(cube_Vb, cube_Layout);
    CORE_INFO("vertex position declaration and binding complete");

    // indices attribute
    std::vector<unsigned int> indices = {
        // front
        0u, 1u, 2u,
        2u, 3u, 0u,
        // top
        4u, 5u, 6u,
        6u, 7u, 4u,
        // back
        8u, 9u, 10u,
        10u, 11u, 8u,
        // bottom
        12u, 13u, 14u,
        14u, 15u, 12u,
        // left
        16u, 17u, 18u,
        18u, 19u, 16u,
        // right
        20u, 21u, 22u,
        22u, 23u, 20u //
    };

    // index buffer object
    cube_Ib.AddBufferv(indices);
    CORE_INFO("vertex index declaration and binding complete");
}

void CubeStructures::DrawGeometry(const ShaderInitialize &Shader)
{
    cube_render->Draw(cube_Va, cube_Ib, Shader);
}

void CubeStructures::Clear(float *color)
{
    cube_render->Clear(color);
}
