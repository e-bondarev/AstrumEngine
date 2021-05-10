#pragma once

#include "component.h"

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/texture.h"

#include "assets/model_asset.h"
#include "assets/image_asset.h"

class Mesh : public Component
{
public:
	Mesh() : Component("Mesh") {}

	std::shared_ptr<OpenGL::VAO> m_VAO;
	std::shared_ptr<OpenGL::Texture> m_Texture;

	void Create(ModelAsset& modelAsset, ImageAsset& imageAsset);
	void Render();
};

REGISTER(Mesh);