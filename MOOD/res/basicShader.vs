#version 120

varying vec2 texCoord0;

attribute vec3 position;
attribute vec2 texCoord;

void main()
{
	gl_Position = vec4(position, 1.0);
	texCoord0 = texCoord;
}