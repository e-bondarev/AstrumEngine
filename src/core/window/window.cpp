#include "window.h"

void Window::create(int _width, int _height, const std::string& _title)
{
    width = _width;
    height = _height;
    title = _title;

    initGlfw();
    initGlew();

    A_DEBUG_LOG_OUT("[Call] Window constructor");
}

void Window::destroy()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();

    A_DEBUG_LOG_OUT("[Call] Window destructor");
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

GLFWwindow* Window::getGlfwWindow()
{
    return glfwWindow;
}

void Window::initGlfw()
{
    glfwInit();

    glfwDefaultWindowHints();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetWindowSizeCallback(glfwWindow, onWindowResize);
    
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);
    glfwShowWindow(glfwWindow);
    glfwMaximizeWindow(glfwWindow);
}

void Window::initGlew()
{
    glewInit();
}

void Window::onWindowResize(GLFWwindow* glfwWindow, int width, int height)
{
    Window::width = width;
    Window::height = height;

    glViewport(0, 0, width, height);
}