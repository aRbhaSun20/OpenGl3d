#pragma once

#include <Precomz/precomz.h>

#include <glad/glad.h> //glad for opengl libraries

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>

#include <StdImage/stb_image.h>

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
    Logger::LogFile &p_File;

public:
    /*  Model Data */
    std::vector<Textures> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    /*  Functions   */
    Model(std::string const &path, Logger::LogFile &LogFile, bool gamma = false)
        : gammaCorrection(gamma), p_File(LogFile)
    {
        loadModel(path);
        CORE_INFO("load complete");
    };

    ~Model()
    {
        CORE_WARN("Model Load Closing");
    }

    void Draw(ShaderInitialize &shader);
    // Model() = default;
};