#pragma once

#include "../precomz.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "mesh.h"
#include "../Shaders/ShaderInitialize.h"
// Logger file
#include "../Core/LogFile.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    /*  Functions   */
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Textures> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

public:
    /*  Model Data */
    std::vector<Textures> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    /*  Functions   */
    Model(std::string const &path, bool gamma = false): gammaCorrection(gamma)
    {
        loadModel(path);
        std::cout << "load complete";
    };

    void Draw(ShaderInitialize &shader);
    // Model() = default;
};