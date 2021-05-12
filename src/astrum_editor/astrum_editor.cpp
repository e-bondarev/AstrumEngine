#include "astrum_editor.h"

#include "layers/gui_layer/gui_layer.h"
#include "layers/graphics_layer/graphics_layer.h"
#include "layers/scene_layer/scene_layer.h"

void AstrumEditor::CreateLayers()
{
    m_Layers.m_GUI = std::make_shared<GUILayer>(m_Layers);
    m_Layers.m_Graphics = std::make_shared<GraphicsLayer>(m_Layers);
    m_Layers.m_Scene = std::make_shared<SceneLayer>(m_Layers);

    layerStack.PushLayer(m_Layers.m_GUI);
    layerStack.PushLayer(m_Layers.m_Graphics);
    layerStack.PushLayer(m_Layers.m_Scene);
}

void AstrumEditor::Init()
{
    layerStack.Attach();
}

void AstrumEditor::Update()
{
    layerStack.Update();
}