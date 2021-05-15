#pragma once

// external libraries and packages
#include <Precomz/precomz.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Logger file
#include "../Core/LogFile.h"


class Initialize
{
private:
    int windowWidth, windowHeight;
    GLFWwindow *m_window;
    Logger::LogFile &index_File;

public:
    Initialize(int, int, const char *, Logger::LogFile &);
    GLFWwindow *getWindowReference() { return m_window; }
    void Gladinitialization();
    ~Initialize();

    int getCount(int ArraySize, int Sizevalue)
    {
        return ArraySize / Sizevalue;
    }

private:
    static void error_callback(int error, const char *description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void framebuffer_size(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};