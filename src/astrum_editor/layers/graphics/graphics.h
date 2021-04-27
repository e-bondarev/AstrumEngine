#pragma once

#include "layers/layer.h"
#include "../gui/gui.h"

#include "gpu/vao.h"
#include "gpu/shader.h"

#include "pch.h"

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

struct Vertex
{
    Vec3 position;
    Vec2 uv;
    Vec3 normal;
};

class Graphics : public Layer
{
public: 
    Graphics();
    ~Graphics();

    void init() override;
    void update() override;

private:
    std::vector<std::shared_ptr<VAO<Vertex>>> vaos;
    std::unique_ptr<Shader> shader;

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
};