#include "vao.h"

void VAO::createAttribute(const unsigned int attribute, const std::vector<float>& data, const unsigned int size)
{
    VBO* vbo = new VBO(GL_ARRAY_BUFFER);

    vbo->bind();
    vbo->storeData(data);

    glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, size * 4, 0);

    vbo->unbind();

    attributes.push_back(attribute);
}

void VAO::createAttribute(const unsigned int attribute, const std::vector<int>& data, const unsigned int size)
{
    VBO* vbo = new VBO(GL_ARRAY_BUFFER);

    vbo->bind();
    vbo->storeData(data);

    glVertexAttribIPointer(attribute, size, GL_INT, size * 4, 0);

    vbo->unbind();

    vbos.push_back(vbo);

    attributes.push_back(attribute);
}

void VAO::createIndexBuffer(const std::vector<int>& data)
{
    VBO* vbo = new VBO(GL_ELEMENT_ARRAY_BUFFER);

    vbo->bind();
    vbo->storeData(data);

    vertexCount = static_cast<unsigned int>(data.size());

    vbos.push_back(vbo);
}

void VAO::createIndexBuffer(const std::vector<unsigned int>& data)
{
    VBO* vbo = new VBO(GL_ELEMENT_ARRAY_BUFFER);

    vbo->bind();
    vbo->storeData(data);

    vertexCount = static_cast<unsigned int>(data.size());

    vbos.push_back(vbo);
}

VAO::VAO()
{
    glGenVertexArrays(1, &handle);
    vertexCount = 0;
}

VAO::~VAO()
{
#ifdef ASTRUM_DEBUG_MODE

    DEBUG_LOG("VAO destructor called.");

#endif
}

void VAO::release()
{
#ifdef ASTRUM_DEBUG_MODE

    DEBUG_LOG("VAO freed: " << handle);

#endif

    unbind();

    for (unsigned int i = 0; i < vbos.size(); i++)
    {
        vbos[i]->release();
        delete vbos[i];
    }

    glDeleteVertexArrays(1, &handle);
}

void VAO::bind()
{
    glBindVertexArray(handle);

    for (int i = 0; i < attributes.size(); i++)
    {
        glEnableVertexAttribArray(attributes[i]);
    }
}

void VAO::unbind()
{
    glBindVertexArray(0);

    for (int i = 0; i < attributes.size(); i++)
    {
        glDisableVertexAttribArray(attributes[i]);
    }
}

unsigned int VAO::getVertexCount() const
{
    return vertexCount;
}