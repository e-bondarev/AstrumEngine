#version 440 core

in VSOutput
{
   vec3 position;
   vec2 uv;
   vec3 normal;
} vsOut;

uniform sampler2D u_Texture;
uniform vec3 u_Col;
uniform int u_Selected;

out vec4 out_Color;
out vec3 out_ID;

void main()
{
	if (u_Selected == 1)
	{
		out_Color = texture(u_Texture, vsOut.uv) * 1.5;
	}
	else
	{
		out_Color = texture(u_Texture, vsOut.uv);
	}

	out_ID = u_Col;
}