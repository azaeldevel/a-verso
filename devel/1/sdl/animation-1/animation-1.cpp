
//Using SDL and standard IO
#include "animation-1.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

namespace verso = oct::verso::v1;


const int ScreenWidth = 800;
const int ScreenHeight = 600;
verso::SDL::Scenary scenary;

// texture manager
static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);


int main(int argc, char* args[])
{
	const int FPS = 60;
	const int frameDelay = 500 / FPS;
	uint32_t frameStart;
	int frameTime;

	scenary.initialize();
	scenary.create_window("Game", ScreenWidth, ScreenHeight);
	scenary.playertex = LoadTexture("../../../assets/player.bmp", scenary.renderer);
	scenary.enemytex = LoadTexture("../../../assets/enemy.bmp", scenary.renderer);

	bool flag = true; // winning condition

	// game loop
	while (scenary.status != verso::IScenary::Status::stop)
	{
		frameStart = SDL_GetTicks();

		// handle user events
		scenary.handleEvents();

		// update the game
		scenary.update();

		// render to the screen
		scenary.render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		if (scenary.p_destR.x >= ScreenWidth / 1.88 && flag)
		{
			printf("\n\t*No Collision Detected!*\n\t*You Won!*\n\n");
			flag = false;
		}
	}

	scenary.clean();

	return 0;
}



static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren) {
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


namespace oct::verso::v1
{
	IScenary::IScenary() : status(Status::stop)
	{
	}
	IScenary::IScenary(Status r) : status(r)
	{
	}
}
namespace oct::verso::v1::SDL
{

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
			status = Status::started;
		}
		else
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			status = Status::stop;
		}

		return true;
	}


	void Scenary::initialize()
	{
		// car position
		p_destR.w = 100;
		p_destR.h = 100;
		p_destR.y = ScreenHeight / 2;

		
	}

	void Scenary::handleEvents() {
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
		// on key press
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT:
				p_destR.x += 5;
				break;
			case SDLK_UP:
				p_destR.y -= 5;
				break;
			default:
				break;
			}
		}

		// enemy position
		e_destR.w = 45;
		e_destR.h = 45;
		e_destR.x = ScreenWidth / 2 - e_destR.w / 2;
		e_destR.y = ScreenHeight / 1.6 - e_destR.h / 1.6;

		// collision detection and game over
		if (AABB(p_destR, e_destR)) {
			printf("\n\t*Collision Detected!*\n");
			printf("\t*Game Over!*\n\n");
			status = Status::stop;
		}

	}

	void Scenary::render() {
		// this is where we add stuff (textutes) to render
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, playertex, NULL, &p_destR);
		SDL_RenderCopy(renderer, enemytex, NULL, &e_destR);
		SDL_RenderPresent(renderer);
	}

	void Scenary::clean() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		printf("Game cleaned!\n");
	}


	bool Scenary::AABB(SDL_Rect recA, SDL_Rect recB) {
		if (
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.y) {
			return true;
		}
		return false;
	}
}