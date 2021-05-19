#pragma once
#include <Precomz/precomz.h>

#include <glm/glm.hpp> //maths library

#include "../Shaders/ShaderInitialize.h"
#include "../Core/LightType.h"
#include "../Materials/Materials.h"

// Logger file
#include "../Core/LogFile.h"

class Materials;

class Light
{
private:
    /* data */
    Materials material;
    unsigned char Lighttype;
    std::string l_MaterialType;
    Logger::LogFile &p_File;

private:
    // ambient material vector is the color the surface reflects under ambient lighting, usually the surface color
    glm::vec3 ambientStrength;
    glm::vec3 ambientIntensity;

    // diffuse material vector is the color the surface reflects under diffuse lighting, usually the desired surface color
    glm::vec3 diffuseStrength;
    glm::vec3 diffuseIntensity;

    // specular material vector sets the color of specular highlight on the surface or surface specific color
    glm::vec3 specularStrength;
    glm::vec3 specularIntensity;
    glm::vec3 LightDirection;
    float SpotCutoff;
    float SpotOuterCutoff;
    glm::vec3 whiteDefault = {1.0f, 1.0f, 1.0f};

private:
    // common to all light source
    float constant_source;
    float linear_source;
    float quadratic_source;

public:
    Light(unsigned char ltype, std::string MaterialType, Logger::LogFile &LogFile)
        : Lighttype(ltype), l_MaterialType(MaterialType), p_File(LogFile)
    {
        setMaterialLight(MaterialType);
        CORE_INFO("Particular Material Light Properties selected");
    }

    ~Light()
    {
        CORE_WARN("Light Declaration Closing");
    }

    void setMaterialLight(std::string MaterialType)
    {
        l_MaterialType = MaterialType;
        auto materialSelected_Ambient = material.getMaterialArrayProperties(l_MaterialType.c_str(), "Ambient");
        auto materialSelected_Diffuse = material.getMaterialArrayProperties(l_MaterialType.c_str(), "Diffuse");
        auto materialSelected_Specular = material.getMaterialArrayProperties(l_MaterialType.c_str(), "Specular");
        float materialSelected_Shininess = material.getMaterialFloatProperties(l_MaterialType.c_str(), "Shininess") * 128.0f;

        // ambient material vector is the color the surface reflects under ambient lighting, usually the surface color
        ambientStrength = {materialSelected_Ambient[0], materialSelected_Ambient[1], materialSelected_Ambient[2]};
        ambientIntensity = {0.9f, 0.9f, 0.9f};
        // diffuse material vector is the color the surface reflects under diffuse lighting, usually the desired surface color
        diffuseStrength = {materialSelected_Diffuse[0], materialSelected_Diffuse[1], materialSelected_Diffuse[2]};
        diffuseIntensity = {0.8f, 0.8f, 0.8f};
        // specular material vector sets the color of specular highlight on the surface or surface specific color
        specularStrength = {materialSelected_Specular[0], materialSelected_Specular[0], materialSelected_Specular[0]};
        specularIntensity = {1.0f, 1.0f, 1.0f};

        constant_source = 1.0f;
        linear_source = 0.0014f;
        quadratic_source = 0.000007f;
        SpotCutoff = glm::cos(glm::radians(12.5f));
        SpotOuterCutoff = glm::cos(glm::radians(17.5f));
    }

    void bindLight(ShaderInitialize &Lightshader, glm::vec3 Orientation)
    {
        Lightshader.SetUniform1i("lightType", Lighttype);

        // ambient
        Lightshader.SetUniform3fv("u_Material.ambientComp.ambientStrength", ambientStrength);
        Lightshader.SetUniform3fv("u_Material.ambientComp.ambientIntensity", ambientIntensity);
        // diffuse
        Lightshader.SetUniform3fv("u_Material.diffuseComp.diffuseStrength", diffuseStrength);
        Lightshader.SetUniform3fv("u_Material.diffuseComp.diffuseIntensity", diffuseIntensity);
        // specular
        Lightshader.SetUniform3fv("u_Material.specularComp.specularStrength", specularStrength);
        Lightshader.SetUniform3fv("u_Material.specularComp.specularIntensity", specularIntensity);

        if (Lighttype == LightType::SpotLightSmoothSource)
        {
            Lightshader.SetUniform1f("u_Material.spotSource.outerCutOff", SpotOuterCutoff);
        }

        if (Lighttype == LightType::SpotLightSource || Lighttype == LightType::SpotLightSmoothSource)
        {
            LightDirection = Orientation;
            Lightshader.SetUniform3fv("u_Material.spotSource.direction", LightDirection);
            Lightshader.SetUniform1f("u_Material.spotSource.cutOff", SpotCutoff);
        }

        if (Lighttype == LightType::PointLightSource || Lighttype == LightType::SpotLightSource || Lighttype == LightType::SpotLightSmoothSource)
        {
            Lightshader.SetUniform1f("u_Material.pointSource.constant_Pointsource", constant_source);
            Lightshader.SetUniform1f("u_Material.pointSource.linear_Pointsource", linear_source);
            Lightshader.SetUniform1f("u_Material.pointSource.quadratic_Pointsource", quadratic_source);
        }
        if (Lighttype != LightType::NoLightSource)
        {
            Lightshader.SetUniform3fv("u_Color", whiteDefault);
        }
    }
};
