#pragma once

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/texture.h"

#include "components/component.h"
#include "components/transform.h"
#include "components/mesh.h"

class Object
{
public:
	Object();

	template<typename T> 
	std::shared_ptr<T> AddComponent()
	{
		// Todo: move it to the component class
		std::string rawName = typeid(T).name();
		std::string prettyName = rawName.substr(rawName.find_first_of(' ') + 1, rawName.size());

		std::function<void* ()> callback = ComponentFactory::GetFactory(prettyName);
		std::shared_ptr<T> newComponent;
		newComponent.reset(reinterpret_cast<T*>(callback()));
		m_Components[prettyName] = newComponent;
		newComponent->OnInit();

		return newComponent;
	}

	std::shared_ptr<Component> AddComponent(const std::string& name)
	{
		std::function<void* ()> callback = ComponentFactory::GetFactory(name);
		std::shared_ptr<Component> newComponent;		
		newComponent.reset(reinterpret_cast<Component*>(callback()));
		m_Components[name] = newComponent;
		newComponent->OnInit();

		return newComponent;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto& pair : m_Components)
		{
			if (std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(pair.second))
			{
				return component;
			}
		}

		return nullptr;
	}

	std::shared_ptr<Component> GetComponent(const std::string& name)
	{
		if (m_Components.find(name) == m_Components.end())
		{
			return nullptr;
		}

		return m_Components[name];
	}

	std::shared_ptr<Transform> GetTransform();

	unsigned int GetID() const;

private:
	std::map<std::string, std::shared_ptr<Component>> m_Components;

	std::shared_ptr<Transform> m_Transform;

	unsigned int m_ID;
};
