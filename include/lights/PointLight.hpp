/**
 * @file PointLight.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Point light declaration
 * @date 2023-01-31
 */

#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "shader/ShaderProgram.hpp"

namespace GLTools
{
    /**
     * @brief A light which emit from a position in all directions and fade out in the distance
     */
    struct PointLight
    {
        public:
            /**
             * @brief Construct a new Point Light object
             */
            PointLight() = default;
            ~PointLight() = default;

            /**
             * @brief set light uniform to a shader
             * @param shader shader to use.
             * @param name name of the light in the shader.
             */
            void render(ShaderProgram &shader, const std::string &name);

            /* position of the point light */
            glm::vec3 position;
            /* light ambient component */
            glm::vec3 ambient;
            /* light diffuse component */
            glm::vec3 diffuse;
            /* light specular component */
            glm::vec3 specular;

            /* constant of the attenuation formula. Usually kept to 1 */
            float constant;
            /* linear term of the attenuation formula, which represent light decrease at close position */
            float linear;
            /* quadratic term of the attenuation formula, which represent light decrease at far position */
            float quadratic;
    };
    
} /* namespace GLTools */