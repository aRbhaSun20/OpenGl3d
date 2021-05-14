#pragma once

#include "../precomz.h"

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

public:
    // model,view,projection mvp matrix
    MvpMatrix(){
        // log.Initdiffer(fileName,identity);
    }

    void setMvpMatrix(ProjectionMatrix &, PerspectiveCamera &, ModelMatrix &);
    glm::mat4 getMvpMatrix() { return u_MVP; };
    glm::mat4 getVpMatrix() { return u_VP; };
};