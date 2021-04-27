#include "graphics.h"

#include "core/window/window.h"

#include "files/files.h"

Graphics::Graphics()
{
    A_DEBUG_LOG_OUT("[Call] Graphics constructor");
}

Graphics::~Graphics()
{
    A_DEBUG_LOG_OUT("[Call] Graphics destructor");
}

void Graphics::init()
{
    std::string vsCode = util::file::read("assets/shaders/default_shader.vert");
    std::string fsCode = util::file::read("assets/shaders/default_shader.frag");

    shader = std::make_unique<Shader>(vsCode, fsCode);

    std::vector<Vertex> model0
    {
        {{ -0.2f - 0.5f, -0.2f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }},
        {{  0.2f - 0.5f, -0.2f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }},
        {{  0.0f - 0.5f,  0.2f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }}
    };
    std::vector<int> indices0 { 0, 1, 2 };

    std::vector<Vertex> model1
    {
        {{ -0.2f + 0.5f, -0.2f, 0.0f }, { 0.2f, 0.4f }, { 0.0f, 0.0f, 0.0f }},
        {{  0.2f + 0.5f, -0.2f, 0.0f }, { 0.4f, 0.2f }, { 0.0f, 0.0f, 0.0f }},
        {{  0.0f + 0.5f,  0.2f, 0.0f }, { 0.0f, 0.8f }, { 0.0f, 0.0f, 0.0f }}
    };
    std::vector<int> indices1 { 0, 1, 2 };

    std::vector<size_t> offsets = {
        offsetof(Vertex, position),
        offsetof(Vertex, uv),
        offsetof(Vertex, normal)
    };

    vaos.resize(2);
    vaos[0] = std::make_shared<VAO<Vertex>>(model0, offsets, indices0);
    vaos[1] = std::make_shared<VAO<Vertex>>(model1, offsets, indices1);
}

void Graphics::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();
        for (const auto& vao : vaos)
        {
            vao->bind();
                glDrawElements(GL_TRIANGLES, vao->getVertexCount(), GL_UNSIGNED_INT, nullptr);
            vao->unbind();
        }
    shader->unbind();
}