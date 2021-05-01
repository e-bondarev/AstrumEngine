#include "framebuffer.h"

Framebuffer::Framebuffer(const GLuint _width, const GLuint _height, GLbitfield _buffersToClear, const std::vector<GLuint>& _drawBuffers)
    : width { _width }, height { _height }, buffersToClear { _buffersToClear }, drawBuffers { _drawBuffers }
{
}

Framebuffer::~Framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &handle);
}

void Framebuffer::beginInit()
{
    glGenFramebuffers(1, &handle);
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void Framebuffer::endInit()
{
    for (auto& attachment : attachments)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment.first, GL_TEXTURE_2D, attachment.second->getHandle(), 0);
    }

    if (drawBuffers.size() > 0)
    {
        glDrawBuffers(drawBuffers.size(), drawBuffers.data());
    }
    else
    {
        glDrawBuffer(GL_NONE);
    }

    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer is not complete.\n";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void Framebuffer::Clear()
{
    glClear(buffersToClear);
}

void Framebuffer::resize(const GLuint _width, const GLuint _height)
{
    width = _width;
    height = _height;

    for (auto& attachment : attachments)
    {
        attachment.second->bind();
        attachment.second->resize(width, height);
        attachment.second->unbind();
    }
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::getWidth() const
{
    return width;
}

unsigned int Framebuffer::getHeight() const
{
    return height;
}