#pragma once

#include "../window/window.h"

#include "pch.h"

template <typename T>
class AstrumEngine
{
private:
    std::unique_ptr<T> app;

public:
    AstrumEngine()
    {
        // window = std::make_unique<Window>();
        Window::create();
        app = std::make_unique<T>();
        app->createLayers();
        app->init();
    }

    ~AstrumEngine()
    {
        Window::destroy();
    }

    void run()
    {
        while (!Window::shouldClose())
        {
            Window::pollEvents();

            app->update();

            Window::swapBuffers();
        }
    }
};