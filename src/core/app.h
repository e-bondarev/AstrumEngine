#pragma once

#include "layers/layer_manager.h"

class App
{
public:
    virtual void createLayers() = 0;
    virtual void init() = 0;
    virtual void update() = 0;

protected:
    LayerManager layerManager;
};