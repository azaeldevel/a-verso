
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
	    Object() = default;
	    constexpr Object(const std::initializer_list<real>& l) : Scenary(l)
	    {
	    }
	    constexpr Object(const numbers::vector<real>& p) : Scenary(p)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		virtual bool into(int,int)const;
	};

    struct Body : public Object
	{
	    Body() = default;
	    constexpr Body(const std::initializer_list<real>& l) : Object(l)
	    {
	    }
	    constexpr Body(const numbers::vector<real>& p) : Object(p)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		std::string name,brief;
	};

    struct Star : public Body
	{
	    Star() = default;
	    constexpr Star(const std::initializer_list<real>& l) : Body(l)
	    {
	    }
	    constexpr Star(const numbers::vector<real>& p) : Body(p)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		virtual bool into(int,int)const;

		float radius;
	};

    struct Planet : public Body
	{
	    Planet() = default;
	    constexpr Planet(const std::initializer_list<real>& l) : Body(l)
	    {
	    }
	    constexpr Planet(const numbers::vector<real>& p) : Body(p)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		virtual bool into(int,int)const;

		float radius;
	};

    struct Space : public Body
	{
	    Space() = default;
	    constexpr Space(const std::initializer_list<real>& l) : Body(l)
	    {
	    }
	    constexpr Space(const numbers::vector<real>& p) : Body(p)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		int unit,y;

		Star sun;
		Planet mercury;
	};
}

#endif // OCTETOS_AVERSO_SPACE_HH
