#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../input/input.h"

#define A_MOUSE_BUTTON_PRESSED(x)  Window::GetInput().MouseButtonPressed(x)
#define A_MOUSE_BUTTON_RELEASED(x) Window::GetInput().MouseButtonReleased(x)
#define A_MOUSE_BUTTON_DOWN(x)     Window::GetInput().MouseButtonDown(x)

#define A_KEY_PRESSED(x)           Window::GetInput().KeyPressed(x)
#define A_KEY_RELEASED(x)          Window::GetInput().KeyReleased(x)
#define A_KEY_DOWN(x)              Window::GetInput().KeyDown(x)

class Window
{
public:
    static void Create(Size size = { 800, 600 }, const std::string& title = "Astrum app");
    static void Destroy();

    static bool ShouldClose();

    static void PollEvents();
    static void SwapBuffers();

    static void Begin();
    static void End();

    static Size GetSize();
    static Pos  GetMousePos();
    static GLFWwindow* GetGlfwWindow();

    static Input& GetInput();

private:
    Size m_Size;
    std::string m_Title;
    std::unique_ptr<Input> m_Input;
    GLFWwindow* m_GlfwWindow;

    inline static void MouseCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
    {
        GetInstance().m_Input->MouseButtonCallback(glfwWindow, button, action, mods);
    }

    inline static void KeyboardCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
    {
        GetInstance().m_Input->KeyboardKeyCallback(glfwWindow, key, scancode, action, mods);
    }

    void InitGlfw();
    void InitGlew();

    static void OnWindowResize(GLFWwindow* glfwWindow, int width, int height);
    static Window& GetInstance();

    Window();
    ~Window();

    Window(const Window&) = delete;
    Window operator=(const Window&) = delete;
};