#include "Event.h"

void Event::Event_Input_Callback()
{
    glfwGetCursorPos(m_Window, &xMouse, &yMouse);

    if (glfwGetKey(m_Window, Key::Escape) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);

    if (glfwGetKey(m_Window, Key::W) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::FORWARD, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::S) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::BACKWARD, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::Up) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::UP, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::Down) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::DOWN, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::Left) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::LEFT, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::Right) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::RIGHT, m_Timestep.GetSeconds());

    if (glfwGetKey(m_Window, Key::LeftShift) == GLFW_PRESS)
        m_View.ProcessKeyboard(Camera_Movement::SHIFT_HOLD, m_Timestep.GetSeconds());

    else if (glfwGetKey(m_Window, Key::LeftShift) == GLFW_RELEASE)
        m_View.ProcessKeyboard(Camera_Movement::SHIFT_RELEASE, m_Timestep.GetSeconds());

    if (glfwGetMouseButton(m_Window, Mouse::ButtonLeft) == GLFW_PRESS)
    {
        if (sensitivity > 0)
            sensitivity *= -1;
        Event_Mouse_Callback();
    }
    else if (glfwGetMouseButton(m_Window, Mouse::ButtonLeft) == GLFW_RELEASE)
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }

    if (glfwGetMouseButton(m_Window, Mouse::ButtonRight) == GLFW_PRESS)
    {
        if (sensitivity < 0)
            sensitivity *= -1;
        Event_Mouse_Callback();
    }
    else if (glfwGetMouseButton(m_Window, Mouse::ButtonRight) == GLFW_RELEASE)
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
    // m_View.ProcessMouseMovement(xMouse, yMouse, WIDTH, HEIGHT, true);
}

void Event::Event_Mouse_Callback()
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (firstMouse)
    {
        glfwSetCursorPos(m_Window, (WIDTH / 2), (HEIGHT / 2));
        firstMouse = false;
    }

    rotX = sensitivity * (float)(yMouse - (HEIGHT / 2)) / HEIGHT;
    rotY = sensitivity * (float)(xMouse - (HEIGHT / 2)) / HEIGHT;

    glm::vec3 newOrientation = glm::rotate(m_View.getOrientation(), glm::radians(-rotX), glm::normalize(glm::cross(m_View.getOrientation(), m_View.getUp())));

    if (abs(glm::angle(newOrientation, m_View.getUp()) - glm::radians(90.0f)) <= glm::radians(85.0f))
        m_View.setOrientation(newOrientation);

    newOrientation = glm::rotate(m_View.getOrientation(), glm::radians(-rotY), m_View.getUp());
    m_View.setOrientation(newOrientation);

    glfwSetCursorPos(m_Window, (WIDTH / 2), (HEIGHT / 2));
}