#pragma once

#include "../window/window.h"

template <typename T>
class AstrumEngine
{
private:
    std::unique_ptr<T> m_App;

public:
    AstrumEngine()
    {
        Window::Create();
        m_App = std::make_unique<T>();
        m_App->CreateLayers();
        m_App->Init();
    }

    ~AstrumEngine()
    {
        Window::Destroy();
    }

    void Run()
    {
        while (!Window::ShouldClose())
        {
            Window::Begin();

            m_App->Update();

            Window::End();
        }
    }
};