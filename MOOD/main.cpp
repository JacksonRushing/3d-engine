#include <SDL2\SDL.h>
#include <iostream>
#include "display.h"
#include <glew/GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#undef main;
int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(1600, 900, "Hello World!");
	
	

	Vertex vertices[] = 
	{					Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0.0)),
						Vertex(glm::vec3(0,		0.5, 0), glm::vec2(0.5, 1.0)),
						Vertex(glm::vec3(0.5,  -0.5, 0), glm::vec2(1.0, 0.0)) 
	};

	unsigned int indices[] = {0, 1, 2};
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Shader shader("./res/basicShader");

	Texture texture("./res/texture.jpg");

	Transform transform;
	
	float counter = 0.0f;

	while (!display.getshouldClose())
	{
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sincounter = sinf(counter);
		float coscounter = cosf(counter);
		float tancounter = tanf(counter);

		transform.getPos()->x = sincounter;
		transform.getPos()->y = coscounter;
		transform.getRot()->z = (counter * 10);
		transform.setScale(glm::vec3(sincounter, coscounter, tancounter));


		shader.bind();
		texture.bind(0);
		shader.update(transform);
		mesh.Draw();

		display.update();
		counter += 0.0001f;
	}

	SDL_Quit();
	return 0;
}