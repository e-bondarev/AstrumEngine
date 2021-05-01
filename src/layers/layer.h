#pragma once

class Layer
{
public:
    Layer();
    virtual ~Layer();

    virtual void OnAttach() = 0;
    virtual void OnUpdate() = 0;

private:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
};