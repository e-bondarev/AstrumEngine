#pragma once

#include "layers/layer.h"
#include "../gui_layer/gui_layer.h"
#include "../layers.h"

#include "assets/assets.h"

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/shader.h"
#include "gpu/backends/opengl/screen_fbo.h"
#include "gpu/vertex_layouts/vertex.h"

#include "ecs/object.h"

#include "math/math.h"

#include <future>

class GraphicsLayer : public Layer
{
public:
    GraphicsLayer(Layers& layers);
    ~GraphicsLayer();

    void OnAttach() override;
    void OnUpdate() override;

    void OnViewportResize(Size size);

    std::shared_ptr<OpenGL::ScreenFBO>& GetRenderTarget();

private:
    Layers& m_Layers;

    struct {
        Mat4 projection{ Mat4(1) };
    } m_SceneUBO;

    std::vector<std::shared_ptr<Object>> m_Objects;

    std::unique_ptr<OpenGL::Shader> m_Shader;

    std::shared_ptr<OpenGL::ScreenFBO> m_RenderTarget;

    GraphicsLayer(const GraphicsLayer&) = delete;
    GraphicsLayer& operator=(const GraphicsLayer&) = delete;
};