/**
 * @file Model.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Model implementation
 * @date 2023-01-25
 */

#include "Model.hpp"

namespace GLTools
{
    Model::Model(const std::string &path)
    {
        m_directory = path.substr(0, path.find_last_of('/'));
        loadModel(path);
    }

    void Model::loadModel(const std::string &path)
    {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
        {
            std::cerr << "Failed to import model: " << importer.GetErrorString() << "\n";
            return;
        }
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            m_meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
        }
        // process childrens
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        vertices.reserve(mesh->mNumVertices);
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        // retrieve vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.position = {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z,
            };
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z,
            };

            if (mesh->mTextureCoords[0])
            {
                vertex.texture = {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y,
                };
            }
            else
            {
                vertex.texture = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }
        // retrieve indices
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }  
        // retrieve textures
        if (mesh->mMaterialIndex != 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                               aiTextureType_DIFFUSE, Texture::TextureType::DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material, 
                                                aiTextureType_SPECULAR, Texture::TextureType::SPECULAR);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType aiType, Texture::TextureType type)
    {
        GLTools::Texture::LoadingParams loadingParams {
            .textureFormat = GL_RGBA,
            .mipmapLevel = 0,
            .flipImage = true,
        };
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
        {
            aiString texturePath;
            mat->GetTexture(aiType, i, &texturePath);
            if (m_cachedTextures.find(texturePath.C_Str()) == m_cachedTextures.end())
            {
                Texture newTexture((m_directory + '/' + texturePath.C_Str()).c_str(), GL_TEXTURE_2D, type, loadingParams);
                textures.push_back(newTexture);
                m_cachedTextures.emplace(texturePath.C_Str(), newTexture);
            }
            else
            {
                textures.push_back(m_cachedTextures[texturePath.C_Str()]);
            }
        }
        return textures;
    }

    void Model::draw(ShaderProgram shader)
    {
        for (const auto &mesh : m_meshes)
        {
            mesh.draw(shader);
        }
    }

} /* namespace GLTools */