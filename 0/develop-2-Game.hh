
#include "Verso.hh"


class Game : public oct::verso::Verso
{
public:
    virtual bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    virtual void rendering();
    virtual void clean();
    virtual void handleEvents();

private:
    SDL_Window* window;
    SDL_Renderer* render;
};
