#include "mesh.h"

void Mesh::Create(ModelAsset& modelAsset, ImageAsset& imageAsset)
{
	m_VAO = std::make_shared<OpenGL::VAO>(modelAsset.Vertices, Vertex::GetLayout(), modelAsset.Indices);

    m_Texture = std::make_shared<OpenGL::Texture>(
        imageAsset.Size,
        imageAsset.Data,
        GL_RGB,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        std::vector<OpenGL::Texture::param_t> {
            { OpenGL::ParamType::Int, GL_TEXTURE_MIN_FILTER, GL_LINEAR },
            { OpenGL::ParamType::Int, GL_TEXTURE_MAG_FILTER, GL_LINEAR },
        }
    );
}