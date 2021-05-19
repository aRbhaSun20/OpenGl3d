#include "index.h"

// camera
glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

#define WIDTH 960
#define HEIGHT 560

// timing
float lastFrame = 0.0f;

float lastX = WIDTH / 1.0;
float lastY = HEIGHT / 1.0;

bool firstMouse = true;
Timestep timestep;

// Log FIle
Logger::LogFile LogFile;

// view matrix defination
PerspectiveCamera p_camera(LogFile, {0.0f, 0.0f, 3.0f});

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main(int argc, char *argv[])
{
    // glfw initializations
    CORE_WARN("Current Execution Starting");

    Initialize Initiate(WIDTH, HEIGHT, "InitGL", LogFile);

    // Commands Executioner
    ExecuteCommands ExeCommands(LogFile);

    // Event handler
    Event EventHandler(Initiate.getWindowReference(), p_camera, timestep, WIDTH, HEIGHT, LogFile);

    glfwSetScrollCallback(Initiate.getWindowReference(), scroll_callback);
    glfwSetInputMode(Initiate.getWindowReference(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad initializations
    Initiate.Gladinitialization();

    // start the declarations from here
    {
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        CubeStructures cube(LogFile);
        Model model("../Models/Cube/cube.obj", LogFile);

        ShaderInitialize shaderColorCube("../source/Shaders/Color.shader", LogFile);

        ShaderInitialize shaderLight("../source/Shaders/Light.shader", LogFile);

        ShaderInitialize ModelLoader("../source/Shaders/loading.shader", LogFile);

        // projection matrix defination
        float Field_Of_View = 60.0f; //greater results zoom out ,vice-versa
        float AspectRatio = lastX / lastY;
        ProjectionMatrix Projection(Field_Of_View, AspectRatio, 0.1f, 100.0f, LogFile);

        //Object model matrix defination
        glm::vec3 Object_Translation(-0.25f, -0.25f, 0.0f);
        float Object_Angle = 0.0f;
        glm ::vec3 Object_AxisRotation(0.0f, 0.0f, 0.0f);
        ModelMatrix Object_Cube(Object_Translation, Object_Angle, Object_AxisRotation, LogFile);
        Object_Cube.setModelScale(0.5);

        //Light model matrix defination
        glm::vec3 Light_Translation(1.2f, 1.0f, 0.8f);
        float Light_Angle = 0.0f;
        glm ::vec3 Light_AxisRotation(0.0f, 0.0f, 0.0f);
        ModelMatrix Light_Cube(Light_Translation, Light_Angle, Light_AxisRotation, LogFile, 0.2f);

        // Mvp matrix defination
        MvpMatrix mvp(LogFile);

        Texture Wooden_Box(LogFile, "../images/woodenContainer.png");
        Wooden_Box.Bind(0);
        Texture Steel_Frame(LogFile, "../images/woodenContainerSspecular.png");
        Steel_Frame.Bind(1);

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // select light type
        Light lightType(LightType::SpotLightSource, "Gold", LogFile);

        // select bg color
        float BGcolor[4] = {0.4f, 0.2f, 0.2f, 1.0f};
        shaderColorCube.SetUniform1i("u_Material.diffuseTexture", 0);
        shaderColorCube.SetUniform1i("u_Material.specularTexture", 1);

        ImguiHandle Imhand(Initiate, ExeCommands, "#version 330", LogFile);

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
                Object_Cube.setModelRotation(timestep.GetSeconds(), {0.0f, 1.0f, 0.0f});
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
            }

            {
                shaderLight.Bind();
                ModelLoader.Bind();
                shaderLight.SetUniform3fv("u_lightColor", lightColor);
                // // draw the texture
                mvp.setMvpMatrix(Projection, p_camera, Light_Cube);
                // shaderLight.SetUniformMat4f("u_MVP", mvp.getMvpMatrix());
                ModelLoader.SetUniformMat4f("u_MVP", mvp.getMvpMatrix());
                // render box
                model.Draw(ModelLoader);
            }

            {
                Imhand.CreateNewFrame();
                // Imhand.Begin();

                // Imhand.End();

                Imhand.DestroyCreatedFrame();
            }

            glfwSwapBuffers(Initiate.getWindowReference());
            glfwPollEvents();
        }
    }
    CORE_WARN("Current Execution Complete");

    return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    p_camera.ProcessMouseScroll(yoffset);
}