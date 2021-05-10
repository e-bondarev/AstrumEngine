#pragma once

#include "ecs/object.h"

class Scene
{
public:
	template <typename... Args>
	Scene(Args ...objects)
	{
		m_Objects = std::vector<std::shared_ptr<Object>>({ std::forward<Args>(objects)... });
	}

	std::vector<std::shared_ptr<Object>> m_Objects;
};