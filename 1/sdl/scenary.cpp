
#include "scenary.hpp"







namespace oct::verso::v1::SDL
{
	SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren) {
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = SDL_LoadBMP(fileName);
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", fileName, IMG_GetError());
		}
		else {
			newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
			}
			SDL_FreeSurface(loadedSurface);
		}
		return newTexture;
	}

	Scenary::Scenary() : window(NULL), renderer(NULL), event{0}
	{
	}

	bool Scenary::create_window(const char* title, int width, int height)
	{
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
		status = Status::stop;

		return true;
	}

	void Scenary::handleEvents() 
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

	void Scenary::clean() 
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		printf("Game cleaned!\n");
	}
	
}