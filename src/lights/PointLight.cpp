/**
 * @file PointLight.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief PointLight implementation
 * @date 2023-01-31
 */

#include "lights/PointLight.hpp"

namespace GLTools
{
    void PointLight::render(ShaderProgram &shader, const std::string &name)
    {
        shader.setVec((name + ".position").c_str(), position);
        shader.setVec((name + ".ambient").c_str(), ambient);
        shader.setVec((name + ".diffuse").c_str(), diffuse);
        shader.setVec((name + ".specular").c_str(), specular);
        shader.setUniform((name + ".constant").c_str(), constant);
        shader.setUniform((name + ".linear").c_str(), linear);
        shader.setUniform((name + ".quadratic").c_str(), quadratic);
    }
} /* namespace GLTools */