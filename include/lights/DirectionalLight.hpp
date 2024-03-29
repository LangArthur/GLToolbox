/**
 * @file DirectionalLight.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Encapsulation of Directional light
 * @date 2023-01-31
 */

#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "shader/ShaderProgram.hpp"

namespace GLTools
{
    /**
     * @brief A light which emit to infinity from a specific direction
     */
    struct DirectionalLight
    {
        public:
            /**
             * @brief Construct a new Directional Light object
             */
            DirectionalLight() = default;
            /**
             * @brief Destroy the Directional Light object
             */
            ~DirectionalLight() = default;

            /**
             * @brief set light uniform to a shader
             * @param shader shader to use.
             * @param name name of the light in the shader.
             */
            void render(ShaderProgram &shader, const std::string &name);

            /* direction of the light */
            glm::vec3 direction;
            /* light ambient component */
            glm::vec3 ambient;
            /* light diffuse component */
            glm::vec3 diffuse;
            /* light specular component */
            glm::vec3 specular;
    };
    
} /* namespace GLTools */