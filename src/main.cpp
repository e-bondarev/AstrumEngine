#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;
    
    glfwInit();
    glewInit();

    glfwDefaultWindowHints();

    window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    return 0;
}