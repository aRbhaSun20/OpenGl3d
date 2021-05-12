#include "structu.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

    structu::structu(string modelPath)
    {
        model.loadModel(modelPath);
        // glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006, 0.006, 0.006));

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &modelMatrix, GL_STATIC_DRAW);

        for (unsigned int i = 0; i < model.meshes.size(); i++)
        {
            unsigned int VAO = model.meshes[i].VAO;
            glBindVertexArray(VAO);

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }
    }

    // void loadModel(string modelPath)
    // {
    //     model = new Model(modelPath);
    // }

    void structu::draw(ShaderInitialize &shader)
    {
        model.Draw(shader);
    }