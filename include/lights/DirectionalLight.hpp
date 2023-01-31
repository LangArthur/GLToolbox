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
    class DirectionalLight
    {
        public:
            /**
             * @brief Construct a new Directional Light object
             * @param name name of the light used in the shader
             */
            DirectionalLight(const std::string &name);
            /**
             * @brief Destroy the Directional Light object
             */
            ~DirectionalLight() = default;

            /**
             * @brief set light uniform to a shader
             * @param shader shader to use.
             */
            void render(ShaderProgram &shader);

            /* direction of the light */
            glm::vec3 direction;
            /* light ambient component */
            glm::vec3 ambient;
            /* light diffuse component */
            glm::vec3 diffuse;
            /* light specular component */
            glm::vec3 specular;

        private:
            /* name of the light, used in the shader */
            std::string m_name;
    };
    
} /* namespace GLTools */