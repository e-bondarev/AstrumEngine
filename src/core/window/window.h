#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "pch.h"

class Window
{
public:
    static void create(int _width = 800, int _height = 600, const std::string& _title = "Astrum app");
    static void destroy();

    static int getWidth();
    static int getHeight();

    static bool shouldClose();
    static void pollEvents();
    static void swapBuffers();

    static GLFWwindow* getGlfwWindow();

private:
    inline static int width;
    inline static int height;
    inline static std::string title;

    inline static GLFWwindow* glfwWindow;

    static void initGlfw();
    static void initGlew();

    static void onWindowResize(GLFWwindow* glfwWindow, int width, int height);

    Window(const Window&) = delete;
    Window operator=(const Window&) = delete;
};