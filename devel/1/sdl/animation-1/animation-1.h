#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>

namespace oct::verso::v1
{
	enum class Status
	{
		stop,//igual a false
		started,
	};
	struct IScenary
	{
		Status status;

		IScenary();
		IScenary(Status);
		virtual void initialize() = 0;
	};

}
namespace oct::verso::v1::SDL
{
	struct Scenary : public IScenary
	{
		SDL_Window* window; // window
		SDL_Renderer* renderer; // renderer
		//bool isRunning; // check if the game is running
		SDL_Texture* playertex; // player sprite 
		SDL_Texture* enemytex; // enemy sprite
		SDL_Rect p_srcR, p_destR; // player source and destination rectangles
		SDL_Rect e_srcR, e_destR; // enemy source and destination rectangles
		SDL_Event event; // event
		int counter;

		virtual void initialize();
		bool create_window(const char* title, int width, int height);
		void update();
		void render();
		void clean();
		void handleEvents();
		bool AABB(SDL_Rect recA, SDL_Rect recB);
	};
}