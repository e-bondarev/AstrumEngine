#include "pch.h"

#include "input.h"

Input::Input(GLFWwindow* glfwWindow) : m_GlfwWindow { glfwWindow }
{

}

void Input::MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	if (action == GLFW_RELEASE) m_MouseButtons[button] = State::Release;
	if (action == GLFW_PRESS)   m_MouseButtons[button] = State::Press;
}

void Input::KeyboardKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) m_Keys[key] = State::Release;
	if (action == GLFW_PRESS)   m_Keys[key] = State::Press;
}

void Input::Begin()
{
}

void Input::End()
{
	m_MouseButtons.clear();
	m_Keys.clear();
}

bool Input::MouseButtonPressed(int button) const
{
	if (m_MouseButtons.find(button) != m_MouseButtons.end())
	{
		return m_MouseButtons.at(button) == State::Press;
	}

	return false;
}

bool Input::MouseButtonReleased(int button) const
{
	if (m_MouseButtons.find(button) != m_MouseButtons.end())
	{
		return m_MouseButtons.at(button) == State::Release;
	}

	return false;
}

bool Input::MouseButtonDown(int button) const
{
	return glfwGetMouseButton(m_GlfwWindow, button);
}

bool Input::KeyPressed(int key) const
{
	if (m_Keys.find(key) != m_Keys.end())
	{
		return m_Keys.at(key) == State::Press;
	}

	return false;
}

bool Input::KeyReleased(int key) const
{
	if (m_Keys.find(key) != m_Keys.end())
	{
		return m_Keys.at(key) == State::Release;
	}

	return false;
}

bool Input::KeyDown(int key) const
{
	return glfwGetKey(m_GlfwWindow, key);
}