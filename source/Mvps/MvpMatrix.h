#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ModelMatrix.h"
#include "ProjectionMatrix.h"
#include "../Camera/PerspectiveCamera.h"

class MvpMatrix
{
private:
    /* data */
    glm::mat4 m_Projection, m_View, m_Model;
    glm::mat4 u_MVP;
    glm::mat4 u_VP;

public:
    // model,view,projection mvp matrix

    void setMvpMatrix(ProjectionMatrix &, PerspectiveCamera &, ModelMatrix &);
    glm::mat4 getMvpMatrix() { return u_MVP; };
    glm::mat4 getVpMatrix() { return u_VP; };
};