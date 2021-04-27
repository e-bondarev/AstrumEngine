#pragma once

#include "layers/layer.h"
#include "gui_element.h"

#include "pch.h"

class GUI : public Layer
{
public: 
    GUI();
    ~GUI();

    void init() override;
    void update() override;

private:
    void newFrame();
    void render();

    std::vector<std::unique_ptr<GUIElement>> guiElements;

    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
};