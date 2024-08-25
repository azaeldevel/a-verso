
#ifndef OCTETOS_AVERSO_V1_SPACE_HH
#define OCTETOS_AVERSO_V1_SPACE_HH


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include <map>

#include "animation.hh"

namespace oct::verso::v1::SDL
{

    struct Object : public Scenary
	{
	    Object();
	    constexpr Object(const std::initializer_list<real>& l) : Scenary(l)
	    {
	    }
	    constexpr Object(const numbers::vector<real>& p) : Scenary(p)
	    {
	    }
	    constexpr Object(const std::initializer_list<real>& l,bool a) : Scenary(l),activable(a)
	    {
	    }
	    constexpr Object(const numbers::vector<real>& p,bool a) : Scenary(p),activable(a)
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

		virtual Object* into(int,int);

		void add_activables(Object*);
		void add_activables(Object&);

		virtual void render_selection(SDL_Renderer*);

		bool activable;
		std::map<Object*,Object*> activables;
		Object* selected;
	};

    struct Body : public Object
	{
	    Body();
	    constexpr Body(const std::initializer_list<real>& l) : Object(l)
	    {
	    }
	    constexpr Body(const numbers::vector<real>& p) : Object(p)
	    {
	    }
	    constexpr Body(const std::initializer_list<real>& l,bool a) : Object(l,a)
	    {
	    }
	    constexpr Body(const numbers::vector<real>& p,bool a) : Object(p,a)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		//virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		std::string name,brief;
		numbers::vector<real> displacement;
	};

    struct Star : public Body
	{
	    Star() = default;
	    constexpr Star(const std::initializer_list<real>& l) : Body(l,true)
	    {
	    }
	    constexpr Star(const std::initializer_list<real>& l,bool a) : Body(l,a)
	    {
	    }
	    constexpr Star(const numbers::vector<real>& p) : Body(p,true)
	    {
	    }
	    constexpr Star(const numbers::vector<real>& p,bool a) : Body(p,a)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		//virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();
		virtual void render_selection(SDL_Renderer*);

		virtual Object* into(int,int);

		float radius;
	};

    struct Planet : public Body
	{
	    Planet() = default;
	    constexpr Planet(const std::initializer_list<real>& l) : Body(l,true)
	    {
	    }
	    constexpr Planet(const numbers::vector<real>& p) : Body(p,true)
	    {
	    }
	    constexpr Planet(const std::initializer_list<real>& l,bool a) : Body(l,a)
	    {
	    }
	    constexpr Planet(const numbers::vector<real>& p,bool a) : Body(p,a)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		//virtual void handler();
		virtual void update();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();

		virtual Object* into(int,int);
		virtual void render_selection(SDL_Renderer*);

		float radius;
	};

	enum class Mode
	{
	    none,
        menu,
        animation,
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

        constexpr Space(const std::initializer_list<real>& l,bool a) : Body(l,a)
	    {
	    }
	    constexpr Space(const numbers::vector<real>& p,bool a) : Body(p,a)
	    {
	    }

		virtual bool initialize();

		virtual void run();

		virtual void loop();

		virtual void handler();
		virtual void update();
		virtual void update_resize();
		virtual void update_orbitar();
		virtual void render();

		virtual void on_active();
		virtual void on_deactive();


		real unit;

		Star sun;
		Planet mercury,venus,earth,mars,jupiter,saturn,uranus,neptune;
		Mode mode;
        real delta;
        real columns;
        numbers::vector<real> step;
		int animation;
	};
}

#endif // OCTETOS_AVERSO_SPACE_HH
