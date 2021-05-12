#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <iostream>

class OrthographicCamera
{
private:
    /* data */
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
    glm::mat4 m_ModelViewProjectionMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 projection, view, model;
    glm::vec3 m_Position;
    float m_Rotation = 0.0f;

public:
    OrthographicCamera(float left, float right, float bottom, float top);
    void SetProjection(float left, float right, float bottom, float top);

    const glm::vec3 &getPosition() const { return m_Position; }
    void setPosition(const glm::vec3 &position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    float getRotation() const { return m_Rotation; }
    void setRotation(const float rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
    glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
    glm::mat4 GetModelMatrix() const { return m_modelMatrix; }
    glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    glm::mat4 GetModelViewProjectionMatrix() const { return m_ModelViewProjectionMatrix; }

private:
    void RecalculateViewMatrix();

public:
    void reorganizeCamera(float left, float right, float bottom, float top);
    void MvpHandleView(glm::vec3 transformation);
    void MvpHandleModel(glm::vec3);
    void CameraTransformation(glm::vec3 transformation);
    void MvpHandleCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

};

