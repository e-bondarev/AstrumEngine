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

uniform mat4 projMat;
uniform mat4 modelMat;

void main()
{
   gl_Position = projMat * modelMat * vec4(position.x, position.y, position.z, 1.0);

   vsOut.position = position;
   vsOut.uv = uv;
   vsOut.normal = normal;
}