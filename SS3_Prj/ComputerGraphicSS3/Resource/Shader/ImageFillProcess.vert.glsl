#version 330 core
layout (location = 0) in vec3 kzPosition;
layout (location = 1) in vec2 kzTextureCoordinate0;

uniform highp mat4 uTransform;
uniform lowp float uRotate; 

out vec2 vTexCoord;
out vec2 centreCoord;

void main()
{
    precision mediump float;
    
	
    gl_Position = uTransform * vec4(kzPosition.xyz, 1.0);
	
	float PI = 3.1415; 
    float angleRadian = uRotate * (PI/180.0); 
    mediump mat2 rotateMatrix = mat2(cos(angleRadian),-sin(angleRadian),sin(angleRadian),cos(angleRadian));
    centreCoord = rotateMatrix *(kzTextureCoordinate0*2.0-1.0) ;

	vTexCoord = kzTextureCoordinate0;
}