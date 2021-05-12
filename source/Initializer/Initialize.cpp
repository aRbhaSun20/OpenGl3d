#include "Initialize.h"

Initialize ::Initialize(int width, int height, const char *title)
    : windowHeight(height), windowWidth(width)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        Log("Failure to initialize glfw");

   m_window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (!m_window)
    {
        glfwTerminate();
        Log("Window cration failure");
        return;
    }
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size);
}

Initialize ::~Initialize()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Initialize ::Gladinitialization()
{

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log("Failure to initialize glad");
        return;
    }
}
