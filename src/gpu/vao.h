#pragma once

#include "vbo.h"

#include "pch.h"

#include <GL/glew.h>

class VAO
{
private:
    unsigned int handle { 0 };
    unsigned int vertexCount { 0 };
    std::vector<VBO*> vbos;
    std::vector<unsigned int> attributes;

    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

public:
    VAO();
    ~VAO();

    void createAttribute(const unsigned int attribute, const std::vector<float>& data, const unsigned int size);
    void createAttribute(const unsigned int attribute, const std::vector<int>& data, const unsigned int size);
    void createIndexBuffer(const std::vector<int>& data);
    void createIndexBuffer(const std::vector<unsigned int>& data);   

    void bind();
    void unbind();
    void release();

    unsigned int getVertexCount() const;
};