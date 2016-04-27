#include "Shader.h"
#include <fstream>
#include <iostream>

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& filename);
static GLuint createShader(const std::string& code, GLenum shaderType);

Shader::Shader(const std::string& filename)
{
	program = glCreateProgram();
	shaders[vertexShader] = createShader(loadShader(filename + ".vs"), GL_VERTEX_SHADER);
	shaders[fragmentShader] = createShader(loadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");

	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::bind()
{
	glUseProgram(program);
}

static GLuint createShader(const std::string& code, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = code.c_str();
	shaderSourceStringLengths[0] = code.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string loadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	
	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}
	
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
	}
}