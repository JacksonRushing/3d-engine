#pragma once
#include <string>
#include <glew/GL/glew.h>
class Shader
{
public:
	Shader(const std::string& filename);
	//set the GPU in a state so that it's using our vertex shader and fragment shader
	void bind();

	virtual ~Shader();
	
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	void operator=(const Shader& other){} 
	GLuint program;
	GLuint shaders[NUM_SHADERS];
	
};
enum
{
	vertexShader,
	fragmentShader
};

