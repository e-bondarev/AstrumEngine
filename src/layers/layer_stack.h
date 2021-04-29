#pragma once

#include "layer.h"

#include "pch.h"

class LayerStack
{
public:
    LayerStack();

    void init();
    void update();

    void addLayer(std::shared_ptr<Layer> layer);

private:
    std::vector<std::shared_ptr<Layer>> layers;
};