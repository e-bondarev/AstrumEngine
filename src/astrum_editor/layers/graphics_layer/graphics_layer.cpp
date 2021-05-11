#include "graphics_layer.h"
#include "core/window/window.h"

#include "gpu/backends/opengl/stencil.h"

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
    m_Shader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsCodeAsset.Content, "u_Projection", "u_Model", "u_Col", "u_Selected");

    TextAsset fsStencilCodeAsset("assets/shaders/outline_shader.frag");
    m_StencilShader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsStencilCodeAsset.Content, "u_Projection", "u_Model");

    std::shared_ptr obj0 = std::make_shared<Object>();
    std::shared_ptr obj1 = std::make_shared<Object>();

    obj0->GetTransform()->SetPosition(0, 0, -10);
    obj1->GetTransform()->SetPosition(4, 0, -10);

    ModelAsset model0("assets/models/cube.fbx");
    ImageAsset image0("assets/textures/brick.jpg");

    obj0->AddComponent<Mesh>()->Create(model0, image0);
    obj1->AddComponent<Mesh>()->Create(model0, image0);

    m_Scene = std::make_shared<Scene>(obj0, obj1);
}

inline static void BeginRenderToStencil()
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
}

inline static void EndRenderToStencil()
{
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_DEPTH_TEST);
}

inline static void ReturnToNormalRendering()
{
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
}

void GraphicsLayer::OnUpdate()
{
    static int theta { 0 }; theta += 1; theta = theta % 360;
    for (int i = 0; i < m_Scene->m_Objects.size(); i++)
    {
        //m_Scene->m_Objects[i]->GetTransform()->SetRotation(theta);
    }

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
    {
        OpenGL::Stencil::Begin();
        {
            m_StencilShader->Bind();
            m_StencilShader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));

            for (int i = 0; i < m_Scene->m_Objects.size(); i++)
            {
                if (m_Scene->m_SelectedObjectID == m_Scene->m_Objects[i]->GetID())
                {
                    std::shared_ptr<Mesh> mesh = m_Scene->m_Objects[i]->GetComponent<Mesh>();

                    Mat4 changed = m_Scene->m_Objects[i]->GetTransform()->GetTransformationMatrix();
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

            for (int i = 0; i < m_Scene->m_Objects.size(); i++)
            {
                std::shared_ptr<Mesh> mesh = m_Scene->m_Objects[i]->GetComponent<Mesh>();

                Mat4 changed = m_Scene->m_Objects[i]->GetTransform()->GetTransformationMatrix();
                m_Shader->SetMat4x4("u_Model", Math::ToPtr(changed));
                Vec3 idToColor = IDToColor(m_Scene->m_Objects[i]->GetID());
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

std::shared_ptr<Scene>& GraphicsLayer::GetScene()
{
    return m_Scene;
}