#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "../../scenary.hh"

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

		virtual bool initialize();
		void update();
		virtual void render();
		bool AABB(SDL_Rect recA, SDL_Rect recB);

		int main(int argc, char* args[]);
	};
}
