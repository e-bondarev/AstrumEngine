#include "astrum_editor.h"

#include "layers/gui/gui.h"
#include "layers/graphics/graphics.h"

void AstrumEditor::createLayers()
{
    // layerManager.addLayer(std::make_shared<GUI>());
    layerManager.addLayer(std::make_shared<Graphics>());
}

void AstrumEditor::init()
{
    layerManager.init();
}

void AstrumEditor::update()
{
    layerManager.update();
}