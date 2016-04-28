#include "Mesh.h"
#include <vector>
#include "obj_loader.h"
Mesh::Mesh(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initMesh(model);

}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].gettexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}
	initMesh(model);
	//drawCount = numVertices;
	//drawCount = numIndices;
	/*glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;

	positions.reserve(numVertices);
	texcoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPos());
		texcoords.push_back(*vertices[i].gettexCoord());
	}*/

	//glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	////interpret the buffer as an array, the array with all of the vertices
	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	//							//number of vertices times the size of one vertice, the array of vertices, GL_STATIC_DRAW = a draw hint, tells OpenGL that we're not going to change the data.
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	////telling OpenGL how to interpret the data, attributes are the members of the class, in this case the vec3
	////there's going to be an attrib array 0, this data is going to be the 0th attrib array, we're going to tell it how to read it as an array (skip over stuff, etc)
	//glEnableVertexAttribArray(0);

	////index, # of pieces of data, the type of data, stride, starting point
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//

	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	////number of vertices times the size of one vertice, the array of vertices, GL_STATIC_DRAW = a draw hint, tells OpenGL that we're not going to change the data.
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);

	////telling OpenGL how to interpret the data, attributes are the members of the class, in this case the vec3
	////there's going to be an attrib array 0, this data is going to be the 0th attrib array, we're going to tell it how to read it as an array (skip over stuff, etc)
	//glEnableVertexAttribArray(1);

	////index, # of pieces of data, the type of data, stride, starting point
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	////references the data of another array
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	////after done with vertex array operations, set it to zero
	//glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel& model)
{
	drawCount = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	//interpret the buffer as an array, the array with all of the vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	//number of vertices times the size of one vertice, the array of vertices, GL_STATIC_DRAW = a draw hint, tells OpenGL that we're not going to change the data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), model.positions.data(), GL_STATIC_DRAW);

	//telling OpenGL how to interpret the data, attributes are the members of the class, in this case the vec3
	//there's going to be an attrib array 0, this data is going to be the 0th attrib array, we're going to tell it how to read it as an array (skip over stuff, etc)
	glEnableVertexAttribArray(0);

	//index, # of pieces of data, the type of data, stride, starting point
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	//number of vertices times the size of one vertice, the array of vertices, GL_STATIC_DRAW = a draw hint, tells OpenGL that we're not going to change the data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), model.texCoords.data(), GL_STATIC_DRAW);

	//telling OpenGL how to interpret the data, attributes are the members of the class, in this case the vec3
	//there's going to be an attrib array 0, this data is going to be the 0th attrib array, we're going to tell it how to read it as an array (skip over stuff, etc)
	glEnableVertexAttribArray(1);

	//index, # of pieces of data, the type of data, stride, starting point
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), model.normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//references the data of another array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);

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
	//glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glDrawElementsBaseVertex(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
}
