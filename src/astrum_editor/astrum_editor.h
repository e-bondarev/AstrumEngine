#pragma once

#include "core/entry.h"
#include "core/app.h"
#include "layers/layer_stack.h"
#include "layers/layers.h"

class AstrumEditor : public App
{
public:
    void CreateLayers() override;
    void Init() override;
    void Update() override;

private:
    Layers m_Layers;
};

A_ENTRY(AstrumEditor)