#version 330 core
layout (location = 0) in vec3 kzPosition;
layout (location = 1) in vec2 kzTextureCoordinate0;

uniform highp mat4 uTransform;

out vec2 vTexCoord;

void main()
{
    precision mediump float;
    
	
    gl_Position = uTransform * vec4(kzPosition.xyz, 1.0);
	vTexCoord = kzTextureCoordinate0;
}