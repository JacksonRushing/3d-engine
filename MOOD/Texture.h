#pragma once
#include <string>
#include <glew/GL/glew.h>
class Texture
{
public:
	Texture(const std::string filename);

	virtual ~Texture();

	void bind(unsigned int unit);

private:
	void operator=(const Texture& other) {}
	Texture(const Texture& other) {}
	//texture handle
	GLuint texture;
};

