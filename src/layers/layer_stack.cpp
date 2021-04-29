#include "layer_stack.h"

LayerStack::LayerStack()
{

}

void LayerStack::init()
{
    for (auto& layer : layers)
    {
        layer->init();
    }
}

void LayerStack::update()
{
    for (auto& layer : layers)
    {
        layer->update();
    }    
}

void LayerStack::addLayer(std::shared_ptr<Layer> layer)
{
    layers.push_back(layer);
}