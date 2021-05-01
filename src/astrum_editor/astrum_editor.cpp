#include "astrum_editor.h"

#include "layers/gui_layer/gui_layer.h"
#include "layers/graphics_layer/graphics_layer.h"

void AstrumEditor::CreateLayers()
{
    m_Layers.GUI = std::make_shared<GUILayer>(m_Layers);
    m_Layers.Graphics = std::make_shared<GraphicsLayer>(m_Layers);

    layerStack.PushLayer(m_Layers.GUI);
    layerStack.PushLayer(m_Layers.Graphics);
}

void AstrumEditor::Init()
{
    layerStack.Attach();
}

void AstrumEditor::Update()
{
    layerStack.Update();
}