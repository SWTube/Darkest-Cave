/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#version 450 core

in vec2 fTexCoord;

layout( location = 0 ) out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor = texture(tex, fTexCoord);
}