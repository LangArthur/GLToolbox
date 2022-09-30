/**
 *  Author: Arthur Lang
 *  Create Time: 2022-02-05 14:36:23
 *  Description:
 */

#pragma once

#include "Shader.hpp"

class ShaderProgram
{
    public:
        ShaderProgram(const std::vector<Shader> shaders);
        ~ShaderProgram();

        inline GLuint id() {
            return m_id;
        }

        inline bool ready() {
            return m_isLinked != GL_FALSE;
        }

        inline void setUniform(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value));
        }

        inline void setUniform(const std::string &name, int value) const {
            glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
        }

        inline void setUniform(const std::string &name, float value) const {
            glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
        }

    private:
        GLuint m_id;
        GLint m_isLinked = GL_FALSE;
};