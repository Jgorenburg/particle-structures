#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;

out vec3 Position;
out vec3 Normal;

uniform mat4 uMV;
uniform mat3 uNMV;
uniform mat3 uRot;
uniform mat4 uVP;


void main()
{  
	Normal = normalize(uNMV * vNor);
	Position = vec3(uMV * vec4(vPos, 1.0));
	gl_Position = uVP * vec4(uRot * ((vPos - vec3(0.5f, 0.5f, 0))), 1); 
}