#include "vao.h"

namespace OpenGL
{
    VAO::~VAO()
    {
        Unbind();
        glDeleteBuffers(m_Buffers.size(), m_Buffers.data());
        glDeleteVertexArrays(1, &m_Handle);

        A_DEBUG_LOG_OUT("[Call] VAO destructor");
    }

    void VAO::Bind() const
    {
        glBindVertexArray(m_Handle);

        for (const auto& attribute : m_Attributes)
        {
            glEnableVertexAttribArray(attribute);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexVboHandle);
    }

    void VAO::Unbind() const
    {
        glBindVertexArray(0);

        for (int i = m_Attributes.size() - 1; i >= 0; --i)
        {
            glDisableVertexAttribArray(m_Attributes[i]);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint VAO::GetVertexCount() const
    {
        return m_VertexCount;
    }
}