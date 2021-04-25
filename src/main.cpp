#include "core/window/window.h"

int main()
{
    window = std::make_unique<Window>();

    while (!window->shouldClose())
    {
        window->pollEvents();
        window->swapBuffers();
    }

    return 0;
}