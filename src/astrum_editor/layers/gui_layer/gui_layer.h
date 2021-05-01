#pragma once

#include "layers/layer.h"
#include "gui_element.h"
#include "../layers.h"

#include "elements/dockspace/dockspace.h"
#include "elements/scene/scene.h"
#include "elements/viewport/viewport.h"
#include "elements/inspector/inspector.h"
#include "elements/assets/assets.h"

class GUILayer : public Layer
{
public: 
    GUILayer(Layers* layers);
    ~GUILayer();

    void OnAttach() override;
    void OnUpdate() override;

private:
    Layers* m_Layers;

    void NewFrame();
    void Render();
    
    std::unique_ptr<Dockspace> m_Dockspace;
    std::unique_ptr<Scene>     m_Scene;
    std::unique_ptr<Inspector> m_Inspector;
    std::unique_ptr<Assets>    m_Assets;

    std::unique_ptr<Viewport>  m_Viewport;
    Size m_LastViewportSize;

    GUILayer(const GUILayer&) = delete;
    GUILayer& operator=(const GUILayer&) = delete;
};