#pragma once

#include "ecs/object.h"

class Scene
{
friend class GraphicsLayer;
public:
	template <typename... Args>
	Scene(Args ...objects)
	{
		m_Objects = std::vector<std::shared_ptr<Object>>({ std::forward<Args>(objects)... });
	}

	std::vector<std::shared_ptr<Object>> m_Objects;

	unsigned int m_SelectedObjectID{ 0 };
	std::shared_ptr<Object> m_SelectedObject;
};