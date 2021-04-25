#include "window.h"

Window::Window(int _width, int _height, const std::string& _title) : width { _width }, height { _height }, title { _title }
{
    initGlfw();
    initGlew();
}

Window::~Window()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(glfwWindow);
}

void Window::initGlfw()
{
    glfwInit();
    glfwDefaultWindowHints();

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSwapInterval(1);
}

void Window::initGlew()
{
    glewInit();
}