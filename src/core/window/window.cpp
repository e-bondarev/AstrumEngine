#include "window.h"

Window::Window() { }
Window::~Window() { }

void Window::create(Size _size, const std::string& _title)
{
    auto& self = getInstance();
    
    self.size = _size;
    self.title = _title;

    self.initGlfw();
    self.initGlew();

    A_DEBUG_LOG_OUT("[Call] Window constructor");
}

void Window::destroy()
{
    auto& self = getInstance();

    glfwDestroyWindow(self.glfwWindow);
    glfwTerminate();

    A_DEBUG_LOG_OUT("[Call] Window destructor");
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(getInstance().getGlfwWindow());
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(getInstance().getGlfwWindow());
}    

Size Window::getSize()
{
    return getInstance().size;
}

GLFWwindow* Window::getGlfwWindow()
{
    return getInstance().glfwWindow;
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

    glfwWindow = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);

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
    Window::getInstance().size.width = width;
    Window::getInstance().size.height = height;

    glViewport(0, 0, width, height);
}

Window& Window::getInstance()
{
    static Window window;

    return window;
}