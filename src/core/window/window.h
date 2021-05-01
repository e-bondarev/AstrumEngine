#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    static void Create(Size size = { 800, 600 }, const std::string& title = "Astrum app");
    static void Destroy();

    static bool ShouldClose();

    static void PollEvents();
    static void SwapBuffers();

    static Size GetSize();
    static GLFWwindow* GetGlfwWindow();

private:
    Size m_Size;
    std::string m_Title;
    GLFWwindow* m_GlfwWindow;

    void InitGlfw();
    void InitGlew();

    static void OnWindowResize(GLFWwindow* glfwWindow, int width, int height);
    static Window& GetInstance();

    Window();
    ~Window();

    Window(const Window&) = delete;
    Window operator=(const Window&) = delete;
};