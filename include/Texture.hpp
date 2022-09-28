/**
 * @file Texture.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief texture declaration
 * @date 2022-09-28
 */

#include <stb_image.h>
#include <GL/glew.h>

#include "Logger.hpp"

namespace GLTool
{
    class Texture
    {
        public:
            Texture(GLenum textureMode, const char *textureFilePath);
            ~Texture();

        private:
            GLint m_mipmapLevel = 0;
            GLenum m_textureFormat = GL_RGB;
            // texture details
            int m_width = 0;
            int m_height = 0;
            int m_nbrCHannels = 0;
            GLuint m_id = 0;
    };
} // namespace GLTool
