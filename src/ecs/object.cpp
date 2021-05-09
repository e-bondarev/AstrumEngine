#include "pch.h"

#include "object.h"

#include "assets/assets.h"

Object::Object(const std::string& meshFilepath, const std::string& textureFilepath)
{
	ModelAsset modelAsset(meshFilepath);
	m_VAO = std::make_shared<OpenGL::VAO>(modelAsset.Vertices, Vertex::GetLayout(), modelAsset.Indices);

	ImageAsset imageAsset(textureFilepath);
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

    m_Transform = std::dynamic_pointer_cast<Transform>(AddComponent("Transform"));
}

std::shared_ptr<Transform> Object::GetTransform()
{
    return m_Transform;
}

std::shared_ptr<OpenGL::VAO>& Object::GetVAO()
{
    return m_VAO;
}

std::shared_ptr<OpenGL::Texture>& Object::GetTexture()
{
    return m_Texture;
}