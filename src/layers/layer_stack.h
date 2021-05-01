#pragma once

#include "layer.h"

#include "pch.h"

class LayerStack
{
public:
    LayerStack();

    void Attach();
    void Update();

    void PushLayer(std::shared_ptr<Layer> layer);

private:
    std::vector<std::shared_ptr<Layer>> m_Layers;
};