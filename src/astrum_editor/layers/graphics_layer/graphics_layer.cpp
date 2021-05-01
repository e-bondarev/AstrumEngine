#include "graphics_layer.h"

#include "core/window/window.h"

#include "assets/asset.h"
#include "assets/text_asset.h"
#include "assets/model_asset.h"

#include "math/math.h"

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
    Size windowSize = Window::GetSize();

    m_RenderTarget = std::make_shared<ScreenFBO>(windowSize.Width, windowSize.Height);

    TextAsset vsCodeAsset("assets/shaders/default_shader.vert");
    TextAsset fsCodeAsset("assets/shaders/default_shader.frag");

    m_Shader = std::make_unique<Shader>(vsCodeAsset.Content, fsCodeAsset.Content, Shader::str_list_t{ "projMat", "modelMat" });

    Mat4 projMat = Math::Perspective(Math::Radians(70.0f), windowSize.Width / windowSize.Height, 0.1f, 1000.0f);

    m_Shader->Bind();
    m_Shader->SetMat4x4("projMat", Math::ToPtr(projMat));
    m_Shader->Unbind();
    
    ModelAsset modelAsset("assets/models/cube.fbx");

    std::vector<VertexBufferLayout> layouts = {
        { 3, sizeof(Vertex), offsetof(Vertex, Position) },
        { 2, sizeof(Vertex), offsetof(Vertex, UV) },
        { 3, sizeof(Vertex), offsetof(Vertex, Normal) },
    };

    m_VAOs.emplace_back(std::make_unique<VAO<Vertex>>(modelAsset.Vertices, layouts, modelAsset.Indices));
}

void GraphicsLayer::OnUpdate()
{
    static Mat4 modelMat = Mat4(1);
    static float theta { 0 };

    theta += 1;

    modelMat = Math::Translate(Mat4(1), Vec3(0, 0, -10));
    modelMat = Math::Rotate(modelMat, Math::Radians(theta), Vec3(1, 1, 1));

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
        m_Shader->Bind();
            m_Shader->SetMat4x4("modelMat", Math::ToPtr(modelMat));
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