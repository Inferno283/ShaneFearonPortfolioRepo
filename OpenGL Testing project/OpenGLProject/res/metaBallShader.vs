#version 330 core

attribute vec3 position;
attribute vec3 normal;

varying vec3 normal0;
varying vec3 FragPos;

uniform mat4 modelMatrix;


void main()
{
    gl_Position = modelMatrix * vec4(position, 1.0);
	FragPos = vec3(modelMatrix* vec4(position, 1.0));
	normal0 = (modelMatrix * vec4(normal, 0.0)).xyz;
}
