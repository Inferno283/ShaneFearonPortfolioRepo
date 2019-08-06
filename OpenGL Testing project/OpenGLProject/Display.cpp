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
	SDL_SetRelativeMouseMode(SDL_TRUE);

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
}

void Display::Update(Camera *camera, bool &wireFrame)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			keysHeld[event.key.keysym.sym] = true;//Crashes here when holding down unhandled key but I don't know why
		}
		if (event.type == SDL_KEYUP)
		{
			keysHeld[event.key.keysym.sym] = false;
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			xPos = static_cast< GLfloat >(event.motion.xrel);//X mouse movement
			yPos = static_cast< GLfloat >(event.motion.yrel);//Y mouse movement
			
			camera->UpdateMouseMovement(glm::vec2(xPos, -yPos));
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
			camera->strafeLeft();
		}
		if (keysHeld[SDLK_d])
		{
			//strafe right
			camera->strafeRight();
		}
		if (keysHeld[SDLK_w])
		{
			//go forward
			camera->moveForward();
		}
		if (keysHeld[SDLK_s])
		{
			//go backward
			camera->moveBackward();
		}
		if (keysHeld[SDLK_r])
		{
			//go up
			camera->moveUpward();
		}
		if (keysHeld[SDLK_f])
		{
			//go down
			camera->moveDownward();
		}
		if (keysHeld[SDLK_1])
		{
			wireFrame = true;
		}
		if (keysHeld[SDLK_2])
		{
			wireFrame = false;
		}
		if (keysHeld[SDLK_n])
		{
			#define numMetaballs  numMetaballs+1
		}
	

	}
}