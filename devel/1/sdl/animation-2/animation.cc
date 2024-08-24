﻿

#include "animation.hh"
#include "space.hh"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "SDL2_gfxPrimitives.h"//https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html

/*void (*glEnable) (int) ;
void (*glLogicOp) (int) ;
void (*glDisable) (int) ;*/

namespace verso = oct::verso::v1;


const int ScreenWidth = 800;
const int ScreenHeight = 600;
verso::SDL::Game scenary;
verso::SDL::Space space;

// texture manager
static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

int cmd = 2;

int main(int argc, char* args[])
{
	switch (cmd)
	{
	case 1:
	    scenary.run();
		break;
	case 2:
        space.run();
		break;
	}
	return EXIT_SUCCESS;
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

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
const int32_t diameter = (radius * 2);

int32_t x = (radius - 1);
int32_t y = 0;
int32_t tx = 1;
int32_t ty = 1;
int32_t error = (tx - diameter);

while (x >= y)
{
// Each of the following renders an octant of the circle
SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

  if (error <= 0)
  {
  	++y;
  	error += ty;
  	ty += 2;
  }

  if (error > 0)
  {
  	--x;
  	tx += 2;
  	error += (tx - diameter);
  }
}
}



namespace oct::verso::v1::SDL
{


	bool Game::initialize()
	{
		p_destR.w = 100;
		p_destR.h = 100;
		p_destR.y = ScreenHeight / 2;

		create_window("Game", ScreenWidth, ScreenHeight);
		playertex = LoadTexture("devel/1/sdl/animation-2/assets/player.bmp", renderer);
		enemytex = LoadTexture("devel/1/sdl/animation-2/assets/enemy.bmp", renderer);
		status = Status::running;
		flag = true; // winning condition

		return false;
	}


	void Game::update()
	{
		// on key press
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
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

	void Game::render() {
		// this is where we add stuff (textutes) to render
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, playertex, NULL, &p_destR);
		SDL_RenderCopy(renderer, enemytex, NULL, &e_destR);
		SDL_RenderPresent(renderer);
	}



	bool Game::AABB(SDL_Rect recA, SDL_Rect recB)
	{
		if (
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.y) {
			return true;
		}
		return false;
	}

	void Game::loop()
	{
        // game loop
		while (status != Status::stop)
		{
			frameStart = SDL_GetTicks();

			// handle user events
			handler();

			// update the game
			update();

			// render to the screen
			render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}

			if (p_destR.x >= ScreenWidth / 1.88 && flag)
			{
				printf("\n\t*No Collision Detected!*\n\t*You Won!*\n\n");
				flag = false;
			}
		}
	}








}
