#include "scene.h"

void Scene::Add(std::shared_ptr<Object>& object)
{
	m_Objects.push_back(object);
}

std::shared_ptr<Object> Scene::CreateGameObject()
{
	std::shared_ptr<Object> object = std::make_shared<Object>(shared_from_this());
	Add(object);
	return object;
}

const std::vector<std::shared_ptr<Object>>& Scene::GetObjects() const
{
	return m_Objects;
}

unsigned int Scene::GetSelectedObjectID() const
{
	return m_SelectedObjectID;
}

void Scene::SetSelectedObjectID(unsigned int selectedObjectID)
{
	m_SelectedObjectID = selectedObjectID;
}