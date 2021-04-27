#pragma once

#include "layers/layer.h"
#include "../gui/gui.h"

#include "gpu/vao.h"
#include "gpu/shader.h"

#include "pch.h"
class Graphics : public Layer
{
public: 
    Graphics();
    ~Graphics();

    void init() override;
    void update() override;

private:
    std::unique_ptr<VAO> vao;
    std::unique_ptr<Shader> shader;

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
};