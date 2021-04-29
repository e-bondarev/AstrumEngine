#pragma once

#include "layers/layer_stack.h"

class App
{
public:
    virtual void createLayers() = 0;
    virtual void init() = 0;
    virtual void update() = 0;

protected:
    LayerStack layerStack;
};