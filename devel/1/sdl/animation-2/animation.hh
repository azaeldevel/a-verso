
#ifndef OCTETOS_VERSO_V1_ANIMATION_HH
#define OCTETOS_VERSO_V1_ANIMATION_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "../../scenary.hh"

namespace oct::verso::v1::SDL
{
	struct Scenary : public IScenary
	{
		SDL_Window* window; // window
		SDL_Renderer* renderer; // renderer
		SDL_Event event; // event
        int width, height;
		Scenary();
		bool create_window(const char* title, int width, int height);
		virtual void handleEvents();
		virtual void clean();
		virtual void loop();
		virtual void render() = 0;
	};

	struct Game : public Scenary
	{
		SDL_Texture* playertex; // player sprite
		SDL_Texture* enemytex; // enemy sprite
		SDL_Rect p_srcR, p_destR; // player source and destination rectangles
		SDL_Rect e_srcR, e_destR; // enemy source and destination rectangles
		int counter;

		const int FPS = 60;
		const int frameDelay = 500 / FPS;
		uint32_t frameStart;
		int frameTime;
		bool flag;

		virtual bool initialize();
		void update();
		virtual void render();
		virtual void loop();
		bool AABB(SDL_Rect recA, SDL_Rect recB);
	};

}

#endif // OCTETOS_VERSO_V1_ANIMATION_HH
