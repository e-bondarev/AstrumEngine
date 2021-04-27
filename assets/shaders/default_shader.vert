#version 440 core

in vec3 position;
in vec2 uv;
in vec3 normal;

out VSOutput
{
   vec3 position;
   vec2 uv;
   vec3 normal;
} vsOut;

void main()
{
   gl_Position = vec4(position, 1.0);

   vsOut.position = position;
   vsOut.uv = uv;
   vsOut.normal = normal;
}