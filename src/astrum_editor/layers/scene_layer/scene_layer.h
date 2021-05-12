#pragma once

#include "layers/layer.h"
#include "../layers.h"

#include "scene/scene.h"

class SceneLayer : public Layer
{
public:
	SceneLayer(Layers& layers);
	~SceneLayer();

	void OnAttach() override;
	void OnUpdate() override;

	std::shared_ptr<Scene>& GetScene();

private:
	Layers& m_Layers;

	std::shared_ptr<Scene> m_Scene;
};