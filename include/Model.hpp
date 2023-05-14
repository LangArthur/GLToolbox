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
            Model() = default;
            /**
             * @brief Construct a new Model
             * @param path path of the model file (.obj for example)
             */
            Model(const std::string &path);
            /**
             * @brief Default destructor
             */
            ~Model() = default;

            /**
             * @brief draw the model.
             * @param shader shader used for the drawing.
             */
            void draw(ShaderProgram &shader);

        private:
            /**
             * @brief Load a model from a path.
             * @details this method handle path error management.
             * @param path path of the model
             */
            void loadModel(const std::string &path);
            /**
             * @brief iterate through each node to load meshes.
             * It intentionally go through children instead of iterate through the full mesh array.
             * @param node current node to process.
             * @param scene global model infos.
             */
            void processNode(aiNode *node, const aiScene *scene);
            /**
             * @brief convert an aiMesh to a Mesh
             * @param mesh the mesh infos
             * @param scene global model infos.
             * @return Mesh a newly created mesh.
             */
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            /**
             * @brief create a vector of textures from aiMaterial.
             * @param mat the ai material.
             * @param aiType the ai type.
             * @param type the texture type.
             * @return std::vector<Texture> the full list of textures extracts from mat.
             */
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType aiType, Texture::TextureType type);

            /*! cached textures based on their file path */
            std::unordered_map<std::string, Texture> m_cachedTextures;
            /*! all meshes which form the model */
            std::vector<Mesh> m_meshes;
            /*! directory where the model is stored */
            std::string m_directory;
    };
} /* namespace GLTools */