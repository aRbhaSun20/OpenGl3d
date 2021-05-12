#pragma once
#include <memory>

#include "../Model_Mesh/model.h"
#include <glad/glad.h>  //glad for opengl libraries
#include <GLFW/glfw3.h> //opengl library

#include "../Shaders/ShaderInitialize.h"

class ShaderInitialize;
class Model;

class structu
{
private:
    /* data */
    // std::unique_ptr<Model> model;
    Model model;
    glm::mat4 modelMatrix;

public:
    structu(string modelPath);
    void draw(ShaderInitialize &shader);
};