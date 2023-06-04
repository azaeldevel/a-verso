

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
            if(render) // renderer init success
            {
                //std::cout << "renderer creation success\n";
                //SDL_SetRenderDrawColor(render, 255,255,255,255);
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

    p0.set(0,0);
    pU.set(1,1);
    O.set(0,0);

    verso_here::Point<int,2,float> p4 {50,50};
    verso_here::Point<int,2,float> p5 {100,100};

    line1.set(p0,p5);
    line1.move(p4);


    return true;
}

void Game::rendering()
{
    SDL_RenderClear(render);

    //SDL_RenderCopy(render, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

    SDL_SetRenderDrawColor(render, 255,255,255,255);
    //SDL_RenderDrawLine(render,rect1.x,rect1.y,rect1.x + rect1.w,rect1.y + rect1.h);
    line1.draw(render);
    SDL_SetRenderDrawColor(render, 0,0,0,255);

    SDL_RenderPresent(render);

    SDL_Delay(100);
}
void Game::update()
{
    line1.move(pU);
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

