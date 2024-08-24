
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

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();
	};

    struct Body : public Object
	{
		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();
	};

    struct Space : public Body
	{
		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();
	};
}

#endif // OCTETOS_AVERSO_SPACE_HH
