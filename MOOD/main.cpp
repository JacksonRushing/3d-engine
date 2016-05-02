#include <SDL2\SDL.h>
#include <iostream>
#include "display.h"
#include <glew/GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "camera.h"
#include <vector>
#include <algorithm>
#undef main;
#define WIDTH 1366
#define HEIGHT 768
int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//Display::Display(int width, int height, const std::string& title, glm::vec3 _pos, float _fov, float _zNear, float _zFar)
	Display display(WIDTH, HEIGHT, "3D-Engine!", glm::vec3(0, 0, -2), 70.0f, 0.01f, 1000.0f);
	
	

	Vertex vertices[] = 
	{					Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0.0)),
						Vertex(glm::vec3(0,		0.5, 0), glm::vec2(0.5, 1.0)),
						Vertex(glm::vec3(0.5,  -0.5, 0), glm::vec2(1.0, 0.0)) 
	};

	unsigned int indices[] = {0, 1, 2};
	
	std::vector<Mesh*> meshes;
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	meshes.push_back(&mesh);

	Mesh monkey("./res/monkey3.obj");
	meshes.push_back(&monkey);

	Mesh cube("./res/cube.obj");
	meshes.push_back(&cube);

	//Mesh ironman("./res/iron_man.obj");
	//meshes.push_back(&ironman);

	Shader shader("./res/basicShader");

	Texture texture("./res/texture2.jpg");


	

	Transform transform;
	
	float counter = 0.0f;

	while (!display.getshouldClose())
	{
		
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sincounter = sinf(counter);
		float coscounter = cosf(counter);
		float tancounter = tanf(counter);

		glm::vec2 mouseMovement = *display.getMouseMotion();
		//transform.getPos()->x = sincounter;
		//transform.getPos()->z = sincounter;
		//transform.getRot()->x = (counter *2);
		//transform.getRot()->y = (counter * 3);
		if (!display.firstPersonToggle)
		{
			transform.getRot()->x += mouseMovement.y / 1000;
			transform.getRot()->y += mouseMovement.x / 1000;
		}
		else
		{
			display.getFirstPersonCamera()->rotate(mouseMovement);
		}
		//transform.getRot()->z = (counter * 1);
		//transform.setScale(glm::vec3(sincounter, coscounter, 1));


		shader.bind();
		texture.bind(0);
		if (!display.firstPersonToggle)
		{
			shader.update(transform, *display.getWorldCamera());
		}
		else
		{
			display.getFirstPersonCamera()->move(*display.getVelocity());
			shader.update(transform, *display.getFirstPersonCamera());
			
		}
		int index = std::max(0, std::min(display.getDrawnMesh() , (int)meshes.size() - 1));
		meshes[index]->Draw();
		//cube.Draw();
		//monkey.Draw();
		//mesh.Draw();

		display.update();
		counter += 0.0001f;
	}

	SDL_Quit();
	return 0;
}