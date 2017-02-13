#include "Display.h"
#include <GL/glew.h> 
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);



	glewExperimental = GL_TRUE;
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);
	
	GLenum status = glewInit();

	if (status != GLEW_OK) 
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Display::IsClosed() {
	return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			keysHeld[event.key.keysym.sym] = true;
		}
		if (event.type == SDL_KEYUP)
		{
			keysHeld[event.key.keysym.sym] = false;
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			
			if (firstMouse)
			{
				xPos = event.motion.xrel;//X mouse movement
				yPos = event.motion.yrel;//Y mouse movement

				lastX = xPos;
				lastY = yPos;
				firstMouse = false;
			}
			GLfloat xOffSet = xPos - lastX;
			GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

			lastX = xPos;
			lastY = yPos;
		
		}

		//Keyboard events
		if (keysHeld[SDLK_ESCAPE])
		{
			//Exit with escape
			m_isClosed = true;
		}
		if (keysHeld[SDLK_a])
		{
			//strafe left
		}
		if (keysHeld[SDLK_d])
		{
			//strafe right
		}
		if (keysHeld[SDLK_w])
		{
			//go forward
		}
		if (keysHeld[SDLK_s])
		{
			//go backward
		}
	}
}
