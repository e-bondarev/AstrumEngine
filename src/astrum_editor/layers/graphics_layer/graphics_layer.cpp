#include "graphics_layer.h"
#include "core/window/window.h"

GraphicsLayer::GraphicsLayer(Layers& layers) : m_Layers { layers }
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
    m_RenderTarget = std::make_shared<OpenGL::ScreenFBO>(windowSize);

    TextAsset vsCodeAsset("assets/shaders/default_shader.vert");
    TextAsset fsCodeAsset("assets/shaders/default_shader.frag");
    m_Shader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsCodeAsset.Content, "u_Projection", "u_Model");

    m_Objects.emplace_back(std::make_unique<Object>("assets/models/cube.fbx", "assets/textures/brick.jpg"));
    m_Objects.emplace_back(std::make_unique<Object>("assets/models/cube.fbx", "assets/textures/brick.jpg"));
}

void GraphicsLayer::OnUpdate()
{
    static int theta { 0 }; theta += 1; theta = theta % 360;

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
        m_Shader->Bind();
            m_Shader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));

            int i = 0;

            for (auto& object : m_Objects)
            {
                OpenGL::VAO& vao = *object->GetVAO();
                OpenGL::Texture& texture = *object->GetTexture();

                object->GetTransform()->SetPosition(Vec3(i * 3, 0, -10));
                object->GetTransform()->SetRotation(Vec3(theta));
                m_Shader->SetMat4x4("u_Model", Math::ToPtr(object->GetTransform()->GetTransformationMatrix()));

                texture.Bind();
                    vao.Bind();
                        glDrawElements(GL_TRIANGLES, vao.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                    vao.Unbind();
                texture.Unbind();

                i++;
            }
        m_Shader->Unbind();
    m_RenderTarget->Unbind();
}

void GraphicsLayer::OnViewportResize(Size size)
{
    m_SceneUBO.projection = Math::Perspective(Math::Radians(70.0f), size.Width / size.Height, 0.1f, 1000.0f);
}

std::shared_ptr<OpenGL::ScreenFBO> & GraphicsLayer::GetRenderTarget()
{
    return m_RenderTarget;
}