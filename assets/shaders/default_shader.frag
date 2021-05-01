#version 440 core

in VSOutput
{
   vec3 position;
   vec2 uv;
   vec3 normal;
} vsOut;

uniform sampler2D u_Texture;

out vec4 out_Color;

void main()
{
   out_Color = texture(u_Texture, vsOut.uv);
}