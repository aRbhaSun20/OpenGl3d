#pragma once

#include "../precomz.h"

#include "../VertexBuffers/VertexBuffer.h"
#include "../IndexBuffers/IndexBuffer.h"
#include "../Shaders/ShaderInitialize.h"

#include <string>
#include <vector>

// Logger file
#include "../Core/LogFile.h"

struct Vertex;

class VertexBuffer;
class IndexBuffer;
class Renderer;
class ShaderInitialize;
struct Textures
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{

    private:
        VertexBuffer mesh_Vb;
        IndexBuffer mesh_Ib;

    private:
        void setupMesh();

    public:
        // Render data
        unsigned int VAO;
        // Mesh Data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Textures> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);
        void Draw(ShaderInitialize shader);
};