
#ifndef OCTETOS_AVERSO_VERSO_HH
#define OCTETOS_AVERSO_VERSO_HH


#include<SDL.h>

namespace oct::verso
{

    class Verso
    {
    private:

    protected:
        bool running;

        SDL_Window* window;
        SDL_Renderer* render;

    public:
        virtual ~Verso();

        virtual void init();
        virtual void rendering();
        virtual void update();
        virtual void handleEvents();
        virtual void clean();

        bool is_running();
    };
}

#endif // OCTETOS_AVERSO_AVERSO_HH
