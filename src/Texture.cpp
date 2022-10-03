/**
 * @file Texture.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief texture encapsulation implementation
 * @date 2022-09-28
 */

#include "Texture.hpp"

namespace GLTool
{
    Texture::Texture(const char *textureFilePath, GLenum targetTexture, GLenum textureFormat, GLenum colorSpace) :
        m_textureType(targetTexture), m_textureFormat(textureFormat)
    {
        // generate texture
        glGenTextures(1, &m_id);
        glBindTexture(m_textureType, m_id);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        // flip image // TODO: integrate this properly
        stbi_set_flip_vertically_on_load(true); 
        // read data from the file
        const auto dataBuffer = stbi_load(textureFilePath, &m_width, &m_height, &m_nbrCHannels, 0);
        if (dataBuffer) {
            glTexImage2D(m_textureType, m_mipmapLevel, m_textureFormat, m_width, m_height, 0, colorSpace, GL_UNSIGNED_BYTE, dataBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load the texture" << std::endl;
        }
        stbi_image_free(dataBuffer);
    }

    void Texture::activate(GLenum textureUnit) const
    {
        glActiveTexture(textureUnit);
        glBindTexture(m_textureType, m_id);
    }
} // namespace GLTool
