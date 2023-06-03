#include <SDL_image.h>

#include "develop-2-Game.hh"

/*Game::Game(const std::filesystem::path& p) : path(p)
{
}*/

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

    /*IMG_Init(IMG_INIT_PNG);
    m_pTexture = IMG_LoadTexture(render, (path/"platform/char9.png").string().c_str());

    m_sourceRectangle.w = 20;
    m_sourceRectangle.h = 20;
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 70;
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;
    m_destinationRectangle.w = 100;
    m_destinationRectangle.h = 100;
    SDL_QueryTexture(m_pTexture, NULL, NULL,&m_sourceRectangle.w, &m_sourceRectangle.h);*/

    rect1.w = 100;
    rect1.h = 100;
    rect1.x = 100;
    rect1.y = 100;

    return true;
}

void Game::rendering()
{
    SDL_RenderClear(render);

    //SDL_RenderCopy(render, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    //SDL_SetRenderDrawColor(render, 0,0,0,0);
    SDL_RenderDrawLine(render,rect1.x,rect1.y,rect1.x + rect1.w,rect1.y + rect1.h);


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

