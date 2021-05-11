#pragma once

namespace OpenGL
{
	class Stencil
	{
	public:
		static void Begin();
		static void End();

	private:
		static void ReturnToNormalRendering();
	};
}