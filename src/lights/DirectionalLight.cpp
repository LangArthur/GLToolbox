/**
 * @file DirectionalLight.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Directional light implementation
 * @date 2023-01-31
 */

#include "lights/DirectionalLight.hpp"

namespace GLTools
{
    void DirectionalLight::render(ShaderProgram &shader, const std::string &name)
    {
        shader.setVec(name + ".direction", direction);
        shader.setVec(name + ".ambient", ambient);
        shader.setVec(name + ".diffuse", diffuse);
        shader.setVec(name + ".specular", specular);
    }
} /* namespace GLTools */