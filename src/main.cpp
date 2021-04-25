#include "core/window/window.h"

int main()
{
    Window window;

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}