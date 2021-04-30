#pragma once

#include "pch.h"

#include "gpu/vertex_layouts/vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

struct Asset
{
    virtual void load(const std::string& path) = 0;
};

struct ModelAsset : public Asset
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    void load(const std::string& path) override
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

        if (!scene)
        {
            A_LOG_OUT("Failed to import model: " << importer.GetErrorString() << '\n');
            return;
        }

        const aiMesh* mesh = scene->mMeshes[0];

        vertices.resize(mesh->mNumVertices);

        for (int v = 0; v < mesh->mNumVertices; v++)
        {
            vertices[v].position = { mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z };
            vertices[v].normal = { mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z };
            // vertices[v].position = { 0,0,0 };
            // vertices[v].normal = { 0,0,0 };

            if (mesh->mTextureCoords[0])
            {
                vertices[v].uv = { mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y };
                // vertices[v].uv = { 0,0 };
            }
        }

        for (int f = 0; f < mesh->mNumFaces; f++)
        {
            // A_DEBUG_LOG_OUT(mesh->mFaces[f].mNumIndices);
            // for (int i = 0; i < mesh->mFaces[f].mNumIndices; i++)
            for (int i = 0; i < 3; i++)
            {
                indices.push_back(mesh->mFaces[f].mIndices[i]);
            }
        }
    }
};

struct ImageAsset : public Asset
{
    void load(const std::string& path) override
    {
        
    }
};