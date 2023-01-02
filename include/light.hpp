#pragma once

/* Some lights type declaration. It is not used at the moment but might be at some points */

#include <glm/vec3.hpp>

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

