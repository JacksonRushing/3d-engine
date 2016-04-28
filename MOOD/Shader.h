#pragma once
#include <string>
#include <glew/GL/glew.h>
#include "Transform.h"
#include "camera.h"
class Shader
{
public:
	Shader(const std::string& filename);
	//set the GPU in a state so that it's using our vertex shader and fragment shader
	void bind();
	void update(const Transform& _transform, const camera& _camera);

	virtual ~Shader();
	
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	void operator=(const Shader& other){} 

	enum
	{
		TRANFORM_U,

		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
	
};
enum
{
	vertexShader,
	fragmentShader
};

