#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "pch.h"

class Window
{
public:
    static void create(Size size = { 800, 600 }, const std::string& title = "Astrum app");
    static void destroy();

    static bool shouldClose();

    static void pollEvents();
    static void swapBuffers();

    static Size getSize();
    static GLFWwindow* getGlfwWindow();

private:
    Size size;
    std::string title;
    GLFWwindow* glfwWindow;

    void initGlfw();
    void initGlew();

    static void onWindowResize(GLFWwindow* glfwWindow, int width, int height);
    static Window& getInstance();

    Window();
    ~Window();

    Window(const Window&) = delete;
    Window operator=(const Window&) = delete;
};