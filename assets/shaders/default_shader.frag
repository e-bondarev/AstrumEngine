#version 440 core

in vec3 out_Position;
in vec2 out_Uv;
in vec3 out_Normal;

out vec4 out_Color;

void main()
{
   out_Color = vec4(out_Uv.x, out_Uv.y, 0.0, 1.0);
}