#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shaders/ShaderInitialize.h"

#include <string>
#include <vector>
using namespace std;

struct Vertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Textures
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
private:
    void setupMesh();

public:
    // Render data
    unsigned int VAO, VBO, EBO;
    // Mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Textures> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Textures> textures);
    void Draw(ShaderInitialize shader);
};