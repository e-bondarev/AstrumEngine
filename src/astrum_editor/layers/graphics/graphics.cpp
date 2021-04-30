#include "graphics.h"

#include "core/window/window.h"

#include "files/files.h"

#include "assets/asset.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Graphics::Graphics(Layers* _layers) : layers { _layers }
{
    A_DEBUG_LOG_OUT("[Call] Graphics constructor");
}

Graphics::~Graphics()
{
    A_DEBUG_LOG_OUT("[Call] Graphics destructor");
}

void Graphics::init()
{
    std::string vsCode = util::file::read("D:/Dev/AstrumEngine/assets/shaders/default_shader.vert");
    std::string fsCode = util::file::read("D:/Dev/AstrumEngine/assets/shaders/default_shader.frag");

    shader = std::make_unique<Shader>(vsCode, fsCode, Shader::str_list_t { "projMat", "modelMat" });

    glm::mat4x4 projMat = glm::perspective(glm::radians(70.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
    glm::mat4x4 modelMat = glm::mat4x4(1);

    modelMat = glm::translate(modelMat, glm::vec3(0, 0, -10));

    shader->bind();
    shader->setMat4x4("projMat", glm::value_ptr(projMat));
    shader->setMat4x4("modelMat", glm::value_ptr(modelMat));
    shader->unbind();

    std::vector<Vertex> model0
    {
        {{ 0, 0, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }},
        {{ 0, 0, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }},
        {{ 0, 0, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }},
        {{ 0, 0, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }},
        {{ 0, 0, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }},
    };
    std::vector<int> indices0 { 0, 1, 2 };

    // std::vector<Vertex> model1
    // {
    //     {{ -0.2f + 0.5f, -0.2f, 0.0f }, { 0.2f, 0.4f }, { 0.0f, 0.0f, 0.0f }},
    //     {{  0.2f + 0.5f, -0.2f, 0.0f }, { 0.4f, 0.2f }, { 0.0f, 0.0f, 0.0f }},
    //     {{  0.0f + 0.5f,  0.2f, 0.0f }, { 0.0f, 0.8f }, { 0.0f, 0.0f, 0.0f }}
    // };
    // std::vector<int> indices1 { 0, 1, 2 };

    ModelAsset modelAsset;
    modelAsset.load("assets/models/cube.fbx");

    std::vector<size_t> offsets = {
        offsetof(Vertex, position),
        offsetof(Vertex, uv),
        offsetof(Vertex, normal)
    };

    vaos.resize(1);
    vaos[0] = std::make_unique<VAO<Vertex>>(modelAsset.vertices, offsets, modelAsset.indices);

    // vaos.resize(2);
    // vaos[0] = std::make_unique<VAO<Vertex>>(model0, offsets, indices0);
    // vaos[1] = std::make_unique<VAO<Vertex>>(model1, offsets, indices1);

    renderTarget = std::make_shared<ScreenFBO>(Window::getSize().width, Window::getSize().height);
}

void Graphics::update()
{
    static glm::mat4x4 modelMat = glm::mat4x4(1);
    static float theta { 0 };

    theta += 1;

    modelMat = glm::translate(glm::mat4x4(1), glm::vec3(0, 0, -10));
    modelMat = glm::rotate(modelMat, glm::radians(theta), glm::vec3(1, 1, 1));

    renderTarget->bind();
    renderTarget->clear();
        shader->bind();

        shader->setMat4x4("modelMat", &modelMat[0][0]);

            for (const auto& vao : vaos)
            {
                vao->bind();
                    glDrawElements(GL_TRIANGLES, vao->getVertexCount(), GL_UNSIGNED_INT, nullptr);
                vao->unbind();
            }
        shader->unbind();
    renderTarget->unbind();
}

std::shared_ptr<ScreenFBO> & Graphics::getRenderTarget()
{
    return renderTarget;
}