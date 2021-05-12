#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_modelMatrix(1.0f)
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_modelMatrix;
    // m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_modelMatrix;
}
void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    // m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_modelMatrix;
}

// zooming functionality
void OrthographicCamera::reorganizeCamera(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ViewMatrix = glm::mat4(1.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix ;
    // m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_modelMatrix;
}
void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    // HZ_PROFILE_FUNCTION();

    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// camera movements
void OrthographicCamera::MvpHandleCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
    m_ViewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void OrthographicCamera::MvpHandleModel(glm::vec3 translation)
{
    m_modelMatrix = glm::translate(glm::mat4(1.0f), translation);
}