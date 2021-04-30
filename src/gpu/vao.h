#pragma once

#include "pch.h"

#include <GL/glew.h>

template <typename T_Vertex>
class VAO
{
public:
    VAO(const std::vector<T_Vertex>& vertices, const std::vector<size_t>& offsets, const std::vector<int>& indices)
    {
        attributes.resize(offsets.size());

        glGenVertexArrays(1, &handle);

        glBindVertexArray(handle);

            unsigned int vbo { 0 };
            glGenBuffers(1, &vbo);    
            glBindBuffer(GL_ARRAY_BUFFER, vbo);        
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T_Vertex), &vertices[0], GL_STATIC_DRAW);
                attributes[0] = 0;
                attributes[1] = 1;
                attributes[2] = 2;

                // glVertexAttribPointer(0, )
                for (int i = 0; i < offsets.size(); i++)
                {
                    int s = i != 1 ? 3 : 2;

                    glVertexAttribPointer(i, s, GL_FLOAT, GL_FALSE, sizeof(T_Vertex), reinterpret_cast<void*>(offsets[i]));     
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
        unbind();
        glDeleteBuffers(buffers.size(), buffers.data());
        glDeleteVertexArrays(1, &handle);

        A_DEBUG_LOG_OUT("[Call] VAO destructor");
    }

    void bind() const
    {
        glBindVertexArray(handle);

        for (const auto& attribute : attributes)
        {
            glEnableVertexAttribArray(attribute);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboHandle);
    }

    void unbind() const
    {
        glBindVertexArray(0);

        for (int i = attributes.size() - 1; i >= 0; --i)
        {
            glDisableVertexAttribArray(attributes[i]);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int getVertexCount() const
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