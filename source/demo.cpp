#include "index.h"
#include "Model_Mesh/model.h"

// camera
glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

#define WIDTH 960
#define HEIGHT 560

// timing
float lastFrame = 0.0f;

float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;

bool firstMouse = true;
Timestep timestep;

// view matrix defination
// glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
PerspectiveCamera p_camera({0.0f, 0.0f, 3.0f});

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main(int argc, char *argv[])
{
    // glfw initializations
    // glm::vec3 demo = {1.0f, 1.0f, 1.0f};

    Initialize Initiate(WIDTH, HEIGHT, "InitGL");

    // Commands Executioner
    ExecuteCommands ExeCommands;
    // structu newStructure("../Models/cub.obj");

    // Event handler
    Event EventHandler(Initiate.getWindowReference(), p_camera, timestep, WIDTH, HEIGHT);

    glfwSetScrollCallback(Initiate.getWindowReference(), scroll_callback);
    glfwSetInputMode(Initiate.getWindowReference(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad initializations
    Initiate.Gladinitialization();

    // start the declarations from here
    {
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);

        // CubeStructures cube;
        // Model model("../Models/Cube/cube.obj");

        ShaderInitialize shaderLight("../source/Shaders/loading.shader");
        // ShaderInitialize ModelLoader("../source/Shaders/Model.shader");

        // projection matrix defination
        float Field_Of_View = 60.0f; //greater results zoom out ,vice-versa
        float AspectRatio = lastX / lastY;
        ProjectionMatrix Projection(Field_Of_View, AspectRatio, 0.1f, 100.0f);

        //Light model matrix defination
        glm::vec3 Light_Translation(1.2f, 1.0f, 0.8f);
        float Light_Angle = 0.0f;
        glm ::vec3 Light_AxisRotation(0.0f, 0.0f, 0.0f);
        ModelMatrix Light_Cube(Light_Translation, Light_Angle, Light_AxisRotation, 0.2f);
        Light_Cube.setModelScale(1.0);

        // Mvp matrix defination
        MvpMatrix mvp;

        // render loop
        while (!glfwWindowShouldClose(Initiate.getWindowReference()))
        {
            // input
            float time = (float)glfwGetTime();
            timestep = time - lastFrame;
            lastFrame = time;
            // input

            EventHandler.Event_Input_Callback();

            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            shaderLight.Bind();

            // draw the texture
            mvp.setMvpMatrix(Projection, p_camera, Light_Cube);
            shaderLight.SetUniformMat4f("u_MVP", mvp.getMvpMatrix());
            // render box
            // newStructure.draw(shaderLight);
            // cube.DrawGeometry(shaderLight);
            // model.Draw(shaderLight);

            glfwSwapBuffers(Initiate.getWindowReference());
            glfwPollEvents();
        }
    }

    return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    p_camera.ProcessMouseScroll(yoffset);
}