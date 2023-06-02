
#include "develop-2-Game.hh"


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    // attempt to initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        //std::cout << "SDL init success\n";
        // init the window
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window != 0) // window init success
        {
            //std::cout << "window creation success\n";
            render = SDL_CreateRenderer(window, -1, 0);
            if(render != 0) // renderer init success
            {
                //std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(render, 255,255,255,255);
            }
            else
            {
                //std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            //std::cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        //std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }
    //std::cout << "init success\n";
    running = true; // everything inited successfully, start the main loop
    return true;
}

void Game::rendering()
{
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
}


void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }
    }
}

