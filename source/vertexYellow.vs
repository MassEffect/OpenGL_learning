#version 330 core

layout (location = 0) in vec3 aPos;
uniform float offsetX;
uniform float offsetY;
out vec3 color; 

void main()
{
	color = vec3(aPos.x + offsetX, aPos.y * (-1.0) + offsetY, aPos.z);	
	gl_Position = vec4(color, 1.0);	
};