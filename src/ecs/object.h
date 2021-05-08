#pragma once

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/texture.h"

class Object
{
public:
	Object() = default;
	Object(const std::string& meshFilepath, const std::string& textureFilepath);

	std::shared_ptr<OpenGL::VAO>& GetVAO();
	std::shared_ptr<OpenGL::Texture>& GetTexture();

private:
	std::shared_ptr<OpenGL::VAO> m_VAO;
	std::shared_ptr<OpenGL::Texture> m_Texture;
};