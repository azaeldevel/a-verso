

#include <filesystem>
#include <SDL.h>
//#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Verso.hh"
#include "shapes.hh"

namespace verso_here = oct::verso::v0;

class Game : public verso_here::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    virtual void rendering();
    virtual void clean();
    virtual void handleEvents();
    virtual void update();

private:
    SDL_Window* window;
    SDL_Renderer* render;


};
