#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <imgui/imgui.h>
#include "ImGuiBuild.h"

#include "../Texture/Texture.h"
#include "../Core/ExecuteCommands.h"

class Texture;
class ImguiHandle
{
private:
    /* data */
    GLFWwindow *m_Window;
    int m_Width, m_Height;
    const char *m_Version;
    ExecuteCommands &m_ExecuteCommands;
    Texture &m_Texture;

public:
    ImguiHandle(GLFWwindow *window, ExecuteCommands &executeCommands,Texture &texture, const char *version, const int Width, const int Height)
        : m_Window(window), m_Width(Width), m_Height(Height), m_Version(version), m_ExecuteCommands(executeCommands),m_Texture(texture){};

    virtual void OnAttach();
    // virtual void OnDetach();
    // virtual void OnEvent(Event &e);

    void CreateNewFrame();
    void DestroyCreatedFrame();

    // static imgui_ext::file_browser_modal fileBrowser("Import");

    void RenderElements();
    void DrawElements();

    void SetDarkThemeColors();
    ~ImguiHandle();
};
