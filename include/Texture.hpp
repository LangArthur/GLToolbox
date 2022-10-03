/**
 * @file Texture.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief texture declaration
 * @date 2022-09-28
 */

#include <iostream>

#include <stb_image.h>
#include <GL/glew.h>

namespace GLTool
{
    class Texture
    {
        public:
            /**
             * @brief Construct a new Texture object.
             * @param textureFilePath path to the texture file.
             * @param targetTexture mode of the texture (2D, 3D ...)
             * @param textureFormat format of the data stored into the texture
             * @param colorSpace color space of texture inside the file
             */
            Texture(const char *textureFilePath, GLenum targetTexture, GLenum textureFormat, GLenum colorSpace);
            ~Texture() = default;

            inline const GLuint id() const {
                return m_id;
            };

            /**
             * @brief activate the texture to a specific texture unit.
             * @param textureUnit texture unit id.
             */
            void activate(GLenum textureUnit) const;

        private:
            GLint m_mipmapLevel = 0;
            /* type of the current texture */
            GLenum m_textureType = GL_NONE;
            /* format store into the texture */
            GLenum m_textureFormat = GL_RGB;
            // texture details
            int m_width = 0;
            int m_height = 0;
            int m_nbrCHannels = 0;
            /* id of the texture */
            GLuint m_id = 0;
            /* if the texture has alpha channel*/
            bool m_isAlpha = false;
    };
} // namespace GLTool
