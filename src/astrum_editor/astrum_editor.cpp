#include "astrum_editor.h"

#include "layers/gui/gui.h"
#include "layers/graphics/graphics.h"

void AstrumEditor::createLayers()
{
    layers.gui = std::make_shared<GUI>(&layers);
    layers.graphics = std::make_shared<Graphics>(&layers);

    layerManager.addLayer(layers.gui);
    layerManager.addLayer(layers.graphics);
}

void AstrumEditor::init()
{
    layerManager.init();
}

void AstrumEditor::update()
{
    layerManager.update();
}