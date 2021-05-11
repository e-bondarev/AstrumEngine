#include "stencil.h"

#include <GL/glew.h>

namespace OpenGL
{
	void Stencil::Begin()
	{
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
	}

	void Stencil::End()
	{
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glEnable(GL_DEPTH_TEST);

		ReturnToNormalRendering();
	}

	void Stencil::ReturnToNormalRendering()
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
	}
}