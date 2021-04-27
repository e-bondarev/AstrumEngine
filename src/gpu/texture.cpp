#include "texture.h"

void Texture::resize(int _width, int _height)
{    
    width = _width;
    height = _height;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);
}

Texture::Texture(
    unsigned int _width, unsigned int _height,
    unsigned char* data,
    int _internalFormat, unsigned int _format, unsigned int _type,
    const std::vector<std::tuple<GLParamType, GLenum, GLfloat>>& parameters
) : width { _width }, height { _height }, internalFormat { _internalFormat }, format { _format }, type { _type }
{
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

    for (const auto& param : parameters)
    {
        switch (std::get<0>(param))
        {
            case GLParamType::Int:
            {
                glTexParameteri(GL_TEXTURE_2D, std::get<1>(param), static_cast<GLint>(std::get<2>(param)));
                break;
            }

            case GLParamType::Float:
            {
                glTexParameterf(GL_TEXTURE_2D, std::get<1>(param), std::get<2>(param));
                break;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &handle);
}

void Texture::setParamFV(unsigned int name, float *params)
{
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameterfv(GL_TEXTURE_2D, name, params);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::bind(unsigned int unit)
{
    glActiveTexture(unit);
    bind();
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getHandle() const
{
    return handle;
}