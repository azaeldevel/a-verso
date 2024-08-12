﻿
//Using SDL and standard IO
#include "animation-1.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

namespace verso = oct::verso::v1;


const int ScreenWidth = 800;
const int ScreenHeight = 600;
verso::SDL::Game scenary;
verso::SDL::OpenGL sc_opengl;

// texture manager
static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

int cmd = 1;

int main(int argc, char* args[])
{
	switch (cmd)
	{
	case 1:
		return scenary.main(argc, args);
		break;
	case 2:
		return sc_opengl.main(argc, args);
		break;
	}
	return EXIT_SUCCESS;
}



static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(fileName);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", fileName, IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}


namespace oct::verso::v1
{
	IScenary::IScenary() : status(Status::stop)
	{
	}
	IScenary::IScenary(Status r) : status(r)
	{
	}
}
namespace oct::verso::v1::SDL
{
	Scenary::Scenary() : window(NULL), renderer(NULL), event{0}
	{
	}

	bool Scenary::create_window(const char* title, int width, int height)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			printf("SDL initialized!\n");
			window = SDL_CreateWindow(title, 0, 0, width, height, 0);
			if (window)
			{
				printf("Window created!\n");
			}
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				printf("Renderer created!\n");
			}
		}
		else
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			
		}
		status = Status::stop;

		return true;
	}

	void Scenary::handleEvents() 
	{
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			status = Status::stop;
			break;
		default:
			break;
		}
	}

	void Scenary::clean() 
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		printf("Game cleaned!\n");
	}





	bool Game::initialize()
	{
		p_destR.w = 100;
		p_destR.h = 100;
		p_destR.y = ScreenHeight / 2;	

		return false;
	}


	void Game::update()
	{
		// on key press
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) 
		{
			switch (event.key.keysym.sym) 
			{
			case SDLK_RIGHT:
				p_destR.x += 5;
				break;
			case SDLK_UP:
				p_destR.y -= 5;
				break;
			default:
				break;
			}
		}

		// enemy position
		e_destR.w = 45;
		e_destR.h = 45;
		e_destR.x = ScreenWidth / 2 - e_destR.w / 2;
		e_destR.y = ScreenHeight / 1.6 - e_destR.h / 1.6;

		// collision detection and game over
		if (AABB(p_destR, e_destR)) {
			printf("\n\t*Collision Detected!*\n");
			printf("\t*Game Over!*\n\n");
			status = Status::stop;
		}

	}

	void Game::render() {
		// this is where we add stuff (textutes) to render
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, playertex, NULL, &p_destR);
		SDL_RenderCopy(renderer, enemytex, NULL, &e_destR);
		SDL_RenderPresent(renderer);
	}



	bool Game::AABB(SDL_Rect recA, SDL_Rect recB) 
	{
		if (
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.y) {
			return true;
		}
		return false;
	}

	int Game::main(int argc, char* args[])
	{
		const int FPS = 60;
		const int frameDelay = 500 / FPS;
		uint32_t frameStart;
		int frameTime;

		scenary.initialize();
		scenary.create_window("Game", ScreenWidth, ScreenHeight);
		scenary.playertex = LoadTexture("../../../assets/player.bmp", scenary.renderer);
		scenary.enemytex = LoadTexture("../../../assets/enemy.bmp", scenary.renderer);
		scenary.status = Status::started;

		bool flag = true; // winning condition

		// game loop
		while (scenary.status != Status::stop)
		{
			frameStart = SDL_GetTicks();

			// handle user events
			scenary.handleEvents();

			// update the game
			scenary.update();

			// render to the screen
			scenary.render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}

			if (scenary.p_destR.x >= ScreenWidth / 1.88 && flag)
			{
				printf("\n\t*No Collision Detected!*\n\t*You Won!*\n\n");
				flag = false;
			}
		}

		scenary.clean();

		return EXIT_SUCCESS;
	}








	bool OpenGL::initialize()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Use OpenGL 3.1 core
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			//Create window
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create context
				gContext = SDL_GL_CreateContext(window);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
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

					//Initialize OpenGL
					if (!initGL())
					{
						printf("Unable to initialize OpenGL!\n");
						success = false;
					}
				}
			}
		}

		return success;
	}

	bool OpenGL::initGL()
	{
		//Success flag
		bool success = true;

		//Generate program
		gProgramID = glCreateProgram();

		//Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Get vertex source
		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};

		//Set vertex source
		glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

		//Compile vertex source
		glCompileShader(vertexShader);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexShader);
			printShaderLog(vertexShader);
			success = false;
		}
		else
		{
			//Attach vertex shader to program
			glAttachShader(gProgramID, vertexShader);


			//Create fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
			};

			//Set fragment source
			glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

			//Compile fragment source
			glCompileShader(fragmentShader);

			//Check fragment shader for errors
			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
			if (fShaderCompiled != GL_TRUE)
			{
				printf("Unable to compile fragment shader %d!\n", fragmentShader);
				printShaderLog(fragmentShader);
				success = false;
			}
			else
			{
				//Attach fragment shader to program
				glAttachShader(gProgramID, fragmentShader);


				//Link program
				glLinkProgram(gProgramID);

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
				if (programSuccess != GL_TRUE)
				{
					printf("Error linking program %d!\n", gProgramID);
					printProgramLog(gProgramID);
					success = false;
				}
				else
				{
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
					if (gVertexPos2DLocation == -1)
					{
						printf("LVertexPos2D is not a valid glsl program variable!\n");
						success = false;
					}
					else
					{
						//Initialize clear color
						glClearColor(0.f, 0.f, 0.f, 1.f);

						//VBO data
						GLfloat vertexData[] =
						{
							-0.5f, -0.5f,
							 0.5f, -0.5f,
							 0.5f,  0.5f,
							-0.5f,  0.5f
						};

						//IBO data
						GLuint indexData[] = { 0, 1, 2, 3 };

						//Create VBO
						glGenBuffers(1, &gVBO);
						glBindBuffer(GL_ARRAY_BUFFER, gVBO);
						glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

						//Create IBO
						glGenBuffers(1, &gIBO);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
					}
				}
			}
		}

		return success;
	}

	void OpenGL::handleKeys(unsigned char key, int x, int y)
	{
		//Toggle quad
		if (key == 'q')
		{
			gRenderQuad = !gRenderQuad;
		}
	}

	void OpenGL::update()
	{
		//No per frame update needed
	}

	void OpenGL::render()
	{
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//Render quad
		if (gRenderQuad)
		{
			//Bind program
			glUseProgram(gProgramID);

			//Enable vertex position
			glEnableVertexAttribArray(gVertexPos2DLocation);

			//Set vertex data
			glBindBuffer(GL_ARRAY_BUFFER, gVBO);
			glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

			//Set index data and render
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
			glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

			//Disable vertex position
			glDisableVertexAttribArray(gVertexPos2DLocation);

			//Unbind program
			glUseProgram(NULL);
		}
	}

	void OpenGL::close()
	{
		//Deallocate program
		glDeleteProgram(gProgramID);

		//Destroy window	
		SDL_DestroyWindow(window);
		window = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

	void OpenGL::printProgramLog(GLuint program)
	{
		//Make sure name is shader
		if (glIsProgram(program))
		{
			//Program log length
			int infoLogLength = 0;
			int maxLength = infoLogLength;

			//Get info string length
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//Allocate string
			char* infoLog = new char[maxLength];

			//Get info log
			glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
			if (infoLogLength > 0)
			{
				//Print Log
				printf("%s\n", infoLog);
			}

			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf("Name %d is not a program\n", program);
		}
	}

	void OpenGL::printShaderLog(GLuint shader)
	{
		//Make sure name is shader
		if (glIsShader(shader))
		{
			//Shader log length
			int infoLogLength = 0;
			int maxLength = infoLogLength;

			//Get info string length
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			//Allocate string
			char* infoLog = new char[maxLength];

			//Get info log
			glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
			if (infoLogLength > 0)
			{
				//Print Log
				printf("%s\n", infoLog);
			}

			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf("Name %d is not a shader\n", shader);
		}
	}

	int OpenGL::main(int argc, char* args[])
	{
		//Start up SDL and create window
		if (!initialize())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Enable text input
			SDL_StartTextInput();

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Handle keypress with current mouse position
					else if (e.type == SDL_TEXTINPUT)
					{
						int x = 0, y = 0;
						SDL_GetMouseState(&x, &y);
						handleKeys(e.text.text[0], x, y);
					}
				}

				//Render quad
				render();

				//Update screen
				SDL_GL_SwapWindow(window);
			}

			//Disable text input
			SDL_StopTextInput();
		}

		//Free resources and close SDL
		close();

		return 0;
	}
}