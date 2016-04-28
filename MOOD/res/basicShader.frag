//shadertype=<glsl>
#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)
	* clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0); //simulates the reflection of light, adjusts pixels brighness by the cosine between the normal and the negative light direction.
}