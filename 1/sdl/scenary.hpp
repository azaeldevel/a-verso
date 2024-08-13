﻿
#ifndef OCTETOS_VERSO_V3_SDL_SCENARY_HPP
#define OCTETOS_VERSO_V3_SDL_SCENARY_HPP
#ifdef OCTETOS_VERSO_V3_SCENARY_HPP_ONCE
	#error "Otro esenario ya existe en este contexto"
#endif

#include "../scenary.hpp"

#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

namespace oct::verso::v1::SDL
{
	struct Scenary : public IScenary
	{
		SDL_Window* window; // window
		SDL_Renderer* renderer; // renderer
		SDL_Event event; // event

		Scenary();
		bool create_window(const char* title, int width, int height);
		void handleEvents();
		void clean();
		virtual void render() = 0;
	};

	struct OpenGL : public Scenary
	{
		SDL_GLContext gContext;
	};

	SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
}

#endif