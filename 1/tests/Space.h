
#include "../sdl/scenary.hpp"
#include <string>
#include <vector>

namespace oct::verso::v1::devel
{
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	//A circle stucture
	struct Circle
	{
		int x, y;
		int r;
	};

	double distanceSquared(int x1, int y1, int x2, int y2);
	bool checkCollision(Circle& a, SDL_Rect& b);
	bool checkCollision(Circle& a, Circle& b);

	//Texture wrapper class
	class LTexture
	{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path, SDL_Renderer*);

#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(int x, int y, SDL_Renderer*, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
	};

	//The dot that will move around on the screen
	class Dot
	{
	public:
		//The dimensions of the dot

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 1;

		//Initializes the variables
		Dot(int x, int y);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent(SDL_Event& e);

		//Moves the dot and checks collision
		void move(SDL_Rect& square, Circle& circle);

		//Shows the dot on the screen
		void render(LTexture&, SDL_Renderer*);

		//Gets collision circle
		Circle& getCollider();

	private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision circle
		Circle mCollider;

		//Moves the collision circle relative to the dot's offset
		void shiftColliders();
	};

	struct Collisions : public SDL::Scenary
	{
		Collisions();

		virtual bool initialize();
		virtual void render();
		virtual void loop();
		virtual void clean();
		virtual void run();

		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
		Dot dot, otherDot;

		SDL_Rect wall;
		LTexture gDotTexture;

		bool loadMedia();
	};
}