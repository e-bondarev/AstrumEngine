#include "vbo.h"

#include <GL/glew.h>

VBO::VBO(unsigned int type)
{
    glGenBuffers(1, &handle);

    this->type = type;
}

VBO::~VBO()
{
}

void VBO::release()
{
    glDeleteBuffers(1, &handle);
}

void VBO::storeData(const std::vector<float>& data)
{
    glBufferData(type, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
}

void VBO::storeData(const std::vector<int>& data)
{
    glBufferData(type, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
}

void VBO::storeData(const std::vector<unsigned int>& data)
{
    glBufferData(type, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(type, handle);
}

void VBO::unbind()
{
    glBindBuffer(type, 0);
}