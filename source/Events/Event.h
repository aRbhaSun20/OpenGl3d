#pragma once

#include <Precomz/precomz.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Camera/PerspectiveCamera.h"
#include "../Core/Timestep.h"

#include "../Core/KeyCodes.h"
#include "../Core/MouseCodes.h"

// Logger file
#include "../Core/LogFile.h"

class Event
{
private:
    GLFWwindow *m_Window;
    PerspectiveCamera &m_View;
    Timestep &m_Timestep;

private:
    int WIDTH;
    int HEIGHT;
    bool firstMouse = true;
    float rotX;
    float rotY;
    float sensitivity = 1.0f;
    double xMouse, yMouse;
    Logger::LogFile &p_File;

public:
    Event(GLFWwindow *window, PerspectiveCamera &View, Timestep &timestep,
          int width, int height, Logger::LogFile &LogFile)
        : m_Window(window), WIDTH(width), HEIGHT(height),
          m_View(View), m_Timestep(timestep), p_File(LogFile)
    {
        CORE_TRACE("Event Declaration Starting");
    };

    ~Event()
    {
        CORE_WARN("Event Declaration Closing");
    }
    
    void Event_Input_Callback();

    void Event_Mouse_Callback();
};
