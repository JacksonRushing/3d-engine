#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	//interpret the buffer as an array, the array with all of the vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
								//number of vertices times the size of one vertice, the array of vertices, GL_STATIC_DRAW = a draw hint, tells OpenGL that we're not going to change the data.
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	//telling OpenGL how to interpret the data, attributes are the members of the class, in this case the vec3
	//there's going to be an attrib array 0, this data is going to be the 0th attrib array, we're going to tell it how to read it as an array (skip over stuff, etc)
	glEnableVertexAttribArray(0);

	//index, # of pieces of data, the type of data, stride, starting point
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	//after done with vertex array operations, set it to zero
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);
	//mode, (triangles, lines, point, etc) where to start, count (how far do you want to read?
	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}
