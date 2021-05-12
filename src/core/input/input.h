#pragma once

#include <GLFW/glfw3.h>

#include "buttons.h"
#include "keys.h"

enum class State
{
	Idle = 0,
	Press,
	Release
};

class Input
{
public:
	Input(GLFWwindow* glfwWindow);

	void MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
	bool MouseButtonPressed(int button) const;
	bool MouseButtonReleased(int button) const;
	bool MouseButtonDown(int button) const;

	void KeyboardKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	bool KeyPressed(int button) const;
	bool KeyReleased(int button) const;
	bool KeyDown(int button) const;

	void Begin();
	void End();

private:
	GLFWwindow* m_GlfwWindow;

	std::map<int, State> m_MouseButtons;
	std::map<int, State> m_Keys;
};