#pragma once

#include "layers/layer.h"
#include "gui_element.h"
#include "../layers.h"

#include "elements/dockspace/dockspace.h"
#include "elements/scene/scene.h"
#include "elements/viewport/viewport.h"
#include "elements/inspector/inspector.h"
#include "elements/assets/assets.h"

#include "pch.h"

class GUI : public Layer
{
public: 
    GUI(Layers* layers);
    ~GUI();

    void init() override;
    void update() override;

private:
    Layers* layers;

    void newFrame();
    void render();
    
    std::unique_ptr<Dockspace> dockspace;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Viewport> viewport;
    std::unique_ptr<Inspector> inspector;
    std::unique_ptr<Assets> assets;

    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
};