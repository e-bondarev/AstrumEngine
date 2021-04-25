#include "astrum_engine.h"

#include "../window/window.h"

AstrumEngine::AstrumEngine()
{
    window = std::make_unique<Window>();
}

void AstrumEngine::run()
{
    while (!window->shouldClose())
    {
        window->pollEvents();

        window->swapBuffers();
    }
}