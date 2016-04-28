#pragma once
#include <glm/glm.hpp>
#include <glew/GL/glew.h>
//XYZ coordinates, must be between -1 and 1, sequence of 3 of them. 3 vertexes


class Vertex
{
public:
	Vertex(const glm::vec3& _pos, const glm::vec2& _texCoord)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		fliptexCoordY();
	}
	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* gettexCoord() { return &texCoord; }
	inline void fliptexCoordY() { texCoord.y = 1 - texCoord.y; }
protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

	virtual ~Mesh();

private:
	Mesh(const Mesh& other) {};
	void operator=(const Mesh& other) {}

	enum
	{
		POSITION_VB,

		TEXCOORD_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	//mesh data
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	//how big it is, how much we want to draw. 
	unsigned int drawCount;
};



