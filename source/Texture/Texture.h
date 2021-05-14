#pragma once

#include "../precomz.h"

#include "../Renderer/Renderer.h"
#include "../Shaders/ShaderInitialize.h"

// Logger file
#include "../Core/LogFile.h"

class ShaderInitialize;

class Texture
{
private:
    /* data */
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    std::string type;
    unsigned int unit;

public:
    Texture(std::string path, std::string typeName, unsigned int slot);
    ~Texture();
    void Bind(unsigned int slot=0) const;
    void Unbind() const;
    void ReBind(std::string path);
    Texture(const std::string &path);
    // Assigns a texture unit to a texture
    void texUnit(ShaderInitialize &shader, const char *uniform, unsigned int unit);
    void LoadImage();
    // Deletes a texture
    void Delete();

    
    std::string GetType() const { return type; };
    std::string GetFilePath() const { return m_FilePath; };
    inline int GetWidth() const { return m_Width; };
    inline int GetHeight() const { return m_Height; };
    unsigned int GetTextureId() const { return m_RendererID; };
};
