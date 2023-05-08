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

namespace GLTools
{
    /**
     * @brief Represent an element composed by vertices.
     */
    class Mesh
    {
        public:
            /**
             * @brief default empty constructor
             */
            Mesh() = default;
            /**
             * @brief construct a Mesh
             * @param vertices list of all vertices.
             * @param indices indices linked to vertices.
             * @param textures texture coordinate for all vertices.
             */
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            /**
             * @brief Mesh destructor.
             */
            ~Mesh();

            /**
             * @brief Render a mesh.
             * @param shader shader used for the rendering.
             */
            void draw(ShaderProgram &shader) const;

        private:
            /**
             * @brief Instantiate buffers of the mesh.
             */
            void setUpMesh();

            /*! vertices of the mesh. */
            std::vector<Vertex> m_vertices;
            /*! indices of all vertices. */
            std::vector<unsigned int> m_indices;
            /*! textures used for the mesh. */
            std::vector<Texture> m_textures;

            /*! VAO index */
            GLuint m_VAO { 0 };
            /*! VBO index */
            GLuint m_VBO { 0 };
            /*! EBO index */
            GLuint m_EBO { 0 };
    };
} /* GLTools namespace */