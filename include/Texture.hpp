/**
 * @file Texture.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief texture declaration
 * @date 2022-09-28
 */

#pragma once

#include <iostream>

#include <stb_image.h>
#include <GL/glew.h>

namespace GLTool
{
    class Texture
    {
        public:

            enum class TextureType {
                DIFFUSE, SPECULAR
            };

            struct LoadingParams
            {
                GLenum textureFormat = GL_RGBA;
                GLint mipmapLevel = 0;
                bool flipImage = false;
            };

            Texture() = default;
            /**
             * @brief Construct a new Texture object from an existing file.
             * @param textureFilePath path to the texture file.
             * @param textureMode mode of the texture (2D, 3D ...)
             * @param textureFormat format of the data stored into the texture.
             * @param type type of the texture (diffuse, specular ...).
             * @param flipImage flip image on load.
             */
            Texture(const char *textureFilePath, GLenum textureMode, GLenum textureFormat, GLint mipmapLevel, TextureType type, bool flipImage);
            Texture(const char *textureFilePath, GLenum textureMode, GLTool::Texture::TextureType type, const LoadingParams &params);
            ~Texture() = default;

            /* Getters */
            inline const GLuint id() const
            {
                return m_id;
            };

            inline const TextureType type() const
            {
                return m_type;
            };

            /**
             * @brief activate the texture to a specific texture unit.
             * @param textureUnit texture unit id.
             */
            void activate(GLenum textureUnit) const;

        private:
            void loadTexture(const char *textureFilePath, bool flipImage);

            /* type of the texture */
            TextureType m_type;
            GLint m_mipmapLevel = 0;
            /* type of the current texture */
            GLenum m_textureMode = GL_NONE;
            /* format store into the texture */
            GLenum m_textureFormat = GL_RGB;
            /* color space store in the texture file */
            GLenum m_colorSpace;
            // texture details
            int m_width = 0;
            int m_height = 0;
            int m_nbrChannels = 0;
            /* id of the texture */
            GLuint m_id = 0;
            /* if the texture has alpha channel*/
            bool m_isAlpha = false;
    };
} // namespace GLTool
