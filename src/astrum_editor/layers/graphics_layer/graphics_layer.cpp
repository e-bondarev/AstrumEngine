#include "graphics_layer.h"

#include "core/window/window.h"

#include "assets/asset.h"
#include "assets/text_asset.h"
#include "assets/model_asset.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GraphicsLayer::GraphicsLayer(Layers* layers) : m_Layers { layers }
{
    A_DEBUG_LOG_OUT("[Call] Graphics constructor");
}

GraphicsLayer::~GraphicsLayer()
{
    A_DEBUG_LOG_OUT("[Call] Graphics destructor");
}

void GraphicsLayer::OnAttach()
{
    TextAsset vsCodeAsset("assets/shaders/default_shader.vert");
    TextAsset fsCodeAsset("assets/shaders/default_shader.frag");

    m_Shader = std::make_unique<Shader>(vsCodeAsset.Content, fsCodeAsset.Content, Shader::str_list_t { "projMat", "modelMat" });

    glm::mat4x4 projMat = glm::perspective(glm::radians(70.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

    m_Shader->Bind();
        m_Shader->SetMat4x4("projMat", glm::value_ptr(projMat));
    m_Shader->Unbind();

    m_RenderTarget = std::make_shared<ScreenFBO>(Window::GetSize().Width, Window::GetSize().Height);
    
    ModelAsset modelAsset("assets/models/cube.fbx");

    std::vector<VertexBufferLayout> layouts = {
        { 3, sizeof(Vertex), offsetof(Vertex, position) },
        { 2, sizeof(Vertex), offsetof(Vertex, uv) },
        { 3, sizeof(Vertex), offsetof(Vertex, normal) },
    };

    m_VAOs.emplace_back(std::make_unique<VAO<Vertex>>(modelAsset.Vertices, layouts, modelAsset.Indices));
}

void GraphicsLayer::OnUpdate()
{
    static glm::mat4x4 modelMat = glm::mat4x4(1);
    static float theta { 0 };

    theta += 1;

    modelMat = glm::translate(glm::mat4x4(1), glm::vec3(0, 0, -10));
    modelMat = glm::rotate(modelMat, glm::radians(theta), glm::vec3(1, 1, 1));

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
        m_Shader->Bind();
            m_Shader->SetMat4x4("modelMat", &modelMat[0][0]);
            for (const auto& vao : m_VAOs)
            {
                vao->Bind();
                    glDrawElements(GL_TRIANGLES, vao->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                vao->Unbind();
            }
        m_Shader->Unbind();
    m_RenderTarget->Unbind();
}

std::shared_ptr<ScreenFBO> & GraphicsLayer::GetRenderTarget()
{
    return m_RenderTarget;
}