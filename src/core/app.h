#pragma once

#include "layers/layer_stack.h"

class App
{
public:
    virtual void CreateLayers() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;

protected:
    LayerStack layerStack;
};