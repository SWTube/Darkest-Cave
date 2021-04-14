#version 450 core

in vec2 fTexCoord;

layout( location = 0 ) out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor = texture(tex, fTexCoord);
}