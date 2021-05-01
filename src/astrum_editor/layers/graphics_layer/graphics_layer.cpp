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

    m_Async.AddToQueue("assets/models/cube.fbx");
    m_Async.AddToQueue("assets/models/cube.fbx");

    ImageAsset imageAsset("assets/textures/brick.jpg");

    m_Texture = std::make_unique<OpenGL::Texture>(
        imageAsset.Size, 
        imageAsset.Data,
        GL_RGB,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        std::vector<OpenGL::Texture::param_t> {
            { OpenGL::GLParamType::Int, GL_TEXTURE_MIN_FILTER, GL_LINEAR },
            { OpenGL::GLParamType::Int, GL_TEXTURE_MAG_FILTER, GL_LINEAR },
        }
    );
}

void GraphicsLayer::Async::AddToQueue(const std::string& path)
{
    // Here we really need to copy this string in order to preserve it in the async scope.
    auto Callback = [&](std::vector<ModelAsset>* queue, std::string pathCopy) {
        ModelAsset modelAsset(pathCopy);
        std::lock_guard<std::mutex> l(lock);
        queue->push_back(modelAsset);
    };

    futures.push_back(std::async(std::launch::async, Callback, &modelQueue, path));
}

void GraphicsLayer::Async::CheckLoadingQueue(std::vector<std::shared_ptr<OpenGL::VAO>>& vaos)
{
    if (!modelQueue.size()) return;

    std::vector<ModelAsset>::iterator it = std::begin(modelQueue);

    while (it != std::end(modelQueue))
    {
        const ModelAsset& model = *it;
        vaos.emplace_back(std::make_unique<OpenGL::VAO>(model.Vertices, Vertex::GetLayout(), model.Indices));
        it = modelQueue.erase(it);
    }
}

void GraphicsLayer::OnUpdate()
{
    m_Async.CheckLoadingQueue(m_VAOs);

    static int theta { 0 }; theta += 1; theta = theta % 360;

    m_SceneUBO.model = Math::Translate(Mat4(1), Vec3(0, 0, -10));
    m_SceneUBO.model = Math::Rotate(m_SceneUBO.model, Math::Radians(static_cast<float>(theta)), Vec3(1, 1, 1));

    m_RenderTarget->Bind();
    m_RenderTarget->Clear();
        m_Shader->Bind();
            m_Shader->SetMat4x4("u_Projection", Math::ToPtr(m_SceneUBO.projection));
            for (size_t i = 0; i < m_VAOs.size(); i++)
            {
                const OpenGL::VAO& vao = *m_VAOs[i];

                m_SceneUBO.model = Math::Translate(m_SceneUBO.model, Vec3(i * 3, 0, 0));
                m_Shader->SetMat4x4("u_Model", Math::ToPtr(m_SceneUBO.model));

                m_Texture->Bind();
                vao.Bind();
                    glDrawElements(GL_TRIANGLES, vao.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                vao.Unbind();
                m_Texture->Unbind();
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