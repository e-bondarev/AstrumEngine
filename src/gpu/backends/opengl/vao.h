#pragma once

#include "pch.h"

#include "../../common/vertex_buffer_layout.h"

#include "common/opengl_object.h"

namespace OpenGL
{
    class VAO : public OpenGLObject
    {
    public:
        template <typename T_Vertex>
        VAO(const std::vector<T_Vertex>& vertices, const std::vector<VertexBufferLayout>& layouts, const std::vector<int>& indices)
        {
            m_Attributes.resize(layouts.size());

            glGenVertexArrays(1, &m_Handle);

            glBindVertexArray(m_Handle);

            unsigned int vbo{ 0 };
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T_Vertex), &vertices[0], GL_STATIC_DRAW);
            for (int i = 0; i < layouts.size(); i++)
            {
                glVertexAttribPointer(i, layouts[i].Size, GL_FLOAT, GL_FALSE, layouts[i].Stride, reinterpret_cast<void*>(layouts[i].Offset));
                m_Attributes[i] = i;
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            m_Buffers.emplace_back(vbo);

            glGenBuffers(1, &m_IndexVboHandle);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexVboHandle);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            m_Buffers.emplace_back(m_IndexVboHandle);

            m_VertexCount = static_cast<unsigned int>(indices.size());

            glBindVertexArray(0);

            A_DEBUG_LOG_OUT("[Call] VAO constructor");
        }
        ~VAO() override;

        void Bind() const override;
        void Unbind() const override;
        GLuint GetVertexCount() const;

    private:
        GLuint m_IndexVboHandle{ 0 };
        GLuint m_VertexCount{ 0 };
        std::vector<GLuint> m_Attributes;
        std::vector<GLuint> m_Buffers;

        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;
    };
}