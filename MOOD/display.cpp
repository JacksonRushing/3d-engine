#include "display.h"
#include <string>
#include <glew/GL/glew.h>
#include <iostream>

void resizeWindow(int w, int h, Camera& _camera);
Display::Display(int width, int height, const std::string& title, glm::vec3 _pos, float _fov, float _zNear, float _zFar)
{	//Number of shades of colors, alpha
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//Buffer size, 32 bits, sum of all above
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//enables doublebuffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl; 
	}
	shouldClose = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	m_camera = Camera(_pos, _fov, (float)width / (float)height, _zNear, _zFar);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
}

void Display::update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{ 
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			resizeWindow(e.window.data1, e.window.data2, m_camera);
			
			break;
		}
		switch (e.type)
		{
		case SDL_QUIT:
			shouldClose = true;
			break;

		case SDL_KEYDOWN:
			std::cout << "key pressed!" << std::endl;
		}

	}
}

bool Display::getshouldClose() const
{
	return shouldClose;
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void resizeWindow(int w, int h, Camera& camera)
{
	glViewport(0, 0, w, h);
	camera.setRatio((float)w / (float)h);
}