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

    self.m_Input = std::make_unique<Input>(self.GetGlfwWindow());

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

void Window::Begin()
{
    PollEvents();

    GetInstance().m_Input->Begin();
}

void Window::End()
{
    GetInstance().m_Input->End();

    SwapBuffers();
}

Size Window::GetSize()
{
    return GetInstance().m_Size;
}

Pos Window::GetMousePos()
{
    double x, y;
    glfwGetCursorPos(GetInstance().GetGlfwWindow(), &x, &y);

    return { static_cast<float>(x), static_cast<float>(y) };
}

GLFWwindow* Window::GetGlfwWindow()
{
    return GetInstance().m_GlfwWindow;
}

Input& Window::GetInput()
{
    return *GetInstance().m_Input;
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

    glfwSetMouseButtonCallback(m_GlfwWindow, Window::MouseCallback);
    glfwSetKeyCallback(m_GlfwWindow, Window::KeyboardCallback);
    
    glfwMakeContextCurrent(m_GlfwWindow);
    glfwSwapInterval(1);
    glfwShowWindow(m_GlfwWindow);
    glfwMaximizeWindow(m_GlfwWindow);
}

void Window::InitGlew()
{
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
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