


#include "scenary.hh"


namespace oct::verso::v1::SDL
{
	Scenary::Scenary() : window(NULL), renderer(NULL), event{0}
	{
	}

	bool Scenary::create_window(const char* title, int w, int h)
	{
	    width = w;
	    height = h;
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

		return true;
	}




	bool Scenary::initialize()
	{
		return true;
	}
	void Scenary::clean()
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	void Scenary::run()
	{
		status = running;
		this->initialize();
		this->loop();
		this->clean();
	}
	void Scenary::loop()
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

	void Scenary::handler()
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

	void Scenary::update()
	{
	}

	void Scenary::render()
	{
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);


        SDL_RenderPresent(renderer);
	}


	void Scenary::on_active()
	{
	}
	void Scenary::on_deactive()
	{
	}



}
