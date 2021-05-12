#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <StdImage/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "../Shaders/ShaderInitialize.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
    /*  Functions   */
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Textures> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

public:
    /*  Model Data */
    vector<Textures> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    /*  Functions   */
    Model(string const &path, bool gamma = false): gammaCorrection(gamma)
    {
        loadModel(path);
        cout << "load complete";
    };

    void Draw(ShaderInitialize &shader);
    // Model() = default;
};