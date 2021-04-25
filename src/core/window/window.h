#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "pch.h"

class Window
{
public:
    Window(int _width = 800, int _height = 600, const std::string& _title = "Astrum app");
    ~Window();

    int getWidth() const;
    int getHeight() const;

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;

    GLFWwindow* getGlfwWindow();

private:
    int width;
    int height;
    std::string title;

    GLFWwindow* glfwWindow;

    void initGlfw();
    void initGlew();

    Window(const Window&) = delete;
    Window operator=(const Window&) = delete;
};