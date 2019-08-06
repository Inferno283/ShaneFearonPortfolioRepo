#version 330 core

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0.st)
		*clamp(dot(-vec3(3,-6,5), normal0), 0.1, 1.0);//vector3 is lightDirection
}