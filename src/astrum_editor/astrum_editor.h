#pragma once

#include "core/entry.h"
#include "core/app.h"
#include "layers/layer_manager.h"

class AstrumEditor : public App
{
public:
    void createLayers() override;
    void init() override;
    void update() override;
};

A_ENTRY(AstrumEditor)