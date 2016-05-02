#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "camera.h"
#include "Mesh.h"
class Display
{
public:
	Display(int width, int height, const std::string& title, glm::vec3 _pos, float _fov, float _zNear, float _zFar);
	virtual ~Display();
	void update();
	bool getshouldClose() const;
	void clear(float r, float g, float b, float a);
	SDL_Window* getWindow() const { return m_window; }
	Camera* getWorldCamera() { return &worldCamera; }
	Camera* getFirstPersonCamera() { return &firstPersonCamera; }
	int getDrawnMesh() { return drawnMesh; }
	void setMouseMotion(int x, int y) { mouseMotion = glm::vec2(x, y); }
	glm::vec2* getMouseMotion() { return &mouseMotion; }
	glm::vec3* getVelocity() { return &velocity; }
	void cameraZoom(int);
	bool firstPersonToggle = false;
private:
	Display(const Display& other);
	Display& operator=(const Display& other){}
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool shouldClose;
	Camera worldCamera;
	Camera firstPersonCamera;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	int drawnMesh = 0;
	glm::vec2 mouseMotion;
};


#endif //DISPLAY_H