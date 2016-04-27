#pragma once
#include <glm/glm.hpp>
#include <glew/GL/glew.h>
//XYZ coordinates, must be between -1 and 1, sequence of 3 of them. 3 vertexes


class Vertex
{
public:
	Vertex(const glm::vec3& _pos)
	{
		this->pos = _pos;
	}
protected:
private:
	glm::vec3 pos;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);

	void Draw();

	virtual ~Mesh();

private:
	Mesh(const Mesh& other) {};
	void operator=(const Mesh& other) {}

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	//mesh data
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	//how big it is, how much we want to draw. 
	unsigned int drawCount;
};



