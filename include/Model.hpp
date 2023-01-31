/**
 * @file Model.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Model declaration
 * @date 2023-01-25
 */

#pragma once

#include <string>
#include <vector>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader/ShaderProgram.hpp"
#include "Mesh.hpp"

namespace GLTools
{
    class Model
    {
        public:
            Model(const std::string &path);
            ~Model() = default;

            void draw(ShaderProgram shader);

        private:
            void loadModel(const std::string &path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType aiType, Texture::TextureType type);

            /* cached textures based on their file path */
            std::unordered_map<std::string, Texture> m_cachedTextures;
            std::vector<Mesh> m_meshes;
            std::string m_directory;
    };
} /* namespace GLTools */