#include "screen_fbo.h"

ScreenFBO::ScreenFBO(unsigned int _width, unsigned int _height) : Framebuffer(_width, _height, GL_DEPTH_BUFFER_BIT, { GL_COLOR_ATTACHMENT0 })
{
    beginInit();

    attachments[GL_COLOR_ATTACHMENT0] = new Texture(
        width,
        height,
        nullptr,
        GL_RGB,
        GL_RGB,
        GL_UNSIGNED_BYTE, {
            { GLParamType::Int, GL_TEXTURE_MIN_FILTER, GL_NEAREST },
            { GLParamType::Int, GL_TEXTURE_MAG_FILTER, GL_NEAREST },
        }
    );
    
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    endInit();
}

void ScreenFBO::resize(unsigned int _width, unsigned int _height)
{
    width = _width;
    height = _height;

    for (auto& attachment : attachments)
    {
        attachment.second->bind();
        attachment.second->resize(width, height);
        attachment.second->unbind();
    }
    
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
}

unsigned int ScreenFBO::getTextureHandle() const
{
    return attachments.at(GL_COLOR_ATTACHMENT0)->getHandle();
}