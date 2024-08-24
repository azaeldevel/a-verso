
#ifndef OCTETOS_AVERSO_V1_SPACE_HH
#define OCTETOS_AVERSO_V1_SPACE_HH


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "animation.hh"

namespace oct::verso::v1::SDL
{

    struct Object : public Scenary
	{
		virtual bool initialize();
		void update();
		virtual void render();
		virtual void loop();
	};

    struct Body : public Object
	{
		virtual bool initialize();
		void update();
		virtual void render();
		virtual void loop();
	};

    struct Space : public Body
	{
		virtual bool initialize();
		void update();
		virtual void render();
		virtual void loop();
	};
}

#endif // OCTETOS_AVERSO_SPACE_HH
