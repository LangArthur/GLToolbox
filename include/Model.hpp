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
            void draw(ShaderProgram shader);

        private:
            /**
             * @brief Load a model from a path.
             * @details this method handle path error management.
             * @param path path of the model
             */
            void loadModel(const std::string &path);
            /**
             * @brief 
             * 
             * @param node 
             * @param scene 
             */
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType aiType, Texture::TextureType type);

            /*! cached textures based on their file path */
            std::unordered_map<std::string, Texture> m_cachedTextures;
            /*! all meshes which form the model */
            std::vector<Mesh> m_meshes;
            /*! directory where the model is stored */
            std::string m_directory;
    };
} /* namespace GLTools */