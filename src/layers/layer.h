#pragma once

class Layer
{
public:
    Layer();
    ~Layer();

    virtual void init() = 0;
    virtual void update() = 0;

private:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
};