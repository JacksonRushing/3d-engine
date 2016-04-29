#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "camera.h"
class Display
{
public:
	Display(int width, int height, const std::string& title, glm::vec3 _pos, float _fov, float _zNear, float _zFar);
	virtual ~Display();
	void update();
	bool getshouldClose() const;
	void clear(float r, float g, float b, float a);
	SDL_Window* getWindow() const { return m_window; }
	Camera* getCamera() { return &m_camera; }

private:
	Display(const Display& other);
	Display& operator=(const Display& other){}
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool shouldClose;
	Camera m_camera;
};


#endif //DISPLAY_H