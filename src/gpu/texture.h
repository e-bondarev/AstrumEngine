#pragma once

#include <string>
#include <vector>
#include <tuple>

#include <GL/glew.h>

enum class GLParamType
{
    Int,
    Float
};

class Texture
{
private:
    unsigned int width;
    unsigned int height;
    int internalFormat;
    unsigned int format;
    unsigned int type;

    unsigned int handle { 0 };

public:
    Texture(
        unsigned int width, unsigned int height,
        unsigned char* data,
        int internalFormat, unsigned int format, unsigned int type,
        const std::vector<std::tuple<GLParamType, unsigned int, float>>& parameters
    );
    ~Texture();

    void resize(int width, int height);

    void setParamFV(unsigned int name, float *params);

    void bind();
    void bind(unsigned int unit);
    void unbind();
    
    unsigned int getHandle() const;
};