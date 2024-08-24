
#include "space.hh"
#include "SDL2_gfxPrimitives.h"//https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html


namespace oct::verso::v1::SDL
{

	bool Object::initialize()
	{
		return true;
	}
	void Object::run()
	{
		status = running;
		this->initialize();
		this->loop();
	}
	void Object::loop()
	{
        // game loop
		while (status != Status::stop)
		{
			// handle user events
			handler();

			// update the game
			update();

			// render to the screen
			render();

			SDL_Delay(1);
		}
	}

	void Object::handler()
	{
	}
	void Object::update()
	{
	}

	void Object::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);


        SDL_RenderPresent(renderer);
	}


	void Object::on_active()
	{
	}
	void Object::on_deactive()
	{
	}













	bool Body::initialize()
	{
		return true;
	}
	void Body::run()
	{
		status = running;
		this->initialize();
		this->loop();
	}
	void Body::loop()
	{
        // game loop
		while (status != Status::stop)
		{
			// handle user events
			handler();

			// update the game
			update();

			// render to the screen
			render();

			SDL_Delay(1);
		}
	}

	void Body::handler()
	{
	}
	void Body::update()
	{
	}

	void Body::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);


        SDL_RenderPresent(renderer);
	}


	void Body::on_active()
	{
	}
	void Body::on_deactive()
	{
	}















	bool Space::initialize()
	{
	    //SDL_SetHint (SDL_HINT_RENDER_DRIVER, "opengl") ;
		create_window("Game", 800, 600);
		status = Status::running;

		return false;
	}

	void Space::run()
	{
		status = running;
		initialize();
		loop();
	}

	void Space::loop()
	{
        // game loop
		while (status != Status::stop)
		{
			// handle user events
			handler();

			// update the game
			update();

			// render to the screen
			render();

			SDL_Delay(1);
		}
	}
	void Space::handler()
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
	void Space::update()
	{
		// on key press
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:

				break;
			case SDLK_UP:

				break;
			default:
				break;
			}
		}

	}

	void Space::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);

		//
        int unit = width/12;
        int y = height/2;
        filledCircleRGBA(renderer,0,y,100,255,227,51,255);

        //mercury
        circleRGBA(renderer,0,y,unit * 2,255,255,255,255);
        filledCircleRGBA(renderer,unit * 2,y,5,224,141,28,255);

        //venus
        circleRGBA(renderer,0,y,unit * 3,255,255,255,255);
        filledCircleRGBA(renderer,unit * 3,y,10,175,255,51,255);

        //tierra
        circleRGBA(renderer,0,y,unit * 4,255,255,255,255);
        filledCircleRGBA(renderer,unit * 4,y,20,28,111,224,255);

        //martes
        circleRGBA(renderer,0,y,unit * 5,255,255,255,255);
        filledCircleRGBA(renderer,unit * 5,y,15,236,66,19,255);

        //jupiter
        circleRGBA(renderer,0,y,unit * 6.5,255,255,255,255);
        filledCircleRGBA(renderer,unit * 6.5,y,40,120,91,12,255);

        //saturno
        circleRGBA(renderer,0,y,unit * 8,255,255,255,255);
        circleRGBA(renderer,unit * 8,y,30,223,172,35,255);
        circleRGBA(renderer,unit * 8,y,31,223,172,35,255);
        circleRGBA(renderer,unit * 8,y,32,223,172,35,255);
        circleRGBA(renderer,unit * 8,y,36,223,172,35,255);
        circleRGBA(renderer,unit * 8,y,37,223,172,35,255);
        filledCircleRGBA(renderer,unit * 8,y,25,223,172,35,255);

        //urano
        circleRGBA(renderer,0,y,unit * 9.5,255,255,255,255);
        filledCircleRGBA(renderer,unit * 9.5,y,25,27,137,58,255);

        //neptuno
        circleRGBA(renderer,0,y,unit * 10.5,255,255,255,255);
        filledCircleRGBA(renderer,unit * 10.5,y,20,70,123,185,255);

        SDL_RenderPresent(renderer);
	}


	void Space::on_active()
	{
	}
	void Space::on_deactive()
	{
	}











}
