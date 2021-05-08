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
	T* AddComponent()
	{
		// Todo: move it to the component class
		std::string rawName = typeid(T).name();
		std::string prettyName = rawName.substr(rawName.find_first_of(' ') + 1, rawName.size());

		std::function<void*()> callback = Component::m_Factories[prettyName];
		T* newComponent = (T*) callback();
		m_Components.push_back(newComponent);
		return newComponent;
	}

	Component* AddComponent(const std::string& name)
	{
		std::function<void* ()> callback = Component::m_Factories[name];
		Component* newComponent = (Component*) callback();
		m_Components.push_back(newComponent);
		return newComponent;
	}

	Transform* GetTransform();

	std::shared_ptr<OpenGL::VAO>& GetVAO();
	std::shared_ptr<OpenGL::Texture>& GetTexture();

private:
	std::vector<Component*> m_Components;
	Transform* m_Transform;

	std::shared_ptr<OpenGL::VAO> m_VAO;
	std::shared_ptr<OpenGL::Texture> m_Texture;
};