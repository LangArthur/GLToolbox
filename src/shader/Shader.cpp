/**
 *  Author: Arthur Lang
 *  Create Time: 2022-02-05 12:00:00
 *  Description:
 */

#include "shader/Shader.hpp"

Shader::Shader(unsigned int shaderType, const char *shaderPath) : m_id(glCreateShader(shaderType))
{
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(shaderPath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();

        std::cout << "Compiling shader: " << shaderPath << "\n";
    	char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(m_id, 1, &VertexSourcePointer, 0);
        glCompileShader(m_id);

        // check compilation
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &m_isCompile);
        if (m_isCompile == GL_FALSE) {
            GLint maxLen = 0;
            glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLen);

            std::vector<GLchar> log(maxLen);
            glGetShaderInfoLog(m_id, maxLen, &maxLen, log.data());

            glDeleteShader(m_id);

            std::cerr << "Shader compilation failed: \n" << log.data();
        }
	} else
        std::cerr << "Error opening shader file\n";
}