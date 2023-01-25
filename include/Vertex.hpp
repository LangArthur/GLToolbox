/**
 * @file Vertex.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief vertex implementation
 * @date 2022-09-21
 */

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace GLTool
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture;

        Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texture) :
            position(position), normal(normal), texture(texture)
        { }
    };
    
} // namespace GLTool
