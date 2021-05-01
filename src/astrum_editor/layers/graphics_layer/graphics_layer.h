#pragma once

#include "layers/layer.h"
#include "../gui_layer/gui_layer.h"
#include "../layers.h"

#include "assets/assets.h"

#include "gpu/backends/opengl/vao.h"
#include "gpu/backends/opengl/shader.h"
#include "gpu/backends/opengl/screen_fbo.h"
#include "gpu/vertex_layouts/vertex.h"

#include "math/math.h"

#include <future>

class GraphicsLayer : public Layer
{
public:
    GraphicsLayer(Layers* layers);
    ~GraphicsLayer();

    void OnAttach() override;
    void OnUpdate() override;

    void OnViewportResize(Size size);

    std::shared_ptr<OpenGL::ScreenFBO>& GetRenderTarget();

private:
    struct Async 
    {
        std::vector<ModelAsset> modelQueue;
        std::mutex lock;
        std::vector<std::future<void>> futures;

        void CheckLoadingQueue(std::vector<std::shared_ptr<OpenGL::VAO>>& vaos);
        void AddToQueue(const std::string& path);
    } m_Async;

    Layers* m_Layers;

    struct {
        Mat4 model{ Mat4(1) };
        Mat4 projection{ Mat4(1) };
    } m_SceneUBO;

    std::vector<std::shared_ptr<OpenGL::VAO>> m_VAOs;
    std::unique_ptr<OpenGL::Shader> m_Shader;
    std::unique_ptr<OpenGL::Texture> m_Texture;

    std::shared_ptr<OpenGL::ScreenFBO> m_RenderTarget;

    GraphicsLayer(const GraphicsLayer&) = delete;
    GraphicsLayer& operator=(const GraphicsLayer&) = delete;
};