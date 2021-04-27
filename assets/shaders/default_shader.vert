#version 440 core

in vec3 position;
in vec2 uv;
in vec3 normal;

out vec3 out_Position;
out vec2 out_Uv;
out vec3 out_Normal;

void main()
{
   gl_Position = vec4(position, 1.0);

   out_Position = position;
   out_Uv = uv;
   out_Normal = normal;
}