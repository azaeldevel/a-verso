
#include "space.hh"
#include "SDL2_gfxPrimitives.h"//https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html


namespace oct::verso::v1::SDL
{

    Object::Object() : activable(false)
    {
    }

	bool Object::initialize()
	{
		return true;
	}
	void Object::run()
	{
	    std::cout << "void Object::run()\n";
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

	char const *convert_button_number_to_string(int button)
    {
        char const *result = "NO_BUTTON";
        switch (button)
        {
            case SDL_BUTTON_LEFT:
            result = "left";
            break;

            case SDL_BUTTON_MIDDLE:
            result = "middle";
            break;

            case SDL_BUTTON_RIGHT:
            result = "right";
            break;

            default:
            break;
        }

        return result;
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

	Object* Object::into(int x,int y)
	{
        return NULL;
	}
	void Object::add_activables(Object* obj)
	{
        if(obj->activable) activables.insert(std::pair(obj,obj));
	}
	void Object::add_activables(Object& obj)
	{
        if(obj.activable) activables.insert(std::pair(&obj,&obj));
	}
	void Object::render_selection(SDL_Renderer*)
	{
	    std::cout << "void Object::render_selection()\n";
	}














	Body::Body()
	{
	    activable = true;
	}

	bool Body::initialize()
	{
		return true;
	}
	void Body::run()
	{
	    //std::cout << "void Body::run()\n";
		status = running;
		this->initialize();
		this->loop();
		this->clean();
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

	/*void Body::handler()
	{
	}*/
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
		create_window("A verso system", 900, 600);
		status = Status::running;
		mode = Mode::menu;
		delta = 0.009;
		columns = 12;
		position.x() = 0;
		position.y() = height/2;
		step.x() = delta * 20;
		step.y() = 0;

        //std::cout << "Space pinter : "<< (void*)this << "\n";

        unit = width/columns;
        //y = height/2;

        //
        sun.position.x() = 0 + position.x();
        sun.position.y() = position.y();
        sun.radius = 100;
        sun.name = "Sol";
        add_activables(sun);

        //
        mercury.position.x() = unit * 2 + position.x();
        mercury.position.y() = position.y();
        mercury.radius = 5;
        mercury.name = "Mercurio";
        add_activables(mercury);

        //
        venus.position.x() = unit * 3 + position.x();
        venus.position.y() = position.y();
        venus.radius = 10;
        venus.name = "Venus";
        add_activables(venus);

        //
        earth.position.x() = unit * 4 + position.x();
        earth.position.y() = position.y();
        earth.radius = 20;
        earth.name = "Tierra";
        add_activables(earth);

        //
        mars.position.x() = unit * 5 + position.x();
        mars.position.y() = position.y();
        mars.radius = 15;
        mars.name = "Martes";
        add_activables(mars);

        //
        jupiter.position.x() = unit * 6.5 + position.x();
        jupiter.position.y() = position.y();
        jupiter.radius = 40;
        jupiter.name = "Jupiter";
        add_activables(jupiter);

        //
        saturn.position.x() = unit * 8 + position.x();
        saturn.position.y() = position.y();
        saturn.radius = 25;
        saturn.name = "Saturno";
        add_activables(saturn);

        //
        uranus.position.x() = unit * 9.5 + position.x();
        uranus.position.y() = position.y();
        uranus.radius = 25;
        uranus.name = "Urano";
        add_activables(uranus);

        //
        neptune.position.x() = unit * 10.5 + position.x();
        neptune.position.y() = position.y();
        neptune.radius = 20;
        neptune.name = "Neptuno";
        add_activables(neptune);

		return true;
	}

	void Space::run()
	{
	    //std::cout << "void Space::run()\n";
		status = running;
		initialize();
		loop();
		clean();
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
	    //std::cout << "void Object::handler()\n";
	    //std::cout << "Object pinter : "<< (void*)this << "\n";
		SDL_PollEvent(&event);
		Object* obj = NULL;
		switch (event.type)
		{
		case SDL_QUIT:
			status = Status::stop;
			break;
        case SDL_MOUSEMOTION:
            /*for(const auto& [k,v] : activables)
            {
                obj = k->into(event.motion.x,event.motion.y);
                if(obj) selected = obj;
            }*/
            break;
        case SDL_MOUSEBUTTONDOWN:
        //case SDL_MOUSEBUTTONUP:
            selected = NULL;
            for(const auto& [k,v] : activables)
            {
                obj = k->into(event.motion.x,event.motion.y);
                if(obj)
                {
                    selected = obj;
                    //std::cout << "Selected :" << (void*)selected << "\n";
                }
            }
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_a)
            {
                mode = Mode::animation;
                std::cout << "Mode de animacion.\n";
            }
            else if(event.key.keysym.sym == SDLK_m)
            {
                mode = Mode::menu;
                std::cout << "Mode de menu.\n";
            }
            break;
		default:
			break;
		}
	}
	void Space::update()
	{
        if(mode == Mode::menu) return;

        if(columns < 30)
        {
            columns += delta;
            unit = width/columns;
        }
        if(position.x() < width/2) position = position + step;
        //std::cout << "unit : " << unit << "\n";

        float zoom = 4;
        if(sun.radius > 30) sun.radius = sun.radius - (delta * zoom * 2);
        if(mercury.radius > 10) mercury.radius = mercury.radius - (delta * zoom);
        if(venus.radius > 10) venus.radius = venus.radius - (delta * zoom);
        if(earth.radius > 10) earth.radius = earth.radius - (delta * zoom);
        if(mars.radius > 10) mars.radius = mars.radius - (delta * zoom);
        if(jupiter.radius > 10) jupiter.radius = jupiter.radius - (delta * zoom);
        if(saturn.radius > 10) saturn.radius = saturn.radius - (delta * zoom);
        if(uranus.radius > 10) uranus.radius = uranus.radius - (delta * zoom);
        if(neptune.radius > 10) neptune.radius = neptune.radius - (delta * zoom);

        //
        sun.position.x() = 0;
        //
        mercury.position.x() = (unit * 2);
        //
        venus.position.x() = (unit * 3);
        //
        earth.position.x() = (unit * 4);
        //
        mars.position.x() = (unit * 5);
        //
        jupiter.position.x() = (unit * 6.5);
        //
        saturn.position.x() = (unit * 8);
        //
        uranus.position.x() = (unit * 9.5);
        //
        neptune.position.x() = (unit * 10.5);
	}

	void Space::render()
	{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//sun
        filledCircleRGBA(renderer,position.x() + sun.position.x(),sun.position.y(),sun.radius,255,227,51,255);

        //mercury
        circleRGBA(renderer,position.x(),position.y(),mercury.position.x(),255,255,255,255);
        filledCircleRGBA(renderer, position.x() + mercury.position.x(),mercury.position.y(),mercury.radius,224,141,28,255);

        //venus
        circleRGBA(renderer,position.x(),position.y(),venus.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + venus.position.x(),venus.position.y(),venus.radius,175,255,51,255);

        //tierra
        circleRGBA(renderer,position.x(),position.y(),earth.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + earth.position.x(),earth.position.y(),earth.radius,28,111,224,255);

        //martes
        circleRGBA(renderer,position.x(),position.y(),mars.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + mars.position.x(),mars.position.y(),mars.radius,236,66,19,255);

        //jupiter
        circleRGBA(renderer,position.x(),position.y(),jupiter.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + jupiter.position.x(),jupiter.position.y(),jupiter.radius,120,91,12,255);

        //saturno
        circleRGBA(renderer,position.x(),position.y(),saturn.position.x(),255,255,255,255);
        circleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius + 5,223,172,35,255);
        circleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius + 6,223,172,35,255);
        circleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius + 7,223,172,35,255);
        circleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius + 11,223,172,35,255);
        circleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius + 12,223,172,35,255);
        filledCircleRGBA(renderer,position.x() + saturn.position.x(),saturn.position.y(),saturn.radius,223,172,35,255);

        //urano
        circleRGBA(renderer,position.x(),position.y(),uranus.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + uranus.position.x(),uranus.position.y(),uranus.radius,27,137,58,255);

        //neptuno
        circleRGBA(renderer,position.x(),neptune.position.y(),neptune.position.x(),255,255,255,255);
        filledCircleRGBA(renderer,position.x() + neptune.position.x(),neptune.position.y(),neptune.radius,70,123,185,255);

        //circleRGBA(renderer,earth.position.x(),earth.position.y(),earth.radius + 1,0,255,0,255);
        //circleRGBA(renderer,neptune.position.x(),neptune.position.y(),neptune.radius + 2,0,255,0,255);

        if(selected)
        {
            std::cout << "Render selection :" << (void*)selected << "\n";
            selected->render_selection(renderer);
        }

        SDL_RenderPresent(renderer);
	}


	void Space::on_active()
	{
	}
	void Space::on_deactive()
	{
	}











	bool Star::initialize()
	{
		return true;
	}
	void Star::run()
	{
		status = running;
		this->initialize();
		this->loop();
		this->clean();
	}
	void Star::loop()
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

	/*void Star::handler()
	{
	}*/
	void Star::update()
	{
	}

	void Star::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);


        SDL_RenderPresent(renderer);
	}


	void Star::on_active()
	{
	}
	void Star::on_deactive()
	{
	}

	Object* Star::into(int x,int y)
	{
        //std::cout << "Star : " << x << "," << y << "\n";
        auto d = position.distance(x,y);
        if(d < radius)
        {
            //std::cout << "distance : " << d << "\n";
            return this;
        }
        return NULL;
	}
	void Star::render_selection(SDL_Renderer* rend)
	{
	    std::cout << "void Star::render_selection()\n";
	    std::cout << "(" << position.x() << "," << position.y() << ")\n";
	    circleRGBA(rend,position.x(),position.y(),radius + 3,0,255,0,255);
	    circleRGBA(rend,position.x(),position.y(),radius + 4,0,255,0,255);
	}

















	bool Planet::initialize()
	{
		return true;
	}
	void Planet::run()
	{
		status = running;
		this->initialize();
		this->loop();
		this->clean();
	}
	void Planet::loop()
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

	/*void Planet::handler()
	{
	}*/
	void Planet::update()
	{
	}

	void Planet::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);


        SDL_RenderPresent(renderer);
	}


	void Planet::on_active()
	{
	}
	void Planet::on_deactive()
	{
	}

	Object* Planet::into(int x,int y)
	{
        //std::cout << "Planet : " << x << "," << y << "\n";
        auto d = position.distance(x,y);
        if(d < radius)
        {
            //std::cout << "distance : " << d << "\n";
            return this;
        }
        return NULL;
	}
	void Planet::render_selection(SDL_Renderer* rend)
	{
	    std::cout << "void Planet::render_selection()\n";
	    std::cout << "(" << position.x() << "," << position.y() << ")\n";
	    circleRGBA(rend,position.x(),position.y(),radius + 3,0,255,0,255);
	    circleRGBA(rend,position.x(),position.y(),radius + 4,0,255,0,255);
	}
}
