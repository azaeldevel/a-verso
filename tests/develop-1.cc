
#include<SDL.h>
SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool g_bRunning = false;

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
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

void render()
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
int main(int argc, char* args[])
{
    if(init("Chapter 1: Setting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN))
    {
        g_bRunning = true;
    }
    else
    {
        return 1; // something's wrong
    }

    //while(g_bRunning)
    {
        render();
    }

    SDL_Quit();

    return 0;
}
