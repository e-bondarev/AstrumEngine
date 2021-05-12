#include "graphics_layer.h"
#include "core/window/window.h"

#include "gpu/backends/opengl/stencil.h"

GraphicsLayer::GraphicsLayer(Layers& layers) : m_Layers { layers }
{
}

GraphicsLayer::~GraphicsLayer()
{
}

void GraphicsLayer::OnAttach()
{
    Size windowSize = Window::GetSize();
    m_RenderTarget = std::make_shared<OpenGL::ScreenFBO>(windowSize);

    TextAsset vsCodeAsset("assets/shaders/default_shader.vert");
    TextAsset fsCodeAsset("assets/shaders/default_shader.frag");
    m_Shader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsCodeAsset.Content, "u_Projection", "u_Model", "u_Col", "u_Selected");

    TextAsset fsStencilCodeAsset("assets/shaders/outline_shader.frag");
    m_StencilShader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsStencilCodeAsset.Content, "u_Projection", "u_Model");
}

void GraphicsLayer::OnUpdate()
{
    static int theta { 0 }; theta += 1; theta = theta % 360;

    for (int i = 0; i < m_Layers.m_Scene->GetScene()->GetObjects().size(); i++)
    {
        //m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetTransform()->SetRotation(theta);
    }

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
    {
        OpenGL::Stencil::Begin();
        {
            m_StencilShader->Bind();
            m_StencilShader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));

            for (int i = 0; i < m_Layers.m_Scene->GetScene()->GetObjects().size(); i++)
            {
                if (m_Layers.m_Scene->GetScene()->GetSelectedObjectID() == m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetID())
                {
                    std::shared_ptr<Mesh> mesh = m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetComponent<Mesh>();

                    Mat4 changed = m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetTransform()->GetTransformationMatrix();
                    changed = glm::scale(changed, Vec3(1.04f));
                    m_StencilShader->SetMat4x4("u_Model", Math::ToPtr(changed));

                    mesh->Render();
                }
            }

            m_StencilShader->Unbind();
        }

        OpenGL::Stencil::End();
        {
            m_Shader->Bind();
            m_Shader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));

            for (int i = 0; i < m_Layers.m_Scene->GetScene()->GetObjects().size(); i++)
            {
                std::shared_ptr<Mesh> mesh = m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetComponent<Mesh>();

                Mat4 changed = m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetTransform()->GetTransformationMatrix();
                m_Shader->SetMat4x4("u_Model", Math::ToPtr(changed));
                Vec3 idToColor = IDToColor(m_Layers.m_Scene->GetScene()->GetObjects()[i]->GetID());
                m_Shader->SetVec3("u_Col", Math::ToPtr(idToColor));

                mesh->Render();
            }

            m_Shader->Unbind();
        }
    }
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