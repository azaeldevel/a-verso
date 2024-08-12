#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

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
		virtual bool initialize() = 0;
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

		virtual bool initialize();
		void update();
		virtual void render();
		bool AABB(SDL_Rect recA, SDL_Rect recB);

		int main(int argc, char* args[]);
	};

	struct OpenGL : public Scenary
	{
		//OpenGL context
		SDL_GLContext gContext;

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
	};
}