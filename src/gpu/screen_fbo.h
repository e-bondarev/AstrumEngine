#pragma once

#include "framebuffer.h"

class ScreenFBO : public Framebuffer
{
private:
    unsigned int depthBuffer;
    
public:
    ScreenFBO(unsigned int _width, unsigned int _height);

    void resize(unsigned int _width, unsigned int _height);
    unsigned int getTextureHandle() const;
};