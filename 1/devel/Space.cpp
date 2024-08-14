
//Using SDL and standard IO
#include "Space.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <iostream>

namespace verso = oct::verso::v1;


namespace oct::verso::v1::devel
{
	Collisions::Collisions() : dot(DOT_WIDTH / 2, DOT_HEIGHT / 2), otherDot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4)
	{
	}
	bool Collisions::initialize()
	{
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning: Linear texture filtering not enabled!");
			}

			//Create window
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				//Create vsynced renderer for window
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					return false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						return false;
					}
				}
			}
		}

		wall.x = 300;
		wall.y = 40;
		wall.w = 40;
		wall.h = 400;
		status = Status::running;

		return true;
	}
	void Collisions::render()
	{
		//std::cout << "Rendering..\n";
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			status = Status::stop;
			break;
		default:
			break;
		}

		//Move the dot and check collision
		dot.move(wall, otherDot.getCollider());

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Render wall
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &wall);

		//Render dots
		dot.render(gDotTexture,renderer);
		otherDot.render(gDotTexture, renderer);

		//Update screen
		SDL_RenderPresent(renderer);
	}
	void Collisions::loop()
	{
		//Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			//User requests quit
			if (event.type == SDL_QUIT)
			{
				status = Status::stop;
			}

			//Handle input for the dot
			dot.handleEvent(event);
		}

		//Move the dot and check collision
		dot.move(wall, otherDot.getCollider());

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Render wall
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &wall);

		//Render dots
		dot.render(gDotTexture, renderer);
		otherDot.render(gDotTexture, renderer);

		//Update screen
		SDL_RenderPresent(renderer);
	}
	bool Collisions::loadMedia()
	{
		//Load dot texture
		if (!gDotTexture.loadFromFile("../../../../devel/assets/dot.bmp", renderer))
		{
			printf("Failed to load dot texture!\n");
			return false;
		}
		return true;
	}

	void Collisions::clean()
	{
		//Free loaded images
		gDotTexture.free();

		//Destroy window	
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		renderer = NULL;
		window = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
	}
	void Collisions::run()
	{
		//Start up SDL and create window
		if (!initialize())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{

				//While application is running
				while (status > Status::star)
				{
					loop();
				}
			}
		}

		//Free resources and close SDL
		clean();
	}







	


	bool checkCollision(Circle& a, Circle& b)
	{
		//Calculate total radius squared
		int totalRadiusSquared = a.r + b.r;
		totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

		//If the distance between the centers of the circles is less than the sum of their radii
		if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared))
		{
			//The circles have collided
			return true;
		}

		//If not
		return false;
	}

	bool checkCollision(Circle& a, SDL_Rect& b)
	{
		//Closest point on collision box
		int cX, cY;

		//Find closest x offset
		if (a.x < b.x)
		{
			cX = b.x;
		}
		else if (a.x > b.x + b.w)
		{
			cX = b.x + b.w;
		}
		else
		{
			cX = a.x;
		}

		//Find closest y offset
		if (a.y < b.y)
		{
			cY = b.y;
		}
		else if (a.y > b.y + b.h)
		{
			cY = b.y + b.h;
		}
		else
		{
			cY = a.y;
		}

		//If the closest point is inside the circle
		if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
		{
			//This box and the circle have collided
			return true;
		}

		//If the shapes have not collided
		return false;
	}

	double distanceSquared(int x1, int y1, int x2, int y2)
	{
		int deltaX = x2 - x1;
		int deltaY = y2 - y1;
		return deltaX * deltaX + deltaY * deltaY;
	}







	LTexture::LTexture()
	{
		//Initialize
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	LTexture::~LTexture()
	{
		//Deallocate
		free();
	}

	bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
	{
		//Get rid of preexisting texture
		free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				//Get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		mTexture = newTexture;
		return mTexture != NULL;
	}

#if defined(SDL_TTF_MAJOR_VERSION)
	bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
	{
		//Get rid of preexisting texture
		free();

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
		if (textSurface != NULL)
		{
			//Create texture from surface pixels
			mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
			if (mTexture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
		else
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}


		//Return success
		return mTexture != NULL;
	}
#endif

	void LTexture::free()
	{
		//Free texture if it exists
		if (mTexture != NULL)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
		}
	}

	void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		//Modulate texture rgb
		SDL_SetTextureColorMod(mTexture, red, green, blue);
	}

	void LTexture::setBlendMode(SDL_BlendMode blending)
	{
		//Set blending function
		SDL_SetTextureBlendMode(mTexture, blending);
	}

	void LTexture::setAlpha(Uint8 alpha)
	{
		//Modulate texture alpha
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}

	int LTexture::getWidth()
	{
		return mWidth;
	}

	int LTexture::getHeight()
	{
		return mHeight;
	}

	Dot::Dot(int x, int y)
	{
		//Initialize the offsets
		mPosX = x;
		mPosY = y;

		//Set collision circle size
		mCollider.r = DOT_WIDTH / 2;

		//Initialize the velocity
		mVelX = 0;
		mVelY = 0;

		//Move collider relative to the circle
		shiftColliders();
	}

	void Dot::handleEvent(SDL_Event& e)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY += DOT_VEL; break;
			case SDLK_DOWN: mVelY -= DOT_VEL; break;
			case SDLK_LEFT: mVelX += DOT_VEL; break;
			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
			}
		}
	}

	void Dot::move(SDL_Rect& square, Circle& circle)
	{
		//Move the dot left or right
		mPosX += mVelX;
		shiftColliders();

		//If the dot collided or went too far to the left or right
		if ((mPosX - mCollider.r < 0) || (mPosX + mCollider.r > SCREEN_WIDTH) || checkCollision(mCollider, square) || checkCollision(mCollider, circle))
		{
			//Move back
			mPosX -= mVelX;
			shiftColliders();
		}

		//Move the dot up or down
		mPosY += mVelY;
		shiftColliders();

		//If the dot collided or went too far up or down
		if ((mPosY - mCollider.r < 0) || (mPosY + mCollider.r > SCREEN_HEIGHT) || checkCollision(mCollider, square) || checkCollision(mCollider, circle))
		{
			//Move back
			mPosY -= mVelY;
			shiftColliders();
		}
	}

	void Dot::render(LTexture& gDotTexture, SDL_Renderer* r)
	{
		//Show the dot
		gDotTexture.render(mPosX - mCollider.r, mPosY - mCollider.r,r);
	}

	Circle& Dot::getCollider()
	{
		return mCollider;
	}

	void Dot::shiftColliders()
	{
		//Align collider to center of dot
		mCollider.x = mPosX;
		mCollider.y = mPosY;
	}

}