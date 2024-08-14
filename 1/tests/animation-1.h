
#include "../sdl/scenary.hpp"

namespace oct::verso::v1::devel
{
	struct Game : public SDL::Scenary
	{
		SDL_Texture* playertex; // player sprite 
		SDL_Texture* enemytex; // enemy sprite
		SDL_Rect p_srcR, p_destR; // player source and destination rectangles
		SDL_Rect e_srcR, e_destR; // enemy source and destination rectangles
		int counter;
		uint32_t frameStart;
		int frameTime;
		const int FPS = 60;
		const int frameDelay = 500 / FPS;
		bool flag = true; // winning condition

		virtual bool initialize();
		void update();
		virtual void render();
		bool AABB(SDL_Rect recA, SDL_Rect recB);
		void handleEvents();

		int main(int argc, char* args[]);
		virtual void run();
		virtual void loop();
	};

	struct OpenGL : public SDL::OpenGL
	{
		//Render flag
		bool gRenderQuad = true;

		//Graphics program
		GLuint gProgramID = 0;
		GLint gVertexPos2DLocation = -1;
		GLuint gVBO = 0;
		GLuint gIBO = 0;


		//Starts up SDL, creates window, and initializes OpenGL
		virtual bool initialize();
		//Initializes rendering program and clear color
		bool initGL();
		//Input handler
		void handleKeys(unsigned char key, int x, int y);
		//Per frame update
		void update();
		//Renders quad to the screen
		void render();
		//Frees media and shuts down SDL
		void close();
		//Shader loading utility programs
		void printProgramLog(GLuint program);
		void printShaderLog(GLuint shader);

		int main(int argc, char* args[]);

		virtual void run();
		virtual void loop();
	};
}