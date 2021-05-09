#pragma once

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/texture.h"

#include "components/component.h"
#include "components/transform.h"
#include "components/mesh.h"

class Object
{
public:
	Object() = default;
	Object(const std::string& meshFilepath, const std::string& textureFilepath);

	template<typename T> 
	std::shared_ptr<T> AddComponent()
	{
		// Todo: move it to the component class
		std::string rawName = typeid(T).name();
		std::string prettyName = rawName.substr(rawName.find_first_of(' ') + 1, rawName.size());

		//std::function<void*()> callback = ComponentFactory::m_Factories[prettyName];
		std::function<void* ()> callback = ComponentFactory::GetFactory(prettyName);
		std::shared_ptr<T> newComponent;
		newComponent.reset(reinterpret_cast<T*>(callback()));
		m_Components.push_back(newComponent);
		return newComponent;
	}

	std::shared_ptr<Component> AddComponent(const std::string& name)
	{
		//std::function<void*()> callback = ComponentFactory::m_Factories[name];		
		std::function<void* ()> callback = ComponentFactory::GetFactory(name);
		std::shared_ptr<Component> newComponent;		
		newComponent.reset(reinterpret_cast<Component*>(callback()));
		m_Components.push_back(newComponent);
		return newComponent;
	}

	std::shared_ptr<Transform> GetTransform();

	std::shared_ptr<OpenGL::VAO>& GetVAO();
	std::shared_ptr<OpenGL::Texture>& GetTexture();

private:
	std::vector<std::shared_ptr<Component>> m_Components;

	std::shared_ptr<Transform> m_Transform;

	std::shared_ptr<OpenGL::VAO> m_VAO;
	std::shared_ptr<OpenGL::Texture> m_Texture;
};
