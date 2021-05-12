#pragma once

// internal libraries and packages
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

// external added libraries and packages
#include <glad/glad.h>  //glad for opengl libraries
#include <GLFW/glfw3.h> //opengl library

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h> // ImguiHeaders

// custom libraries

// TimeStep, ExecuteCommands Headers
// #include "Core/Base.h"
#include "Core/Timestep.h" // Timestep for frameRate Duration Header
// #include "Core/Input.h"
#include "Core/ExecuteCommands.h" // Command Executioning header
#include "Core/LightType.h"

// KeyBoard, Mouse Events Headers
#include "Events/Event.h"

// Window Initializer Header
#include "Initializer/Initialize.h"

// Shaders, Texture Headers
#include "Shaders/ShaderInitialize.h"
#include "Texture/Texture.h"

// Renderer Headers
// #include "Renderer/Renderer.h"

// Imgui Gui Handler Headers
// #include "ImguiHandle/ImguiHandle.h"

// model,view,projection Headers
#include "Mvps/MvpMatrix.h"
#include "Mvps/ProjectionMatrix.h"
#include "Mvps/ModelMatrix.h"
#include "Camera/PerspectiveCamera.h"

// Cube Structure
#include "GeometricalStructure/CubeStructure.h"

// Light Types
#include "Light/Light.h"

#include "Core/Log.h"

// #include "GeometricalStructure/structu.h"