
//Using SDL and standard IO

#include <gl/glew.h>
#include <gl/glu.h>

#include "glew-examples.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <iostream>


namespace oct::verso::v1::devel::glew
{
	bool Scenary::initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Create context
				context = SDL_GL_CreateContext(window);
				if (context == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					//Initialize GLEW
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();
					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					}

					//Use Vsync
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}

				}
				//SDL_GL_MakeCurrent(window, context);
			}
		}
		status = Status::running;

		return true;
	}
	void Scenary::render()
	{
	}
	void Scenary::loop()
	{
		SDL_PollEvent(&event);

		//User requests quit
		if (event.type == SDL_QUIT)
		{
			status = Status::stop;
		}

		render();
	}
	void Scenary::clean()
	{
		//Destroy window	
		SDL_DestroyWindow(window);
		window = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}
	void Scenary::run()
	{
		//Start up SDL and create window
		if (!initialize())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//While application is running
			while (status > Status::star)
			{
				loop();
			}

		}

		//Free resources and close SDL
		clean();
	}




}