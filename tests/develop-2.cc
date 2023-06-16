
#include "Verso.hh"


class Game : public oct::verso::Verso
{
public:
    virtual bool init(const char* title, int xpos, int ypos, int width, int height, int flags)
    {
        // initialize SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
        {
            // if succeeded create our window
            g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
            // if the window creation succeeded create our renderer
            if(g_pWindow != 0)
            {
                g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
            }
        }
        else
        {
            return false; // sdl could not initialize
        }

        return true;
    }

    virtual void render()
    {
        // everything succeeded lets draw the window
        // set to black // This function expects Red, Green, Blue and
        // Alpha as color values
        SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
        // clear the window to black
        SDL_RenderClear(g_pRenderer);
        // show the window
        SDL_RenderPresent(g_pRenderer);
        // set a delay before quitting
        SDL_Delay(5000);
        // clean up SDL
    }


private:
    SDL_Window* g_pWindow = 0;
    SDL_Renderer* g_pRenderer = 0;
};


int main(int argc, char* argv[])
{
    Game g_game;
    g_game.init("Chapter 1", 100, 100, 640, 480, 0);
    while(g_game.is_running())
    {
        g_game.handleEvents();
        g_game.update();
        g_game.render();
    }

    g_game.clean();
    return 0;
}
