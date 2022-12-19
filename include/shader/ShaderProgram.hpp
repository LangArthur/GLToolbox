/**
 *  Author: Arthur Lang
 *  Create Time: 2022-02-05 14:36:23
 *  Description:
 */

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        inline void use() {
            glUseProgram(m_id);
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

        inline void setVec(const std::string &name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z); 
        }

        inline void setVec(const std::string &name, const glm::vec3 &vec) const {
            glUniform3f(glGetUniformLocation(m_id, name.c_str()), vec.x, vec.y, vec.z); 
        }

        inline void setVec(const std::string &name, float x, float y, float z, float w) const {
            glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w); 
        }

        inline void setVec(const std::string &name, const glm::vec4 &vec) const {
            glUniform4f(glGetUniformLocation(m_id, name.c_str()), vec.x, vec.y, vec.z, vec.w); 
        }

        inline void setMat(const std::string &name, const glm::mat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        inline void setMat(const std::string &name, const glm::mat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        inline void setMat(const std::string &name, const glm::mat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

    private:
        GLuint m_id;
        GLint m_isLinked = GL_FALSE;
};