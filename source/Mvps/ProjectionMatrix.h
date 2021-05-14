#pragma once

#include "../precomz.h"

// Logger file
#include "../Core/LogFile.h"

#define ASPECT_RATIO 0.0f
#define ZOOM_LEVEL 0.0f

class ProjectionMatrix
{
private:
    /* data */
    float m_AspectRatio = 0.0f;
    float m_ZoomLevel = 0.0f;
    float m_Zfar = 0.0f;
    float m_Znear = 0.0f;
    glm::mat4 m_Projection;
std::string identity = "Mvps";
std::string fileName = "Projection";
    Logger::LogFile log;
public:
    ProjectionMatrix(float Zoom, float AspectRatio, float zNear, float zFar)
        : m_ZoomLevel(Zoom), m_AspectRatio(AspectRatio), m_Zfar(zFar), m_Znear(zNear)
    {log.Initdiffer(fileName,identity);
        m_Projection = glm::perspective(glm::radians(m_ZoomLevel), m_AspectRatio, m_Znear, m_Zfar);
        // m_Projection = glm::inverse(m_Projection);
    };

    glm::mat4 GetProjectionMatrix() { return m_Projection; };

    void SetProjectionMatrix(float Zoom, float AspectRatio, float zNear, float zFar)
    {
        m_ZoomLevel = Zoom;
        m_AspectRatio = AspectRatio;
        m_Znear = zNear;
        m_Zfar = zFar;
        m_Projection = glm::perspective(glm::radians(m_ZoomLevel), m_AspectRatio, m_Znear, m_Znear);
        m_Projection = glm::inverse(m_Projection);
    }
};
