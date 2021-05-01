#include "layer_stack.h"

LayerStack::LayerStack()
{

}

void LayerStack::Attach()
{
    for (auto& layer : m_Layers)
    {
        layer->OnAttach();
    }
}

void LayerStack::Update()
{
    for (auto& layer : m_Layers)
    {
        layer->OnUpdate();
    }    
}

void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
{
    m_Layers.push_back(layer);
}