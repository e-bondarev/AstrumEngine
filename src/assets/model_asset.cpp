#include "model_asset.h"

void ModelAsset::Load(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(ASTRUM_ROOT + path, aiProcess_Triangulate);

    if (!scene)
    {
        A_LOG_OUT("Failed to import model: " << importer.GetErrorString() << '\n');
        return;
    }

    const aiMesh* mesh = scene->mMeshes[0];

    Vertices.resize(mesh->mNumVertices);

    for (int v = 0; v < mesh->mNumVertices; v++)
    {
        Vertices[v].position = { mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z };
        Vertices[v].normal = { mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z };

        if (mesh->mTextureCoords[0])
        {
            Vertices[v].uv = { mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y };
        }
    }

    for (int f = 0; f < mesh->mNumFaces; f++)
    {
        for (int i = 0; i < 3 /* mesh->mFaces[f].mNumIndices */; i++)
        {
            Indices.push_back(mesh->mFaces[f].mIndices[i]);
        }
    }
}

ModelAsset::ModelAsset(const std::string& path)
{
    Load(path);
}