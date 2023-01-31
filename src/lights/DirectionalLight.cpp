/**
 * @file DirectionalLight.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Directional light implementation
 * @date 2023-01-31
 */

#include "lights/DirectionalLight.hpp"

namespace GLTools
{
    DirectionalLight::DirectionalLight(const std::string &name)
        : m_name(name)
    { }

    void DirectionalLight::render(ShaderProgram &shader)
    {
        shader.setVec(m_name + ".direction", direction);
        shader.setVec(m_name + ".ambient", ambient);
        shader.setVec(m_name + ".diffuse", diffuse);
        shader.setVec(m_name + ".specular", specular);
    }
} /* namespace GLTools */