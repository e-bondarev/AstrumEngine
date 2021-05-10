#include "screen_fbo.h"

namespace OpenGL
{
    ScreenFBO::ScreenFBO(Size size) : Framebuffer(size, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 })
    {
        BeginInit();

        m_Attachments[GL_COLOR_ATTACHMENT0] = std::make_unique<Texture>(
            size,
            nullptr,
            GL_RGB,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            std::vector<Texture::param_t> {
                { ParamType::Int, GL_TEXTURE_MIN_FILTER, GL_NEAREST },
                { ParamType::Int, GL_TEXTURE_MAG_FILTER, GL_NEAREST },
            }
        );

        m_Attachments[GL_COLOR_ATTACHMENT1] = std::make_unique<Texture>(
            size,
            nullptr,
            GL_RGB,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            std::vector<Texture::param_t> {
                { ParamType::Int, GL_TEXTURE_MIN_FILTER, GL_NEAREST },
                { ParamType::Int, GL_TEXTURE_MAG_FILTER, GL_NEAREST },
            }
        );

        glGenRenderbuffers(1, &m_DepthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.Width, size.Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);

        EndInit();
    }

    void ScreenFBO::Resize(Size size)
    {
        Framebuffer::Resize(size);

        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Size.Width, m_Size.Height);
    }

    unsigned int ScreenFBO::GetTextureHandle() const
    {
        return m_Attachments.at(GL_COLOR_ATTACHMENT0)->GetHandle();
    }
}