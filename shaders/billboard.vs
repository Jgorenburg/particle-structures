#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNorm;

uniform vec3 uCameraPos;
uniform vec4 uColor;
uniform mat3 uRot;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{
  color = uColor;
  uv = vPos.xy;
  gl_Position = uVP * vec4(uRot * ((vPos - vec3(0.5f, 0.5f, 0))), 1); 
// gl_Position = vPos;
}
