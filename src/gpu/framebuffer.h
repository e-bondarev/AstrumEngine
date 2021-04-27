#pragma once

#include "texture.h"

#include <GL/glew.h>

#include <vector>
#include <map>

class Framebuffer
{
public:
    Framebuffer(const unsigned int _width, const unsigned int _height, unsigned int _buffersToClear, const std::vector<unsigned int>& _drawBuffers = {});
    virtual ~Framebuffer();

    void bind();
    void unbind();

    void clear();
    void resize(const unsigned int _width, const unsigned int _height);

    const unsigned int getWidth() const;
    const unsigned int getHeight() const;

protected:
    unsigned int width;
    unsigned int height;
    
    std::map<unsigned int, Texture*> attachments;

    unsigned int handle { 0 };

    void beginInit();
    void endInit();

private:
    std::vector<unsigned int> drawBuffers;
    unsigned int buffersToClear { GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT };
};