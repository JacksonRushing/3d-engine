#pragma once
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glew/GL/glew.h>
#include "obj_loader.h"
//XYZ coordinates, must be between -1 and 1, sequence of 3 of them. 3 vertexes


class Vertex
{
public:
	Vertex(const glm::vec3& _pos, const glm::vec2& _texCoord, const glm::vec3& _normal = glm::vec3(0, 0, 0))
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->normal = _normal;
		fliptexCoordY();
	}
	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* gettexCoord() { return &texCoord; }
	inline glm::vec3* getNormal() { return &normal; }
	inline void fliptexCoordY() { texCoord.y = 1 - texCoord.y; }
protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(const Mesh& other) {};
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& filename);

	void Draw();

	virtual ~Mesh();

private:
	void initMesh(const IndexedModel& model);
	
	void operator=(const Mesh& other) {}

	enum
	{
		POSITION_VB,

		TEXCOORD_VB,

		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	//mesh data
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	//how big it is, how much we want to draw. 
	unsigned int drawCount;
};



