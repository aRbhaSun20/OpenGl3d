#include "Texture.h"

Texture::Texture(std::string path, std::string typeName, unsigned int slot)
    : m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    // Assigns the type of the texture ot the texture object
    type = typeName;

    glGenTextures(1, &m_RendererID);

    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (m_LocalBuffer)
    {
        Bind(slot);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Check what type of color channels the texture has and load it accordingly
        if (m_BPP == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        else if (m_BPP == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
        else if (m_BPP == 1)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, m_LocalBuffer);
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");

        // Generates MipMaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(m_LocalBuffer);
        Unbind();
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

Texture::Texture(const std::string &path)
    : m_FilePath(path), m_LocalBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    LoadImage();
}

void Texture::LoadImage()
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (m_LocalBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(m_LocalBuffer);
}

void Texture::texUnit(ShaderInitialize &shader, const char *uniform, unsigned int unit)
{
    // Gets the location of the uniform
    unsigned int texUni = glGetUniformLocation(shader.GetRendererId(), uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Bind();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}
void Texture::ReBind(std::string path)
{
    Unbind();
    m_FilePath = path;
    m_LocalBuffer = nullptr;
    m_Width = 0;
    m_Height = 0;
    m_BPP = 0;
    LoadImage();
    Bind();
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &m_RendererID);
}
