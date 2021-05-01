#pragma once

#include "pch.h"

#include <GL/glew.h>

struct VertexBufferLayout
{
    size_t size   { 0 };
    size_t stride { 0 };
    size_t offset { 0 };
};

template <typename T_Vertex>
class VAO
{
public:
    VAO(const std::vector<T_Vertex>& vertices, const std::vector<VertexBufferLayout>& layouts, const std::vector<int>& indices)
    {
        attributes.resize(layouts.size());

        glGenVertexArrays(1, &handle);

        glBindVertexArray(handle);

            unsigned int vbo { 0 };
            glGenBuffers(1, &vbo);    
            glBindBuffer(GL_ARRAY_BUFFER, vbo);        
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T_Vertex), &vertices[0], GL_STATIC_DRAW);
                for (int i = 0; i < layouts.size(); i++)
                {
                    glVertexAttribPointer(i, layouts[i].size, GL_FLOAT, GL_FALSE, layouts[i].stride, reinterpret_cast<void*>(layouts[i].offset));     
                    attributes[i] = i;
                }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            buffers.emplace_back(vbo);
        
            glGenBuffers(1, &indexVboHandle);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboHandle);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            buffers.emplace_back(indexVboHandle);

            vertexCount = static_cast<unsigned int>(indices.size());

        glBindVertexArray(0);

        A_DEBUG_LOG_OUT("[Call] VAO constructor");
    }

    ~VAO()
    {
        Unbind();
        glDeleteBuffers(buffers.size(), buffers.data());
        glDeleteVertexArrays(1, &handle);

        A_DEBUG_LOG_OUT("[Call] VAO destructor");
    }

    void Bind() const
    {
        glBindVertexArray(handle);

        for (const auto& attribute : attributes)
        {
            glEnableVertexAttribArray(attribute);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboHandle);
    }

    void Unbind() const
    {
        glBindVertexArray(0);

        for (int i = attributes.size() - 1; i >= 0; --i)
        {
            glDisableVertexAttribArray(attributes[i]);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int GetVertexCount() const
    {
        return vertexCount;
    }
    
private:
    unsigned int handle { 0 };
    unsigned int indexVboHandle { 0 };
    unsigned int vertexCount { 0 };
    std::vector<unsigned int> attributes;
    std::vector<unsigned int> buffers;

    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;
};