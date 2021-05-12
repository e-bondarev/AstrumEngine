#pragma once

#include "ecs/object.h"

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene() = default;

	template <typename... Args>
	Scene(Args... objects) : m_Objects { { std::forward<Args>(objects)... } } { }

	void Add(std::shared_ptr<Object>& object);
	std::shared_ptr<Object> CreateGameObject();

	const std::vector<std::shared_ptr<Object>>& GetObjects() const;
	
	unsigned int GetSelectedObjectID() const;
	void SetSelectedObjectID(unsigned int selectedObjectID);

private:
	std::vector<std::shared_ptr<Object>> m_Objects;

	unsigned int m_SelectedObjectID{ 0 };
	std::shared_ptr<Object> m_SelectedObject;
};