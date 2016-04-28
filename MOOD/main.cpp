#include <SDL2\SDL.h>
#include <iostream>
#include "display.h"
#include <glew/GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#undef main;
int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(800, 600, "Hello World!");
	
	

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0.0)),
							Vertex(glm::vec3(0,		0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5,  -0.5, 0), glm::vec2(1.0, 0.0)) };
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");

	Texture texture("./res/texture.jpg");
	texture.bind(0);

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