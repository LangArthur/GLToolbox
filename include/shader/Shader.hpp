/**
 *  Author: Arthur Lang
 *  Create Time: 2022-02-05 12:00:05
 *  Description:
 */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

class Shader {

    public:
        Shader(unsigned int shaderType, const char *shaderPath);
        ~Shader() = default;

        inline GLuint id()
        {
            return m_id;
        }
        inline bool ready()
        {
            return m_isCompile == GL_TRUE;
        }

    private:
        GLuint m_id;
        GLint m_isCompile { GL_FALSE };
};