/**
 * @file Mesh.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief declaration of a Mesh object
 * @date 2022-09-21
 */

#pragma once

#include <vector>

#include "Vertex.hpp"
#include "Texture.hpp"
#include "shader/ShaderProgram.hpp"

namespace GLTool
{
    class Mesh
    {
        public:
            Mesh() = default;
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            ~Mesh();

            void draw(ShaderProgram &shader) const;

        private:
            void setUpMesh();

            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Texture> m_textures;

            GLuint m_VAO { 0 };
            GLuint m_VBO { 0 };
            GLuint m_EBO { 0 };
    };
} /* GLTool namespace */