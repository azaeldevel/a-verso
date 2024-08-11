#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>

namespace oct::verso::v1
{

	struct IScenary
	{
		bool running;
		SDL_Window* window; // window
		SDL_Renderer* renderer; // renderer

		virtual void initialize() = 0;

		bool create_window(const char* title, int width, int height);
	};

	struct Scenary : public IScenary
	{
		//bool isRunning; // check if the game is running
		SDL_Texture* playertex; // player sprite 
		SDL_Texture* enemytex; // enemy sprite
		SDL_Rect p_srcR, p_destR; // player source and destination rectangles
		SDL_Rect e_srcR, e_destR; // enemy source and destination rectangles
		SDL_Event event; // event
		int counter;

		virtual void initialize();
		void update();
		void render();
		void clean();
		void handleEvents();
		bool AABB(SDL_Rect recA, SDL_Rect recB);
	};
}