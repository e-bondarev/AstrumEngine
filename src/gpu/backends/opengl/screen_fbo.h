#pragma once

#include "framebuffer.h"

namespace OpenGL
{
    class ScreenFBO : public Framebuffer
    {
    private:
        GLuint m_DepthBuffer;

    public:
        ScreenFBO(Size size);

        void Resize(Size size) override;
        GLuint GetTextureHandle() const;
    };
}