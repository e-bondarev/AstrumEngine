#include "layer_manager.h"

LayerManager::LayerManager()
{

}

void LayerManager::init()
{
    for (auto& layer : layers)
    {
        layer->init();
    }
}

void LayerManager::update()
{
    for (auto& layer : layers)
    {
        layer->update();
    }    
}

void LayerManager::addLayer(std::shared_ptr<Layer> layer)
{
    layers.push_back(layer);
}