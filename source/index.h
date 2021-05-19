#pragma once
#include <Precomz/precomz.h>

// custom libraries
#include <glad/glad.h> //glad for opengl libraries
#include <GLFW/glfw3.h>  //opengl library

// TimeStep, ExecuteCommands Headers
#include "Core/Timestep.h"        // Timestep for frameRate Duration Header
#include "Core/ExecuteCommands.h" // Command Executioning header
#include "Core/LightType.h"

// KeyBoard, Mouse Events Headers
#include "Events/Event.h"

// Window Initializer Header
#include "Initializer/Initialize.h"

// Shaders, Texture Headers
#include "Shaders/ShaderInitialize.h"
#include "Texture/Texture.h"

// Imgui Gui Handler Headers
#include "ImguiHandle/ImguiHandle.h"

// model,view,projection Headers
#include "Mvps/MvpMatrix.h"
#include "Mvps/ProjectionMatrix.h"
#include "Mvps/ModelMatrix.h"
#include "Camera/PerspectiveCamera.h"

// Cube Structure
#include "GeometricalStructure/CubeStructure.h"

// Light Types
#include "Light/Light.h"

// Assimp loader
#include "Model_Mesh/model.h"

#include "Core/LogFile.h"

class index
{
public:
    index();
    ~index();
};
