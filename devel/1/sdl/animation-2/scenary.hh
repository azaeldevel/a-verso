
#ifndef OCTETOS_VERSO_V1_SCENARY_HH
#define OCTETOS_VERSO_V1_SCENARY_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "../../scenary.hh"

namespace oct::verso::v1::SDL
{
	struct Scenary : public IScenary
	{
	    Scenary();
	    constexpr Scenary(const std::initializer_list<real>& l) : IScenary(l)
	    {
	    }
	    constexpr Scenary(const numbers::vector<real>& p) : IScenary(p)
	    {
	    }

		SDL_Window* window; // window
		SDL_Renderer* renderer; // renderer
		SDL_Event event; // event
        int width, height;
		bool create_window(const char* title, int width, int height);


		virtual bool initialize();
		virtual void clean();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();
	};
}

#endif // OCTETOS_VERSO_V1_ANIMATION_HH
