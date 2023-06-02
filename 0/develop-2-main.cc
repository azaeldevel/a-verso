
#include "develop-2-Game.hh"

int main(int argc, char* argv[])
{
    Game g_game;
    g_game.init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    while(g_game.is_running())
    {
        g_game.handleEvents();
        g_game.update();
        g_game.rendering();
    }

    g_game.clean();
    return 0;
}
