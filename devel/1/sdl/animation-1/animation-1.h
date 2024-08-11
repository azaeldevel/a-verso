#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>

namespace oct::verso::v1
{
	struct IScenary
	{
		enum Status
		{
			stop,//igual a false
			started,
		};
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
		SDL_Event event; // event

		Scenary();
		bool create_window(const char* title, int width, int height);
		void handleEvents();
		void clean();
		virtual void render() = 0;
	};

	struct Game : public Scenary
	{
		SDL_Texture* playertex; // player sprite 
		SDL_Texture* enemytex; // enemy sprite
		SDL_Rect p_srcR, p_destR; // player source and destination rectangles
		SDL_Rect e_srcR, e_destR; // enemy source and destination rectangles
		int counter;

		virtual void initialize();
		void update();
		virtual void render();
		bool AABB(SDL_Rect recA, SDL_Rect recB);
	};
}