/**
 * @file Mesh.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief declaration of a Mesh object
 * @date 2022-09-21
 */

#include "Mesh.hpp"

namespace GLTool
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
        m_vertices(vertices), m_indices(indices), m_textures(textures)
    {
        setUpMesh();
    }

    Mesh::~Mesh()
    { }

    void Mesh::setUpMesh()
    {
        glGenVertexArrays(1, &m_VAO);
    	glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW); // FIXME: check if data works here
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW); // idem
        
        // positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, position)));
        // normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));
        // texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, texture)));

        glBindVertexArray(0);
    }

    void Mesh::draw(ShaderProgram &shader)
    {
        unsigned int diffuseNbr = 1;
        unsigned int specularNbr = 1;
        for (unsigned int i = 0; i < m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name;
            if (m_textures[i].type() == Texture::TextureType::DIFFUSE)
            {
                number = std::to_string(diffuseNbr++);
                name = "diffuse";
            }
            else if (m_textures[i].type() == Texture::TextureType::SPECULAR)
            {
                number = std::to_string(specularNbr++);
                name = "specular";
            }
            shader.setUniform(("material." + name + number).c_str(), m_textures[i].id());
            glBindTexture(GL_TEXTURE_2D, m_textures[i].id());
        }
        glActiveTexture(GL_TEXTURE0);

        // draw mesh
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

} /* GLTool namespace */

