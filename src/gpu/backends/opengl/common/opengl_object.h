#pragma once

#include <GL/glew.h>

namespace OpenGL
{
	class OpenGLObject
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		inline GLuint GetHandle() { return m_Handle; }

	protected:
		GLuint m_Handle{ 0 };

		OpenGLObject() = default;
		virtual ~OpenGLObject() = default;
	};
}