#include "window.h"

Window::Window() { }
Window::~Window() { }

void Window::Create(Size size, const std::string& title)
{
    auto& self = GetInstance();
    
    self.m_Size = size;
    self.m_Title = title;

    self.InitGlfw();
    self.InitGlew();

    A_DEBUG_LOG_OUT("[Call] Window constructor");
}

void Window::Destroy()
{
    auto& self = GetInstance();

    glfwDestroyWindow(self.m_GlfwWindow);
    glfwTerminate();

    A_DEBUG_LOG_OUT("[Call] Window destructor");
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(GetInstance().GetGlfwWindow());
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(GetInstance().GetGlfwWindow());
}    

Size Window::GetSize()
{
    return GetInstance().m_Size;
}

GLFWwindow* Window::GetGlfwWindow()
{
    return GetInstance().m_GlfwWindow;
}

void Window::InitGlfw()
{
    glfwInit();

    glfwDefaultWindowHints();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    m_GlfwWindow = glfwCreateWindow(m_Size.Width, m_Size.Height, m_Title.c_str(), nullptr, nullptr);

    glfwSetWindowSizeCallback(m_GlfwWindow, OnWindowResize);
    
    glfwMakeContextCurrent(m_GlfwWindow);
    glfwSwapInterval(1);
    glfwShowWindow(m_GlfwWindow);
    glfwMaximizeWindow(m_GlfwWindow);
}

void Window::InitGlew()
{
    glewInit();

    glEnable(GL_DEPTH_TEST);
}

void Window::OnWindowResize(GLFWwindow* glfwWindow, int width, int height)
{
    Window::GetInstance().m_Size.Width = width;
    Window::GetInstance().m_Size.Height = height;

    glViewport(0, 0, width, height);
}

Window& Window::GetInstance()
{
    static Window window;

    return window;
}