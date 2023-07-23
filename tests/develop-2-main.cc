
#include "develop-2-Game.hh"

int main(int argc, char* argv[])
{
    Game g_game;//("ing/library/spritelib_gpl/spritelib_gpl");
    g_game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    while(g_game.is_running())
    {
        g_game.rendering();
    }

    g_game.clean();
    return 0;
}
