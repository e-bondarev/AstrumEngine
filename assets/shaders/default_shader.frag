#version 440 core

in VSOutput
{
   vec3 position;
   vec2 uv;
   vec3 normal;
} vsOut;

out vec4 out_Color;

void main()
{
   out_Color = vec4(vsOut.uv.x, vsOut.uv.y, 0.0, 1.0);
}