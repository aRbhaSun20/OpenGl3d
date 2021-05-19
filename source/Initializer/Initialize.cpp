#include "Initialize.h"

Initialize ::Initialize(int width, int height, const char *title, Logger::LogFile &LogFile)
    : windowHeight(height), windowWidth(width), index_File(LogFile)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()){
        std::cout << "Failure to initialize glfw" << std::endl;
        CORE_CRITICAL("Failure to initialize glfw");
    }

    m_window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    CORE_INFO("window creation complete");
    if (!m_window)
    {
        glfwTerminate();
        std::cout << "Window cration failure" << std::endl;
        CORE_CRITICAL("Window cration failure");
        return;
    }
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size);
}

Initialize ::~Initialize()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    CORE_WARN("Window Close Complete");
}

void Initialize ::Gladinitialization()
{

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failure to initialize glad" << std::endl;
        CORE_CRITICAL("Failure to initialize glad");
        return;
    }
}
