#pragma once

#include "layers/layer.h"
#include "../gui_layer/gui_layer.h"
#include "../layers.h"

#include "gpu/vao.h"
#include "gpu/shader.h"
#include "gpu/screen_fbo.h"
#include "gpu/vertex_layouts/vertex.h"

#include "pch.h"

#include <future>

class GraphicsLayer : public Layer
{
public:
    GraphicsLayer(Layers* layers);
    ~GraphicsLayer();

    void OnAttach() override;
    void OnUpdate() override;

    std::shared_ptr<ScreenFBO>& GetRenderTarget();

private:
    Layers* m_Layers;

    std::vector<std::unique_ptr<VAO<Vertex>>> m_VAOs;
    std::unique_ptr<Shader> m_Shader;

    std::shared_ptr<ScreenFBO> m_RenderTarget;

    GraphicsLayer(const GraphicsLayer&) = delete;
    GraphicsLayer& operator=(const GraphicsLayer&) = delete;
};