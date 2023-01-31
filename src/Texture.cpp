/**
 * @file Texture.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief texture encapsulation implementation
 * @date 2022-09-28
 */

#include "Texture.hpp"

namespace GLTools
{
    Texture::Texture(const char *textureFilePath, GLenum targetTexture, GLenum textureFormat,
                     GLint mipmapLevel, TextureType type, bool flipImage) :
        m_textureMode(targetTexture), m_textureFormat(textureFormat), m_type(type), m_mipmapLevel(mipmapLevel)
    {
        loadTexture(textureFilePath, flipImage);
    }

    Texture::Texture(const char *textureFilePath, GLenum targetTexture, GLTools::Texture::TextureType type,
                     const LoadingParams &params) :
        m_textureMode(targetTexture), m_type(type), m_textureFormat(params.textureFormat)
    {
        loadTexture(textureFilePath, params.flipImage);
    }

    void Texture::loadTexture(const char *textureFilePath, bool flipImage)
    {
        // generate texture
        glGenTextures(1, &m_id);
        // flip image
        stbi_set_flip_vertically_on_load(flipImage); 
        // read data from the file
        const auto dataBuffer = stbi_load(textureFilePath, &m_width, &m_height, &m_nbrChannels, 0);
        if (dataBuffer) {
            if (m_nbrChannels == 1)
                m_colorSpace = GL_RED;
            else if (m_nbrChannels == 3)
                m_colorSpace = GL_RGB;
            else if (m_nbrChannels == 4)
                m_colorSpace = GL_RGBA;
            glBindTexture(m_textureMode, m_id);
            glTexImage2D(m_textureMode, m_mipmapLevel, m_textureFormat, m_width, m_height, 0,
                         m_colorSpace, GL_UNSIGNED_BYTE, dataBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        } else {
            std::cerr << "Failed to load the texture: " << stbi_failure_reason() << std::endl;
        }
        stbi_image_free(dataBuffer);
    }

    void Texture::activate(GLenum textureUnit) const
    {
        glActiveTexture(textureUnit);
        glBindTexture(m_textureMode, m_id);
    }
} // namespace GLTools
