#include "scene_layer.h"

SceneLayer::SceneLayer(Layers& layers) : m_Layers { layers }
{
}

SceneLayer::~SceneLayer()
{
}

void SceneLayer::OnAttach()
{
    m_Scene = std::make_shared<Scene>();

    std::shared_ptr obj0 = m_Scene->CreateGameObject();
    std::shared_ptr obj1 = m_Scene->CreateGameObject();

    ModelAsset model0("assets/models/cube.fbx");
    ImageAsset image0("assets/textures/brick.jpg");

    obj0->AddComponent<Mesh>()->Create(model0, image0);
    obj1->AddComponent<Mesh>()->Create(model0, image0);

    obj0->GetTransform()->SetPosition(0, 0, -10);
    obj1->GetTransform()->SetPosition(4, 0, -10);
}

void SceneLayer::OnUpdate()
{

}

std::shared_ptr<Scene>& SceneLayer::GetScene()
{
	return m_Scene;
}