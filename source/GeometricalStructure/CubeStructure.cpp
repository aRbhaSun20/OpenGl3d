#include "CubeStructure.h"
#include <iostream>
// #include "Core/Log.h"
#include <glm/glm.hpp>
#include <vector>

CubeStructures::CubeStructures(Logger::LogFile &LogFile)
    : p_File(LogFile)
{
    // Logger::Log LogOut;
    // LogOut.Init();

    std::vector<float> positions = {
        // front
        //position       //texture   // normals
        -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f,  //0 0 1  2  3  4  5  6  7
         1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f,  0.0f,  1.0f,  //1 8 9 10 11 12 13 14 15
         1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f,  //2
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,    0.0f,  0.0f,  1.0f,  //3
        // top    
        -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //4
         1.0f,  1.0f,  1.0f,   1.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //5
         1.0f,  1.0f, -1.0f,   1.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //6
        -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //7
        // back    
         1.0f, -1.0f, -1.0f,   0.0f, 0.0f,    0.0f,  0.0f, -1.0f,  //8
        -1.0f, -1.0f, -1.0f,   1.0f, 0.0f,    0.0f,  0.0f, -1.0f,  //9
        -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,    0.0f,  0.0f, -1.0f,  //10
         1.0f,  1.0f, -1.0f,   0.0f, 1.0f,    0.0f,  0.0f, -1.0f,  //11
        // bottom    
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,    0.0f, -1.0f,  0.0f,  //12
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,  //13
         1.0f, -1.0f,  1.0f,   1.0f, 1.0f,    0.0f, -1.0f,  0.0f,  //14
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,  //15
        // left    
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,  //16
        -1.0f, -1.0f,  1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,  //17
        -1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,  //18 
        -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,  //19
        // right    
         1.0f, -1.0f,  1.0f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,  //20
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,  //21
         1.0f,  1.0f, -1.0f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,  //22
         1.0f,  1.0f,  1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f   //23
    };

    cube_Vb.AddBufferv(positions);

    cube_Layout.Push<float>(3);
    cube_Layout.Push<float>(2);
    cube_Layout.Push<float>(3);
    
    cube_Va.AddBuffer(cube_Vb, cube_Layout);

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
}

void CubeStructures::DrawGeometry(const ShaderInitialize &Shader)
{
    cube_render->Draw(cube_Va, cube_Ib, Shader);
}

void CubeStructures::Clear(float *color)
{
    cube_render->Clear(color);
}

