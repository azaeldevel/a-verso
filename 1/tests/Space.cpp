
//Using SDL and standard IO
#include "Space.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <iostream>

namespace verso = oct::verso::v1;


namespace oct::verso::v1::devel
{
	bool Space::initialize()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		{
			printf("error initializing SDL: %s\n", SDL_GetError());
		}
		window = SDL_CreateWindow("Space",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 600, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		std::cout << "Inicializando Space...\n";

		return true;
	}
	void Space::render()
	{
		std::cout << "Rendering..\n";
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			status = Status::stop;
			break;
		default:
			break;
		}

	}
	void Space::loop()
	{
		while (status > Status::star)
		{
			this->render();
		}
	}

}