#pragma once

#include <Precomz/precomz.h>

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/LogFile.h"

class ModelMatrix
{
private:
    glm::vec3 m_Translation;
    glm::vec3 m_RotationAxis;
    float m_RotationAngle = 0.0f;
    float m_Scale = 1.0f;
    glm::mat4 m_Model = glm::mat4(1.0f);
    Logger::LogFile &p_File;

public:
    ModelMatrix(glm::vec3 Translation, float Angle, glm::vec3 Axis, Logger::LogFile &LogFile, float scale = 1.0f)
        : m_Translation(Translation), m_RotationAxis(Axis), m_RotationAngle(Angle), m_Scale(scale), p_File(LogFile)
    {

        if (Translation != glm::vec3(0.0f, 0.0f, 0.0f))
            m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
        if (Angle != 0.0f)
            m_Model = glm::rotate(m_Model, glm::radians(m_RotationAngle), m_RotationAxis);
        if (scale != 1.0f)
            m_Model = glm::scale(m_Model, glm::vec3(m_Scale));
        CORE_INFO("Model Matrix Created");
    };

    ~ModelMatrix()
    {
        CORE_WARN("Model Matrix Dissolved");
    }

    void setModelMatrix(glm::vec3 Translation, float Angle, glm::vec3 Axis)
    {
        m_Translation = Translation;
        m_RotationAngle = Angle;
        m_RotationAxis = Axis;

        m_Model = glm::translate(glm::mat4(1.0f), m_Translation) *
                  glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationAngle), m_RotationAxis);
    };

    void setModelRotation(float angle, glm::vec3 axis)
    {
        m_Model = glm::rotate(m_Model, angle, axis);
    };

    void setModelScale(float scale)
    {
        m_Model = glm::scale(m_Model, glm::vec3(scale));
    };

    glm::mat4 getModelMatrix() { return m_Model; };

    glm::mat4 getNormalizedModelMatrix()
    {
        return glm::mat4(glm::inverse(m_Model));
    };
};
