#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <SDL2/SDL.h>
class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();
	void update();
	bool getshouldClose() const;
	void clear(float r, float g, float b, float a);

private:
	Display(const Display& other);
	Display& operator=(const Display& other){}
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool shouldClose;
};


#endif //DISPLAY_H