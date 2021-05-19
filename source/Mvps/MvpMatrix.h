#pragma once

#include <Precomz/precomz.h>

#include <glm/glm.hpp> //maths library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ModelMatrix.h"
#include "ProjectionMatrix.h"
#include "../Camera/PerspectiveCamera.h"

// Logger file
#include "../Core/LogFile.h"

class MvpMatrix
{
private:
    /* data */
    glm::mat4 m_Projection, m_View, m_Model;
    glm::mat4 u_MVP;
    glm::mat4 u_VP;
    Logger::LogFile &p_File;

public:
    // model,view,projection mvp matrix
    MvpMatrix(Logger::LogFile &LogFile)
        : p_File(LogFile)
    {
        CORE_INFO("Mvp Matrix Declaration");
    }
    
    ~MvpMatrix()
    {
        CORE_WARN("Mvp Matrix Dissolved");
    }

    void setMvpMatrix(ProjectionMatrix &, PerspectiveCamera &, ModelMatrix &);
    glm::mat4 getMvpMatrix() { return u_MVP; };
    glm::mat4 getVpMatrix() { return u_VP; };
};