#include <SDL2\SDL.h>
#include <iostream>
#include "display.h"
#include <glew/GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#undef main;
int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(800, 600, "Hello World!");
	
	Shader shader("./res/basicShader");

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0)),
							Vertex(glm::vec3(0,		0.5, 0)),
							Vertex(glm::vec3(0.5,  -0.5, 0)) };
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	while (!display.getshouldClose())
	{
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.bind();

		mesh.Draw();

		display.update();
	}

	SDL_Quit();
	return 0;
}