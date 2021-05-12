#include "MvpMatrix.h"

void MvpMatrix::setMvpMatrix(ProjectionMatrix &Projection, PerspectiveCamera &View, ModelMatrix &Model)
{
    m_Projection = Projection.GetProjectionMatrix();
    m_View = View.GetViewMatrix();
    m_Model = Model.getModelMatrix();
    u_MVP = m_Projection * m_View * m_Model;
    u_VP = m_Projection * m_View;
};
