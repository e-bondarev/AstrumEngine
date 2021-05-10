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

    std::shared_ptr obj0 = std::make_shared<Object>();
    std::shared_ptr obj1 = std::make_shared<Object>();

    obj0->GetTransform()->SetPosition(0, 0, -10);
    obj1->GetTransform()->SetPosition(4, 0, -10);

    ModelAsset model0("assets/models/cube.fbx");
    ImageAsset image0("assets/textures/brick.jpg");

    obj0->AddComponent<Mesh>()->Create(model0, image0);
    obj1->AddComponent<Mesh>()->Create(model0, image0);

    m_Objects.emplace_back(obj0);
    m_Objects.emplace_back(obj1);
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
                std::shared_ptr<Mesh> mesh = object->GetComponent<Mesh>();

                object->GetTransform()->SetRotation(theta);

                m_Shader->SetMat4x4("u_Model", Math::ToPtr(object->GetTransform()->GetTransformationMatrix()));

                mesh->m_Texture->Bind();
                    mesh->m_VAO->Bind();
                        glDrawElements(GL_TRIANGLES, mesh->m_VAO->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                    mesh->m_VAO->Unbind();
                mesh->m_Texture->Unbind();

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