#pragma once

/** some stuff about materials. It is not used at the moment but might be at some point */

#include <glm/vec3.hpp>

struct Material {

    // for texture
    // in shader
    // sampler2D diffuse;
    // sampler2D specular;

    // for color
    glm::vec3 diffuse;
    glm::vec3 specular;

    float shininess;
}; 
