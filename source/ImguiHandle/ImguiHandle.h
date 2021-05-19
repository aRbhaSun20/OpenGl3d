#pragma once

#include <Precomz/precomz.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include "ImGuiBuild.h"
#include "../Core/ExecuteCommands.h"
#include "../Initializer/Initialize.h"

// Logger file
#include "../Core/LogFile.h"

class Texture;
class Initialize;
class ImguiHandle
{
private:
    /* data */
    GLFWwindow *m_Window;
    int m_Width, m_Height;
    const char *m_Version;
    ExecuteCommands &m_ExecuteCommands;
    Logger::LogFile &p_File;
    Initialize &m_Initiate;

public:
    ImguiHandle(Initialize &Initiate, ExecuteCommands &executeCommands, const char *version,
                Logger::LogFile &LogFile)
        : m_Initiate(Initiate), m_Version(version),
          m_ExecuteCommands(executeCommands), p_File(LogFile)
    {
        OnAttach();
    };

    virtual void OnAttach();
    // virtual void OnDetach();
    // virtual void OnEvent(Event &e);

    void CreateNewFrame();
    void DestroyCreatedFrame();

    // static imgui_ext::file_browser_modal fileBrowser("Import");

    void RenderElements();
    void Begin();
    void End();

    void SetDarkThemeColors();
    ~ImguiHandle();

    inline const int getWidth() { return m_Width; };
    inline const int getHeight() { return m_Height; };
};
