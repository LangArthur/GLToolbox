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
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform1i(loc, static_cast<int>(value));
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setUniform(const std::string &name, int value) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform1i(loc, value);
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setUniform(const std::string &name, float value) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform1f(loc, value);
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setVec(const std::string &name, float x, float y, float z) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform3f(loc, x, y, z); 
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setVec(const std::string &name, const glm::vec3 &vec) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform3f(loc, vec.x, vec.y, vec.z); 
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setVec(const std::string &name, float x, float y, float z, float w) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform4f(loc, x, y, z, w); 
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setVec(const std::string &name, const glm::vec4 &vec) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniform4f(loc, vec.x, vec.y, vec.z, vec.w); 
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setMat(const std::string &name, const glm::mat2 &mat) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setMat(const std::string &name, const glm::mat3 &mat) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

        inline void setMat(const std::string &name, const glm::mat4 &mat) const {
            GLint loc = glGetUniformLocation(m_id, name.c_str());
            if (loc != -1) {
                glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
            } else {
                throw std::runtime_error(std::string(name) + " is not a valid uniform.");
            }
        }

    private:
        GLuint m_id;
        GLint m_isLinked = GL_FALSE;
};