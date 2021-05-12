#include "Renderer.h"

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderInitialize &shader) const
{
    shader.Bind();
    va.Bind();

    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(float *color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}