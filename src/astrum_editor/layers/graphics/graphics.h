#pragma once

#include "layers/layer.h"
#include "../gui/gui.h"
#include "../layers.h"

#include "gpu/vao.h"
#include "gpu/shader.h"
#include "gpu/screen_fbo.h"
#include "gpu/vertex_layouts/vertex.h"

#include "pch.h"

class Graphics : public Layer
{
public: 
    Graphics(Layers* layers);
    ~Graphics();

    void init() override;
    void update() override;

    unsigned int getRenderTargetTexture() const;

private:
    Layers* layers;

    std::vector<std::unique_ptr<VAO<Vertex>>> vaos;
    std::unique_ptr<Shader> shader;

    std::unique_ptr<ScreenFBO> renderTarget;

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
};