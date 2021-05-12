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

        CubeStructures cube;
        Model model("../Models/Cube/cube.obj");

        ShaderInitialize shaderColorCube("../source/Shaders/Color.shader");
        ShaderInitialize shaderLight("../source/Shaders/Light.shader");
        ShaderInitialize ModelLoader("../source/Shaders/loading.shader");

        // projection matrix defination
        float Field_Of_View = 60.0f; //greater results zoom out ,vice-versa
        float AspectRatio = lastX / lastY;
        ProjectionMatrix Projection(Field_Of_View, AspectRatio, 0.1f, 100.0f);

        //Object model matrix defination
        glm::vec3 Object_Translation(-0.25f, -0.25f, 0.0f);
        float Object_Angle = 0.0f;
        glm ::vec3 Object_AxisRotation(0.0f, 0.0f, 0.0f);
        ModelMatrix Object_Cube(Object_Translation, Object_Angle, Object_AxisRotation);
        Object_Cube.setModelScale(0.5);

        //Light model matrix defination
        glm::vec3 Light_Translation(1.2f, 1.0f, 0.8f);
        float Light_Angle = 0.0f;
        glm ::vec3 Light_AxisRotation(0.0f, 0.0f, 0.0f);
        ModelMatrix Light_Cube(Light_Translation, Light_Angle, Light_AxisRotation, 0.2f);
        Light_Cube.setModelScale(1.0);

        // Mvp matrix defination
        MvpMatrix mvp;

        Texture Wooden_Box("../images/woodenContainer.png");
        Wooden_Box.Bind(0);
        Texture Steel_Frame("../images/woodenContainerSspecular.png");
        Steel_Frame.Bind(1);

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // select light type
        Light lightType(LightType::PointLightSource, "Gold");

        // select bg color
        float BGcolor[4] = {0.4f, 0.2f, 0.2f, 1.0f};
        shaderColorCube.SetUniform1i("u_Material.diffuseTexture", 0);
        shaderColorCube.SetUniform1i("u_Material.specularTexture", 1);
        // render loop
        while (!glfwWindowShouldClose(Initiate.getWindowReference()))
        {
            // input
            float time = (float)glfwGetTime();
            timestep = time - lastFrame;
            lastFrame = time;
            // input
            EventHandler.Event_Input_Callback();

            // // render
            Wooden_Box.Bind(0);
            Steel_Frame.Bind(1);

            shaderColorCube.SetUniform1i("u_Material.diffuseTexture", 0);
            shaderColorCube.SetUniform1i("u_Material.specularTexture", 1);

            cube.Clear(BGcolor);
            {
                Object_Cube.setModelRotation(timestep.GetSeconds(), {0.5f, 1.0f, 0.0f});
                // draw the texture
                shaderColorCube.Bind();

                shaderColorCube.SetUniform3fv("u_lightPos", Light_Translation);
                shaderColorCube.SetUniform3fv("u_viewPos", p_camera.getCameraPosition());

                lightType.bindLight(shaderColorCube, p_camera.getOrientation());

                mvp.setMvpMatrix(Projection, p_camera, Object_Cube);
                shaderColorCube.SetUniformMat4f("u_Model", Object_Cube.getModelMatrix());
                shaderColorCube.SetUniformMat3f("u_NormalizedModel", Object_Cube.getNormalizedModelMatrix());
                shaderColorCube.SetUniformMat4f("u_MVP", mvp.getMvpMatrix());

                // render box
                cube.DrawGeometry(shaderColorCube);
                // model.Draw(ModelLoader);
            }

            {
                shaderLight.Bind();

                shaderLight.SetUniform3fv("u_lightColor", lightColor);
                // // draw the texture
                mvp.setMvpMatrix(Projection, p_camera, Light_Cube);
                shaderLight.SetUniformMat4f("u_MVP", mvp.getMvpMatrix());
                // render box
                // newStructure.draw(shaderLight);
                cube.DrawGeometry(shaderLight);
                model.Draw(ModelLoader);
            }

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