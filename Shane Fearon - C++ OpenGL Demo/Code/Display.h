#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>


class Display
{
public:
	Display(int width, int height, const std:: string& title);

	void Clear(float r, float g, float b, float a);
	bool IsClosed();
	void Update();
	int getMouseX() { return x; }
	int getMouseY(){return y;}
	virtual ~Display();
protected:
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	bool keysHeld[323] = { false };
	int x;
	int y;
	bool firstMouse = true;
	int lastX;
	int lastY;
	int xPos;
	int yPos;
};

#endif //DISPLAY_H