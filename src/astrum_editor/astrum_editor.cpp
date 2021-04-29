#include "astrum_editor.h"

#include "layers/gui/gui.h"
#include "layers/graphics/graphics.h"

void AstrumEditor::createLayers()
{
    layers.gui = std::make_shared<GUI>(&layers);
    layers.graphics = std::make_shared<Graphics>(&layers);

    layerStack.addLayer(layers.gui);
    layerStack.addLayer(layers.graphics);
}

void AstrumEditor::init()
{
    layerStack.init();
}

void AstrumEditor::update()
{
    layerStack.update();
}