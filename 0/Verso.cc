
#include "Verso.hh"

namespace oct::verso
{

    Verso::~Verso()
    {
    }


    void Verso::init()
    {
        running = true;
    }
    void Verso::rendering()
    {

    }
    void Verso::update()
    {
    }
    void Verso::handleEvents()
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
    void Verso::clean()
    {

    }

    bool Verso::is_running()
    {
        return running;
    }


}
