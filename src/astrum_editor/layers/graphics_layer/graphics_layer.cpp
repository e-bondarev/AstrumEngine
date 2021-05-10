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
    m_Shader = std::make_unique<OpenGL::Shader>(vsCodeAsset.Content, fsCodeAsset.Content, "u_Projection", "u_Model", "u_Col", "u_Selected");

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

void GraphicsLayer::OnUpdate()
{
    static int theta { 0 }; theta += 1; theta = theta % 360;
    for (int i = 0; i < m_Scene->m_Objects.size(); i++)
    {
        m_Scene->m_Objects[i]->GetTransform()->SetRotation(theta);
    }

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
        m_Shader->Bind();
            m_Shader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));

            for (int i = 0; i < m_Scene->m_Objects.size(); i++)
            {
                std::shared_ptr<Mesh> mesh = m_Scene->m_Objects[i]->GetComponent<Mesh>();
                m_Shader->SetMat4x4("u_Model", Math::ToPtr(m_Scene->m_Objects[i]->GetTransform()->GetTransformationMatrix()));

                Vec3 idToColor = IDToColor(m_Scene->m_Objects[i]->GetID());
                m_Shader->SetVec3("u_Col", Math::ToPtr(idToColor));

                m_Shader->SetInt("u_Selected", m_Scene->m_SelectedObjectID == m_Scene->m_Objects[i]->GetID());

                mesh->Render();
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

std::shared_ptr<Scene>& GraphicsLayer::GetScene()
{
    return m_Scene;
}