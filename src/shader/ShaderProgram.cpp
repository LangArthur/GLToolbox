/**
 *  Author: Arthur Lang
 *  Create Time: 2022-02-05 14:36:18
 *  Description:
 */

#include "shader/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(std::vector<Shader> shaders)
{
    m_id = glCreateProgram();
    for (auto &shader : shaders) {
        if (shader.ready()) {
            glAttachShader(m_id, shader.id());
            m_attachedShaders++;
        } else
            std::cerr << "Dropping shader " << shader.id() << std::endl;
    }
    if (m_attachedShaders == shaders.size()) {
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &m_isLinked);
        if (m_isLinked == GL_FALSE) {
            GLint maxLen = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLen);

            std::vector<GLchar> log(maxLen);
            glGetProgramInfoLog(m_id, maxLen, &maxLen, log.data());
            // cleaning resources
            glDeleteProgram(m_id);
            for (auto &shader : shaders) {
                glDeleteShader(shader.id());
            }
            std::cerr << "Shader linking failed: " << log.data() << std::endl;
        } else {
            for (auto &shader : shaders) {
                glDetachShader(m_id, shader.id());
                glDeleteShader(shader.id());
            }
        }
    }
}

ShaderProgram::~ShaderProgram()
{
}
