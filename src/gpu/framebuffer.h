#pragma once

#include "texture.h"

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <map>

class Framebuffer
{
public:
    Framebuffer(const unsigned int _width, const unsigned int _height, unsigned int _buffersToClear, const std::vector<unsigned int>& _drawBuffers = {});
    virtual ~Framebuffer();

    void Bind();
    void Unbind();

    void Clear();
    void resize(const unsigned int _width, const unsigned int _height);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

protected:
    unsigned int width;
    unsigned int height;
    
    std::map<unsigned int, std::unique_ptr<Texture>> attachments;

    unsigned int handle { 0 };

    void beginInit();
    void endInit();

private:
    std::vector<unsigned int> drawBuffers;
    unsigned int buffersToClear { GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT };
};