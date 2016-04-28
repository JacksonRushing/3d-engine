#include <SDL2\SDL.h>
#include <iostream>
#include "display.h"
#include <glew/GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "camera.h"
#undef main;
#define WIDTH 1920
#define HEIGHT 1080
int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(WIDTH, HEIGHT, "3D-Engine!");
	SDL_SetWindowFullscreen(display.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	

	Vertex vertices[] = 
	{					Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0.0)),
						Vertex(glm::vec3(0,		0.5, 0), glm::vec2(0.5, 1.0)),
						Vertex(glm::vec3(0.5,  -0.5, 0), glm::vec2(1.0, 0.0)) 
	};

	unsigned int indices[] = {0, 1, 2};
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Mesh monkey("./res/monkey3.obj");

	Shader shader("./res/basicShader");

	Texture texture("./res/texture2.jpg");

	Camera camera(glm::vec3(0, 0, -4), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	Transform transform;
	
	float counter = 0.0f;

	while (!display.getshouldClose())
	{
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sincounter = sinf(counter);
		float coscounter = cosf(counter);
		float tancounter = tanf(counter);

		transform.getPos()->x = sincounter;
		transform.getPos()->z = sincounter;
		transform.getRot()->x = (counter *2);
		transform.getRot()->y = (counter * 3);
		transform.getRot()->z = (counter * 1);
		//transform.setScale(glm::vec3(sincounter, coscounter, 1));


		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		monkey.Draw();

		display.update();
		counter += 0.0001f;
	}

	SDL_Quit();
	return 0;
}