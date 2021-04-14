#version 450 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 vTexCoord;

out vec2 fTexCoord;

void main()
{
	gl_Position = vPosition;
	fTexCoord = vTexCoord;
}