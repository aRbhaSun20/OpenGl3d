#pragma once

#include "../precomz.h"

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

public:
    Event(GLFWwindow *window, PerspectiveCamera &View, Timestep &timestep, int width, int height)
        : m_Window(window), WIDTH(width), HEIGHT(height),  m_View(View), m_Timestep(timestep){};

    void Event_Input_Callback();

    void Event_Mouse_Callback();
};
