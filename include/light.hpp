#pragma once

/* Some lights type declaration. It is not used at the moment but might be at some points */

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    /**
     * @brief Get the Attenuation
     * This function should be calculate in a shader. It is implemented here for keeping track of it.
     * @param dist distance between the light and the fragment position
     * @return float, the attenuation value
     */
    float getAttenuation(float dist) {
        return 1.0 / (constant + linear * dist + quadratic * dist * dist);
    }
};

struct SpotLight {
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff; // store a cos of an angle to avoid heavy calculation in shader

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    /**
     * @brief check if a fragment position is into the spot light.
     * This function should be calculate in a shader. It is implemented here for keeping track of it.
     * @param FragPos position of the fragment.
     * @return bool, true if the fragment is in the spot light, false otherwise.
     */
    bool isInSpot(glm::vec3 FragPos) {
        glm::vec3 lightDir = glm::normalize(position - FragPos);
        float theta = glm::dot(lightDir, glm::normalize(-direction));
        return theta > cutOff; // here it is cosine comparison
    }
};
