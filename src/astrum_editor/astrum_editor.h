#pragma once

#include "core/entry.h"
#include "core/app.h"
#include "layers/layer_stack.h"
#include "layers/layers.h"

class AstrumEditor : public App
{
public:
    void createLayers() override;
    void init() override;
    void update() override;

private:
    Layers layers;
};

A_ENTRY(AstrumEditor)